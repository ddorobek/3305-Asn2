/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* tokenize.h
*
******************************************************************************/


#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdlib.h>
#include <string.h>

#include "helper.h"
#include "linked_list.h"

void process_io_redirection_commands(short, char *, struct linked_list*,
	int, int, int);
struct linked_list* extract_command(char*, struct linked_list*, int, int*,
	short);
char*** tokenize(char*);

#define PIPE '|'
#define INPUT_REDIRECTION '<'
#define OUTPUT_REDIRECTION '>'

#define CMD_LENGTH 3

#define CAT_CMD 1
#define TEE_CMD 2
#define OUT_CMD 3

#endif