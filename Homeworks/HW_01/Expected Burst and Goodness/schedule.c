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

#define GOODNESS
#define DEBUG

struct task_struct *sjf_sched();
struct task_struct *min_exp();
struct task_struct *min_goodness();
struct task_struct *max_waiting_rq();
double process_goodness(struct task_struct *process);

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

struct task_struct *min_exp_node = NULL;
struct task_struct *max_waiting_rq_node = NULL;
unsigned long long cpu_clock_till_comletion = 0;
int num_of_processes = 0;
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

	// initialize min_exp_node max_waiting_rq_node to list head (init)
	min_exp_node = newrq->head;
	max_waiting_rq_node = newrq->head;
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

	printf("\033[0;32mCurrent State of Run Queue: %ld\n\033[0m", rq->nr_running);
	curr = rq->head;
	if (curr){
			printf("%s, (goodness: %f, exp: %.2lf, waiting_in_rq: %lld, burst: %.2lf got_cpu: %lld, lost_cpu: %lld)\n", curr->thread_info->processName, curr->goodness, curr->expected_burst, sched_clock() - curr->last_time_rq, curr->burst, curr->got_cpu, curr->lost_cpu);
		}
	
	i++;

	while(curr->next != rq->head){
		curr = curr->next;
		printf("%s, (goodness: %lf, exp: %.2lf, waiting_in_rq: %lld, burst: %.2lf, got_cpu: %lld, lost_cpu: %lld)\n", curr->thread_info->processName, curr->goodness, curr->expected_burst, sched_clock() - curr->last_time_rq, curr->burst, curr->got_cpu, curr->lost_cpu);

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
	struct task_struct *nxt = NULL; //[IMPORTANT]: STATIC VARIABLE REMAINS IN MEMORY
	
	unsigned long long temp_lost_cpu;

	current->need_reschedule = 0; /* Always make sure to reset that, in case *
								   * we entered the scheduler because current*
								   * had requested so by setting this flag   */

	// burst info needs to be updated because newer data exist for the current process
	// calculate burst info for the current process before initiating the scheduling process 
	
	// Temp lost cpu variable to calculate the current burst //
	temp_lost_cpu = sched_clock();
	current->expected_burst = (current->burst + A * current->expected_burst) / (1 + A);
	current->burst = temp_lost_cpu - current->got_cpu;

	#ifdef GOODNESS 
		struct task_struct *curr;
		// calculate min exp_burst and max goodness
		min_exp_node = min_exp();
		max_waiting_rq_node = max_waiting_rq();

		// recalculate goodness of nodes
		#ifdef DEBUG
			if(rq->nr_running != 1)
				printf("\033[0;33mGoodness Table\n\033[0m");
		#endif
		for(curr = rq->head->next; curr != rq->head; curr = curr->next){	
			curr->goodness = process_goodness(curr);
		}
		printf("\n");
	#endif

	// -> init ->
	if (rq->nr_running == 1) {
		#ifdef DEBUG
			print_rq();
			printf("\033[0;31mSwitching from %s to %s\033[0m\n\n", rq->head->thread_info->processName, rq->head->thread_info->processName);
		#else
			printf("\033[0;36mSwitching from %s to %ss\033[0m\n\n", rq->head->thread_info->processName, rq->head->thread_info->processName);
		#endif
		
		context_switch(rq->head);
		nxt = rq->head->next;
	}
	else {
		// find next process to switch to based on either goodness or exp_burst
		nxt = sjf_sched();
		
		// Updating lost_cpu only when the process loses the cpu //
		if (nxt != current){
			current->lost_cpu = temp_lost_cpu;
			current->burst = current->lost_cpu - current->got_cpu;
			nxt->got_cpu = sched_clock();
		}
		
		#ifdef DEBUG
			print_rq();
			printf("\033[0;31mSwitching from %s to %s\033[0m\n\n", current->thread_info->processName, nxt->thread_info->processName);
		#else
			printf("\033[0;36mSwitching from %s to %s\033[0m\n\n", current->thread_info->processName, nxt->thread_info->processName);
		#endif
		
		context_switch(nxt);
	}
}


/* sched_fork
 * Sets up schedule info for a newly forked task
 */
void sched_fork(struct task_struct *p){
	p->time_slice = 100;
	p->got_cpu = 0;
	p->lost_cpu = 0;
	p->burst = 0;
	p->goodness = -1;
	p->expected_burst = min_exp_node->expected_burst;
	p->last_time_rq = sched_clock();
}

