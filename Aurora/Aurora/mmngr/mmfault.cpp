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

#include <mmngr\mmfault.h>
#include <proc.h>
#include <mmngr\vma.h>
#include <fs\fat\fat.h>
#include <serial.h>

/*
 * AuHandlePageNotPresent -- Handle not present
 * pages
 */
void AuHandlePageNotPresent (uint64_t vaddr, bool user, void* param) {
	x64_cli();
	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;
	if (!user) {
		x64_cli();
		printf ("Kernel Panic!! Page fault \n");
		printf ("Virtual address -> %x \n", vaddr);
		printf ("RIP ->%x \n", frame->rip);
		printf ("Current thread -> %s \n", get_current_thread()->name);
		for(;;);
	}
	au_vm_area_t *vm = AuFindVMA(vaddr);
	if (vm == NULL){
		x64_cli();
		printf ("Page Fault -> %x \n", vaddr);
		printf ("RIP -> %x \n", frame->rip);
		printf ("Current thread -> %s \n", get_current_thread()->name);
		for(;;);
		return;
	}

	for (int i = 0; i < vm->length; i++) {
		void* phys_addr = AuPmmngrAlloc();
		if (vm->file && vm->file->eof != 1) {
			fat32_read(vm->file, (uint64_t*)phys_addr);
		}
		AuMapPage((uint64_t)phys_addr, vaddr, PAGING_USER);
	}
}