#ifndef IDT_H
#define IDT_H

#include "type.h"

struct idt_desc{
	u16 offset_low; // offset 0-15 bits 
	u16 selector;
	u8 zero;
	u8 type_attr;
	u16 offset_high; // offset 16-31 bits
} __attribute__((packed));

struct idtr_desc{
	u16 limit;
	u32 base;
};


void idt_init();


#endif
