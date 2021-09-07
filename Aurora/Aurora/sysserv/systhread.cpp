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


void create_uthread (void (*entry) (void*)) {

	/*
	 * Not implemented properly
	 *
	 * when syscalls occurs it causes page fault 
	 */

	for (int i = 0; i < 0x100000/ 4096; i++)
		map_page((uint64_t)pmmngr_alloc(), 0x0000000080000000 + i * 4096);

	thread_t *cthread = get_current_thread();
	uthread *uthr = (uthread*)pmmngr_alloc();
	uthr->entry = entry;
	uthr->self_pointer = uthr;
	thread_t * t = create_user_thread (entry, (uint64_t)pmmngr_alloc() + 4096, cthread->cr3, "uthread", 1);
}


void sys_sleep (uint64_t ms) {
	x64_cli();
	thread_t* t = get_current_thread();
	sleep_thread (t, ms);
	force_sched();
}
