#ifndef DISK_H
#define DISK_H

#include "type.h"

enum disk_type{
	REAL_DISK,
};


struct disk{
	enum disk_type type;
	int sector_size;
};

int ata_read_sector(int lba, int count, void* buffer);

#endif
