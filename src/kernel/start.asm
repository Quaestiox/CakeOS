[bits 32]
global _start
global problem
global intret
extern kernel_main

_start:


	mov byte [0xb8004], 'K'

	call kernel_main

	mov byte [0xb8006], 'N'
	jmp $

problem:
	mov eax, 0
	div eax
	ret


times 512 - ($ - $$) db 0
