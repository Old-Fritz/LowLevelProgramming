#ifndef _MEM_H
#define _MEM_H

#define _USE_MISC

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "mmapControl.h"

#define HEAP_START ((void*)0x04040000)
#define BLOCK_MIN_SIZE 32

#pragma pack(push,1)
struct Mem{
	struct Mem* next;
	size_t capacity;
	bool isFree;
};
#pragma pack(pop)

void* _malloc(size_t query);
void _free(void* ptr);
void* heapInit(size_t initial_size);

#define DEBUG_FIRST_BYTES 64
void memallocDebugStructInfo( FILE* f, struct Mem const* const address );
void memallocDebugHeap( FILE* f,   struct Mem  const* ptr );

#endif