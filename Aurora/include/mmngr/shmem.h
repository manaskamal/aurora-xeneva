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

#ifndef __SHMEM_H__
#define __SHMEM_H__

#include <stdio.h>
#include <stdint.h>
#include <arch\x86_64\thread.h>

typedef struct _shared_mem_ {
	uint32_t id;
	void* ptr;
	uint32_t key;
	size_t size;
	uint8_t flags;
	uint32_t num_frames;
	uint16_t link_count;
	thread_t* map_in_thread;
	void *first_process_vaddr;
}shared_mem_t;


/*
 * AuInitializeShMem -- initialize the shared memory manager
 */
extern void AuInitializeShMem ();

/*
 * AuCreateShMem -- Create a shared memory object
 */
extern uint32_t AuCreateShMem (uint32_t key,size_t size, uint32_t flags);

/*
 * Obtain Shared Memory for this process 
 * @param key -- Unique Key identifier
 * @param shmaddr -- address to map, if NULL, Aurora will choose
 * the address
 * @param shmflg -- shared memory flags
 */
extern void* AuObtainShMem (uint32_t key, void * shmaddr, int shmflg);

/*
 * Unlinks a shared memory 
 * @param key -- unique key id
 */
extern void shm_unlink (uint32_t key);

/*
 * shm_unlink_direct -- removes the shared memory directly without
 * waiting for the clients to unlink
 * @param key -- shared memory chunk key
 */
extern void shm_unlink_direct (uint32_t key);
#endif