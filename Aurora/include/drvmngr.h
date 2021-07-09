/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  drvmngr.h -- Aurora Driver Manager
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#ifndef __DRVMNGR_H__
#define __DRVMNGR_H__

#include <stdint.h>
#include <hal.h>
#include <stdio.h>
#include <drivers\pci.h>
#include <arch\x86_64\apic.h>
#include <_xnboot.h>

//! Basic Driver classes to register driver
#define DRIVER_CLASS_AUDIO  1
#define DRIVER_CLASS_VIDEO  2
#define DRIVER_CLASS_NETWORK 3
#define DRIVER_CLASS_CONNECTIVITY_BLUETOOTH 4
#define DRIVER_CLASS_CONNECTIVITY_WIFI 5
#define DRIVER_CLASS_STORAGE 6
#define DRIVER_CLASS_USB 7
#define DRIVER_CLASS_HID 8
#define DRIVER_CLASS_UNKNOWN 9

//!Maximum Supported Drivers in Aurora Xeneva v1.0 is 256
#define AURORA_MAX_DRIVERS  256

//! The driver parameter to pass
#pragma pack (push)
typedef struct _driver_param_ {
	void (*kdebug) (const char* str, ...);
	void (*irq_eoi) ();
	void (*interrupt_set) (size_t vector, void (*fn)(size_t, void* p),uint8_t irq);
	bool (*pci_find_device) (uint16_t vendor_id, uint16_t device_id, pci_address *addr);
	uint32_t (*pci_get_bar) (const pci_address *addr, int index);
	void (*pci_set_mem_enable) (const pci_address *addr, bool enable);
}driver_param_t;
#pragma pack (pop)

//! Aurora driver interface structure
typedef struct _aurora_driver_ {
	int class_type;
	const char* name;
	bool present;
	int (*aurora_init_driver) (driver_param_t *param);
	void (*aurora_close_driver) ();
}aurora_driver_t;


//!driver manager initialization
extern void driver_mngr_initialize (KERNEL_BOOT_INFO *info);

#endif


