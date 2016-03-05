#ifndef __TGS_CORE_H__
#define __TGS_CORE_H__

//#include <xmmintrin.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "typealias.h"

#define MEMORY_ALIGNMENT 16

void* memalloc(uint size);
void memfree(void* data);

#endif
