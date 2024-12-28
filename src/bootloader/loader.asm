org 0x900

dw 0x7777

loader_start:
	mov si, loader_message
	call print_with_interrupt
	jmp $



print_with_interrupt:
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

loader_message: db "loading...",0
times 512 - ($ - $$) db 0
