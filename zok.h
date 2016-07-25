//
// Created by ruansheng on 16/4/8.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define ZOK_OK 0
#define ZOK_ERR -1

#define ZOK_HOST "127.0.0.1"
#define ZOK_PORT 10032

#include "version.h"
#include "zds.h"
//#include "net.h"
//#include "log.h"
#include "util.h"

typedef struct Object{
    void *val;
} zobj;

typedef struct context{
    int cid;
    zds raw;
    int argc;
    char **argv;
    zds obuf;
} context;

/* define function pointer */
typedef void commandFunc(context *c);

typedef struct{
    char *name;
    commandFunc *func; /* function pointer */
}zokCommand;

/* zokAddr */
typedef struct zokAddr {
    char *host;
    int port;
} zokAddr;

/* event */
typedef struct event {
    int fd;
} event;

struct zokServer{
    pid_t pid;
    zokAddr *zokaddr;
    event *event;
    int daemonize;
    char *conf_filename;
};

extern struct zokServer server;

/* exec command function */
/* string */
void setCommand(context *c);
void getCommand(context *c);
void delCommand(context *c);
void ttlCommand(context *c);

/* system  */
void pingCommand(context *c);
void infoCommand(context *c);

void initServer();