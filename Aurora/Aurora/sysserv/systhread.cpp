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
	x64_cli();
	/*
	 * Not implemented properly
	 *
	 * TODO: Update the process structure and add an
	 * entry for the new user thread!!
	 */  
	uint64_t *old_cr3 = (uint64_t*)p2v(x64_read_cr3());
	uint64_t* new_cr3 = (uint64_t*)AuCreateAddressSpace();
	


	//uint64_t stack = (uint64_t)p2v((size_t)AuPmmngrAlloc()); //create_inc_stack(old_cr3);


	/* Create the new user thread */
	//thread_t * t = create_user_thread(entry,stack + 4096,(uint64_t)new_cr3,name,1);
	return;
}


void sys_sleep (uint64_t ms) {
	x64_cli();
	thread_t* t = get_current_thread();
	sleep_thread (t, ms);
	force_sched();
}
