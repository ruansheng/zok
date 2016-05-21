//
// Created by ruansheng on 16/4/23.
//

#include "net.h"
#include "z_epoll.h"

/**
 * loop
 */
void netMain(event *ev) {
    int listenfd = socket_create();
    int port = atoi(argv[1]);
    socket_bind(listenfd, "127.0.0.1", port);
    socket_listen(listenfd);
    do_event(listenfd);
}
