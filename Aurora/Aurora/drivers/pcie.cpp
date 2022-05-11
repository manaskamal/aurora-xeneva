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

#include <drivers\pcie.h>
#include <drivers\acpi\acpi.h>
#include <stdint.h>
#include <stdio.h>

extern void debug_print (const char* text, ...);

uint32_t pci_express_get_device (uint16_t segment, uint16_t bus, uint16_t device, uint16_t function) {
	if (bus > 255)
		return 0;
	if (device > 31)
		return 0;
	if (function > 7)
		return 0;

	uint32_t addr = 0;
	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);
	if (allocs->startBusNum <= bus && bus <= allocs->endBusNum) {
		addr = allocs->baseAddress + ((bus - allocs->startBusNum) << 20) | (device << 15) | (function << 12);
		return addr;
	}

	return 0xFFFFFFFF;
}

uint32_t pci_express_read (uint32_t device, int reg) {
	if(acpi_pcie_supported() == false) {
		return pci_read(device,reg);
	}

	size_t* address = (size_t*)device;
	uint32_t result = 0;

	int size = 0;
	switch(reg) {
	case PCI_VENDOR_ID:
		size = 2;
		break;
	case PCI_DEVICE_ID:
		size = 2;
		break;
	case PCI_COMMAND:
		size = 2;
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
	case PCI_CAPABILITIES_PTR:
		size = 1;
		break;
	case PCI_INTERRUPT_LINE:
		size = 1;
		break;
	case PCI_INTERRUPT_PIN:
		size = 1;
		break;
	default:
		size = 4;
		break;
	}

	if (size == 1){
		result = *raw_offset<volatile uint8_t*>(address, reg);
		return result;
	}else if (size == 2) {
		result = *raw_offset<volatile uint16_t*>(address, reg);
		return result;
	}else if (size == 4) {
		result = *raw_offset<volatile uint32_t*>(address, reg);
		return result;
	}

	return 0xFFFFFFFF;
}


uint32_t pci_express_read2 (uint32_t device, int reg, int size) {
	size_t* address = (size_t*)device;
	uint32_t result = 0;

	if (size == 1){
		result = *raw_offset<volatile uint8_t*>(address, reg);
		return result;
	}else if (size == 2) {
		result = *raw_offset<volatile uint16_t*>(address, reg);
		return result;
	}else if (size == 4) {
		result = *raw_offset<volatile uint32_t*>(address, reg);
		return result;
	}

	return 0xFFFFFFFF;
}


uint32_t pci_express_scan_class (uint8_t classCode, uint8_t subClassCode) {
	if(acpi_pcie_supported() == false) {
		return pci_scan_class(classCode, subClassCode);
	}

	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);

	for (int bus = 0; bus < allocs->endBusNum; bus++){
		for (int dev = 0; dev < PCI_DEVICE_PER_BUS; dev++) {
			for (int func = 0; func < PCI_FUNCTION_PER_DEVICE; func++) {
				uint32_t address = pci_express_get_device(allocs->pciSegment, bus,dev,func);
				//debug_print ("Dev Address ->%x \n", address);
				if (address == 0xFFFFFFFF)
					continue;
				uint32_t class_code = pci_express_read(address,PCI_CLASS);
				uint32_t sub_ClassCode = pci_express_read(address, PCI_SUBCLASS);
				//debug_print ("ClassCode -> %x, SubClass -> %x \n", classCode, sub_ClassCode);
				if(class_code == classCode && sub_ClassCode == subClassCode) {
					return address;
				}
			}
		}
	}

	return 0xFFFFFFFF;
}

void pcie_print_capabilities (uint32_t device) {
	uint32_t status = pci_express_read2 (device,PCI_COMMAND, 4);
	status >>= 16;
	if ((status & (1<<4)) != 0) {
		uint32_t capptr = pci_express_read2(device,PCI_CAPABILITIES_PTR, 4);
		capptr &= 0xFF; 
		uint32_t cap_reg = 0;
		while (capptr != 0) {
			cap_reg = pci_express_read2(device,capptr, 4);
			if ((cap_reg & 0xff) == 0x05) {
				printf ("MSI-X found for this device\n");
				break;
			}

			if ((cap_reg & 0xff)  == 0x11) {
				printf ("MSI found for this device\n");
				break;
			}
			capptr = ((cap_reg >> 8) & 0xff);   //((cap_reg >> 8) & 0xFF) / 4;
		}
	}
}