#include "kheap.h"
#include "heap.h"
#include "memory.h"
#include "print.h"
#include "error.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;



void kheap_init(){
	i32 entry_count = HEAP_SIZE_BYTES / HEAP_BLOCK_SIZE;

	kernel_heap_table.entries = (heap_table_entry*)HEAP_TABLE_ADDRESS;
	kernel_heap_table.count = entry_count;

	void* heap_end = (void*)(HEAP_ADDRESS + HEAP_SIZE_BYTES);
	i32 res = heap_create(&kernel_heap, (void*)HEAP_ADDRESS, &kernel_heap_table, heap_end);
	if(res < 0){
		eprint(res);
	}

	print_string("Kernel heap initialized.\n");
}


void* kmalloc(size_t size){
	return heap_malloc(&kernel_heap, size);

}

void* kzalloc(size_t size){
	void* ptr = kmalloc(size);
	if(!ptr) return 0;
	memset(ptr,0x00,size);
	return ptr;
}

void kfree(void* ptr){
	heap_free(&kernel_heap,ptr);
}
