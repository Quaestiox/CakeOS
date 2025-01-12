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

/*
struct thread_stack{
	u32 ebp;
	u32 ebx;
	u32 edi;
	u32 esi;
	
	void (*eip)(thread_func* func, void* func_arg);

	void (*unused_retaddr);
	thread_func* function;
	void* func_arg;
};
*/
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
//	struct link_list_node ready_node;
//	struct link_list_node all_node;
//	u32* dictionary;
	u32 magic;
};


//struct task_struct* thread_start(thread_func function, void* func_arg, char* name, int prior);
void schedule();
struct task_struct* running_task();

void task_init();
#endif
