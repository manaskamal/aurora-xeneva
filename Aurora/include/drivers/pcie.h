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
 *
 **/

#ifndef __PCIE_H__
#define __PCIE_H__

#include <drivers\pci.h>
#include <stdint.h>
#include <aurora.h>

#define PCI_VENDOR_ID  0x00
#define PCI_DEVICE_ID  0x02
#define PCI_COMMAND    0x04
#define PCI_STATUS     0x06
#define PCI_REVISION_ID  0x08
#define PCI_PROG_IF      0x09
#define PCI_SUBCLASS     0x0a
#define PCI_CLASS   0x0b
#define PCI_CACHE_LINE_SIZE   0x0c
#define PCI_LATENCY_TIMER   0x0d
#define PCI_HEADER_TYPE  0x0e
#define PCI_BIST  0x0f
#define PCI_BAR0  0x10
#define PCI_BAR1  0x14
#define PCI_BAR2  0x18
#define PCI_BAR3  0x1C
#define PCI_BAR4  0x20
#define PCI_BAR5  0x24
#define PCI_CAPABILITIES_PTR 0x34
#define PCI_INTERRUPT_LINE  0x3C
#define PCI_INTERRUPT_PIN  0x3D

#define PCI_MAX_BUS 0x20
#define PCI_DEVICE_PER_BUS 32
#define PCI_FUNCTION_PER_DEVICE 8

extern uint64_t pci_express_get_device (uint16_t segment, int bus, int device, int function);
AU_EXTERN AU_EXPORT uint64_t pci_express_scan_class (uint8_t classCode, uint8_t subClassCode, int *bus_, int *dev_, int *func_);
AU_EXTERN AU_EXPORT uint32_t pci_express_read (uint64_t device, int reg,  int bus, int dev,int func);
AU_EXTERN AU_EXPORT uint64_t pci_express_read2 (uint64_t device, int reg, int size, int bus, int dev, int func);
AU_EXTERN AU_EXPORT void pci_express_write (uint64_t device, int reg, uint32_t val,  int bus, int dev, int func);
AU_EXTERN AU_EXPORT void pci_express_write2 (uint64_t device, int reg, int size,uint64_t val,  int bus, int dev,int func);
AU_EXTERN AU_EXPORT void pcie_alloc_msi (uint64_t device, size_t vector,  int bus, int dev, int func);

#endif

