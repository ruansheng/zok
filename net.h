//
// Created by ruansheng on 16/4/23.
//
#include <sys/select.h>

/* event */
typedef struct event {
    int port;
    int buffer_size;
    int sfd;
    fd_set read_fds;
    fd_set temp_fds;
} event;

/**
 * init_socket
 */
void init_socket(event *ev);

/**
 * create_bind_socket
 */
void create_bind_socket(event *ev);

/**
 * listen_socket
 */
void listen_socket(event *ev);

/**
 * loop
 */
void loop(event *ev);