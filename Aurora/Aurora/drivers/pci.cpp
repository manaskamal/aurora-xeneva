/**
 *  Copyright (C) Manas Kamal Choudhury
 *
 *  pci.cpp -- PCI Configurations for Hardware devices
 *
 *  /PROJECT - Aurora {Xeneva }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =======================================================
 */

#include <drivers\pci.h>
#include <stdio.h>

#define PCI_MAX_BUS  0x20
#define PCI_REG_CONFIG_ADDRESS 0xCF8
#define PCI_REG_CONFIG_DATA 0xCFC

#define header_address(bus,device,function,reg) \
	(0x80000000L | (((unsigned) ((bus) & 0xFF) << 16) |  \
	(((device) & 0x1F) << 11) | (((function) & 0x7) << 8) | \
	((reg) & 0x3F) << 2))


static uint32_t pci_config_pack_address (const pci_address *addr, uint16_t offset) {

	const uint32_t enable_bit = 0x80000000UL;

	return (((uint32_t)addr->bus << 16) |
		((uint32_t)addr->device << 11) |
		((uint32_t)addr->function << 8) |
		offset | enable_bit);
}


uint32_t pci_config_read32 (const pci_address *addr, uint16_t offset) {
	outportd (PCI_REG_CONFIG_ADDRESS, pci_config_pack_address (addr, offset));
	return inportd (PCI_REG_CONFIG_DATA);
}


void  read_config_32 (int bus, int dev, int function, int reg, uint32_t data)
{
	//! read configuration dword
	unsigned address = header_address (bus, dev, function, reg);
	x64_outportd (PCI_CONFIG_PORT, address);
	data = x64_inportd (PCI_DATA_PORT);
}

void  read_config_16 (int bus, int dev, int function, int reg, unsigned short *data )
{
	//! read configuration word
	unsigned address = header_address (bus, dev, function, (reg / 2));
	x64_outportd (PCI_CONFIG_PORT, address);
	*data = x64_inportw (PCI_DATA_PORT + (reg % 2));
}


void  write_config_16 (int bus, int dev, int function, int reg, unsigned short data )
{
	//! write configuration word
	unsigned address = header_address (bus, dev, function, (reg / 2));
	x64_outportd (PCI_CONFIG_PORT, address);
	x64_outportw ((PCI_DATA_PORT + (reg % 2)), data);
}


uint16_t pci_config_read16 (const pci_address *addr, uint16_t offset) {
	outportd (PCI_REG_CONFIG_ADDRESS, pci_config_pack_address (addr, offset));
	return inportw (PCI_REG_CONFIG_DATA);
}

uint8_t pci_config_read8 (const pci_address *addr, uint16_t offset) {
	outportd (PCI_REG_CONFIG_ADDRESS, pci_config_pack_address (addr, offset));
	return inportb (PCI_REG_CONFIG_DATA);
}

void pci_config_write32 (const pci_address *addr, uint16_t offset, uint32_t data) {
	outportd (PCI_REG_CONFIG_ADDRESS, pci_config_pack_address (addr, offset));
	outportd (PCI_REG_CONFIG_DATA, data);
}

void pci_config_write16 (const pci_address *addr, uint16_t offset, uint16_t data) {
	outportd (PCI_REG_CONFIG_ADDRESS, pci_config_pack_address (addr, offset));
	outportw (PCI_REG_CONFIG_DATA, data);
}

void pci_config_write8 (const pci_address *addr, uint16_t offset, uint8_t data) {
	outportd (PCI_REG_CONFIG_ADDRESS, pci_config_pack_address(addr, offset));
	outportb (PCI_REG_CONFIG_DATA, data);
}


void read_config_header (int bus, int dev, int function, pci_device_info *dev_info)
{
	unsigned address = 0;
	int reg;

	for (reg = 0; reg < (PCI_CONFIGHEADER_SIZE / 4); reg ++)
	{
		address = header_address (bus, dev, function, reg);
		x64_outportd (PCI_CONFIG_PORT, address);
		dev_info->header[reg] = x64_inportd(PCI_DATA_PORT);
	}
}


bool pci_scan_bus (pci_scan_state *state) {
	pci_config_space config;
	
	for (;;) {
		config.words[0] = pci_config_read32(&state->next_addr, 0);

		state->addr = state->next_addr;

		if (++state->next_addr.function == 0x8) {
			state->next_addr.function = 0;
			if (++state->next_addr.device == 0x20) {
				state->next_addr.device = 0;
				if (++state->next_addr.bus == PCI_MAX_BUS) {
					return false;
				}
			}
		}

		if (config.words[0] != 0xFFFFFFFFUL) {
			state->vendor_id = config.vendor_id;
			state->device_id = config.device_id;
			state->subclass = config.subclass;
			state->class_code = config.class_code;
			return true;
		}
	}
}


