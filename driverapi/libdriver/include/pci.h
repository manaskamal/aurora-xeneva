/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  pci.h -- PCI Device Interface
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==================================================
 */

#ifndef __PCI_DEV_H__
#define __PCI_DEV_H__

#include <stdint.h>

#define  PCI_CONFIG_PORT   0x0CF8
#define  PCI_DATA_PORT     0x0CFC

#define  PCI_MAX_BUSES       256
#define  PCI_MAX_DEVICES      32
#define  PCI_MAX_FUNCTIONS     8
#define  PCI_CONFIGHEADER_SIZE 256


//!PCI class
typedef struct _pci_address_ {
	uint8_t bus;
	uint8_t device;
	uint8_t function;
} pci_address;


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
#endif