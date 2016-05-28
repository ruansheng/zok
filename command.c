//
// Created by ruansheng on 16/5/28.
//

#include "command.h"

int zokCommandArgvToString(zokClient *zc, int argc, char **argv) {
    char *cmd;
    int len;
    len = zokFormatCommandArgvToString(&cmd, argc, argv);
    if(len == -1) {
        printf("Out of memory");
        return ZOK_COMMAND_ERR;
    }

    zds z = newlenzds(cmd, len);
    if(z == NULL) {
        free(cmd);
        printf("newlenzds alloc memory");
        return ZOK_COMMAND_ERR;
    }
    zc->obuf = z;
    free(cmd);
    return ZOK_COMMAND_OK;
}

int zokFormatCommandArgvToString(char **target, int argc, char **argv) {
    int i, total;

    total = 1 + intlen(argc) + 2; /*  add first line "*3\r\n" string length  */
    for(i = 0; i < argc; i++) {
        int len = strlen(argv[i]);
        total += bulklen(len); /*  add an cmd item two line "$3\r\n" and "set\r\n" string length  */
    }

    char *cmd = (char *)malloc(total + 1); /*  add total cmd + '\0' string length  */
    if(cmd == NULL) return -1;

    int pos = sprintf(cmd, "*%d\r\n", argc);
    for(i = 0; i < argc; i++) {
        len = strlen(argv[i]);
        pos += sprintf(cmd + pos, "$%zu\r\n", len);
        memcpy(cmd + pos, argv[i], len);
        pos += len;
        cmd[pos++] = '\r';
        cmd[pos++] = '\n';
    }
    cmd[pos] = '\0';
    *target = cmd;
    return total;
}