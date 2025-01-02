#ifndef CONFIG_H
#define CONFIG_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define CODE_SELECTOR 0x08
#define DATA_SELECTOR 0x10

#define INTERRUPT_COUNT 256

#define HEAP_SIZE_BYTES 104857600
#define HEAP_BLOCK_SIZE 4096
#define HEAP_ADDRESS 0x01000000
#define HEAP_TABLE_ADDRESS 0x00007E00

#endif 
