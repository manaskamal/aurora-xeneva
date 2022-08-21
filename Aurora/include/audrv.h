/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 **/

#ifndef __AU_DRV_H__
#define __AU_DRV_H__

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

#define DEVICE_CLASS_ETHERNET  1
#define DEVICE_CLASS_HD_AUDIO  2
#define DEVICE_CLASS_USB3      3

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

typedef struct _aurora_device_{
	uint16_t class_code;
	uint16_t sub_class_code;
	uint8_t prog_if;
	bool initialized;
	uint8_t aurora_dev_class;
	uint8_t aurora_driver_class;
}aurora_device_t;


//!driver manager initialization
extern void AuDrvMngrInitialize (KERNEL_BOOT_INFO *info);
extern void drv_mngr_write_driver (unsigned char* buffer, size_t length);
extern void AuDriverLoadMem (uint8_t* mem);

/*
 * AuRegisterDevice -- registers a new device to 
 * aurora system
 * @param dev -- device structure to register
 */
AU_EXTERN AU_EXPORT void AuRegisterDevice (aurora_device_t *dev);
/*
 * AuCheckDevice -- checks an aurora device if it's already present
 * @param classC -- class code of the device to check
 * @param subclassC -- sub class code of the device to check
 * @param prog_if -- programming interface of the device
 */
AU_EXTERN AU_EXPORT bool AuCheckDevice (uint16_t classC, uint16_t subclassC, uint8_t prog_if);

#endif


