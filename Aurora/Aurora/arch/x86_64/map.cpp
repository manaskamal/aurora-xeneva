/**  
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *   
 *   map.cpp -- Memory Mapping of files, devices, free memories goes here
 *
 *   /PROJECT - Aurora Xeneva
 *   /AUTHOR  - Manas Kamal Choudhury
 *
 * =========================================================================
 */

#include <arch\x86_64\mmngr\map.h>
#include <fs\fat32.h>
#include <proc.h>

/**
 * do a memory map with given length,
 * at future, file mapping will be implemented
 */
void *map_memory (uint64_t addr, uint32_t length,uint8_t attribute) {
	x64_cli();
	process_t * c_proc = get_current_process();

	//!Attribute check
	bool user = false;
	if (attribute & ATTRIBUTE_USER)
		user = true;

	//! For more convenient, give a null to address parameter 
	//! cause, null parameter will cause map_memory to look for free
	//! memory in process's address space
	if (addr == NULL) {
		addr = (uint64_t)get_free_page (length, user);
		if (length == 4096) {
			map_page ((uint64_t)pmmngr_alloc(), addr);
			return (void*)addr;
		}

		for (int i = 0; i < length / 4096; i++)
				map_page ((uint64_t)pmmngr_alloc(),addr + i * 4096);


	} 
	//! use the given address to map a region
	//! TODO: Check if there's already a mapped region, and relocate the mapping
	else {
		if (length == 4096) {
			map_page ((uint64_t)pmmngr_alloc(), addr);
			return (void*)addr;
		}

		for (int i = 0; i < length / 4096; i++)
				map_page ((uint64_t)pmmngr_alloc(),addr + i * 4096);
	}

	//! MAP_GLOBAL flag will cause the map_memory to map the address
	//! in its child process, for now its not implemented

	//if (attribute & MAP_GLOBAL) {
	//	process_map_addresses (addr,length,(uint64_t*)c_proc->thread_data_pointer->cr3,c_proc);
	//}
	
	//! return the mapped address
	return (void*)addr;
}


/**
 * Just simply unmap the memory region for now,
 * at future commiting the data to disk by checking the
 * file handle, will be implemented
 */
void unmap_memory (void* addr, uint32_t length) {
	x64_cli();
	printf ("munmap called -> %x, length -> %d\n", addr, length);
	/*
	 * Before unmapping the object, we should get the object
	 * and write it to a file if object is not null
	 * but for now object manager is not implemented,
	 * kept for future use
	 */

	uint64_t address = (uint64_t)addr;

	if (length == 4096) 
		unmap_page (address);

	if (length > 4096) {
		for (int i = 0; i < length / 4096; i++) {
			unmap_page (address + i * 4096);
		}
	}
}



