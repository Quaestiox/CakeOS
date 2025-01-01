#include "heap.h"
#include "error.h"
#include "type.h"
#include <stdbool.h>

struct heap kernel_heap;
struct heap_table kernel_heap_table;

static int heap_validate_table(void* ptr,void* end,struct heap_table* table){
	int res = 0;
	
	size_t table_size = (size_t)(end - ptr);
	size_t block_count = table_size / HEAP_BLOCK_SIZE;
	if(table->count != block_count){
		res = -ERR_HEAP_TABLE;
		goto out;

	}


out:
	return res;


}

static bool heap_validate_alignment(void* ptr){
	return ((u32)ptr % HEAP_BLOCK_SIZE) == 0;
};


int heap_create(heap* heap , void* addr, heap_table* heap_table, void* heap_end){
	int res = 0;

	if(!heap_validate_alignment(addr) || !heap_validate_alignment(heap_end)){
		res = -ERR_HEAP;
		goto out;
	}
	
	memset(heap,0,sizeof(struct heap));
	heap->addr = addr;
	heap->table = heap_table;

	res = heap_validate_table(addr, heap_end ,heap_table);
	if(res < 0){
		goto out;
	}

	size_t table_size = sizeof(heap_table_entry) * heap_table->count;
	memset(table->entries,HEAP_FREE,table_size);

out:
	return res;
}

void heap_init(){
	int entry_count = HEAP_SIZE_BYTES / HEAP_BLOCK_SIZE;

	kernel_heap_table.entries = (heap_table_entry*)HEAP_TABLE_ADDRESS;
	kernel_heap_table.count = entry_count;

	void* heap_end = (void*)HEAP_ADDRESS + HEAP_BLOCK_SIZE;
	heap_create(&kernel_heap, (void*)HEAP_ADDRESS, &kernel_heap_table, heap_end);
	if(res < 0){
		print("\nFailed to create heap\n");
	}


}


static int heap_get_entry_type(heap_table_entry entry){
	return entry & 0x0f;
}


void kmalloc(){

}


