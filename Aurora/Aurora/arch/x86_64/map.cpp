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

/**
 * do a memory map with given length,
 * at future, file mapping will be implemented
 */
void *map_memory (uint64_t addr, uint32_t length, uint8_t map_type, uint8_t attribute) {
	bool user = false;
	if (attribute & ATTRIBUTE_USER)
		user = true;
	if (addr == NULL) {
		addr = (uint64_t)get_free_page (length, user);
		if (length == 4096) {
			map_page ((uint64_t)pmmngr_alloc(), addr);
			return (void*)addr;
		}

		for (int i = 0; i < length / 4096; i++)
				map_page ((uint64_t)pmmngr_alloc(),addr + i * 4096);


	} else {
		if (length == 4096) {
			map_page ((uint64_t)pmmngr_alloc(), addr);
			return (void*)addr;
		}

		for (int i = 0; i < length / 4096; i++)
				map_page ((uint64_t)pmmngr_alloc(),addr + i * 4096);
	}

	return (void*)addr;
}


/**
 * Just simply unmap the memory region for now,
 * at future commiting the data to disk by checking the
 * file handle, will be implemented
 */
void unmap_memory (void* addr, uint32_t length) {
	/*unsigned char* buffer = (unsigned char*)addr;
	fat32_create_file ("MM1.txt",buffer, length);*/

	uint64_t address = (uint64_t)addr;

	if (length == 4096) 
		unmap_page (address);

	if (length > 4096) {
		for (int i = 0; i < length / 4096; i++) {
			unmap_page (address + i * 4096);
		}
	}
}



