#ifndef PIC_H
#define PIC_H

#include "type.h"

#define PIC1 0x20 // IO base address for master PIC 
#define PIC2 0xA0 // IO base address for slave PIC 

#define PIC1_COMMAND PIC1 // command port for master PIC
#define PIC1_DATA (PIC1+1) // data port for master PIC 

#define PIC2_COMMAND PIC2 // command port for slave PIC
#define PIC2_DATA (PIC2+1) // data port for slave PIC

#define PIC_EOI 0x20

#define COMMAND_INIT 0x11

#define ICW1_ICW4	0b00000001
#define ICW1_SINGLE	0b00000010
#define ICW1_INTERVAL4	0b00000100
#define ICW1_LTIM	0b00001000
#define ICW1_INIT	0b00010000

#define ICW4_8086	0b00000001
#define ICW4_AUTO	0b00000010
#define ICW4_BUF_SLAVE		0b00001000
#define ICW4_BUF_MASTER	0b00001100
#define ICW4_SFNM	0b00010000

/*	
 *	********************
	ICW1 -> command port 
	ICW2 -> data port
	ICW3 -> data port
	ICW4 -> data port 

	********************
*/

void PIC_remap(int offset1, int offset2);

#endif
