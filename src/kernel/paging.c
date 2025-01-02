#include "paging.h"
#include "kheap.h"
#include "error.h"
#include <stdbool.h>

extern void paging_load_directory(paging_directory directory);
static paging_directory current_directory = 0;

struct paging_4gb* paging_new_4gb(u8 flags){
	paging_directory directory = kzalloc(sizeof(paging_directory_entry) * PAGING_DIRECTORY_ENTRY_COUNT);
	int offset = 0;

	for(int i = 0;i < PAGING_DIRECTORY_ENTRY_COUNT; i++){
		paging_table table = kzalloc(sizeof(paging_table_entry) * PAGING_TABLE_ENTRY_COUNT);
		for(int j = 0; j < PAGING_TABLE_ENTRY_COUNT; j++){
			table[j] = (offset + (j * PAGING_PAGE_SIZE)) | flags;
		}	
		offset += (PAGING_TABLE_ENTRY_COUNT * PAGING_PAGE_SIZE);
		directory[i] = (paging_directory_entry)table | flags | PAGING_IS_WRITEABLE;
	}

	struct paging_4gb* new_paging = kzalloc(sizeof(struct paging_4gb));
	new_paging->directory = directory;
	return new_paging;
}

void paging_switch(struct paging_4gb* paging){
	paging_load_directory(paging->directory);
	current_directory = paging->directory;
}


void paging_free(struct paging_4gb* paging){
	for(int i=0; i < PAGING_DIRECTORY_ENTRY_COUNT; i++){
		paging_directory_entry entry = paging->directory[i];
		paging_table table = (paging_table)(entry & 0xfffff000);
		kfree(table);
	}

	kfree(paging->directory);
	kfree(paging);
}


paging_directory paging_get_directory(struct paging_4gb* paging){
	return paging->directory;
}


bool paging_is_aligned(void* addr){
	return ((u32)addr % PAGING_PAGE_SIZE) == 0;
}

int paging_get_indexes(void* virt_addr, u32* directory_index, u32* table_index){
	int res = 0;
	if(!paging_is_aligned(virt_addr)){
		res = -ERR_PAGING;
		goto out;
	}

	*directory_index = ((u32)virt_addr /(PAGING_TABLE_ENTRY_COUNT * PAGING_PAGE_SIZE));
	*table_index = ((u32)virt_addr % (PAGING_TABLE_ENTRY_COUNT * PAGING_PAGE_SIZE) / PAGING_PAGE_SIZE);

out: 
	return res;
}



void* paging_align_address(void* ptr){
	if((u32) ptr % PAGING_PAGE_SIZE){
		return (void*)((u32)ptr + PAGING_PAGE_SIZE - ((u32) ptr % PAGING_PAGE_SIZE));
	}
	return ptr;
}

void* paging_align_to_lower_page(void* addr){
	u32 new_addr = (u32) addr;
	new_addr -= (new_addr % PAGING_PAGE_SIZE);
	return (void*) new_addr;
}

int paging_map(struct paging_4gb* paging, void* virt, void* phys, int flags){
	if(((u32)virt % PAGING_PAGE_SIZE) || ((u32)phys % PAGING_PAGE_SIZE)){
		return -ERR_PAGING;
	}

	return paging_set(paging->directory, virt, (u32)phys | flags);
}

int paging_map_range(struct paging_4gb* paging, void* virt, void* phys,int count,int flags){
	int res = 0;
	for(int i = 0; i < count;i++){
		res = paging_map(paging, virt, phys, flags);
		if(res < 0){
			break;
		}
		virt += PAGING_PAGE_SIZE;
		phys += PAGING_PAGE_SIZE;
	}

	return res;
}

int paging_map_to(struct paging_4gb* paging, void* virt, void* phys, void* phys_end,int flags){
	int res = 0;
	if((u32)virt % PAGING_PAGE_SIZE){
		res = -ERR_PAGING;
		goto out;
	}

	if((u32)phys % PAGING_PAGE_SIZE){
		res = -ERR_PAGING;
		goto out;
	}

	if((u32)phys_end % PAGING_PAGE_SIZE){
		res = -ERR_PAGING;
		goto out;
	}

	if((u32) phys_end <= (u32)phys){
		res = -ERR_PAGING;
		goto out;
	}

	u32 len_bytes = phys_end - phys;
	int page_count = len_bytes / PAGING_PAGE_SIZE; 
	res = paging_map_range(paging, virt, phys, page_count, flags);

out: 
	return res;
}

int paging_set(paging_directory directory, void* virt, u32 val){
	if(!paging_is_aligned(virt)){
		return -ERR_PAGING;
	}

	u32 directory_index = 0;
	u32 table_index = 0;
	int res = paging_get_indexes(virt, &directory_index, &table_index);
	if(res < 0){
		return res;
	}

	paging_directory_entry entry = directory[directory_index];
	paging_table_entry* table = (paging_table_entry*)(entry & 0xfffff000);
	table[table_index] = val;

	return 0;   
}

void* paging_get_physical_address(paging_directory directory, void* virt){
	void* virt_addr_new = (void*)paging_align_to_lower_page(virt);
	void* diff = (void*)((u32)virt - (u32)virt_addr_new);
	return (void*)((paging_get(directory, virt_addr_new) & 0xfffff000) + diff);
}

u32 paging_get(paging_directory directory, void* virt ){
	u32 directory_index = 0;
	u32 table_index = 0;
	paging_get_indexes(virt, &directory_index, &table_index);
	paging_directory_entry entry = directory[directory_index];
	paging_table table = (paging_table)(entry & 0xfffff000);
	return table[table_index];
}









