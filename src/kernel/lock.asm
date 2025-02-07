section .asm
[bits 32]

global atomic_exchange

atomic_exchange:
	push ebp 
	mov ebp, esp
	mov ecx, [ebp + 8]
	mov eax, [ebp + 12]
	xchg [ecx], eax

	pop ebp
	ret


