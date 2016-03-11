#ifndef __LIST_H__
#define __LIST_H__

typedef struct TGS_LIST_NODE {
    void* object;
    struct TGS_LIST_NODE* next;
} TGS_LIST_NODE;

typedef struct TGS_LINKED_LIST {
    uint size;
    TGS_LIST_NODE* node;
    void* (*add)(struct TGS_LINKED_LIST* list, void* init_function_params);
    void* (*add_at_init)(struct TGS_LINKED_LIST* list, void* init_function_params);
    bool (*remove)(struct TGS_LINKED_LIST* list, void* remove_function_params);
    void* (*object_init)(void* init_function_params);
    void (*object_free)(void* free_function_params);
    bool (*is_empty)(struct TGS_LINKED_LIST* list);
} TGS_LINKED_LIST;

TGS_LINKED_LIST* list_init(void* (*object_init_function)(void*), void (*object_free_function)(void *));
void list_quit(TGS_LINKED_LIST* list);
void* list_add(TGS_LINKED_LIST* list, void* init_function_params);
void* list_add_at_init(TGS_LINKED_LIST* list, void* init_function_params);
bool list_remove(TGS_LINKED_LIST* list, void* remove_function_params);
void list_view(TGS_LINKED_LIST* list);
bool list_is_empty(TGS_LINKED_LIST* list);

#endif
