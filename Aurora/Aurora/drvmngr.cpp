/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  drvmngr.cpp -- Aurora's Xeneva Driver Manager
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#include <drvmngr.h>
#include <pe.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <string.h>


//!Global Variable for the program
aurora_driver_t drivers[256];
static uint32_t driver_class_unique_id = 0;

typedef int (*init) (driver_param_t *param);
typedef void (*close) ();
typedef void (*write) (unsigned char* buffer, size_t length);

//! request an unique id for driver class
uint32_t request_driver_class_uid () {
	uint32_t uid = driver_class_unique_id;
	driver_class_unique_id++;
	return uid;
}

//! decreaments an unique id for driver class in order to free
void decreament_driver_class_uid () {
	driver_class_unique_id--;
}

driver_param_t * create_driver_parameter () {
	cpu_t *cpu = (cpu_t*)pmmngr_alloc();
	cpu->interrupt_set_p = interrupt_set;
	cpu->interrupt_eoi_p = interrupt_end;
	cpu->inportb_p = x64_inportb;
	cpu->inportd_p = x64_inportd;
	cpu->inportw_p = x64_inportw;
	cpu->outportb_p = x64_outportb;
	cpu->outportd_p = x64_outportd;
	cpu->outportw_p = x64_outportw;

	pci_p_t *pci = (pci_p_t*)pmmngr_alloc();
	pci->pci_enable_bus_master_p = pci_enable_bus_master;
	pci->pci_enable_interrupt_p = pci_enable_interrupt;
	pci->pci_find_device_class_p = pci_find_device_class;
	pci->pci_find_device_id_p = pci_find_device_id;
	pci->read_config_16_p = read_config_16;
	pci->read_config_8_p = read_config_8;
	pci->read_config_32_p = read_config_32;
	pci->read_config_32_ext_p = read_config_32_ext;
	pci->write_config_16_p = write_config_16;
	pci->write_config_32_p = write_config_32;
	pci->write_config_8_p = write_config_8;

	mem_t *m = (mem_t*)pmmngr_alloc();
	m->get_free_page_p = get_free_page;
	m->get_phys_address_p = get_physical_address;
	m->malloc_p = malloc;
	m->map_page_p = map_page;
	m->mfree_p = free;
	m->pmmngr_alloc_blocks_p = pmmngr_alloc_blocks;
	m->pmmngr_alloc_p = pmmngr_alloc;
	m->pmmngr_free_p = pmmngr_free;
	m->unmap_page_p = unmap_page;


	driver_param_t* param = (driver_param_t*)pmmngr_alloc();
	param->mem = m;
	param->cpu = cpu;
	param->pci = pci;
	param->kdebug = printf;
	return param;
}
//!Driver Manager initializer
void driver_mngr_initialize (KERNEL_BOOT_INFO *info) {
	memset (drivers,0,sizeof(aurora_driver_t));
	driver_param_t *param = create_driver_parameter ();

	//!First of all register the pre-boot driver classes
	if (info->driver_entry1 != NULL) {  
		void* init_address = GetProcAddress (info->driver_entry1,"aurora_init_driver");
		void* close_address = GetProcAddress (info->driver_entry1, "aurora_close_driver");
		void* write_address = GetProcAddress(info->driver_entry1 ,"aurora_write");
		init i = (init)init_address;
		close c = (close)close_address;
		write w = (write)write_address;
	    uint32_t uid = request_driver_class_uid();
		drivers[uid].class_type = DRIVER_CLASS_AUDIO;
		drivers[uid].name = "sb16";
		drivers[uid].present = true;
		drivers[uid].aurora_init_driver = i;
		drivers[uid].aurora_close_driver = c;
		drivers[uid].aurora_write = w;
	}

	for (int i = 0; i < 256; i++) { 
		if (drivers[i].present)
			drivers[i].aurora_init_driver(param);
	}

}

void drv_mngr_write_driver (unsigned char* buffer, size_t length) {
	for (int i = 0; i < 256; i++) { 
		if (drivers[i].present)
			drivers[i].aurora_write(buffer, length);
	}
}