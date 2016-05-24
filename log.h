//
// Created by ruansheng on 16/4/23.
//
#include<stdio.h>
#include<time.h>

#define LOG_DEBUG "debug"
#define LOG_INFO "info"
#define LOG_WARNING "warning"
#define LOG_ERROR "error"

#define LOG_FILENAME "./zok.log"

void logger(int mode, const char *level, const char *msg);