/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *   ACPI.h -- Advanced Configuration and Power Interface
 *
 *  /PROJECT - Aurora Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ============================================================
 */

#ifndef __ACPI_XE_H__
#define __ACPI_XE_H__


#include <stdint.h>

//APIC structure types
#define ACPI_APICTYPE_LAPIC  0
#define ACPI_APICTYPE_IOAPIC 1


#define ACPI_SIG_RSDP     "RSD PTR "
#define ACPI_SIG_APIC     "APIC"
#define ACPI_SIG_DSDT     "DSDT"
#define ACPI_SIG_FADT     "FACP"
#define ACPI_SIG_FACS     "FACS"
#define ACPI_SIG_PSDT     "PSDT"
#define ACPI_SIG_RSDT     "RSDT"
#define ACPI_SIG_SSDT     "SSDT"
#define ACPI_SIG_SBST     "SBST"

//FACS flags
#define ACPI_FACSFL_S4BIOS   0x00000001

//! Power management control block command
#define ACPI_PMCTRL_SCI_EN   0x0001
#define ACPI_PMCTRL_BM_RLD   0x0002
#define ACPI_PMCTRL_GBL_RLS  0x0004
#define ACPI_PMCTRL_SLP_TYPX 0x1C00
#define ACPI_PMCTRL_SLP_EN   0x2000


//ACPI Version 2.0 definitions
#define ACPI_SIG_ECDT   "ECDT"
#define ACPI_SIG_OEMX   "OEM"
#define ACPI_SIG_XSDT   "XSDT"
#define ACPI_SIG_BOOT   "BOOT"
#define ACPI_SIG_CPEP   "CPEP"
#define ACPI_SIG_DBGP   "DBGP"
#define ACPI_SIG_ETDT   "ETDT"
#define ACPI_SIG_HPET   "HPET"
#define ACPI_SIG_SLIT   "SLIT"
#define ACPI_SIG_SPCR   "SPCR"
#define ACPI_SIG_SRAT   "SRAT"
#define ACPI_SIG_SPMI   "SPMI"
#define ACPI_SIG_TCPA   "TCPA"

//! APIC structure type
#define ACPI_APICTYPE_ISOVER   2
#define ACPI_APICTYPE_NMI      3
#define ACPI_APICTYPE_LAPIC_NMI  4
#define ACPI_APICTYPE_LAPIC_AOS  5
#define ACPI_APICTYPE_IOSAPIC    6
#define ACPI_APICTYPE_LSAPIC     7
#define ACPI_APICTYPE_PLATIS     8

//! ACPI Version 3.0 definitions
#define ACPI_SIG_BERT     "BERT"     //Boot Error Record Table
#define ACPI_SIG_DMAR     "DMAR"     //DMA Remapping Table
#define ACPI_SIG_ERST     "ERST"     //Error Record Serialization Table
#define ACPI_SIG_HEST     "HEST"     //Hardware error source table
#define ACPI_SIG_IBFT     "IBFT"     // iSCSI Boot firmware table
#define ACPI_SIG_MCFG     "MCFG"
#define ACPI_SIG_UEFI     "UEFI"    //UEFI ACPI Boot Optimization Table
#define ACPI_SIG_WAET     "WAET"    // Windows ACPI Enlightenment Table
#define ACPI_SIG_WDAT     "WDAT"   // Watchdog action table
#define ACPI_SIG_WDRT     "WDRT"   // Watchdog resource table
#define ACPI_SIG_WSPT     "WSPT"

// ACPI Version 4.0 Definitions
#define ACPI_SIG_EINJ     "EINJ"  // Error injection table
#define ACPI_SIG_MSCT     "MSCT"  // Max System Characteristics Table
#define ACPI_SIG_PSDT     "PSDT"  // Persistent System DT
#define ACPI_SIG_IVRS     "IVRS"  // I/O Virt Reporting Structure
#define ACPI_SIG_MCHI     "MCHI"  // Mgmt Ctrllr Host Interface Table

