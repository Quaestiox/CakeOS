#include "string.h"

char tolower(char s1){
	if(s1 >= 65 && s1 <= 90){
		s1 += 32;
	}

	return s1;
}

int strlen(const char* ptr){
	int i = 0;
	while(*ptr != 0){
		i++;
		ptr += 1;
	}

	return i;
}

int strnlen(const char* ptr, int max){
	int i = 0;
	for(i = 0; i < max; i++){
		if (ptr[i] == 0)
			break;
	}

	return i;
}

int strnlen_terminator(const char* str, int max, char terminator){
	int i = 0;
	for(i = 0; i < max; i++){
		if(str[i] == '\0' || str[i] == terminator )
			break;
	}

	return i;
}

int istrncmp(const char* str1, const char* str2, int n){
	unsigned char u1, u2;

	while(n-- > 0){
		u1 = (unsigned char)*str1++;
		u2 = (unsigned char)*str2++;
		if(u1 != u2 && tolower(u1) != tolower(u2))
			return u1 - u2;
		if(u1 == '\0')
			return 0;
	}

	return 0;
}

int strcmp(const char* str1,const char* str2) {
  int i = 0;
  char c;
  while ((c = str1[i]) != '\0') {
    char c2 = str2[i];
    if (c2 == '\0') {
      return 1;
    }
    if (c != c2) {
      return c < c2 ? -1 : 1;
    }
    i++;
  }
  return str2[i] == '\0' ? 0 : 1;
}


int strncmp(const char* str1, const char* str2, int n){
	unsigned char u1, u2;

	while(n-- > 0){
		u1 = (unsigned char)*str1++;
		u2 = (unsigned char)*str2++;
		if(u1 != u2)
			return u1 - u2;
		if(u1 == '\0')
			return 0;
	}

	return 0;
}

char* strcpy(char* dest ,const char* src){
	char* res = dest;
	while(*src != 0){
		*dest = *src;
		src += 1;
		dest += 1;
	}

	*dest = 0x00;

	return res;
}

char* strncpy(char* dest, const char* src, int count){
	int i = 0;
	for(i = 0; i < count; i++){
		if(src[i] == 0x00)
			break;

		dest[i] = src[i];
	}

	dest[i] = 0x00;
	return dest;
}

bool isdigit(char c){
	return c >= 48 && c <= 57;
}

int tonumericdigit(char c){
	return c - 48;
}

int int2str(char* dst, int num) {
  u32 start = 0;
  if (num < 0 ) {
    dst[start++] = '-';
    num = -num;
  }

  char buf[16];
  buf[15] = '\0';
  u32 i = 14;
  while (num > 0) {
    u32 remain = num % 10;
    buf[i--] = '0' + remain;
    num = num / 10;
  }

  strcpy(dst + start, buf + i + 1);
  return start + 14 - i;
}

void strcat(char *dest, const char *src) {
    while (*dest != '\0') {
        dest++;
    }

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
}

int strpushchar(char* str, char c){
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }

    str[len] = c;
    str[len + 1] = '\0';


    return 0;
}

int isspace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

char* trim(char *str) {
	char* res;
    while (*str && isspace((unsigned char)*str)) {
        str++;
    }
    
	res = str;
    if (*str) {
        char *end = str + strlen(str) - 1;
        while (end > str && isspace((unsigned char)*end)) {
            end--;
        }
        *(end + 1) = '\0';
    }
	return res;
}


