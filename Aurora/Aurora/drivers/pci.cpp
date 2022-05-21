/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
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

#include <drivers\pci.h>
#include <hal.h>
#include <stdio.h>

#define PCI_ADDRESS_PORT  0xCF8
#define PCI_VALUE_PORT  0xCFC

int pci_decode_bus (uint32_t device) {
	return (uint8_t)((device >> 16));
}

int pci_decode_slot (uint32_t device) {
	return (uint8_t)((device >> 8));
}

int pci_decode_func (uint32_t device) {
	return (uint8_t)(device);
}

uint32_t pci_get_address(uint32_t device, int reg) {
	return 0x80000000 | (pci_decode_bus(device) << 16) | (pci_decode_slot(device) << 11) | (pci_decode_func(device) << 8) | 
		reg & 0x3F;
}


uint32_t pci_encode_device(uint32_t bus, uint32_t slot, uint32_t func) {
	return (uint32_t)((bus << 16)  |(slot << 8) | func);
}

uint32_t pci_read (uint32_t device, int reg) {
	int size = 0;
	switch(reg) {
	case PCI_VENDOR_ID:
		size = 2;
		break;
	case PCI_DEVICE_ID:
		size = 2;
		break;
	case PCI_COMMAND:
		size = 4;
		break;
	case PCI_STATUS:
		size = 2;
		break;
	case PCI_REVISION_ID:
		size = 1;
		break;
	case PCI_PROG_IF:
		size = 1;
		break;
	case PCI_SUBCLASS:
		size = 1;
		break;
	case PCI_CLASS:
		size = 1;
		break;
	case PCI_CACHE_LINE_SIZE:
		size = 1;
		break;
	case PCI_LATENCY_TIMER:
		size = 1;
		break;
	case PCI_HEADER_TYPE:
		size = 1;
		break;
	case PCI_BIST:
		size = 1;
		break;
	case PCI_BAR0:
		size = 4;
		break;
	case PCI_BAR1:
		size = 4;
		break;
	case PCI_BAR2:
		size = 4;
		break;
	case PCI_BAR3:
		size = 4;
		break;
	case PCI_BAR4:
		size = 4;
		break;
	case PCI_BAR5:
		size = 4;
		break;
	case PCI_INTERRUPT_LINE:
		size = 1;
		break;
	case PCI_INTERRUPT_PIN:
		size = 1;
		break;
	}

	x64_outportd(PCI_ADDRESS_PORT, pci_get_address(device, reg));

	if (size == 4) {
		uint32_t t = x64_inportd(PCI_VALUE_PORT);
		return t;
	}else if (size == 2) {
		uint16_t t =  x64_inportw(PCI_VALUE_PORT + (reg & 2)); //+ (reg & 2));
		return t;
	}else if (size == 1) {
		uint8_t t = x64_inportb (PCI_VALUE_PORT + (reg & 3));
		return t;
	}

	return 0xFFFF;
}

void pci_write (uint32_t device, int reg, uint32_t value) {
	if (reg == PCI_COMMAND) {
		reg = 2;
		unsigned short data = (unsigned short)value;
		unsigned addr = pci_get_address(device, reg/2);
		outportd(PCI_ADDRESS_PORT, addr);
		outportw((PCI_VALUE_PORT + (reg % 2)),data);
	}else {
		x64_outportd(PCI_ADDRESS_PORT, pci_get_address(device,reg));
		x64_outportd(PCI_VALUE_PORT, value);
	}
}

uint32_t pci_scan_class(uint8_t classcode, uint8_t subclass) {
	for (int bus = 0; bus < PCI_MAX_BUS; bus++) {
		for (int dev = 0; dev < PCI_DEVICE_PER_BUS; dev++) {
			for (int func = 0; func < PCI_FUNCTION_PER_DEVICE; func++) {
				uint32_t addr = pci_encode_device(bus,dev,func);
				uint32_t cc = pci_read(addr,PCI_CLASS);
				uint32_t sc = pci_read(addr,PCI_SUBCLASS);
				if (cc == 0xFF && sc == 0xFF)
					continue;
				if (cc == classcode && sc == subclass) 
					return addr;
			}
		}
	}
	return 0xFFFFFFFF;
}

uint32_t pci_scan_device(uint32_t vendid, uint32_t devid) {
	for (int dev = 0; dev < PCI_DEVICE_PER_BUS; dev++) {
		for (int func = 0; func < PCI_FUNCTION_PER_DEVICE; func++) {
			uint32_t addr = pci_encode_device(0,dev,func);
			uint32_t v = pci_read(addr,PCI_VENDOR_ID);
			uint32_t d = pci_read(addr,PCI_DEVICE_ID);
			if (v == vendid && d == devid) 
				return addr;
		}
	}

	return 0xFFFFFFFF;
}

void pci_enable_bus_master (uint32_t device) {
	uint32_t command = pci_read(device, PCI_COMMAND);
	command |= (1<<2);
	pci_write(device, PCI_COMMAND,command);
}

void pci_enable_interrupts (uint32_t device) {
	uint32_t command = pci_read(device, PCI_COMMAND);
	command &= ~(1<<10);
	pci_write(device,PCI_COMMAND,command);
}
