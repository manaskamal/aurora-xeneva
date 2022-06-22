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
 *
 *
 **/

#include <arch\x86_64\kstack.h>
#include <string.h>
#include <stdio.h>
#include <serial.h>


/*
 * allocate_kstack -- allocates a kernel stack
 * @param cr3 -- destination cr3
 */
uint64_t allocate_kstack (uint64_t *cr3) {
	uint64_t location = KSTACK_START; 
	for (int i = 0; i < 8192/4096; i++) {
		void* p = AuPmmngrAlloc();
		AuMapPageEx (cr3,(uint64_t)p,location + i * 4096, 0);
	}
	
	return (KSTACK_START + 8192);
}


void free_kstack (uint64_t *cr3) {
	uint64_t location = KSTACK_START; 
	/* 
	 * Here kernel stack is not directly unmapped
	 * because untill we call force_sched() the system 
	 * will be using kstack, rather we just get the
	 * physical addresses and free them using physical 
	 * mmngr
	 */
	for (int i = 0; i < 8192 / 4096; i++) {
		void* p = AuGetPhysicalAddress((size_t)cr3,location + i * 4096);
		AuPmmngrFree((void*)v2p((size_t)p));
	}
}


/*
 * Allocate's stack for child threads
 * @param -- parent thread Address Space
 */
uint64_t allocate_kstack_child (uint64_t *cr3) {
	uint64_t location = (uint64_t)AuGetFreePage(0,true,(void*)KSTACK_START);
	for (int i = 0; i < 8192/4096; i++) {
		void* p = AuPmmngrAlloc();
		AuMapPageEx (cr3,(uint64_t)p,location + i * 4096, 0);
	}
	
	return (location + 8192);
}

/*
 * free_kstack_child -- free up child kernel stacks
 * @param cr3 -- Parent thread address space
 * @param location -- start of stack address
 */
void free_kstack_child (uint64_t *cr3, uint64_t location) {
	for (int i = 0; i < 8192 / 4096; i++) {
		void* p = AuGetPhysicalAddress((size_t)cr3,location + i * 4096);
		AuPmmngrFree((void*)v2p((size_t)p));
	}
}
