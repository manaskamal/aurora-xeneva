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
		*data = *raw_offset<volatile uint8_t*>(address, reg);
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
		*raw_offset<volatile uint8_t*>(address, reg) = data;
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
		*data = *raw_offset<volatile uint16_t*>(address, reg);
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


bool pci_find_device_class (uint8_t class_code, uint8_t sub_class, pci_device_info *addr_out, int *bus_, int *dev_, int *func_) {	
	pci_device_info config;
	acpiMcfg *mcfg = acpi_get_mcfg();
	acpiMcfgAlloc *alloc = mem_after<acpiMcfgAlloc*>(mcfg);
	//if (!acpi_pcie_supported()){
		for (int bus = 0; bus < 256; bus++) {
			for (int dev = 0; dev < 32; dev++) {
				for (int func = 0; func < 8; func++) {
					if (!acpi_pcie_supported()) {
						read_config_32 (0,bus, dev, func, 0, config.header[0]);
						read_config_header (bus, dev, func, &config);
						
						if (config.device.classCode == class_code && config.device.subClassCode == sub_class) {
							 *addr_out = config;
							 *bus_ = bus;
					         *dev_ = dev;
					         *func_ = func;
							 return true;
						}
					} else {
						uint32_t class_, subclass_;
						uint32_t result = 0;
						read_config_32_ext (alloc->pciSegment,bus, dev, func, 0x8, &result);
						class_ = (result >> 24) & 0xFF;
						subclass_ = (result >> 16) & 0xFF;
						if (class_ == 0xFF || class_ == 0x00)
							continue;

						//printf ("Class found -> %x, sub_class -> %x\n", class_, subclass_);
					   //read_config_header (bus, dev, func, &config);

						if (class_ == class_code && subclass_ == sub_class) {	
							uint32_t intLine = 0;
							read_config_32_ext(alloc->pciSegment, bus, dev, func, 0x3C, &intLine);
						    read_config_32_ext (alloc->pciSegment, bus, dev, func, 0x10, &config.device.nonBridge.baseAddress[0]);
				     	    read_config_32_ext (alloc->pciSegment, bus, dev, func, 0x14, &config.device.nonBridge.baseAddress[1]);
					        read_config_32_ext (alloc->pciSegment, bus, dev, func, 0x18, &config.device.nonBridge.baseAddress[2]);
					        read_config_32_ext (alloc->pciSegment,bus, dev, func, 0x1C, &config.device.nonBridge.baseAddress[3]);
					        read_config_32_ext (alloc->pciSegment, bus, dev, func, 0x20, &config.device.nonBridge.baseAddress[4]);
					
						    *addr_out = config;
						    addr_out->device.nonBridge.interruptLine = intLine & 0xff;
						    addr_out->device.nonBridge.interruptPin = (intLine >> 8) & 0xff;
						
					         *bus_ = bus;
					         *dev_ = dev;
					         *func_ = func;
					         return true;
						}
					}	
				}
			}
		}

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
		uint8_t capptr = 0;
		uint8_t cap_reg = 0, msi_reg = 0; 
		read_config_8 (0,bus, dev, func, 0x34, &capptr);
		/*capptr &= 0xFF; 
		capptr /= 4;*/
		while (capptr != 0) {
			read_config_8 (0,bus, dev, func, capptr, &cap_reg);
			if ((cap_reg & 0xff) == PCI_CAPABILITY_MSIX) {
				printf ("MSI-X found for this device\n");
				msi_reg = capptr;
				break;
			}

			if ((cap_reg & 0xff)  == PCI_CAPABILITY_MSI) {
				printf ("MSI found for this device\n");
				msi_reg = capptr;
				//break;
			}
			capptr = ((cap_reg >> 8) & 0xff);   //((cap_reg >> 8) & 0xFF) / 4;
			printf ("CAPPTR -> %x \n", capptr);
		}

		if (msi_reg == 0)
			return false;

		uint32_t vector = 60 + v_i;
		setvect (vector, fn);

		uint64_t msi_data = 0;
		uint64_t msi_addr = pci_get_msi_addr (&msi_data, vector, 0,0,0);
		printf ("MSI-DATA -> %x\n", msi_data);
		uint64_t internal_ptr = 0;
		read_config_8 (0, bus, dev, func, 32,&cap_reg);
		if ((cap_reg & 0xFF) == 0x11) { 
			//!MSI-X interrupt handling not implemented yet
		} else {
			uint64_t msgctrl = cap_reg >> 16;
			printf ("MSG Control -> %x\n", msgctrl);
			bool mask_cap = ((msgctrl & (1<<8)) != 0);
			bool bits64_cap = ((msgctrl & (1<<7)) != 0);
			uint32_t requested_vecs= (msgctrl >> 1) & 0x7;

			//! write msg and data
			write_config_32 (bus, dev, func, msi_reg + 1, (uint32_t)msi_addr);
			uint32_t data_offset = 2;
			if (bits64_cap) {
				printf ("MSI 64BIT Capable\n");
				write_config_32(bus, dev, func, msi_reg + 2, msi_addr >> 32);
				++data_offset;
			}
			write_config_32(bus,dev,func,msi_reg + data_offset,msi_data);
			if (mask_cap){
				printf ("MSI Mask Capable\n");
				write_config_32 (bus, dev, func, msi_reg + 4, 0);
			}
			//!Enable MSI
			msgctrl |= 0x1;
			cap_reg = (cap_reg & UINT16_MAX) | (msgctrl << 16);
			write_config_32 (bus, dev, func, msi_reg, cap_reg);
			printf ("MSI interrupt for this device enabled msi reg -> %x\n", msi_reg);
			v_i++;
			return true;
		}
	}
}


