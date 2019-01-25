/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* simulate.h
*
******************************************************************************/

#ifndef SIMULATE_H
#define SIMULATE_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "job.h"
#include "linked_stack.h"
#include "helper.h"

#define SYSTEM_OUTPUT "system.out"
#define NUMBER_OF_THREADS 4

void simulate(int, linked_stack_t*);
void *process_job(void*);

#endif