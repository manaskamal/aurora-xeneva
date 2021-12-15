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
	timer_t *t = (timer_t*)pmmngr_alloc();
	t->timer_count = 0;
	t->task_id = id;
	t->interval = interval;
	t->utimer_id = utimer_id;
	timer_insert (t);
	utimer_id++;
	return utimer_id;
}


/*
  destroy_timer -- Destroy a specific timer

  @param utimer_id -- Unique timer id to destroy
  */
void destroy_timer (int utimer_id) {
	for (timer_t *t = timer_head; t != NULL; t = t->next) {
		if (t->utimer_id = utimer_id) {
			timer_delete (t);
			break;
		}
	}
	utimer_id--;
}


/**
   timer_fire -- this routine is called by the scheduler
                 for monitoring time for threads.
				 
  */
void timer_fire () {
	if (timer_head != NULL) {
		for (timer_t *t = timer_head; t != NULL; t = t->next) {
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
