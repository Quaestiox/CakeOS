section .asm
global idt_load
global problem

global int_0
global int_21h
global int_nothing
global int_20h
global enable_interrupt
global disable_interrupt

extern int_0_handler
extern int_21h_handler
extern int_20h_handler
extern int_nothing_handler
extern interrupt_handler

idt_load:
	push ebp
	mov ebp, esp

	mov eax, [ebp+8]
	lidt [eax]

	pop ebp
	ret

enable_interrupt:
	sti
	ret

disable_interrupt:
	cli
	ret

int_0:
	call int_0_handler
	iret

int_20h:
	cli
	pushad
	call int_20h_handler
	popad
	sti
	iret

int_21h:
	cli
	pushad

	call int_21h_handler
	
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


message: db "idt!!!!!!!!!!!!!!!!",0

