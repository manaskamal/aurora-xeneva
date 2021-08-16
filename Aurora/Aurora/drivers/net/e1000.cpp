/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  e1000.h -- Intel Ethernet i217 driver
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#include <drivers\net\e1000.h>
#include <pmmngr.h>
#include <stdio.h>
#include <console.h>


uint64_t e1000_base = 0;
uint64_t e1000_mem_base = 0;
bool eerprom_exists = false;
uint32_t e1000_irq = 0;
uint8_t mac[6];


uint32_t e1000_read_command (uint16_t p_address) {
	x64_outportd (e1000_base,p_address);
	return x64_inportd (e1000_base + 4);
}

void e1000_write_command (uint16_t p_address, uint32_t p_value) {
	x64_outportd (e1000_base, p_address);
	x64_outportd (e1000_base + 4, p_value);
}

bool e1000_detect_eeprom () {
	
	uint32_t val = 0;
	e1000_write_command (REG_EEPROM, 0x1);

	for (int i = 0; i < 1000 && ! eerprom_exists; i++) {
		val = e1000_read_command (REG_EEPROM);
		if (val & 0x10)
			eerprom_exists = true;
		else
			eerprom_exists = false;
	}

	return eerprom_exists;
}


uint32_t e1000_eerprom_read (uint8_t addr) {
	
	uint16_t data = 0;
	uint32_t tmp = 0;
	if (eerprom_exists) {
		e1000_write_command (REG_EEPROM, (1) | ((uint32_t)(addr) << 8));
		while (! ((tmp = e1000_read_command (REG_EEPROM)) & (1 << 4)));
	} else {
		e1000_write_command ( REG_EEPROM, (1) | ((uint32_t)(addr) << 2));
		while (!((tmp = e1000_read_command (REG_EEPROM)) & (1 << 1)));
	}
	data = (uint16_t)((tmp >> 16) & 0xFFFF);
	return data;
}


bool e1000_read_mac_address () {
	if (eerprom_exists) {
		printf ("EEPROM exist\n");
		uint32_t temp;
		temp = e1000_eerprom_read (0);
		mac[0] = temp & 0xff;
		mac[1] = temp >> 8;
		temp = e1000_eerprom_read (1);
		mac[2] = temp & 0xff;
		mac[3] = temp >> 8;
		temp = e1000_eerprom_read (2);
		mac[4] = temp & 0xff;
		mac[5] = temp >> 8;
	} else {
		printf ("Applying memory map\n");
		uint8_t * mem_base_mac_8 = (uint8_t*)(e1000_mem_base + 0x5400);
		uint32_t * mem_base_mac_32 = (uint32_t*) (e1000_mem_base + 0x5400);
		if (mem_base_mac_32[0] != 0) {
			for (int i = 0; i < 6; i++) {
				mac[i] = mem_base_mac_8[i];
			}
		}else {
			return false;
		}
	}

	return true;
}

void e1000_interrupt_handler (size_t v, void* p) {
	printf ("E1000 Interrupt fired\n");
	//apic_local_eoi();
	interrupt_end(e1000_irq);
}
	

void e1000_setup_interrupt () {
	e1000_write_command (REG_IMASK, 0x1F6DC);
	e1000_write_command (REG_IMASK, 0xff & ~4);
	e1000_read_command (0xc0);
}


void e1000_initialize () {
	pci_device_info *dev = (pci_device_info*)pmmngr_alloc();
	if (!pci_find_device_class (0x02,0x00,dev)) {
		printf ("Intel Ethernet not found\n");
	}

	e1000_base = dev->device.nonBridge.baseAddress[2] & ~1;  //TODO:Auto search 
	e1000_mem_base = dev->device.nonBridge.baseAddress[4] & ~3;  //TODO:Auto search  4
	printf ("E1000 Base -> %x, mmio-> %x\n", e1000_base, e1000_mem_base);
	e1000_irq = dev->device.nonBridge.interruptLine;
	e1000_detect_eeprom();
	if (e1000_read_mac_address()) {
		printf ("E1000 MAC address received\n");
		printf ("E1000 MAC Address -> \n");
		for (int i = 0; i < 6; i++)
			printf ("%c", mac[i]);
	}

	//interrupt_set (dev->device.nonBridge.interruptLine, e1000_interrupt_handler,dev->device.nonBridge.interruptLine);
	e1000_setup_interrupt();

	pci_print_capabilities(dev);
}
