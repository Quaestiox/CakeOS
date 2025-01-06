#include "gdt.h"
#include "error.h"
#include "config.h"
#include "memory.h"
#include "print.h"

struct gdt gdt_real[GDT_SEGMENT_COUNT];
struct gdt_structured gdt_structured[GDT_SEGMENT_COUNT] = {
	{.base = 0x00, .limit = 0x00, .type = 0x00},
	{.base = 0x00, .limit = 0xffffffff, .type = 0x9a},
	{.base = 0x00, .limit = 0xffffffff, .type = 0x92},
	{.base = 0x00, .limit = 0xffffffff, .type = 0xf8},		//User code segment
	{.base = 0x00, .limit = 0xffffffff, .type = 0xf2},	//User data segment
};
void encodeGdtEntry(u8* target, struct gdt_structured source){
	if((source.limit > 65536) && ((source.limit & 0xFFF) != 0xFFF)){
		panic("encodeGdtEntry: Invalid argument\n");
	}

	target[6] = 0x40;
	if(source.limit > 65536){
		source.limit = source.limit >> 12;
		target[6] = 0xC0;
	}

	target[0] = source.limit & 0xFF;
	target[1] = (source.limit >> 8) & 0xFF;
	target[6] |= (source.limit >> 16) & 0x0F;

	target[2] = source.base & 0xFF;
	target[3] = (source.base >> 8) & 0xFF;
	target[4] = (source.base >> 16) & 0xFF;
	target[7] = (source.base >> 24) & 0xFF;

	target[5] = source.type;

}

void gdt_structured_to_gdt(struct gdt* gdt, struct gdt_structured* structured_gdt, int total_entires){
	for(int i = 0; i < total_entires; i++){
		encodeGdtEntry((u8*) & gdt[i], structured_gdt[i]);
	}
}


void gdt_init(){
	memset(gdt_real, 0x00, sizeof(gdt_real));
	gdt_structured_to_gdt(gdt_real, gdt_structured,GDT_SEGMENT_COUNT);

	gdt_load(gdt_real, sizeof(gdt_real));
	print_string("GDT initialized.\n");
}

struct gdt* get_gdt(){
	return gdt_real;
}
