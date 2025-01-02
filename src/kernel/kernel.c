#include "kernel.h"
#include "print.h"
#include "idt.h"
#include "crt.h"
#include "io.h"
#include "kheap.h"

extern void problem();

void kernel_main(){
	screen_clean();	
	set_color(LightCyan, Black);
	print_char('H');
	print_string("hello!\n");

	idt_init();

	kheap_init();

	enable_interrupt();
}
