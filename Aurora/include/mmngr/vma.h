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

#ifndef __VMA_H__
#define __VMA_H__

#include <stdint.h>
#include <arch\x86_64\thread.h>
#include <fs\vfs.h>

#define VM_READ   0x0001
#define VM_WRITE  0x0002
#define VM_EXEC   0x0004
#define VM_SHARED 0x0008

#define VM_TYPE_TEXT  1
#define VM_TYPE_DATA  2
#define VM_TYPE_STACK 3
#define VM_TYPE_HEAP  4
#define VM_TYPE_RESOURCE 5

/* au_vm_area_t -- Virtual Memory Regions */
typedef struct _vma_area_ {
	uint64_t  start;
	uint64_t  end;
	uint16_t  prot_flags;
	vfs_node_t *file;
	uint64_t  offset;
	size_t    length;
	char      type;
	struct _vma_area_ *next;
	struct _vma_area_ *prev;
}au_vm_area_t;


#endif