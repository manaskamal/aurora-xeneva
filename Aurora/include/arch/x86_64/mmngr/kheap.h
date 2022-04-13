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
**/

#ifndef __KMALLOC_H__
#define __KMALLOC_H__

#include <stdint.h>
#include <_null.h>
#include <string.h>
#include <arch\x86_64\mmngr\vmmngr.h>
#include <pmmngr.h>

/* Meta data magic */
#define MAGIC_USED  0x12112002
#define MAGIC_FREE  0x16062002

typedef struct _meta_data_ {
	uint32_t magic;
	size_t   size;
	bool     free;
	uint8_t*   eob_mark;
	_meta_data_ *next;
	_meta_data_ *prev;
}meta_data_t;


/*
* x86_64_kmalloc_initialize -- initialize
* kernel malloc library with two pages
*/
extern void heap_initialize();

/*
* au_request_page -- request contiguous 4k virtual pages
* @param pages -- number of pages needs to be mapped
*/
extern uint64_t* au_request_page(int pages);

/*
* au_free_page -- frees up pages, note that pages
* are needed to be 4k and contiguous
* @param ptr -- pointer to the first page
* @param pages --pages -- number of pages
*/
extern void au_free_page(void* ptr, int pages);

/*
* kmalloc -- allocate a small chunk of memory
* @param size -- size in bytes
*/
extern void* malloc(size_t size);

/*
* free up a pointer
*@param ptr -- pointer to the address block to free
*/
extern void free(void* ptr);

/*
* krealloc -- reallocate a block from the old block
* @param ptr -- pointer to the old block
* @param new_size -- size of the new block
*/
extern void* realloc(void* ptr, size_t new_size);

/*
* kcalloc -- allocates a memory filled with zeroes
* @param n_item -- number of items
* @param size -- size of each items
*/
extern void* calloc(size_t n_item, size_t size);

#endif