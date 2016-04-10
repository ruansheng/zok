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
    printf("%p s1:%d size:%d used:%d sizemask:%d \n", d, s2, d->size, d->used, d->sizemask);

    int s3 = dictAdd(d, "name", "jinghao", 10);
    printf("%p s1:%d size:%d used:%d sizemask:%d \n", d, s3, d->size, d->used, d->sizemask);

    for (int i = 0; i < d->size; i++) {
        if(d->table[i] == NULL) continue;
        dictNode *dn = d->table[i];
        while(dn) {
            printf("key:%s val:%s ttl:%d \n", dn->key, dn->val, dn->ttl);
            dn = dn->next;
        }
    }
    return 0;
}