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
extern void pmmngr_init (KERNEL_BOOT_INFO *_info);

/**
 * Allocate a free page
 */
extern void* pmmngr_alloc();

/** 
 * Allocate some free pages
 * @param size -- amount to allocate
 */
extern void* pmmngr_alloc_blocks (int size);

/**
 * Reserve a page: Mark it as unusable
 * @param addr -- Address to mark
 * @param size -- Number of pages
 */
extern void pmmngr_lock_pages (void *addr, size_t size);

/**
 * Free a page
 * @param addr -- Address to free
 */
extern void pmmngr_free (void* addr);

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


#endif
