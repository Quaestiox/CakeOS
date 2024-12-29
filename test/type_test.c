#include <stdio.h>
#include "test.h"
#include "type.h"

int main(){

	printf("=============== type test ===============\n");
	printf("size of i8: %d\n", sizeof(i8));
	printf("size of i16: %d\n", sizeof(i16));
	printf("size of i32: %d\n", sizeof(i32));
	printf("size of i64: %d\n", sizeof(i64));

	printf("size of u8: %d\n", sizeof(u8));
	printf("size of u16: %d\n", sizeof(u16));
	printf("size of u32: %d\n", sizeof(u32));
	printf("size of u64: %d\n", sizeof(u64));



	printf_green("\ntype test is finished!\n");

	
}

