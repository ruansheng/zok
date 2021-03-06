//
// Created by ruansheng on 16/4/8.
//

#include "zok.h"

/* global var */
struct zokServer server;

zokCommand commandTables[] ={
    {"set", setCommand},
    {"get", getCommand},
    {"del", delCommand},
    {"ttl", ttlCommand},
    {"ping", pingCommand},
    {"info", infoCommand}
};

/**
 * echo zok version
 */
void version() {
    printf("zok server version %s \n", ZOK_VERSION);
    exit(0);
}

/**
 * echo zok help
 */
void usage() {
    printf("Usage: ./zok-server -v or --version\n");
    printf("       ./zok-server -h or --help\n");
    printf("       ./zok-server \n");
    printf("       ./zok-server -c ./zok.conf or --conf ./zok.conf\n");
    printf("       ./zok-server -d true or -d false or --daemon true or --daemon false\n");
    exit(0);
}

/**
 * daemonize
 */
void daemonize() {
    int pid = fork();

    //是父进程，结束父进程
    if(pid > 0) exit(0);

    //fork失败，退出
    if(pid < 0) exit(1);

    //第一子进程成为新的会话组长和进程组长
    setsid();

    //重定向输出到/dev/null
    int fd;
    if ((fd = open("/dev/null", 0x0002)) != -1) {
        dup2(fd, 0);
        dup2(fd, 1);
        dup2(fd, 2);
        if (fd > 2) close(fd);
    }

    server.pid = pid;
}

void setCommand(context *c) {

}

void getCommand(context *c) {

}

void delCommand(context *c) {

}

void ttlCommand(context *c) {

}

void pingCommand(context *c) {

}

void infoCommand(context *c) {

}

/**
 * initServer
 */
void initServer() {
    server.pid = getpid();
    server.zokaddr = (zokAddr *)malloc(sizeof(zokAddr));
    server.zokaddr->host = ZOK_HOST;
    server.zokaddr->port = ZOK_PORT;
    server.daemonize = 0;
    server.conf_filename = NULL;
    server.event = (event *)malloc(sizeof(event));
}

/*
int zokStringToCommandArgv(context *ctx, int argc, char **argv) {
    char *cmd;
    int len;
    len = zokStringToFormatCommandArgv(&cmd, argc, argv);
    if(len == -1) {
        printf("Out of memory");
        return ZOK_ERR;
    }

    zds z = newlenzds(cmd, len);
    if(z == NULL) {
        free(cmd);
        printf("newlenzds alloc memory");
        return ZOK_ERR;
    }
    ctx->obuf = z;
    free(cmd);
    return ZOK_OK;
}
*/

/*
int zokStringToFormatCommandArgv(char **target, int argc, char **argv) {
    int i, total;

    total = 1 + intlen(argc) + 2; //  add first line "*3\r\n" string length
    for(i = 0; i < argc; i++) {
        int len = strlen(argv[i]);
        total += bulklen(len); // add an cmd item two line "$3\r\n" and "set\r\n" string length
    }

    char *cmd = (char *)malloc(total + 1); //  add total cmd + '\0' string length
    if(cmd == NULL) return -1;

    int pos = sprintf(cmd, "*%d\r\n", argc);
    for(i = 0; i < argc; i++) {
        int len = strlen(argv[i]);
        pos += sprintf(cmd + pos, "$%d\r\n", len);
        memcpy(cmd + pos, argv[i], len);
        pos += len;
        cmd[pos++] = '\r';
        cmd[pos++] = '\n';
    }
    cmd[pos] = '\0';
    *target = cmd;
    return total;
}
*/

int main(int argc, char **argv) {
    initServer();
    if(argc >= 2) {
        if(strcmp(argv[1] ,"-v") == 0 || strcmp(argv[1] ,"--version") == 0) {
            version();
        }
        if(strcmp(argv[1] ,"-h") == 0 || strcmp(argv[1] ,"--help") == 0) {
            usage();
        }
        /*
        int i;
        for(i = 1; i < argc; i++) {
            if(argc == (i + 1)) {
                printf("cli params is error \n");
                exit(1);
            }
            if(strcmp(argv[i] ,"-d") == 0 || strcmp(argv[i] ,"--daemon") == 0) {
                if(strcmp(argv[i + 1] ,"true") == 0) {
                    server.daemonize = 1;
                    i++;
                } else if(strcmp(argv[i + 1] ,"false") == 0) {
                    server.daemonize = 0;
                    i++;
                } else {
                    printf("cli params -d is error \n");
                    exit(1);
                }
            } else if(strcmp(argv[i] ,"-c") == 0 || strcmp(argv[i] ,"--conf") == 0) {
                server.conf_filename = argv[i + 1];
                i++;
            } else {
                printf("cli params is error \n");
                exit(1);
            }
        }
         */
    }

    /*
    if(server.daemonize) {
        daemonize();
    }

    for(;;) {

    }

    //netMain(server.zokaddr, server.event);
    */
    return ZOK_OK;
}