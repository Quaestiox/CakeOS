#include "shell.h"
#include "print.h"
#include "keyboard.h"
#include "idt.h"

void read_terminal(){
	char c;
	while(c != '\n'){
		c = get_last_key();
	}
	print_string("enter!\n");	
}




void shell_start(){
	enable_interrupt();
	screen_clean();
	print_string("Welcome to CakeOS *v*)/\n");
	while(1){
		print_string("root:>");
		read_terminal();
	}
	
}


