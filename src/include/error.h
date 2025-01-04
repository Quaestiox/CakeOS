#ifndef ERROR_H
#define ERROR_H

#include "type.h"

#define ERR_HEAP 2
#define ERR_HEAP_TABLE 3
#define ERR_NO_MEMORY 4
#define ERR_PAGING 5
#define ERR_DISK 6
#define ERR_PATH 7

void eprint(i32 code);

void panic(const char* msg);

#endif
