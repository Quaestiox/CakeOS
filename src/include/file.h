#ifndef FILE_H
#define FILE_H

#include "type.h"

enum fs_type{
	MILK
};

struct file_stat{
	u32 flags;
	u32 size;
};
typedef struct file_stat file_stat_t;

struct fs_partition{
	u32 offset;
};
typedef struct fs_partition fs_partition_t;

typedef i32 (*fs_read_func)(char* filename, char* buffer, u32 start, u32 length);
typedef i32 (*fs_write_func)(char* filename, char* buffer, u32 start, u32 length);
typedef i32 (*fs_list_func)(char* dir);
typedef i32 (*fs_stat_func)(char* filename, file_stat_t* stat);

struct filesystem{
	enum fs_type type;
	fs_partition_t partition;

	fs_read_func read_data;
	fs_write_func write_data;
	fs_list_func list_dir;
	fs_stat_func stat_file;

};
typedef struct filesystem fs_t;



#endif
