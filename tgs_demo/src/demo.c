#include <stdio.h>
#include "memory.h"
#include "typealias.h"
#include "logger.h"
#include "list.h"

void* string_init(void* params);
void string_free(void *params);

int main(int argc, char** argv) {
    TGS_LOGGER* logger = logger_init(NULL, LVL_INFO);
    logger->log(logger, "Testing message", LVL_INFO);
    TGS_LINKED_LIST* list = list_init(&string_init, &string_free);
    void* s1 = list->add(list, "String01");
    list->add_at_init(list, "String02");
    fprintf(stdout, "List Size: %d\n", list->size);
    list->remove(list, s1);
    list_view(list);
    list_quit(list);
    logger_quit(logger);
    return 0;
}

void* string_init(void* params) {
    char* buffer = (char*)memalloc(1024);
    strcpy(buffer, params);
    return buffer;
}

void string_free(void* params) {
    memfree(params);
}

