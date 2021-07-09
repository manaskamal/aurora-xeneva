/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  pci.h -- PCI Card device driver
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *============================================
 */

#ifndef __PCI_H__
#define __PCI_H__

#include <stdint.h>
#include <hal.h>


#define  PCI_CONFIG_PORT   0x0CF8
#define  PCI_DATA_PORT     0x0CFC

#define  PCI_MAX_BUSES       256
#define  PCI_MAX_DEVICES      32
#define  PCI_MAX_FUNCTIONS     8
#define  PCI_CONFIGHEADER_SIZE 256


#define  PCI_INVALID_CLASSCODE  -1
#define  PCI_INVALID_SUBCLASSCODE  -2

//! pci device info header types
#define  PCI_HEADERTYPE_NORMAL   0x00
#define  PCI_HEADERTYPE_BRIDGE   0x01
#define  PCI_HEADERTYPE_CARDBUS  0x02
#define  PCI_HEADERTYPE_MULTIFUNC  0x80

//! PCI configuration register numbers
#define  PCI_CONFREG_VENDORID_16    0
#define  PCI_CONFREG_DEVICEID_16    1
#define  PCI_CONFREG_COMMAND_16     2
#define  PCI_CONFREG_STATUS_16      3
#define  PCI_CONFREG_REVISONID_8    8
#define  PCI_CONFREG_PROGIF_8       9
#define  PCI_CONFREG_SUBCLASSCODE_8  10
#define PCI_CONFREG_CLASSCODE_8			11
#define PCI_CONFREG_CACHELINESIZE_8		12
#define PCI_CONFREG_LATENCY_8			13
#define PCI_CONFREG_HEADERTYPE_8		14
#define PCI_CONFREG_BIST_8				15
#define PCI_CONFREG_CLASSREG_32			2
#define PCI_CONFREG_BASEADDRESS0_32		4
#define PCI_CONFREG_BASEADDRESS1_32		5
#define PCI_CONFREG_BASEADDRESS2_32		6
#define PCI_CONFREG_BASEADDRESS3_32		7
#define PCI_CONFREG_BASEADDRESS4_32		8
#define PCI_CONFREG_BASEADDRESS5_32		9
#define PCI_CONFREG_INTLINE_8			60

// PCI device command bits
#define PCI_COMMAND_INTERRUPTDISABLE	0x0400
#define PCI_COMMAND_FASTBACK2BACK		0x0200
#define PCI_COMMAND_SYSTEMERROR			0x0100
#define PCI_COMMAND_WAITCYCLE			0x0080
#define PCI_COMMAND_PARITYERROR			0x0040
#define PCI_COMMAND_VGAPALSNOOP			0x0020
#define PCI_COMMAND_MEMWRITEINV			0x0010
#define PCI_COMMAND_SPECIALCYCLE		0x0008
#define PCI_COMMAND_MASTERENABLE		0x0004
#define PCI_COMMAND_MEMORYENABLE		0x0002
#define PCI_COMMAND_IOENABLE			0x0001

// PCI device status bits
#define PCI_STATUS_DETPARTIYERROR		0x8000
#define PCI_STATUS_SIGSYSTEMERROR		0x4000
#define PCI_STATUS_RECVMASTERABRT		0x2000
#define PCI_STATUS_RECVTARGETABRT		0x1000
#define PCI_STATUS_SIGTARGETABRT		0x0800
#define PCI_STATUS_DEVSEL_SLOW			0x0400
#define PCI_STATUS_DEVSEL_MEDIUM		0x0200
#define PCI_STATUS_DEVSEL_FAST			0x0000
#define PCI_STATUS_DATAPARITYERROR		0x0100
#define PCI_STATUS_FASTBACK2BACK		0x0080
#define PCI_STATUS_66MHZ				0x0020
#define PCI_STATUS_CAPSLIST				0x0010

