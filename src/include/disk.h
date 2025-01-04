#ifndef DISK_H
#define DISK_H

#include "type.h"
#include "config.h"


struct partition{
	u32 start_lba;
	u32 sector_count;
	struct disk* disk;
	char name[8];
};

struct disk{
	char name[8];
	u8 dev_no;
	struct ide_channel* channel;
	struct partition pri_parts[4];
	struct partition logic_parts[LOGIC_PARTITION_COUNT];
};

struct ide_channel{
	char name[8];
	u16 port_base;
	u8 irq_no;
	struct disk devices[2];
};


int ata_read_sector(int lba, int count, void* buffer);

#endif
