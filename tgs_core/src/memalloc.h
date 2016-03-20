#ifndef __MEMALLOC_H__
#define __MEMALLOC_H__

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>

typedef struct MEMALLOC_NODE {
    void* data;
    struct MEMALLOC_NODE* next;
    void* (*create)(void* data);
    void (*destroy)(void* data);
} MEMALLOC_NODE;

typedef struct MEMALLOC {
    uint32_t size;
    struct MEMALLOC_NODE* node;
    void* (*add)(void* data, void* (*create)(void*), void (*destroy)(void*));
} MEMALLOC;

unsigned char memalloc_init(void);
void memalloc_quit(void);
void* memalloc_node_add(void* data, void* (*create)(void*), void (*destroy)(void*));

MEMALLOC* memalloc;

#endif // MEMALLOC_H
