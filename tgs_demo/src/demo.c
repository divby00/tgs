#include <stdio.h>
#include "luautils.h"
#include "memory.h"
#include "memmngr.h"
#include "hashtable.h"
#include "linkedlist.h"
#include "fileutils.h"
#include "display.h"
#include "logger.h"
#include "config.h"
#include <sys/time.h>


int main(void) {
    int status = 0;
    lua_State* ls = NULL;
    ls=luaL_newstate();
    luaL_openlibs(ls);
    status = luaL_dofile(ls, "demo.bin");
    if (status) {
        fprintf(stdout, "\n--------------------- ");
        fprintf(stdout, "\nError code %d", status);
        fprintf(stdout, "\nError message: %s", lua_tostring(ls ,-1));
        fprintf(stdout, "\n---------------------\n");
    }
    lua_close(ls);
    return 0;
}



/*
int main(int argc, char** argv) {
    TGS_HASHTABLE* table = hashtable_init_small();
    struct timeval stop, start;
    double secs;
    int a = 45;
    TGS_CONFIG* config = NULL;
    TGS_LOGGER* logger = NULL;

    config = config_init();
    config->add_field(config, "paths", "data", "./data/", CFG_TYPE_STRING);
    config->add_field(config, "paths", "lang", "./data/locale/", CFG_TYPE_STRING);
    config->add_field(config, "graphics", "fullscreen", "false", CFG_TYPE_BOOLEAN);
    config->add_field(config, "graphics", "width", "640", CFG_TYPE_NUMBER);
    config->add_field(config, "graphics", "height", "480", CFG_TYPE_NUMBER);
    config->add_field(config, "control", "keyboard", "true", CFG_TYPE_BOOLEAN);
    config->add_field(config, "control", "joystick", "false", CFG_TYPE_BOOLEAN);
    config->read(config, "example.json");

    fprintf(stdout, "\nControl - Keyboard: %d", config->get_boolean(config, "control", "keyboard"));
    fprintf(stdout, "\nPaths - Data: %s", config->get_string(config, "paths", "data"));
    fprintf(stdout, "\nGraphics - Width: %lf", config->get_number(config, "graphics", "width"));

    config->set_boolean(config, "control", "keyboard", 0);
    config->set_number(config, "graphics", "width", 101);
    config->set_string(config, "paths", "data", "Testing string");

    fprintf(stdout, "\nControl - Keyboard: %d", config->get_boolean(config, "control", "keyboard"));
    fprintf(stdout, "\nGraphics - Width: %lf", config->get_number(config, "graphics", "width"));
    fprintf(stdout, "\nPaths - Data: %s", config->get_string(config, "paths", "data"));

    config->save(config, "example.json");

    logger = logger_init(NULL, LOG_LEVEL_WARN);
    gettimeofday(&start, NULL);
    table->put(table, "17", "seventeen", table->string_create, table->string_destroy);
    table->put(table, "18", "eighteen", table->string_create, table->string_destroy);
    table->put(table, "19", "nineteen", table->string_create, table->string_destroy);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    logger->log(logger, LOG_LEVEL_DEBUG, "Logger Test: %d", a);

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
    logger_quit(logger);
    config_quit(config);

    char* buf = file_read("tgs_demo");
    memfree(buf);

    return 0;
}

*/
