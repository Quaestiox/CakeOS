org 0x7c00
bits 16

start:

	mov ax, 0
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7c00

	call set_text_mode

	call print_with_interrupt

	jmp $

set_text_mode:
	mov ax, 3
	int 0x10
	ret

print_with_memory:
	mov ax, 0xb800
	mov ds, ax
	mov byte [0x00], 'b'
	mov byte [0x02], 'o'
	mov byte [0x04], 'o'
	mov byte [0x06], 't'
	mov byte [0x08], 'i'
	mov byte [0x0a], 'n'
	mov byte [0x0c], 'g'
	mov byte [0x0e], '.'
	mov byte [0x10], '.'
	mov byte [0x12], '.'
	ret

print_with_interrupt:
	mov si, message
	mov bx, 0
.loop:
	lodsb
	cmp al, 0
	je .done
	call .print_char
	jmp .loop
.print_char:
	mov ah, 0eh
	int 0x10
	ret

.done: 	
	ret


message: db "booting...",0

times 510 - ($ - $$) db 0
db 0x55, 0xaa



