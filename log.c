//
// Created by ruansheng on 16/4/23.
//
#include "log.h"

void logger(int line, const char *level, const char *msg) {
    struct tm *p;
    time_t timep;
    time(&timep);
    p = localtime(&timep);
    char time[20];
    sprintf(time, "%d-%d-%d %d:%d:%d", (p->tm_year + 1900), (p->tm_mon + 1), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    printf("[%s] line %d [%s]:%s\n", time, line, level, msg);
}