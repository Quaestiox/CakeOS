#include "thread.h"
#include "print.h"
#include "memory.h"
#include "kheap.h"
#include "config.h"
#include "string.h"
#include "idt.h"

struct task_struct* main_thread;
struct link_list thread_ready_list;
struct link_list thread_all_list;
static struct link_list_node* thread_node;

extern void switch_to(struct task_struct* cur, struct task_struct* next);

struct task_struct* running_thread(){
	u32 esp;
	asm ("mov %%esp, %0": "=g" (esp));
	return (struct task_struct*)(esp & 0xfffff000);
}

static void kernel_thread(thread_func* function, void* func_arg){
	enable_interrupt();
	function(func_arg);
}

void init_thread(struct task_struct* task, char* name, int prior){
	memset(task, 0,sizeof(*task));

	strcpy(task->name,name);
	if(task == main_thread){
		task->status = TASK_RUNNING;
	} else{
		task->status = TASK_READY;
	}
	task->status = TASK_RUNNING;
	task->priority = prior;
	task->kstack = (u32*)((u32)task + PAGE_SIZE);
	task->clock = prior;
	task->run_clock = 0;
	task->pgdir = NULL;
	task->stack_magic = STACK_MAGIC;
}

void thread_create(struct task_struct* task, thread_func function, void* func_arg){
	task->kstack -= sizeof(struct registers);
	task->kstack -= sizeof(struct thread_stack);
	struct thread_stack* kstack = (struct thread_stack*)task->kstack;
	kstack->eip = kernel_thread;
	kstack->function = function;
	kstack->func_arg = func_arg;
	kstack->esi = kstack->ebx = kstack->ebp = kstack->edi = 0;

}

struct task_struct* thread_start(thread_func function, void* func_arg, char* name, int prior){
	struct task_struct* thread = kzalloc(PAGE_SIZE);
	init_thread(thread, name, prior);
	thread_create(thread, function, func_arg);

	if(link_list_find(&thread_ready_list, &thread->ready_node)){
		print_string("thread should not exist in the ready_list");
		return NULL;
	}
	link_list_append(&thread_ready_list, &thread->ready_node);

	if(link_list_find(&thread_all_list, &thread->all_node)){
		print_string("thread should not exist in the all_list");
		return NULL;
	}
	link_list_append(&thread_all_list, &thread->all_node);


/*
	asm volatile ("movl %0, %%esp; \
		pop	%%ebp; \
		pop %%ebx; \
		pop %%edi; \
		pop %%esi; \
		ret": : "g"(thread->kstack):"memory");
*/
	return thread;
}

static void set_main_thread(void){
	main_thread = running_thread();
	init_thread(main_thread, "main", 31);

	if(link_list_find(&thread_all_list, &thread->all_node)){
		print_string("thread should not exist in the all_list");
		return NULL;
	}
	link_list_append(&thread_all_list, &thread->all_node);


}

void schedule(){
	disable_interrupt();

	struct task_struct* current = running_thread();
	if(current->status == TASK_RUNNING){
		if(link_list_find(&thread_ready_list, &current->ready_node)){
			print_string("schedule error!");
			return;
		}
		link_list_append(&thread_ready_list, &current->ready_node);
		current->clock = current->priority;
		current->status = TASK_READY;
	}else{

	}

	if(list_empty(&thread_ready_list)){
		print_string("schedule error!");
		return;
	}
	thread_node = NULL;
	thread_node = list_pop(&thread_ready_list);

}
