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

void socket_connect(client c) {
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));       /* Clear struct */
    server.sin_family = AF_INET;                  /* Internet/IP */
    server.sin_addr.s_addr = inet_addr(c.host);  /* IP address */
    server.sin_port = htons(c.ip);
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Failed to connect with server.\n");
        exit(1);
    }
}

void socket_read(client c, char *msg) {
    if(send(sock, msg, strlen(msg), 0) != echolen) {
        perror("Mismatch in number of sent bytes");
        exit(1);
    }
}

client c;

int main(int argc, char *argv[]) {
    c.host = "127.0.0.1";
    c.ip = 10032;

    c.socket = socket_create();
    socket_connect(c);
    return 0;
}