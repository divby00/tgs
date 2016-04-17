#ifndef __LOGGER_H__
#define __LOGGER_H__


#include <stdio.h>


enum TGS_LOG_LEVEL {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
};


typedef struct TGS_LOGGER {
    FILE* file;
    char* filename;
    enum TGS_LOG_LEVEL selected_level;
    void (*set_level)(struct TGS_LOGGER* logger, enum TGS_LOG_LEVEL level);
    void (*log)(struct TGS_LOGGER* logger, enum TGS_LOG_LEVEL level, const char* format, ...);
} TGS_LOGGER;


TGS_LOGGER* logger_init(char* filename, enum TGS_LOG_LEVEL level);
void logger_quit(TGS_LOGGER* logger);



#endif
