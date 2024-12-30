#include "kernel.h"
#include "print.h"
#include "idt.h"

extern void problem();

void kernel_main(){
	screen_clean();	
	set_color(LightCyan, Black);
	print_char('H');
	print_string("hello!\n");
	print_string("ooo!\n");
	idt_init();

	problem();
}
