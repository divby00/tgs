#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>


enum TGS_HASHTABLE_SIZE {
    HT_SIZE_SMALL,
    HT_SIZE_NORMAL
};


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
    void* (*get)(struct TGS_HASHTABLE* hashtable, char* key);
    void (*remove)(struct TGS_HASHTABLE* hashtable, char* key);
    uint8_t (*contains)(struct TGS_HASHTABLE* hashtable, char* key);
    uint16_t (*hash)(char* key, uint32_t len);
    void* (*string_create)(void* params);
    void (*string_destroy)(void* params);
    void* (*uint32_create)(void* params);
    void (*uint32_destroy)(void* params);
} TGS_HASHTABLE;


TGS_HASHTABLE* hashtable_init();
TGS_HASHTABLE* hashtable_init_small();
void hashtable_quit(TGS_HASHTABLE* hashtable);
void hashtable_put(TGS_HASHTABLE* hashtable, char* key, void* params_create, void* (*create)(void *params), void (*destroy)(void *params));
void* hashtable_get(TGS_HASHTABLE* hashtable, char* key);
void hashtable_remove(TGS_HASHTABLE* hashtable, char* key);
uint16_t pearson_hash(char* str, uint32_t len);
uint16_t bkdr_hash(char* str, uint32_t len);
uint8_t hashtable_contains(TGS_HASHTABLE* hashtable, char* key);

void* hashtable_string_create(void* params);
void hashtable_string_destroy(void* params);
void* hashtable_uint32_create(void* params);
void hashtable_uint32_destroy(void* params);


#endif // HASHTABLE_H
