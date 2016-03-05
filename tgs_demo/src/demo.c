#include <stdio.h>
#include "memory.h"
#include "typealias.h"
#include "logger.h"

int main(int argc, char** argv) {
    TGS_LOGGER* logger = logger_init(NULL, LVL_INFO);
    logger->log(logger, "Testing message", LVL_INFO);
    logger_quit(logger);
    return 0;
}
