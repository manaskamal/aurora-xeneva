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
 * @ahci.h -- AHCI controller
 *
 **/

#include <drivers/ahci.h>
#include <drivers/ahci_disk.h>
#include <drivers/pci.h>
#include <drivers/hdaudio/hda.h>
#include <pmmngr.h>
#include <stdio.h>

#define SATA_SIG_ATA   0x00000101
#define SATA_SIG_ATAPI 0xEB140101
#define SATA_SIG_SEMB  0xC33C0101
#define SATA_SIG_PM    0x96690101

#define AHCI_DEV_NULL 0
#define AHCI_DEV_SATA 1
#define AHCI_DEV_SEMB 2
#define AHCI_DEV_PM   3
#define AHCI_DEV_SATAPI 4

#define HBA_PORT_IPM_ACTIVE 1
#define HBA_PORT_DET_PRESENT 3

/* 
 * Global Variables 
 */
static bool ___ahci_64_bit___ = false;
void* hbabar = NULL;


int ahci_check_type (HBA_PORT *port) {
	uint32_t ssts = port->ssts;
	uint8_t ipm = (ssts >> 8) & 0x0F;
	uint8_t det = ssts & 0x0F;

	if (det != HBA_PORT_DET_PRESENT)
		return AHCI_DEV_NULL;
	if (ipm != HBA_PORT_IPM_ACTIVE)
		return AHCI_DEV_NULL;

	switch (port->sig) {
	case SATA_SIG_ATAPI:
		return AHCI_DEV_SATAPI;
	case SATA_SIG_SEMB:
		return AHCI_DEV_SEMB;
	case SATA_SIG_PM:
		return AHCI_DEV_PM;
	default:
		return AHCI_DEV_SATA;
	}
}

/* ahci_control_hand_os -- takes the control from BIOS/UEFI 
 * @param mem -- AHCI Bar address
 */
void ahci_control_hand_os (HBA_MEM *mem) {
	mem->bohc = mem->bohc | GHC_BOHC_OOS;
	int i = 0;
	while (!(mem->bohc & GHC_BOHC_BOS | GHC_BOHC_OOS | GHC_BOHC_OOS)) {
		i++;
	}
	printf ("[AHCI]: Taking the control from firmware took %d ms\n", i);
}

/*
 * ahci_interrupt_handler -- handles AHCI interrupts
 */
void ahci_interrupt_handler (size_t v, void* p) {
	HBA_MEM *hba = (HBA_MEM*)hbabar;
	uint32_t is = hba->is;
#if 0
	printf ("[AHCI]: Interrupt fired++\n");
#endif
	for (int i = 0; i < 32; i++) {
		if ((hba->is & hba->pi & (1<<i))) {
#if 0
			printf ("[AHCI]: Interrupt from %d port\n", i);
#endif
			uint32_t port_is = hba->port[i].is;
#if 0
			if ((hba->port[i].is & (1<<2))) {
				printf ("[AHCI]: DMA Setup FIS Interrupt\n");
			}else if ((hba->port[i].is & (1<<1))) {
				printf ("[AHCI]: PIO Setup FIS Interrupt\n");
			}else if (hba->port[i].is & (1<<0)) {
				printf ("[AHCI]: D2H Fis received\n");
			}else if (hba->port[i].is & (1<<30)) {
				printf ("[AHCI]: Task File Error Status\n");
			}else if (hba->port[i].is & (1<<29)) {
				printf ("[AHCI]: Host Bus Fetal Error Status\n");
			}else if (hba->port[i].is & (1<<4)) {
				printf ("[AHCI]: Unknown FIS interrupt status\n");
			}
#endif
			hba->port[i].is = port_is;
			break;
		}
	}

	if (is_hdaudio_initialized())
		hda_handler(v,p);
	
	hba->is = is;
	interrupt_end(0);
}

/* 
 * ahci_initialize -- initialize the AHCI Controller
 */
