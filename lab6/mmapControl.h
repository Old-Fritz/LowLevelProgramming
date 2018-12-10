#ifndef MMAP_CONTROL_H
#define MMAP_CONTROL_H

#include <sys/mman.h>

void* getMemory(void* lastEnd, size_t size);

void freeMemory(void* ptr, size_t size);

#endif 