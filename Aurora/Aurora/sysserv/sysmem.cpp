/**
 **  Copyright (C) Manas Kamal Choudhury 2021
 **
 **  sysmem.cpp -- System Memory Callbacks
 **
 **  /PORJECT - Aurora {Xeneva}
 **  /AUTHOR  - Manas Kamal Choudhury
 **
 **/

#ifdef ARCH_X64
#include <arch\x86_64\mmngr\vmmngr.h>
#include <arch\x86_64\thread.h>
#include <_null.h>
#include <serial.h>
#include <stdio.h>
#endif


void map_shared_memory (uint16_t dest_id,uint64_t pos, size_t size) {
	x64_cli ();

	thread_t* t = thread_iterate_ready_list (dest_id);
	if (t == NULL) {
		t = thread_iterate_block_list(dest_id);
	}
	uint64_t *current_cr3 = (uint64_t*)get_current_thread()->cr3;
	uint64_t *cr3 = (uint64_t*)t->cr3;

	for (int i = 0; i < size/4096; i++) {
	   if (map_page ((uint64_t)pmmngr_alloc(),pos + i * 4096, PAGING_USER)) {
		   cr3[pml4_index(pos + i * 4096)] = current_cr3[pml4_index(pos + i * 4096)];
	   }
	}
}

void copy_memory (uint16_t dest_id, uint64_t pos, size_t size) {
	x64_cli();
	thread_t* t = thread_iterate_ready_list (dest_id);
	if (t == NULL) {
		t = thread_iterate_block_list(dest_id);
	}
	uint64_t *current_cr3 = (uint64_t*)get_current_thread()->cr3;
	uint64_t *cr3 = (uint64_t*)t->cr3;

	for (int i = 0; i < size/4096; i++) {
		cr3[pml4_index(pos + i * 4096)] = current_cr3[pml4_index(pos + i * 4096)];
	}
}

void unmap_shared_memory (uint16_t dest_id, uint64_t pos, size_t size) {
	x64_cli ();

	thread_t* t = thread_iterate_ready_list (dest_id);
	if (t == NULL) {
		t = thread_iterate_block_list(dest_id);
	}
	uint64_t *cr3 = (uint64_t*)t->cr3;

	for (int i = 0; i < size/4096; i++) {
		unmap_page (pos + i * 4096);
		//unmap_page_ex(cr3,pos + i * 4096, false);
	}
}


uint64_t sys_get_used_ram () {
	x64_cli ();
	return pmmngr_get_used_ram ();
}

uint64_t sys_get_free_ram () {
	x64_cli ();
	return pmmngr_get_free_ram ();
}