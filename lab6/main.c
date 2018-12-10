#include "mem.h"



int main()
{
	//int32_t *testVars1, *testVars2, *testVars3, i;
	FILE* file;
	void* start = heapInit(10000000);


	_malloc(100);
	_malloc(200);
	_malloc(3000);
	_malloc(4000);
	_malloc(5000);
	_malloc(600);
	_malloc(1024);
	_malloc(1025);
	_malloc(4097);

	
	file = fopen("debug", "w");

	memallocDebugHeap(file, (struct Mem*)((uint8_t*)start-sizeof(struct Mem)));
}