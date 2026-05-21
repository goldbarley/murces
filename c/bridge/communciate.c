#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include "communciate.h"
#include "cJSON.h"
#include "router.h"
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t orchestrator_pid = -1;

int *init_orchestrator(int mode) {
  static int orcIO[3];
  if (orchestrator_pid != -1)
    return NULL;

  if (mode == 0) {
    if (access("./murces-orchestrator", X_OK) == 0) {
      orcIO[0] = -1;
      orcIO[1] = -1;
      return orcIO;
    } else {
      return NULL;
    }

    return 0;
  }

  int orcInput[2];
  int orcOutput[2];

  if (pipe(orcInput) == -1 || pipe(orcOutput) == -1) {
    perror("Pipe failed");
    return NULL;
  }

  orchestrator_pid = fork();

  if (orchestrator_pid == 0) {
    dup2(orcInput[0], STDIN_FILENO);
    dup2(orcOutput[1], STDOUT_FILENO);
    execlp("./murces-orchestrator", "./murces-orchestrator", NULL);
    perror("execlp failed");
    exit(1);
  } else if (orchestrator_pid > 0) {
    close(orcInput[0]);
    close(orcOutput[1]);
    orcIO[0] = orcInput[1];
    orcIO[1] = orcOutput[0];
    return orcIO;
  } else {
    perror("fork failed");
    return NULL;
  }
}

char **search(const char *modBrowser, const char *query, const char *version,
              const char *modLoader, int *orcIO) {

  cJSON *temp = cJSON_CreateObject();
  cJSON_AddStringToObject(temp, "type", "modding");
  cJSON_AddStringToObject(temp, "modBrowser", modBrowser);
  cJSON_AddStringToObject(temp, "subType", "search");
  cJSON_AddStringToObject(temp, "modName", query);
  cJSON_AddStringToObject(temp, "version", version);
  cJSON_AddStringToObject(temp, "modLoader", modLoader);
  cJSON_AddStringToObject(temp, "modId", "");

  char *request = cJSON_PrintUnformatted(temp);
  cJSON_Delete(temp);

  if (!request)
    return NULL;

  dprintf(orcIO[0], "%s\n", request);
  free(request);

  cJSON *response = get_search();

  if (!response)
    return NULL;

  int status = cJSON_GetObjectItem(response, "status")->valueint;
  if (status == 1)
    return NULL;

  cJSON *mods = cJSON_GetObjectItem(response, "mods");
  int count = cJSON_GetArraySize(mods);

  char **results = malloc((count + 1) * sizeof(char *));
  if (!results) {
    cJSON_Delete(response);
    return NULL;
  }

  for (int i = 0; i < count; i++) {
    cJSON *mod = cJSON_GetArrayItem(mods, i);
    if (cJSON_IsArray(mod) && cJSON_GetArraySize(mod) >= 2) {
      cJSON *title = cJSON_GetArrayItem(mod, 1);
      results[i] = strdup(title->valuestring);
    }
  }
  results[count] = NULL;

  cJSON_Delete(response);
  return results;
}

// #include <signal.h>

void cleanup_orchestrator(int *orcIO) {
  if (orchestrator_pid != -1) {
    cJSON *kill_req = cJSON_CreateObject();
    cJSON_AddStringToObject(kill_req, "type", "kill");
    char *kill_str = cJSON_PrintUnformatted(kill_req);
    if (kill_str) {
      dprintf(orcIO[0], "%s\n", kill_str);
      free(kill_str);
    }
    cJSON_Delete(kill_req);

    int status;
    waitpid(orchestrator_pid, &status, 0);

    orchestrator_pid = -1;
  }
}
