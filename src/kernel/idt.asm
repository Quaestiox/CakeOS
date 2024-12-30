section .text
global idt_load
global problem

global int_0
global int_21
global int_nothing


extern int_0_handler
extern int_21_handler
extern int_nothing_handler

idt_load:
	push ebp
	mov ebp, esp

	mov eax, [ebp + 8]
	lidt [eax]

	pop ebp
	ret

int_0:
	cli
	pushad

	call int_0_handler
	
	popad
	sti
	iret



int_21:
	cli
	pushad

	call int_21_handler
	
	popad
	sti
	iret

int_nothing:
	cli
	pushad

	call int_nothing_handler
	
	popad
	sti
	iret


problem:
	mov eax, 1
	mov ebx, 2
	div ebx
	jmp $
	

message: db "idt!!!!!!!!!!!!!!!!",0
