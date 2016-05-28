//
// Created by ruansheng on 16/5/28.
//

#include "util.h"

int intlen(int i) {
    int len = 0;
    if (i < 0) {
        len++;
        i = -i;
    }
    do {
        len++;
        i /= 10;
    } while(i);
    return len;
}

int bulklen(int len) {
    return 1 + intlen(len) + 2 + len + 2;
}

clock_t start_time() {
    return clock();
}

clock_t end_time() {
    return clock();
}

double duration_time(clock_t start, clock_t end) {
    double duration = (double)(end - start);
    return duration / CLOCKS_PER_SEC;
}