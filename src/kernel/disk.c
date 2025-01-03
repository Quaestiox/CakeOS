#include "disk.h"
#include "io.h"

int ata_read_sector(int lba, int count, void* buffer){
	
	outb(0x1F2, count);
	outb(0x1F3, (u8)(lba & 0xff));
	outb(0x1F4, (u8)lba >> 8);
	outb(0x1F5, (u8)(lba >> 16));
	outb(0x1F6, 0xE0);
	outb(0x1F7, 0x20);
	
	u16* ptr = (u16*)buffer;

	for(int b = 0; b < count; b++){
		char c = inb(0x1F7);
		// wait for ready
		while(!(c & 0x08)){
			c = inb(0x1F7);
		}

		for(int i = 0; i < 256; i++){
			*ptr = inw(0x1F0);
			ptr++;
		}
		
	}

	return 0;
}


