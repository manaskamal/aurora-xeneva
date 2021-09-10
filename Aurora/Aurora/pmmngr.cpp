/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  pmmngr.h -- Physical Memory Manager
 *
 *  /PROJECT - Aurora v1.0 {Xeneva v1.0}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#include <pmmngr.h>
#include <_null.h>

uint64_t free_memory;
uint64_t reserved_memory;
uint64_t used_memory;
uint64_t ram_bitmap_index;


//! A bitmap class
class Bitmap {
public:
	size_t Size;
	uint8_t* Buffer;

	//! Operator set up
	bool operator[](uint64_t index) {
		
		if (index > Size * 8) return false;
		uint64_t byteIndex = index / 8;
		uint8_t  bitIndex = index % 8;
		uint8_t  bitIndexer = 0x80 >> bitIndex;

		if ((Buffer[byteIndex] & bitIndexer) > 0) {
			return true;
		}
		return false;
	}

	//! Set a bit to a index
	bool Set(uint64_t index, bool value) {
		
		if (index > Size * 8) return false;

		uint64_t byteIndex = index / 8;
		uint8_t  bitIndex = index % 8;
		uint8_t  bitIndexer = 0x80 >> bitIndex;

		Buffer[byteIndex] &= -bitIndexer;
		if (value) {
			Buffer[byteIndex] |= bitIndexer;
		}

		return false;
	}
};

Bitmap ram_bitmap;


void pmmngr_init_bitmap (size_t bitmap_size, void* buffer) {

	ram_bitmap.Size = bitmap_size;
	ram_bitmap.Buffer = (uint8_t*)buffer;

	for (int i = 0; i < bitmap_size ; i++) {
		*(uint8_t*)(ram_bitmap.Buffer + i) = 0;
	}
}

void pmmngr_lock_page ( void* addr) {

	uint64_t index = (uint64_t)addr / 4096;
	if (ram_bitmap[index] == true) return;
	if (ram_bitmap.Set (index, true)) {
		free_memory -= 4096;
		used_memory += 4096;
	}
}

void pmmngr_unreserve_page (void* addr) {

	uint64_t index = (uint64_t)addr / 4096;
	if (ram_bitmap[index] == false) return;
	if (ram_bitmap.Set(index, false)) {
		free_memory += 4096;
		reserved_memory -= 4096;
		if (ram_bitmap_index > index) ram_bitmap_index = index;
	}
}




/**
 * Initialize the physical memory manager
 *
 * @param _info == Kernel boot information passed by xnldr
 */
void pmmngr_init(KERNEL_BOOT_INFO *_info)
{
	//! scan for memory above 1MB and set up the current pointer

	uint64_t memory_size = _info->ram_size;
	free_memory = memory_size;
	uint64_t bitmap_size = memory_size / 4096 / 8 + 1;
	ram_bitmap_index = 0;


	pmmngr_init_bitmap (bitmap_size, (void*)_info->phys_start);
	void * p = (void*)pmmngr_alloc();
}


/**
 * Allocates numbers of blocks for use
 *
 * @param blocks -- number of blocks to return,
 *                  assume that 1 blocks = 4096 bytes
 */
void* pmmngr_alloc()
{
	free_memory -= 4096 * 1;
	used_memory += 4096 * 1;
	for (; ram_bitmap_index < ram_bitmap.Size * 8; ram_bitmap_index++) {
		if (ram_bitmap[ram_bitmap_index] == true) continue;
		pmmngr_lock_page ((void*)(ram_bitmap_index * 4096));
		return (void*)(ram_bitmap_index * 4096);
	}

	return NULL; //here we need to swap page to file
}

/**
 * Free block i.e make it available for use that address
 *
 * @param blocks -- number of blocks to free
 */
void pmmngr_free (void* addr)
{
	uint64_t index = (uint64_t)addr / 4096;
	if (ram_bitmap[index] == false) return;
	if (ram_bitmap.Set (index, false)) {
		free_memory += 4096;
		used_memory -= 4096;
		if (ram_bitmap_index > index) ram_bitmap_index = index;
	}
}


uint64_t pmmngr_get_free_ram () {
	return free_memory;
}

uint64_t pmmngr_get_used_ram () {
	return used_memory;
}




