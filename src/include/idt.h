#ifndef IDT_H
#define IDT_H

#include "type.h"

#define INTR_DE 0   // 除零错误
#define INTR_DB 1   // 调试
#define INTR_NMI 2  // 不可屏蔽中断
#define INTR_BP 3   // 断点
#define INTR_OF 4   // 溢出
#define INTR_BR 5   // 越界
#define INTR_UD 6   // 指令无效
#define INTR_NM 7   // 协处理器不可用
#define INTR_DF 8   // 双重错误
#define INTR_OVER 9 // 协处理器段超限
#define INTR_TS 10  // 无效任务状态段
#define INTR_NP 11  // 段无效
#define INTR_SS 12  // 栈段错误
#define INTR_GP 13  // 一般性保护异常
#define INTR_PF 14  // 缺页错误
#define INTR_RE1 15 // 保留
#define INTR_MF 16  // 浮点异常
#define INTR_AC 17  // 对齐检测
#define INTR_MC 18  // 机器检测
#define INTR_XM 19  // SIMD 浮点异常
#define INTR_VE 20  // 虚拟化异常
#define INTR_CP 21  // 控制保护异常

#define IRQ_CLOCK 0      // 时钟
#define IRQ_KEYBOARD 1   // 键盘
#define IRQ_CASCADE 2    // 8259 从片控制器
#define IRQ_SERIAL_2 3   // 串口 2
#define IRQ_SERIAL_1 4   // 串口 1
#define IRQ_PARALLEL_2 5 // 并口 2
#define IRQ_SB16 5       // SB16 声卡
#define IRQ_FLOPPY 6     // 软盘控制器
#define IRQ_PARALLEL_1 7 // 并口 1
#define IRQ_RTC 8        // 实时时钟
#define IRQ_REDIRECT 9   // 重定向 IRQ2
#define IRQ_NIC 11       // 网卡
#define IRQ_MOUSE 12     // 鼠标
#define IRQ_MATH 13      // 协处理器 x87
#define IRQ_HARDDISK 14  // ATA 硬盘第一通道
#define IRQ_HARDDISK2 15 // ATA 硬盘第二通道

#define IRQ_MASTER_NR 0x20 // 主片起始向量号
#define IRQ_SLAVE_NR 0x28  // 从片起始向量号


struct idt_desc{
	u16 offset_low; // offset 0-15 bits 
	u16 selector;
	u8 zero;
	u8 type_attr;
	u16 offset_high; // offset 16-31 bits
} __attribute__((packed));

struct idtr_desc{
	u16 limit;
	u32 base;
} __attribute__((packed));


void idt_init();
void enable_interrupt();
void disable_interrupt();

bool interrupt_disable();
bool get_interrupt_state();
void set_interrupt_state(bool state);

void init_timer(unsigned int frequency);
#endif
