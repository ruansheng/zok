//
// Created by ruansheng on 16/4/23.
//
#include "log.h"

void logger(int line, const char *level, const char *msg) {
    struct tm *p;
    time_t timep;
    time(&timep);
    /*
    p = localltime(&timep);
    char *time = sprintf("%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    char log_line = sprintf("[%s] line %d [%s]:%s", time, level, line, msg);
    printf(log_line);
     */
}