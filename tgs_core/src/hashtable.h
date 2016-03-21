#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

typedef struct TGS_HASHTABLE_ENTRY {
    char* key;
    void* value;
    struct TGS_HASHTABLE_ENTRY* next;
    void (*destroy)(void* params);
} TGS_HASHTABLE_ENTRY;

typedef struct TGS_HASHTABLE {
    uint32_t size;
    TGS_HASHTABLE_ENTRY** table;
    void (*put)(struct TGS_HASHTABLE* hashtable, char* key, void* params_create, void* (*create)(void* params), void (*destroy)(void* params));
    char* (*get)(struct TGS_HASHTABLE* hashtable, char* key);
    uint32_t (*hash)(char* key, uint32_t len);
} TGS_HASHTABLE;

TGS_HASHTABLE* hashtable_init(uint32_t size);
void hashtable_quit(TGS_HASHTABLE* hashtable);
void hashtable_put(TGS_HASHTABLE* hashtable, char* key, void* params_create, void* (*create)(void *params), void (*destroy)(void *params));
char* hashtable_get(TGS_HASHTABLE* hashtable, char* key);
uint32_t pearson_hash(char* str, unsigned int len);
uint32_t hashtable_keys(TGS_HASHTABLE* hashtable);


#endif // HASHTABLE_H
