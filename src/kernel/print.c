#include "config.h"
#include "type.h"
#include "crt.h"
#include "io.h"
#include "idt.h"
#include "string.h"

struct ScreenChar* buffer = (struct ScreenChar*)0xb8000;
i32 row_pos = 0;
i32 col_pos = 0;
ColorCode color = White | (Black << 4);


static struct ScreenChar empty = (struct ScreenChar){
	character: ' ',
	color: White,
};

void set_color(u8 fore, u8 back){
	color = fore | (back << 4);
}

void clean_row(i32 row){
	for (i32 i = 0; i < VGA_WIDTH; i++){
		buffer[i + VGA_WIDTH * row] = empty;
	}
}


void scroll_up(){
	for(i32 row = 0; row < VGA_HEIGHT - 1; row ++){
		for(i32 col = 0; col < VGA_WIDTH ; col ++){
			buffer[col + VGA_WIDTH * row] = buffer[col + VGA_WIDTH * (row + 1)];
		}
		
	}
	clean_row(VGA_HEIGHT-1);
}

void new_line(){
	if (row_pos >= VGA_HEIGHT - 1){
		scroll_up();
		col_pos = 0;
	}else{
		row_pos ++;
		col_pos = 0;
	}
}

void set_cursor(){
	
	u32 pos = row_pos * VGA_WIDTH + col_pos;
	
	u8 cursor_high = pos / 256;
	u8 cursor_low = pos % 256;

	outb(CRT_ADDR_REG, CRT_CURSOR_H);
	outb(CRT_DATA_REG, cursor_high);
	outb(CRT_ADDR_REG, CRT_CURSOR_L);
	outb(CRT_DATA_REG, cursor_low);
	
}


void backspace(){
	if(col_pos > 0){
		buffer[col_pos + VGA_WIDTH * row_pos - 1] = empty;
		col_pos--;

	}
}

void print_char(char c){
	if(c == '\n'){
		new_line();
	}else if(c == 0x08){
		backspace();
	}else if(col_pos >= VGA_WIDTH){
		new_line();
	}else{
		buffer[col_pos + VGA_WIDTH * row_pos] = (struct ScreenChar){
			character: (u8)c,
			color: color,
		};

		col_pos ++;
	}
	set_cursor();

}

void print_string(char* str){
	for (i32 i = 0; 1; i++){
		char c = (u8)str[i];

		if(c == '\0'){
			return;
		}

		print_char(c);
	}
}

void print_number(int num){
	char* str = "";

	int2str(str, num);
	print_string(str);

}


void screen_clean(){
	for(i32 row = 0; row < VGA_HEIGHT; row ++){
		clean_row(row);
	}
}


