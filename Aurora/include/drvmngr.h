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

//! The driver parameter to pass
#pragma pack (push,1)

typedef struct _pci_p_ {
	bool (*pci_find_device_class_p) (uint8_t class_code, uint8_t sub_class, pci_device_info *addr_out, int *bus, int *dev, int *func);
	bool (*pci_find_device_id_p) (uint16_t device_id, uint16_t vendor_id, pci_device_info *addr_out);
	void (*pci_enable_bus_master_p) (int bus, int dev, int func);
    void (*pci_enable_interrupt_p) (int bus, int dev, int func);
	void (*read_config_16_p) (uint16_t segment,int bus, int dev, int function, int reg, unsigned short *data );
	void (*write_config_16_p) (uint16_t segment,int bus, int dev, int function, int reg, unsigned short data );
	void (*read_config_32_p) (uint16_t segment, int bus, int dev, int function, int reg, uint32_t data);
	void (*read_config_8_p) (uint16_t segment,int bus, int dev, int function, int reg, unsigned char* data);
	void (*write_config_8_p) (uint16_t segment,int bus, int dev, int func, int reg, unsigned char data);
	void (*read_config_32_ext_p) (uint16_t segment,int bus, int dev, int function, int reg, uint32_t *data);
	void (*write_config_32_p) (int bus, int dev, int func, int reg, unsigned data);
}pci_p_t;

typedef struct _mem_ {
	void* (*malloc_p) (unsigned int size);
	uint64_t* (*get_phys_address_p) (uint64_t virt_address);
	void (*mfree_p) (void* addr);
	void* (*pmmngr_alloc_p) ();
	void* (*pmmngr_alloc_blocks_p) (int size);
	void  (*pmmngr_free_p) (void* addr);
	bool  (*map_page_p) (uint64_t physical_address, uint64_t virtual_address, uint8_t attrib);
	void (*unmap_page_p) (uint64_t virt_addr);
	uint64_t* (*get_free_page_p) (size_t s, bool user);
}mem_t;

typedef struct _cpu_ {
	void (*interrupt_eoi_p) (uint32_t irq);
	void (*interrupt_set_p) (size_t vector, void (*fn)(size_t, void* p),uint8_t irq);
	uint8_t (*inportb_p) (uint16_t port);
	uint16_t (*inportw_p) (uint16_t port);
	uint32_t (*inportd_p) (uint16_t port);
	void (*outportb_p) (uint16_t port, uint8_t data);
    void (*outportw_p) (uint16_t port, uint16_t data);
    void (*outportd_p) (uint16_t port, uint32_t data);
}cpu_t;

typedef struct _vfs_p_ {
	void (*vfs_mount_p) (char *path, vfs_node_t *node);
}fs_t;

typedef struct _driver_param_ {
	void (*kdebug) (const char* str, ...);
	mem_t *mem;
	cpu_t *cpu;
	pci_p_t *pci;
	fs_t    *fs;
}driver_param_t;
#pragma pack (pop)

//! Aurora driver interface structure
typedef struct _aurora_driver_ {
	int class_type;
	const char* name;
	bool present;
	int (*aurora_init_driver) (driver_param_t *param);
	void (*aurora_close_driver) ();
	void (*aurora_write) (unsigned char* sound_buffer, size_t length);
}aurora_driver_t;


//!driver manager initialization
extern void driver_mngr_initialize (KERNEL_BOOT_INFO *info);
extern void drv_mngr_write_driver (unsigned char* buffer, size_t length);

#endif


