/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
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

#ifndef __SHM_H__
#define __SHM_H__

#include <stdint.h>
#include <sys\_xeneva.h>

/*
 * sys_shmget -- Create a shared memory object
 */
XE_EXTERN XE_EXPORT uint32_t sys_shmget (uint32_t key,size_t size, uint32_t flags);

/*
 * Obtain Shared Memory for this process 
 * @param key -- Unique Key identifier
 * @param shmaddr -- address to map, if NULL, Aurora will choose
 * the address
 * @param shmflg -- shared memory flags
 */
XE_EXTERN XE_EXPORT void* sys_shmat (uint32_t key, void * shmaddr, int shmflg);


/*
 * unlink the shared memory segment
 * @param key -- key identifier
 */
XE_EXTERN XE_EXPORT void sys_shm_unlink(uint32_t key);

/*
 * unlink the shared memory segment without waiting for the
 * clients to disconnect
 * @param key -- shared memory segment key
 */
XE_EXTERN XE_EXPORT void sys_shm_unlink_direct(uint32_t key);
#endif