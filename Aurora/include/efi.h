/**
 **  Copyright (C) Manas Kamal Choudhury 2021
 ** 
 **  efi.h -- UEFI structures definitions 
 **
 **  /PROJECT - Aurora's Xeneva v1.0
 **  /AUTHOR  - Manas Kamal Choudhury
 **
 **=================================================
 **/

#ifndef __EFI_H__
#define __EFI_H__

#include <stdint.h>

//! UEFI Memory Descriptor structure
//! used to obtain the memory maps by uefi
typedef struct _EFI_MEM_DESC_ {
	uint32_t type;
	uint64_t phys_start;
	uint64_t virt_start;
	uint64_t num_pages;
	uint64_t attrib;
}EFI_MEMORY_DESCRIPTOR;

#endif