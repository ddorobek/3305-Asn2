/******************************************************************************
* Author: Damien Dorobek (250907609)
* Email: ddorobek@uwo.ca
* Date: November 2, 2018
*
******************************************************************************/

#include "simulate.h"

int memory, max_memory;
FILE *fp;
linked_stack_t *jobs;

void simulate(int memory_value, linked_stack_t *stack)
{
	pthread_t threads[NUMBER_OF_THREADS];
	jobs = stack;
	max_memory = memory_value;
	memory = memory_value;
	fp = fopen(SYSTEM_OUTPUT,"w"); //Open fp for printing statements.
	
	//While there are still jobs in the stack, this code is executed.
	while(jobs->size != 0) {
		int i = 0; //Set thread counter to 0.
		
		//While there are still jobs to be added to the threads array (up to 4), this code is executed.
		while(i < NUMBER_OF_THREADS) {
			if(jobs->size == 0) {
				break; //If there are no more jobs to create threads for (stack is empty), break out of this loop.
			} 
			
			//Create a thread for the job being popped off the jobs stack and increment thread counter (i).
			if(pthread_create(&threads[i++], NULL, process_job, pop(jobs))) {
				printf("Error while creating thread.\n"); //If the thread cannot be created, an error is printed and the program exits.
				exit(1);
			}
		}
		
		//Join each thread in the threads array (up to 4).
		for(int j=0; j<i; j++) {
			pthread_join(threads[j], NULL);				
		}
	}
	
	fclose(fp);
}

void *process_job(void *poppedJob) {
	job_t *job = poppedJob; //Set job to job that was popped off jobs stack.
	
	//If the job's required memory exceeds the max memory, then statement is printed.
	if(job->required_memory > max_memory) {
		print_exceed_memory(fp, job->number);
	}
	
	//If there is enough memory to start the job, the following code is executed.
	else if(job->required_memory < memory){
		print_starting(fp, job->number);
		
		memory -= job->required_memory; //Allocates memory for job.
		print_allocate_memory(fp, memory, job->required_memory); 
		
		sleep(job->required_time); //Sleeps for job's required time.
		print_completed(fp, job->number); 
		
		memory += job->required_memory; //Deallocates memory for job.
		print_deallocate_memory(fp, memory, job->required_memory); 
	} 
	
	//If there is not enough memory to start the job, a statement is printed and the job gets pushed back onto the jobs stack.
	else {
		print_insufficient_memory(fp, job->number);
		push(jobs, (void*)job);
	}
}