//
// Created by ruansheng on 16/4/23.
//

#include "net.h"

/**
 * loop
 */
void netMain(zokServer *server) {
    int listenfd = socket_create();
    int port = atoi(argv[1]);
    socket_bind(listenfd, server->host, server->port);
    socket_listen(listenfd);
    do_event(listenfd);
}
