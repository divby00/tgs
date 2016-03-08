#ifndef __LIST_H__
#define __LIST_H__

typedef struct TGS_LIST_NODE {
    uint index;
    void* object;
    struct TGS_LIST_NODE* next;
} TGS_LIST_NODE;

typedef struct TGS_LINKED_LIST {
    uint size;
    TGS_LIST_NODE* node;
    void (*add)(struct TGS_LINKED_LIST* list, void* init_function_params);
    TGS_LIST_NODE* (*get)(struct TGS_LINKED_LIST* list, uint index);
    bool (*remove)(struct TGS_LINKED_LIST* list, uint index);
    void* (*object_init)(void* init_function_params);
    void (*object_free)(TGS_LIST_NODE* node);
    bool (*is_empty)(struct TGS_LINKED_LIST* list);
    //uint (*size)(struct TGS_LINKED_LIST* list);
} TGS_LINKED_LIST;

TGS_LINKED_LIST* list_init(void* (*object_init_function)(void* params), void (*object_free_function)(TGS_LIST_NODE* node));
void list_quit(TGS_LINKED_LIST* list);
void list_add(TGS_LINKED_LIST* list, void* init_function_params);
bool list_remove(TGS_LINKED_LIST* list, uint index);
void list_view(TGS_LINKED_LIST* list);
bool list_is_empty(TGS_LINKED_LIST* list);
uint list_size(TGS_LINKED_LIST* list);
TGS_LIST_NODE* list_get(TGS_LINKED_LIST* list, uint index);

#endif
