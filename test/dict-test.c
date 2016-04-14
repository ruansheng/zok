//
// Created by ruansheng on 16/4/10.
//

#include "../dict.h"

int main() {
    dict * d;
    dictOp op = {
        dictGenHashFunction
    };
    d = dictCreate(&op);
    int s1 = dictAdd(d, "name", "ruansheng", 10);
    printf("%p s1:%d size:%d used:%d sizemask:%d \n", d, s1, d->size, d->used, d->sizemask);

    int s2 = dictAdd(d, "age", "jinghao", 10);
    printf("%p s2:%d size:%d used:%d sizemask:%d \n", d, s2, d->size, d->used, d->sizemask);

    int s3 = dictAdd(d, "name", "jinghao", 10);
    printf("%p s3:%d size:%d used:%d sizemask:%d \n", d, s3, d->size, d->used, d->sizemask);

    printf("-------------------------\n");

    for (int i = 0; i < d->size; i++) {
        if(d->table[i] == NULL) continue;
        dictNode *dn = d->table[i];
        while(dn) {
            printf("key:%s i:%d val:%s ttl:%d \n", dn->key, i, dn->val, dn->ttl);
            dn = dn->next;
        }
    }

    printf("-------------------------\n");

    dictNode * fdn = dictFind(d, "name");
    if(fdn) {
        printf("key:%s val:%s ttl:%d \n", fdn->key, fdn->val, fdn->ttl);
    } else {
        printf("jinghao key is empty\n");
    }

    printf("-------------------------\n");

    int dstatus = dictDelete(d, "age");
    if(dstatus == DICT_OK) {
        printf("delete key age success\n");
    } else {
        printf("delete key age fail\n");
    }

    printf("-------------------------\n");

    for (int i = 0; i < d->size; i++) {
        if(d->table[i] == NULL) continue;
        dictNode *dn = d->table[i];
        while(dn) {
            printf("key:%s i:%d val:%s ttl:%d \n", dn->key, i, dn->val, dn->ttl);
            dn = dn->next;
        }
    }

    return 0;
}