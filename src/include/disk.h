#ifndef DISK_H
#define DISK_H

#include "type.h"

int ata_read_sector(int lba, int count, void* buffer);

#endif
