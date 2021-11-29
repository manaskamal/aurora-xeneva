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
	 * when syscalls occurs it causes page fault 
	 */  
	uint64_t *old_cr3 = (uint64_t*)x64_read_cr3();

	uint64_t* cr3 = create_user_address_space();
	uint64_t stack = (uint64_t)create_inc_stack((uint64_t*)cr3);
	
	for (int i = 0; i < 10*1024*1024/4096; i++) {
		cr3[pml4_index(0x0000400000000000 + i * 4096)] = old_cr3[pml4_index(0x0000400000000000 + i * 4096)];
	}

	uint64_t pos = 0x0000030000000000;   //0x0000080000000000;
	for (int i = 0; i < 0xC01000 / 4096; i++) {
		cr3[pml4_index(0x0000030000000000 + i * 4096)] = old_cr3[pml4_index(0x0000030000000000 + i * 4096)];
	}


	thread_t * t = create_user_thread (entry, stack,(uint64_t)cr3,name, 1);	
	
	//force_sched();
}


void sys_sleep (uint64_t ms) {
	x64_cli();
	thread_t* t = get_current_thread();
	sleep_thread (t, ms);
	force_sched();
}
