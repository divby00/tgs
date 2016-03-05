#include "stringutils.h"

bool is_empty(char* str) {
    return (str == NULL || !(strcmp(str, "")));
}
