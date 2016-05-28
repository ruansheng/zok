//
// Created by ruansheng on 16/4/8.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<unistd.h>

#define ZOK_OK 0
#define ZOK_ERR -1

#include "version.h"
#include "net.h"
#include "log.h"
#include "util.h"
#include "zds.h"

typedef struct Object{
    void *val;
} zobj;

typedef struct {
    zds obuf;
} zokClient;

/* define function pointer */
typedef void commandFunc(zokClient *c);

typedef struct{
    char *name;
    commandFunc *func; /* function pointer */
}zCommand;

typedef struct{
    pid_t pid;
    zokAddr *zokaddr;
    event *event;
    int daemonize;
    char *conf_filename;
} zokServer;

/* exec command function */
/* string */
void setCommand(zokClient *c);
void getCommand(zokClient *c);
void delCommand(zokClient *c);
void ttlCommand(zokClient *c);

/* system  */
void pingCommand(zokClient *c);
void infoCommand(zokClient *c);

void initServer(zokServer *server);