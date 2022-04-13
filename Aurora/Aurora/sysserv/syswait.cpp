/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  syswait.h -- puts a thread on waitlist
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#ifdef ARCH_X64
#include <arch\x86_64\mmngr\vmmngr.h>
#include <arch\x86_64\thread.h>
#include <stdio.h>
#include <arch\x86_64\user64.h>
#include <atomic\mutex.h>
#endif

void wait () {
	x64_cli();
	thread_t *t = get_current_thread ();
	block_thread (t);
	force_sched();
}

void sys_unblock_id (uint16_t id) {
	x64_cli();
	thread_t* thr = (thread_t*)thread_iterate_block_list (id);
	if (thr != NULL){
		if (thr->state == THREAD_STATE_BLOCKED) {
			unblock_thread(thr);
		}
	}
}


