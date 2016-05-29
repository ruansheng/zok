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

int is_hex_digit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

int hex_digit_to_int(char c) {
    switch(c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'a': case 'A': return 10;
        case 'b': case 'B': return 11;
        case 'c': case 'C': return 12;
        case 'd': case 'D': return 13;
        case 'e': case 'E': return 14;
        case 'f': case 'F': return 15;
        default: return 0;
    }
}

zds *zdssplitargs(const char *t, int *argc) {
    const char * p = t;
    char *current= NULL;
    *argc = 0;
    char **argv = NULL;
    while(1) {
        while(*p && isspace(*p)) p++;
        if(*p) {
            int inq = 0;  /* "quotes" */
            int insq = 0; /* 'single quotes' */
            int done = 0;

            if(current == NULL) {
                current = zdsempty();
            }
            while(!done) {
                if(inq) {
                    if (*p == '\\' && *(p+1) == 'x' && is_hex_digit(*(p+2)) && is_hex_digit(*(p+3))) {
                        unsigned char byte;
                        byte = (hex_digit_to_int(*(p+2))*16) + hex_digit_to_int(*(p+3));
                        current = zdscatlen(current, (char*)&byte, 1);
                        p += 3;
                    } else if (*p == '\\' && *(p+1)) {
                        char c;
                        p++;
                        switch(*p) {
                            case 'n':
                                c = '\n';
                                break;
                            case 'r':
                                c = '\r';
                                break;
                            case 't':
                                c = '\t';
                                break;
                            case 'b':
                                c = '\b';
                                break;
                            case 'a':
                                c = '\a';
                                break;
                            default:
                                c = *p;
                                break;
                        }
                        current = zdscatlen(current, &c, 1);
                    } else if (*p == '"') {
                        if (*(p+1) && !isspace(*(p+1))) goto err;
                        done=1;
                    } else if (!*p) {
                        goto err;
                    } else {
                        current = zdscatlen(current, p, 1);
                    }
                } else if (insq) {
                    if(*p == '\\' && *(p+1) == '\'') {
                        p++;
                        current = zdscatlen(current, "'", 1);
                    } else if (*p == '\'') {
                        if (*(p+1) && !isspace(*(p+1))) goto err;
                        done=1;
                    } else if (!*p) {
                        goto err;
                    } else {
                        current = zdscatlen(current, p, 1);
                    }
                } else {
                    switch (*p) {
                        case ' ':
                        case '\n':
                        case '\r':
                        case '\t':
                        case '\0':
                            done = 1;
                            break;
                        case '"':
                            inq = 1;
                            break;
                        case '\'':
                            insq = 1;
                            break;
                        default:
                            current = zdscatlen(current, p, 1);
                            break;
                    }
                }
                if(*p) p++;
            }
            argv = (char **)realloc(argv, ((*argc) + 1) * sizeof(char*));
            argv[*argc] = current;
            (*argc)++;
            current = NULL;
        } else {
            if (argv == NULL) argv = malloc(sizeof(void*));
            return argv;
        }
    }

err:
    while((*argc)--)
        freezds(argv[*argc]);
    free(argv);
    if (current) freezds(current);
    *argc = 0;
    return NULL;
}