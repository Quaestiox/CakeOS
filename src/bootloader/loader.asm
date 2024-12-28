org 0x900

dw 0x7777

loader_start:
	mov si, loader_message
	call print_with_interrupt

get_sys_mem_map:
	
	; ards's position
	mov ax, 0
	mov es, ax
	mov edi, ards_buffer

	xor ebx, ebx

	mov edx,0x534d4150 

.next:
	mov eax, 0xe820
	mov ecx, 20 ; ards size
	int 0x15

	jc error

	add edi, ecx
	inc word [ards_count]

	test ebx, ebx
	jnz .next
	
	mov si, msg_success
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

print_4bytes_number:
	mov dx, 0
	mov bx, 0
.loop:
	lodsb 
	add al, 48
	call .print_number
	inc dx
	cmp dx, 4
	jne .loop
	ret
.print_number:
	mov ah, 0eh
	int 0x10
	ret


error:
	mov si, msg_err
	call print_with_interrupt
	jmp $

loader_message: db "Loading...",10, 13, 0
msg_err: db "Get system memory map error!", 10, 13, 0
msg_success: db "Get system memory map succeed.", 10, 13, 0
ards_count: dw 0
ards_buffer:

times 512 - ($ - $$) db 0


