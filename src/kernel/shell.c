#include "shell.h"
#include "print.h"
#include "keyboard.h"
#include "idt.h"
#include "string.h"
#include "vfs.h"

void cmd_echo_handler(char* cmd){
	cmd += 5;
	print_string(cmd);
	print_char('\n');
}

void cmd_ls_handler(){
	list_dir("/");
}

void parse_command(char* cmd){

	char hi[] = "hello";
	char echo[] = "echo ";	
	char ls[] = "ls";
	if(!strcmp(hi, cmd)){
		print_string("hi :D\n");
	} else if (!strncmp(cmd, echo, strlen(echo))){
		cmd_echo_handler(cmd);
	} else if (!strcmp(cmd, ls)){
		cmd_ls_handler();
	} else{
		print_string("invalid command: ");
		print_string(cmd);
		print_char('\n');
	}
}

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
    char* str_trim = trim(str);
	parse_command(str_trim);
//	print_string(str_trim);
//	print_char('\n');
}

void shell_start(){
//	enable_interrupt();
	screen_clean();
	print_string("shell v1.0.0\n");
	while(1){
		print_string("root:>");
		read_terminal();
	}
	
}


