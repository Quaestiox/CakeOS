#include "disk.h"
#include "bda.h"
#include "print.h"

bool valid_disk_count(){
	return hard_disk_count() > 0;
}

void disk_init(){
	if(!valid_disk_count()){
		print_string("No hard disk!");
		return;
	}

	print_string("Disk init done.");



	
}

u8 hard_disk_count(){
	return *((u8*)HARD_DISK_DRIVE_DETECT);
}
