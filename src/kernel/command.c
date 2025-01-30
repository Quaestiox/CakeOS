#include "command.h"
#include "print.h"
#include "keyboard.h"

void* syscmd1_print(){
	print_string("Hello CakeOS!\n");
	return 0;
}

void* syscmd2_getKey(){
	return 0;
}
