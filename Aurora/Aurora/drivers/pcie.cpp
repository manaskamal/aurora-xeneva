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
#include <arch\x86_64\mmngr\paging.h>
#include <arch\x86_64\cpu.h>

extern void debug_print (const char* text, ...);

uint64_t pci_express_get_device (uint16_t segment, int bus, int device, int function) {
	if (bus > 255)
		return 0;
	if (device > 31)
		return 0;
	if (function > 7)
		return 0;

	uint64_t addr = 0;
	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);
	if (allocs->startBusNum <= bus && bus <= allocs->endBusNum) {
		addr = allocs->baseAddress + ((bus - allocs->startBusNum) << 20) | (device << 15) | (function << 12);
		return addr;
	}

	return 0xFFFFFFFF;
}

uint32_t pci_express_read (uint64_t device, int reg, int bus,int dev,int func) {
	/*if(acpi_pcie_supported() == false) {
		return pci_read(device,reg);
	}*/
	uint32_t address = 0;
	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);
	if (allocs->startBusNum <= bus && bus <= allocs->endBusNum) {
		address = allocs->baseAddress + ((bus - allocs->startBusNum) << 20) | (device << 15) | (func << 12);
	}

	uint64_t result = 0;
	if (address == 0)
		return 0;


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
		size = 1;
		break;
	}

	if (size == 1){
		result = *raw_offset<volatile uint8_t*>(device,reg);
		return result;
	}else if (size == 2) {
		result = *raw_offset<volatile uint16_t*>(device, reg);
		return result;
	}else if (size == 4) {
		result = *raw_offset<volatile uint32_t*>(device,reg);
		return result;
	}

	return 0xFFFFFFFF;
}

uint64_t pci_express_read2 (uint64_t device, int reg, int size, int bus, int dev, int func) {
	if(acpi_pcie_supported() == false) {
		return 0;
	}

	size_t address = 0;
	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);
	if (allocs->startBusNum <= bus && bus <= allocs->endBusNum) 
		address = allocs->baseAddress + ((bus - allocs->startBusNum) << 20) | (device << 15) | (func << 12);

	if (address == 0)
		return 0;

	uint64_t result = 0;

	if (size == 1){
		result = *raw_offset<volatile uint8_t*>(device,reg);
		return result;
	}else if (size == 2) {
		result = *raw_offset<volatile uint16_t*>(device, reg);
		return result;
	}else if (size == 4) {
		result = *raw_offset<volatile uint32_t*>(device,reg);
		return result;
	}
	

	return UINT64_MAX;
}


void pci_express_write (uint64_t device, int reg, uint32_t val, int bus,int dev, int func) {
	if(acpi_pcie_supported() == false) {
		return; //pci_write(device,reg, val);
	}
	
	size_t address = 0;

	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);
	if (allocs->startBusNum <= bus && bus <= allocs->endBusNum) 
		address = allocs->baseAddress + ((bus - allocs->startBusNum) << 20) | (device << 15) | (func << 12);
	

	if (address == 0)
		return;
	
	reg = reg;
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
		*raw_offset<volatile uint8_t*>(device, reg) = (uint8_t)val;
	}else if (size == 2) {
		*raw_offset<volatile uint16_t*>(device, reg) = (uint16_t)val;
	}else if (size == 4) {
		*raw_offset<volatile uint32_t*>(device, reg) = (uint32_t)val;
	}
}

void pci_express_write2 (uint64_t device, int reg, int size,uint64_t val, int bus, int dev, int func) {
	if(acpi_pcie_supported() == false) {
		return; //pci_write(device,reg, val);
	}

	size_t address = 0;
	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);
	if (allocs->startBusNum <= bus && bus <= allocs->endBusNum) 
		address = allocs->baseAddress + ((bus - allocs->startBusNum) << 20) | (device << 15) | (func << 12) | (reg);


	if (size == 1){
		*raw_offset<volatile uint8_t*>(device, reg) = (uint8_t)val;
	}else if (size == 2) {
		*raw_offset<volatile uint16_t*>(device, reg) = (uint16_t)val;
	}else if (size == 4) {
		*raw_offset<volatile uint32_t*>(device, reg) = val;
	}
}



