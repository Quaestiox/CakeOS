#ifndef LIST_H
#define LIST_H

#include "type.h"

struct link_list_node{
	struct link_list_node* prev;
	struct link_list_node* next;
};

struct link_list{
	struct link_list_node head;
	struct link_list_node tail;
};


bool link_list_empty(struct link_list* list);
u32 link_list_len(struct link_list* list);
bool link_list_find(struct link_list* list,struct link_list_node* target_node);
struct link_list_node* list_pop(struct link_list* list);
void link_list_remove(struct link_list_node* node);
void list_append(struct link_list* list, struct link_list_node* node);
void link_list_push(struct link_list* list, struct link_list_node* node);
void link_list_insert_bf(struct link_list_node* before , struct link_list_node* node);
void link_list_init(struct link_list* list);
#endif
