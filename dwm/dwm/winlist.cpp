/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT - Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 * ===============================================
 */

#include <winlist.h>
#include <allocator.h>
#include <sys.h>

winlist* initialize_winlist() {
	winlist *list = (winlist*)dalloc(sizeof(winlist));
	list->entry_current = nullptr;
	list->pointer = 0;
	return list;
}


void win_list_add(winlist* list, void* data) {
	dataentry *current_data = (dataentry*)dalloc(sizeof(dataentry));
	current_data->next = nullptr;
	current_data->prev = nullptr;
	current_data->data = data;
	//print_text ("[Winlist_Add]: Current data address -> %x\n", current_data);

	if (!list->entry_current) {
		list->entry_current = current_data;
	}else {
		dataentry * current_entry = list->entry_current;
		while (current_entry->next) {
			current_entry = current_entry->next;
		}
		current_entry->next = current_data;
		current_data->prev = current_entry;
	}

	list->pointer++;
}

void * win_list_get_at(winlist* list, unsigned int index) {

	if (list->pointer == 0 || index >= list->pointer)
		return nullptr;

	dataentry * current_node = list->entry_current;
	
	for (unsigned int current_index = 0; (current_index < index) && current_node; current_index++)
		current_node = current_node->next;

	return current_node ? current_node->data : nullptr;
}

void* win_list_remove(winlist* list, unsigned int index) {

	void* payload;

	if (list->pointer == 0 || index >= list->pointer)
		return nullptr;

	dataentry* current_node = list->entry_current;

	for (unsigned int current_index = 0; (current_index < index) && current_node; current_index++)
		current_node = current_node->next;

	if (!current_node)
		return nullptr;
	payload = current_node->data;

	if (current_node->prev)
		current_node->prev->next = current_node->next;

	if (current_node->next)
		current_node->next->prev = current_node->prev;

	if (index == 0)
		list->entry_current = current_node->next;

	//dfree(current_node);

	list->pointer--;

	return payload;
}