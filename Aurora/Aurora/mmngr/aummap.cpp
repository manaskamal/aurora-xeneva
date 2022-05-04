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
 **/

#include <mmngr\aummap.h>
#include <stdint.h>
#include <arch\x86_64\mmngr\paging.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <mmngr\vma.h>
#include <proc.h>
#include <serial.h>

/**
 * au_mmap -- memory map
 * @param address -- starting address
 * @param length -- length of the mappings
 * @param protect -- protection flags
 * @param flags -- memory map flags
 * @param filedesc -- file descriptor to map
 * @param offset -- offset from where to begin, it should be multiple of PAGE_SIZE
 */
void* au_mmap (void* address, size_t length, int protect, int flags, int filedesc, uint64_t offset) {
	/* this is a system call, so make sure it is atomic */
	x64_cli();

	process_t *proc = get_current_process();
	uint64_t vaddr_start = 0;

	/* Get the starting address */
	if (address == NULL) {
		address = AuGetFreePage(0,true, 0);
		vaddr_start = (uint64_t)address;
	}else 
		vaddr_start = (uint64_t)address;

	vfs_node_t *file = NULL;
	if (filedesc) {
		file = get_current_thread()->fd[filedesc];
	}

	uint64_t size = length / 4096;
	
	if (size == 0)
		size = 1;
	
	au_vm_area_t *vma = (au_vm_area_t*)malloc(sizeof(au_vm_area_t));
	vma->start = vaddr_start;
	vma->end = vma->start + (size * 0x1000);
	vma->file = file;
	vma->offset = offset;
	vma->prot_flags = protect;
	vma->type = VM_TYPE_RESOURCE;
	vma->length = size;
	AuInsertVMArea(proc, vma);

	/* Map it quicky */
	if (vma->file == NULL)
		for (int i = 0; i < size; i++) {
			AuMapPage((uint64_t)AuPmmngrAlloc(), vma->start + i * 4096, PAGING_USER);
		}
	return address;
}