#ifndef GDT_H
#define GDT_H

#include "type.h"

struct gdt{
	u16 segment;
	u16 base_first;
	u8 base;
	u8 access;
	u8 high_flags;
	u8 base_24_31;
} __attribute__((packed));

struct gdt_structured{
	u32 base;
	u32 limit;
	u8 type;
};

void gdt_load(struct gdt* gdt,int size);
void gdt_structured_to_gdt(struct gdt* gdt,struct gdt_structured* structured_gdt, int total_entires);
struct gdt* get_gdt();
void gdt_init();

#endif

