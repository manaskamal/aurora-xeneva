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

static int dbl_buffer_pos = 0;


uint32_t* acrylic_allocate_buffer (size_t sz) {
	uint64_t location = DOUBLE_BUFFER_START + dbl_buffer_pos;
	
	for (int i = 0; i < sz / 4096; i++) {
		valloc (location + i * 4096);
	}

	dbl_buffer_pos += sz;
	return (uint32_t*)location;
}


void acrylic_free_buffer (void *p,size_t sz) {
	uint64_t location = (uint64_t)p;
	for (int i = 0; i < sz / 4096; i++) 
		vfree(location + i * 4096);
	dbl_buffer_pos -= sz;
}