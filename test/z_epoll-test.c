//
// Created by ruansheng on 16/5/21.
//

#include "../z_epoll.h"

int main() {
    int listenfd = socket_create();
    socket_bind(listenfd, "127.0.0.1", 9527);
    socket_listen(listenfd);
    do_event(listenfd);
}