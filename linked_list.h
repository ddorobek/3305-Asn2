/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* linked_list.h cotains the defenitions for the linked_list struct
*
******************************************************************************/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "stdlib.h"

struct linked_list
{
   	void *value;
   	struct linked_list *next;
};

struct linked_list* init_linked_list();

#endif