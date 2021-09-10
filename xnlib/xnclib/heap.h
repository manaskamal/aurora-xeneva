/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  heap.h -- Heap Memory Manager for user application
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==================================================
 */

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdint.h>


#define ALLOCATOR_START     0x0000080000000000


//! A Simple fixed size allocator for DWM Allocation use
typedef struct _list_entry_ {
	struct _list_entry_ *next;
	struct _list_entry_ *prev;
	bool    is_free;
	size_t  length;
}LIST_ENTRY;

//! INIT: Initialize the user space allocator
extern "C" void heap_initialize_allocator();
//! ALLOCATE: Allocate some memory
extern void* _malloc(uint32_t size);
//! FREE: Free pointed memory
extern void _free(void* memory);


#endif