//
// Created by ruansheng on 16/5/21.
//

#include "../zds.h"

int main(int argc, char *argv[]) {
    zds z = zdsempty();
    printf("%p \n", z);
    z = zdscat(z, "jinghao");
    printf("%p \n", z);
    z = zdscat(z, "ruansheng");
    printf("%p \n", z);
    z = zdscatlen(z, "zhanshen", 2);
    printf("%p \n", z);
    printf("%s \n", z);
    return 0;
}