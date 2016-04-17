#ifndef __CONTEXT_H__
#define __CONTEXT_H__


#include <stdlib.h>
#include <stdint.h>
#include "config.h"
#include "logger.h"


enum TGS_SUBSYSTEM {
    VIDEO = 0x01,
    CONFIG = 0x02,
    LOGGING = 0x04
};


typedef struct TGS_CONTEXT {
    TGS_CONFIG* config;
    TGS_LOGGER* logger;
    TGS_CONFIG* (*get_config)(struct TGS_CONTEXT* ctx);
    TGS_LOGGER* (*get_logger)(struct TGS_CONTEXT* ctx);
} TGS_CONTEXT;


TGS_CONTEXT* context_init(uint32_t subsystems_to_init);
void context_quit(TGS_CONTEXT* tgs_context);


#endif
