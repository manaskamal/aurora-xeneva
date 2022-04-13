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

#include <arch\x86_64\mmngr\vmmngr.h>
#include <screen.h>
#include <ipc\dwm_ipc.h>
#include <arch\x86_64\thread.h>
#include <pmmngr.h>
#include <serial.h>


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
 * Initialize Virtual Memory Setup
 */
void vmmngr_x86_64_init () {

	uint64_t *cr3 = (uint64_t*)x64_read_cr3();
	uint64_t *new_cr3 = (uint64_t*)pmmngr_alloc();    

	memset (new_cr3, 0, 4096);

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

	uint64_t* pdpt = (uint64_t*)pmmngr_alloc();
	memset(pdpt, 0, 4096);

	new_cr3[pml4_index(PHYSICAL_MEMORY_BASE)] = (uint64_t)pdpt | PAGING_PRESENT | PAGING_WRITABLE;

	for (size_t i = 0; i < 512; i++)
		pdpt[pdp_index(PHYSICAL_MEMORY_BASE) + i] = i * 512 * 512 * 4096 | 0x80 | PAGING_PRESENT | PAGING_WRITABLE;

	//! Store the kernel's address space
	root_cr3 = new_cr3;

	//! Switch to new mapping!!!
	x64_write_cr3 ((size_t)new_cr3);

	pmmngr_move_higher_half();

}


//! Map a page in current address space
bool map_page (uint64_t physical_address, uint64_t virtual_address, uint8_t attrib){
	size_t flags = PAGING_WRITABLE | PAGING_PRESENT | attrib;
	
	const long i4 = (virtual_address >> 39) & 0x1FF;
	const long i3 = (virtual_address >> 30) & 0x1FF;
	const long i2 = (virtual_address >> 21) & 0x1FF;
	const long i1 = (virtual_address >> 12) & 0x1FF;

	uint64_t *pml4i = (uint64_t*)p2v(x64_read_cr3());

	if (!(pml4i[i4] & PAGING_PRESENT))
	{
		
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml4i[i4] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
	}
	uint64_t* pml3 = (uint64_t*)(p2v(pml4i[i4]) & ~(4096 - 1));
	
	if (!(pml3[i3] & PAGING_PRESENT))
	{
		
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml3[i3] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}
    
	
	uint64_t* pml2 = (uint64_t*)(p2v(pml3[i3]) & ~(4096 - 1));
	
	if (!(pml2[i2] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml2[i2] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}
	
	uint64_t* pml1 = (uint64_t*)(p2v(pml2[i2]) & ~(4096 - 1));
	if (pml1[i1] & PAGING_PRESENT)
	{
		pmmngr_free((void*)physical_address);
		return false;
	}

	pml1[i1] = physical_address | flags;
	flush_tlb ((void*)virtual_address);
	x64_mfence ();
	return true;
}


void unmap_page(uint64_t virt_addr){
	
	const long i1 = pml4_index(virt_addr);

	uint64_t *pml4_ = (uint64_t*)x64_read_cr3();
	uint64_t *pdpt = (uint64_t*)(pml4_[pml4_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pd = (uint64_t*)(pdpt[pdp_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pt = (uint64_t*)(pd[pd_index(virt_addr)] & ~(4096 - 1));
	uint64_t *page = (uint64_t*)(pt[pt_index(virt_addr)] & ~(4096 - 1));
	
	if ((pt[pt_index(virt_addr)] & PAGING_PRESENT) != 0) {
		
		pt[pt_index(virt_addr)] = 0;
	}
	if (page != 0)
		pmmngr_free(page);
}


void unmap_page_ex(uint64_t* cr3, uint64_t virt_addr, bool free_physical){
	
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
		pmmngr_free(page);

}


void vmmngr_free_pages(uint64_t virt_addr, bool free_physical, size_t s){
	
	const long i1 = pml4_index(virt_addr);

	for (int i = 0; i < s /  4096; i++) {
		uint64_t *pml4_ = (uint64_t*)x64_read_cr3();
		uint64_t *pdpt = (uint64_t*)(pml4_[pml4_index(virt_addr)] & ~(4096 - 1));
		uint64_t *pd = (uint64_t*)(pdpt[pdp_index(virt_addr)] & ~(4096 - 1));
		uint64_t *pt = (uint64_t*)(pd[pd_index(virt_addr)] & ~(4096 - 1));
		uint64_t *page = (uint64_t*)(pt[pt_index(virt_addr)] & ~(4096 - 1));

		if ((pt[pt_index(virt_addr)] & PAGING_PRESENT) != 0) {
			pt[pt_index(virt_addr)] = 0;
		}

		if (free_physical && page != 0) 
			pmmngr_free(page);

		virt_addr = virt_addr + i * 4096;
	}

}


//! returns a physical address from virtual address
uint64_t* get_physical_address (uint64_t virt_addr) {
	const long i1 = pml4_index(virt_addr);

	uint64_t *pml4 = (uint64_t*)x64_read_cr3();
	uint64_t *pdpt = (uint64_t*)(pml4[pml4_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pd = (uint64_t*)(pdpt[pdp_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pt = (uint64_t*)(pd[pd_index(virt_addr)] & ~(4096 - 1));
	uint64_t *page = (uint64_t*)(pt[pt_index(virt_addr)] & ~(4096 - 1));

	if (page != NULL)
		return page;
}



bool map_page_ex (uint64_t *pml4i,uint64_t physical_address, uint64_t virtual_address, uint8_t attrib){


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
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml4i[i4] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
	}
	uint64_t* pml3 = (uint64_t*)(p2v(pml4i[i4]) & ~(4096 - 1));

	if (!(pml3[i3] & PAGING_PRESENT)){
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml3[i3] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}

	uint64_t* pml2 = (uint64_t*)(p2v(pml3[i3]) & ~(4096 - 1));
	if (!(pml2[i2] & PAGING_PRESENT)){

		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml2[i2] = page | flags;
		clear((void*)p2v(page));
		flush_tlb((void*)page);
		x64_mfence();
		
	}

	uint64_t* pml1 = (uint64_t*)(p2v(pml2[i2]) & ~(4096 - 1));

	if (pml1[i1] & PAGING_PRESENT){
		pmmngr_free((void*)physical_address);
		return false;
	}

	pml1[i1] = physical_address | flags;
	flush_tlb ((void*)virtual_address);
	x64_mfence ();
	return true;
}



//! creates a new address space for user with same structure
//! to kernel i.e clone kernel space
uint64_t *create_user_address_space (){
	
	uint64_t *cr3 = (uint64_t*)root_cr3; //x64_read_cr3();
	uint64_t *new_cr3 = (uint64_t*)p2v((size_t)pmmngr_alloc());
	memset(new_cr3,0,4096);

	//! For now, copy the 4 GiB identity mapping from old pml4
	//! but later, we should avoid this by mapping only those physical
	//! addresses that are needed, like physical addresses allocated for 
	//! paging tables creations and memory mapped I/O which are not
	//! virtually allocated in higher half sections
	new_cr3[0] = cr3[0];
	new_cr3[1] = cr3[1];
	new_cr3[2] = cr3[2];
	new_cr3[3] = cr3[3];

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


uint64_t* get_free_page (size_t s, bool user) {
	uint64_t* page = 0;
	uint64_t start = 0;
	if (user)
		start = USER_BASE_ADDRESS;
	else
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


uint64_t* vmmngr_get_kernel_pml4() {
	return root_cr3;
}
