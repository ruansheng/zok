//
// Created by ruansheng on 16/4/8.
//

#include<stdio.h>
#include<sys/time.h>

#include "version.h"
#include "zds.h"
#include "util.h"


#define ZOK_COMMAND_OK 0
#define ZOK_COMMAND_ERR -1

typedef struct zokClient{
    char *ip;
    int port;
    int sock;
    char prompt[128];
    zds obuf;
} zokClient;

int zokCommandArgvToString(zokClient *zc, int argc, char **argv);

int zokFormatCommandArgvToString(char **target, int argc, char **argv);