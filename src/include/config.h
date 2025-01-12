#ifndef CONFIG_H
#define CONFIG_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define CODE_SELECTOR 0x08
#define DATA_SELECTOR 0x10
#define TSS_SELECTOR  0x28

#define INTERRUPT_COUNT 256

#define HEAP_SIZE_BYTES 104857600
#define HEAP_BLOCK_SIZE 4096
#define HEAP_ADDRESS 0x01000000
#define HEAP_TABLE_ADDRESS 0x007E0000

#define SECTOR_SIZE 512

#define PAGE_SIZE 4096

#define MAX_PATH 108

#define GDT_SEGMENT_COUNT 6

#define LOGIC_PARTITION_COUNT 8

#define MAX_THREAD 8

#define STACK_MAGIC 0x14159265
#endif 
