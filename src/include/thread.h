#ifndef THREAD_H
#define THREAD_H

typedef void thread_func(void*);

enum task_status{
	TASK_RUNNING,
	TASK_READY,
	TASK_BLOCKED,
	TASK_WAITING,
	TASK_HANGLING,
	TASK_DIED
};

struct task_pcb{
	u32* stack;
	enum task_status status;
	u8 priority;
	char name[16];
	u32 magic;
};

#endif