void ahci_initialize () {
	pci_device_info *info = (pci_device_info*)pmmngr_alloc();
	int bus,dev,func;
	bool ahci_not_found = false;

	/* First find in standard registry */
	if (!pci_find_device_class(0x01,0x06,info,&bus,&dev,&func)) {
		ahci_not_found = true;
	}
	/* not found? now search in RAID registry */
	if (ahci_not_found) {
		if (!pci_find_device_class(0x01,0x04,info,&bus,&dev,&func)) {
			printf ("*******************************\n");
			printf ("AHCI/SATA not found\n");
			printf ("Xeneva initialisation failed\n");
			printf ("Halting System\n");
			printf ("*******************************\n");
			for(;;);
		}
	}

	uint16_t command_reg = 0;
	read_config_16 (0,bus,dev,func,0x4, &command_reg);
	command_reg |= (1<<2);
	command_reg &= ~(1<<10);
	command_reg |= (1<<1);
    write_config_16 (0,bus, dev,func,0x4,command_reg);

	uint8_t int_line = info->device.nonBridge.interruptLine;
	if (info->device.nonBridge.interruptLine < 255) {
		interrupt_set(11, ahci_interrupt_handler, 11);
	}

	printf ("AHCI/SATA found at dev -> %d, func -> %d, bus -> %d\n", dev, func, bus);
	HBA_MEM *hba = (HBA_MEM*)(info->device.nonBridge.baseAddress[5] & 0xFFFFFFF0);
	hbabar = (void*)(info->device.nonBridge.baseAddress[5] & 0xFFFFFFF0);
	
	hba->ghc = 1;

	timer_sleep(500);
	hba->ghc = (1<<31);
	timer_sleep(100);
	hba->ghc = (1<<1);

	uint32_t version_major = hba->vs >> 16 & 0xff;
	uint32_t version_minor = hba->vs & 0xff;

	printf ("[AHCI]: Version -- %d.%d\n", version_major, version_minor);
	uint32_t _bit = hba->cap >> 31 & 0xff;
	if (_bit) {
		printf ("[AHCI]: 64-bit DMA supported\n");
		___ahci_64_bit___ = true;
	}

	
	hba->is = UINT32_MAX;
	hba->ghc |= 0x2;

	uint32_t num_command_slots  = hba->cap >> 8 & 0xff;
	printf ("[AHCI]: Num Command Slots -> %d\n", num_command_slots);

	uint8_t support_spin = hba->cap & (1<<27);
	if (support_spin) {
		printf ("[AHCI]: Support Staggered spin-up %d\n", support_spin);
	}

	if (hba->cap & (1<<16))
		printf ("[AHCI]: FIS-Based Switching supported\n");
	uint32_t pi = hba->pi;
	int i = 0;
	while (i < 32) {
		if (pi & 1) {
			int dt = ahci_check_type (&hba->port[i]);
			if (dt == AHCI_DEV_SATA) {
				printf ("[AHCI]: SATA Drive found at port %d\n", i);
				hba->port[i].sctl &= ~PX_SCTL_IPM_MASK;
				hba->port[i].sctl |= PX_SCTL_IPM_NONE;
				ahci_disk_initialize(&hba->port[i]);
			}
			else if (dt == AHCI_DEV_SATAPI) {
				printf ("[AHCI]: SATAPI Drive found at port %d\n", i);
			}else if (dt == AHCI_DEV_SEMB) {
				printf ("[AHCI]: SEMB Drive found at port %d\n", i);
			}else if (dt == AHCI_DEV_PM) {
				printf ("[AHCI]: PM Drive found at port %d\n", i);
			}
		}
		pi >>= 1;
		i++;
	}
}

/*
 * ahci_is_64_bit_supported -- checks if 64 bit DMA
 * is supported
 */
bool ahci_is_64_bit_supported () {
	return ___ahci_64_bit___;
}

