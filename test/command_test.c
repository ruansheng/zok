//
// Created by ruansheng on 16/5/21.
//

#include "../command.h"
#include<time.h>

int main(int argc, char *argv[]) {
    zokClient zc;
    int a = 3;

    clock_t start = clock();
    int i;
    zc.start = clock();
    for(i = 0; i < 20000; i++) {
        char *b1 = "set";
        char *b2 = "name";
        char *b3 = "ruansheng";
        char *b[3];
        b[0] = b1;
        b[1] = b2;
        b[2] = b3;
        zokCommandArgvToString(&zc, a, b);
        printf("%d\n", i);
        printf("%s", zc.obuf);
    }
    zc.end = clock();
    clock_t end = clock();
    printf("duration=%lf s\n", duration_time(zc.start, zc.end));
    double duration= (double)(end - start);
    printf("%lf\n",duration/CLOCKS_PER_SEC);
    printf("%d\n",start);
    printf("%d\n",end);
    return 0;
}