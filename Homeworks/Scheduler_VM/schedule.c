/* schedule.c
 * This file contains the primary logic for the 
 * scheduler.
 */

#include "privatestructs.h"
#include "schedule.h"
#include "macros.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define NEWTASKSLICE (NS_TO_JIFFIES(1000000000))
#define A 0.5

struct task_struct *sjf_sched();


/* Local Globals
 * rq - This is a pointer to the runqueue that the scheduler uses.
 * current - A pointer to the current running task.
 */
struct runqueue *rq;
struct task_struct *current;

/* External Globals
 * jiffies - A discrete unit of time used for scheduling.
 *			 There are HZ jiffies in a second, (HZ is
 *			 declared in macros.h), and is usually
 *			 1 or 10 milliseconds.
 */
extern long long jiffies;
extern struct task_struct *idle;

/*-----------------Initilization/Shutdown Code-------------------*/
/* This code is not used by the scheduler, but by the virtual machine
 * to setup and destroy the scheduler cleanly.
 */
 
 /* initscheduler
  * Sets up and allocates memory for the scheduler, as well
  * as sets initial values. This function should also
  * set the initial effective priority for the "seed" task 
  * and enqueu it in the scheduler.
  * INPUT:
  * newrq - A pointer to an allocated rq to assign to your
  *			local rq.
  * seedTask - A pointer to a task to seed the scheduler and start
  * the simulation.
  */
void initschedule(struct runqueue *newrq, struct task_struct *seedTask){
	seedTask->next = seedTask->prev = seedTask;
	newrq->head = seedTask;
	newrq->nr_running++;
}

/* killschedule
 * This function should free any memory that 
 * was allocated when setting up the runqueu.
 * It SHOULD NOT free the runqueue itself.
 */
void killschedule(){
	return;
}


void print_rq () {
	struct task_struct *curr;
	int i = 0;

	printf("Rq: \n");
	curr = rq->head;
	if (curr){
			// printf("%s", curr->threadinfo->processName);

			printf("%s, (slice: %d, exp: %.2lf, burst: %.2lf got_cpu: %lld, lost_cpu: %lld)\n", curr->thread_info->processName, curr->time_slice, curr->expected_burst, curr->burst, curr->got_cpu, curr->lost_cpu);
			// printf("%p", curr);
		}
	
	i++;

	while(curr->next != rq->head){
		curr = curr->next;
		// printf(", %s ", curr->threadinfo->processName);
		// printf(", %p ", curr);
		printf("%s, (slice: %d, exp: %.2lf, burst: %.2lf got_cpu: %lld, lost_cpu: %lld)\n", curr->thread_info->processName, curr->time_slice, curr->expected_burst, curr->burst, curr->got_cpu, curr->lost_cpu);

		i++;
	};
	
	printf("\n");
}

/*-------------Scheduler Code Goes Below------------*/
/* This is the beginning of the actual scheduling logic */

/* schedule
 * Gets the next task in the queue
 */
void schedule(){
	static struct task_struct *nxt = NULL; //[IMPORTANT]: STATIC VARIABLE REMAINS IN MEMORY
	// struct task_struct *curr;
	
	current->need_reschedule = 0; /* Always make sure to reset that, in case *
								   * we entered the scheduler because current*
								   * had requested so by setting this flag   */

	// burst info needs to be updated because newer data exist for the current process
	// calculate burst info for the current process before initiating the scheduling process 
	current->lost_cpu = sched_clock();
	current->burst = current->lost_cpu - current->got_cpu;
	current->expected_burst = (current->burst + A * current->expected_burst) / (1 + A);

	printf("In schedule\n");
	print_rq();	

	//-> init ->
	if (rq->nr_running == 1) {
		context_switch(rq->head);
		nxt = rq->head->next;
	}
	else {
		
		nxt = sjf_sched();

		// curr = nxt;
		//nxt = nxt->next;

		//************************* OUR SCHEDULER *************************//


		//init -> papakia -> vatraxakia nr = 3
		// if (nxt == rq->head)    /* Do this to always skip init at the head 	*/
		// 	nxt = nxt->next;			/* of the queue, whenever there are other  	*/
		// 												/* processes available					   					*/
		
		context_switch(nxt);

	}
	
	current->got_cpu = sched_clock();
	printf("\033[0;32m\nLost CPU: %lld\nGot CPU: %lld\n\n\033[0m", current->lost_cpu, current->got_cpu);
}


/* sched_fork
 * Sets up schedule info for a newly forked task
 */
void sched_fork(struct task_struct *p){
	p->time_slice = rand() % 100;
	p->got_cpu = 0;
	p->lost_cpu = 0;
	p->burst = 0;
	p->goodness = 0;
	p->expected_burst = 0;
	p->last_time_rq = sched_clock();
}

/* scheduler_tick
 * Updates information and priority
 * for the task that is currently running.
 */
void scheduler_tick(struct task_struct *p){
	schedule();
}

/* wake_up_new_task
 * Prepares information for a task
 * that is waking up for the first time
 * (being created).
 */
void wake_up_new_task(struct task_struct *p){	
	p->next = rq->head->next;
	p->prev = rq->head;
	p->next->prev = p;
	p->prev->next = p;
	
	rq->nr_running++;

	p->last_time_rq = sched_clock();
}

/* activate_task
 * Activates a task that is being woken-up
 * from sleeping.
 */
void activate_task(struct task_struct *p){
	p->next = rq->head->next;
	p->prev = rq->head;
	p->next->prev = p;
	p->prev->next = p;
	
	rq->nr_running++;

	// update lost_cpu based on what happened last (cpu change or rq insertion)
	p->lost_cpu = p->lost_cpu > p->last_time_rq ? p->lost_cpu : p->last_time_rq; 
	
	// lost_cpu is updated => update burst and expected_burst  
	p->burst = p->lost_cpu - p->got_cpu;
	p->expected_burst = (p->burst + A * p->expected_burst) / (1 + A);

	// got in rq => update last_time_rq
	p->last_time_rq = sched_clock();
}

/* deactivate_task
 * Removes a running task from the scheduler to
 * put it to sleep.
 */
void deactivate_task(struct task_struct *p){
	p->prev->next = p->next;
	p->next->prev = p->prev;
	p->next = p->prev = NULL; /* Make sure to set them to NULL *
							   * next is checked in cpu.c      */

	rq->nr_running--;

	// Interactive Process Lost CPU
	p->lost_cpu = sched_clock();
	p->burst = p->lost_cpu - p->got_cpu;
	p->expected_burst = (p->burst + A * p->expected_burst) / (1 + A);
}

// returns a pointer to maximum_waiting_rq_time, if GOODNESS is defined, else to minimum_exp_burst_time
struct task_struct *sjf_sched(){
	int i;
	struct task_struct *curr;
	struct task_struct *process_info;
	double minimum_exp_burst_time = __DBL_MAX__;
	double maximum_waiting_rq_time = -__DBL_MAX__;
	
	for(i = 0, curr = rq->head; i < rq->nr_running; curr = curr->next, i++){
		if(curr == rq->head){
				continue;
			}
			#ifdef GOODNESS
				if (curr->goodness > maximum_waiting_rq_time){
					maximum_waiting_rq_time = curr->goodness;
					process_info = curr;
				}

			#else
				if (curr->expected_burst < minimum_exp_burst_time){
					minimum_exp_burst_time = curr->expected_burst;
					process_info = curr; 
				}
			#endif
	}

	return process_info;
}

double goodness(){

}