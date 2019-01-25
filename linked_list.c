/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* linked_list.c contins helper functions for the linked_list struct
*
******************************************************************************/

#include "linked_list.h"

struct linked_list* init_linked_list()
{
	struct linked_list* node = (struct linked_list*)
		malloc(sizeof(struct linked_list));
	node->next = NULL;
	return node;
}
