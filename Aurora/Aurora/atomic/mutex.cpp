/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @mutex.h -- atomic mutex lock 
 *
 **/

#include <atomic\mutex.h>

//! for Debugging purpose
#include <stdio.h>

//! Creates a new mutex object
AU_EXTERN AU_EXPORT mutex_t * AuMutexCreate () {
	mutex_t * obj = (mutex_t*)malloc(sizeof(mutex_t));
	obj->blocks = 0;
	obj->owner_thread= 0;
	obj->block_thread_num = 0;
	return obj;
}


//! Locks a critical section from other process
AU_EXTERN AU_EXPORT void AuMutexLock (mutex_t * obj) {
	//! check
	if (get_current_thread() == NULL)
		return;

	if (obj->blocks != 0 && obj->owner_thread == get_current_thread()) {
		obj->blocks++;
		return;
	}
	

	while (obj->blocks != 0) {
		block_thread(get_current_thread());
		obj->block_thread_id[obj->block_thread_num] = get_current_thread()->id;
		obj->block_thread_num++;
		force_sched();
	}
	
	obj->blocks = 1;
	obj->owner_thread = get_current_thread();
}


//! Unlock a mutex and allow the blocked task to 
//! access the critical section
//! BUGGY: FIXME
AU_EXTERN AU_EXPORT void AuMutexUnlock (mutex_t *obj) {

	if (get_current_thread() == NULL)
		return;


	if (obj->blocks <= 0) 
		return;

	
	if (obj->blocks == 1) {
		for (int i = 0; i < obj->block_thread_num; i++){
			uint16_t id = obj->block_thread_id[obj->block_thread_num];
			thread_t * thr = thread_iterate_block_list (id);
			if (thr != NULL)
				unblock_thread(thr);
		}
		obj->block_thread_num = 0;
		obj->owner_thread = NULL;
		return;
	}

	//! decreament the block count
	obj->blocks--;
}


/*
 * AuMutexDestroy -- Destroy the pointed mutex
 * @param obj -- Pointer to mutex
 */
AU_EXTERN AU_EXPORT void AuMutexDestroy (mutex_t *obj) {
	free(obj);
}

	
