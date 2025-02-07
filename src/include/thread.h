#ifndef THREAD_H
#define THREAD_H

#include "type.h"
#include "list.h"

typedef void thread_func(void*);

enum task_status{
	TASK_RUNNING,
	TASK_READY,
	TASK_BLOCKED,
	TASK_WAITING,
	TASK_HANGLING,
	TASK_DIED
};

struct registers{
	u32 edi;
	u32 esi;
	u32 ebp;
	u32 ebx;
	u32 edx;
	u32 ecx;
	u32 eax;
	
	u32 ip;
	u32 cs;
	u32 flags;
	u32 esp;
	u32 ss;
};

struct task_stack_frame{
	u32 ebp;
	u32 ebx;
	u32 edi;
	u32 esi;	
	void (*eip)(thread_func* func, void* func_arg);
};

struct task_struct{
	u32* stack;
	enum task_status status;
	char name[16];
	u32 id;
	u8 priority;

	u8 clock;
	u8 run_clock;
	u32 magic;
};


void schedule();
struct task_struct* running_task();

void task_init();
#endif
