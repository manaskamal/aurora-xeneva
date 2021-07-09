/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  gmr.h -- VMware Guest Memory
 *  
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#ifndef __GMR_H__
#define __GMR_H__

#include <arch\x86_64\mmngr\kheap.h>
#include <drivers\svga\svga_reg.h>
#include <drivers\svga\vmsvga.h>

#define PAGE_SIZE  4096
#define PAGE_SHIFT 12
#define PAGE_MASK  (PAGE_SIZE - 1)
#define PPN_POINTER(ppn)  ((void*)((ppn)*PAGE_SIZE))
typedef uint32_t ppn;

extern svga_device svga_dev;

typedef struct _gmr_state_ {
	uint32_t max_ids;
	uint32_t max_descriptor_len;
	uint32_t max_pages;
} gmr_state;

extern void gmr_init ();
extern void gmr2_init ();

//!
extern ppn gmr_alloc_descriptor (SVGAGuestMemDescriptor *desc_array, uint32 num_descriptors);

extern void gmr_define (uint32_t gmr_id, SVGAGuestMemDescriptor *desc_array, uint32_t num_descriptors);
extern ppn gmr_define_contiguous (uint32_t gmr_id, uint32_t num_pages);
extern ppn gmr_define_even_pages (uint32_t gmr_id, uint32_t num_pages);
extern void gmr_free_all();
#endif