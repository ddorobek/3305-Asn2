/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* simulator.h
*
******************************************************************************/

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>

#include "simulate.h"
#include "job.h"
#include "linked_stack.h"
#include "helper.h"

#define SYSTEM_SPECS "system.in"

void simulator(char*);
linked_stack_t* build_jobs_stack(char*);

#endif