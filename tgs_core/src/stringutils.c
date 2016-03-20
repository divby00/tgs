#include "stringutils.h"

unsigned char is_empty(char* str) {
    return (str == NULL || !(strcmp(str, "")));
}
