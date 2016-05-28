//
// Created by ruansheng on 16/5/21.
//

#include "../zok.h"
#include "../command.h"

int main(int argc, char *argv[]) {
    zokClient zc;
    zokCommandArgvToString(&zc, argc, argv);
    printf("%s", zc.obuf);
    return 0;
}