/* scheduler_tick
 * Updates information and priority
 * for the task that is currently running.
 */
void scheduler_tick(struct task_struct *p){
	schedule();
	// update timeslice
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
	p->time_till_completion = sched_clock();
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

	// got in rq => update last_time_rq
	p->last_time_rq = sched_clock();
}

/* deactivate_task
 * Removes a running task from the scheduler to
 * put it to sleep.
 */
void deactivate_task(struct task_struct *p){
	//struct task_struct *curr;
	//int min, max;

	p->prev->next = p->next;
	p->next->prev = p->prev;
	p->next = p->prev = NULL; /* Make sure to set them to NULL *
							   * next is checked in cpu.c      */

	rq->nr_running--;

	// Interactive Process Lost CPU
	p->lost_cpu = sched_clock();
	
	if (p->thread_info->kill == 1 && p->thread_info->children == 0){
		if(rq->nr_running != 0){
			cpu_clock_till_comletion += p->lost_cpu;
			p->time_till_completion = sched_clock() - p->time_till_completion; // from entering rq till finish
			num_of_processes++;
			fprintf(stderr, "Process %s completed on %lld, finished in %lld clock ticks, accumulated end time is %lld, number of finished processes %d\n", p->thread_info->processName, p->lost_cpu, p->time_till_completion, cpu_clock_till_comletion, num_of_processes);
		}
		else {
			fprintf(stderr, "Mean Time to completion: %lf\n", ((double) cpu_clock_till_comletion / (double) num_of_processes));
		}
	}
}

// returns a pointer to maximum_waiting_rq_time, if GOODNESS is defined, else to minimum_exp_burst_time
struct task_struct *sjf_sched(){
	
	#ifdef GOODNESS
		return min_goodness();
	#else
		return min_exp();
	#endif
}

struct task_struct *min_exp(){
	struct task_struct *curr;
	struct task_struct *process = NULL;
	double minimum_exp_burst_time = __DBL_MAX__;


	// loop through list without looking at init (head)
	for(curr = rq->head->next; curr != rq->head; curr = curr->next){
		
		if (curr->expected_burst < minimum_exp_burst_time){
			minimum_exp_burst_time = curr->expected_burst;
			process = curr; 
		}
	}

	if (rq->nr_running == 1) {
		process = rq->head;
	}

	return process;
}

struct task_struct *min_goodness(){
	struct task_struct *curr;
	struct task_struct *process = NULL;
	double min_goodness_time = __DBL_MAX__;


	for(curr = rq->head->next; curr != rq->head; curr = curr->next){
		
		if (curr->goodness < min_goodness_time){
			min_goodness_time = curr->goodness;
			process = curr; 
		}
	}

	if (rq->nr_running == 1) {
		process = rq->head;
	}

	return process;
}

// Finds the oldest process in the running queue. //  
struct task_struct *max_waiting_rq(){
	struct task_struct *curr;
	struct task_struct *process = NULL;
	double oldest_node_in_rq_time = __DBL_MAX__;

	

	//min(1 + Exp_Burst(m)i)
	for(curr = rq->head->next; curr != rq->head; curr = curr->next){
		
		// waiting_in_rq = sched_clock() - last_time_rq = min(last_time_rq)
		if(curr->last_time_rq < oldest_node_in_rq_time){
			oldest_node_in_rq_time = curr->last_time_rq;
			process = curr;
		}
	}

	if (rq->nr_running == 1) {
		process = rq->head;
	}

	return process;
}

double process_goodness(struct task_struct *process){
	double min_exp_burst, max_waiting_in_rq;
	unsigned long long curr_time;
	double result;
	max_waiting_in_rq = max_waiting_rq_node->last_time_rq;
	min_exp_burst = min_exp_node->expected_burst;

	curr_time = sched_clock();

	result = ((1 + process->expected_burst) / (1 + min_exp_burst)) / ((1 + (curr_time - max_waiting_in_rq)) / (1 + (curr_time - process->last_time_rq)));
	
	#ifdef DEBUG
		printf("[GOODNESS] of %s: (%f / %f) * (%f / %lld) = %f\n", process->thread_info->processName, 1 + process->expected_burst, 1 + min_exp_burst, 1 + (curr_time - max_waiting_in_rq), (1 + (curr_time - process->last_time_rq)), result);
	#endif
	
	return result;
}