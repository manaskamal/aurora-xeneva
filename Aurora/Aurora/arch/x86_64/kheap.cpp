/**
 *
 *     Copyright (C) Manas Kamal Choudhury 2020-2021
 *
 * kheap.h -- Kernel Heap Allocator
 *
 * /PROJECT - Xeneva v1.0
 * /AUTHOR  - Manas Kamal Choudhury 
 *
 * -----------------------------------------------------------
 *=============================================================*/

#include <arch\x86_64\mmngr\kheap.h>
#include "pmmngr.h"
#include <serial.h>

#define HEAP_START   0xFFFF800000000000

heap_t *first_heap;
void*  last = NULL;
heap_t *last_heap;

void initialize_kmemory (size_t sz) {

	if (sz < 4096) {
		if (sz % 0x1000) {
			sz -= sz % 0x1000;
			sz += 0x1000;
		}
	}


	size_t pos = HEAP_START;  //0xFFFFB00000000000;

	for (size_t i=0; i < sz / 4096; i++) {
		map_page ((uint64_t)pmmngr_alloc(),(uint64_t)pos,0);
		pos = pos + 4096;
	}
	
	first_heap = (heap_t*)HEAP_START;
	first_heap->length = sz;
	first_heap->magic = HEAP_MAGIC;
	first_heap->free = true;
	first_heap->next = NULL;
	first_heap->prev = NULL;
	last = (void*)pos;
	last_heap = first_heap;

#ifdef _DEBUG_ON_
	if (is_serial_initialized())
		_debug_print_ ("[KHeap]: Initialized -> size -> %d MB \r\n", sz / 1024/ 1024);
#endif

}


heap_t *split_heap (heap_t* heap, uint32_t req_size) {
	unsigned int new_length = heap->length - req_size;
	void* new_addr = (void*)(heap + req_size);

#ifdef _DEBUG_ON_
	if (is_serial_initialized())
		_debug_print_("[KHeap]: Splited heap ->old address -> %x, new address - %x \r\n", heap,new_addr);
#endif
	heap_t *new_heap = (heap_t*)new_addr;
	new_heap->free = true;
	new_heap->length = new_length;
	new_heap->magic = HEAP_MAGIC;
	new_heap->next = heap->next;
	new_heap->prev = heap;

	heap->length = req_size;
	heap->next = new_heap;
	return heap;
}


void heap_expand (size_t sz) {
	if (sz % 0x1000) {
		sz -= sz % 0x1000;
		sz += 0x1000;
	}

	size_t page_count = sz / 0x1000;

	void* last_store = last;
	for (int i = 0; i < page_count; i++) {
		map_page ((uint64_t)pmmngr_alloc(), (uint64_t)last, 0);
		last = (void*)((size_t)last + 0x1000);
	}

	heap_t *heap = (heap_t*)last_store;
	heap->free = true;
	heap->length = sz;
	heap->magic = HEAP_MAGIC;
	heap->next = NULL;
	heap->prev = last_heap;
	last_heap->next = heap;
	last_heap = heap;

#ifdef _DEBUG_ON_
	if (is_serial_initialized()) {
		_debug_print_ ("[KHeap]: New block created address:- %x, length -%d bytes \r\n",heap,heap->length);
		_debug_print_ ("[KHeap]: Heap Expanded by %d bytes \r\n", page_count * 4096);
	}
#endif

}



void* malloc(size_t sz) {
	for (heap_t *heap = first_heap; heap != NULL; heap = heap->next) {
		if (heap->free) {
			if (heap->length == sz) {
				heap->free = false;
				return (void*)(heap + sizeof(heap_t));
			}

			if (sz < heap->length) {
				heap_t *return_h = split_heap (heap,sz);
				return_h->free = false;
				return (void*)(return_h + sizeof(heap_t));
			}
		}
	}

	heap_expand(sz);
	return malloc(sz);
}

void free (void* memory) {
	//x64_cli();
	heap_t *heap = (heap_t*)memory - sizeof(heap_t);
	heap->free = true;
}


void kheap_print () {
	printf ("Heap Start -> %x\n", first_heap);
	printf ("Heap End -> %x\n", last_heap);
}