//
// Created by ruansheng on 16/4/23.
//
#include "zok.h"

/* monitorInfo */
typedef struct monitorInfo {
    time_t time;
    char *ip;
    int port;
    char *command;
} monitorInfo;