#ifndef __TGS_CORE_H__
#define __TGS_CORE_H__


//#include <xmmintrin.h>
#include <stdint.h>


#define MEMORY_ALIGNMENT 16


void* memalloc(uint32_t size);
void memfree(void* data);


#endif
