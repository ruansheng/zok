//
// Created by ruansheng on 16/5/21.
//

#include "z_epoll.h"

int socket_create() {
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1) {
        perror("socket error.\n");
        exit(0);
    }
    return listenfd;
}

void socket_bind(int listenfd, const char *ip, int port) {
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    int ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(ret == -1) {
        perror("bind error.\n");
        exit(1);
    }
}

void socket_listen(int listenfd) {
    listen(listenfd, LISTENQ);
}

void do_event(int listenfd) {
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    int ret;
    char buf[MAXSIZE];
    memset(buf, 0, MAXSIZE);

    epollfd = epoll_create(FDSIZE);
    add_event(epollfd, listenfd, EPOLLIN); //本地端口监听时间,可读

    for(;;) {
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
        handle_events(epollfd, events, ret, listenfd, buf);
    }
    close(epollfd);
}

void handle_events(int epollfd, struct epoll_event* events, int num, int listenfd, char* buf) {
    int i;
    int fd;
    for(i = 0; i < num; i++){
        fd = events[i].data.fd;
        if((fd == listenfd) && (events[i].events & EPOLLIN)) { //处理接受链接事件
            handle_accept(epollfd, listenfd);
        } else if(events[i].events & EPOLLIN) {  //处理读
            do_read(epollfd, fd, buf);
        } else if(events[i].events & EPOLLOUT) { //处理写
            do_write(epollfd, fd, buf);        //echo
        }
    }
}

void handle_accept(int epollfd, int listenfd) {
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;

    memset(&cliaddr, 0, sizeof(struct sockaddr_in));
    cliaddrlen = sizeof(cliaddr);

    clifd = accept(listenfd, (struct sockaddr *) &cliaddr, &cliaddrlen);
    if (clifd == -1) {
        perror("accept error.\n");
    }else {
        printf("accept a new client:%s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        add_event(epollfd, clifd, EPOLLIN);   //从cliaddr端口， 可读
    }
}

void do_read(int epollfd, int fd, char* buf) {
    int nread = read(fd, buf, MAXSIZE);
    if(nread == -1) {
        perror("read error.\n");
        close(fd);
        delete_event(epollfd,fd, EPOLLIN);
    } else if (nread == 0) {
        fprintf(stderr,"client close.\n");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    } else {
        printf("read message is: %s", buf);
        modify_event(epollfd, fd, EPOLLOUT);   //实现echo处理
    }
}

void do_write(int epollfd, int fd, char* buf) {
    int nwrite = write(fd, buf, strlen(buf));
    if(nwrite == -1) {
        perror("write error:");
        close(fd);
        delete_event(epollfd, fd, EPOLLOUT);
    } else {
        modify_event(epollfd, fd, EPOLLIN);
        memset(buf, 0, MAXSIZE);  //写完清空
    }
}

void add_event(int epollfd, int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void modify_event(int epollfd, int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

void delete_event(int epollfd, int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}