/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  pci.h -- PCI/PCI Express Card device driver
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

#pragma pack(push)
// This structure is adapted from Ralf Brown's CPI configuration data dumper
typedef union {
	struct {
		unsigned short vendorID;					// 00 - 01
		unsigned short deviceID;					// 02 - 03
		unsigned short commandReg;					// 04 - 05
		unsigned short statusReg;					// 06 - 07
		unsigned char revisionID;					// 08
		unsigned char progIF;						// 09
		unsigned char subClassCode;					// 0A
		unsigned char classCode;					// 0B
		unsigned char cachelineSize;				// 0C
		unsigned char latency;						// 0D
		unsigned char headerType;					// 0E
		unsigned char BIST;							// 0F
		union {
			struct {
				unsigned char reserved1[44];		// 10 - 3B
				unsigned char interruptLine;		// 3C
				unsigned char interruptPin;			// 3D
				unsigned char reserved2[194];		// 3E - FF
			} all;
			struct {
				unsigned baseAddress[6];			// 10 - 27
				unsigned cardBusCIS;				// 28 - 2B
				unsigned short subsystemVendorID;	// 2C - 2D
				unsigned short subsystemDeviceID;	// 2E - 2F
				unsigned expansionROM;				// 30 - 33
				unsigned char capPtr;				// 34
				unsigned char reserved1[3];			// 35 - 37
				unsigned reserved2;					// 38 - 3B
				unsigned char interruptLine;		// 3C
				unsigned char interruptPin;			// 3D
				unsigned char minGrant;				// 3E
				unsigned char maxLatency;			// 3F
				unsigned deviceSpecific[48];		// 40 - FF
			} nonBridge;
			struct {
				unsigned baseAddress[2];			// 10 - 17
				unsigned char primaryBus;			// 18
				unsigned char secondaryBus;			// 19
				unsigned char subordinateBus;		// 1A
				unsigned char secondaryLatency;		// 1B
				unsigned char ioBaseLow;			// 1C
				unsigned char ioLimitLow;			// 1D
				unsigned short secondaryStatus;		// 1E - 1F
				unsigned short memoryBaseLow;		// 20 - 21
				unsigned short memoryLimitLow;		// 22 - 23
				unsigned short prefetchBaseLow;		// 24 - 25
				unsigned short prefetchLimitLow;	// 26 - 27
				unsigned prefetchBaseHigh;			// 28 - 2B
				unsigned prefetchLimitHigh;			// 2C - 2F
				unsigned short ioBaseHigh;			// 30 - 31
				unsigned short ioLimitHigh;			// 32 - 33
				unsigned reserved2;					// 34 - 37
				unsigned expansionROM;				// 38 - 3B
				unsigned char interruptLine;		// 3C
				unsigned char interruptPin;			// 3D
				unsigned short bridgeControl;		// 3E - 3F
				unsigned deviceSpecific[48];		// 40 - FF
			} bridge;
			struct {
				unsigned exCaBase;					// 10 - 13
				unsigned char capPtr;				// 14
				unsigned char reserved05;			// 15
				unsigned short secondaryStatus;		// 16 - 17
				unsigned char pciBus;				// 18
				unsigned char bardBusBus;			// 19
				unsigned char subordinateBus;		// 1A
				unsigned char latencyTimer;			// 1B
				unsigned memoryBase0;				// 1C - 1F
				unsigned memoryLimit0;				// 20 - 23
				unsigned memoryBase1;				// 24 - 27
				unsigned memoryLimit1;				// 28 - 2B
				unsigned short ioBase0Low;			// 2C - 2D
				unsigned short ioBase0High;			// 2E - 2F
				unsigned short ioLimit0Low;			// 30 - 31
				unsigned short ioLimit0High;		// 32 - 33
				unsigned short ioBase1Low;			// 34 - 35
				unsigned short ioBase1High;			// 36 - 37
				unsigned short ioLimit1Low;			// 38 - 39
				unsigned short ioLimit1High;		// 3A - 3B
				unsigned char interruptLine;		// 3C
				unsigned char interruptPin;			// 3D
				unsigned short bridgeControl;		// 3E - 3F
				unsigned short subsystemVendorID;	// 40 - 41
				unsigned short subsystemDeviceID;	// 42 - 43
				unsigned legacyBaseAddr;			// 44 - 47
				unsigned cardbusReserved[14];		// 48 - 7F
				unsigned vendorSpecific[32];		// 80 - FF
			} cardBus;
		};
	} device;
	unsigned header[PCI_CONFIGHEADER_SIZE / 4];

}pci_device_info;
#pragma pack(pop)

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
	uint8_t  subclass;
	uint8_t  class_code;
}pci_scan_state;

#pragma pack(push,1)
typedef struct {
	uint16_t id;								// 00
	uint16_t next;								// 01
} pci_cap_header;
#pragma pack(pop)

typedef struct {
	pci_cap_header header;							// 00 - 01
	unsigned short msgCtrl;							// 02 - 03
	void *msgAddr;									// 04 - 07
	unsigned short msgData;							// 08 - 09

} pci_msi_cap;

typedef struct {
	pci_cap_header header;							// 00 - 01
	unsigned short msgCtrl;							// 02 - 03
	void *msgAddr;									// 04 - 07
	void *msgUpperAddr;								// 08 - 0B
	unsigned short msgData;							// 0C - 0D

} pci_msi_cap64;

typedef struct {
	pci_cap_header header;							// 00 - 01
	unsigned short msgCtrl;							// 02 - 03
	void *msgUpperAddr;								// 04 - 07
	unsigned tableOffBir;							// 08 - 0B

} pci_msi_xcap;


#define PCI_CONF_BAR_IO  0x01
#define PCI_CONF_BAR_64BIT 0x04
#define PCI_CONF_BAR_PREFETCH  0x08


extern void read_config_header (int bus, int dev, int function, pci_device_info *dev_info);
extern void  read_config_16 (uint16_t segment,int bus, int dev, int function, int reg, unsigned short *data );
extern void  write_config_16 (uint16_t segment,int bus, int dev, int function, int reg, unsigned short data );
extern void  read_config_32 (uint16_t segment, int bus, int dev, int function, int reg, uint32_t data);
extern void read_config_8 (uint16_t segment,int bus, int dev, int function, int reg, unsigned char* data);
extern void write_config_8 (uint16_t segment,int bus, int dev, int func, int reg, unsigned char data);

extern bool pci_find_device (uint16_t vendor_id, uint16_t device_id, pci_address *addr_out);
extern void pci_set_mem_enable (const pci_address *addr, bool enabe);
extern bool pci_find_device_class (uint8_t class_code, uint8_t sub_class, pci_device_info *addr_out, int *bus, int *dev, int *func);
extern bool pci_find_device_id (uint16_t device_id, uint16_t vendor_id, pci_device_info *addr_out);
extern bool pci_alloc_msi (int func, int dev, int bus, void (*fn)(size_t, void* p));
extern void pci_enable_bus_master (int bus, int dev, int func);
extern void pci_enable_interrupt (int bus, int dev, int func);
extern bool pcie_supported ();
#endif