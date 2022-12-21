/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *
 **/

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

#define PROCESS_HEAP_BREAK  0x0000000380000000   //12GiB

extern size_t  pml4_index (uint64_t addr);
extern size_t pdp_index (uint64_t addr);
extern size_t pd_index (uint64_t addr);
extern size_t pt_index (uint64_t addr);
extern size_t p_index (uint64_t addr);


typedef union _AuVPage_ {
	struct {
		uint64_t present:1;
		uint64_t writable:1;
		uint64_t user:1;
		uint64_t write_through:1;
		uint64_t cache_disable:1;
		uint64_t access:1;
		uint64_t dirty:1;
		uint64_t size:1;
		uint64_t global:1;
		uint64_t cow:1;
		uint64_t _avail:2;
		uint64_t page:28;
		uint64_t reserved:12;
		uint64_t nx:1;
	} bits;
	uint64_t raw;
}AuVPage;

//*************************************************
//! F U N C T I O N S   P R O T O T Y P E
//*************************************************
extern void AuPagingInit();

/*
 * AuMapPage -- Map a page in current address space
 * @param physical_address -- Physical address
 * @param virtual_address -- Virtual address to map to
 * @param attrib -- Additional attributes
 */
AU_EXTERN AU_EXPORT bool AuMapPage (uint64_t physical_address, uint64_t virtual_address, uint8_t attrib);
extern bool AuMapPageEx(uint64_t *pml4i,uint64_t physical_address, uint64_t virtual_address, uint8_t attrib);
extern void AuUnmapPageEx(uint64_t* cr3, uint64_t virt_addr, bool free_physical);

/*
 * AuUnmapPage -- Unmaps a physical address from its virtual address
 * @param virt_addr -- virtual address
 * @param free_physical -- boolean value specifies if physical frame
 * needs to be freed or not
 */
AU_EXTERN AU_EXPORT void AuUnmapPage(uint64_t virt_addr, bool free_physical);

/*
 * AuCreateAddressSpace -- Creates a new address space 
 */
extern uint64_t *AuCreateAddressSpace();

/*
 * AuGetPage -- Returns a virtual page in a AuVPage structure
 * if it's not present then a new virtual page will be created
 * and returned to the caller
 * @param virtual_address -- virtual address to check
 * @param attrib -- new attribute to follow
 */
AU_EXTERN AU_EXPORT AuVPage* AuGetPage (uint64_t virtual_address, uint8_t attrib);
AU_EXTERN AU_EXPORT uint64_t* AuGetPhysicalAddress(uint64_t cr3,uint64_t virt_addr);
AU_EXTERN AU_EXPORT uint64_t* AuGetFreePage(size_t s, bool user, void* ptr);
AU_EXTERN AU_EXPORT  uint64_t* AuGetRootPageTable();
AU_EXTERN AU_EXPORT void AuFreePages(uint64_t virt_addr, bool free_physical, size_t s);
AU_EXTERN AU_EXPORT void* AuMapMMIO (uint64_t phys_addr, size_t page_count);
extern void AuPagingClearLow();
#endif