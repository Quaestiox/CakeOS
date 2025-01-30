[BITS 32]

section .asm

global program1

program1:

	mov eax, 1
	int 0x80

	ret
