#ifndef __LIST_H__
#define __LIST_H__

typedef struct TGS_LIST_NODE {
    int index;
    void* object;
    struct TGS_LIST_NODE* next;
} TGS_LIST_NODE;

typedef struct TGS_LLIST {
    TGS_LIST_NODE* node;
    void (*add)(struct TGS_LLIST* list, void* init_function_params);
    void (*remove)(struct TGS_LLIST* list, TGS_LIST_NODE* node);
    void* (*object_init)(void* params);
    void (*object_free)(TGS_LIST_NODE* node);
} TGS_LLIST;

TGS_LLIST* list_init(void* (*object_init_function)(void* params), void (*object_free_function)(TGS_LIST_NODE* node));
void list_quit(TGS_LLIST* list);
void list_add(TGS_LLIST* list, void* init_function_params);
void list_remove(TGS_LLIST* list, TGS_LIST_NODE* node);
void list_view(TGS_LLIST* list);

#endif
