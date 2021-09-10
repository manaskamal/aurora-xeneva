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

extern void pmmngr_init (KERNEL_BOOT_INFO *_info);
extern void* pmmngr_alloc();
extern void pmmngr_free (void* addr);
extern uint64_t pmmngr_get_free_ram ();
extern uint64_t pmmngr_get_used_ram ();

#endif
