//
// Created by ruansheng on 16/5/21.
//

#include<stdio.h>
#include<stdlib.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

#define LISTENQ     5      //
#define EPOLLEVENTS 100
#define MAXSIZE     1024   //read  maxsize

#define FDSIZE      1000

int socket_create();

void socket_bind(int listenfd, const char *ip, int port);

void socket_listen(int listenfd);

void do_event(int listenfd);

void add_event(int epollfd, int fd, int state);

void handle_events(int epollfd, struct epoll_event* events, int num, int listenfd, char* buf);

void handle_accept(int epollfd, int listenfd);

void do_read(int epollfd, int fd, char* buf);

void do_write(int epollfd, int fd, char* buf);

void delete_event(int epollfd, int fd, int state);

void modify_event(int epollfd, int fd, int state);