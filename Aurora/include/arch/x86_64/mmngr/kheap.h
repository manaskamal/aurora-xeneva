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

#define HEAP_MAGIC   0x12112002

typedef struct _kmem_ {
	uint32_t magic;
	bool free;
	size_t length;
	struct _kmem_* next;
	struct _kmem_* prev;
}heap_t;


void initialize_kmemory (size_t sz);
void* malloc(size_t sz);
void free(void* memory);

#endif