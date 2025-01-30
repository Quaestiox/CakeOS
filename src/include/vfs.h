#ifndef VFS_H
#define VFS_H

#include "type.h"
#include "file.h"  

void init_file_system();

i32 read_file(char* filename, char* buffer, u32 start, u32 length);
i32 write_file(char* filename, char* buffer, u32 start, u32 length);
i32 stat_file(char* filename, file_stat_t* stat);
i32 list_dir(char* dir);


#endif
