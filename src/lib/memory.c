#include "memory.h"

void* memset(void* dest, int ch, size_t size){
	char* ptr = (char*) dest;
	for(int i = 0; i < size; i++){
		ptr[i] = (char)ch;
	}
	return dest;

}

int memcmp(void* s1,void* s2,int count){
	char* c1 = s1;
	char* c2 = s2;
	while(count-- > 0){
		if(*c1++ != *c2++){
			return c1[-1] < c2[-1] ? -1 : 1;
		}
	}

	return 0;	
}

void* memcpy(void* dest, void* src, int len){
	char* d = dest;
	char* s = src;
	while(len--){
		*d++ = *s++;
	}

	return dest;
}
