#include "kernel.h"
#include "print.h"
#include "idt.h"
#include "crt.h"
#include "io.h"
#include "kheap.h"
#include "paging.h"
#include "pic.h"
extern void problem();

static struct paging_4gb* kernel_paging = 0;

void kernel_main(){
	screen_clean();	
	set_color(LightCyan, Black);
	print_char('H');
	print_string("hello!\n");

	PIC_remap(0x20, 0x28);
	idt_init();

	kheap_init();

	kernel_paging = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

	paging_switch(kernel_paging);

	enable_paging();

	enable_interrupt();
}
