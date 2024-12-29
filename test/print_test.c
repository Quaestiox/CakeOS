#include <stdio.h>
#include "print.h"
#include "test.h"


int main(){


	printf("=============== print test ===============\n");
	ColorCode color = White | (Black << 4);
	printf("code of color white is: %d\n", White);
	printf("code of color black is: %d\n", Black);
	printf("color is: %d", color);

	printf_green("print test finished!\n");

	
}


