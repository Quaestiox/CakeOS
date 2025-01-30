#ifndef MILK_H
#define MILK_H

#include "type.h" 
#include "file.h"

struct milk_info{
	char filename[64];
	u32 size;
	u32 offset;
};
typedef struct milk_info milk_info_t;

void init_fs_milk();

fs_t* get_fs_milk();

#endif 
