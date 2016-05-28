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