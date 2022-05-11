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

#include <audrv.h>
#include <pe.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <string.h>
#include <fs\fat\fat.h>
#include <pmmngr.h>
#include <drivers\pci.h>


/* Drivers are located from 4 MiB of kernel address */
#define AU_DRIVER_BASE_START   0xFFFFC00000400000  

//!Global Variable for the program
aurora_driver_t *drivers[256];
static uint32_t driver_class_unique_id = 0;
static uint64_t driver_load_base = 0;

//! request an unique id for driver class
uint32_t AuRequestDriverId () {
	uint32_t uid = driver_class_unique_id;
	driver_class_unique_id++;
	return uid;
}

//! decreaments an unique id for driver class in order to free
void AuDecreaseDriverId () {
	driver_class_unique_id--;
}


/* 
 * AuGetConfEntry -- Get an entry offset in the file for required device
 * @param vendor_id -- vendor id of the product
 * @param device_id -- device id of the product
 * @param buffer -- configuration file buffer
 * @param entryoff -- entry offset from where search begins
 */
char* AuGetConfEntry(uint32_t vendor_id, uint32_t device_id,uint8_t* buffer,int entryoff) {
re:
	int entry_num = entryoff;
	char* fbuf = (char*)buffer;
	/* Check the entry for the device */
search:
	char* p = strchr(fbuf,'(');
	if (p) {
		p++;
		fbuf++;
	}
	int entret = atoi(p);
	
	/* Check for last entry '(0)' it indicates that
	 * there is no more entry
	 */
	if (entret == 0) {
		return 0;
	}

	if (entret != entry_num)
		goto search;


	/* Search for vendor id of the product */
	fbuf = p;
	p = strchr(fbuf,'[');
	int venid ,devid = 0;
	if (p)
		p++;

	fbuf = p;
	char num[2];
	memset(num, 0, 2);
	int i;
	for (i= 0; i < 2; i++) {
		if (p[i] == ',' || p[i] == ']')
			break;
		num[i] = p[i];
		fbuf++;
	}
	num[i]=0;
	venid = atoi(num);

	/* Now search for device id / product id */
	p = strchr(fbuf,',');
	if (p)
		p++;
	for (int i = 0; i < 2; i++) {
		if (p[i] == ',' || p[i] == ']')
			break;
		num[i] = p[i];
	}
	num[i] = 0;
	devid = atoi(num);


	if (vendor_id != venid || devid != device_id) {
		entryoff++;
		goto re;
	}

	/* Finally we found the device driver */
	if (vendor_id == venid && devid == device_id) {
		return fbuf;
	}

	return 0;
}

void AuCreateDriverInstance (char* drivername) {
	aurora_driver_t *driver = (aurora_driver_t*)malloc(sizeof(aurora_driver_t));
	memset(driver, 0, sizeof(aurora_driver_t));
	strcpy(driver->name, drivername);
	driver->id = AuRequestDriverId();
	driver->present = false;
	drivers[driver->id] = driver;

}

/* 
 * AuGetDriverName -- Extract the driver path from its entry offset 
 * @param vendor_id -- vendor id of the product
 * @param device_id -- device id of the product
 * @param buffer -- configuration file buffer
 * @param entryoff -- entry offset from where search begins
 */
void AuGetDriverName (uint32_t vendor_id, uint32_t device_id,uint8_t* buffer,int entryoff) {

	/* Get the entry offset for required device driver */
	char* offset = AuGetConfEntry(vendor_id, device_id, buffer, entryoff);

	if (offset == NULL)
		return;
	char *p = strchr(offset, ']');
	if (p)
		p++;

	/* get the driver path */
	char drivername[32];
	memset(drivername,0, 32);
	int i = 0;
	for (i = 0; i < 32; i++) {
		if(p[i] == '|')
			break;
		drivername[i] = p[i];
	}

	drivername[i] = 0;

	AuCreateDriverInstance(drivername);
	return;
}

/*
 * AuDriverLoad -- Manage and loads dll drivers
 * @param filename -- file path
 * @param driver -- driver instance
 */
void AuDriverLoad (char* filename, aurora_driver_t *driver) {
	int next_base_offset = 0;
	uint64_t* virtual_base = (uint64_t*)driver_load_base;

	vfs_node_t file = fat32_open(NULL, filename);
	uint64_t* buffer = (uint64_t*)AuPmmngrAlloc();
	memset(buffer, 0, 4096);
	fat32_read(&file, buffer);
	AuMapPage((uint64_t)buffer,driver_load_base,0);
	next_base_offset = 1;
	

	while(file.eof != 1) {
		uint64_t* block = (uint64_t*)AuPmmngrAlloc();
		memset(block, 0, 4096);
		fat32_read (&file,block);
		AuMapPage((uint64_t)block,(driver_load_base + next_base_offset * 4096), 0);
		next_base_offset++;
	}


	void* entry_addr = AuGetProcAddress((void*)driver_load_base,"AuDriverMain");
	void* unload_addr = AuGetProcAddress((void*)driver_load_base,"AuDriverUnload");

	AuPeLinkLibrary(virtual_base);
	driver->entry = (au_drv_entry)entry_addr;
	driver->unload = (au_drv_unload)unload_addr;
	driver->base = AU_DRIVER_BASE_START;
	driver->end = driver->base + file.size;
	driver->present = true;
	driver_load_base = driver_load_base + next_base_offset * 4096;
}

/* 
 * AuDrvMngrInitialize -- Initialize the driver manager
 * @param info -- kernel boot info
 */
void AuDrvMngrInitialize (KERNEL_BOOT_INFO *info) {
	driver_class_unique_id = 0;
	driver_load_base = AU_DRIVER_BASE_START;
	printf ("[aurora]: initializing drivers, please wait... \n");
	/* Load the conf data */
	uint64_t* conf = (uint64_t*)p2v((size_t)AuPmmngrAlloc());
	memset(conf, 0, 4096);
	vfs_node_t file = fat32_open(NULL, "/audrv.cnf");
	int filesize = file.size / 1024;
	if(filesize < 4096)
		fat32_read(&file,(uint64_t*)v2p((size_t)conf));

	uint8_t* confdata = (uint8_t*)conf;

	for (int bus = 0; bus < 256; bus++) {
		for (int dev = 0; dev < 32; dev++) {
			for (int func = 0; func < 8; func++) {

				uint32_t addr = pci_encode_device(bus,dev,func);
				uint32_t vendid = pci_read(addr, PCI_VENDOR_ID);
				uint32_t devid = pci_read(addr, PCI_DEVICE_ID);
				uint32_t classCode = pci_read(addr, PCI_CLASS);
				uint32_t subClass = pci_read(addr, PCI_SUBCLASS);
				if (devid == 0xFFFF || vendid == 0xFFFF) 
					continue;	
				AuGetDriverName(classCode,subClass,  confdata,1);
				for(int i = 0; i < 1000; i++)
					;
			}
		}
	}

	/* Serially call each startup entries of each driver */
	for (int i = 0; i < driver_class_unique_id; i++) {
		aurora_driver_t *driver = drivers[i];
		AuDriverLoad(driver->name, driver);
		driver->entry();
	}
}