bool pci_find_device (uint16_t vendor_id, uint16_t device_id, pci_address *addr_out) {
	pci_scan_state bus_scan = {};

	while (pci_scan_bus (&bus_scan)) {
		if (bus_scan.vendor_id == vendor_id && bus_scan.device_id == device_id) {
			*addr_out = bus_scan.addr;
			return true;
		}
	}

	return false;
}

bool pci_find_device_class (uint8_t class_code, uint8_t sub_class, pci_device_info *addr_out) {
	pci_device_info config;
	printf ("PCI Scanning device\n");
	for (int bus = 0; bus < 256; bus++) {
		for (int dev = 0; dev < 32; dev++) {
			for (int func = 0; func < 8; func++) {
				uint16_t command_reg = 0;

				read_config_32 (bus, dev, func, 0, config.header[0]);

				read_config_header (bus, dev, func, &config);

				if (config.device.classCode == class_code && config.device.subClassCode == sub_class) {
					*addr_out = config;
					read_config_16 (bus,dev,func,PCI_CONFREG_COMMAND_16, &command_reg);
					command_reg |= PCI_COMMAND_IOENABLE;
					command_reg |= PCI_COMMAND_MEMORYENABLE;
					command_reg |= PCI_COMMAND_MASTERENABLE;
					command_reg &= ~PCI_COMMAND_INTERRUPTDISABLE;
				    write_config_16 (bus, dev,func,PCI_CONFREG_COMMAND_16,command_reg);
					return true;
				}
				
			}
		}
	}

	return false;
}


bool pci_find_device_id (uint16_t device_id, uint16_t vendor_id, pci_device_info *addr_out) {
	pci_device_info config;
	printf ("PCI Scanning device\n");
	for (int bus = 0; bus < 256; bus++) {
		for (int dev = 0; dev < 32; dev++) {
			for (int func = 0; func < 8; func++) {

				read_config_32 (bus, dev, func, 0, config.header[0]);

				read_config_header (bus, dev, func, &config);

				if (config.device.deviceID == device_id && config.device.vendorID == vendor_id) {
					*addr_out = config;
					printf ("Device found\n");
					printf ("Device ID -> %x, Vendor ID -> %x\n", config.device.deviceID, config.device.vendorID);
					return true;
				}
			}
		}
	}

	return false;
}

void pci_setBAR (const pci_address *addr, int index, uint32_t value) {
	pci_config_write32 (addr, offsetof (pci_config_space,BAR[index]),value);
}


uint32_t pci_get_bar_addr (const pci_address *addr, int index) {
	uint32_t bar = pci_config_read32 (addr, offsetof (pci_config_space, BAR[index]));
	uint32_t mask = (bar & PCI_CONF_BAR_IO) ? 0x3 : 0xf;

	return bar & ~mask;
}


void pci_set_mem_enable (const pci_address *addr, bool enable) {
	uint16_t command = pci_config_read16 (addr, offsetof (pci_config_space, command));

	const uint16_t flags = 0x0007;

	if (enable) {
		command |= flags;
	}else {
		command &= ~flags;
	}

	pci_config_write16 (addr, offsetof (pci_config_space, command), command);
}

pci_cap_header * pci_get_capability (pci_device_info *dev_info, pci_cap_header* cap_header) {
	
	if (!dev_info) 
		return NULL;

	if ((dev_info->device.statusReg & (1<<4)) != 0) {

		switch (dev_info->device.headerType & ~PCI_HEADERTYPE_MULTIFUNC) {
		case PCI_HEADERTYPE_NORMAL:
			if (cap_header) {
				if (cap_header->next){
					cap_header = ((pci_cap_header*)dev_info + cap_header->next);
					//printf ("Cap Header next is not null\n");
				}else
					cap_header = NULL;
			} else {
				cap_header = ((pci_cap_header*)dev_info + 0xD);
			//	printf ("CAp PTR\n");
				//printf ("CAp Hdr nxt %x\n", cap_header->next);
			}
			break;

		default:
			cap_header = NULL;
			break;
		}
	} else {
		cap_header = NULL;
	}

	return cap_header;
}

void pci_print_capabilities (pci_device_info *dev_info) {

	pci_cap_header *cap_header = NULL;
	pci_msi_cap *msi_cap = NULL;
	pci_msi_xcap *msi_x_cap = NULL;

	uint64_t *capptr;
	if ((dev_info->device.statusReg & (1<<4)) != 0) {
		cap_header = (pci_cap_header*)(dev_info + dev_info->device.nonBridge.capPtr);
		while (cap_header->next != 0x00) {
			if (cap_header->id == 0x05) {
				printf ("MSI Available\n");
			}

			if (cap_header->id == 0x11) {
				printf ("MSI-X Available for this device\n");
			}
			cap_header = (pci_cap_header*)(cap_header + cap_header->next);
		}
	}
}



