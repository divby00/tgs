#include <stdio.h>
#include "memory.h"
#include "typealias.h"
#include "logger.h"
#include "list.h"

void* string_init(void* params);
void string_free(TGS_LIST_NODE* node);

int main(int argc, char** argv) {
    TGS_LOGGER* logger = logger_init(NULL, LVL_INFO);
    logger->log(logger, "Testing message", LVL_INFO);

    fprintf(stdout, "\nAdding 3 elements to linked list");
    TGS_LINKED_LIST* list = list_init(&string_init, &string_free);
    list->add(list, "String01");
    list->add(list, "String02");
    list->add(list, "String03");
    fprintf(stdout, "\nList Size: %d", list->size);
    TGS_LIST_NODE* node = list->get(list, 2);
    fprintf(stdout, "\nData in index 2: %s", (char*)node->object);
    fprintf(stdout, "\nRemoving index 1...");
    list->remove(list, 0);
    list->remove(list, 2);
    list->remove(list, 0);
    fprintf(stdout, "\nShowing list...\n");
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

void string_free(TGS_LIST_NODE* node) {
    memfree(node->object);
}

