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

#include <arch\x86_64\mmngr\kheap.h>
#include <stdio.h>
#include <serial.h>

meta_data_t *first_block = NULL;
meta_data_t *last_block = NULL;
uint8_t* last_mark = NULL;

/*
 * AuHeapInitialize -- initialize
 * kernel malloc library with four pages (16KiB)
 */
void AuHeapInitialize() {
	uint64_t* page = au_request_page(1);
	memset(page, 0, (1*4096));
	/* setup the first meta data block */
	uint8_t* desc_addr = (uint8_t*)page;
	meta_data_t *meta = (meta_data_t*)desc_addr;
	meta->free = true;
	meta->next = NULL;
	meta->prev = NULL;
	meta->magic = MAGIC_FREE;
	/* meta->size holds only the usable area size for user */
	meta->size = (1*4096) - sizeof(meta_data_t);
	first_block = meta;
	last_block = meta;
	uint64_t lm = (uint64_t)page;
	last_mark = (uint8_t*)(lm + (1*4096));
}
/* 
 * au_split_block -- split block into two block
 */
int au_split_block(meta_data_t* meta_block, size_t req_size) {
	uint8_t* meta_block_a = (uint8_t*)meta_block;	
	
	if (meta_block->size <= sizeof(meta_data_t))
		return 0;

	meta_data_t* new_block = (meta_data_t*)(meta_block_a + sizeof(meta_data_t) + req_size);
	size_t size =  meta_block->size - req_size - sizeof(meta_data_t);
	if ((((uint8_t*)new_block + sizeof(meta_data_t)) > last_mark)) {
		return 0;
	}

	new_block->free = true;
	new_block->magic = MAGIC_FREE;
	new_block->prev = meta_block;
	new_block->next = meta_block->next;
	if (meta_block->next != NULL)
		meta_block->next->prev = new_block;

	new_block->size = meta_block->size - req_size - sizeof(meta_data_t);
	if (new_block->size <= sizeof(meta_data_t)) {
		new_block->free = false;
	}
	
	meta_block->size = req_size + sizeof(meta_data_t);
	meta_block->next = new_block;
	last_block = new_block;

	return 1;
}


void au_expand_kmalloc(size_t req_size) {
	size_t req_pages = 1;
	if (req_size >= 4096)
		req_pages = (req_size + sizeof(meta_data_t)) / 4096 + 1;

	void* page = au_request_page(req_pages);
	uint8_t* desc_addr = (uint8_t*)page;
	/* setup the first meta data block */
	meta_data_t *meta = (meta_data_t*)desc_addr;
	meta->free = true;
	meta->next = NULL;
	meta->prev = NULL;
	meta->magic = MAGIC_FREE;

	/* meta->size holds only the usable area size for user */
	meta->size = req_pages * 4096 - sizeof(meta_data_t);
	last_block->next = meta;
	meta->prev = last_block;
	last_block = meta;


	/* now check if we can merge the last block and this
	* into one
	*/
	if (meta->prev->free) {
		meta->prev->size += meta->size;
		meta->prev->next = NULL;
		last_block = meta->prev;
	}

	uint64_t lm = (uint64_t)page;
	last_mark = (uint8_t*)(lm + (req_pages * 4096));
	
}

/*
 * kmalloc -- allocate a small chunk of memory
 * @param size -- size in bytes
 */
void* malloc(size_t size) {
	meta_data_t *meta = first_block;
	uint8_t* ret = 0;
	/* now search begins */
	while(meta){
		if (meta->free) {
			if (meta->size > size) {
				if (au_split_block(meta, size)){
					meta->free = false;
					meta->magic = MAGIC_USED;
					ret = ((uint8_t*)meta + sizeof(meta_data_t));
				}
				break;
			}

			if (meta->size == size) {
				meta->free = false;
				meta->magic = MAGIC_USED;
				ret =  ((uint8_t*)meta + sizeof(meta_data_t));
				break;
			}
		}

		if (meta->next == meta && meta->prev == meta &&
			meta->size == 0) {
				meta->next = NULL;
				meta->prev = NULL;
				meta->free = false;
		}

		meta = meta->next;
	}

	if (ret) {
		return ret;
	} else{
		au_expand_kmalloc(size);
		
	}
	return malloc(size);
}

/*
 * merge_forward -- merges the next free block 
 * with current one
 * @param meta -- current meta block
 */
void merge_forward(meta_data_t *meta) {
	if (meta->next == NULL) 
		return;
	if (!meta->next->free)
		return;

	/* Corrupted meta block */
	if (meta->next->size <= sizeof(meta_data_t))
		return;

	if (last_block == meta->next)
		last_block = meta;

	meta->size += meta->size + meta->next->size;
	
	if (meta->next->next != NULL)
		meta->next->next->prev = meta;

	meta->next = meta->next->next;
}

/*
 * merge_backward -- merges previos free block with
 * current one
 * @param meta -- current block
 */
void merge_backward (meta_data_t* meta) {
	if (meta->prev != NULL && meta->prev->free)
		merge_forward(meta->prev);
}

/*
 * free up a pointer
 * @param ptr -- pointer to the address block to free
 */
void free(void* ptr) {
	uint8_t* actual_addr = (uint8_t*)ptr;
	meta_data_t *meta = (meta_data_t*)(actual_addr - sizeof(meta_data_t));
	meta->free = true;
	/* merge it with 3 near blocks if they are free*/
	merge_forward(meta);
	merge_backward(meta);
}

/*
 * krealloc -- reallocate a block from the old block
 * @param ptr -- pointer to the old block
 * @param new_size -- size of the new block
 */
void* krealloc(void* ptr, size_t new_size) {
	void* result = malloc(new_size);
	if (ptr) {
		/* here we can check the size difference
		 * of new_size and old size from internal
		 * data structure of kmalloc */
		memcpy(result, ptr, new_size);
	}

	free(ptr);
	return result;
}

/*
 * kcalloc -- allocates a memory filled with zeroes
 * @param n_item -- number of items
 * @param size -- size of each items
 */
void* kcalloc(size_t n_item, size_t size) {
	size_t total = n_item * size;

	void* ptr = malloc(total);
	if (ptr)
		memset(ptr, 0, total);
	return ptr;
}
/*
 * au_request_page -- request contiguous 4k virtual pages
 * @param pages -- number of pages needs to be mapped
 */
uint64_t* au_request_page(int pages) {
	uint64_t* page = AuGetFreePage(0,false, 0);
	uint64_t page_ = (uint64_t)page;

	_debug_print_ ("*****Requesting page -> %x \r\n", page);
	for (size_t i = 0; i < pages; i++) {
		AuMapPage((uint64_t)AuPmmngrAlloc(), page_ + i * 4096, 0);
		
	}
	return (uint64_t*)page;
}

/*
 * au_free_page -- frees up pages, note that pages
 * are needed to be 4k and contiguous
 * @param ptr -- pointer to the first page
 * @param pages --pages -- number of pages
 */
void au_free_page(void* ptr, int pages) {
	AuFreePages((uint64_t)ptr,true,pages);
}