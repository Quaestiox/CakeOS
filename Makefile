bootloader_dir ?= src/bootloader
boot_source_file := ${bootloader_dir}/boot.asm


all: mkdir boot.bin

.PHONY: all clean run img 

cake_os.img: boot.bin

boot.bin:
	nasm -f bin ${boot_source_file} -o ./build/boot.bin

mkdir:
	mkdir build

run:
	qemu-system-x86_64 -hda ./build/boot.bin

clean:
	rm -r build



