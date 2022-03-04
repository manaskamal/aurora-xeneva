/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  apic.h -- Advanced programmable interrupt controller
 *
 *  /PROJECT - Aurora v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *============================================================
 */

#ifndef __APIC_H__
#define __APIC_H__


#include <stdint.h>
#include <arch\x86_64\cpu.h>

//! APIC Definitions
#define LAPIC_SPURIOUS   0x00f0
#define LAPIC_LVT_TIMER  0x0320
#define LAPIC_LVT_LINT0  0x0350
#define LAPIC_LVT_LINT1  0x0360

#define LAPIC_TIMER_INIT  0x0380
#define LAPIC_TIMER_CUR   0x0390
#define LAPIC_TIMER_DIV   0x03e0

#define LAPIC_REGISTER_ID  0x2
#define LAPIC_REGISTER_EOI 0xB
#define LAPIC_REGISTER_SVR 0xF
#define LAPIC_REGISTER_ICR  0x30
#define LAPIC_REGISTER_LVT_TIMER  0x32
#define LAPIC_REGISTER_LVT_ERROR  0x37

#define LAPIC_REGISTER_TMRINITCNT  0x38
#define LAPIC_REGISTER_TMRCURRCNT  0x39
#define LAPIC_REGISTER_TMRDIV      0x3E

//! initialize apic
extern void initialize_apic ();
//! sends eoi to cpu local apic
extern void apic_local_eoi();

//!APIC REGISTER R/W
extern uint64_t read_apic_register(uint16_t reg);
extern void write_apic_register(uint16_t reg, uint64_t value);

#ifdef SMP
extern void initialize_cpu (uint32_t processor);
#endif
extern void timer_sleep(uint32_t ms);
#endif