/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021 - present, Manas Kamal Choudhury
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

#include <arch\x86_64\mmngr\paging.h>
#include <screen.h>
#include <arch\x86_64\thread.h>
#include <pmmngr.h>
#include <serial.h>
#include <arch\x86_64\apic.h>
#include <stdio.h>


//!!!======================================================================================
//!!! TODO --- Address Space Manager
//!!! I/O Address Manager --- Allocates Virtual Memory for memory mapped I/O
//!!! Address Space for User --- Currently it copies 4GB identity mappings from 
//!!!                            kernel's address space, which needs to avoided
//!!                             by only copying those addresses which needs to 
//!!                             mapped in the new address space like, physical
//!!                             addresses needed for page tables creation and
//!!                             some memory mapped I/Os which are not mapped
//!!                             in higher half section of kernel's address space
//!!
//!!  Pages Management --- Keeping tracks for allocated pages and free pages
//!!  Randomization    --- This is an address space management concept, from where
//!!                       random pages will be allocated from the given address space
//!!--------------------------------------------------------------------------------------
//!!======================================================================================

uint64_t* mmio_base_address = 0;
uint64_t* root_cr3;


static void* make_canonical_i(size_t addr)
{
	if (addr & ((size_t)1 << 47))
		addr |= 0xFFFF000000000000;
	return (void*)addr;
}

static void* make_canonical(void* addr)
{
	return make_canonical_i((size_t)addr);
}

size_t  pml4_index (uint64_t addr){
	return (addr >> 39) & 0x1ff;
}

size_t pdp_index (uint64_t addr){
	return (addr >> 30) & 0x1ff;
}

size_t pd_index (uint64_t addr){
	return (addr >> 21) & 0x1ff;
}

size_t pt_index (uint64_t addr){
	return (addr >> 12) & 0x1ff;
}

size_t p_index (uint64_t addr){
	return (addr & 0x7ff);
}


//! Clear a 4k page
static void clear(void* addr){
	uint64_t* t = (uint64_t*)addr;
	for (size_t n = 0; n < 4096 / sizeof(uint64_t); ++n){
		t[n] = 0;
	}
}


/**
 * AuPagingInit -- initialize the
 * paging system
 */
void AuPagingInit() {

	uint64_t *cr3 = (uint64_t*)x64_read_cr3();
	uint64_t *new_cr3 = (uint64_t*)AuPmmngrAlloc();    

	memset (new_cr3, 0, 4096);
	mmio_base_address = (uint64_t*)MMIO_BASE;

	//! Copy all higher half mappings to new mapping
	for (int i = 0; i < 512; ++i) {
		if (i == 511)
			continue;

		if (cr3[i] & PAGING_PRESENT) {
			new_cr3[i] = cr3[i];
		}else {
			new_cr3[i] = 0;
		}
		
	}

	uint64_t* pdpt = (uint64_t*)AuPmmngrAlloc();
	memset(pdpt, 0, 4096);

	new_cr3[pml4_index(PHYSICAL_MEMORY_BASE)] = (uint64_t)pdpt | PAGING_PRESENT | PAGING_WRITABLE;

	for (size_t i = 0; i < 512; i++)
		pdpt[pdp_index(PHYSICAL_MEMORY_BASE) + i] = i * 512 * 512 * 4096 | 0x80 | PAGING_PRESENT | PAGING_WRITABLE;

	//! Store the kernel's address space
	root_cr3 = new_cr3;

	//! Switch to new mapping!!!
	x64_write_cr3 ((size_t)new_cr3);

	AuPmmngrMoveHigher();
}


/*
 * AuMapPage -- Map a page in current address space
 * @param physical_address -- Physical address
 * @param virtual_address -- Virtual address to map to
 * @param attrib -- Additional attributes
 */
