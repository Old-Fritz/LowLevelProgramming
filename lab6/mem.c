#include "mem.h"

static struct Mem* memStart = 0;

static void splitBlock(struct Mem* mem, size_t query)
{
	struct Mem* next;
	next = (struct Mem*)((uint8_t*)mem+sizeof(struct Mem)+query);
	next->isFree = true;
	next->capacity = mem->capacity - query - sizeof(struct Mem);
	next->next = mem->next;

	mem->next = next;
	mem->capacity=query;
}

void* _malloc(size_t query)
{
	struct Mem* mem = memStart;
	struct Mem* next;
	void* ptr;
	void* startAdress;

	if(query<BLOCK_MIN_SIZE)
		query = BLOCK_MIN_SIZE;

	while(mem)
	{
		if(mem->isFree && mem->capacity>=query)
		{
			ptr=(uint8_t*)mem+sizeof(struct Mem);
			mem->isFree = false;
			if(mem->capacity+BLOCK_MIN_SIZE+sizeof(struct Mem)>=query)
				splitBlock(mem, query);
			return ptr;
		}
		if(mem->next)
			mem = mem->next;
		else
			break;
	}

	//if nothing has returned
	if(mem)
		startAdress = (uint8_t*)mem+sizeof(struct Mem);
	else
		startAdress = HEAP_START;
	ptr = getMemory(startAdress, query+sizeof(struct Mem));
	if(!ptr)
		return ptr;

	next = (struct Mem*)ptr;
	next->isFree = false;
	next->next = NULL;
	next->capacity = query;
	if(mem)
		mem->next = next;

	return (uint8_t*)ptr+sizeof(struct Mem);
}
void _free(void* ptr)
{
	struct Mem* mem = (struct Mem*)((uint8_t*)ptr-sizeof(struct Mem));
	mem->isFree = true;
	while(mem->next && mem->next->isFree==true && (uint8_t*)mem->next==(uint8_t*)mem+sizeof(struct Mem)+mem->capacity)
	{
		mem->capacity += mem->next->capacity + sizeof(struct Mem);
		mem->next = mem->next->next;
	}
}

void* heapInit(size_t initialSize)
{
	void* ptr;

	ptr = _malloc(initialSize);
	if(!ptr)
		return ptr;

	memStart = (struct Mem*)((uint8_t*)ptr-sizeof(struct Mem));
	memStart->isFree = true;

	return ptr;
}