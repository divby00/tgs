#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "logger.h"
#include "memory.h"
#include "sizes.h"
#include "stringutils.h"


TGS_LOGGER* logger_init(char* filename, log_level level) {
    TGS_LOGGER* logger = NULL;
    logger = _memalloc(sizeof(struct TGS_LOGGER));
    if (!is_empty(filename)) {
        logger->filename = _memalloc(MAXSTRING);
        strcpy(logger->filename, filename);
        logger->file = fopen(logger->filename, "wt");
        if (logger->file == NULL) {
            logger->file = stdout;
        }
    } else {
        logger->file = stdout;
    }
    logger->selected_level = level;
    logger->set_level = logger_set_level;
    logger->log = logger_log;
    return logger;
}

void logger_quit(TGS_LOGGER* logger) {
    if (!is_empty(logger->filename)) {
        if (logger->file != NULL) {
            fflush(logger->file);
            fclose(logger->file);
        }
    }
    _memfree(logger->filename);
    _memfree(logger);
}

void logger_set_level(TGS_LOGGER* logger, log_level level) {
    logger->selected_level = level;
}

void logger_log(TGS_LOGGER* logger, char* msg, log_level level) {
    struct timeval tv;
    struct tm *tm;
    char* buffer = NULL;
    char* datestr = NULL;
    const char levelstr[4][6] = {
        "DEBUG", " INFO", " WARN", "ERROR"
    };

    if (level > logger->selected_level) return;

    buffer = _memalloc(MAXSTRING);
    if (buffer != NULL) {
        if (gettimeofday(&tv, NULL) != -1) {
            if ((tm = localtime(&tv.tv_sec)) != NULL) {
                datestr = _memalloc(MAXSTRING);
                strftime(datestr, MAXSTRING, "%d-%b-%Y %H:%M:%S", tm);
                sprintf(buffer, "[%s - %s] %s\n", datestr, levelstr[logger->selected_level], msg);
                _memfree(datestr);
            }
        }
        fprintf(logger->file, "%s", buffer);
        _memfree(buffer);
    }
}