// FACS Flags
#define ACPI_FACSFL_64BITWAKE  0x00000002 // 64-bit waking vector support

//!source from Visopsys Operating System
#pragma pack (push,1)
// ACPI version 2.0 structures
typedef struct 
{
	unsigned char addrSpaceId;
	unsigned char regBitWidth;
	unsigned char regBitOffset;
	unsigned char addrSize;
	uint64_t address;
} acpiGenAddr;

//! ACPI version 1.0 structures
typedef struct _rsdp_ 
{
	char signature[8];
	unsigned char checksum;
	char oemId[6];
	unsigned char revision;
	unsigned rsdtAddr;

	unsigned length;
	uint64_t xsdtAddr;
	unsigned char xChecksum;
	unsigned char res[3];
} acpiRsdp;

typedef struct _acpiSysDesc
{
	char signature[4];
	unsigned length;
	unsigned char revision;
	unsigned char checksum;
	char oemId[6];
	char oemTableId[8];
	unsigned oemRevision;
	unsigned creatorId;
	unsigned creatorRevision;
} acpiSysDescHeader;


//! Root System Descriptor Table
typedef struct 
{
	acpiSysDescHeader header;
	unsigned entry[];
} acpiRsdt;

typedef struct _acpi_apic_header_
{
	unsigned char type;
	unsigned char length;
} acpiApicHeader;

typedef struct
{
	acpiApicHeader header;
	unsigned char procId;
	unsigned char lapicId;
	unsigned flags;
} acpiLocalApic;

typedef struct
{
	acpiApicHeader header;
	unsigned char ioApicId;
	unsigned char res;
	unsigned int ioApicAddr;
	unsigned gsiBase;
}acpiIoApic;

typedef struct
{
	acpiSysDescHeader header;
	unsigned localApicAddr;
	unsigned flags;
    size_t entry[];
}acpiMadt;

typedef struct
{
	acpiSysDescHeader header;
	unsigned facsAddr;
	unsigned dsdtAddr;
	unsigned char intMode;
	unsigned char res1;
	unsigned short sciInt;
	unsigned sciCmdPort;
	unsigned char acpiEnable;
	unsigned char acpiDisable;
	unsigned char s4BiosReq;
	unsigned char res2;
	unsigned pm1aEventBlock;
	unsigned pm1bEventBlock;
	unsigned pm1aCtrlBlock;
	unsigned pm1bCtrlBlock;
	unsigned pm2CtrlBlock;
	unsigned pmTimerBlock;
	unsigned genEvent0Block;
	unsigned genEvent1Block;
	unsigned char pm1EventBlockLen;
	unsigned char pm1CtrlBlockLen;
	unsigned char pm2CtrlBlockLen;
	unsigned char pmTimerBlockLen;
	unsigned char genEvent0BlockLen;
	unsigned char genEvent1BlockLen;
	unsigned char genEvent1Bbase;
	unsigned char res3;
	unsigned short c2Latency;
	unsigned short c3Latency;
	unsigned short flushSize;
	unsigned short flushStride;
	unsigned char dutyOffset;
	unsigned char dutyWidth;
	unsigned char dutyAlarm;
	unsigned char century;
	unsigned short bootArch;
	unsigned char res4[1];
	unsigned flags;
	// Fields added in ACPI 2.0
	acpiGenAddr resetReg;
	unsigned char resetValue;
	unsigned char res5[3];
	uint64_t xFacsAddr;
	uint64_t xDsdtAddr;
	acpiGenAddr xPm1aEventBlock;
	acpiGenAddr xPm1bEventBlock;
	acpiGenAddr xPm1aCtrlBlock;
	acpiGenAddr xPm1bCtrlBlock;
	acpiGenAddr xPm2CtrlBlock;
	acpiGenAddr xPmTimerBlock;
	acpiGenAddr xGenEvent0Block;
	acpiGenAddr xGenEvent1Block;

} acpiFadt;

