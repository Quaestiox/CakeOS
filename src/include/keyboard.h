#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_CTRL_PORT 0x64

#define ESC '\033'
#define BACKSPACE '\b'
#define TAB '\t'
#define ENTER '\r'
#define DELETE '\177'


#define INV 0

#define shift_l_make 0x2a
#define shift_r_make 0x36
#define caps_lock_make 0x3a

#define KEY_BUFFER_SIZE 256

#include "type.h"

typedef struct {
	char buffer[KEY_BUFFER_SIZE];
	int head;
	int tail;
} key_buffer_t;

void keyboard_handler();
void keyboard_init();
char get_last_key();
char dequeue_key();
#endif 
