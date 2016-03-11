#include "memory.h"

void* memalloc(uint size) {
    void* aux = NULL;
    //aux = _mm_malloc(size, MEMORY_ALIGNMENT);
    aux = malloc(size);
    if (aux != NULL) {
        memset(aux, 0, size);
    }
    return aux;
}

void memfree(void* data) {
    if (data != NULL) {
        free(data);
        data = NULL;
    }
}
