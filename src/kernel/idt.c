#include "idt.h"
#include "memory.h"
#include "config.h"
#include "print.h"
#include "io.h"

struct idt_desc idt_descriptor_table[INTERRUPT_COUNT];
struct idtr_desc idtr_descriptor;

volatile int zero = 0;

extern void idt_load(void* ptr);
extern void int_0();
extern void int_21h();
extern void int_20h();
extern void int_nothing();

void int_21h_handler(){
	print_string("Key!!!\n");
	outb(0x20, 0x20);
}


void int_20h_handler(){
	print_char('.');
	outb(0x20, 0x20);
}
void int_nothing_handler(){
	outb(0x20, 0x20);
}




void int_0_handler(){
		print_string("Divided by zero!\n");
}

void idt_set(int interrupt_id, void* address){
	struct idt_desc desc = idt_descriptor_table[interrupt_id];
	desc.offset_low = (u32)address & 0x0000ffff;
	desc.selector = CODE_SELECTOR;
	desc.zero = 0x00;
	desc.type_attr = 0xEE;
	desc.offset_high = (u32)address>>16;
	idt_descriptor_table[interrupt_id] = desc;
}	

void idt_init(){
	memset(idt_descriptor_table, 0, sizeof(idt_descriptor_table));
	idtr_descriptor.limit = sizeof(idt_descriptor_table) - 1;
	idtr_descriptor.base = (u32)idt_descriptor_table;

	for(int i = 0; i < INTERRUPT_COUNT; i++){
		idt_set(i, int_nothing);
	}

	
	idt_set(0x00, (void*)int_0);
	idt_set(0x21, (void*)int_21h);
	idt_set(0x20, int_20h);

    
	idt_load(&idtr_descriptor);
	print_string("IDT initialized.\n");
}



