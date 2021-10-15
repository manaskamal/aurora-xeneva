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


void vmmngr_x86_64_init () {
	//! FIXME: pml4 address should be relocatable
	//! FIXME: the address assigned should be 4 KB aligned
	uint64_t * pml4 = (uint64_t*)pmmngr_alloc(); 
	uint64_t* old_pml4 = (uint64_t*)x64_read_cr3();
	root_cr3 = pml4;
	//! just copy the paging structure setuped by XNLDR 
	//! for the kernel! also known as kernel address space
	for (int i = 0; i < 512; i++) {
		if ((old_pml4[i] & 1) == 1)
			pml4[i] = old_pml4[i];
	}

	x64_write_cr3((size_t)pml4);
}


//! Map a page in current address space
bool map_page (uint64_t physical_address, uint64_t virtual_address)
{
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
	//if (pml1[i1] & PAGING_PRESENT)
	//{
	//	printf ("Paging present\n");
	//	return false;
	//}

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
		printf ("Address already present\n");
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


void unmap_page_ex(uint64_t* cr3, uint64_t virt_addr){
	
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



bool map_page_ex (uint64_t *pml4i,uint64_t physical_address, uint64_t virtual_address){

	size_t flags = PAGING_WRITABLE | PAGING_PRESENT | PAGING_USER;

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
		//printf ("Paging present\n");
		//return false;
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
	
	uint64_t* pml4_i = (uint64_t*)pmmngr_alloc(); 
	uint64_t* old_pml4 = (uint64_t*)x64_read_cr3(); //root_cr3;

	memset (pml4_i, 0, 4096);
	//! copy the 0 and 1 entries from old address space to new one
	/*for (int i = 0; i < 512; i++) {
		if ((old_pml4[i] & 1) == 1)
			pml4_i[i] = old_pml4[i];
	}
*/
	pml4_i[0] = old_pml4[0];
	pml4_i[1] = old_pml4[1];
	//!**Copy the kernel stack to new address space
	for (int i=0; i < 0x200000/4096; i++)
		pml4_i[pml4_index(0xFFFFA00000000000 + i *4096) ] = old_pml4[pml4_index(0xFFFFA00000000000 + i *4096) ];
	
	//! copy the entire kernel to new address space {180kb kernel size}
	for (int i=0; i < 0x100000/4096; i++)  {
		pml4_i[pml4_index(0xFFFFC00000000000 + i*4096)] = old_pml4[pml4_index(0xFFFFC00000000000 + i*4096)];
	}

	////
	for (int i=0; i < get_screen_width() * get_screen_height() * 32 / 4096; i++) 
		pml4_i[pml4_index(0xFFFFF00000000000 + i * 4096)] = old_pml4[pml4_index(0xFFFFF00000000000 + i * 4096)];
	//
	//////! copy the kernel heap area to new address space
	for (int i=0; i < 0x200000/4096; i++) 
		pml4_i[pml4_index(0xFFFF800000000000 + i*4096)] = old_pml4[pml4_index(0xFFFF800000000000 + i*4096)];
	

	pml4_i[pml4_index(0xFFFFFD0000000000)] = old_pml4[pml4_index(0xFFFFFD0000000000)];
	pml4_i[pml4_index(0xFFFFD00000000000)] = old_pml4[pml4_index(0xFFFFD00000000000)];
	//! copy the user stack area to new address space
	//pml4_i[511] = *pml4_i | PAGING_PRESENT | PAGING_WRITABLE;
	//! return the new address space governor
	return pml4_i;
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
