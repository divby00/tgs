#include <stdio.h>
#include "memory.h"
#include "memmngr.h"
#include "hashtable.h"
#include "linkedlist.h"
#include "display.h"
#include "logger.h"
#include <sys/time.h>


int main(int argc, char** argv) {
    TGS_HASHTABLE* table = hashtable_init_small();
    struct timeval stop, start;
    double secs;
    int a = 45;

    logger_init(NULL, LOG_LEVEL_WARN);
    gettimeofday(&start, NULL);
    table->put(table, "17", "seventeen", table->string_create, table->string_destroy);
    table->put(table, "18", "eighteen", table->string_create, table->string_destroy);
    table->put(table, "19", "nineteen", table->string_create, table->string_destroy);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    logger->log(LOG_LEVEL_DEBUG, "Logger Test: %d", a);

    gettimeofday(&start, NULL);
    char* data00 = table->get(table, "19");
    char* data01 = table->get(table, "18");
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    fprintf(stdout, "Took %f\n", secs);

    fprintf(stdout, "\n%s", data00);
    fprintf(stdout, "\n%s", data01);

    table->remove(table, "19");
    fprintf(stdout, "\nExit: %d", table->contains(table, "19"));

    fprintf(stdout, "\nExit: %d", table->contains(table, "17"));

    table->remove(table, "18");
    fprintf(stdout, "\nExit: %d", table->contains(table, "18"));

    hashtable_quit(table);
    logger_quit();

    return 0;
}
