/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* simulator.c 
*
******************************************************************************/

#include "simulator.h"

/******************************************************************************
* 
******************************************************************************/
void simulator(char *filename)
{
	FILE *fp = fopen(SYSTEM_SPECS, READ);
	int memory;

	/**************************************************************************
	* check if the system file is in the directory
	**************************************************************************/
	if (fp == NULL)
	{
		printf("Unable to open %s file\n", SYSTEM_SPECS);
		exit(FAILURE);
	}
	/**************************************************************************
	* set the main memory value to the value read from the system file
	**************************************************************************/
	fscanf(fp, "%d", &memory);
	fclose(fp);

	linked_stack_t *jobs = build_jobs_stack(filename);
	job_t *p;

	simulate(memory, jobs);
}

/******************************************************************************
* Scans input file and builds a stack of jobs
******************************************************************************/
linked_stack_t* build_jobs_stack(char *filename) {

	FILE *fp = fopen(filename, READ);

	/**************************************************************************
	* check if the input file exists
	**************************************************************************/
	if (fp == NULL)
	{
		printf("Unable to open %s file\n", filename);
		exit(FAILURE);
	}

	int number, memory, time, len;
	linked_stack_t *s;

	/**************************************************************************
	* load all simulation jobs into the jobs stack
	**************************************************************************/
	if (fscanf(fp, "%d %d %d", &number, &memory, &time) == 3)
		s = init_linked_stack((void*)init_job(number, memory, time));

	while(fscanf(fp, "%d %d %d", &number, &memory, &time) == 3)
		push(s, (void*)init_job(number, memory, time));

	fclose(fp);

	return s;
}
