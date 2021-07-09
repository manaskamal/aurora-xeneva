/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT -Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *-----=-=-=---=-==-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 */

#ifndef __MM_H__
#define __MM_H__

//! A Simple fixed size allocator for DWM Allocation use
typedef struct _list_entry_ {
	struct _list_entry_ *next;
	struct _list_entry_ *prev;
	bool is_free;
}LIST_ENTRY;

//! INIT: Initialize the user space allocator
extern void initialize_allocator(int sz);
//! ALLOCATE: Allocate some memory
extern void* malloc(int size);
//! FREE: Free pointed memory
extern void mfree(void* memory);
#endif