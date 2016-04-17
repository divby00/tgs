#include "context.h"
#include "memory.h"

/*
static TGS_CONFIG* context_get_config(TGS_CONTEXT* ctx) {
    return ctx->config;
}
*/


TGS_CONTEXT* context_init(uint32_t subsystems_to_init) {
    TGS_CONTEXT* context = NULL;

    context = memalloc(sizeof(TGS_CONTEXT));
    if (context != NULL) {
        context->config = config_init();
        context->logger = logger_init("tgs.txt", LOG_LEVEL_DEBUG);
    }
    return context;
}


void context_quit(TGS_CONTEXT* context) {
    if (context != NULL) {
        logger_quit(context->logger);
        config_quit(context->config);
        memfree(context);
    }
}

void context_test(void) {
    fprintf(stdout, "Testing...");
}


