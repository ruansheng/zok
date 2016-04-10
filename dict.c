//
// Created by ruansheng on 16/4/8.
//

#include "dict.h"

dictOp op = {
    dictGenHashFunction
};

/* create dict */
dict *dictCreate(dictOp *op) {
    dict *d = (dict *)malloc(sizeof(dict));
    d->table = NULL;
    d->op = op;
    d->size = 0;
    d->sizemask = 0;
    d->used = 0;
    return d;
}

/* check dict need expand */
int _ifDictNeedExpand(dict *d) {
    if(d->size == 0) {
        return dictExpand(d, DICT_INIT_SIZE);
    }
    if(d->used == d->size) {
        return dictExpand(d, d->size * 2);
    }
    return DICT_OK;
}

/* find dict key index */
int _findDictKeyIndex(dict *d, void *key) {
    unsigned int h;
    h = dictHashKey(d, key) & d->sizemask;
    dictNode *dn = d->table[h];
    while(dn) {
        if(strcmp(dn->key, key) == 0) {
            return -1;
        }
        dn = dn->next;
    }
    return h;
}

/* find dict node */
dictNode * _findDictNode(dict *d, void *key) {
    if(d->size == 0) return NULL;
    unsigned int h;
    h = dictHashKey(d, key) & d->sizemask;
    dictNode *dn = d->table[h];
    while(dn) {
        if(strcmp(dn->key, key) == 0) {
            return dn;
        }
        dn = dn->next;
    }
    return NULL;
}

/* expand dict size */
int dictExpand(dict *d, unsigned long size) {
    dict *ed;

    if(d->used > size) {
        return DICT_ERR;
    }

    ed = dictCreate(d->op);
    ed->size = size;
    ed->sizemask = size - 1;
    ed->used = d->used;
    ed->table = calloc(size, sizeof(dict *));

    for (int i = 0; i < ed->size && ed->used > 0; i++) {
        if(d->table[i] == NULL) continue;

        dictNode *dn, *nextDn;
        dn = d->table[i];
        while(dn) {
            unsigned int hash;
            nextDn = dn->next;
            hash = dictHashKey(d, dn->key) & ed->sizemask;
            dn->next = d->table[hash];
            ed->table[hash] = dn;
            d->used--;
            dn = nextDn;
        }
    }
    free(d->table);

    *d = *ed;
    return DICT_OK;
}

/* add dict key -> val */
int dictAdd(dict *d, void *key, void *val, int ttl) {
    if(_ifDictNeedExpand(d) == -1) {
        return DICT_ERR;
    }

    unsigned int index;
    /* exists : update */
    if((index = _findDictKeyIndex(d, key)) == -1) {
        dictNode *dn = _findDictNode(d, key);
        dn->val = val;
        dn->ttl = ttl;
        return DICT_OK;
    }

    /* not exists : add */
    dictNode * node = (dictNode *)malloc(sizeof(dictNode));

    node->key = key;
    node->val = val;
    node->ttl = ttl;

    node->next = d->table[index];
    d->table[index] = node;
    d->used++;
    return DICT_OK;
}

/* delete dict key -> val */
int dictDelete(dict *d, void *key) {
    return DICT_OK;
}

/* find dict key -> val */
dictNode *dictFind(dict *d, void *key) {
    return NULL;
}

/* free dict */
int dictRelease(dict *d) {
    return DICT_OK;
}

/* hash function */
unsigned int dictGenHashFunction(const char *buf, int len) {
    unsigned int hash = 5381;

    while (len--)
        hash = ((hash << 5) + hash) + (*buf++); /* hash * 33 + c */
    return hash;
}