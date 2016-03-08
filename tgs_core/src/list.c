#include "memory.h"
#include "list.h"


TGS_LINKED_LIST* list_init(void* (*object_init_function)(void* params), void (*object_free_function)(TGS_LIST_NODE* node)) {
    TGS_LINKED_LIST* list = NULL;
    list = (struct TGS_LINKED_LIST*)memalloc(sizeof(TGS_LINKED_LIST));
    if (list != NULL) {
        list->node = NULL;
        list->size = 0;
        list->add = list_add;
        list->get = list_get;
        list->remove = list_remove;
        list->object_init = object_init_function;
        list->object_free = object_free_function;
        list->is_empty = list_is_empty;
        //list->size = list_size;
    }
    return list;
}

void list_quit(TGS_LINKED_LIST* list) {
    if (list != NULL) {
        TGS_LIST_NODE* node = list->node;
        while (node != NULL) {
            TGS_LIST_NODE* prev = node;
            node = node->next;
            list->object_free(prev);
            memfree(prev);
        }
        memfree(list);
    }
}

void list_add(TGS_LINKED_LIST* list, void* init_function_params) {
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

TGS_LIST_NODE* list_get(TGS_LINKED_LIST* list, uint index) {
    TGS_LIST_NODE* node = list->node;
    while(node != NULL) {
        if (node->index == index) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

bool list_remove(TGS_LINKED_LIST* list, uint index) {
    TGS_LIST_NODE* node = list->node;
    TGS_LIST_NODE* prev = NULL;

    if (node->index == index) {
        list->node = node->next;
        list->object_free(node);
        memfree(node);
        return 1;
    } else {
        while(node != NULL) {
            prev = node;
            node = node->next;
            if (node->index == index) {
                prev->next = node->next;
                list->object_free(node);
                memfree(node);
                return 1;
            }
        }
    }
    return 0;
}

void list_view(TGS_LINKED_LIST* list) {
    TGS_LIST_NODE* node = list->node;
    while(node != NULL) {
        fprintf(stdout, "Object %d: %s\n", node->index, (char*)node->object);
        node = node->next;
    }
}

bool list_is_empty(TGS_LINKED_LIST *list) {
    return !(list != NULL && list->node != NULL);
}

uint list_size(TGS_LINKED_LIST* list) {
    uint size = 0;
    TGS_LIST_NODE* node = list->node;
    while(node != NULL) {
        node = node->next;
        size++;
    }
    return size;
}
