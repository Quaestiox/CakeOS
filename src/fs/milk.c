#include "milk.h"
#include "file.h"
#include "string.h"
#include "config.h"
#include "error.h"
#include "disk.h"
#include "math.h"
#include "print.h"
#include "kheap.h"
#include "idt.h"
#include "ata.h"

fs_t milk_fs;
u32 file_num;
milk_info_t* file_info;

fs_t* get_fs_milk(){
	return &milk_fs;
}

static i32 milk_fs_read_data(char* filename, char* buffer, u32 start, u32 length){
	milk_info_t* info = NULL;
	for (int i = 0; i < file_num; i++){
		milk_info_t* info2 = file_info + i;
		if(strcmp(info2->filename, filename) == 0){
			info = info2;
			break;
		}
	}
	if (info == NULL){
		return -ERR_FS_READ;
	}

	u32 offset = info->offset;
	u32 size = info->size;
	if(length > size ){
		length = size;
	}
	read_hard_disk((char*)buffer, milk_fs.partition.offset + offset + start, length);
	return length;
}

static i32 milk_fs_write_data(char* filename, char* buffer, u32 start, u32 length){
	return 0;
}

static i32 milk_fs_list_dir(char* dir){
u32 size_length[file_num];
  u32 max_length = 0;
  for (u32 i = 0; i < file_num; i++) {
    milk_info_t* info = file_info + i;
    u32 size = info->size;
    u32 length = 1;
    while ((size /= 10) > 0) {
      length++;
    }
    size_length[i] = length;
    max_length = max(max_length, length);
  }

  for (u32 i = 0; i < file_num; i++) {
    milk_info_t* info = file_info + i;
    print_string("root  ");
    for (u32 j = 0; j < max_length - size_length[i]; j++) {
      print_string(" ");
    }
    print_string(info->filename);
  }
  return -1;

}

static i32 milk_fs_stat_file(char* filename, file_stat_t* stat){
	for(int i = 0; i < file_num; i++){
		milk_info_t* info = file_info + i;
		if (strcmp(info->filename, filename) == 0){
			stat->size = info ->size;
			return 0;
		}
	}
	return -ERR_FS_STAT;
}

void init_fs_milk(){
	milk_fs.type = MILK;
	milk_fs.partition.offset = MILK_PARTITION;

	milk_fs.stat_file = milk_fs_stat_file;
	milk_fs.read_data = milk_fs_read_data;
	milk_fs.write_data = milk_fs_write_data;
	milk_fs.list_dir = milk_fs_list_dir;

	ata_read_sector(0 + milk_fs.partition.offset, sizeof(u32), (char*)&file_num);

	u32 info_size = file_num * sizeof(milk_info_t);
	file_info = (milk_info_t*)kmalloc(info_size);
	ata_read_sector( 4 + milk_fs.partition.offset, info_size, (char*)file_info);
	for (int i = 0; i < file_num; i++){
		milk_info_t* info = file_info + i;
		print_string(info->filename);
		print_string("\n");
	}
	print_string("MILK file system initialized.\n");

}
