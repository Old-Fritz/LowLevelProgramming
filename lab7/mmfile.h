#include <sys/mman.h>


void* openMMFile(FILE* file, size_t length, off_t offset);
int closeMMFile(void* addr, size_t length);