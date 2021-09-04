/**
 *  Copyright (C) Manas Kamal Choudhury
 *
 *  pci.cpp -- PCI/PCIe Configurations for Hardware devices
 *
 *  /PROJECT - Aurora {Xeneva }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =======================================================
 */

#include <drivers\pci.h>
#include <stdio.h>
#include <drivers\acpi\acpi.h>

/** Legacy PCI port configurations **/
#define PCI_MAX_BUS  0x20
#define PCI_REG_CONFIG_ADDRESS 0xCF8
#define PCI_REG_CONFIG_DATA 0xCFC

#define header_address(bus,device,function,reg) \
	(0x80000000L | (((unsigned) ((bus) & 0xFF) << 16) |  \
	(((device) & 0x1F) << 11) | (((function) & 0x7) << 8) | \
	((reg) & 0x3F) << 2))


//! Configuration space pack address
static uint32_t pci_config_pack_address (const pci_address *addr, uint16_t offset) {

	const uint32_t enable_bit = 0x80000000UL;

	return (((uint32_t)addr->bus << 16) |
		((uint32_t)addr->device << 11) |
		((uint32_t)addr->function << 8) |
		offset | enable_bit);
}

//! Read Configuration space 4 byte
uint32_t pci_config_read32 (const pci_address *addr, uint16_t offset) {
	outportd (PCI_REG_CONFIG_ADDRESS, pci_config_pack_address (addr, offset));
	return inportd (PCI_REG_CONFIG_DATA);
}

/**
 * Iterate through PCIe to get correct memory mapped address
 */
uint64_t pcie_find_device (uint16_t segment, int bus, int dev, int func) {
	if (bus > 255)
		return 0;
	if (dev > 31)
		return 0;
	if (func > 7)
		return 0;
	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc* allocs = mem_after<acpiMcfgAlloc*>(mcfg);
	for (; raw_diff(allocs, mcfg) < mcfg->header.length; ++allocs) {
		if (allocs->startBusNum <= bus && bus <= allocs->endBusNum)
			break;
	}
	if (raw_diff(allocs, mcfg) >= mcfg->header.length)
		return 0;
	uint64_t addr = allocs->baseAddress + ((bus - allocs->startBusNum) << 20) | (dev << 15) | (func << 12);
	return addr;
}


/** Read Configuration space 1 byte **/
void read_config_8 (uint16_t segment, int bus, int dev, int function, int reg, unsigned char* data) {
	if (!acpi_pcie_supported()){
		unsigned address = header_address (bus, dev, function, (reg / 4));
		x64_outportd (PCI_CONFIG_PORT, address);
		*data = x64_inportb ((PCI_DATA_PORT + (reg % 4)));
	}else {
		uint64_t addr = pcie_find_device(segment, bus, dev, function);
		if (addr == 0)
			return;
		void *address = (void*)addr;
		*data = *raw_offset<volatile uint8_t*>(address, reg * 4);
	}
}

/** Write configuration space 1 byte **/
void write_config_8 (uint16_t segment, int bus, int dev, int func, int reg, unsigned char data) {
	if (!acpi_pcie_supported()) {
		unsigned address = header_address (bus, dev, func, (reg / 4));
		outportd (PCI_CONFIG_PORT, address);
		outportb (PCI_DATA_PORT + (reg % 4), data);
	}else {
		uint64_t addr = pcie_find_device(segment, bus, dev, func);
		if (addr == 0)
			return;
		void *address = (void*)addr;
		*raw_offset<volatile uint8_t*>(address, reg * 4) = data;
	}
}

/**
 * Read Configuration space 4 byte 
 **/
void read_config_32 (uint16_t segment,int bus, int dev, int function, int reg, uint32_t data)
{
	if (!acpi_pcie_supported()) {
		//! read configuration dword
		unsigned address = header_address (bus, dev, function, reg);
		x64_outportd (PCI_CONFIG_PORT, address);
		data = x64_inportd (PCI_DATA_PORT);
	}else {
		uint64_t addr = pcie_find_device(segment, bus, dev, function);
		if (addr == 0)
			return;
		void *address = (void*)addr;
		data = *raw_offset<volatile uint32_t*>(address, reg * 4);
	}
}

/**
 * Same as read_config_32 instead here data is used as pointer
 */
