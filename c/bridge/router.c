#include "cJSON.h"
#include <poll.h>
#include <semaphore.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define POOL_SIZE 256

static int flag = 0;

typedef struct {
  cJSON *pool[POOL_SIZE];
  int head;
  int tail;
  sem_t sem;
} responseQueue;

static responseQueue qSearch, qDownload, qServer;
// This is a lock to stop the reading and writing to the queue at the same time.
static sem_t semSuper;

void initQueue(responseQueue *q) {
  q->head = 0;
  q->tail = 0;
  // So this is a sephamore to make the read function wait if the queue is
  // empty.
  sem_init(&q->sem, 0, 0);
}

void enqueue(responseQueue *q, cJSON *response) {
  int next_tail = (q->tail + 1) % POOL_SIZE;
  if (next_tail == q->head) {
    cJSON_Delete(q->pool[q->head]);
    q->head = (q->head + 1) % POOL_SIZE;
    sem_trywait(&q->sem);
  }
  q->pool[q->tail] = response;
  q->tail = next_tail;
  sem_post(&q->sem);
}

cJSON *dequeue(responseQueue *q) {
  sem_wait(&q->sem);

  sem_wait(&semSuper);
  cJSON *response = NULL;
  if (q->head != q->tail) {
    response = q->pool[q->head];
    q->head = (q->head + 1) % POOL_SIZE;
  }
  sem_post(&semSuper);

  return response;
}

void *initRouter(void *temp) {

  int *IOP = (int *)temp;

  struct pollfd fds[1];
  fds[0].fd = IOP[1];
  fds[0].events = POLLIN;

  sem_init(&semSuper, 0, 1);
  initQueue(&qSearch);
  initQueue(&qDownload);
  initQueue(&qServer);

  while (flag) {
    int ret = poll(fds, 1, 100);
    if (ret <= 0)
      continue;

    sem_wait(&semSuper);

    if (fds[0].revents & POLLIN) {
      char buffer[16384];
      ssize_t bytes_read = read(IOP[1], buffer, sizeof(buffer) - 1);
      if (bytes_read <= 0) {
        sem_post(&semSuper);
        break;
      }
      buffer[bytes_read] = '\0';

      cJSON *response = cJSON_Parse(buffer);
      if (!response) {
        sem_post(&semSuper);
        continue;
      }

      cJSON *typeItem = cJSON_GetObjectItem(response, "type");
      cJSON *statusItem = cJSON_GetObjectItem(response, "status");
      char *type = typeItem ? typeItem->valuestring : "";
      int status = statusItem ? statusItem->valueint : 0;

      if (strcmp(type, "query") == 0 || status == 1) {
        enqueue(&qSearch, response);
      } else if (strcmp(type, "download") == 0) {
        enqueue(&qDownload, response);
      } else if (strcmp(type, "server") == 0) {
        enqueue(&qServer, response);
      } else {
        cJSON_Delete(response);
      }
    }

    sem_post(&semSuper);
  }
  return NULL;
}

void controlRouter(short i) { flag = i; }

void cleanupQueue(responseQueue *q) {
  while (q->head != q->tail) {
    cJSON_Delete(q->pool[q->head]);
    q->head = (q->head + 1) % POOL_SIZE;
  }
  sem_destroy(&q->sem);
}

void cleanupRouter() {
  sem_wait(&semSuper);
  cleanupQueue(&qSearch);
  cleanupQueue(&qDownload);
  cleanupQueue(&qServer);
  sem_post(&semSuper);
  sem_destroy(&semSuper);
}

cJSON *get_search() { return dequeue(&qSearch); }
cJSON *get_download() { return dequeue(&qDownload); }
cJSON *get_server() { return dequeue(&qServer); }
