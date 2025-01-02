#include "error.h"
#include "print.h"


void eprint(i32 code){
	switch (code){
		case -1: 
			print_string("io error\n");
		case -ERR_HEAP:
			print_string("heap_error\n");
		case -ERR_HEAP_TABLE:
			print_string("heap_table_error\n");
		case -ERR_NO_MEMORY:
			print_string("no_memory_error\n");
	}
}
