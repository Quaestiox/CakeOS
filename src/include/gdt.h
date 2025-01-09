#ifndef GDT_H
#define GDT_H

#include "type.h"

struct gdt_entry_original{
	u16 segment;
	u16 base_first;
	u8 base;
	u8 access;
	u8 high_flags;
	u8 base_24_31;
} __attribute__((packed));

struct gdt_entry{
	u32 base;
	u32 limit;
	u8 type;
};

void gdt_load(struct gdt_entry_original* gdt,int size);
void gdt_entry_to_original(struct gdt_entry_original* gdt,struct gdt_entry* structured_gdt, int total_entires);
struct gdt_entry_original* get_gdt();
void gdt_init();

#endif

