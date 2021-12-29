/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  timer.h -- The Global Timer used by usermode objects
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */


#include <timer.h>
#include <_null.h>
#include <pmmngr.h>
#include <stdio.h>
#include <arch\x86_64\cpu.h>
#include <ipc\postbox.h>

timer_t *timer_head = NULL;
timer_t *timer_last = NULL;
uint32_t utimer_id = 0;

void timer_insert (timer_t* new_timer ) {
	new_timer->next = NULL;
	new_timer->prev = NULL;

	if (timer_head == NULL) {
		timer_last = new_timer;
		timer_head = new_timer;
	} else {
		timer_last->next = new_timer;
		new_timer->prev = timer_last;
	}
	timer_last = new_timer;
}


void timer_delete (timer_t* new_timer) {

	if (timer_head == NULL)
		return;

	if (new_timer == timer_head) {
		timer_head = timer_head->next;
	} else {
		new_timer->prev->next = new_timer->next;
	}

	if (new_timer == timer_last) {
		timer_last = new_timer->prev;
	} else {
		new_timer->next->prev = new_timer->prev;
	}
	pmmngr_free(new_timer);
}


/*
  create_timer -- Creates a new timer

  @param interval -- the difference time
  @param id -- the caller thread id
  @return -- a unique id of the timer
  */
int create_timer (uint32_t interval, uint16_t id) {	
	utimer_id++;
	timer_t *t = (timer_t*)pmmngr_alloc();
	t->timer_count = 0;
	t->task_id = id;
	t->interval = interval;
	t->utimer_id = utimer_id;
	t->start = false;
	timer_insert (t);
	return utimer_id;
}


/*
  pause_timer -- pauses the timer
  @param utimer_id -- Unique timer id to pause
  */
void pause_timer (int utimer_id) {
	for (timer_t *t = timer_head; t != NULL; t = t->next) {
		if (t->utimer_id == utimer_id) {
			t->start = false;
			break;
		}
	}
}


/*
  start_timer - start the timer

  @param utimer_id -- Unique timer id to start
  */
void start_timer (int utimer_id ) {
	for (timer_t *t = timer_head; t != NULL; t = t->next) {
		if (t->utimer_id == utimer_id) {
			t->start = true;
			break;
		}
	}
}

/*
  destroy_timer -- Destroy a specific timer

  @param utimer_id -- Unique timer id to destroy
  */
void destroy_timer (int utimer_id) {
	for (timer_t *t = timer_head; t != NULL; t = t->next) {
		if (t->utimer_id == utimer_id) {
			timer_delete (t);
			utimer_id--;
			break;
		}
	}
	
}

/*
 find_timer_id -- find a timer by a given task id
 @param id -- task id
 @return -- unique timer id of the timer, if found
 */
int find_timer_id (uint16_t id) {
	for (timer_t *t = timer_head; t != NULL; t = t->next) {
		if (t->task_id == id) {
			return t->utimer_id;
			break;
		}
	}

	return -1;
}


/**
   timer_fire -- this routine is called by the scheduler
                 for monitoring time for threads.
				 
  */
void timer_fire () {
	x64_cli();
	if (timer_head != NULL) {
		for (timer_t *t = timer_head; t != NULL; t = t->next) {
			if (t->start) {
				if (t->timer_count == t->interval ) {
					postmsg_t msg;
			        msg.type = SYSTEM_MESSAGE_TIMER_EVENT;
			        msg.to_id = t->task_id;
			        post_box_put_msg (&msg,t->task_id);
			        t->timer_count = 0;
		         }
			     t->timer_count++;
			}
		}
	}
}
