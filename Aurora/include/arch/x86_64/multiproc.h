/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  multiproc.h -- Multi Processor Spec
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#ifndef __MULTIPROC_H__
#define __MULTIPROC_H__

#define MULTIPROC_SIG_FLOAT    "_MP_"
#define MULTIPROC_SIG_CONFIG   "PCMP"

//! configuration table entry types
#define MULTIPROC_ENTRY_CPU    0
#define MULTIPROC_ENTRY_BUS    1
#define MULTIPROC_ENTRY_IOAPIC 2
#define MULTIPROC_ENTRY_IOINTASSMT 3
#define MULTIPROC_ENTRY_LOCINTASSMT 4

//! Cpu flags
#define MULTIPROC_CPUFLAG_ENABLED  0x01
#define MULTIPROC_CPUFLAG_BOOT     0x02

//! Bus type strings
#define MULTIPROC_BUSTYPE_CBUS    "CBUS  "
#define MULTIPROC_BUSTYPE_CBUSII  "CBUSII"
#define MULTIPROC_BUSTYPE_EISA    "EISA"
#define MULTIPROC_BUSTYPE_FUTURE  "FUTURE"
#define MULTIPROC_BUSTYPE_INTERN   "INTERN"
#define MULTIPROC_BUSTYPE_ISA      "ISA   "
#define MULTIPROC_BUSTYPE_MBI      "MBI   "
#define MULTIPROC_BUSTYPE_MBII     "MBII  "
#define MULTIPROC_BUSTYPE_MCA			"MCA   " // Micro Channel Arch
#define MULTIPROC_BUSTYPE_MPI			"MPI   " // MPI
#define MULTIPROC_BUSTYPE_MPSA			"MPSA  " // MPSA
#define MULTIPROC_BUSTYPE_NUBUS			"NUBUS " // Apple Macintosh NuBus
#define MULTIPROC_BUSTYPE_PCI			"PCI   " // PCI
#define MULTIPROC_BUSTYPE_PCMCIA		"PCMCIA" // PCMCIA
#define MULTIPROC_BUSTYPE_TCDEC			"TC DEC" // TurboChannel
#define MULTIPROC_BUSTYPE_VL			"VL    " // VESA Local Bus
#define MULTIPROC_BUSTYPE_VME			"VME   " // VMEbus
#define MULTIPROC_BUSTYPE_XPRESS		"XPRESS" // Express System Bus

// I/O APIC flags
#define MULTIPROC_IOAPICFLAG_ENABLED	0x01

// Interrupt types
#define MULTIPROC_INTTYPE_INT			0
#define MULTIPROC_INTTYPE_NMI			1
#define MULTIPROC_INTTYPE_SMI			2
#define MULTIPROC_INTTYPE_EXTINT		3

// Interrupt polarity
#define MULTIPROC_INTPOLARITY_CONFORMS	0x00
#define MULTIPROC_INTPOLARITY_ACTIVEHI	0x01
#define MULTIPROC_INTPOLARITY_RESERVED	0x02
#define MULTIPROC_INTPOLARITY_ACTIVELO	0x03
#define MULTIPROC_INTPOLARITY_MASK		0x03

// Interrupt trigger mode
#define MULTIPROC_INTTRIGGER_CONFORMS	0x00
#define MULTIPROC_INTTRIGGER_EDGE		0x04
#define MULTIPROC_INTTRIGGER_RESERVED	0x08
#define MULTIPROC_INTTRIGGER_LEVEL		0x0C
#define MULTIPROC_INTTRIGGER_MASK		0x0C
#endif