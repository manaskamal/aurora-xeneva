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
	x64_cli ();
	map_page((uint64_t)pmmngr_alloc(), 0x0000000080000000);
	printf ("Current cr3 value -> %x\n", x64_read_cr3());
	printf ("Current entry address -> %x\n", entry);
	thread_t * t = create_user_thread (entry,0x0000000080000000 + 4096, x64_read_cr3(), "uthread", 1);
}


void sys_sleep (uint64_t ms) {
	x64_cli();
	thread_t* t = get_current_thread();
	sleep_thread (t, ms);
	force_sched();
}
