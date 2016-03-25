#ifndef __LIST_H__
#define __LIST_H__


#include <stdint.h>


typedef struct TGS_LINKED_LIST_NODE {
    void* object;
    struct TGS_LINKED_LIST_NODE* next;
} TGS_LINKED_LIST_NODE;


typedef struct TGS_LINKED_LIST {
    uint32_t size;
    TGS_LINKED_LIST_NODE* node;
    void* (*add)(struct TGS_LINKED_LIST* list, void* init_function_params);
    void* (*add_at_init)(struct TGS_LINKED_LIST* list, void* init_function_params);
    uint8_t (*remove)(struct TGS_LINKED_LIST* list, void* remove_function_params);
    void* (*object_init)(void* init_function_params);
    void (*object_free)(void* free_function_params);
    uint8_t (*is_empty)(struct TGS_LINKED_LIST* list);
} TGS_LINKED_LIST;


TGS_LINKED_LIST* linkedlist_init(void* (*object_init_function)(void*), void (*object_free_function)(void *));
void linkedlist_quit(TGS_LINKED_LIST* list);


#endif
