/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  allocator.h -- DWM Internal memory allocator
 *
 *  /PROJECT - Aurora { Xeneva }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <stdtypes.h>


//! A Simple fixed size allocator for DWM Allocation use
typedef struct _list_entry_ {
	struct _list_entry_ *next;
	struct _list_entry_ *prev;
	bool is_free;
	size_t  length;
}LIST_ENTRY;


//! INIT: Initialize the DWM internal memory allocator
extern void initialize_dwm_allocator(int sz);
//! ALLOCATE: Allocate some memory
extern void* dalloc(uint32_t size);
//! FREE: Free pointed memory
extern void dfree(void* memory);

#endif