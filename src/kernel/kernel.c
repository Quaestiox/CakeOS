#include "kernel.h"
#include "print.h"

void kernel_main(){
	screen_clean();	
	print_char('H');
	print_string("hello!\n");
	print_string("ooo!\n");
	i8 i = 0;
	while(1){
		for(int i=0; i<5000000;i++){

		}
		print_char((i8)i);
		i ++;
	}
}
