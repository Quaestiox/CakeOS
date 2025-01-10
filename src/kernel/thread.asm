[bits 32]
section .asm
global switch_to

switch_to:
	
	push ebp
	mov ebp, esp
	push esi
	push edi
	push ebx
	

	mov eax, [ebp + 8]
	mov [eax], esp

	mov eax, [ebp + 12]
	mov esp, [eax]

	
	pop ebx
	pop edi
	pop esi
	pop ebp

	
	
	ret






