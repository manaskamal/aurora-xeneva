/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
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
 * @shmem -- Shared Memory Management
 * /PROJECT - Aurora Kernel
 *
 **/

#include <mmngr\shmem.h>
#include <utils\lnklist.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <proc.h>
#include <serial.h>

list_t *shared_mem_list;
uint32_t sh_id;

/*
 * AuInitializeShMem -- initialize the shared memory manager
 */
void AuInitializeShMem () {
	shared_mem_list = initialize_list();
	sh_id = 1;
}


/*
 * AuCreateShMem -- Create a shared memory object
 */
uint32_t AuCreateShMem (uint32_t key,size_t size, uint32_t flags) {
	x64_cli();
	for (int i = 0; i < shared_mem_list->pointer; i++) {
		shared_mem_t *mem = (shared_mem_t*)list_get_at(shared_mem_list, i);
		if (mem->key == key)
			return mem->id;
	}
	shared_mem_t *sh_mem = (shared_mem_t*)malloc(sizeof(shared_mem_t));
	memset(sh_mem, 0, sizeof(shared_mem_t));
	sh_mem->id = sh_id;
	sh_mem->ptr = 0;
	sh_mem->key = key;
	sh_mem->size = size;
	sh_mem->num_frames = (size / 4096);
	sh_mem->map_in_thread = NULL;
	sh_mem->first_process_vaddr = NULL;
	list_add(shared_mem_list, sh_mem);
	sh_id++;
	return sh_mem->id;
}

/*
 * Obtain Shared Memory for this process 
 * @param key -- Unique Key identifier
 * @param shmaddr -- address to map, if NULL, Aurora will choose
 * the address
 * @param shmflg -- shared memory flags
 */
void* AuObtainShMem (uint32_t id, void * shmaddr, int shmflg) {
	x64_cli();
	shared_mem_t *mem = NULL;
	for (int i = 0; i < shared_mem_list->pointer; i++) {
		mem = (shared_mem_t*)list_get_at(shared_mem_list, i);
		if (mem->id == id){
			break;
		}
	}

	void* ret_addre = NULL;
	/* Shared memory was already mapped so, 
	 * lets copy the physical frames from that process's
	 * address space */
	if (mem->map_in_thread) {
		uint64_t cr3 = mem->map_in_thread->cr3;
		uint64_t virtual_addr = (uint64_t)mem->first_process_vaddr;
		/*Now we have the first virtual address, lets map in */
		for (int i = 0; i < mem->num_frames; i++) {
			uint64_t *phys_addr = (uint64_t*)AuGetPhysicalAddress(cr3,virtual_addr + i * 4096);
			uint64_t current_virt = (uint64_t)AuGetFreePage(0,true, 0);
			AuMapPage(v2p((uint64_t)phys_addr),current_virt,PAGING_USER);
			if (ret_addre == NULL)
				ret_addre = (void*)current_virt;
		}
	}else {
		/* No process has mapped the shared memory, let this process's
		   thread map in some memory for other process to use */
		mem->map_in_thread = get_current_thread();

		/* Allocate some memory for this process */
		for (int i = 0; i < mem->num_frames; i++) {
			void* p = AuPmmngrAlloc();
			uint64_t virt = (uint64_t)AuGetFreePage(0,true, 0);
			AuMapPage ((uint64_t)p,virt, PAGING_USER);

			/* Store the first virtual address */
			if (mem->first_process_vaddr == NULL)
				mem->first_process_vaddr = (void*)virt;
		}
		ret_addre = mem->first_process_vaddr;
	}

	return ret_addre;
}