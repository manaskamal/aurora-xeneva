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
	uint64_t *cr3 = create_user_address_space();
	uthread *uthr = (uthread*)pmmngr_alloc();
	uthr->entry = entry;
	uthr->self_pointer = uthr;
	x64_write_msr (0xC0000100, (uint64_t)uthr->self_pointer);
	//printf ("FS Base written\n");
	//thread_t * t = create_user_thread (uthr->entry,0x0000000080000000 + 4096, (size_t)cr3, "uthread", 1);
}


void sys_sleep (uint64_t ms) {
	x64_cli();
	thread_t* t = get_current_thread();
	sleep_thread (t, ms);
	force_sched();
}
