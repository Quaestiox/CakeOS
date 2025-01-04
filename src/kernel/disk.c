#include "disk.h"
#include "io.h"

int ata_read_sector(int lba, int count, void* buffer){
	
	outb(ATA_MASTER_IO_BASE, count);
	outb(ATA_LBA_LOW, (u8)(lba & 0xff));
	outb(ATA_LBA_MID, (u8)lba >> 8);
	outb(ATA_LBA_HI, (u8)(lba >> 16));
	outb(ATA_DRIVE_HEAD, 0xE0);
	outb(ATA_COMMAND, 0x20);
	
	u16* ptr = (u16*)buffer;

	for(int b = 0; b < count; b++){
		char c = inb(ATA_COMMAND);
		// wait for ready
		while(!(c & 0x08)){
			c = inb(ATA_COMMAND);
		}

		for(int i = 0; i < 256; i++){
			*ptr = inw(ATA_DATA);
			ptr++;
		}
		
	}

	return 0;
}


