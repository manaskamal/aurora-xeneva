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

#define PAGING_PRESENT  0x1
#define PAGING_WRITABLE 0x2
#define PAGING_USER     0x4

#define KERNEL_BASE_ADDRESS  0xFFFFE00000000000
#define USER_BASE_ADDRESS 0x0000020000000000   //0x0000400000000000
#define PHYSICAL_MEMORY_BASE  0xFFFF800000000000

extern size_t  pml4_index (uint64_t addr);
extern size_t pdp_index (uint64_t addr);
extern size_t pd_index (uint64_t addr);
extern size_t pt_index (uint64_t addr);
extern size_t p_index (uint64_t addr);


//*************************************************
//! F U N C T I O N S   P R O T O T Y P E
//*************************************************
extern void vmmngr_x86_64_init ();
extern bool map_page (uint64_t physical_address, uint64_t virtual_address, uint8_t attrib);
extern bool map_page_ex (uint64_t *pml4i,uint64_t physical_address, uint64_t virtual_address, uint8_t attrib);
//! Map a page in current address space
extern bool map_page2 (uint64_t physical_address, uint64_t virtual_address, uint8_t attrib);
extern void unmap_page_ex(uint64_t* cr3, uint64_t virt_addr, bool free_physical);
extern uint64_t *create_user_address_space ();
extern void unmap_page(uint64_t virt_addr);
extern uint64_t* get_physical_address (uint64_t virt_addr);
extern uint64_t* get_free_page (size_t s, bool user);
extern uint64_t* vmmngr_get_kernel_pml4();
extern void vmmngr_free_pages(uint64_t virt_addr, bool free_physical, size_t s);
#endif