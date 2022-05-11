/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @hal.h -- Hardware Abstraction Layer
 *
 **/

#ifndef __HAL_H__
#define __HAL_H__


#include <stdint.h>
#include <arch\x86_64\apic.h>
#include <aurora.h>


//!Architecture specific
#ifdef ARCH_X64
#include <arch\x86_64\cpu.h>
#elif ARCH_ARM
#include <arch\arm\cpu.h>
#elif ARCH_ARM64
#include <arch\arm64\cpu.h>
#endif


//! Architecture specific : Hal initializer

/**
 * AuHalInitialize -- Initialize the HA Layer
 */
extern void AuHalInitialize ();

/**
 * hal_set_vect -- Install a isr to a vector to serve desired interrupt
 * @param vector -- vector number (0-254)
 * @param function -- function pointer to isr
 */
AU_EXTERN AU_EXPORT void AuHalSetVect (size_t vector, void (*function)(size_t vector, void* param));

//! Port functions

/**
 * inportb -- reads a data from a port in bytes
 * @param port -- port address
 */
AU_EXTERN AU_EXPORT uint8_t inportb(uint16_t port);

/**
 * inportw -- reads word data from given port
 * @param port -- port address
 */
AU_EXTERN AU_EXPORT uint16_t inportw(uint16_t port);

/**
 * inportd -- read dword data from given port
 * @param port -- port address
 */
AU_EXTERN AU_EXPORT uint32_t inportd(uint16_t port);

/** 
 * outportb -- writes byte data to given port
 * @param port -- port address
 * @param data -- data to write
 */
AU_EXTERN AU_EXPORT void outportb(uint16_t port, uint8_t data);

/**
 * outportw -- write word data to given port
 * @param port -- port address
 * @param data -- data to write
 */
AU_EXTERN AU_EXPORT void outportw(uint16_t port, uint16_t data);

/**
 * outportd -- writes dword data to given port
 * @param port -- port address
 * @param data -- data to write
 */
AU_EXTERN AU_EXPORT void outportd(uint16_t port, uint32_t data);

/*
 * AuInterruptEnd -- Ends an interrupt handler
 * @param irq -- interrupt irq
 */
AU_EXTERN AU_EXPORT void AuInterruptEnd (uint32_t irq);

/*
 * AuInterruptSet -- Register an interrupt handler for a device
 * @param vector -- interrupt vector num
 * @param fn -- function pointer
 * @param irq -- irq number
 */
AU_EXTERN AU_EXPORT void AuInterruptSet (size_t vector, void (*fn)(size_t, void* p),uint8_t irq, bool level);

/*
 * AuIrqMask -- Mask an Irq, so that it will never delivers an 
 * interrupt untill it is unmasked
 * @param value -- if true, mask else unmask
 */
AU_EXTERN AU_EXPORT void AuIrqMask (uint8_t irq, bool value);

/*
 * AuDisableInterrupts -- disable all interrupts
 */
AU_EXTERN AU_EXPORT void AuDisableInterupts();

/*
 * AuEnableInterrupts -- enable all interrupts
 */
AU_EXTERN AU_EXPORT void AuEnableInterrupts();

extern void* get_ap_address ();
#endif
