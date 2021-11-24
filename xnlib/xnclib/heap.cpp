/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT - DWM Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *-----=-=-=---=-==-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 */

#include <heap.h>
#include <stdint.h>
#include <sys/mmap.h>
#include <string.h>
#include <sys\_term.h>

void* free_list;
//const int allocation_block_size = 64;
LIST_ENTRY *last_header;
void* alloc_end = NULL;
void* start = NULL;

void heap_initialize_allocator() {
	//for (int i=0; i < 0xB00000/4096; i++) {
	//	valloc(0x0000080000000000 + i * 4096);
	//}

	start = (uint64_t*)0x0000080000000000;

	LIST_ENTRY *link = (LIST_ENTRY*)start;
	link->is_free = true;
	link->length = 0xB00000 - sizeof(LIST_ENTRY);// * (4096 - sizeof(LIST_ENTRY));
	link->next = NULL;
	link->prev = NULL;
	last_header = link;
	alloc_end = (void*)(0x0000080000000000 + 0xB00000);
}

void expand_allocator(int sz) {
	if (sz % 0x1000)  {
		sz -= sz % 0x1000;
		sz += 0x1000;
	}


	int page_count = sz / 0x1000;
	LIST_ENTRY *link = (LIST_ENTRY*)alloc_end;	

	for (int i=0; i < page_count; i++) {
		valloc((uint64_t)alloc_end + i * 4096);
		alloc_end = (void*)((size_t)alloc_end + 0x1000);
	}
	
    link->is_free = true;
	link->length = sz ;//- sizeof(LIST_ENTRY);
	link->next = NULL;
	link->prev = last_header;
	last_header->next = link;
	last_header = link;
}

void* _malloc (uint32_t size) {

	LIST_ENTRY* list = (LIST_ENTRY*)start;
	

	while(true) {
		if (list->is_free) {

			if (list->length > size) {
				uint64_t split_length = list->length - size - (sizeof(LIST_ENTRY));
				size_t* new_addr = (size_t*)((size_t)list + size + sizeof(LIST_ENTRY));
				LIST_ENTRY* new_list = (LIST_ENTRY*)new_addr;
				new_list->is_free = true;
				new_list->length = split_length;

				if (list->next != 0)
					list->next->prev = new_list;

				new_list->next = list->next;
				list->next = new_list;
				list->is_free = false;
				list->length = size;
				new_list->prev = list;
				if (last_header == list) last_header = new_list;	
				return (void*)((size_t)list + sizeof(LIST_ENTRY));
			}

		
			if (list->length == size){
				list->is_free = false;
				return (void*)((size_t)list + sizeof(LIST_ENTRY));
			}	

		}


		if (list->next == NULL) break;

        list = list->next;
	}

	expand_allocator(size);
	return _malloc(size);
}


void _free (void* memory) {
	LIST_ENTRY* entry = (LIST_ENTRY*)memory - 1;
	entry->is_free = true;
}

void* _realloc (void* address, uint32_t new_size) {
	LIST_ENTRY *old_segment_header = (LIST_ENTRY*)address;
	uint64_t smaller_size = new_size;
	if (old_segment_header->length < new_size)
		smaller_size = old_segment_header->length;
	void* new_mem = _malloc(new_size);
	memcpy (new_mem, address, new_size);
	_free(address);
	return new_mem;
}

void* _calloc(uint64_t size) {
	void* malloc_val = _malloc(size);
	memset(malloc_val, 0, size);
	return malloc_val;
}

void* _calloc(uint64_t num, uint64_t size) {
	return _calloc(num * size);
}


	