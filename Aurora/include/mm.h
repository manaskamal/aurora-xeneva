/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 *  mm.h -- Memory Manager Abstraction Layer
 *
 *  /PROJECT - Aurora { Xeneva v1.0 }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *===============================================
 */

#ifndef __MM_H__
#define __MM_H__

#include <stdint.h>
#ifdef ARCH_X64
#include <arch\x86_64\mmngr\vmmngr.h>
#endif

extern void mm_init ();
extern void* malloc (size_t size);
extern void mfree (void* address);
#endif