bool AuMapPage(uint64_t physical_address, uint64_t virtual_address, uint8_t attrib){
	uint8_t flags = PAGING_PRESENT | PAGING_WRITABLE | attrib;

	
	const long i4 = (virtual_address >> 39) & 0x1FF;
	const long i3 = (virtual_address >> 30) & 0x1FF;
	const long i2 = (virtual_address >> 21) & 0x1FF;
	const long i1 = (virtual_address >> 12) & 0x1FF;

	uint64_t *pml4i = (uint64_t*)p2v(x64_read_cr3());

	if (!(pml4i[i4] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)AuPmmngrAlloc();
		pml4i[i4] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
	}
	uint64_t* pml3 = (uint64_t*)(p2v(pml4i[i4]) & ~(4096 - 1));
	
	if (!(pml3[i3] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)AuPmmngrAlloc();
		pml3[i3] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}
    
	
	uint64_t* pml2 = (uint64_t*)(p2v(pml3[i3]) & ~(4096 - 1));
	
	if (!(pml2[i2] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)AuPmmngrAlloc();
		pml2[i2] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}
	
	uint64_t* pml1 = (uint64_t*)(p2v(pml2[i2]) & ~(4096 - 1));
	if (pml1[i1] & PAGING_PRESENT)
	{
		AuPmmngrFree((void*)physical_address);
		return false;
	}

	pml1[i1] = physical_address | flags;
	flush_tlb ((void*)virtual_address);
	x64_mfence ();
	return true;
}

/*
 * AuUnmapPage -- Unmaps a physical address from its virtual address
 * @param virt_addr -- virtual address
 * @param free_physical -- boolean value specifies if physical frame
 * needs to be freed or not
 */
void AuUnmapPage(uint64_t virt_addr, bool free_physical){
	
	const long i1 = pml4_index(virt_addr);

	uint64_t *pml4_ = (uint64_t*)p2v(x64_read_cr3());
	uint64_t *pdpt = (uint64_t*)(p2v(pml4_[pml4_index(virt_addr)]) & ~(4096 - 1));
	uint64_t *pd = (uint64_t*)(p2v(pdpt[pdp_index(virt_addr)]) & ~(4096 - 1));
	uint64_t *pt = (uint64_t*)(p2v(pd[pd_index(virt_addr)]) & ~(4096 - 1));
	uint64_t *page = (uint64_t*)(p2v(pt[pt_index(virt_addr)]) & ~(4096 - 1));
	
	if ((pt[pt_index(virt_addr)] & PAGING_PRESENT) != 0) {
		
		pt[pt_index(virt_addr)] = 0;
	}

	if (page != 0 && free_physical == true) {
		AuPmmngrFree((void*)v2p((size_t)page));
	}
}