uint64_t pci_express_scan_class (uint8_t classCode, uint8_t subClassCode, int *bus_, int *dev_, int *func_) {
	if(acpi_pcie_supported() == false) {
		return 0; //pci_scan_class(classCode, subClassCode);
	}

	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);
	uint16_t pciSegment = 0;
	if (allocs->pciSegment <= 65535)
		pciSegment = allocs->pciSegment;
	else
		pciSegment = 0;

	for (int bus = 0; bus < allocs->endBusNum; bus++){
		for (int dev = 0; dev < PCI_DEVICE_PER_BUS; dev++) {
			for (int func = 0; func < PCI_FUNCTION_PER_DEVICE; func++) {
				uint64_t address = pci_express_get_device(pciSegment, bus,dev,func);
			
				if (address == 0xFFFFFFFF)
					continue;
				uint8_t class_code = pci_express_read(address,PCI_CLASS, bus,dev,func);
				uint8_t sub_ClassCode = pci_express_read(address, PCI_SUBCLASS, bus, dev, func);
				if (classCode == 0xFF || sub_ClassCode == 0xFF)
					continue;
				if(class_code == classCode && sub_ClassCode == subClassCode) {
					*bus_ = bus;
					*dev_ = dev;
					*func_ = func;
					return address;
				}
			}
		}
	}

	return 0xFFFFFFFF;
}

void pcie_alloc_msi (uint64_t device, size_t vector,  int bus, int dev, int func) {
	if (acpi_pcie_supported() == false)
		return;

	uint64_t status = pci_express_read2 (device,PCI_COMMAND, 4, bus, dev, func);
	status >>= 16;
	if ((status & (1<<4)) != 0) {
		uint32_t capptr = pci_express_read2(device,PCI_CAPABILITIES_PTR, 4, bus, dev, func);
		capptr &= 0xFF; 
		uint32_t cap_reg = 0;
		uint32_t msi_reg = 0;
		while (capptr != 0) {
			cap_reg = pci_express_read2(device,capptr, 4, bus, dev, func);
			if ((cap_reg & 0xff) == 0x5) {
				printf ("MSI found for this device, -> %x\n", cap_reg);
				msi_reg = cap_reg;
				uint16_t msctl = msi_reg >> 16;
				bool bit64_cap = (msctl & (1<<7));
				bool maskcap = (msctl & (1<<8));

				uint64_t msi_data = 0;
	
				uint32_t msi_addr = cpu_msi_address(&msi_data,vector,0,1,0);

				//*(uint32_t*)(cap_reg + 0x4) = msi_addr & UINT32_MAX;
				pci_express_write2(device, capptr + 0x4, 4, msi_addr & UINT32_MAX, bus, dev, func);

				if (bit64_cap) {
					pci_express_write2(device, capptr + 0x8, 4, msi_addr >> 32, bus, dev ,func);
					pci_express_write2(device, capptr + 0xC, 2, msi_data & UINT16_MAX, bus, dev, func);
				}else 
					pci_express_write2(device, capptr + 0x8, 2, msi_data & UINT16_MAX, bus, dev, func);
				
				
				if (maskcap) 
					pci_express_write2(device, capptr + 0x10, 4, 0, bus, dev, func);
				


				msctl |= 1;
				//pci_express_write2(device, capptr, 4,cap_reg, bus, dev, func);
				cap_reg = msi_reg & UINT16_MAX | msctl << 16;
				pci_express_write2(device, capptr, 4,  cap_reg & UINT32_MAX, bus, dev, func);
				uint32_t cap_reg2 = pci_express_read2(device, capptr, 4, bus, dev, func);
				break;
			}

			if ((cap_reg & 0xff)  == 0x11) {
				printf ("MSI-X found for this device\n");
				break;
			}
			capptr = ((cap_reg >> 8) & 0xff);   //((cap_reg >> 8) & 0xFF) / 4;
		}
	}
}