#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>


uint8_t file_exists(const char* filename);
uint64_t file_size(const char* filename);
char* file_read(const char* filename);


#endif
