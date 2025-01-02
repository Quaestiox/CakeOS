#include "heap.h"
#include "error.h"
#include "type.h"
#include "memory.h"
#include <stdbool.h>

static i32 heap_validate_table(void* ptr,void* end,struct heap_table* table){
	i32 res = 0;
	
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


i32 heap_create(struct heap* heap , void* addr,struct heap_table* heap_table, void* heap_end){
	i32 res = 0;

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
	memset(heap_table->entries,HEAP_FREE,table_size);

out:
	return res;
}

static i32 heap_get_entry_type(heap_table_entry entry){
	return entry & 0x0f;
}

i32 heap_get_start_block(struct heap* heap,u32 total_blocks){
	struct heap_table* table = heap->table;
	i32 block_count = 0;
	i32 block_start = -1;

	for(size_t i = 0; i < table->count; i++){
		if(heap_get_entry_type(table->entries[i]) != HEAP_FREE){
			block_count = 0;
			block_start = -1;
			continue;
		}

		if(block_start == -1){
			block_start = i;

		}
		block_count++;
		if(block_count == total_blocks){
			break;
		}
	}

	if(block_start == -1){
		return -ERR_NO_MEMORY;
	}

	return block_start;
}


void* heap_block_to_address(struct heap* heap, i32 block){
	return heap->addr + (block * HEAP_BLOCK_SIZE);
}

void heap_mark_blocks_taken(struct heap* heap,i32 start_block,i32 total_blocks){
	i32 end_block = (start_block + total_blocks) - 1;
	heap_table_entry entry = HEAP_TAKEN | HEAP_IS_FIRST;

	if(total_blocks > 1){
		entry |= HEAP_HAS_NEXT;
	}
	
	for(i32 i=start_block; i <= end_block;i++){
		heap->table->entries[i] = entry;
		entry = HEAP_TAKEN;
		if(i != end_block - 1){
			entry |= HEAP_HAS_NEXT;
		}
	}
}

void* heap_malloc_blocks(struct heap* heap,u32 total_blocks){
	void* address = 0;

	i32 start_block = heap_get_start_block(heap,total_blocks);

	if(start_block < 0){
		goto out;
	}

	address = heap_block_to_address(heap,start_block);

	heap_mark_blocks_taken(heap,start_block,total_blocks);

out:
	return address;
}


static u32 heap_align_to_upper(u32 val){
	if((val % HEAP_BLOCK_SIZE) == 0){
		return val;
	}

	val = (val - (val % HEAP_BLOCK_SIZE)) + HEAP_BLOCK_SIZE;
	return val;
}


void* heap_malloc(struct heap* heap, size_t size){
	size_t aligned_size = heap_align_to_upper(size);
	u32 total_blocks = aligned_size / HEAP_BLOCK_SIZE;

	return heap_malloc_blocks(heap,total_blocks);
}

void heap_mark_blocks_free(struct heap* heap, i32 starting_block){
	struct heap_table* table = heap->table;
	for(i32 i = starting_block;i < (i32)table->count;i++){
		heap_table_entry entry = table->entries[i];
		table->entries[i] = HEAP_FREE;
		if (!(entry & HEAP_HAS_NEXT)){
			break;
		}
	}
}


i32 heap_address_to_block(struct heap* heap,void* address){
	return((i32)(address - heap->addr)) / HEAP_BLOCK_SIZE;
}

void heap_free(struct heap* heap,void* ptr){

	heap_mark_blocks_free(heap, heap_address_to_block(heap,ptr));
}







