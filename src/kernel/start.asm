[bits 32]
global _start
extern kernel_main

_start:

	mov al, 00010001b
	out 0x20, al

	mov al, 0x20
	out 0x21, al

	mov al, 00000001b
	out 0x21, al

	mov byte [0xb8004], 'K'

	call kernel_main

	mov byte [0xb8006], 'N'
	jmp $
	


times 512 - ($ - $$) db 0
