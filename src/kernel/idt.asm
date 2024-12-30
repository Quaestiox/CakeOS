section .text
global idt_load
global idt_zero
idt_load:
	mov byte [0xb8006], 'I' 
	push ebp
	mov ebp, esp

	mov eax, [ebp + 8]
	lidt [eax]

	pop ebp
	ret


message: db "idt!!!!!!!!!!!!!!!!",0
