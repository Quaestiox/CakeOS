#include "idt.h"
#include "memory.h"
#include "config.h"
#include "print.h"
#include "io.h"
#include "thread.h"
#include "keyboard.h"

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


bool get_interrupt_state(){
	bool res;
	asm volatile(
		"pushfl\n"
		"popl %%eax\n"
		"shrl $9, %%eax\n"
		"andl $1, %%eax\n"
	: "=a"(res));
	return res;
}

void set_interrupt_state(bool state){
	if(state)
		asm volatile("sti\n");
	else
		asm volatile("cli\n");
}


void int_21h_handler(){
	keyboard_handler();
	outb(0x20, 0x20);
}


void int_20h_handler(){
	outb(0x20, 0x20);

	struct task_struct* current = running_task();
	if(current->magic != STACK_MAGIC){
		print_string("stack overflow!");
	}


	current->clock --;
	current->run_clock ++;
	if(current->clock <= 0){
		current->clock = current->priority;
		schedule();
	}

//	outb(0x20, 0x20);
}

void default_handler(){
	outb(0x20, 0x20);
}


void init_timer(unsigned int frequency) {
    unsigned int divisor = 1193180 / frequency;
    outb(0x43, 0x36);               // 设置模式
    outb(0x40, divisor & 0xFF);     // 低字节
    outb(0x40, (divisor >> 8) & 0xFF); // 高字节
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



