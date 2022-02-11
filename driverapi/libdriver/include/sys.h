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


struct _vfs_node_;


typedef _vfs_node_ (*open_callback) (_vfs_node_ *node, char* path);
typedef void (*read_callback) (_vfs_node_ *file, uint8_t* buffer,uint32_t length);
typedef void (*read_block_callback) (_vfs_node_ *file, uint8_t* buffer);
typedef void (*write_callback) (_vfs_node_ *file, uint8_t* buffer, uint32_t length);
typedef int (*ioquery_callback) (_vfs_node_ *file, int code, void *arg);

//! The File Node -- everything is file
typedef struct _vfs_node_ {
	char filename[32];
	uint32_t  size;
	uint32_t  eof;
	uint32_t  pos;
	uint32_t  current;  //inode -- in unix term
	uint32_t  flags; 
	uint32_t  status;
	void* device;
	open_callback open;
	read_callback read;
	write_callback write;
	read_block_callback read_blk;
	ioquery_callback ioquery;
}vfs_node_t;

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
	void* (*malloc_p) (size_t size);
	uint64_t* (*get_phys_address_p) (uint64_t virt_address);
	void (*mfree_p) (void* addr);
	void* (*pmmngr_alloc_p) ();
	void* (*pmmngr_alloc_blocks_p) (int size);
	void  (*pmmngr_free_p) (void* addr);
	bool  (*map_page_p) (uint64_t physical_address, uint64_t virtual_address, uint8_t attrib);
	void (*unmap_page_p) (uint64_t virt_addr);
	uint64_t (*get_free_page_p) (size_t s, bool user);
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
	pci_p_t* pci;
	fs_t *fs;
}driver_param_t;

#pragma pack(pop)

#endif