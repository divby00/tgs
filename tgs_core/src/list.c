#include "memory.h"
#include "list.h"


TGS_LLIST* list_init(void* (*object_init_function)(void* params), void (*object_free_function)(TGS_LIST_NODE* node)) {
    TGS_LLIST* list = NULL;
    list = (struct TGS_LLIST*)memalloc(sizeof(TGS_LLIST));
    if (list != NULL) {
        list->node = NULL;
        list->add = list_add;
        list->remove = list_remove;
        list->object_init = object_init_function;
        list->object_free = object_free_function;
    }
    return list;
}

void list_quit(TGS_LLIST* list) {
    if (list != NULL) {
        TGS_LIST_NODE* node = list->node;
        while (node != NULL) {
            TGS_LIST_NODE* prev = node;
            node = node->next;
            list->remove(list, prev);
            memfree(prev);
        }
        memfree(list);
    }
}

void list_add(TGS_LLIST* list, void* init_function_params) {
    TGS_LIST_NODE* aux = NULL;
    TGS_LIST_NODE* node = list->node;
    aux = (struct TGS_LIST_NODE*)memalloc(sizeof(TGS_LIST_NODE));
    if (aux != NULL) {
        aux->object = list->object_init(init_function_params);
        aux->next = NULL;
        aux->index = 1;
        if (node != NULL) {
            while(node->next != NULL) {
                node = node->next;
                aux->index++;
            }
            node->next = aux;
        } else {
            aux->index = 0;
            list->node = aux;
        }
    }
}

void list_remove(TGS_LLIST* list, TGS_LIST_NODE* node) {
    list->object_free(node);
}

void list_view(TGS_LLIST* list) {
    TGS_LIST_NODE* node = list->node;
    while(node != NULL) {
        fprintf(stdout, "Object %d: %s\n", node->index, (char*)node->object);
        node = node->next;
    }
}
