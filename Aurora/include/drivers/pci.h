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
 **/

#ifndef __PCI_H__
#define __PCI_H__

#include <stdint.h>
#include <aurora.h>

#define PCI_VENDOR_ID    0x00
#define PCI_DEVICE_ID    0x02
#define PCI_COMMAND      0x04
#define PCI_STATUS       0x06
#define PCI_REVISION_ID  0x08
#define PCI_PROG_IF      0x09
#define PCI_SUBCLASS     0x0a
#define PCI_CLASS        0x0b
#define PCI_CACHE_LINE_SIZE   0x0c
#define PCI_LATENCY_TIMER     0x0d
#define PCI_HEADER_TYPE       0x0e
#define PCI_BIST          0x0f
#define PCI_BAR0          0x10
#define PCI_BAR1          0x14
#define PCI_BAR2          0x18
#define PCI_BAR3          0x1C
#define PCI_BAR4          0x20
#define PCI_BAR5          0x24
#define PCI_CAPABILITIES_PTR  0x34
#define PCI_INTERRUPT_LINE  0x3C
#define PCI_INTERRUPT_PIN  0x3D

#define PCI_SECONDARY_BUS   0x09

#define PCI_HEADER_TYPE_DEVICE 0
#define PCI_HEADER_TYPE_BRIDGE 1
#define PCI_HEADER_TYPE_CARDBUS 2
#define PCI_TYPE_BRIDGE 0x0604
#define PCI_TYPE_SATA   0x0106
#define PCI_NONE        0xFFFF

#define PCI_MAX_BUS  256
#define PCI_DEVICE_PER_BUS 32
#define PCI_FUNCTION_PER_DEVICE 8


AU_EXTERN AU_EXPORT uint32_t pci_read (uint32_t device, int reg);
AU_EXTERN AU_EXPORT uint32_t pci_scan_class(uint8_t classcode, uint8_t subclass);
AU_EXTERN AU_EXPORT uint32_t pci_scan_device(uint32_t vendid, uint32_t devid);
AU_EXTERN AU_EXPORT void pci_write (uint32_t device, int reg, uint32_t value);
AU_EXTERN AU_EXPORT void pci_enable_bus_master (uint32_t device);
AU_EXTERN AU_EXPORT void pci_enable_interrupts (uint32_t device);
extern uint32_t pci_encode_device(uint32_t bus, uint32_t slot, uint32_t func);

#endif