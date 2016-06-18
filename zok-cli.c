//
// Created by ruansheng on 16/4/8.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "zok-cli.h"

zokClient cli;

int zokCommandArgvToString(zokClient *zc, int argc, char **argv) {
    char *cmd;
    int len;
    len = zokFormatCommandArgvToString(&cmd, argc, argv);
    if(len == -1) {
        printf("Out of memory");
        return ZOK_COMMAND_ERR;
    }

    zds z = newlenzds(cmd, len);
    if(z == NULL) {
        free(cmd);
        printf("newlenzds alloc memory");
        return ZOK_COMMAND_ERR;
    }
    zc->ctx->obuf = z;
    free(cmd);
    return ZOK_COMMAND_OK;
}

int zokFormatCommandArgvToString(char **target, int argc, char **argv) {
    int i, total;

    total = 1 + intlen(argc) + 2; /*  add first line "*3\r\n" string length  */
    for(i = 0; i < argc; i++) {
        int len = strlen(argv[i]);
        total += bulklen(len); /*  add an cmd item two line "$3\r\n" and "set\r\n" string length  */
    }

    char *cmd = (char *)malloc(total + 1); /*  add total cmd + '\0' string length  */
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

static long long ustime(void) {
    struct timeval tv;
    long long ust;

    gettimeofday(&tv, NULL);
    ust = ((long long)tv.tv_sec)*1000000;
    ust += tv.tv_usec;
    return ust;
}

static long long mstime(void) {
    return ustime()/1000;
}

int cliConnect() {
    if(cli.sock > 0) {
        close(cli.sock);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        printf("%s\n", strerror(errno));
        return ZOK_COMMAND_ERR;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));       /* Clear struct */
    server.sin_family = AF_INET;                  /* Internet/IP */
    server.sin_addr.s_addr = inet_addr(cli.ip);  /* IP address */
    server.sin_port = htons(cli.port);
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("%s\n", strerror(errno));
        return ZOK_COMMAND_ERR;
    }

    cli.sock = sock;
    return ZOK_COMMAND_OK;
}

void socket_read() {
    char buf[1024];
    int s = recv(cli.sock, buf, 1024, 0);
    if(s != -1) {
        printf("%s\n", strerror(errno));
    }
    printf("%s\n", buf);
}

void socket_send(const char *cmd) {
    int s = send(cli.sock, cmd, strlen(cmd), 0);
    if(s == -1) {
        printf("%s\n", strerror(errno));
    }
}

/**
 * sendCommand
 */
void sendCommand() {
    int s = write(cli.sock, cli.ctx->obuf, strlen(cli.ctx->obuf));
    if(s < 0) {
        cliConnect();
        write(cli.sock, cli.ctx->obuf, strlen(cli.ctx->obuf));
    }
}

/**
* reflush connected server prompt
* command length <= 100
*/
void refreshConnectPrompt() {
    sprintf(cli.prompt, "%s:%d> ", cli.ip, cli.port);
}

context * initContext() {
    context *ctx = (context *)malloc(sizeof(context));
    ctx->cid = rand();
    ctx->raw = NULL;
    ctx->argc = 5;
    ctx->argv = NULL;
    ctx->obuf = zdsempty();
    if(ctx == NULL) {
        printf("malloc context fail\n");
        exit(0);
    }
    return ctx;
}

/**
 * getResponse
 */
void getResponse() {
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    read(cli.sock, buffer, 1024);
    printf("%s \n", buffer);
}

char *getCommand() {
    char buf[4096];
    int len;
    if(cli.sock > 0) {
        printf("%s", cli.prompt);
    } else {
        printf("not connected> ");
    }

    fflush(stdout);
    if (fgets(buf, 4096, stdin) == NULL)
        return NULL;
    len = strlen(buf);
    while(len && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
        len--;
        buf[len] = '\0';
    }
    return strdup(buf);
}

void repl() {
    int argc;
    zds *argv;
    refreshConnectPrompt();
    char *line;
    while((cli.ctx->raw = getCommand())!= NULL) {
        if(cli.ctx->raw[0] != '\0') {
            argv = zdssplitargs(cli.ctx->raw, &argc);
            if(argv == NULL) {
                printf("Invalid argument(s)\n");
                free(cli.ctx->raw);
                continue;
            } else if(argc > 0){
                cli.ctx->argc = argc;
                cli.ctx->argv = argv;
                if(strcasecmp(argv[0], "quit") == 0 || strcasecmp(argv[0], "exit") == 0) {
                    exit(0);
                } else if(argc == 3 && strcasecmp(argv[0],"connect") == 0) {
                    cli.ip = argv[1];
                    cli.port = atoi(argv[2]);
                    refreshConnectPrompt();
                    cliConnect();
                } else {
                    long long start_time = mstime(), elapsed;
                    zokCommandArgvToString(&cli, argc, argv);
                    sendCommand();
                    getResponse();
                    elapsed = mstime() - start_time;
                    // print exec time
                    printf("(%.2fs)\n",(double)elapsed/1000);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    cli.ip = "127.0.0.1";
    cli.port = 10032;
    context *ctx;

    ctx = initContext();
    cli.ctx = ctx;
    cliConnect();
    repl();

    return 0;
}