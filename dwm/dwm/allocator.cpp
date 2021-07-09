/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  allocator.cpp -- DWM Internal memory allocator
 *
 *  /PROJECT - DWM {Desktop Window Manager}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =====================================================
 */

#include <allocator.h>
#include <sys.h>


static void* free_list;
//const int allocation_block_size = 64;
static LIST_ENTRY *last_header;
static void* dwm_alloc_end;
static void* dwm_start;


void initialize_dwm_allocator(int sz) {
	for (int i=0; i < sz; i++) {
		valloc(0xFFFFD00000800000 + i * 4096);
	}

	dwm_start = (void*)0xFFFFD00000800000;
	LIST_ENTRY *link = (LIST_ENTRY*)dwm_start;
	link->next = NULL;
	link->prev = NULL;
	link->is_free = true;
	last_header = link;
	dwm_alloc_end = (void*)((size_t)dwm_start + sz * 4096);
}

void expand_dwm_allocator(int sz) {
	int page_count = sz / 4096;

	for (int i=0; i < page_count; i++) {
		valloc((uint64_t)((size_t)dwm_alloc_end + i * 4096));
	}

	LIST_ENTRY *link = (LIST_ENTRY*)dwm_alloc_end;
	link->is_free = true;
	link->next = NULL;
	link->prev = last_header;
	last_header = link;
}

void* dalloc (int size) {

	LIST_ENTRY* list = (LIST_ENTRY*)dwm_start;

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
	return dalloc(size);

}


void dfree (void* memory) {
	LIST_ENTRY* entry = (LIST_ENTRY*)memory - 1;
	entry->is_free = true;
}


uint64_t pos = 0xFFFFD00000800000;
void initialize_flat_allocator (int size) {
	for (int i = 0; i < size / 4096; i++) {
		valloc(0xFFFFD00000800000 + i * 4096);
	}
}

void *flat_alloc () {
	void* ret = (void*)pos;
	pos += 4096;
	return ret;
}

void flat_free () {
	pos -= 4096;
}



	