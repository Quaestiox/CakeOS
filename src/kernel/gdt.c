#include "gdt.h"
#include "error.h"
#include "config.h"
#include "memory.h"
#include "print.h"
#include "tss.h"

struct tss tss;
struct gdt_entry kernel_code_segment = { 
	0x00, 
	0xffffffff,
	0x9a,
};

struct gdt_entry kernel_data_segment = {
	0x00, 
	0xffffffff, 
	0x92,
};

struct gdt_entry user_code_segment = {
	0x00,
	0xffffffff,
	0xf8,	
};

struct gdt_entry user_data_segment = {
	0x00, 
	0xffffffff,
	0xf2,
};

struct gdt_entry null_segment = {
	00,00,00
};

struct gdt_entry_original gdt_original[GDT_SEGMENT_COUNT];
struct gdt_entry gdt[GDT_SEGMENT_COUNT] = {
	{.base = (u32)&tss, .limit = sizeof(tss), .type = 0xE9},
};
void encodeGdtEntry(u8* target, struct gdt_entry source){
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

void gdt_entry_to_original(struct gdt_entry_original* gdt, struct gdt_entry* gdt_e, int total_entires){
	for(int i = 0; i < total_entires; i++){
		encodeGdtEntry((u8*) & gdt[i], gdt_e[i]);
	}
}


void gdt_init(){

	gdt[0] = null_segment;
	gdt[1] = kernel_code_segment;
	gdt[2] = kernel_data_segment;
	gdt[3] = user_code_segment;
	gdt[4] = user_data_segment;
	gdt[5].base = (u32)&tss;
    gdt[5].limit = sizeof(tss);
    gdt[5].type = 0xE9; 


	memset(gdt_original, 0x00, sizeof(gdt_original));
	gdt_entry_to_original(gdt_original, gdt, GDT_SEGMENT_COUNT);

	gdt_load(gdt_original, sizeof(gdt_original));

	memset(&tss, 0x00, sizeof(tss));
	tss.esp0 = 0x600000;
	tss.ss0 = DATA_SELECTOR;
	tss_load(TSS_SELECTOR);

	print_string("GDT initialized.\n");
}

struct gdt_entry_original* get_gdt(){
	return gdt_original;
}
