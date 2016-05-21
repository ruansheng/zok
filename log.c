//
// Created by ruansheng on 16/4/23.
//
#include "log.h"

/**
 * mode 0 printf  1 fprintf
 */
void logger(int mode, int line, const char *level, const char *msg) {
    struct tm *p;
    time_t timep;
    time(&timep);
    p = localtime(&timep);
    char time[18];
    sprintf(time, "%d-%d-%d %d:%d:%d", (p->tm_year + 1900), (p->tm_mon + 1), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    if(mode == 0) {
        printf("[%s] line %d [%s]:%s\n", time, line, level, msg);
    } else {
        FILE *handler;
        handler=fopen(filepath,"at+");
        if(handler==NULL){
            return -1;
        }
        fprintf(handler, "[%s] line %d [%s]:%s\n", time, line, level, msg);
    }
}