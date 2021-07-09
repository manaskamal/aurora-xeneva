/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  mutex.cpp -- Mutual Exclusion Lock for critical section programming
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==========================================================================
 */

#include <atomic\mutex.h>

//! for Debugging purpose
#include <stdio.h>

//! Creates a new mutex object
mutex_t * create_mutex () {
	mutex_t * obj = (mutex_t*)malloc(sizeof(mutex_t));
	obj->blocks = 0;
	obj->owner_thread= 0;
	obj->block_thread_num = 0;
	return obj;
}


//! Locks a critical section from other process
void mutex_lock (mutex_t * obj) {

	//!disable multi tasking
	set_multi_task_enable (false);

	//! check
	if (obj->blocks != 0 && obj->owner_thread == get_current_thread()) {
		obj->blocks++;
		set_multi_task_enable (true);
		return;
	}


	while (obj->blocks != 0) {
		block_thread(get_current_thread());
		obj->block_thread_num++;
		set_multi_task_enable (true);
		force_sched();
	}

	obj->blocks = 1;
	obj->owner_thread = get_current_thread();
	set_multi_task_enable (true);
}


//! Unlock a mutex and allow the blocked task to 
//! access the critical section
//! BUGGY: FIXME
void mutex_unlock (mutex_t *obj) {

	set_multi_task_enable (false);

	if (obj->blocks <= 0) {
		set_multi_task_enable (true);
		return;
	}

	if (obj->block_thread_num > 0) {
		//unblock_thread(1);
	}
	//! decreament the block count
	obj->blocks--;
	obj->owner_thread = 0;
	set_multi_task_enable (true);
}

	
