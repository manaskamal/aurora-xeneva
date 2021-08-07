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
	driver_param_t* param = (driver_param_t*)pmmngr_alloc();
	param->kdebug = printf;
	param->irq_eoi = apic_local_eoi;
	param->interrupt_set = interrupt_set;
	param->pci_find_device = pci_find_device;
	param->pci_get_bar = pci_get_bar_addr;
	param->pci_set_mem_enable = pci_set_mem_enable;
	param->malloc = alloc;
	param->get_phys_address = get_physical_address;
	return param;
}
//!Driver Manager initializer
void driver_mngr_initialize (KERNEL_BOOT_INFO *info) {

	
   
	memset (drivers,0,sizeof(aurora_driver_t));

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

    driver_param_t *param = create_driver_parameter ();
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