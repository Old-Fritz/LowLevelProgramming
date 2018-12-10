#ifndef MMFILE_H
#define MMFILE_H

#include <sys/mman.h>

void* openMMFile(FILE* file, size_t length, off_t offset);
int closeMMFile(void* addr, size_t length);

#endif