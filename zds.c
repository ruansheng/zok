//
// Created by ruansheng on 16/4/23.
//

#include "zds.h"
#include<string.h>
#include<stdlib.h>

zds newzds(const char *init) {
    int len = (init == NULL) ? 0 : strlen(init);
    return newlenzds(init, len);
}

zds newlenzds(const char *init, int len) {
    zdshdr *zh;
    if(init) {
        zh = (zdshdr *) malloc(sizeof(zdshdr) + len + 1);
    } else {
        zh = (zdshdr *) calloc(0, sizeof(zdshdr) + len + 1);
    }
    if(zh == NULL) return NULL;
    zh->len = len;
    zh->free = 0;
    if(init && len) {
        memcpy(zh->buf, init, len);
    }
    zh->buf[len] = '\0';
    return (zds)zh->buf;
}

int zdslen(const zds z) {
    zdshdr *zh;
    zh = (zdshdr *)(z - sizeof(zdshdr));
    return zh->len;
}

int zdsfreelen(const zds z) {
    zdshdr *zh;
    zh = (zdshdr *)(z - sizeof(zdshdr));
    return zh->free;
}

zds zdsempty() {
    return newlenzds("", 0);
}

void zdsclear(const zds z) {
    zdshdr *zh;
    zh = (zdshdr *)(z - sizeof(zdshdr));
    zh->free += zh->len;
    zh->len = 0;
    zh->buf[0] = '\0';
}

zds zdscat(zds z, const char *t) {
    return zdscatlen(z, t, strlen(t));
}

zds zdscatlen(zds z, const char *t, int len) {
    zdshdr *zh;
    int zlen = zdslen(z);
    z = zdsMakeRoom(z, len);
    if(z == NULL) return NULL;
    zh = (zdshdr *)(z - sizeof(zdshdr));
    memcpy(zh->buf + zlen, t, len);
    zh->len = zlen + len;
    zh->free = zh->free - len;
    zh->buf[zlen + len] = '\0';
    return z;
}

void freezds(zds z) {
    if(z == NULL) return;
    free(z - sizeof(zdshdr));
}

zds zdsMakeRoom(zds z, int addlen) {
    zdshdr *zh, *newzh;
    int len, freelen, newlen;
    len = zdslen(z);
    freelen = zdsfreelen(z);
    if(freelen >= addlen) return z;
    newlen = len + addlen;
    if(newlen < ZOK_ZDS_PREALLOC_SIZE) {
        newlen = newlen * 2;
    } else {
        newlen += ZOK_ZDS_PREALLOC_SIZE;
    }
    zh = (zdshdr *)(z - sizeof(zdshdr));
    newzh = (zdshdr *)realloc(zh, sizeof(zdshdr) + newlen + 1);
    if(newzh == NULL) return NULL;
    newzh->free = newlen - len;
    return newzh->buf;
}