void AuUnmapPageEx(uint64_t* cr3, uint64_t virt_addr, bool free_physical){
	
	const long i1 = pml4_index(virt_addr);

	uint64_t *pml4_ = cr3;
	uint64_t *pdpt = (uint64_t*)(pml4_[pml4_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pd = (uint64_t*)(pdpt[pdp_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pt = (uint64_t*)(pd[pd_index(virt_addr)] & ~(4096 - 1));
	uint64_t *page = (uint64_t*)(pt[pt_index(virt_addr)] & ~(4096 - 1));

	if ((pt[pt_index(virt_addr)] & PAGING_PRESENT) != 0) {
		pt[pt_index(virt_addr)] = 0;
	}

	if (free_physical && page != 0) 
		AuPmmngrFree(page);

}

/*
 * AuGetPage -- Returns a virtual page in a AuVPage structure
 * if it's not present then a new virtual page will be created
 * and returned to the caller
 * @param virtual_address -- virtual address to check
 * @param attrib -- new attribute to follow
 */
AuVPage* AuGetPage (uint64_t virtual_address, uint8_t attrib) {
	uint8_t flags = PAGING_PRESENT | PAGING_WRITABLE | attrib ;

	
	const long i4 = (virtual_address >> 39) & 0x1FF;
	const long i3 = (virtual_address >> 30) & 0x1FF;
	const long i2 = (virtual_address >> 21) & 0x1FF;
	const long i1 = (virtual_address >> 12) & 0x1FF;

	uint64_t *pml4i = (uint64_t*)p2v(x64_read_cr3());

	if (!(pml4i[i4] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)AuPmmngrAlloc();
		pml4i[i4] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
	}
	uint64_t* pml3 = (uint64_t*)(p2v(pml4i[i4]) & ~(4096 - 1));
	
	if (!(pml3[i3] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)AuPmmngrAlloc();
		pml3[i3] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}
    
	
	uint64_t* pml2 = (uint64_t*)(p2v(pml3[i3]) & ~(4096 - 1));
	
	if (!(pml2[i2] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)AuPmmngrAlloc();
		pml2[i2] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}
	
	uint64_t* pml1 = (uint64_t*)(p2v(pml2[i2]) & ~(4096 - 1));
	if (pml1[i1] & PAGING_PRESENT)
	{

		AuVPage *page = (AuVPage*)&pml1[i1];
		return page;
	} else {
		uint64_t phys_addr = (uint64_t)AuPmmngrAlloc();
		memset((void*)p2v(phys_addr), 0, 4096);
		pml1[i1] = phys_addr | flags;
		flush_tlb ((void*)virtual_address);
		x64_mfence ();
		AuVPage *vpage = (AuVPage*)&pml1[i1];
		return vpage;
	}
	return NULL;
}


void AuFreePages(uint64_t virt_addr, bool free_physical, size_t s){
	
	const long i1 = pml4_index(virt_addr);

	for (int i = 0; i < (s /  4096) + 1; i++) {
		uint64_t *pml4_ = (uint64_t*)x64_read_cr3();
		uint64_t *pdpt = (uint64_t*)(pml4_[pml4_index(virt_addr)] & ~(4096 - 1));
		uint64_t *pd = (uint64_t*)(pdpt[pdp_index(virt_addr)] & ~(4096 - 1));
		uint64_t *pt = (uint64_t*)(pd[pd_index(virt_addr)] & ~(4096 - 1));
		uint64_t *page = (uint64_t*)(pt[pt_index(virt_addr)] & ~(4096 - 1));

		if ((pt[pt_index(virt_addr)] & PAGING_PRESENT) != 0) {
			pt[pt_index(virt_addr)] = 0;
		}

		if (free_physical && page != 0) 
			AuPmmngrFree(page);

		virt_addr = virt_addr + i * 4096;
	}

}


//! returns a physical address from virtual address
uint64_t* AuGetPhysicalAddress (uint64_t cr3,uint64_t virt_addr) {
	const long i1 = pml4_index(virt_addr);

	uint64_t *pml4 = (uint64_t*)p2v(cr3);
	uint64_t *pdpt = (uint64_t*)(p2v(pml4[pml4_index(virt_addr)]) & ~(4096 - 1));
	uint64_t *pd = (uint64_t*)(p2v(pdpt[pdp_index(virt_addr)]) & ~(4096 - 1));
	uint64_t *pt = (uint64_t*)(p2v(pd[pd_index(virt_addr)]) & ~(4096 - 1));
	uint64_t *page = (uint64_t*)(p2v(pt[pt_index(virt_addr)]) & ~(4096 - 1));

	if (page != NULL)
		return page;
}


/*
 * AuMapPageEx -- Maps a page in external paging structure
 * @param pml4i -- Root paging structure
 * @param physical_address -- Physical address to map
 * @param virtual address -- Virtual address to map to
 * @param attrib -- Extra attributes
 */
bool AuMapPageEx (uint64_t *pml4i,uint64_t physical_address, uint64_t virtual_address, uint8_t attrib){


	size_t flags = 0;
	if (attrib == PAGING_USER)
		flags  = PAGING_PRESENT | PAGING_WRITABLE | PAGING_USER;
	else
		flags = PAGING_PRESENT | PAGING_WRITABLE;

	const long i4 = (virtual_address >> 39) & 0x1FF;
	const long i3 = (virtual_address >> 30) & 0x1FF;
	const long i2 = (virtual_address >> 21) & 0x1FF;
	const long i1 = (virtual_address >> 12) & 0x1FF;

	if (!(pml4i[i4] & PAGING_PRESENT)){
		const uint64_t page = (uint64_t)AuPmmngrAlloc();
		pml4i[i4] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
	}
	uint64_t* pml3 = (uint64_t*)(p2v(pml4i[i4]) & ~(4096 - 1));

	if (!(pml3[i3] & PAGING_PRESENT)){
		const uint64_t page = (uint64_t)AuPmmngrAlloc();
		pml3[i3] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}

	uint64_t* pml2 = (uint64_t*)(p2v(pml3[i3]) & ~(4096 - 1));
	if (!(pml2[i2] & PAGING_PRESENT)){

		const uint64_t page = (uint64_t)AuPmmngrAlloc();
		pml2[i2] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}

	uint64_t* pml1 = (uint64_t*)(p2v(pml2[i2]) & ~(4096 - 1));

	if (pml1[i1] & PAGING_PRESENT){
		AuPmmngrFree((void*)physical_address);
		return false;
	}

	pml1[i1] = physical_address | flags;
	flush_tlb ((void*)virtual_address);
	x64_mfence ();
	return true;
}


/*
 * AuPagingClearLow -- Clears the lower half for 
 * user user
 */
void AuPagingClearLow() {
	uint64_t* cr3 = (uint64_t*)x64_read_cr3();
	for (int i = 0; i < 256; i++)
		cr3[i] = 0;
}

/*
 * AuCreateAddressSpace -- Creates a new address space 
 */
uint64_t *AuCreateAddressSpace (){
	
	uint64_t *cr3 = (uint64_t*)p2v((uint64_t)root_cr3);
	uint64_t *new_cr3 = (uint64_t*)p2v((size_t)AuPmmngrAlloc());
	memset(new_cr3,0,4096);

	//! For now, copy the 4 GiB identity mapping from old pml4
	//! but later, we should avoid this by mapping only those physical
	//! addresses that are needed, like physical addresses allocated for 
	//! paging tables creations and memory mapped I/O which are not
	//! virtually allocated in higher half sections
	//! Copy Kernel's Higher Half section
	for (int i = 0; i < 512; i++) {
		if (i < 256)
			continue;
		if ((cr3[i] & PAGING_PRESENT))
			new_cr3[i] = cr3[i];
		else
			new_cr3[i] = 0;
	}

	return new_cr3;
}

/*
 * AuGetFreePage -- Checks for free page
 * @param size -- UNUSED
 * @param user -- specifies if it needs to look from 
 * user base address
 * @param ptr -- if it is non-null, than lookup
 * begins from given pointer
 */
uint64_t* AuGetFreePage (size_t s, bool user, void* ptr) {
	uint64_t* page = 0;
	uint64_t start = 0;
	if (user) {
		if (ptr)
			start = (uint64_t)ptr;
		else
			start = USER_BASE_ADDRESS;
	}else
		start = KERNEL_BASE_ADDRESS;

	uint64_t* end = 0;
	uint64_t *pml4 = (uint64_t*)p2v(x64_read_cr3());
	
	/* Walk through every page tables */
	for (;;) {
		if (!(pml4[pml4_index(start)] & PAGING_PRESENT))
			return (uint64_t*)start;

		uint64_t *pdpt = (uint64_t*)(p2v(pml4[pml4_index(start)]) & ~(4096 - 1));
		if (!(pdpt[pdp_index(start)] & PAGING_PRESENT))
			return (uint64_t*)start;

		uint64_t *pd = (uint64_t*)(p2v(pdpt[pdp_index(start)]) & ~(4096 - 1));
		if (!(pd[pd_index(start)] & PAGING_PRESENT))
			return (uint64_t*)start;

		uint64_t *pt = (uint64_t*)(p2v(pd[pd_index(start)]) & ~(4096 - 1));

		if (!(pt[pt_index(start)] & PAGING_PRESENT))
			return (uint64_t*)start;
		
		start += 4096;
	}
	return 0;
}


/*
 * AuMapMMIO -- Maps Memory Mapped IO addresses
 * @param phys_addr -- mmio physical address
 * @param page_count -- number of pages
 */
void* AuMapMMIO (uint64_t phys_addr, size_t page_count) {
	uint64_t out = (uint64_t)mmio_base_address;
	for (size_t i = 0; i < page_count; i++) {
		AuMapPage(phys_addr + i * 4096, out + i * 4096,0x04 | 0x08);  //
	}

	uint64_t address = out;
	mmio_base_address = (uint64_t*)(address + (page_count * 4096));

	return (void*)out;
}


uint64_t* AuGetRootPageTable() {
	return root_cr3;
}
