SHELL := /bin/bash
os_img ?= cakeos.img
os_img_size ?= 2048b
bootloader_dir ?= src/boot
bootloader_src_file := ${wildcard ${bootloader_dir}/*.asm}
bootloader_bin_file := ${patsubst ${bootloader_dir}/%.asm, build/%.bin, ${bootloader_src_file}}

linker_script ?= src/linker_script/linker.ld
kernel_dir ?= src/kernel
kernel_asm_file := ${kernel_dir}/start.asm
kernel_object_file := ${patsubst ${kernel_dir}/%.asm, build/kernel/%.o, ${kernel_asm_file}}
kernel_bin_file := build/kernel.bin

kernel_c_file := ${wildcard ${kernel_dir}/*.c}
kernel_c_object_file := ${patsubst ${kernel_dir}/%.c, build/kernel/%.o, ${kernel_c_file}}

include ?= src/include
ld_flags := -ffreestanding -O0 -nostdlib 
gcc_flags := -g -ffreestanding -falign-jumps -falign-functions -falign-labels        \
			 -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions \
			 -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp    \
			 -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: mkdir shell ${os_img}

.PHONY: all clean run auto debug

${os_img}: ${bootloader_bin_file} ${kernel_bin_file} 
	qemu-img create build/${os_img} ${os_img_size}
	dd if=build/boot.bin of=build/${os_img} bs=512 count=1
	dd if=/dev/zero bs=512 count=1 >> build/${os_img}
	dd if=build/loader.bin bs=512 count=2 conv=sync >> build/${os_img}
	dd if=build/kernel.bin >> build/${os_img}
	dd if=/dev/zero bs=512 count=20 >> build/${os_img}

build/%.bin: ${bootloader_dir}/%.asm
	nasm -f bin $< -o $@

${kernel_object_file}:
	nasm -f elf -g ${kernel_asm_file} -o ${kernel_object_file}

build/kernel/%.o: ${kernel_dir}/%.c
	i686-elf-gcc -I${include} ${gcc_flags} -std=gnu99 -c $< -o $@

build/kernel.bin: ${kernel_object_file} ${kernel_c_object_file}
	i686-elf-ld -g -relocatable ${kernel_object_file} ${kernel_c_object_file} -o build/kernel/kernel_all.o
	i686-elf-gcc -T ${linker_script} build/kernel/kernel_all.o -o build/kernel.bin ${ld_flags}

mkdir:
	mkdir build
	mkdir build/kernel

shell:

run:
	qemu-system-x86_64 -hda ./build/${os_img}

clean:
	rm -r build

auto: clean all run

debug: 
	qemu-system-x86_64 -hda ./build/${os_img} -S -s
