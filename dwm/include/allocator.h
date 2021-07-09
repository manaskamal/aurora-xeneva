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
}LIST_ENTRY;


//! INIT: Initialize the DWM internal memory allocator
extern void initialize_dwm_allocator(int sz);
//! ALLOCATE: Allocate some memory
extern void* dalloc(int size);
//! FREE: Free pointed memory
extern void dfree(void* memory);

extern void initialize_flat_allocator (int size);

extern void *flat_alloc ();

extern void flat_free ();
#endif