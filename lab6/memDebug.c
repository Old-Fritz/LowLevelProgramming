#include "mem.h"

void memallocDebugStructInfo( FILE* f, struct Mem const* const address ) 
{
    size_t i;
    fprintf( f,
            "start: %p\nsize: %lu\nis_free: %d\n",
            (void*)address,
            address->capacity,
            address->isFree);
    for ( i = 0; i <  DEBUG_FIRST_BYTES  &&  i <  address->capacity; ++i )
        fprintf( f, "%hhX", ((char*)address)[ sizeof( struct Mem ) + i ] );
    putc( '\n', f );
}

void memallocDebugHeap( FILE* f, struct Mem const* ptr ) 
{
    for( ; ptr; ptr = ptr->next )
        memallocDebugStructInfo( f, ptr );
}