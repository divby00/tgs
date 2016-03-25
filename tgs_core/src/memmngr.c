#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "memmngr.h"


static void* mem_mngr_node_add(void* data, void* (*create)(void* params), void (*destroy)(void* params)) {
    MEM_MNGR_NODE* aux = NULL;
    aux = malloc(sizeof(struct MEM_MNGR_NODE));
    if (aux != NULL) {
        aux->data = create(data);
        aux->destroy = destroy;
        aux->next = NULL;
        if (mem_mngr->node == NULL) {
            mem_mngr->node = aux;
            mem_mngr->size++;
        } else {
            MEM_MNGR_NODE* last = mem_mngr->node;
            mem_mngr->node = aux;
            aux->next = last;
            mem_mngr->size++;
        }
        return aux->data;
    }
    return NULL;
}


uint8_t mem_mngr_init(void) {
    mem_mngr = malloc(sizeof(struct MEM_MNGR));
    if (mem_mngr != NULL) {
        memset(mem_mngr, 0, sizeof(struct MEM_MNGR));
        mem_mngr->node = NULL;
        mem_mngr->size = 0;
        mem_mngr->add = mem_mngr_node_add;
    }
    return 0;
}


void mem_mngr_quit(void) {
    MEM_MNGR_NODE* node = NULL;
    if (mem_mngr != NULL) {
        node = mem_mngr->node;
        while(node != NULL) {
            node->destroy(node->data);
            MEM_MNGR_NODE* aux = node->next;
            free(node);
            node = aux;
        }
        free(mem_mngr);
        mem_mngr = NULL;
    }
}
