#ifndef PAGING_H
#define PAGING_H

#include "type.h"

#define PAGING_ATTRIBUTE_TABLE	0b10000000
#define PAGING_DIRTY		    0b01000000
#define PAGING_ACCESSED			0b00100000
#define PAGING_CACHE_DISABLED	0b00010000
#define PAGING_WRITE_THROUGH	0b00001000
#define PAGING_ACCESS_FROM_ALL	0b00000100
#define PAGING_IS_WRITEABLE		0b00000010
#define PAGING_IS_PRESENT		0b00000001

#define PAGING_TABLE_ENTRY_COUNT		1024
#define PAGING_DIRECTORY_ENTRY_COUNT	1024
#define PAGING_PAGE_SIZE				4096

typedef u32 paging_table_entry;
typedef paging_table_entry* paging_table;
typedef u32 paging_directory_entry;
typedef paging_directory_entry* paging_directory;

struct paging_4gb{
	paging_directory directory;
};

struct paging_4gb* paging_new_4gb(u8 flags);
void paging_switch(struct paging_4gb* paging);
void enable_paging();
paging_directory paging_get_directory(struct paging_4gb* paging);

int paging_map_to(struct paging_4gb* paging, void* virt, void* phys, void* phys_end,int flags);
int paging_set(paging_directory dircetory, void* virt, u32 val);
void paging_free(struct paging_4gb* paging);
u32 paging_get(paging_directory directory, void* virt );


#endif
