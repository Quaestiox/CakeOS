#include "syscmd.h"
#include "idt.h"
#include "command.h"

void init_syscmd(){
	register_command(SYSCMD1_PRINT, syscmd1_print);
	register_command(SYSCMD2_GETKEY, syscmd2_getKey);	
}
