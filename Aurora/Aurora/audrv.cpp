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
aurora_driver_t drivers[256];
static uint32_t driver_class_unique_id = 0;

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
	char num[5];
	memset(num, 0, 5);
	int i;
	for (i= 0; i < 5; i++) {
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
	for (int i = 0; i < 5; i++) {
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

	printf ("Drivername -> %s\n", drivername);
}


/* 
 * AuDrvMngrInitialize -- Initialize the driver manager
 * @param info -- kernel boot info
 */
void AuDrvMngrInitialize (KERNEL_BOOT_INFO *info) {
	driver_class_unique_id = 0;

	/* Load the conf data */
	uint64_t* conf = (uint64_t*)AuPmmngrAlloc();
	memset(conf, 0, 4096);
	vfs_node_t file = fat32_open(NULL, "/audrv.cnf");
	fat32_read_file (&file,conf,file.size);

	uint8_t* confdata = (uint8_t*)conf;

	pci_device_info config;
	for (int bus = 0; bus < 256; bus++) {
		for (int dev = 0; dev < 32; dev++) {
			for (int func = 0; func < 8; func++) {

				read_config_32 (0,bus, dev, func, 0, config.header[0]);
				read_config_header (bus, dev, func, &config);
				if (config.device.deviceID == 0xFFFF || config.device.vendorID == 0xFFFF) 
					continue;	
				AuGetDriverName(config.device.vendorID,config.device.deviceID,  confdata,1);
			}
		}
	}

	printf ("Search over \n");
}

