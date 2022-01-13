/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  pmmngr.h -- Physical Memory Manager
 *
 *  /PROJECT - Aurora v1.0 {Xeneva v1.0}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *  @Reference : Poncho OSDev S2 Series
 * ================================================
 */

#include <pmmngr.h>
#include <_null.h>
#include <stdio.h>
#include <arch\x86_64\cpu.h>
#include <efi.h>

uint64_t free_memory = 0;
uint64_t reserved_memory;
uint64_t used_memory = 0;
uint64_t ram_bitmap_index;
uint64_t total_ram;


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
	
		Buffer[byteIndex] &= ~bitIndexer;
		if (value) {
			Buffer[byteIndex] |= bitIndexer;	
		}

		return true;
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

//! Reserve a page : mark it as unusable
void pmmngr_lock_page ( void* addr) {

	uint64_t index = (uint64_t)addr / 4096;
	if (ram_bitmap[index] == true) return;
	if (ram_bitmap.Set (index, true)) {
		free_memory -= 4096;
		reserved_memory += 4096;
	}
}

//! Reserve pages : mark it as unusable
void pmmngr_lock_pages (void *addr, size_t size) {
	for (int i = 0; i < size; i++) 
		pmmngr_lock_page ((void*)((size_t)addr + i * 4096));
}

//! Unreserve a page : Mark it as usable
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
	total_ram = 0;

	pmmngr_init_bitmap (bitmap_size, (void*) _info->phys_start); 

	pmmngr_lock_pages ((void*)_info->phys_start,bitmap_size);

	//Lock every EFI-Reserved memories here
	uint64_t memmap_entries = _info->mem_map_size / _info->descriptor_size;

	//! Currently uses EFI-Memory Maps to check reserved regions
	for (int i = 0; i < memmap_entries; i++) {
		EFI_MEMORY_DESCRIPTOR *efi_mem = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)_info->map + i * _info->descriptor_size);
		total_ram += efi_mem->num_pages * 4096;
		if (efi_mem->type != 7) {
			//! lock every pages
			free_memory -= 4096;
			pmmngr_lock_pages ((void*)efi_mem->phys_start,efi_mem->num_pages);
		}
	}

	total_ram -= reserved_memory;

	void *unusable = pmmngr_alloc(); //0 is avoided
}


/**
 * Allocates numbers of blocks for use
 *
 * @param blocks -- number of blocks to return,
 *                  assume that 1 blocks = 4096 bytes
 */
void* pmmngr_alloc()
{
	
	for (; ram_bitmap_index < ram_bitmap.Size * 8; ram_bitmap_index++) {
		if (ram_bitmap[ram_bitmap_index] == true) continue;
		pmmngr_lock_page ((void*)(ram_bitmap_index * 4096));
		used_memory += 4096 * 1;
		return (void*)(ram_bitmap_index * 4096);
	}

	for (int index = 0; index  < ram_bitmap.Size * 8; index++) {
		if (ram_bitmap[index] == true) continue;
		pmmngr_lock_page ((void*)(index * 4096));
		used_memory += 4096 * 1;
		return (void*)(index * 4096);
	}
	x64_cli();
	printf ("Used RAM -> %d MB, Free RAM -> %d MB\n", used_memory /1024 / 1024, free_memory / 1024 / 1024);
	printf ("No more available pages\n");
	x64_hlt();
	for(;;);
	return NULL; //here we need to swap page to file
}


void* pmmngr_alloc_blocks (int size) {
	void *first = pmmngr_alloc();
	for (int i = 0; i < size / 4096; i++) {
		pmmngr_alloc();
	}

	return first; //here we need to swap page to file
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
		if (ram_bitmap_index > index) {
			ram_bitmap_index = index;
		}
	}
}

//! Returns amount of free RAM
uint64_t pmmngr_get_free_ram () {
	return free_memory;
}

//! Return amount of used RAM
uint64_t pmmngr_get_used_ram () {
	return used_memory;
}

//! Return total RAM size
uint64_t pmmngr_get_total_ram () {
	return total_ram;
}






