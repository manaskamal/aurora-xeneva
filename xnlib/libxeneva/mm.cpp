/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT - DWM Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *-----=-=-=---=-==-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 */

#include <mm.h>
#include <xnsys.h>


void* free_list;
//const int allocation_block_size = 64;
LIST_ENTRY *last_header;
void* alloc_end;
void* start;

void initialize_allocator(int sz) {
	for (int i=0; i < sz; i++) {
		valloc(0xFFFFFFFF80000000 + i * 4096);
	}

	start = (void*)0xFFFFFFFF80000000;
	LIST_ENTRY *link = (LIST_ENTRY*)start;
	link->next = NULL;
	link->prev = NULL;
	link->is_free = true;
	last_header = link;
	alloc_end = (void*)((size_t)start + sz * 4096);
}

void expand_dwm_allocator(int sz) {
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

void* malloc (int size) {

	LIST_ENTRY* list = (LIST_ENTRY*)start;

	while(true) {
		if (list->is_free) {
			if (size < 4096) {
				uint64_t split_length = 4096 - size; // - sizeof(LIST_ENTRY);
				void* new_addr = (void*)((size_t)list + split_length);
				LIST_ENTRY* new_list = (LIST_ENTRY*)new_addr;
				new_list->next = list->next;
				list->next = new_list;
				list->is_free = false;
				new_list->prev = list;
				new_list->is_free = true;
				last_header = new_list;
				return (void*)((size_t)list + sizeof(LIST_ENTRY));
			}

			/*if (size > 4096) {
				print_text("USER HEAP: size requested is > 4096\n");
			}
*/
			if (size == 4096){
				list->is_free = false;
				return (void*)((size_t)list + sizeof(LIST_ENTRY));
			}

			
		}


		if (list->next == NULL) break;

        list = list->next;
	}

	expand_dwm_allocator(size);
	return malloc(size);

}


void mfree (void* memory) {
	LIST_ENTRY* entry = (LIST_ENTRY*)memory - 1;
	entry->is_free = true;
}


	