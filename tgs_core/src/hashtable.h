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
    char* value;
    struct TGS_HASHTABLE_ENTRY* next;
} TGS_HASHTABLE_ENTRY;

typedef struct TGS_HASHTABLE {
    uint32_t size;
    TGS_HASHTABLE_ENTRY** table;
    void (*put)(struct TGS_HASHTABLE* hashtable, char* key, char* value);
    char* (*get)(struct TGS_HASHTABLE* hashtable, char* key);
} TGS_HASHTABLE;

TGS_HASHTABLE* hashtable_init(uint32_t size);
void hashtable_quit(TGS_HASHTABLE* hashtable);
TGS_HASHTABLE_ENTRY* hashtable_entry_create(char* key, char* value);
void hashtable_put(TGS_HASHTABLE* hashtable, char* key, char* value);
char* hashtable_get(TGS_HASHTABLE* hashtable, char* key);
uint32_t hashtable_keys(TGS_HASHTABLE* hashtable);

#endif // HASHTABLE_H
