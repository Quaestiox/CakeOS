#include "vfs.h"
#include "milk.h"
#include "print.h"

static fs_t* get_fs(char* path){
	return get_fs_milk();
}

void init_file_system(){
	init_fs_milk();
	print_string("File system initialized.\n");
}

i32 read_file(char* filename, char* buffer, u32 start, u32 length){
	fs_t* fs = get_fs(filename);
	return fs->read_data(filename, buffer, start, length);	
}
i32 write_file(char* filename, char* buffer, u32 start, u32 length){
	fs_t* fs = get_fs(filename);
	return fs->write_data(filename, buffer, start, length);
}
i32 stat_file(char* filename, file_stat_t* stat){
	fs_t* fs = get_fs(filename);
	return fs->stat_file(filename, stat);

}
i32 list_dir(char* dir){
	fs_t* fs = get_fs(dir);
	return fs->list_dir(dir);

}


