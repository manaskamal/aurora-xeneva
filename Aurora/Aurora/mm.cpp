/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 *  mm.h -- Memory Manager Abstraction Layer
 *
 *  /PROJECT - Aurora { Xeneva v1.0 }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *===============================================
 */
#include <mm.h>
#include <arch\x86_64\mmngr\kheap.h>

void mm_init (KERNEL_BOOT_INFO *info) {
#ifdef ARCH_X64
	vmmngr_x86_64_init (info);
	initialize_kmemory(16);
#elif  ARCH_ARM
	//!initialize arm32 virtual memory manager
#elif  ARCH_ARM64
	//!initialize arm64 virtual memory manager
#endif
}

void* malloc (uint32_t address) {
#ifdef ARCH_X64
	return alloc (address);
#elif  ARCH_ARM
	//return with arm32 allocator
#elif  ARCH_ARM64
	//!return with arm64 allocator
#endif
}


void mfree(void* address) {
#ifdef ARCH_X64
	 free (address);
#elif  ARCH_ARM
	//arm32 free routine
#elif  ARCH_ARM64
	//!arm64 free routine
#endif
}