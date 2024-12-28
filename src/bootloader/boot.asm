org 0x7c00
bits 16

start:
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7c00

	call set_text_mode

	mov si, message
	call print_with_interrupt

	mov eax, 2 ; lba of beginning
	mov ecx, 1 ; sector count
	mov edi, 0x900 ; target address

	call read_ata_disk

	mov ax, 0
	mov ds, ax
	cmp word [0x900], 0x7777
	jne .err_to_loader

	jmp 0:902

.err_to_loader:
	mov si, msg_err_to_loader
	call print_with_interrupt
	jmp $

set_text_mode:
	mov ax, 3
	int 0x10
	ret

print_with_memory:
	mov ax, 0xb800
	mov ds, ax
	mov byte [0x00], 'B'
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

read_ata_disk:
	mov ebx, eax ; backup the LBA

	mov eax, ecx
	mov dx, 0x1F2 ; set sector count
	out dx, al

	mov eax, ebx
	mov dx, 0x1F3
	out dx, al

	mov dx,0x1F4
	mov eax, ebx
	shr eax, 8
	out dx, al

	mov dx, 0x1F5
	mov eax, ebx
	shr eax, 16
	out dx, al

	shr eax, 24
	or eax, 0xE0  ; set master disk
	mov dx, 0x1F6 ; set high 4 bits of LBA
	out dx, al

	mov dx, 0x1F7
	mov al, 0x20 ; read command
	out dx, al
.next_sector:
	push ecx
.do_again:
	mov dx, 0x1F7
	in al, dx
	test al, 8 ; check DQR bit
	jz .do_again 

	mov ecx, 256
	mov dx, 0x1F0
	rep insw 
	pop ecx
	loop .next_sector

	ret




message: db "Booting...",13,10,0
msg_err_to_loader: db "Loading loader error!",13,10,0

times 510 - ($ - $$) db 0
db 0x55, 0xaa