void pci_enable_bus_master (int bus, int dev, int func) {
	//command reg -> 0x4
	uint16_t command_reg = 0;
	read_config_16 (0,bus,dev,func,PCI_CONFREG_COMMAND_16, &command_reg);
	command_reg |= PCI_COMMAND_MASTERENABLE;
    write_config_16 (0,bus, dev,func,0x2,command_reg);
}

void pci_enable_interrupt (int bus, int dev, int func) {
	uint16_t command_reg = 0;
	read_config_16 (0,bus,dev,func,PCI_CONFREG_COMMAND_16, &command_reg);
	command_reg |= PCI_COMMAND_IOENABLE;
	command_reg |= PCI_COMMAND_MEMORYENABLE;
	command_reg &= ~PCI_COMMAND_INTERRUPTDISABLE;
    write_config_16 (0,bus, dev,func,PCI_CONFREG_COMMAND_16,command_reg);
}

void pci_enable_mem_space (int bus, int dev, int func) {
	uint16_t command_reg = 0;
	read_config_16 (0,bus,dev, func, 0x2, &command_reg);
	command_reg |= (1<<1);
	write_config_16(0,bus,dev,func,0x2,command_reg);
}


bool pcie_supported () {
	/*if (!acpi_pcie_supported ())
		return false;
	else 
		return true;*/
	return false;
}


void pci_detect () {
	pci_device_info config;
	for (int bus = 0; bus < 256; bus++) {
		for (int dev = 0; dev < 32; dev++) {
			for (int func = 0; func < 8; func++) {

				read_config_32 (0,bus, dev, func, 0, config.header[0]);

				read_config_header (bus, dev, func, &config);

				if (config.device.deviceID == 0xFFFF || config.device.vendorID == 0xFFFF) 
					continue;
				
				printf ("Device found -> %d, vendor -> %d \n", config.device.deviceID, config.device.vendorID);
			}
		}
	}
}

pci_cap_header *pci_get_capabilities(pci_device_info *dev, pci_cap_header* cap_header) {
	if (dev->device.statusReg & PCI_STATUS_CAPSLIST) {
		switch(dev->device.headerType & ~PCI_HEADERTYPE_MULTIFUNC) {
		case PCI_HEADERTYPE_NORMAL:
			if (cap_header){
				if (cap_header->next)
					cap_header = ((pci_cap_header*)dev + cap_header->next);
				else
					cap_header = NULL;
			}else {
				cap_header = ((pci_cap_header*)dev+ dev->device.nonBridge.capPtr);
			}
			break;
		default:
			cap_header = NULL;
			break;
		}
	}else{
		cap_header = NULL;
	}
	return cap_header;
}


void pci_print_capabilities (pci_device_info *dev) {
	pci_cap_header *cap_header = NULL;
	pci_msi_cap *msi_Cap = NULL;
	pci_msi_xcap *msi_xcap = NULL;

	if (dev->device.statusReg & PCI_STATUS_CAPSLIST) {
		cap_header = pci_get_capabilities(dev,cap_header);
		while (cap_header) {
			switch(cap_header->id) {
			case PCI_CAPABILITY_MSI:
				printf ("This device has MSI support \n");
				break;
			case PCI_CAPABILITY_MSIX:
				printf ("This device has MSIX support \n");
				break;
			default:
				break;
			}
			
			cap_header = pci_get_capabilities(dev,cap_header);
		}
	}
	
}

