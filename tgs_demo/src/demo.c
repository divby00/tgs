#include <stdio.h>
#include "memory.h"
#include "memalloc.h"
#include "hashtable.h"
#include "display.h"
#include <sys/time.h>

int main(int argc, char** argv) {
    TGS_HASHTABLE* table = hashtable_init(256);
    struct timeval stop, start;
    double secs;

    gettimeofday(&start, NULL);
    table->put(table, "18", "eighteen");
    table->put(table, "19", "nineteen");
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    fprintf(stdout, "Took %f\n", secs);

    gettimeofday(&start, NULL);
    char* data00 = table->get(table, "19");
    char* data01 = table->get(table, "18");
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    fprintf(stdout, "Took %f\n", secs);

    hashtable_quit(table);

    return 0;
}
