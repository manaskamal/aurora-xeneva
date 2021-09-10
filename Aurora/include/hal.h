/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  hal.h -- Hardware Abstraction Layer
 *
 *  /PROJECT - Aurora v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ====================================================
 */

#ifndef __HAL_H__
#define __HAL_H__


#include <stdint.h>
#include <arch\x86_64\apic.h>


//!Architecture specific
#ifdef ARCH_X64
#include <arch\x86_64\cpu.h>
#elif ARCH_ARM
#include <arch\arm\cpu.h>
#elif ARCH_ARM64
#include <arch\arm64\cpu.h>
#endif


//! Architecture specific : Hal initializer
extern void hal_init ();
extern void hal_set_vect (size_t vector, void (*function)(size_t vector, void* param));

//! Port functions
extern uint8_t inportb(uint16_t port);
extern uint16_t inportw(uint16_t port);
extern uint32_t inportd(uint16_t port);
extern void outportb(uint16_t port, uint8_t data);
extern void outportw(uint16_t port, uint16_t data);
extern void outportd(uint16_t port, uint32_t data);

//! Interrupt EOI routine
extern void interrupt_end (uint32_t irq);
//! Interrupt Vector Registration
extern void interrupt_set (size_t vector, void (*fn)(size_t, void* p),uint8_t irq);
//! Mask or unmask an interrupt
extern void irq_mask (uint8_t irq, bool value);

#endif
