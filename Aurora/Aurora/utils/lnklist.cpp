/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * lnklist.cpp -- Linked list data structure
 *
 * /PROJECT - Aurora {Xeneva}
 * /AUTHOR  - Manas Kamal Choudhury
 *
 *===============================================
 */

#include <utils\lnklist.h>
#include <mm.h>


list_t* initialize_list() {
	list_t *list = (list_t*)malloc(sizeof(list_t));
	list->entry_current = nullptr;
	list->pointer = 0;
	return list;
}


void list_add(list_t* list, void* data) {
	dataentry *current_data = (dataentry*)malloc(sizeof(dataentry));
	current_data->next = nullptr;
	current_data->prev = nullptr;
	current_data->data = data;


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

void * list_get_at(list_t* list, unsigned int index) {

	if (list->pointer == 0 || index >= list->pointer)
		return nullptr;

	dataentry * current_node = list->entry_current;
	
	for (unsigned int current_index = 0; (current_index < index) && current_node; current_index++)
		current_node = current_node->next;

	return current_node ? current_node->data : nullptr;
}

void* list_remove(list_t* list, unsigned int index) {

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

	mfree(current_node);

	list->pointer--;

	return payload;
}