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

//================================================
// M E M O R Y   M A P 
//================================================
/*
 * FFFFC00000000000 - FFFFD00000000000   - Kernel
 * FFFF800000000000 - FFFF900000000000   - Kernel Heap
 * FFFFA00000200000 - FFFFB00000000000   - Paged Pool
 * 0000400000000000 - 0000500000000000   - User Space
 */

#define KERNEL_BASE_ADDRESS  0xFFFFE00000000000
#define USER_BASE_ADDRESS 0x0000400000000000
uint64_t* root_cr3;

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
	uint64_t *pdpt = (uint64_t*)pmmngr_alloc();
	uint64_t *pd = (uint64_t*)pmmngr_alloc();
	uint64_t *pd2 = (uint64_t*)pmmngr_alloc();
	uint64_t *pd3 = (uint64_t*)pmmngr_alloc();
	uint64_t *pd4 = (uint64_t*)pmmngr_alloc();


	memset (new_cr3, 0, 4096);
	memset (pd, 0, 4096);
	memset (pd2, 0, 4096);
	memset (pd3, 0, 4096);
	memset (pd4, 0, 4096);

	//! Identity Map : first 4 GiB of RAM
    new_cr3[0] = (uint64_t)pdpt | 0x3;
	pdpt[0] =  (uintptr_t)&pd[0] | 0x3;
	pdpt[1] = (uintptr_t)&pd2[0] | 0x3;
	pdpt[2] = (uintptr_t)&pd3[0] | 0x3;
	pdpt[3] = (uintptr_t)&pd4[0] | 0x3;

	for (uint64_t i = 0; i != 2048; ++i)
		pd[i] = i * 512 * 4096 | 0x83;

	uint64_t pos = 1024*1024*1024;
	for (uint64_t i = 0; i != 512; ++i)
		pd2[i] = pos + i * 512 * 4096 | 0x83;

	for (uint64_t i = 0; i != 512; ++i)
		pd3[i] = 2*pos + i * 512 * 4096 | 0x83;

	for (uint64_t i = 0; i != 512; ++i)
		pd4[i] = 3*pos + i * 512 * 4096 | 0x83;



	///! Copy all higher half mappings to new mapping
	for (int i = 0; i < 512; ++i) {
		if (i < 256) {
			//new_cr3[i] = 0;
			continue;
		}
		if (i == 511)
			continue;

		if (cr3[i] & PAGING_PRESENT) {
			new_cr3[i] = cr3[i];
		}else {
			new_cr3[i] = 0;
		}
		
	}

	//! Switch to new mapping!!!
	x64_write_cr3 ((size_t)new_cr3);
}


