//
// Created by ruansheng on 16/4/23.
//
#include<stdio.h>
#include "z_epoll.h"

#define ZOK_HOST "127.0.0.1"
#define ZOK_PORT 10032

/* event */
typedef struct event {
    int fd;
} event;

/**
 * netMain
 */
void netMain(event *ev);