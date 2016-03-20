#include "memory.h"
#include "linkedlist.h"


TGS_LINKED_LIST* list_init(void* (*object_init_function)(void* params), void (*object_free_function)(void* params)) {
    TGS_LINKED_LIST* list = NULL;
    list = _memalloc(sizeof(TGS_LINKED_LIST));
    if (list != NULL) {
        list->node = NULL;
        list->size = 0;
        list->add = list_add;
        list->add_at_init = list_add_at_init;
        list->remove = list_remove;
        list->object_init = object_init_function;
        list->object_free = object_free_function;
        list->is_empty = list_is_empty;
    }
    return list;
}

void list_quit(TGS_LINKED_LIST* list) {
    if (list != NULL) {
        TGS_LIST_NODE* node = list->node;
        while (node != NULL) {
            TGS_LIST_NODE* prev = node;
            node = node->next;
            list->object_free(prev->object);
            _memfree(prev);
        }
        _memfree(list);
    }
}

void* list_add_at_init(TGS_LINKED_LIST* list, void* init_function_params) {
    TGS_LIST_NODE* aux = NULL;
    aux = _memalloc(sizeof(TGS_LIST_NODE));
    if (aux != NULL) {
        aux->object = list->object_init(init_function_params);
        aux->next = NULL;
        if (list->node == NULL) {
            list->node = aux;
            list->size++;
        } else {
            TGS_LIST_NODE* last = list->node;
            list->node = aux;
            aux->next = last;
            list->size++;
        }
        return aux->object;
    }
    return NULL;
}

void* list_add(TGS_LINKED_LIST* list, void* init_function_params) {
    TGS_LIST_NODE* aux = NULL;
    TGS_LIST_NODE* node = list->node;
    aux = _memalloc(sizeof(TGS_LIST_NODE));
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

unsigned char list_remove(TGS_LINKED_LIST* list, void *remove_function_params) {
    TGS_LIST_NODE* node = list->node;
    TGS_LIST_NODE* prev = NULL;

    if (node->object == remove_function_params) {
        list->node = node->next;
        list->object_free(node->object);
        _memfree(node);
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
                    _memfree(node);
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

void list_view(TGS_LINKED_LIST* list) {
    TGS_LIST_NODE* node = list->node;
    while(node != NULL) {
        fprintf(stdout, "Object %p: %s\n", node->object, (char*)node->object);
        node = node->next;
    }
}


unsigned char list_is_empty(TGS_LINKED_LIST *list) {
    return !(list != NULL && list->node != NULL);
}
