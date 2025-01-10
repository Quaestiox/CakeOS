#include "list.h"
#include "idt.h"

void link_list_init(struct link_list* list){
	list->head.prev = NULL;
	list->head.next = &list->tail;
	list->tail.prev = &list->head;
	list->tail.next = NULL;
}

void link_list_insert_bf(struct link_list_node* before , struct link_list_node* node){
	disable_interrupt();

	before->prev->next = node;
	node->prev = before->prev;
	node->next = before;
	before->prev = node;
	
	enable_interrupt();
}

void link_list_push(struct link_list* list, struct link_list_node* node){
	link_list_insert_bf(list->head.next, node);
}

void link_list_append(struct link_list* list, struct link_list_node* node){
	link_list_insert_bf(&list->tail, node);
}

void link_list_remove(struct link_list_node* node){
	disable_interrupt();

	node->prev->next = node->next;
	node->next->prev = node->prev;

	enable_interrupt();	
}

struct link_list_node* list_pop(struct link_list* list){
	struct link_list_node* node = list->head.next;
	link_list_remove(node);
	return node;
}

bool link_list_find(struct link_list* list,struct link_list_node* target_node){
	struct link_list_node* node = list->head.next;
	while(node != &list->tail){
		if (node == target_node){
			return true;
		}

		node = node->next;
	}
	return false;
}

u32 link_list_len(struct link_list* list){
	struct link_list_node* node = list->head.next;
	u32 len = 0;
	while(node != &list->tail){
		len++;
		node = node->next;
	}
	return len;
}

bool link_list_empty(struct link_list* list){
	return (list->head.next == &list->tail ? true : false);
}
