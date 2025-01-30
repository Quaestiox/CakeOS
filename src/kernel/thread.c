#include "thread.h"
#include "print.h"
#include "memory.h"
#include "kheap.h"
#include "config.h"
#include "string.h"
#include "idt.h"
#include "shell.h"

extern void switch_to(struct task_struct* cur, struct task_struct* next);

extern void program1();

struct task_struct* thread_list[MAX_THREAD];

struct task_struct* idle;

struct task_struct* running_task(){
	u32 esp;
	asm ("mov %%esp, %0": "=g" (esp));
	return (struct task_struct*)(esp & 0xfffff000);
}


static struct task_struct* get_free_task(){
	for(int i = 0; i < MAX_THREAD; i++){
		if(thread_list[i] == NULL){
			thread_list[i] = (struct task_struct*) kzalloc(PAGE_SIZE);
			return thread_list[i];
		}

	}
	print_string("no more free task");
	return NULL;
}

struct task_struct* task_create(thread_func function, char* name, u32 id, u8 prior){
	struct task_struct* task = get_free_task();
	u32 stack = (u32)task + PAGE_SIZE;
	stack -= sizeof(struct task_stack_frame);
	struct task_stack_frame* frame = (struct task_stack_frame*) stack;
	frame->ebp = frame->ebx = frame->edi = frame->esi = 0;
	frame->eip = (void *)function;
	strcpy(task->name,name);
	task->status = TASK_READY;
	task->id = id;
	task->priority = prior;
	task->clock = prior;
	task->run_clock = 0;
	task->magic = STACK_MAGIC;


	task->stack = (u32*)stack;

	print_string("task_create done!\n");
	return task;
}

struct task_struct* task_search(enum task_status status){
	struct task_struct* task = NULL;
	struct task_struct* current = running_task();

	for (int i = 0; i < MAX_THREAD; i++){
		struct task_struct* ptr = thread_list[i];

		if(ptr == NULL || ptr->status != status || ptr == current)
			continue;
	
		if(task == NULL || ptr->priority > task->priority || ptr->run_clock < task->run_clock)
			task = ptr;
	}	


	if(task == NULL && status == TASK_READY){
		task = idle;
	}

	return task;	

}


void schedule(){

	struct task_struct* current = running_task();
	struct task_struct* next = task_search(TASK_READY);

	if(!next){
		print_string("get next task failed\n");
	}

	if(next->magic != STACK_MAGIC){
		print_string("stack overflow\n");
		return;
	}


	if(current->status == TASK_RUNNING){
		current->status = TASK_READY;
	}
	next->status = TASK_RUNNING;

	switch_to(current,next);

}

void thread_1(void* arg){
	set_interrupt_state(true);

	while(1){

		print_char('1');
	}

	
}

void thread_2(void* arg){

	enable_interrupt();
	print_string("enter the second thread\n");

	while(1){
	}
}

void first_thread(void* arg){
	
	enable_interrupt();
	print_string("first thread\n");
	program1();
	shell_start();
}

void idle_thread(void* arg){
	enable_interrupt();

	while(1){

	}
}

void task_init(){
	struct task_struct* main = running_task();
	main->status = TASK_RUNNING;
	main->magic = STACK_MAGIC;
	main->clock = 1;
	main->priority = 1;

	memset(thread_list, 0, sizeof(thread_list));

	idle = task_create(idle_thread, "idle", 1, 1);
//	task_create(shell_start, "shell", 3, 10);
	task_create(first_thread, "first", 1, 10);
//	task_create(thread_2, "second", 2, 10);
}

