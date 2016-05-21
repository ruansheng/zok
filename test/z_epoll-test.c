//
// Created by ruansheng on 16/5/21.
//

#include "../z_epoll.h"

int main(int argc, char *argv[]) {
    int listenfd = socket_create();
    int port = atoi(argv[1]);
    socket_bind(listenfd, "127.0.0.1", port);
    socket_listen(listenfd);
    do_event(listenfd);
}