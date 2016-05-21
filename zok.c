//
// Created by ruansheng on 16/4/8.
//

#include "zok.h"

/* global var */
zokServer server;

zCommand commandTables[] ={
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
}

/**
 * initServer
 */
void initServer(zokServer *server) {
    server->pid = 0;
    server->host = ZOK_HOST;
    server->port = ZOK_PORT;
    server->daemonize = 0;
    server->event = (event *)malloc(sizeof(event));
}

int main(int argc, char **argv) {
    initServer(&server);
    if(argc >= 2) {
        if(strcmp(argv[1] ,"-v") == 0 || strcmp(argv[1] ,"--version") == 0) {
            version();
        }
        if(strcmp(argv[1] ,"-h") == 0 || strcmp(argv[1] ,"--help") == 0) {
            usage();
        }

        for(int i = 1; i < argc; i++) {
            if(argc == i) {
                break;
            }
            if(strcmp(argv[i] ,"-d") == 0 || strcmp(argv[i] ,"--daemon") == 0) {
                if(strcmp(argv[i + 1] ,"true") == 0) {
                    server.daemonize = 1;
                    i++;
                } else if(strcmp(argv[i + 1] ,"false") == 0) {
                    server.daemonize = 0;
                    i++;
                }
            } else if(strcmp(argv[i] ,"-c") == 0 || strcmp(argv[i] ,"--conf") == 0) {
                server.conf_filename = argv[i + 1];
                i++;
            } else {
                printf("cli params is error \n");
                exit(1);
            }
        }
    }

    printf("%s \n", server.conffile);

    exit(ZOK_OK);

    if(server.daemonize) {
        daemonize();
    }

    netMain(server.event);

    return ZOK_OK;
}