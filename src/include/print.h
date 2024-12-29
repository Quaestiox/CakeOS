#ifndef PRINT_H
#define PRINT_H

#include "./type.h"

void set_color(u8 fore, u8 back);

void new_line();

void print_char(u8 c);

void print_string(char* str);

void screen_clean();


#endif
