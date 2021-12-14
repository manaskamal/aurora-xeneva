//!
//!   Copyright (C) Manas Kamal Choudhury 2021
//!
//!   kstack -- Kernel Stack allocator 
//!
//!   //PROJECT - Aurora's Xeneva
//!   //AUTHOR  - Manas Kamal Choudhury
//!
//!=================================================

#include <arch\x86_64\kstack.h>
#include <string.h>

unsigned int index = 0;

extern uint64_t allocate_kstack (uint64_t *cr3) {

	uint64_t location = KSTACK_START; //+ index;
	for (int i = 0; i < (2*1024*1024)/4096; i++) {
		void* p = pmmngr_alloc();
		map_page_ex (cr3,(uint64_t)p,location + i * 4096, 0);
	}
	//index += 2*1024*1024;
	return (KSTACK_START + 2*1024*1024);
}

