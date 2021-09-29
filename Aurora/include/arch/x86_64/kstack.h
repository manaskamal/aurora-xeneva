//!
//!   Copyright (C) Manas Kamal Choudhury 2021
//!
//!   kstack -- Kernel Stack allocator 
//!
//!   //PROJECT - Aurora's Xeneva
//!   //AUTHOR  - Manas Kamal Choudhury
//!
//!=================================================

#ifndef __KSTACK_H__
#define __KSTACK_H__

#include <stdint.h>
#include <arch\x86_64\mmngr\vmmngr.h>


#define KSTACK_START  0xFFFFFB0000000000


extern uint64_t allocate_kstack (uint64_t *cr3);
#endif