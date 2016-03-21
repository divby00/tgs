#include <stdio.h>
#include "memory.h"
#include "memalloc.h"
#include "hashtable.h"
#include "linkedlist.h"
#include "display.h"
#include <sys/time.h>

void* hashtable_create_entry(void* params);
void hashtable_destroy_entry(void* params);

int main(int argc, char** argv) {
    TGS_HASHTABLE* table = hashtable_init(256);
    struct timeval stop, start;
    double secs;

    gettimeofday(&start, NULL);
    table->put(table, "18", "eighteen", hashtable_create_entry, hashtable_destroy_entry);
    table->put(table, "19", "nineteen", hashtable_create_entry, hashtable_destroy_entry);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    fprintf(stdout, "Took %f\n", secs);

    gettimeofday(&start, NULL);
    char* data00 = table->get(table, "19");
    char* data01 = table->get(table, "18");
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    fprintf(stdout, "Took %f\n", secs);

    fprintf(stdout, "\n%s", data00);
    fprintf(stdout, "\n%s", data01);

    hashtable_quit(table);

    return 0;
}

void* hashtable_create_entry(void* params) {
    char* buffer = NULL;
    buffer = _memalloc(sizeof(char)*(strlen(params)+1));
    strcpy(buffer, params);
    return buffer;
}

void hashtable_destroy_entry(void* params) {
    _memfree(params);
}
