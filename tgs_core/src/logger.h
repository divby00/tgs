#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>

typedef enum log_level {
    LVL_DEBUG,
    LVL_INFO,
    LVL_WARN,
    LVL_ERROR
} log_level;

typedef struct TGS_LOGGER {
    char* filename;
    FILE* file;
    log_level selected_level;
    void (*set_level)(struct TGS_LOGGER* logger, log_level level);
    void (*log)(struct TGS_LOGGER* logger, char* msg, log_level level);
} TGS_LOGGER;

TGS_LOGGER* logger_init(char* filename, log_level level);
void logger_quit(TGS_LOGGER* logger);
void logger_log(TGS_LOGGER* logger, char* msg, log_level level);
void logger_set_level(TGS_LOGGER* logger, log_level level);

#endif // LOGGER_H
