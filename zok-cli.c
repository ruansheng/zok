//
// Created by ruansheng on 16/4/8.
//

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#include "version.h"

typedef struct client{
    char *host;
    int ip;
    int socket;
} client;

int socket_create() {
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1) {
        perror("socket error.\n");
        exit(0);
    }
    return listenfd;
}

void socket_connect(client *c) {
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));       /* Clear struct */
    server.sin_family = AF_INET;                  /* Internet/IP */
    server.sin_addr.s_addr = inet_addr(c->host);  /* IP address */
    server.sin_port = htons(c->ip);
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Failed to connect with server.\n");
        exit(1);
    }
}

char *socket_read(client *c) {
    char buf[1024];
    int s = recv(c->socket, buf, 1024, 0);
    if(s != -1) {
        perror("Mismatch in number of sent bytes");
        exit(1);
    }
    return buf;
}

void socket_send(client c, char *msg) {
    int s = send(sock, msg, strlen(msg), 0);
    if(s == -1) {
        perror("Mismatch in number of sent bytes");
        exit(1);
    }
}

client cli;

int main(int argc, char *argv[]) {
    cli.host = "127.0.0.1";
    cli.ip = 10032;

    cli.socket = socket_create();
    socket_connect(&cli);
    return 0;
}