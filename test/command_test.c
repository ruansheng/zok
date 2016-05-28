//
// Created by ruansheng on 16/5/21.
//

#include "../command.h"

int main(int argc, char *argv[]) {
    zokClient zc;
    int a = 3;
    char *b[] = {
      "set",
      "name"
    };
    int i;
    for(i = 0; i < 10000; i++) {
        sprintf(b[2], i);
        zokCommandArgvToString(&zc, a, b);
        printf("%s", zc.obuf);
    }
    return 0;
}