// PCI 2.2 capability IDs
#define PCI_CAPABILITY_PMI				0x01  // Power Management Interface
#define PCI_CAPABILITY_AGP				0x02  // Accelerated Graphics Port
#define PCI_CAPABILITY_VPD				0x03  // Vital Product Data
#define PCI_CAPABILITY_SLOTID			0x04  // Expansion slot identification
#define PCI_CAPABILITY_MSI				0x05  // Message Signaled Interrupts
#define PCI_CAPABILITY_CPHS				0x06  // CompactPCI Hot Swapping
// PCI 3.0 capability IDs
#define PCI_CAPABILITY_PCIX				0x07  // PCI-X
#define PCI_CAPABILITY_HYPERTRANS		0x08  // Hypertransport
#define PCI_CAPABILITY_VENDORSPEC		0x09  // Vendor-specific
#define PCI_CAPABILITY_DEBUGPORT		0x0A  // Debug port
#define PCI_CAPABILITY_CPCIRESCONT		0x0B  // CompactPCI cent. res. control
#define PCI_CAPABILITY_PCIHOTPLUG		0x0C  // PCI hot-plug
#define PCI_CAPABILITY_AGP8X			0x0E  // AGP 8x (?)
#define PCI_CAPABILITY_SECUREDEVICE		0x0F  // Secure device
#define PCI_CAPABILITY_PCIEXPRESS		0x10  // PCI Express
#define PCI_CAPABILITY_MSIX				0x11  // MSI-X

// MSI message control bitfields
#define PCI_MSI_MSGCTRL_64BIT			0x0080
#define PCI_MSI_MSGCTRL_MULTIMSGEN		0x0070
#define PCI_MSI_MSGCTRL_MULTIMSGCAP		0x00E0
#define PCI_MSI_MSGCTRL_MSIENABLE		0x0001

// MSI-X message control bitfields
#define PCI_MSIX_MSGCTRL_MSIXEN			0x8000
#define PCI_MSIX_MSGCTRL_TABLESIZE		0x07FF

#define PCI_IRQ_ROUTINGTABLE_SIG		"$PIR"

#define offsetof(type, member)  ((uint32_t)(&((type*)NULL)->member))


#pragma pack (push)

typedef union _pci_config_space_ {
	uint32_t words[16];
	struct {
		uint16_t vendor_id;
		uint16_t device_id;
		uint16_t command;
		uint16_t status;
		uint16_t revision_id;
		uint8_t  subclass;
		uint8_t  class_code;
		uint8_t  cache_line_size;
		uint8_t  lat_timer;
		uint8_t  header_type;
		uint8_t  bist;
		uint32_t BAR[6];
		uint32_t card_bus_cis;
		uint16_t sub_sys_vendor_id;
		uint16_t sub_sys_id;
		uint32_t expansion_rom_addr;
		uint32_t reserved0;
		uint32_t reserved1;
		uint8_t  intr_line;
		uint8_t  intr_pin;
		uint8_t  min_grant;
		uint8_t  max_latency;
	};
} pci_config_space;

#pragma pack (pop)

typedef struct _pci_address_ {
	uint8_t bus;
	uint8_t device;
	uint8_t function;
} pci_address;

typedef struct _pci_scan_state_ {
	uint16_t vendor_id;
	uint16_t device_id;
	pci_address next_addr;
	pci_address addr;
}pci_scan_state;

#define PCI_CONF_BAR_IO  0x01
#define PCI_CONF_BAR_64BIT 0x04
#define PCI_CONF_BAR_PREFETCH  0x08

extern uint32_t pci_config_read32 (const pci_address *addr, uint16_t offset);
extern uint16_t pci_config_read16 (const pci_address *addr, uint16_t offset);
extern uint8_t  pci_config_read8 (const pci_address *addr, uint16_t offset);
extern void pci_config_write32 (const pci_address *addr, uint16_t offset, uint32_t data);
extern void pci_config_write16 (const pci_address *addr, uint16_t offset, uint16_t data);
extern void pci_config_write8 (const pci_address *addr, uint16_t offset, uint8_t data);

extern bool pci_scan_bus (pci_scan_state *state);
extern bool pci_find_device (uint16_t vendor_id, uint16_t device_id, pci_address *addr_out);
extern void pci_setBAR (const pci_address *addr, int index, uint32_t value);
extern uint32_t pci_get_bar_addr (const pci_address *addr, int index);
extern void pci_set_mem_enable (const pci_address *addr, bool enabe);


#endif