void  read_config_32_ext (uint16_t segment,int bus, int dev, int function, int reg, uint32_t *data)
{
	if (!acpi_pcie_supported()) {
		//! read configuration dword
		unsigned address = header_address (bus, dev, function, reg);
		x64_outportd (PCI_CONFIG_PORT, address);
		*data = x64_inportd (PCI_DATA_PORT);
	}else {
		uint64_t addr = pcie_find_device(segment, bus, dev, function);
		if (addr == 0)
			return;
		void *address = (void*)addr;
		*data = *raw_offset<volatile uint32_t*>(address, reg);
		//printf ("Data returned -> %x\n", *data);
	}
}

/**
 * Write config in 4 bytes
 */
void write_config_32 (int bus, int dev, int func, int reg, unsigned data) {
	//! write
	unsigned address = header_address (bus, dev, func, reg);
	x64_outportd (PCI_CONFIG_PORT, address);
	x64_outportd (PCI_DATA_PORT, data);
}

/**
 * Read config space in word
 */
void  read_config_16 (uint16_t segment,int bus, int dev, int function, int reg, unsigned short *data )
{
	if (!acpi_pcie_supported()) {
		//! read configuration word
		unsigned address = header_address (bus, dev, function, (reg / 2));
		x64_outportd (PCI_CONFIG_PORT, address);
		*data = x64_inportw (PCI_DATA_PORT + (reg % 2));
	}else {
		uint64_t addr = pcie_find_device(segment, bus, dev, function);
		if (addr == 0)
			return;
		void *address = (void*)addr;
		*data = *raw_offset<volatile uint16_t*>(address, reg * 4);
	}
}

/**
 * Write config space in word
 */
void  write_config_16 (uint16_t segment,int bus, int dev, int function, int reg, unsigned short data )
{
	if (!acpi_pcie_supported()) {
		//! write configuration word
		unsigned address = header_address (bus, dev, function, (reg / 2));
		x64_outportd (PCI_CONFIG_PORT, address);
		x64_outportw ((PCI_DATA_PORT + (reg % 2)), data);
	}else {
		uint64_t addr = pcie_find_device(segment, bus, dev, function);
		if (addr == 0)
			return;
		void *address = (void*)addr;
		*raw_offset<volatile uint16_t*>(address, reg * 4) = data;
	}
}


//!======================================================================
//! implemented for SVGA driver
//!=====================================================================

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


//!!
//!!   Scan a bus
//!! 
//!! only used in svga driver
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


//!===========================================================================
//! End of SVGA implementation
//!=============================================================================

void read_config_header (int bus, int dev, int function, pci_device_info *dev_info)
{
	if (!acpi_pcie_supported()) {
		unsigned address = 0;
		int reg;

		for (reg = 0; reg < (PCI_CONFIGHEADER_SIZE / 4); reg ++)
		{
			address = header_address (bus, dev, function, reg);
			x64_outportd (PCI_CONFIG_PORT, address);
			dev_info->header[reg] = x64_inportd(PCI_DATA_PORT);
		}
	} 
}


/**
 * PCIe Stuff
 */
uint8_t pcie_get_header_type (uint16_t segment, uint16_t bus, uint16_t device, uint16_t function) {
	uint32_t result;
	read_config_32_ext (segment, bus, device, function, 0x3, &result);
	return (result >> 16) & 0xFF;
}

uint32_t pcie_get_classcode (uint16_t segment, uint8_t bus, uint8_t device, uint8_t function) {
	uint32_t result;
	read_config_32_ext (segment, bus, device, function, 0x2, &result);
	return (result >> 8) & 0xFFFFFF;
}

uint32_t pcie_get_subclass (uint16_t segment, uint8_t bus, uint8_t device, uint8_t function) {
	uint32_t result;
	read_config_32_ext (segment, bus, device, function, 0x2, &result);
	return (result >> 16) & 0xFF;
}

uint16_t pcie_get_vendor_id (uint16_t segment, uint16_t bus, uint16_t device, uint16_t function) {
	uint32_t result;
	read_config_32_ext (segment, bus, device, function, 0x0, &result);
	return result & 0xFFFF;
}

uint16_t pcie_get_secondary_bus (uint16_t segment, uint16_t bus, uint16_t device, uint16_t function) {
	uint32_t result;
	read_config_32_ext (segment,bus, device, function, 6, &result);
	return (result >> 8) & 0xFF;
}


