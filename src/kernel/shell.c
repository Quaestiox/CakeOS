#include "shell.h"
#include "print.h"
#include "keyboard.h"
#include "idt.h"
#include "string.h"

void read_terminal(){
	char str[256] = {'\0'};
	char c = '\0';
	while(1){
		c = get_last_key();
		if ( c != '\0' ){
			if (c == '\n'){
				break;
			}else{
				strpushchar(str, c);
			}
		}
	}
	print_string(str);
	print_char('\n');
}

void shell_start(){
//	enable_interrupt();
	screen_clean();
	print_string("aaaaaaaaaa\n");
	print_string("shell v1.0.0\n");
	while(1){
		print_string("root:>");
		read_terminal();
	}
	
}


