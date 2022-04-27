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

#include <sys\mmap.h>
#include <stdlib.h>


/* 
 * mmap_params_t -- memory mappings
 * parameters
 */
typedef struct _mmap_params_ {
	int protect;
	int flags;
	int filedesc;
	uint64_t offset;
}mmap_params_t;

/**
 * au_mmap -- memory map
 * @param address -- starting address
 * @param length -- length of the mappings
 * @param protect -- protection flags
 * @param flags -- memory map flags
 * @param filedesc -- file descriptor to map
 * @param offset -- offset from where to begin, it should be multiple of PAGE_SIZE
 */
void* mmap(void* address, size_t length, int protect, int flags, int filedesc, uint64_t offset){
	valloc(0x10000);
	mmap_params_t* params = (mmap_params_t*)0x10000;
	params->protect = protect;
	params->flags = flags;
	params->filedesc = filedesc;
	params->offset = offset;
	void* ptr = sys_mmap(address, length, params);
	vfree(0x10000);
	return ptr;
}