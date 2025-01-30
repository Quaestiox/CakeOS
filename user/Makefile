user_img_dir ?= .
user_img ?= user_img.img

all: tool run

PHONY: all tool run

tool: 
	gcc -o milk_tool MILKTool.c 

run: 
	./milk_tool

clean: 
	rm -f milk_tool ${user_img}
