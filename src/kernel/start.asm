section .text
[bits 32]
global _start
extern kernel_main

code_selector equ 0x08
data_selector equ 0x10

_start:
	mov ax, data_selector
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov ebp, 0x0020000
	mov esp, ebp

	; enable A20 line
	in al, 0x92
	or al, 2
	out 0x92, al




	call kernel_main

	jmp $
	


times 512 - ($ - $$) db 0
