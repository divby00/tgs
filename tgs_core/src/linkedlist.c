#include <stdlib.h>
#include "memory.h"
#include "linkedlist.h"


static void* linkedlist_add_at_init(TGS_LINKED_LIST* list, void* init_function_params) {
    TGS_LINKED_LIST_NODE* aux = NULL;
    aux = memalloc(sizeof(TGS_LINKED_LIST_NODE));
    if (aux != NULL) {
        aux->object = list->object_init(init_function_params);
        aux->next = NULL;
        if (list->node == NULL) {
            list->node = aux;
            list->size++;
        } else {
            TGS_LINKED_LIST_NODE* last = list->node;
            list->node = aux;
            aux->next = last;
            list->size++;
        }
        return aux->object;
    }
    return NULL;
}


static void* linkedlist_add(TGS_LINKED_LIST* list, void* init_function_params) {
    TGS_LINKED_LIST_NODE* aux = NULL;
    TGS_LINKED_LIST_NODE* node = list->node;
    aux = memalloc(sizeof(TGS_LINKED_LIST_NODE));
    if (aux != NULL) {
        aux->object = list->object_init(init_function_params);
        aux->next = NULL;
        if (node != NULL) {
            while(node->next != NULL) {
                node = node->next;
            }
            node->next = aux;
            list->size ++;
        } else {
            list->node = aux;
            list->size ++;
        }
    }
    return aux->object;
}


static uint8_t linkedlist_remove(TGS_LINKED_LIST* list, void* remove_function_params) {
    TGS_LINKED_LIST_NODE* node = list->node;
    TGS_LINKED_LIST_NODE* prev = NULL;

    if (node->object == remove_function_params) {
        list->node = node->next;
        list->object_free(node->object);
        memfree(node);
        list->size--;
        return 1;
    } else {
        while(node != NULL) {
            prev = node;
            if (node->next != NULL) {
                node = node->next;
                if (node->object == remove_function_params) {
                    prev->next = node->next;
                    list->object_free(node->object);
                    memfree(node);
                    list->size--;
                    return 1;
                }
            } else {
                break;
            }
        }
    }
    return 0;
}


/*
static void linkedlist_view(TGS_LINKED_LIST* list) {
    TGS_LIST_NODE* node = list->node;
    while(node != NULL) {
        fprintf(stdout, "Object %p: %s\n", node->object, (char*)node->object);
        node = node->next;
    }
}
*/


static uint8_t linkedlist_is_empty(TGS_LINKED_LIST* list) {
    return !(list != NULL && list->node != NULL);
}


TGS_LINKED_LIST* linkedlist_init(void* (*object_init_function)(void* params), void (*object_free_function)(void* params)) {
    TGS_LINKED_LIST* list = NULL;
    list = memalloc(sizeof(TGS_LINKED_LIST));
    if (list != NULL) {
        list->node = NULL;
        list->size = 0;
        list->add = linkedlist_add;
        list->add_at_init = linkedlist_add_at_init;
        list->remove = linkedlist_remove;
        list->object_init = object_init_function;
        list->object_free = object_free_function;
        list->is_empty = linkedlist_is_empty;
    }
    return list;
}


void linkedlist_quit(TGS_LINKED_LIST* list) {
    if (list != NULL) {
        TGS_LINKED_LIST_NODE* node = list->node;
        while (node != NULL) {
            TGS_LINKED_LIST_NODE* prev = node;
            node = node->next;
            list->object_free(prev->object);
            memfree(prev);
        }
        memfree(list);
    }
}

