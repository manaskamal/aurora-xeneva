/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT - DWM Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *-----=-=-=---=-==-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 */

#include <allocator.h>
#include <sys.h>

#define ALLOCATOR_START  0x0000080000000000

void* free_list;
//const int allocation_block_size = 64;
LIST_ENTRY *last_header;
uint64_t* alloc_end = NULL;
uint64_t* start = NULL;

void initialize_dwm_allocator(int sz) {
	for (int i=0; i < 0xA00000/4096; i++) {
		valloc(0x0000080000000000 + i * 4096);
	}

	start = (uint64_t*)0x0000080000000000;

	LIST_ENTRY *link = (LIST_ENTRY*)start;
	link->next = NULL;
	link->prev = NULL;
	link->is_free = true;
	link->length = 0xA00000 * ( 4096 - sizeof(LIST_ENTRY)); 
	last_header = link;
	alloc_end = (uint64_t*)((ALLOCATOR_START + 0xA00000) * 4096);  
}

void expand_allocator(int sz) {
	int page_count = sz / 4096;

	for (int i=0; i < page_count; i++) {
		valloc((uint64_t)((size_t)alloc_end + i * 4096));
	}

	LIST_ENTRY *link = (LIST_ENTRY*)alloc_end;
	link->is_free = true;
	link->next = NULL;
	link->prev = last_header;
	last_header = link;
}

void*  dalloc (uint32_t size) {

	LIST_ENTRY* list = (LIST_ENTRY*)start;

	while(true) {
		if (list->is_free) {

			if (list->length > size) {
				uint64_t split_length = list->length - (size - sizeof(LIST_ENTRY));
				size_t* new_addr = (size_t*)((size_t)list + size + sizeof(LIST_ENTRY));
				LIST_ENTRY* new_list = (LIST_ENTRY*)new_addr;

				if (list->next != 0)
					list->next->prev = new_list;

				new_list->next = list->next;
				list->next = new_list;
				list->is_free = false;
				new_list->length = split_length;
				list->length = size;
				new_list->prev = list;
				new_list->is_free = true;
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
	return dalloc(size);

}


void dfree (void* memory) {
	LIST_ENTRY* entry = (LIST_ENTRY*)memory - 1;
	entry->is_free = true;
}


	