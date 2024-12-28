os_img ?= cakeos.img
os_img_size ?= 2048b
bootloader_dir ?= src/bootloader
bootloader_src_file := ${wildcard ${bootloader_dir}/*.asm}
bootloader_bin_file := ${patsubst ${bootloader_dir}/%.asm, build/%.bin, ${bootloader_src_file}}

all: mkdir ${os_img}

.PHONY: all clean run auto debug

${os_img}: ${bootloader_bin_file}
	qemu-img create build/${os_img} ${os_img_size}
	dd if=build/boot.bin of=build/${os_img} bs=512 count=1
	dd if=/dev/zero bs=512 count=1 >> build/${os_img}
	dd if=build/loader.bin bs=512 count=2 >> build/${os_img}



build/%.bin: ${bootloader_dir}/%.asm
	nasm -f bin $< -o $@

mkdir:
	mkdir build

run:
	qemu-system-x86_64 -hda ./build/${os_img}

clean:
	rm -r build

auto: clean all run

debug: 
	qemu-system-x86_64 -hda ./build/${os_img} -S -s
