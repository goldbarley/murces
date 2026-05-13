#ifndef ROUTER_H
#define ROUTER_H

#include "cJSON.h"

int initRouter(int *IOP);
void controlRouter(short i);
void cleanupRouter();

cJSON *get_search();
cJSON *get_download();
cJSON *get_server();

#endif
