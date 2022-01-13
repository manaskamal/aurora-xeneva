/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  kheap.h -- Kernel Heap Memory Allocator
 *
 *  /PROJECT - Aurora {Xeneva }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *=============================================
 */

#ifndef __KHEAP_H__
#define __KHEAP_H__

#include <stdint.h>
#include <arch\x86_64\mmngr\vmmngr.h>
#include <stdio.h>

struct kmem {
	size_t length;
	kmem* next;
	kmem* last;
	bool free;
	void align_next ();
	void align_prev();
	kmem* split (size_t length);
};

void initialize_kmemory (size_t sz);
void* malloc(size_t sz);
void free(void* memory);

#endif