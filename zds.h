//
// Created by ruansheng on 16/4/23.
//
#include<stdio.h>

#define ZOK_ZDS_PREALLOC_SIZE (1024 * 1024)

typedef char *zds;

/* zdshdr */
typedef struct {
    int len;
    int free;
    char buf[];
} zdshdr;

zds newzds(const char *init);
zds newlenzds(const char *init, int len);
int zdslen(const zds z);
int zdsfreelen(const zds z);
zds zdsempty();
void zdsclear(const zds z);
zds zdscat(zds z, const char *t);
zds zdscatlen(zds z, const char *t, int len);
void freezds(zds z);

zds zdsMakeRoom(zds z, int addlen);