//
// Created by ruansheng on 16/5/28.
//

#include <stdio.h>
#include "zok.h"

#define ZOK_COMMAND_OK 0
#define ZOK_COMMAND_ERR -1

int zokCommandArgvToString(zokClient *zc, int argc, char **argv);

int zokFormatCommandArgvToString(char **target, int argc, char **argv);