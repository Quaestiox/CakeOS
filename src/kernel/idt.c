#include "idt.h"
#include "memory.h"
#include "config.h"
#include "print.h"
#include "io.h"
#include "thread.h"

struct idt_desc idt[INTERRUPT_COUNT];
struct idtr_desc idtr_descriptor;

volatile int zero = 0;
u32 ticks;

extern void idt_load(void* ptr);
extern void int_0();
extern void int_21h();
extern void int_20h();
extern void int_nothing();

void* handler_table[INTERRUPT_COUNT];
extern void* handler_entry_table[INTERRUPT_COUNT]; 

void int_21h_handler(){
	print_string("Key!!!\n");
	outb(0x20, 0x20);
}


void int_20h_handler(){
//	print_char('.');	

	struct task_struct* current = running_task();
	current->clock -= 1;
	current->run_clock += 1;
	if(!current->clock){
		current->clock = current->priority;
		schedule();
	}

	
/*
	if(current_thread->stack_magic != STACK_MAGIC){
		print_string("stack overflow!");
	}

	current_thread->run_clock++;
	ticks++;

	if (current_thread->clock == 0){
		schedule();
	} else{
		current_thread->clock--;
	}

*/
	outb(0x20, 0x20);
}
void default_handler(){
	outb(0x20, 0x20);
}




void int_0_handler(){
		print_string("Divided by zero!\n");
}

void idt_set(int interrupt_id, void* address){
	struct idt_desc desc = idt[interrupt_id];
	desc.offset_low = (u32)address & 0x0000ffff;
	desc.selector = CODE_SELECTOR;
	desc.zero = 0x00;
	desc.type_attr = 0xEE;
	desc.offset_high = (u32)address>>16;
	idt[interrupt_id] = desc;
}	

void idt_init(){
	memset(idt, 0, sizeof(idt));
	idtr_descriptor.limit = sizeof(idt) - 1;
	idtr_descriptor.base = (u32)idt;

	for(int i = 0; i < INTERRUPT_COUNT; i++){
		idt_set(i, default_handler);
	}

	
	idt_set(0x00, (void*)int_0);
	idt_set(0x21, (void*)int_21h);
	idt_set(0x20, int_20h);

    
	idt_load(&idtr_descriptor);
	print_string("IDT initialized.\n");
}



