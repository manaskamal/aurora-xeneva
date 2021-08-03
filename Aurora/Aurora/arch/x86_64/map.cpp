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

void *map_memory (uint64_t addr, uint32_t length, uint8_t map_type, uint8_t attribute) {
	if (addr == NULL) {
		addr = (uint64_t)get_free_page (length);
		if (length == 4096) {
			map_page ((uint64_t)pmmngr_alloc(), addr);
			return (void*)addr;
		}

		for (int i = 0; i < length / 4096; i++)
				map_page ((uint64_t)pmmngr_alloc(),addr + i * 4096);
	}
	return (void*)addr;
}

void unmap_memory (void* addr, uint32_t length) {
	unsigned char* buffer = (unsigned char*)addr;
	fat32_create_file ("MM1.txt",buffer, length);

	/*if (length == 4096) 
		unmap_page ((uint64_t)addr);
	else if (length > 4096) {
		for (int i = 0; i < length / 4096; i++) {
			unmap_page ((uint64_t)addr + i * 4096);
		}
	}*/
}



