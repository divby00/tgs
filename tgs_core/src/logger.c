#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include "logger.h"


static void logger_set_level(TGS_LOGGER* logger, enum TGS_LOG_LEVEL level) {
    logger->selected_level = level;
}


static void logger_log(TGS_LOGGER* logger, enum TGS_LOG_LEVEL level, const char* format, ...) {
    va_list args;
    struct timeval tv;
    struct tm *tm;
    char* buffer = NULL;
    char* datestr = NULL;
    const char levelstr[4][6] = {
        "DEBUG", " INFO", " WARN", "ERROR"
    };
    size_t size = 0;

    if (level > logger->selected_level) return;
    size = sizeof(char) * (strlen(format) + 100);

    buffer = malloc(size);
    if (buffer != NULL) {
        memset(buffer, 0, size);
        if (gettimeofday(&tv, NULL) != -1) {
            if ((tm = localtime(&tv.tv_sec)) != NULL) {
                datestr = malloc(size);
                if (datestr != NULL) {
                    memset(datestr, 0, size);
                    strftime(datestr, size, "%d-%b-%Y %H:%M:%S", tm);
                    sprintf(buffer, "[%s - %s] %s\n", datestr, levelstr[logger->selected_level], format);
                    free(datestr);
                    datestr = NULL;
                }
            }
        }
        va_start(args, format);
        vfprintf(logger->file, buffer, args);
        va_end(args);
        free(buffer);
        buffer = NULL;
    }
}


TGS_LOGGER* logger_init(char* filename, enum TGS_LOG_LEVEL level) {
    TGS_LOGGER* logger = NULL;
    logger = malloc(sizeof(TGS_LOGGER));

    if (logger != NULL) {
        memset(logger, 0, sizeof(TGS_LOGGER));

        if (filename != NULL && strcmp(filename, "")) {
            logger->filename = malloc(sizeof(char) * (strlen(filename) + 1));
            if (logger->filename != NULL) {
                memset(logger->filename, 0, sizeof(char) * (strlen(filename) + 1));
                strcpy(logger->filename, filename);
                logger->file = fopen(logger->filename, "wt");
                if (logger->file == NULL) {
                    logger->file = stdout;
                }
            }
        } else {
            logger->file = stdout;
        }

        logger->selected_level = level;
        logger->set_level = logger_set_level;
        logger->log = logger_log;
    }
    return logger;
}


void logger_quit(TGS_LOGGER* logger) {
    if (logger != NULL) {
        if (logger->filename != NULL && strcmp(logger->filename, "")) {
            if (logger->file != NULL) {
                fflush(logger->file);
                fclose(logger->file);
            }
        }
        if (logger->filename != NULL) {
            free(logger->filename);
            logger->filename = NULL;
        }
        free(logger);
        logger = NULL;
    }
}
