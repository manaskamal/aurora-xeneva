/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ring.h -- Circular Buffer
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *====================================================
 */

#ifndef __RING_H__
#define __RING_H__

#include <stdint.h>

typedef struct _element_ {
	void* data;
	struct _element_ *next;
}element_t;

typedef struct _ring_ {
	element_t* begin;
	element_t* current;
}ring_t;

extern void initialize_ring (ring_t* ring);
extern bool ring_insert (ring_t* ring, void* data, bool single);
extern bool ring_is_empty (const ring_t* ring);
extern bool ring_delete_first (ring_t* ring, void* data);
extern void ring_move (ring_t* dest, ring_t* source, void* data);

#endif