section .asm
global idt_load
global problem

global int_0
global int_21h
global int_20h
global enable_interrupt
global disable_interrupt

extern int_0_handler
extern int_21h_handler
extern int_20h_handler
extern interrupt_handler
extern handler_table


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



%macro INTERRUPT_HANDLER 2
interrupt_handler_%1:
%ifn %2
	push  0x10011001
%endif
	push %1
	jmp interrupt_entry
%endmacro


interrupt_entry:

	push ds
	push es
	push fs
	push gs
	pusha

	mov eax, [esp + 12 * 4]

	push eax
	call [handler_table + eax * 4]

	add esp, 4

	popa
	pop gs
	pop fs
	pop es
	pop ds

	iret

INTERRUPT_HANDLER 0x00, 0
INTERRUPT_HANDLER 0x01, 0
INTERRUPT_HANDLER 0x02, 0
INTERRUPT_HANDLER 0x03, 0
INTERRUPT_HANDLER 0x04, 0
INTERRUPT_HANDLER 0x05, 0
INTERRUPT_HANDLER 0x06, 0
INTERRUPT_HANDLER 0x07, 0
INTERRUPT_HANDLER 0x08, 1
INTERRUPT_HANDLER 0x09, 0
INTERRUPT_HANDLER 0x0a, 1
INTERRUPT_HANDLER 0x0b, 1
INTERRUPT_HANDLER 0x0c, 0
INTERRUPT_HANDLER 0x0d, 0
INTERRUPT_HANDLER 0x0e, 0
INTERRUPT_HANDLER 0x0f, 0
INTERRUPT_HANDLER 0x10, 0
INTERRUPT_HANDLER 0x11, 0
INTERRUPT_HANDLER 0x12, 0
INTERRUPT_HANDLER 0x13, 0
INTERRUPT_HANDLER 0x14, 0
INTERRUPT_HANDLER 0x15, 0
INTERRUPT_HANDLER 0x16, 0
INTERRUPT_HANDLER 0x17, 0
INTERRUPT_HANDLER 0x18, 1
INTERRUPT_HANDLER 0x19, 0
INTERRUPT_HANDLER 0x1a, 1
INTERRUPT_HANDLER 0x1b, 1
INTERRUPT_HANDLER 0x1c, 0
INTERRUPT_HANDLER 0x1d, 0
INTERRUPT_HANDLER 0x1e, 0
INTERRUPT_HANDLER 0x1f, 0

INTERRUPT_HANDLER 0x20, 0; clock 时钟中断
INTERRUPT_HANDLER 0x21, 0; keyboard 键盘中断
INTERRUPT_HANDLER 0x22, 0; cascade 级联 8259
INTERRUPT_HANDLER 0x23, 0; com2 串口2
INTERRUPT_HANDLER 0x24, 0; com1 串口1
INTERRUPT_HANDLER 0x25, 0; sb16 声霸卡
INTERRUPT_HANDLER 0x26, 0; floppy 软盘
INTERRUPT_HANDLER 0x27, 0
INTERRUPT_HANDLER 0x28, 0; rtc 实时时钟
INTERRUPT_HANDLER 0x29, 0
INTERRUPT_HANDLER 0x2a, 0
INTERRUPT_HANDLER 0x2b, 0; nic 网卡
INTERRUPT_HANDLER 0x2c, 0
INTERRUPT_HANDLER 0x2d, 0
INTERRUPT_HANDLER 0x2e, 0; harddisk1 硬盘主通道
INTERRUPT_HANDLER 0x2f, 0; harddisk2 硬盘从通道




section .data
global handler_entry_table
handler_entry_table:
	dd interrupt_handler_0x00
	dd interrupt_handler_0x01
	dd interrupt_handler_0x02
	dd interrupt_handler_0x03
	dd interrupt_handler_0x04
	dd interrupt_handler_0x05
	dd interrupt_handler_0x06
	dd interrupt_handler_0x07
	dd interrupt_handler_0x08
	dd interrupt_handler_0x09
	dd interrupt_handler_0x0a
	dd interrupt_handler_0x0b
	dd interrupt_handler_0x0c
	dd interrupt_handler_0x0d
	dd interrupt_handler_0x0e
	dd interrupt_handler_0x0f
	dd interrupt_handler_0x10
	dd interrupt_handler_0x11
	dd interrupt_handler_0x12
	dd interrupt_handler_0x13
	dd interrupt_handler_0x14
	dd interrupt_handler_0x15
	dd interrupt_handler_0x16
	dd interrupt_handler_0x17
	dd interrupt_handler_0x18
	dd interrupt_handler_0x19
	dd interrupt_handler_0x1a
	dd interrupt_handler_0x1b
	dd interrupt_handler_0x1c
	dd interrupt_handler_0x1d
	dd interrupt_handler_0x1e
	dd interrupt_handler_0x1f

	dd interrupt_handler_0x20
    dd interrupt_handler_0x21
    dd interrupt_handler_0x22
    dd interrupt_handler_0x23
    dd interrupt_handler_0x24
    dd interrupt_handler_0x25
    dd interrupt_handler_0x26
    dd interrupt_handler_0x27
    dd interrupt_handler_0x28
    dd interrupt_handler_0x29
    dd interrupt_handler_0x2a
    dd interrupt_handler_0x2b
    dd interrupt_handler_0x2c
    dd interrupt_handler_0x2d
    dd interrupt_handler_0x2e
    dd interrupt_handler_0x2f







message: db "idt!!!!!!!!!!!!!!!!",0

