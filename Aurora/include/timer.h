/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  timer.h -- The Global Timer used by usermode objects
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

typedef struct _timer_ {
	uint32_t timer_count;
	uint32_t interval;
	uint16_t task_id;
	uint32_t utimer_id;
	bool start;
	struct _timer_ *next;
	struct _timer_ *prev;
}timer_t;


/*
  create_timer -- Creates a new timer

  @param interval -- the difference time
  @param id -- the caller thread id
  @return -- a unique id of the timer
  */
extern int create_timer (uint32_t interval, uint16_t id);


/*
  destroy_timer -- Destroy a specific timer

  @param utimer_id -- Unique timer id to destroy
  */
extern void destroy_timer (int utimer_id);

/*
  pause_timer -- pauses the timer
  @param utimer_id -- Unique timer id to pause
  */
extern void pause_timer (int utimer_id);

/*
  start_timer - start the timer

  @param utimer_id -- Unique timer id to start
  */
extern void start_timer (int utimer_id);


/**
   timer_fire -- this routine is called by the scheduler
                 for monitoring time for threads.
				 
  */
extern void timer_fire ();


/*
 find_timer_id -- find a timer by a given task id
 @param id -- task id
 @return -- unique timer id of the timer, if found
 */
extern int find_timer_id (uint16_t id);

#endif