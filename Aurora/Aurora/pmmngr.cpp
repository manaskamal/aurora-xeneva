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
#include <arch\x86_64\mmngr\paging.h>
#include <serial.h>
#include <efi.h>

uint64_t free_memory = 0;
uint64_t reserved_memory;
uint64_t used_memory = 0;
uint64_t ram_bitmap_index;
uint64_t total_ram;
uint64_t bitmap_size = 0;
bool higher_half = false;

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


void AuPmmngrInitBitmap (size_t bitmap_size, void* buffer) {

	ram_bitmap.Size = bitmap_size;
	ram_bitmap.Buffer = (uint8_t*)buffer;

	for (int i = 0; i < bitmap_size ; i++) {
		*(uint8_t*)(ram_bitmap.Buffer + i) = 0;
	}
}

//! Reserve a page : mark it as unusable
void AuPmmngrLockPage ( void* addr) {

	uint64_t index = (uint64_t)addr / 4096;
	if (ram_bitmap[index] == true) return;
	if (ram_bitmap.Set (index, true)) {
		free_memory -= 4096;
		reserved_memory += 4096;
	}
}

//! Reserve pages : mark it as unusable
void AuPmmngrLockPages (void *addr, size_t size) {
	for (int i = 0; i < size; i++) 
		AuPmmngrLockPage ((void*)((size_t)addr + i * 4096));
}

//! Unreserve a page : Mark it as usable
void AuPmmngrUnreservePage (void* addr) {

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
void AuPmmngrInit(KERNEL_BOOT_INFO *info)
{
	free_memory = 0;
	bitmap_size = 0;
	total_ram = 0;
	ram_bitmap_index = 0;

	uint64_t memmap_entries = info->mem_map_size / info->descriptor_size;
	void* bitmap_area = 0;

	/* Scan a suitable area for the bitmap */
	for (size_t i = 0; i < memmap_entries; i++) {
		EFI_MEMORY_DESCRIPTOR *efi_mem = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)info->map + i * info->descriptor_size);
		total_ram += efi_mem->num_pages * 4096;
		if (efi_mem->type == 7) {
			if (((efi_mem->num_pages * 4096) > 0x100000) && bitmap_area == 0) {
				bitmap_area = (void*)efi_mem->phys_start;
			}
			uint64_t size_in_mb_kb = 0;
			char* unit = "B";
			if ((efi_mem->num_pages * 4096 / 1024 / 1024) == 0) {
				size_in_mb_kb = efi_mem->num_pages * 4096 / 1024;
				unit = "KB";
			}
			else {
				size_in_mb_kb = (efi_mem->num_pages * 4096 / 1024 / 1024);
				unit = "MB";
			}
			info->printf_gui("[aurora]: usable memory -> %x length -> %d %s\n", efi_mem->phys_start, size_in_mb_kb, unit);
		}
	}

	info->printf_gui("[aurora]: total memory -> %d GB \n", (total_ram/ 1024 / 1024 / 1024));
	uint64_t bitmap_size = total_ram / 4096 / 8 + 1;

	AuPmmngrInitBitmap(bitmap_size, bitmap_area);

	info->printf_gui("[aurora]: bitmap initialized %d bytes\n", bitmap_size);
	AuPmmngrLockPages((void*)bitmap_area, bitmap_size);

	/* No lock all pages, that are not for use */
	for (size_t i = 0; i < memmap_entries; i++) {
		EFI_MEMORY_DESCRIPTOR *efi_mem = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)info->map + i * info->descriptor_size);
		total_ram += efi_mem->num_pages;
		if (efi_mem->type != 7) {
			AuPmmngrLockPages((void*)efi_mem->phys_start, efi_mem->num_pages);
		}
	}

	AuPmmngrLockPage((void*)0x0);

	/* also lock the early used physical blocks for 
	 * kernel and kernel stack */
	uint32_t allocated_count = info->reserved_mem_count;
	uint64_t* allocated_stack = (uint64_t*)info->allocated_stack;
	while (allocated_count) {
		uint64_t address = *allocated_stack--;
		AuPmmngrLockPage((void*)address);
		allocated_count--;
	}

	/* Will be used for SMP AP initialisation code */
	uint64_t *address = (uint64_t*)0xA000;
	AuPmmngrLockPage((void*)0xA000);
	memset(address, 0, 4096);
	memcpy(address, info->apcode, 4096);

	higher_half = false;
	info->printf_gui("[aurora]:pmmngr initialized\n");
}

/*
 * pmmngr_move_higher_half -- moves the kernel to higher half
 * of memory 
 */
void AuPmmngrMoveHigher () {
	ram_bitmap.Buffer = (uint8_t*)p2v((uint64_t)ram_bitmap.Buffer);
	higher_half = true;
}


uint64_t p2v (uint64_t addr) {
	if (higher_half)
		return (PHYSICAL_MEMORY_BASE + addr);
	else
		return addr;
}

uint64_t v2p (uint64_t vaddr) {
	if (higher_half)
		return (vaddr - PHYSICAL_MEMORY_BASE);
	else 
		return vaddr;
}

bool is_higher_half() {
	return higher_half;
}

/**
 * Allocates numbers of blocks for use
 *
 * @param blocks -- number of blocks to return,
 *                  assume that 1 blocks = 4096 bytes
 */
void* AuPmmngrAlloc()
{
	
	for (; ram_bitmap_index < ram_bitmap.Size * 8; ram_bitmap_index++) {
		if (ram_bitmap[ram_bitmap_index] == true) continue;
		AuPmmngrLockPage((void*)(ram_bitmap_index * 4096));
		used_memory += 4096 * 1;
		return (void*)(ram_bitmap_index * 4096);
	}

	x64_cli();
	printf ("Used RAM -> %d MB, Free RAM -> %d MB\n", used_memory /1024 / 1024, free_memory / 1024 / 1024);
	printf ("No more available pages\n");
	x64_hlt();
	for(;;);
	return NULL; //here we need to swap page to file
}


void* AuPmmngrAllocBlocks(int size) {
	void *first = AuPmmngrAlloc();
	for (int i = 0; i < size / 4096; i++) {
		AuPmmngrAlloc();
	}

	return first; //here we need to swap page to file
}
/**
 * Free block i.e make it available for use that address
 *
 * @param blocks -- number of blocks to free
 */
void AuPmmngrFree (void* addr)
{
	uint64_t index = (uint64_t)addr / 4096;
	if (ram_bitmap[index] == false) return;
	if (ram_bitmap.Set (index, false)) {
		free_memory += 4096;
		used_memory -= 4096 * 1;	
		if (ram_bitmap_index > index) {
			ram_bitmap_index = index;
		}
	}
}

/**
 * pmmngr_free_block -- free a list of blocks
 */
void AuPmmngrFreeBlocks(void* addr, int count) {
	uint64_t * address = (uint64_t*)addr;
	for (uint32_t i = 0; i < count; i++) {
		AuPmmngrFree(address);
		address += 0x1000;
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


uint64_t pmmngr_get_ram_bitmap_size() {
	return bitmap_size;
}






