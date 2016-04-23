//
// Created by ruansheng on 16/4/23.
//

#include "net.h"

/**
 * init_socket
 */
void init_socket(event *ev) {
    /*
    ev->port = PORT;
    ev->queue = QUEUE_SIZE;
    ev->buffer_size = BUFFER_SIZE;
     */
}

/**
 * create_bind_socket
 */
void create_bind_socket(event *ev) {
    /*
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_sockaddr.sin_port = htons(ev->port);

    int ret = bind(server_sockfd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr));
    if(ret == -1) {
        EXIT("bind socket fail");
    }

    ev->server_sockfd = server_sockfd;

    FD_ZERO(&ev->read_fds);
    FD_SET(server_sockfd, &ev->read_fds);
     */
}

/**
 * listen_socket
 */
void listen_socket(event *ev) {
    /*
    int ret = listen(ev->server_sockfd, ev->queue);
    if(ret == -1) {
        EXIT("listen socket fail");
    }
     */
}

/**
 * loop
 */
void loop(event *ev) {
    /*
    init_socket(ev);
    create_bind_socket(ev);

    listen_socket(ev);
    ev->list = init(ev->list);
    for(;;) {
        ev->temp_fds = ev->read_fds;
        int ret = select(FD_SETSIZE, &ev->temp_fds, (fd_set *)0,(fd_set *)0, (struct timeval *) 0);

        if(ret <= 0) {
            EXIT("select fd_set fail");
        }

        int nread;
        int fd;

        for(fd = 0; fd < FD_SETSIZE; fd++) {
            if(FD_ISSET(fd, &ev->temp_fds)) {
                if(fd == ev->server_sockfd) {
                    struct sockaddr_in client;
                    socklen_t addrlen = sizeof(client);
                    int connfd = accept(ev->server_sockfd, (struct sockaddr *)&client, &addrlen);
                    FD_SET(connfd, &ev->read_fds);
                } else {
                    ioctl(fd, FIONREAD, &nread);
                    if(nread == 0) {
                        close(fd);
                        FD_CLR(fd, &ev->read_fds);
                    } else {
                        char buffer[1024];
                        memset(buffer, '\0', 1024);
                        int ret = read(fd, buffer, 1024);
                        if(nread == 1 && buffer[0] == 4) { // 处理RST包
                            close(fd);
                            FD_CLR(fd, &ev->read_fds);
                        } else {
                            char *data = parseCommand(ev, buffer);
                            write(fd, data, strlen(data));
                        }
                    }
                }
            }
        }
    }
     */
}
