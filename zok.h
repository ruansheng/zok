//
// Created by ruansheng on 16/4/8.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define ZOK_OK 0
#define ZOK_ERR -1

#include "version.h"

typedef struct Object{
    void *val;
} zobj;

typedef struct {
    int id;

} zokClient;

/* define function pointer */
typedef void commandFunc(zokClient *c);

typedef struct{
    char *name;
    commandFunc *func; /* function pointer */
}zCommand;

typedef struct{
    pid_t pid;
    zobj *obj;
    int port;
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