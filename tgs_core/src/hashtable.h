#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__


#include <stdint.h>
#include "linkedlist.h"


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
    TGS_LINKED_LIST* keys;
    TGS_HASHTABLE_ENTRY** table;
    void (*put)(struct TGS_HASHTABLE* hashtable, const char* key, void* params_create, void* (*create)(void* params), void (*destroy)(void* params));
    void* (*get)(struct TGS_HASHTABLE* hashtable, const char* key);
    void (*remove)(struct TGS_HASHTABLE* hashtable, const char* key);
    uint8_t (*contains)(struct TGS_HASHTABLE* hashtable, const char* key);
    uint16_t (*hash)(const char* key, size_t len);
    void* (*string_create)(void* params);
    void (*string_destroy)(void* params);
    void* (*uint32_create)(void* params);
    void (*uint32_destroy)(void* params);
} TGS_HASHTABLE;


TGS_HASHTABLE* hashtable_init();
TGS_HASHTABLE* hashtable_init_small();
void hashtable_quit(TGS_HASHTABLE* hashtable);


#endif
