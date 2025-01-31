#ifndef STRING_H
#define STRING_H

#include "type.h"

int strlen(const char* ptr);
bool isdigit(char c);
int tonumericdigit(char c);
int strnlen(const char* ptr, int max);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, int count);
int strcmp(const char* str1,const char* str2);
int strncmp(const char* str1, const char* str2, int n);
int istrncmp(const char* s1, const char* s2, int n);
int strnlen_terminator(const char* str, int max, char terminator);
char tolower(char s1);
int int2str(char* str, int num);
void strcat(char *dest, const char *src);
int strpushchar(char* str, char c);

#endif
