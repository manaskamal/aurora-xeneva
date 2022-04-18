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

#ifndef __PMMNGR_H__
#define __PMMNGR_H__

#include <_xnboot.h>
#include <stdint.h>

/**
 * Initialize The Physical Memory Manager
 * @param _info -- Bootloader informations
 */
extern void AuPmmngrInit (KERNEL_BOOT_INFO *_info);

/**
 * Allocate a free page
 */
extern void* AuPmmngrAlloc();

/** 
 * Allocate some free pages
 * @param size -- amount to allocate
 */
extern void* AuPmmngrAllocBlocks (int size);

/**
 * Reserve a page: Mark it as unusable
 * @param addr -- Address to mark
 * @param size -- Number of pages
 */
extern void AuPmmngrLockPages (void *addr, size_t size);

//! Reserve a page : mark it as unusable
extern void AuPmmngrLockPage ( void* addr);

/**
 * Free a page
 * @param addr -- Address to free
 */
extern void AuPmmngrFree (void* addr);

/**
 * pmmngr_free_block -- free a list of blocks
 */
extern void AuPmmngrFreeBlocks (void* addr, int count);

/**
 * Returns the total amount of free ram
 */
extern uint64_t pmmngr_get_free_ram ();

/**
 * Returns the total amount of used ram
 */
extern uint64_t pmmngr_get_used_ram ();

/**
 * Returns the total amount to RAM
 */
extern uint64_t pmmngr_get_total_ram ();

extern void AuPmmngrMoveHigher();

extern uint64_t pmmngr_get_ram_bitmap_size();

extern uint64_t p2v (uint64_t addr);

extern uint64_t v2p (uint64_t vaddr);

extern bool is_higher_half();

#endif
