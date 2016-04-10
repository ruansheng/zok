//
// Created by ruansheng on 16/4/8.
//

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define DICT_OK 0
#define DICT_ERR -1

#define DICT_INIT_SIZE 4

typedef struct dictNode{
    void *key;
    void *val;
    int ttl;
    struct dictNode *next;
}dictNode;

typedef struct {
    unsigned int (*hashFunction)(const char *, int);
} dictOp;

typedef struct {
  dictNode **table;
  dictOp *op;
  int size;
  int sizemask;
  int used;
} dict;

#define dictHashKey(dict, key) (dict->op->hashFunction(key, strlen(key)))

/* API */
dict *dictCreate(dictOp *op);
int _ifDictNeedExpand(dict *d);
int _findDictKeyIndex(dict *d, void *key);
dictNode * _findDictNode(dict *d, void *key);
int dictExpand(dict *d, unsigned long size);
int dictAdd(dict *d, void *key, void *val, int ttl);
int dictDelete(dict *d, void *key);
dictNode *dictFind(dict *d, void *key);
int dictRelease(dict *d);

/* hash function */
unsigned int dictGenHashFunction(const char *buf, int len);