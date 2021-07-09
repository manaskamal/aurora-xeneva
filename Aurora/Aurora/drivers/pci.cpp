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

#define PCI_MAX_BUS  0x20
#define PCI_REG_CONFIG_ADDRESS 0xCF8
#define PCI_REG_CONFIG_DATA 0xCFC


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

