#include <stdio.h>
#include "mmfile.h"

void* openMMFile(FILE* file, size_t length, off_t offset)
{
	int fd;
	fd = fileno(file);
	return mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED,fd, offset);
}


int closeMMFile(void* addr, size_t length)
{
	return munmap(addr, length);
}