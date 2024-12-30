#include "idt.h"
#include "memory.h"
#include "config.h"
#include "print.h"
#include "io.h"

extern void idt_load(struct idtr_desc* ptr);
extern void int_0();
extern void int_21();
extern void int_nothing();

void int_21_handler(){
	print_string("Key!!!\n");
	outb(0x20, 0x20);
}


void int_nothing_handler(){
	outb(0x20, 0x20);
}

struct idt_desc idt_descriptor_table[INTERRUPT_COUNT];
struct idtr_desc idtr_descriptor;


void int_0_handler(){
	print_string("Divided by zero!\n");
	while(1){

	}
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

	for(int i = 0; i < INTERRUPT_COUNT; i++){
		idt_set(i, int_nothing);
	}

	idt_set(0, int_0);
	idt_set(0x21, int_21);


	print_string("idt!\n");
	idt_load(&idtr_descriptor);

	print_string("idt!2\n");
}



