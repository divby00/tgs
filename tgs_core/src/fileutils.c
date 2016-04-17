#include "fileutils.h"


uint8_t file_exists(const char* filename) {
    FILE* f = NULL;
    uint8_t result = 0;

    if (filename != NULL && strcmp(filename, "")) {
        f = fopen(filename, "rb");
        if (f != NULL) {
            result = 1;
            fclose(f);
        }
    }
    return result;
}


uint64_t file_size(const char* filename) {
    FILE* f = NULL;
    uint64_t size = 0L;

    if (filename != NULL && strcmp(filename, "")) {
        f = fopen(filename, "rb");
        if (f != NULL) {
            fseek(f, 0L, SEEK_END);
            size = ftell(f);
            fseek(f, 0L, SEEK_SET);
            fclose(f);
        }
    }
    return size;
}


char* file_read(const char* filename) {
    FILE* f = NULL;
    char* buffer = NULL;
    uint64_t size = 0L;
    uint64_t result = 0L;

    if (filename != NULL && strcmp(filename, "")) {
        f = fopen(filename, "rb");
        if (f != NULL) {
            fseek(f, 0L, SEEK_END);
            size = ftell(f);
            fseek(f, 0L, SEEK_SET);

            buffer = malloc(size + 1);
            if (buffer != NULL) {
                memset(buffer, 0, size + 1);
                result = fread(buffer, size, 1, f);
                if (result != 1) {
                    free(buffer);
                    buffer = NULL;
                }
            }
            fclose(f);
        }
    }
    return buffer;
}


uint64_t file_save(const char* filename, char* data) {
    FILE* f = NULL;
    uint64_t size = 0L;
    uint64_t result = 0L;

    if (filename != NULL && strcmp(filename, "") && data != NULL) {
        f = fopen(filename, "wb");
        if (f != NULL) {
            size = strlen(data);
            result = fwrite(data, size, 1, f);
            fflush(f);
            fclose(f);
        }
    }
    return result;
}





