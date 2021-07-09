/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 *  vmmngr.h -- Memory Manager Abstraction Layer
 *
 *  /PROJECT - Aurora { Xeneva v1.0 }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *===============================================
 */

#ifndef __VMMNGR_H__
#define __VMMNGR_H__

#include <pmmngr.h>
#include <arch\x86_64\cpu.h>

#define PAGING_PRESENT  (1<<0)
#define PAGING_WRITABLE (1<<1)
#define PAGING_USER     0x4

extern size_t  pml4_index (uint64_t addr);
extern size_t pdp_index (uint64_t addr);
extern size_t pd_index (uint64_t addr);
extern size_t pt_index (uint64_t addr);
extern size_t p_index (uint64_t addr);


//*************************************************
//! F U N C T I O N S   P R O T O T Y P E
//*************************************************
extern void vmmngr_x86_64_init ();
extern bool map_page (uint64_t physical_address, uint64_t virtual_address);
extern bool map_page_ex (uint64_t *pml4i,uint64_t physical_address, uint64_t virtual_address);
extern uint64_t *create_user_address_space ();
#endif