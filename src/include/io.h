#ifndef IO_H
#define IO_H

#include "type.h"

u16 inb(u8 port);
u16 inw(u16 port);

void outb(u16 port, u8 val);
void outw(u16 port, u16 val);


#endif
