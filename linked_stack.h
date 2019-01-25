/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* linked_stack_t.h cotains the function defenitions for a linked_list
* implementation of a stack
*
******************************************************************************/

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "linked_list.h"

typedef struct
{
	struct linked_list *head, *tail;
	int size;
} linked_stack_t;

linked_stack_t* init_linked_stack(void*);
void push(linked_stack_t*, void*);
void* pop(linked_stack_t*);
#endif