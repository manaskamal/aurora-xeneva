///! 
///!  Copyright (C) Manas Kamal Choudhury
///!
///!  buffer.h -- Buffer manager for double buffering uses
///!
///!  /PROJECT - Aurora's Xeneva v1.0
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=============================================================

#include <buffer.h>
#include <sys\mmap.h>
#include <sys\_term.h>

static int dbl_buffer_pos = 0;


uint32_t* acrylic_allocate_buffer (size_t sz) {
	uint64_t location = DOUBLE_BUFFER_START + dbl_buffer_pos;
	sys_print_text ("SIZE -> %x \r\n", (location + sz));

	void* address = mmap(NULL,sz,0,0,0,0);

	return (uint32_t*)address;
}


void acrylic_free_buffer (void *p,size_t sz) {
	uint64_t location = (uint64_t)p;
	sys_munmap(p,sz);
}