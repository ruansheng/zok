//
// Created by ruansheng on 16/4/23.
//

#include "net.h"

/**
 * loop
 */
void netMain(zokAddr *zokaddr, event *ev) {
    ev->fd = socket_create();
    socket_bind(ev->fd, zokaddr->host, zokaddr->port);
    socket_listen(ev->fd);
    do_event(ev->fd);
}
