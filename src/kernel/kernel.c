#include "kernel.h"
#include "print.h"
#include "idt.h"
#include "crt.h"
#include "io.h"
#include "kheap.h"
#include "paging.h"
#include "pic.h"
#include "disk.h"
#include "ata.h"
#include "gdt.h"
#include "tss.h"
#include "thread.h"
#include "keyboard.h"
#include "vfs.h"

extern void problem();

static struct paging_4gb* kernel_paging = 0;


void p3(void* arg){
	char* str = arg;
	while(1){

	print_string(str);
	}
}


void p2(void* arg){
	char* str = arg;
	while(1){

	print_string(str);
	}
}



void kernel_main(){
	screen_clean();	


	set_color(LightCyan, Black);
	print_char('H');

	print_number(254);
	print_string("hello!\n");

	PIC_remap(0x20, 0x28);
	
	gdt_init();


	idt_init();

	kheap_init();

	kernel_paging = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

	paging_switch(kernel_paging);

	enable_paging();


	keyboard_init();

	disk_init();
	init_file_system();
//	print_string("kernel thread start\n");
//	thread_start(p3, "p3:ccc", "p3", 31);
//	thread_start(p2, "p2:aaa", "p2", 8);

	task_init();


	enable_interrupt();



	print_string("aaa");
	while(1){
	}
	
}


