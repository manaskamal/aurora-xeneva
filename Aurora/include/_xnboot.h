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

/**
 * Kernel Boot information structure passed by XNLDR
 */
#pragma pack (push,1)
typedef struct _KERNEL_BOOT_INFO_ {
	/* Boot type either UEFI_BOOT or BIOS_BOOT */
	int boot_type;  

	void* allocated_stack;
	uint64_t reserved_mem_count;

	/* map -- UEFI memory map */
	void *map;

	/* descriptor_size -- UEFI memory map descriptor size */
	uint64_t descriptor_size;

	/* mem_map_size -- UEFI memory map size */
	uint64_t mem_map_size;

	/* graphics_framebuffer -- framebuffer address passed by XNLDR */
	uint32_t* graphics_framebuffer;

	/* fb_size -- framebuffer total size */
	size_t   fb_size;

	/* X_Resolution -- Total width of the entire display */
	uint16_t  X_Resolution;

	/* Y_Resolution -- Total height of the entire display */
	uint16_t   Y_Resolution;

	/* pixels_per_line -- scanline of the current display */
	uint16_t   pixels_per_line;

	/* redmask, greenmask, bluemask, resvmask -- color mask */
	uint32_t redmask;
	uint32_t greenmask;
	uint32_t bluemask;
	uint32_t resvmask;

	/* acpi_table_pointer -- acpi base memory map */
	void*    acpi_table_pointer;

	/* kernel_size -- total kernel image size */
	size_t   kernel_size;

	/* psf_font_data -- screen font address loaded
	   by XNLDR to use for debugging purpose */
	uint8_t* psf_font_data;

	/* printf_gui -- character printing function pointer to use
	   for debugging purpose provided by XNLDR */
	void (*printf_gui) (const char* text, ...);

	/* unused pointer entries */
	uint8_t* driver_entry1;   //OTHER
	uint8_t *driver_entry2;   //!NVME
	uint8_t *driver_entry3;   //!AHCI
	uint8_t* driver_entry4;   //!FLOPPY
	uint8_t* driver_entry5;   //!ATA
	uint8_t* driver_entry6;   //!USB
	void*    apcode;
}KERNEL_BOOT_INFO, *PKERNEL_BOOT_INFO;
#pragma pack(pop)


#pragma pack(push,1)
/*
 * aurora_info_t -- aurora boot informations
 */
typedef struct _AURORA_INFO_ {
	void* mem_map;
	uint64_t mem_desc_size;
	uint64_t mem_map_size;
	void* phys_stack_allocated;
	size_t resvd_mem_count;
	uint32_t* fb_addr;
	size_t fb_size;
	uint32_t x_res;
	uint32_t y_res;
	uint16_t pixels_per_line;
	void*  acpi_table_pointer;
	size_t kernel_size;
	void(*auprint)(const char* text, ...);
}aurora_info_t;

#pragma pack(pop)

#endif
