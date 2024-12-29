#include <stdio.h>
#include "type.h"

int main(){

	printf("=============== type test ===============\n");
	printf("size of i8: %d\n", sizeof(i8));
	printf("size of i16: %d\n", sizeof(i16));
	printf("size of i32: %d\n", sizeof(i32));
	printf("size of i64: %d\n", sizeof(i64));


	printf_green("\ntype test is finished!\n");

	
}

void printf_green(const char *s)
{
    printf("\033[0m\033[1;32m%s\033[0m", s);
}
