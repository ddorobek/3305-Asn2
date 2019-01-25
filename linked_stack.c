/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* stack.c contins helper functions for a linked_list implementation of a stack
*
******************************************************************************/

#include "linked_stack.h"

linked_stack_t* init_linked_stack(void *v)
{
	linked_stack_t *s = (linked_stack_t*)malloc(sizeof(linked_stack_t));
	struct linked_list* head = (struct linked_list*)
		malloc(sizeof(struct linked_list));

	head->value = v;
	head->next = NULL;

	s->head = head;
	s->tail = head;
	s->size = 1;

	return s;
}

void push(linked_stack_t *s, void *v)
{
	struct linked_list* node = (struct linked_list*)
		malloc(sizeof(struct linked_list));

	node->value = v;
	node->next = NULL;

	s->tail->next = node;
	s->tail = node;

	if (s->size == 0) s->head = s->tail;

	s->size++;
}

void* pop(linked_stack_t *s)
{
	struct linked_list *node = s->head;
	void *v = s->head->value;

	s->size--;
	s->head = s->head->next;
	free(node);
	return v;
}