//! Firmware ACPI Control structure
typedef struct
{
	char signature[4];
	unsigned length;
	unsigned hardwareSig;
	unsigned wakingVector;
	unsigned globalLock;
	unsigned flags;
	// Fields added in ACPI 2.0 (version field >= 1)
	uint64_t xWakingVector;
	unsigned char version;
	// Fields added in ACPI 4.0 (version field >= 2)
	unsigned char res1[3];
	unsigned ospmFlags;
	// Padding
	unsigned char res2[24];
} acpiFacs;

typedef struct
{
	acpiSysDescHeader header;
	unsigned char data[];
} acpiDsdt;


typedef struct 
{
	acpiApicHeader header;
	uint8_t id;
	uint8_t reserved;
	uint32_t global_irq_base;
	uint64_t address;
} acpiIsOver;

typedef struct
{
	acpiSysDescHeader header;
	uint64_t entry[];
} acpiXsdt;

typedef struct
{
	acpiSysDescHeader header;
	unsigned char cmosIndex;
	unsigned char res[3];
} acpiBoot;

typedef struct {
	acpiSysDescHeader header;
	uint8_t reserved[8];
} acpiMcfg;

typedef struct {
	uint64_t baseAddress;
	uint16_t pciSegment;
	uint8_t  startBusNum;
	uint8_t  endBusNum;
	uint32_t reserved;
} acpiMcfgAlloc;

//! Standard kernel ACPI header for kernel use only
typedef struct _aurora_acpi_ 
{
	unsigned char revision;
	acpiMadt *madt;
	acpiFadt *fadt;
	acpiFacs *facs;
	acpiDsdt *dsdt;
	acpiMcfg *mcfg;
	uint16_t slp_typa;
	uint16_t slp_typb;
	uint8_t  num_cpu;
}aurora_acpi;

typedef struct _apic_interrupt_override_
{
	acpiApicHeader header;
	uint8_t bus;
	uint8_t source;
	uint32_t interrupt;
	uint16_t flags;
}apic_interrupt_override;

typedef struct _acpi_table_srat_x_
{
	acpiSysDescHeader  Header;         /* Common ACPI Table Header */
	uint32_t           TableRevision;  /* Must be value '1' */
	uint64_t           Reserved;       /* Reserved, must be zero */
}acpi_table_srat_xe;


typedef struct _acpi_sub_tab_
{
	uint8_t    type;
	uint8_t    length;
}acpi_sub_table;

#pragma pack (pop)
enum acpi_srat_type
{
	acpi_srat_type_cpu_affinity =        0,
	acpi_srat_type_memory_affinity =     1,
	acpi_srat_type_x2apic_cpu_affinity = 2,
	acpi_srat_type_gicc_affinity  =      3,
	acpi_srat_type_gic_its_affinity =    4,   //! ACPI 6.2 
	acpi_srat_type_generic_affinity =    5,   //! ACPI 6.3
	acpi_srat_type_reserved =            6    //! 5 and greater are reserved
};

#pragma pack(push,1)
typedef struct _acpi_srat_mem_affinity_
{
	acpi_sub_table header;
	uint32_t proximity_domain;
	uint16_t reserved;
	uint64_t base_address;
	uint64_t length;
	uint32_t reserved1;
	uint32_t flags;
	uint64_t reserved2;
}acpi_srat_mem_affinity;
#pragma pack(pop)

#define APIC_TYPE_INTERRUPT_OVERRIDE 2


//! initialize acpi subsystem
extern void AuInitializeBasicAcpi (void* acpi_base);
extern void acpi_parse_madt ();
extern void acpi_system_reboot ();
extern uint8_t* search_s5 (acpiDsdt* header);
extern void acpi_shutdown ();
extern bool acpi_pcie_supported ();
extern acpiMcfg *acpi_get_mcfg ();
/*
 * AuGetNumCPU -- get the total number
 * of cpu
 */
extern uint8_t AuGetNumCPU ();
#endif