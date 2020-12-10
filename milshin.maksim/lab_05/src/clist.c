#include "clist.h"
#include <stdio.h>

void add_node (struct intrusive_list* list, struct intrusive_node* node) {
	if (list->head) {
		list->head->prev = node;
	}
	node->next = list->head;
	node->prev = NULL;
	list->head = node;
} 


void remove_node (struct intrusive_list* list, struct intrusive_node* node) {
	if (list->head == node) {
		list->head = node->next;
	}
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
}

int get_length(struct intrusive_list* list) {
	struct intrusive_node* cur_node = list->head;
	int len = 0;
	while (cur_node) {
		cur_node = cur_node->next;
		len++;	
	}
	return len;
}



void init_list(struct intrusive_list* list) {
	list->head = NULL;
}

void reverse_list(struct intrusive_list* list) {
  struct intrusive_node* cur_node = list->head;
  while (cur_node->next) {
    struct intrusive_node* next_node = cur_node->next;
    cur_node->next = cur_node->prev;
    cur_node->prev = next_node;
    cur_node = next_node;
  }
  cur_node->next = cur_node->prev;
  cur_node->prev = NULL;
  list->head = cur_node;
}
