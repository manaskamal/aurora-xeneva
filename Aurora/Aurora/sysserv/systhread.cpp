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

uint16_t get_thread_id () {
	x64_cli ();
	return get_current_thread()->id;
}


void create_uthread (void (*entry) (void*)) {
	x64_cli ();
	create_user_thread (entry,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"uthread",1);
}


void sys_sleep (uint64_t ms) {
	x64_cli();
	thread_t* t = get_current_thread();
	sleep_thread (t, ms);
	force_sched();
}
