/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  pci.h -- PCI Device Interface
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==================================================
 */

#ifndef __PCI_DEV_H__
#define __PCI_DEV_H__

#include <stdint.h>


//!PCI class
typedef struct _pci_address_ {
	uint8_t bus;
	uint8_t device;
	uint8_t function;
} pci_address;

#endif