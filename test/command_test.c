//
// Created by ruansheng on 16/5/21.
//

#include "../command.h"

int main(int argc, char *argv[]) {
    zokClient zc;
    int a = 3;

    int i;
    for(i = 0; i < 10000; i++) {
        char *b1 = "set";
        char *b2 = "name";
        char *b3 = "ruansheng";
        //sprintf(b3, "%d", i);
        char *b[3];
        b[0] = b1;
        b[1] = b2;
        b[2] = b3;
        zokCommandArgvToString(&zc, a, b);
        printf("%s", zc.obuf);
    }
    return 0;
}