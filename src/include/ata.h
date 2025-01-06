#ifndef ATA_H
#define ATA_H

#include "type.h"
#include "config.h"


#define ATA_MASTER_IO_BASE	0x1F0
#define ATA_MASTER_CT_BASE	0x3F6

#define ATA_SLAVE_IO_BASE	0x170
#define ATA_SLAVE_CT_BASE	0x376

enum {
	ATA_DATA = ATA_MASTER_IO_BASE,
	ATA_ERR,
	ATA_FEATUER,
	ATA_SECTOR_COUNT,
	ATA_LBA_LOW,
	ATA_LBA_MID,
	ATA_LBA_HI,
	ATA_DRIVE_HEAD,
	ATA_STATUS,
	ATA_COMMAND,
};

enum{
	ATA_EXSTAT_DEVICE = ATA_MASTER_CT_BASE,
	ATA_DRIVE_ADDR,
};

#define STAT_ERR	0b00000001
#define STAT_IDX	0b00000010
#define STAT_CORR	0b00000100
#define STAT_READY	0b00001000
#define STAT_SRV	0b00010000
#define STAT_DF		0b00100000
#define STAT_RDY	0b01000000
#define STAT_BSY	0b10000000

#define ATA_READ		0x20
#define ATA_WRITE		0x30
#define ATA_IDENTIFY	0xec


int ata_read_sector(int lba, int count, void* buffer);

#endif
