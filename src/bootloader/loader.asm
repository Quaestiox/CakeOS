org 0x900

dw 0x7777

loader_start:
	mov si, loader_message
	call print_with_interrupt
		
	call get_sys_mem_map

.load_protected_mode:
	cli 

	; load to gdtr
	lgdt[gdt_descriptor]

	; enable A20 line
	in al, 0x92
	or al, 0b10
	out 0x92, al

	; enable protected mode
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	jmp code_selector:protected_mode_start




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
	ret

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


error:
	mov si, msg_err
	call print_with_interrupt
	jmp $

loader_message: db "Loading...",10, 13, 0
msg_err: db "Get system memory map error!", 10, 13, 0
msg_success: db "Get system memory map succeed.", 10, 13, 0

gdt_start:
gdt_null:
	dd 0x00
	dd 0x00
gdt_code:
	dw 0xFFFF ; limit 0-15 bits
	dw 0x0  ; base 0-15 bits
	db 0x0 ; base 16-23 bits
	db 0x9a ; access byte
	db 0xCF ; limit 16-19 bits and flags
	db 0x0 ; base 24-31 bits
gdt_data:
	dw 0xFFFF ; limit 0-15 bits
	dw 0x0  ; base 0-15 bits
	db 0x0 ; base 16-23 bits
	db 0x92 ; access byte
	db 0xCF ; limit 16-19 bits and flags
	db 0x0 ; base 24-31 bits
gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start



code_selector equ gdt_code - gdt_start
data_selector equ gdt_data - gdt_start


[bits 32]
protected_mode_start:
	mov ax, data_selector
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov ebp, 0x00200000
	mov esp, ebp

	jmp $

times 512 - ($ - $$) db 0
ards_count: dw 0
ards_buffer:



