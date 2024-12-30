#include "idt.h"
#include "memory.h"
#include "config.h"
#include "print.h"

extern void idt_load(void* ptr);

struct idt_desc idt_descriptor_table[INTERRUPT_COUNT];
struct idtr_desc idtr_descriptor;


void idt_0(){
	print_string("Divided by zero \n");
}

void idt_set(int interrupt_id, void* address){
	struct idt_desc* desc = &idt_descriptor_table[interrupt_id];
	desc->offset_low = (u32)address & 0x0000ffff;
	desc->selector = CODE_SELECTOR;
	desc->zero = 0x00;
	desc->type_attr = 0xEE;
	desc->offset_high = (u32)address>>16;
}	

void idt_init(){
	memset(idt_descriptor_table, 0, sizeof(idt_descriptor_table));
	idtr_descriptor.limit = sizeof(idt_descriptor_table) - 1;
	idtr_descriptor.base = (u32)idt_descriptor_table;

	idt_set(0, idt_0);
	print_string("idt!\n");
	idt_load(&idtr_descriptor);
}



