#include "kernel.h"
#include "print.h"

void kernel_main(){
	screen_clean();	
	print_char('H');
	print_string("hello!\n");
	print_string("ooo!\n");
}
