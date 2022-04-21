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
#include <fs\vfs.h>

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

typedef int (*au_drv_entry) ();
typedef int (*au_drv_unload) ();
//! Aurora driver interface structure
typedef struct _aurora_driver_ {
	uint8_t id;
	uint8_t class_type;
	char name[32];
	bool present;
	uint64_t base;
	uint64_t end;
	au_drv_entry entry;
	au_drv_unload unload;
}aurora_driver_t;


//!driver manager initialization
extern void AuDrvMngrInitialize (KERNEL_BOOT_INFO *info);
extern void drv_mngr_write_driver (unsigned char* buffer, size_t length);

#endif


