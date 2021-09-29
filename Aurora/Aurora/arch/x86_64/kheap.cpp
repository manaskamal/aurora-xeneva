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



void*  kmem_start;
void*  kmem_end;
kmem   *last_header;

void initialize_kmemory (size_t sz) {

	void* pos = (void*)0xFFFF800000000000;  //0xFFFFB00000000000;

	for (size_t i=0; i < sz; i++) {
		map_page ((uint64_t)pmmngr_alloc(),(uint64_t)pos);
		pos = (void*)((size_t)pos + 0x1000);
	}

    size_t kmem_length = sz * 0x1000;

	kmem_start = (void*)0xFFFF800000000000;                   //0xFFFFB00000000000;
	kmem_end = (void*)((size_t)kmem_start + kmem_length);
	kmem* start_seg = (kmem*)kmem_start;
	start_seg->length = kmem_length - sizeof (kmem);
	start_seg->next = NULL;
	start_seg->last = NULL;
	start_seg->free = true;
	last_header = start_seg;

}

void kmem::align_next () {

	if (next == NULL) return;
	if (!next->free) return;

	if (next == last_header) last_header = this;

	if (next->next != NULL) {
		next->next->last = this;
	}

	length = length + next->length * sizeof(kmem);
	next = next->next;
}


void kmem::align_prev () {
	if (last != NULL && last->free) last->align_next();
}


kmem* kmem::split(size_t split_length) {

	if (split_length < 0x10) return NULL;
	int64_t split_seg_length = length - split_length - (sizeof(kmem));
	if (split_seg_length < 0x10) return NULL;

	kmem* new_split = (kmem*) ((size_t)this + split_length + sizeof (kmem));
	next->last = new_split;
	new_split->next = next;
	next = new_split;
	new_split->last = this;
	new_split->length = split_seg_length;
	new_split->free = free;
	length = split_length;

	if (last_header == this) last_header = new_split;
	return new_split;
}


void expand_kmem (size_t length) {
	if (length % 0x1000) {
		length -=  length % 0x1000;
		length += 0x1000;
	}

	size_t page_count = length / 0x1000;
	kmem* new_seg = (kmem*)kmem_end;
	
	for (size_t i = 0; i < page_count; i++) {
		map_page ((uint64_t)pmmngr_alloc(), (uint64_t)kmem_end);
		kmem_end = (void*)((size_t)kmem_end + 0x1000);
	}

	new_seg->free = true;
	new_seg->last = last_header;
	last_header->next = new_seg;
	last_header = new_seg;
	new_seg->next = NULL;
	new_seg->length = length - sizeof (kmem);
	new_seg->align_next ();
}



void* alloc(size_t size) {
	x64_cli();
	if (size % 0x10 > 0) {
		size -= (size % 0x10);
		size += 0x10;
	}

	if (size == 0) return NULL;

	kmem* current_seg = (kmem*) kmem_start;
	while (true) {
		if (current_seg->free) {
			if (current_seg->length > size) {
				current_seg->split (size);
				current_seg->free = false;
				return (void*)((uint64_t)current_seg + sizeof (kmem));
			}

			if (current_seg->length == size) {
				current_seg->free = false;
				return (void*)((uint64_t)current_seg + sizeof (kmem));
			}
		}
		if (current_seg->next == NULL) break;
		current_seg = current_seg->next;
	}

	expand_kmem(size);
	x64_sti();
	return alloc(size);
}

void free (void* memory) {
   kmem* seg = (kmem*)memory - 1;
   seg->free = true;
   seg->align_next();
   seg->align_prev();	
}