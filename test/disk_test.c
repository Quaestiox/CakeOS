#include <stdio.h>
#include "disk.h"
#include "test.h"

int main(){
	printf("=============== disk test ===============\n");

	printf("value of ATA_DATA is: %X\n", ATA_DATA );
	printf("value of ATA_ERR is: %X \n ", ATA_ERR);

	printf_green("\ndisk test is finished!\n");


}
