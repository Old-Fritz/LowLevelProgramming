#include "mmapControl.h"

void* getMemory(void* lastEnd, size_t size)
{
	void* ptr;
	ptr=mmap(lastEnd, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED | MAP_ANONYMOUS,0, 0);
	if(ptr!= MAP_FAILED)
		return ptr;
	ptr =  mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,0, 0);
	if(ptr== MAP_FAILED)
		return 0;
	return ptr;
}

void freeMemory(void* ptr, size_t size)
{
	munmap(ptr, size);
}