bool pcie_check_function (uint16_t segment, uint16_t bus, uint16_t device, uint16_t function);

bool pcie_check_device (uint16_t segment, uint16_t bus, uint16_t device) {

	uint8_t function = 0;

	uint16_t vendor_id = pcie_get_vendor_id (segment, bus, device, function);
	if (vendor_id == 0xFFFF) return false;
	if (pcie_check_function(segment, bus, device, function))
		return true;

	uint16_t header_type = pcie_get_header_type(segment, bus, device, function);
	if ((header_type & 0x80) != 0) {
		printf ("Multi functional device\n");
		for (function = 1; function < 8; function++) {
			if (pcie_get_vendor_id (segment, bus, device, function) != 0xFFFF) {
				if (pcie_check_function(segment, bus, device, function)) 
					return true;
			}
		}
	}
	return false;
}
bool pcie_check_bus (uint16_t segment, uint16_t bus) {
	uint8_t device;

	for (device = 0; device < 32; device++) {
		if (pcie_check_device (segment, bus, device))
			return true;
	}
	return false;
}

bool pcie_check_function (uint16_t segment, uint16_t bus, uint16_t device, uint16_t function) {
	uint8_t base_class;
	uint8_t sub_class;
	uint8_t secondary_bus;

	if ((pcie_get_classcode (segment, bus, device, function) >> 8) == 0x0604) {
		secondary_bus = pcie_get_secondary_bus (segment, bus, device, function);
		return true;
	} 

	return false;
}


bool pcie_check_all_bus (uint16_t segment, uint16_t startbus, uint16_t endbus) {
	uint8_t function;
	uint8_t bus;

	if (startbus != 0)
		return pcie_check_bus (segment, startbus);

	uint8_t header_type = pcie_get_header_type (segment, startbus, 0, 0);
	if ((header_type & 0x80) == 0) {
		printf ("Single PCIe Host controller\n");
		if (pcie_check_bus (segment, startbus))
			return true;
	}
}


//!============================================================================
//!  PCIE implementation 
//!============================================================================

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



bool pci_find_device_class (uint8_t class_code, uint8_t sub_class, pci_device_info *addr_out, int *bus_, int *dev_, int *func_) {	
	pci_device_info config;
	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *alloc = mem_after<acpiMcfgAlloc*>(mcfg);
	//if (!acpi_pcie_supported()){
	/**
	 * Use legacy PCI method
	 */
		for (int bus = 0; bus < 256; bus++) {
			for (int dev = 0; dev < 32; dev++) {
				for (int func = 0; func < 8; func++) {
					uint16_t command_reg;

					uint32_t class_, subclass_;
					uint32_t result = 0;
					read_config_32_ext (alloc->pciSegment,bus, dev, func, 0x8, &result);
					class_ = (result >> 24) & 0xFF;
					subclass_ = (result >> 16) & 0xFF;

					read_config_32_ext (alloc->pciSegment, bus, dev, func, 0x10, &config.device.nonBridge.baseAddress[0]);
					read_config_32_ext (alloc->pciSegment, bus, dev, func, 0x14, &config.device.nonBridge.baseAddress[1]);
					read_config_32_ext (alloc->pciSegment, bus, dev, func, 0x18, &config.device.nonBridge.baseAddress[2]);
					read_config_32_ext (alloc->pciSegment,bus, dev, func, 0x1C, &config.device.nonBridge.baseAddress[3]);
					read_config_32_ext (alloc->pciSegment, bus, dev, func, 0x20, &config.device.nonBridge.baseAddress[4]);
					
					if (class_ == 0xFF || class_ == 0x00)
						continue;
					//printf ("Class found -> %x, sub_class -> %x\n", class_, subclass_);
					//read_config_header (bus, dev, func, &config);

					if (class_ == class_code && subclass_ == sub_class) {
						//printf ("Device Found on pcie bus -> %d.%d.%d\n", bus, dev, func);
						*addr_out = config;
						//command reg -> 0x4
						read_config_16 (0,bus,dev,func,0x4, &command_reg);
					    command_reg |= (1<<2);
					    command_reg &= ~(1<<10);
				        write_config_16 (0,bus, dev,func,0x4,command_reg);
					    *bus_ = bus;
					    *dev_ = dev;
					    *func_ = func;
					     return true;
				    }
				}
			}
		}
	//} else {
	//	acpiMcfg *mcfg = acpi_get_mcfg();
	//	acpiMcfgAlloc *alloc = mem_after<acpiMcfgAlloc*>(mcfg);
	//	for(; raw_diff(alloc, mcfg) < mcfg->header.length; ++alloc) {
	//		pcie_check_all_bus (alloc->pciSegment, alloc->startBusNum, alloc->endBusNum);
	//	}
	//}
	return false;
}


