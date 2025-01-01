#ifndef HEAP_H
#define HEAP_H

#include "type.h"
#include "config.h"


#define HEAP_TAKEN 1
#define HEAP_FREE 0

#define HEAP_HAS_NEXT 0b10000000
#define HEAP_IS_FIRST 0b01000000

typedef u8 heap_table_entry;

struct heap_table{
	heap_table_entry* entries;
	size_t count;
}

struct heap{
	struct heap_table* table;
	void* addr;
}





void heap_init();

#endif
