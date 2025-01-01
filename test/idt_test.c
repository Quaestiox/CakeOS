#include <stdio.h>
#include "idt.h"


int main(){

	idt_init();

	printf("=============== idt test ===============\n");
	struct idt_desc* desc_table = get_idt_addr();
	printf("idt_descriptor_table address is: %d", (u32)desc_table);




}