bool pci_find_device_id (uint16_t device_id, uint16_t vendor_id, pci_device_info *addr_out) {
	pci_device_info config;
	for (int bus = 0; bus < 256; bus++) {
		for (int dev = 0; dev < 32; dev++) {
			for (int func = 0; func < 8; func++) {

				read_config_32 (0,bus, dev, func, 0, config.header[0]);

				read_config_header (bus, dev, func, &config);

				if (config.device.deviceID == device_id && config.device.vendorID == vendor_id) {
					*addr_out = config;
					return true;
				}
			}
		}
	}

	return false;
}


//! Get MSI address
uint64_t pci_get_msi_addr (uint64_t* data, size_t vector, uint32_t processor, uint8_t edge_trigger, uint8_t deassert) {

	*data = (vector & 0xFF) | (edge_trigger == 1 ? 0 : (1 << 15)) | (deassert == 1 ? 0 : (1 << 14));
	return (0xFEE00000 | (processor << 12));
}

int v_i = 0;
/**
 * Check for MSI and MSI-x Capabilities
 */
bool pci_alloc_msi (int func, int dev, int bus, void (*fn)(size_t, void* p)) {
	
	pci_cap_header *cap_header = NULL;
	pci_msi_cap *msi_cap = NULL;
	pci_msi_xcap *msi_x_cap = NULL;


	uint32_t status = 0;
	read_config_32_ext (0,bus, dev, func, 0x4,&status);
	status >>= 16;
	if (status & (1<<4)) {
		uint32_t capptr = 0, cap_reg = 0, msi_reg = 0; 
		read_config_32_ext (0,bus, dev, func, 0x34, &capptr);
		/*capptr &= 0xFF;
		capptr /= 4;*/
		while (capptr != 0) {
			read_config_32_ext (0,bus, dev, func, capptr, &cap_reg);
			if ((cap_reg & 0xFF) == PCI_CAPABILITY_MSIX) {
				printf ("MSI-X found for this device\n");
				msi_reg = capptr;
				break;
			}

			if ((cap_reg & 0xFF) == PCI_CAPABILITY_MSI) {
				printf ("MSI found for this device\n");
				msi_reg = capptr;
				break;
			}
			capptr = ((cap_reg >> 8) & 0xFF) / 4;
		}

		if (msi_reg == 0)
			return false;
		uint32_t vector = 60 + v_i;
		setvect (vector, fn);

		uint64_t msi_data = 0;
		uint64_t msi_addr = pci_get_msi_addr (&msi_data, vector, 0,1,0);

		uint64_t internal_ptr = 0;
		read_config_32_ext (0, bus, dev, func, 32,&cap_reg);
		if ((cap_reg & 0xFF) == 0x11) { 
			//!MSI-X interrupt handling not implemented yet
		} else {
			uint32_t msgctrl = (cap_reg >> 16);
			bool mask_cap = ((msgctrl & (1<<8)) != 0);
			bool bits64_cap = ((msgctrl & (1<<7)) != 0);
			uint32_t requested_vecs= (msgctrl >> 1) & 0x7;

			//! write msg and data
			write_config_32 (bus, dev, func, msi_reg + 1, msi_addr & UINT32_MAX);
			uint32_t data_offset = 2;
			if (bits64_cap) {
				write_config_32(bus, dev, func, msi_reg + 2, msi_addr >> 32);
				++data_offset;
			}
			if (mask_cap){
				write_config_32 (bus, dev, func, msi_reg + 4, 0);
			}
			//!Enable MSI
			msgctrl |= 1;
			cap_reg = (cap_reg & UINT16_MAX) | (msgctrl << 16);
			write_config_32 (bus, dev, func, msi_reg, cap_reg);
			printf ("MSI interrupt for this device enabled msi reg -> %x\n", msi_reg);
			v_i++;
		}
	}
}




