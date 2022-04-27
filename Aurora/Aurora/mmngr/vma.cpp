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

#include <mmngr\vma.h>
#include <proc.h>
#include <arch\x86_64\mmngr\kheap.h>

/*
 * AuInsertVMArea -- Insert vm area object to given process
 * @param proc -- process where to insert vm object
 * @param vma -- vm area
 */
void AuInsertVMArea(process_t *proc, au_vm_area_t *vma) {
	vma->next = NULL;
	vma->prev = NULL;

	if (proc->vma_area == NULL){
		proc->vma_area = vma;
		proc->last_vma = proc->vma_area;
	}else {
		proc->last_vma->next = vma;
		vma->prev = proc->last_vma;
		proc->last_vma = vma;
	}
}

/*
 * AuRemoveVMArea -- Remove vm area object from given process
 * @param proc -- process from where to remove
 * @param vma -- vm area object
 */
void AuRemoveVMArea (process_t *proc, au_vm_area_t *vma) {
	if (proc->vma_area == NULL)
		return;

	if (vma == proc->vma_area) {
		proc->vma_area = proc->vma_area->next;
	} else {
		vma->prev->next = vma->next;
	}

	if (vma == proc->last_vma) {
		proc->last_vma = vma->prev;
	} else {
		vma->next->prev = vma->prev;
	}

	free(vma);
}

/*
 * AuFindVMA -- finds a vm region
 * @param address -- address to search
 */
au_vm_area_t *AuFindVMA (uint64_t address) {
	process_t *proc = get_current_process();
	for (au_vm_area_t *vma = proc->vma_area; vma != NULL; vma = vma->next) {
		if (address >= vma->start && address <= vma->end){
			return vma;
		}
	}
	return NULL;
}
