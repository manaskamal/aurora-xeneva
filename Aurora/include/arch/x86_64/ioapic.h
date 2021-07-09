/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ioapic.h -- I/O APIC
 *
 *  /PROJECT - Aurora v1.0 {Xeneva v1.0}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==================================================
 */

#ifndef __IOAPIC_H__
#define __IOAPIC_H__

#include <arch\x86_64\cpu.h>
#include <arch\x86_64\apic.h>
#include <stdint.h>

#define IOAPIC_REG_ID  0x00
#define IOAPIC_REG_VER 0x01
#define IOAPIC_REG_ARB 0x02
#define IOAPIC_REG_RED_TBL_BASE 0x10

//! Initialize I/O Apic
extern void ioapic_init(void* address);
extern void ioapic_register_irq(size_t vector, void (*fn)(size_t, void* p),uint8_t irq);
#endif