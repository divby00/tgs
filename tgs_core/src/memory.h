#ifndef __TGS_CORE_H__
#define __TGS_CORE_H__

//#include <xmmintrin.h>
#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define MEMORY_ALIGNMENT 16

void* _memalloc(uint32_t size);
void _memfree(void* data);

#endif
