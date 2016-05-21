//
// Created by ruansheng on 16/4/8.
//

#include "zok.h"

/* global var */
zokServer server;

/*
zCommand commandTables[] ={
    {"set", setCommand},
    {"get", getCommand},
    {"del", delCommand},
    {"ttl", ttlCommand},
    {"ping", pingCommand},
    {"info", infoCommand}
};
*/

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
    printf("       ./zok-server -p 9527 or --port 9527\n");
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
}

/**
 * initServer
 */
void initServer(zokServer *server) {
    server->pid = 0;
    server->event = (event *)malloc(sizeof(event));
}

int main(int argc, char **argv) {
    if(argc >= 2) {
        if(strcmp(argv[1] ,"-v") == 0 || strcmp(argv[1] ,"--version") == 0) {
            version();
        }
        if(strcmp(argv[1] ,"-h") == 0 || strcmp(argv[1] ,"--help") == 0) {
            usage();
        }

        if(strcmp(argv[1] ,"-p") == 0 || strcmp(argv[1] ,"--port") == 0) {
            if(argc >= 3) {
                server.port = atoi(argv[2]);
            } else {
                printf("params is loss \n");
                exit(1);
            }
        } else {
            printf("params is loss \n");
            exit(1);
        }
        printf("port=%d\n", server.port);
    }

    initServer(&server);

    //daemonize();
    loop(server.event);
    return ZOK_OK;
}