/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  sys.h -- Aurora's Xeneva System callbacks
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#ifndef __SYS_H__
#define __SYS_H__

#include <pci.h>

//!DRIVER RETURN CODES
#define AURORA_DRIVER_FAILED  0
#define AURORA_DRIVER_SUCCESS 1
#define AURORA_DRIVER_HARDWARE_ERR 2
#define AURORA_DRIVER_HARDWARE_SUCC 3
#define AURORA_DRIVER_NOT_PRESENT 4
#define AURORA_DRIVER_PRESENT 5
#define AURORA_DRIVER_ADDRESS_INVALID 6
#define AURORA_DRIVER_DATA_SIZE_ERR 7
#define AURORA_DRIVER_ERR_UNKNOWN 8


#pragma pack(push)

//! The driver parameter to process
typedef struct _driver_param_ {
	void (*kdebug) (const char* str, ...);
	void (*irq_eoi) ();
	void (*interrupt_set) (size_t vector, void (*fn)(size_t, void* p),uint8_t irq);
	bool (*pci_find_device) (uint16_t vendor_id, uint16_t device_id, pci_address *addr);
	uint32_t (*pci_get_bar) (const pci_address *addr, int index);
	void (*pci_set_mem_enable) (const pci_address *addr, bool enable);
	void* (*malloc) (size_t size);
}driver_param_t;

#pragma pack (pop)

#endif