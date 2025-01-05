#include "pic.h"
#include "io.h"
#include "print.h"


void PIC_remap(int offset1, int offset2){
	u8 a1, a2;


	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)

	outb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);

	print_string("PIC remap done.\n");
}


void PIC_disable(){
	outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);

	print_string("PIC disable done.\n");
}

void IRQ_set_mask(u8 irq){
	u16 port;
	u8 value;

	if(irq < 8){
		port = PIC1_DATA;
	} else{
		port = PIC2_DATA;
		irq -= 8;
	}
	value = inb(port) | (1 << irq);
	outb(port, value);
}

void IRQ_clear_mask(u8 irq){
	u16 port;
	u8 value;

	if(irq < 8){
		port = PIC1_DATA;
	} else{
		port = PIC2_DATA;
		irq -= 8;
	}
	value = inb(port) & ~(1 << irq);
	outb(port, value);
}

