/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ring.cpp -- Ring Buffer {Circular Buffer}
 *
 *  /PROJECT -- Aurora {Xeneva}
 *  /AUTHOR  -- Manas Kamal Choudhury
 *
 *===============================================
 */

#include <utils\ring.h>
#include <string.h>
#include <pmmngr.h>
#include <arch\x86_64\mmngr\kheap.h>

void initialize_ring (ring_t * ring) {
	ring->current = 0;
	ring->begin = 0;
}

static void put_in (ring_t* ring, element_t *prev, element_t *elem) {
	if (ring->begin == 0) {
		elem->next = elem;
		ring->begin = elem;
		ring->current = elem;
	} else {
		elem->next = prev->next;
		prev->next = elem;
	}
}


static void take_out (ring_t* ring, element_t* prev) {
	if (!ring) 
		return;

	if (prev->next == prev) {
		ring->begin = 0;
		ring->current = 0;
	} else {
		if (prev->next == ring->begin) ring->begin = prev->next->next;
		if (prev->next == ring->current) ring->current = prev->next->next;
		prev->next = prev->next->next;
	}
}

bool ring_insert (ring_t* ring, void* data, bool single) {

	if (!ring)
		return false;

	if (single && ring->begin != 0) {
		element_t * current = ring->current;
		element_t * begin = current;
		do {
			if (current->data == data) {
				return false;
			}
			current = current->next;
		}
		while (current != begin);
	}
	element_t* item = (element_t*)malloc(sizeof(element_t*));
	if (item) {
		item->data = data;
		put_in (ring,ring->current, item);
		return (true);
	}
	return false;
}

bool ring_is_empty (const ring_t* ring) {
	if (!ring)
		return false;
	return (ring->begin == 0);
}


bool ring_delete_first (ring_t* ring, void* data) {
	
	if (!ring) 
		return false;

	if (ring->begin == 0) return false;

	element_t * current = ring->current;
	element_t * begin = current;

	do {
		if (current->next->data == data) {
			element_t * temp = current->next;
			take_out (ring, current);
			free(temp);
			return (true);
		}
		current = current->next;
	}
	while (current != begin);

	return (false);
}


void ring_move (ring_t* dest, ring_t * source, void* data) {

	if (!dest && !source)
		return;

	if (source == 0 || dest == 0 || source->begin == 0) return;
	
	element_t * prev = source->begin;
	element_t * begin = prev;
	element_t * current = prev->next;

	do {
		if (current->data == data) {
			take_out(source, prev);
			break;
		}
		prev = current;
		current = current->next;
	} while (prev != begin);

	if (current->data == data) 
		put_in (dest, dest->current, current);

}

