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

int main(int argc, char **argv) {
    if(argc >= 2) {

    }

    daemonize();

    for(;;) {
        printf("s\n");
    }
    return ZOK_OK;
}