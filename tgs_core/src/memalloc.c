#include "memalloc.h"

unsigned char memalloc_init(void) {
    memalloc = malloc(sizeof(struct MEMALLOC));
    if (memalloc != NULL) {
        memset(memalloc, 0, sizeof(struct MEMALLOC));
        memalloc->node = NULL;
        memalloc->size = 0;
        memalloc->add = memalloc_node_add;
    }
    return 0;
}

void* memalloc_node_add(void* data, void* (*create)(void* params), void (*destroy)(void* params)) {
    MEMALLOC_NODE* aux = NULL;
    aux = malloc(sizeof(struct MEMALLOC_NODE));
    if (aux != NULL) {
        aux->data = create(data);
        aux->destroy = destroy;
        aux->next = NULL;
        if (memalloc->node == NULL) {
            memalloc->node = aux;
            memalloc->size++;
        } else {
            MEMALLOC_NODE* last = memalloc->node;
            memalloc->node = aux;
            aux->next = last;
            memalloc->size++;
        }
        return aux->data;
    }
    return NULL;
}

void memalloc_quit(void) {
    MEMALLOC_NODE* node = NULL;
    if (memalloc != NULL) {
        node = memalloc->node;
        while(node != NULL) {
            node->destroy(node->data);
            MEMALLOC_NODE* aux = node->next;
            free(node);
            node = aux;
        }
        free(memalloc);
        memalloc = NULL;
    }
}
