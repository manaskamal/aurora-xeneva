/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  systhread -- System thread callbacks
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#include <arch\x86_64\thread.h>
#include <proc.h>


uint16_t get_thread_id () {
	x64_cli ();
	return get_current_thread()->id;
}


void create_uthread (void (*entry) (void*), char* name) {

	/*
	 * Not implemented properly
	 *
	 * when syscalls occurs it causes page fault 
	 */
    thread_t *cthread = get_current_thread();
	uint64_t stack = (uint64_t)create_inc_stack((uint64_t*)cthread->cr3);
	uthread *uthr = (uthread*)pmmngr_alloc();
	uthr->entry = entry;
	uthr->self_pointer = uthr;
	thread_t * t = create_user_thread (entry, stack, cthread->cr3,name, 1);
}


void sys_sleep (uint64_t ms) {
	x64_cli();
	thread_t* t = get_current_thread();
	sleep_thread (t, ms);
	force_sched();
}
