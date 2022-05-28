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
#include <aurora.h>

#define PAGING_PRESENT  0x1
#define PAGING_WRITABLE 0x2
#define PAGING_USER     0x4
#define PAGING_NO_EXECUTE 0x80000
#define PAGING_NO_CACHING 0x200000
#define PAGING_WRITE_THROUGH  0x400000

#define KERNEL_BASE_ADDRESS  0xFFFFE00000000000
#define USER_BASE_ADDRESS 0x0000000060000000   //0x0000400000000000
#define USER_END_ADDRESS  0x0000000080000000
#define PHYSICAL_MEMORY_BASE  0xFFFF800000000000
#define MMIO_BASE    0xffffff1000000000            //  0xffffff1fc0000000

#define PROCESS_HEAP_BREAK  0x0000000020000000   //8GiB

extern size_t  pml4_index (uint64_t addr);
extern size_t pdp_index (uint64_t addr);
extern size_t pd_index (uint64_t addr);
extern size_t pt_index (uint64_t addr);
extern size_t p_index (uint64_t addr);


//*************************************************
//! F U N C T I O N S   P R O T O T Y P E
//*************************************************
extern void AuPagingInit();
AU_EXTERN AU_EXPORT bool AuMapPage (uint64_t physical_address, uint64_t virtual_address, uint8_t attrib);
extern bool AuMapPageEx(uint64_t *pml4i,uint64_t physical_address, uint64_t virtual_address, uint8_t attrib);
extern void AuUnmapPageEx(uint64_t* cr3, uint64_t virt_addr, bool free_physical);
AU_EXTERN AU_EXPORT void AuUnmapPage(uint64_t virt_addr, bool free_physical);
extern uint64_t *AuCreateAddressSpace();

AU_EXTERN AU_EXPORT uint64_t* AuGetPhysicalAddress(uint64_t cr3,uint64_t virt_addr);
AU_EXTERN AU_EXPORT uint64_t* AuGetFreePage(size_t s, bool user, void* ptr);
AU_EXTERN AU_EXPORT  uint64_t* AuGetRootPageTable();
AU_EXTERN AU_EXPORT void AuFreePages(uint64_t virt_addr, bool free_physical, size_t s);
AU_EXTERN AU_EXPORT void* AuMapMMIO (uint64_t phys_addr, size_t page_count);
extern void AuPagingClearLow();
#endif