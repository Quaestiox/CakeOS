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
};

struct heap{
	struct heap_table* table;
	void* addr;
};


i32 heap_create(struct heap* heap,void* ptr,struct heap_table* table,void* end);
void* heap_malloc(struct heap* heap,size_t size);
void heap_free(struct heap* heap,void* ptr);




#endif
