os_img ?= cakeos.img
os_img_size ?= 2048b
bootloader_dir ?= src/boot
bootloader_src_file := ${wildcard ${bootloader_dir}/*.asm}
bootloader_bin_file := ${patsubst ${bootloader_dir}/%.asm, build/%.bin, ${bootloader_src_file}}

linker_script ?= src/linker_script/linker.ld
kernel_dir ?= src/kernel
kernel_asm_file := ${wildcard ${kernel_dir}/*.asm}
kernel_object_file := ${patsubst ${kernel_dir}/%.asm, build/kernel/%_asm.o, ${kernel_asm_file}}
kernel_bin_file := build/kernel.bin

kernel_c_file := ${wildcard ${kernel_dir}/*.c}
kernel_c_object_file := ${patsubst ${kernel_dir}/%.c, build/kernel/%.o, ${kernel_c_file}}

lib_dir ?= src/lib
lib_c_file := ${wildcard ${lib_dir}/*.c}
lib_c_object_file := ${patsubst ${lib_dir}/%.c, build/lib/%.o, ${lib_c_file}}

fs_dir ?= src/fs
fs_c_file := ${wildcard ${fs_dir}/*.c}
fs_c_object_file := ${patsubst ${fs_dir}/%.c, build/fs/%.o, ${fs_c_file}}

test_dir ?= test
test_src_file := ${wildcard ${test_dir}/*.c}
test_exec_file := ${patsubst ${test_dir}/%.c, test_build/%, ${test_src_file}}



include ?= ./src/include
gcc_flags ?= -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops \
			 -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function \
			 -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib \
			 -nostartfiles -nodefaultlibs -Wall -O0 -Iinc



all: mkdir shell ${os_img}

.PHONY: all clean run auto debug test test_clean

${os_img}: ${bootloader_bin_file} ${kernel_bin_file} 
	qemu-img create build/${os_img} ${os_img_size}
	dd if=build/boot.bin of=build/${os_img} bs=512 count=1
	dd if=/dev/zero bs=512 count=1 >> build/${os_img}
	dd if=build/loader.bin bs=512 count=2  conv=sync >> build/${os_img}
	dd if=build/kernel.bin >> build/${os_img}
	dd if=/dev/zero bs=512 count=200 >> build/${os_img}




build/%.bin: ${bootloader_dir}/%.asm
	nasm -f bin $< -o $@

build/kernel/%_asm.o: ${kernel_dir}/%.asm
	nasm -f elf -g $< -o $@

build/kernel/%.o: ${kernel_dir}/%.c
	i686-elf-gcc -I${include} ${gcc_flags} -std=gnu99 -c $< -o $@

build/lib/%.o: ${lib_dir}/%.c
	i686-elf-gcc -I${include} ${gcc_flags} -std=gnu99 -c $< -o $@

build/fs/%.o: ${fs_dir}/%.c
	i686-elf-gcc -I${include} ${gcc_flags} -std=gnu99 -c $< -o $@

build/kernel.bin: build/kernel/start_asm.o \
					build/kernel/idt_asm.o \
					build/kernel/io_asm.o \
					build/kernel/paging_asm.o \
					build/kernel/gdt_asm.o \
 					${lib_c_object_file} \
					${kernel_c_object_file} \
					${fs_c_object_file}
	i686-elf-ld -relocatable -g build/kernel/start_asm.o \
					build/kernel/idt_asm.o \
					build/kernel/io_asm.o \
					build/kernel/paging_asm.o \
					build/kernel/gdt_asm.o \
 					${lib_c_object_file} \
					${kernel_c_object_file} \
					${fs_c_object_file} \
				-o build/kernel_all.o
 
	i686-elf-gcc -T ${linker_script} build/kernel_all.o -o build/kernel.bin ${gcc_flags}

mkdir:
	mkdir build
	mkdir build/kernel
	mkdir build/test
	mkdir build/lib
	mkdir build/fs

shell:

run:
	qemu-system-i386 -hda ./build/${os_img}

clean:
	rm -r build

auto: clean all run

debug: 
	qemu-system-x86_64 -hda ./build/${os_img} -S -s

test: test_mkdir ${test_exec_file}

test_mkdir:
	mkdir test_build
test_clean: 
	rm -r test_build

test_build/%: ${test_dir}/%.c
	gcc -I${include} $< -o $@
	./$@
