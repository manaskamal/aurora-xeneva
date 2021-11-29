///! 
///!  Copyright (C) Manas Kamal Choudhury
///!
///!  buffer.h -- Buffer manager for double buffering uses
///!
///!  /PROJECT - Aurora's Xeneva v1.0
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=============================================================

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>

#define DOUBLE_BUFFER_START  0x0000600000000000

extern uint32_t* acrylic_allocate_buffer (size_t sz);
extern void acrylic_free_buffer (void *p,size_t sz);
#endif