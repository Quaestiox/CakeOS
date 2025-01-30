#include "disk.h"
#include "bda.h"
#include "print.h"
#include "config.h"
#include "memory.h"
#include "kheap.h"
#include "math.h"


bool valid_disk_count(){
	return hard_disk_count() > 0;
}

void disk_init(){
	if(!valid_disk_count()){
		print_string("No hard disk!\n");
		return;
	}

	print_string("Disk init done.\n");



	
}

u8 hard_disk_count(){
	return *((u8*)HARD_DISK_DRIVE_DETECT);
}

static void read_sector(char* buffer, u32 sector) {
  read_disk(buffer, sector, 1);
}

void read_hard_disk(char* buffer, u32 start, u32 length) {
  u32 end = start + length;

  u32 start_sector = start / SECTOR_SIZE;
  u32 end_sector = (end - 1) / SECTOR_SIZE + 1;

  // Do NOT allocate buffer on kernel stack!
  char* sector_buffer = (char*)kmalloc(SECTOR_SIZE);

  for (u32 i = start_sector; i < end_sector; i++) {
    read_sector(sector_buffer, i);

    u32 copy_start_addr = max(i * SECTOR_SIZE, start);
    u32 copy_end_addr = min((i + 1) * SECTOR_SIZE, end);
    u32 copy_size = copy_end_addr - copy_start_addr;
    memcpy(buffer, sector_buffer + copy_start_addr - i * SECTOR_SIZE, copy_size);
    buffer += (copy_size);
  }

  kfree(sector_buffer);
}

