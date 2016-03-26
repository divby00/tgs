#include <string.h>
#include "stringutils.h"

uint8_t str_is_empty(const char* str) {
    return (str == NULL || !(strcmp(str, "")));
}
