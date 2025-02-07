#ifndef DISK_H
#define DISK_H

#include "type.h"
#include "config.h"

extern void read_disk(void* buffer, u32 lba, u8 sector_count);

struct partition{
	u32 start_lba;
	u32 sector_count;
	struct disk* disk;
	char name[8];
};

struct disk{
	char name[8];
	u8 dev_no;
	struct partition pri_parts[4];
	struct partition logic_parts[LOGIC_PARTITION_COUNT];
};



void get_disk_info(struct disk* hd);

void disk_init();

u8 hard_disk_count();

void read_hard_disk(char* buffer, u32 start, u32 length);

static void read_sector(char* buffer, u32 sector);
#endif
