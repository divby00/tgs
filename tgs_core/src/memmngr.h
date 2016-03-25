#ifndef __MEM_MNGR_H__
#define __MEM_MNGR_H__


#include <stdint.h>


typedef struct MEM_MNGR_NODE {
    void* data;
    struct MEM_MNGR_NODE* next;
    void* (*create)(void* data);
    void (*destroy)(void* data);
} MEM_MNGR_NODE;


typedef struct MEM_MNGR {
    uint32_t size;
    struct MEM_MNGR_NODE* node;
    void* (*add)(void* data, void* (*create)(void*), void (*destroy)(void*));
} MEM_MNGR;


unsigned char mem_mngr_init(void);
void mem_mngr_quit(void);


MEM_MNGR* mem_mngr;


#endif
