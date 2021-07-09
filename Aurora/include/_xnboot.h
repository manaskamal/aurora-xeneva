/**
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *   _xnboot.h -- Boot information passed by XNLDR
 *
 *   /PROJECT - Aurora v1.0
 *   /AUTHOR  - Manas Kamal Choudhury
 *
 *===========================================================
 */

#ifndef __XNBOOT_H__
#define __XNBOOT_H__

#include <stdint.h>


#pragma pack (push,1)
typedef struct _KERNEL_BOOT_INFO_ {
	int boot_type;
	uint64_t phys_start;
	uint64_t phys_size;
	uint64_t ram_size;
	uint32_t* graphics_framebuffer;
	size_t   fb_size;
	uint16_t   X_Resolution;
	uint16_t   Y_Resolution;
	uint16_t   pixels_per_line;
	uint32_t redmask;
	uint32_t greenmask;
	uint32_t bluemask;
	uint32_t resvmask;
	void*    acpi_table_pointer;
	size_t   kernel_size;
	uint8_t* psf_font_data;
	void (*printf_gui) (const char* text, ...);
	uint8_t* driver_entry1;   //OTHER
	uint8_t *driver_entry2;   //!NVME
	uint8_t *driver_entry3;   //!AHCI
	uint8_t* driver_entry4;   //!FLOPPY
	uint8_t* driver_entry5;   //!ATA
	uint8_t* driver_entry6;   //!USB
}KERNEL_BOOT_INFO, *PKERNEL_BOOT_INFO;
#pragma pack(pop)


#endif