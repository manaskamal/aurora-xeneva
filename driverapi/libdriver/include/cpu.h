/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  cpu.h -- Cpu functions wrapper for drivers
 *
 *  /PROJECT - Aurora Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

extern "C" void x64_cli ();
extern "C" void x64_sti ();
//! in & out port functions
extern "C" uint8_t x64_inportb(uint16_t port);
extern "C" uint16_t x64_inportw(uint16_t port);
extern "C" uint32_t x64_inportd(uint16_t port);

extern "C" void x64_outportb(uint16_t port, uint8_t data);
extern "C" void x64_outportw(uint16_t port, uint16_t data);
extern "C" void x64_outportd(uint16_t port, uint32_t data);

#endif