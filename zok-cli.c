//
// Created by ruansheng on 16/4/8.
//

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//#include "version.h"

typedef struct client{
    char *host;
    int ip;
    int sock;
    char *line;
    char *cmd;
} client;

int socket_create() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        perror("socket error.\n");
        exit(0);
    }
    return sock;
}

void socket_connect(client *c) {
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));       /* Clear struct */
    server.sin_family = AF_INET;                  /* Internet/IP */
    server.sin_addr.s_addr = inet_addr(c->host);  /* IP address */
    server.sin_port = htons(c->ip);
    if (connect(c->sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Failed to connect with server.\n");
        exit(1);
    }
}

void socket_read(client *c) {
    char buf[1024];
    int s = recv(c->sock, buf, 1024, 0);
    if(s != -1) {
        perror("Mismatch in number of sent bytes");
        exit(1);
    }
    printf("%s\n", buf);
}

void socket_send(client c, char *msg) {
    int s = send(sock, msg, strlen(msg), 0);
    if(s == -1) {
        perror("Mismatch in number of sent bytes");
        exit(1);
    }
}

void close_sock(client *c) {
    close(c->sock);
    exit(0);
}

/**
 * splitString
 */
void splitString(client *clio) {
    const char *c = clio->line;
    char cmd[3][1024];
    int i = 0;
    int j = 0;
    int total = 0;
    while(*c != '\0') {
        if(*c == ' ') {
            cmd[i][j] = '\0';
            i++;
            j = 0;
            c++;
            while(*c == ' ') {
                *c++;
            }
        } else {
            cmd[i][j] = *c;
            j++;
            c++;
            total++;
        }
    }

    char *str = (char *)malloc(total + 9); // *queue \n set \n name \n ruansheng
    if(str == NULL) {
        printf("malloc error\n");
        exit(1);
    }
    char *tmp = str;
    strcpy(str, "*queue\n");
    str += 7;
    for(int s = 0; s <= i; s++) {
        strcpy(str, cmd[s]);
        str += strlen(cmd[s]);
        strcpy(str, "\n");
        str += 1;
    }
    clio->cmd = tmp;
}

/**
 * sendCommand
 */
void sendCommand(client *clio) {
    write(clio->sock, clio->cmd, strlen(clio->cmd) + 1);
}

/**
* 获取输入的command
* command length <= 100
*/
void getLineKey(client *clio) {
    printf("%s:%d>", clio->host, clio->port);
    char line[1024];
    memset(line, '\0', 1014);
    fgets(line, 1024, stdin);
    clio->line = (char *)malloc(strlen(line));
    strcpy(clio->line, line);

    splitString(clio);
    sendCommand(clio);
}

/**
 * getResponse
 */
void getResponse(client *clio) {
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    read(clio->sock, buffer, 1024);
    printf("%s \n", buffer);
}


client cli;

int main(int argc, char *argv[]) {
    cli.host = "127.0.0.1";
    cli.ip = 10032;

    cli.sock = socket_create();
    socket_connect(&cli);

    for(;;) {
        getLineKey(&cli);
        sendCommand(&cli);
        getResponse(&cli);
    }
    return 0;
}