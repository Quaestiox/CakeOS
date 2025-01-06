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
	struct partition pri_parts[4];
	struct partition logic_parts[LOGIC_PARTITION_COUNT];
};


struct partition_table_entry{
	u8 bootable;
	u8 start_head;
	u8 start_sector;
	u8 start_chs;
	u8 fs_type;
	u8 end_head;
	u8 end_sector;
	u8 end_chs;
	u32 start_lba;
	u32 sector_count;
} __attribute__((packed));

struct boot_sector{
	u8 code[446];
	struct partition_table_entry partition_table[4];
	u16 signature;
}__attribute__((packed));


void get_disk_info(struct disk* hd);

void disk_init();

u8 hard_disk_count();

#endif