//! Map a page in current address space
bool map_page (uint64_t physical_address, uint64_t virtual_address, uint8_t attrib)
{
	size_t flags = PAGING_WRITABLE | PAGING_PRESENT | attrib;

	const long i4 = (virtual_address >> 39) & 0x1FF;
	const long i3 = (virtual_address >> 30) & 0x1FF;
	const long i2 = (virtual_address >> 21) & 0x1FF;
	const long i1 = (virtual_address >> 12) & 0x1FF;

	uint64_t *pml4i = (uint64_t*)x64_read_cr3();
	if (!(pml4i[i4] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml4i[i4] = page | flags;
		clear((void*)page);
		flush_tlb((void*)page);
		x64_mfence();
	}
	uint64_t* pml3 = (uint64_t*)(pml4i[i4] & ~(4096 - 1));
	
	if (!(pml3[i3] & PAGING_PRESENT))
	{
		
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml3[i3] = page | flags;
		clear((void*)page);
		flush_tlb((void*)page);
		x64_mfence();
		
	}
    
	
	uint64_t* pml2 = (uint64_t*)(pml3[i3] & ~(4096 - 1));
	
	if (!(pml2[i2] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml2[i2] = page | flags;
		clear((void*)page);
		flush_tlb((void*)page);
		x64_mfence();
		
	}
	
	uint64_t* pml1 = (uint64_t*)(pml2[i2] & ~(4096 - 1));
	if (pml1[i1] & PAGING_PRESENT)
	{
		return false;
	}

	pml1[i1] = physical_address | flags;
	flush_tlb ((void*)virtual_address);
	x64_mfence ();
	return true;
}


bool vmmngr_update_flags (uint64_t virtual_address, size_t flags_){

	uint64_t phys_addr = (uint64_t)get_physical_address (virtual_address);

	size_t flags = PAGING_WRITABLE | PAGING_PRESENT | PAGING_USER;

	const long i4 = (virtual_address >> 39) & 0x1FF;
	const long i3 = (virtual_address >> 30) & 0x1FF;
	const long i2 = (virtual_address >> 21) & 0x1FF;
	const long i1 = (virtual_address >> 12) & 0x1FF;

	uint64_t *pml4i = (uint64_t*)x64_read_cr3();
	if (!(pml4i[i4] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml4i[i4] = page | flags;
		clear((void*)page);
		flush_tlb((void*)page);
		x64_mfence();
	}
	uint64_t* pml3 = (uint64_t*)(pml4i[i4] & ~(4096 - 1));
	if (!(pml3[i3] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml3[i3] = page | flags;
		clear((void*)page);
		flush_tlb((void*)page);
		x64_mfence();
		
	}

	uint64_t* pml2 = (uint64_t*)(pml3[i3] & ~(4096 - 1));
	if (!(pml2[i2] & PAGING_PRESENT))
	{
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml2[i2] = page | flags;
		clear((void*)page);
		flush_tlb((void*)page);
		x64_mfence();
		
	}
	uint64_t* pml1 = (uint64_t*)(pml2[i2] & ~(4096 - 1));
	if (pml1[i1] & PAGING_PRESENT)
	{
		return false;
	}

	pml1[i1] = phys_addr | flags;
	flush_tlb ((void*)virtual_address);
	x64_mfence ();
	return true;
}

void unmap_page(uint64_t virt_addr){
	
	const long i1 = pml4_index(virt_addr);

	uint64_t *pml4 = (uint64_t*)x64_read_cr3();
	uint64_t *pdpt = (uint64_t*)(pml4[pml4_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pd = (uint64_t*)(pdpt[pdp_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pt = (uint64_t*)(pd[pd_index(virt_addr)] & ~(4096 - 1));
	uint64_t *page = (uint64_t*)(pt[pt_index(virt_addr)] & ~(4096 - 1));

	uint64_t *pml = (uint64_t*)x64_read_cr3();
	if (pml[i1] & PAGING_PRESENT){
		pml[i1] = 0;
	}

	pmmngr_free(page);
}


void unmap_page_ex(uint64_t* cr3, uint64_t virt_addr, bool free_physical){
	
	const long i1 = pml4_index(virt_addr);

	uint64_t *pml4 = cr3;
	uint64_t *pdpt = (uint64_t*)(pml4[pml4_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pd = (uint64_t*)(pdpt[pdp_index(virt_addr)] & ~(4096 - 1));
	uint64_t *pt = (uint64_t*)(pd[pd_index(virt_addr)] & ~(4096 - 1));
	uint64_t *page = (uint64_t*)(pt[pt_index(virt_addr)] & ~(4096 - 1));

	uint64_t *pml = cr3;
	if (pml[i1] & PAGING_PRESENT){
		pml[i1] = 0;
	}

	if (free_physical)
		pmmngr_free(page);
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

	size_t flags = PAGING_WRITABLE | PAGING_PRESENT | attrib;

	const long i4 = (virtual_address >> 39) & 0x1FF;
	const long i3 = (virtual_address >> 30) & 0x1FF;
	const long i2 = (virtual_address >> 21) & 0x1FF;
	const long i1 = (virtual_address >> 12) & 0x1FF;

	if (!(pml4i[i4] & PAGING_PRESENT)){
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml4i[i4] = page | flags;
		clear((void*)page);
		flush_tlb((void*)page);
		x64_mfence();
	}
	uint64_t* pml3 = (uint64_t*)(pml4i[i4] & ~(4096 - 1));

	if (!(pml3[i3] & PAGING_PRESENT)){
		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml3[i3] = page | flags;
		clear((void*)page);
		flush_tlb((void*)page);
		x64_mfence();
		
	}

	uint64_t* pml2 = (uint64_t*)(pml3[i3] & ~(4096 - 1));
	if (!(pml2[i2] & PAGING_PRESENT)){

		const uint64_t page = (uint64_t)pmmngr_alloc();
		pml2[i2] = page | flags;
		clear((void*)page);
		flush_tlb((void*)page);
		x64_mfence();
		
	}

	uint64_t* pml1 = (uint64_t*)(pml2[i2] & ~(4096 - 1));

	if (pml1[i1] & PAGING_PRESENT){
		//printf ("Paging already present -> %x\n", virtual_address);
		return false;
	}

	pml1[i1] = physical_address | flags;
	flush_tlb ((void*)virtual_address);
	x64_mfence ();
	return true;
}



//! creates a new address space for user with same structure
//! to kernel i.e clone kernel space
uint64_t *create_user_address_space ()
{
	
	uint64_t *cr3 = (uint64_t*)x64_read_cr3();
	uint64_t *new_cr3 = (uint64_t*)pmmngr_alloc();
	new_cr3[0] = cr3[0];
	new_cr3[pml4_index(0xFFFFC00000000000)] = cr3[pml4_index(0xFFFFC00000000000)];
	new_cr3[pml4_index(0xFFFFA00000000000)] = cr3[pml4_index(0xFFFFA00000000000)];
	new_cr3[pml4_index(0xFFFF800000000000)] = cr3[pml4_index(0xFFFF800000000000)];
	new_cr3[pml4_index(0xFFFFE00000000000)] = cr3[pml4_index(0xFFFFE00000000000)];
	new_cr3[pml4_index(0xFFFFD00000000000)] = cr3[pml4_index(0xFFFFE00000000000)];

	//map_page_ex (new_cr3,(uint64_t)new_cr3,(uint64_t)new_cr3, 0);
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
	uint64_t *pml4 = (uint64_t*)x64_read_cr3();
	for (int i = 0; i < s; i++) {
		uint64_t *pdpt = (uint64_t*)(pml4[pml4_index(start)] & ~(4096 - 1));
	    uint64_t *pd = (uint64_t*)(pdpt[pdp_index(start)] & ~(4096 - 1));
		uint64_t *pt = (uint64_t*)(pd[pd_index(start)] & ~(4096 - 1));
		uint64_t *page = (uint64_t*)(pt[pt_index(start)] & ~(4096 - 1));

		if ((pt[pt_index(start)] & PAGING_PRESENT) == 0){
			return (uint64_t*)start;
		}
		start+= 4096;
	}
	return 0;
}


uint64_t* vmmngr_get_kernel_pml4() {
	return root_cr3;
}
