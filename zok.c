//
// Created by ruansheng on 16/4/8.
//

#include "zok.h"

/* global var */
zokServer server;

zCommand commandTables[] ={
    {"set", setCommand},
    {"get", getCommand},
    {"del", delCommand},
    {"ttl", ttlCommand},
    {"ping", pingCommand},
    {"info", infoCommand}
};



int main() {

    return ZOK_OK;
}