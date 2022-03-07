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
 * @ahci_disk.h -- AHCI Disk driver
 *
 **/
#include <drivers/ahci_disk.h>
#include <arch/x86_64/apic.h>
#include <pmmngr.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <drivers/ata.h>
#include <drivers/hdaudio/hda.h>

HBA_PORT *sata_drive_port = NULL;

/*
 * ahci_disk_stop_cmd -- Stops AHCI DMA Engine
 * @param port -- SATA Drive port
 */
void ahci_disk_stop_cmd (HBA_PORT *port) {
	port->cmd &= ~PX_CMD_START;
	port->cmd &= ~PX_CMD_FRE;
	while(1) {
		if (port->cmd & PX_CMD_FR)
			continue;
		if (port->cmd & PX_CMD_CR)
			continue;
		break;
	}
}

/*
 * ahci_disk_start_cmd -- Starts comand DMA engine
 * @param port -- SATA Drive port
 */
void ahci_disk_start_cmd (HBA_PORT *port) {
	while (port->cmd & PX_CMD_CR)
		;
	port->cmd |= PX_CMD_FRE;
	port->cmd |= PX_CMD_START;
}


/*
 * ahci_disk_find_slot -- finds a free command slot
 * @param port -- SATA Drive port
 * @return i -- slot number
 */
uint32_t ahci_disk_find_slot (HBA_PORT *port) {
	uint32_t slots = (port->sact | port->ci);
	for (int i = 0; i < 32; i++) {
		if ((slots & 1) == 0)
			return i;
		slots >>= 1;
	}
}


/*
 * ahci_disk_read -- reads data to specific memory buffer 
 * @param port -- SATA port
 * @param lba -- LBA value
 * @param count -- number of sectors to use
 * @param buffer -- memory buffer
 */
void ahci_disk_read (HBA_PORT *port, uint64_t lba, uint32_t count, uint64_t *buffer) {
	//port->is = (uint32_t)-1;
	int spin = 0;
	HBA_CMD_HEADER *cmd_list = (HBA_CMD_HEADER*)port->clb;
	uint64_t buffer_whole = (uint64_t)buffer;

	cmd_list->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);
	cmd_list->w = 0;
	cmd_list->prdtl = 1;
	
	uint32_t command_slot = ahci_disk_find_slot(port);

	HBA_CMD_TABLE *tbl = (HBA_CMD_TABLE*)cmd_list[command_slot].ctba;
	int i=0;
	//for (i = 0; i < cmd_list->prdtl; i++){
	tbl->prdt[0].data_base_address = buffer_whole & 0xffffffff;
	tbl->prdt[0].dbau = buffer_whole >> 32;
	tbl->prdt[0].data_byte_count = 512 * count -1;
	tbl->prdt[0].i = 1;


	FIS_REG_H2D *fis = (FIS_REG_H2D*)tbl->cmd_fis;
	fis->fis_type = FIS_TYPE_REG_H2D;
	fis->c = 1;
	fis->command = ATA_CMD_READ_DMA_EXT;
	fis->lba0 = lba & 0xff;
	fis->lba1 = (lba>>8) & 0xff;
	fis->lba2 = (lba>>16) & 0xff;
	fis->device = 1<<6;
	fis->lba3 = (lba>>24) & 0xff;
	fis->lba4 = (lba>>32) & 0xff;
	fis->lba5 = (lba>>40) & 0xff;
	fis->countl = count & 0xff;
	fis->counth = (count >> 8) & 0xff;

	while((port->tfd & (ATA_SR_BSY  | ATA_SR_DRQ)) && spin < 1000000) {
		spin++;
	}
	if (spin==1000000)
		printf ("[AHCI]:Port Hung\n");

	port->ci = 1<<command_slot;
	while(1) {
		if ((port->ci & (1<<command_slot)) == 0) 
			break;
		/*if (port->is & (1<<30)) 
			break;*/
	}
}


/*
 * ahci_disk_write -- Writes data to SATA disk 
 * @param port -- SATA port
 * @param lba -- LBA value
 * @param count -- number of sectors to use
 * @param buffer -- memory buffer
 */
void ahci_disk_write (HBA_PORT *port, uint64_t lba, uint32_t count, uint64_t *buffer) {
	int spin = 0;
	HBA_CMD_HEADER *cmd_list = (HBA_CMD_HEADER*)port->clb;
	uint64_t buffer_whole = (uint64_t)buffer;

	cmd_list->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);
	cmd_list->w = 1;
	cmd_list->prdtl = 1;
	
	uint32_t command_slot = ahci_disk_find_slot(port);

	HBA_CMD_TABLE *tbl = (HBA_CMD_TABLE*)cmd_list[command_slot].ctba;
	int i=0;
	tbl->prdt[0].data_base_address = buffer_whole & 0xffffffff;
	tbl->prdt[0].dbau = buffer_whole >> 32;
	tbl->prdt[0].data_byte_count = 512 * count -1;
	tbl->prdt[0].i = 1;

	FIS_REG_H2D *fis = (FIS_REG_H2D*)tbl->cmd_fis;
	fis->fis_type = FIS_TYPE_REG_H2D;
	fis->c = 1;
	fis->command = ATA_CMD_WRITE_DMA_EXT;
	fis->lba0 = lba & 0xff;
	fis->lba1 = (lba>>8) & 0xff;
	fis->lba2 = (lba>>16) & 0xff;
	fis->device = 1<<6;
	fis->lba3 = (lba>>24) & 0xff;
	fis->lba4 = (lba>>32) & 0xff;
	fis->lba5 = (lba>>40) & 0xff;
	fis->countl = count & 0xff;
	fis->counth = (count >> 8) & 0xff;

	while((port->tfd & (ATA_SR_BSY  | ATA_SR_DRQ)) && spin < 1000000) {
		spin++;
	}
	if (spin==1000000)
		printf ("[AHCI]:Port Hung\n");

	port->ci = 1<<command_slot;
	while(1) {
		if ((port->ci & (1<<command_slot)) == 0) 
			break;
		/*if (port->is & (1<<30)) 
			break;*/
	}
}

/*
 * ahci_disk_identify -- identify the disk information
 * @param port -- SATA Drive port
 * @param lba -- Logical Block Address, for identification set this to 0
 * @param count -- count --> 1
 * @param buffer -- memory area to store the information
 */
void ahci_disk_identify (HBA_PORT *port, uint64_t lba, uint32_t count, uint64_t *buffer) {
	int spin = 0;
	HBA_CMD_HEADER *cmd_list = (HBA_CMD_HEADER*)port->clb;
	uint64_t buffer_whole = (uint64_t)buffer;

	cmd_list->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);
	cmd_list->w = 0;
	cmd_list->prdtl = (uint16_t)((count-1)>>4)+1;

	uint32_t command_slot = ahci_disk_find_slot(port);

	HBA_CMD_TABLE *tbl = (HBA_CMD_TABLE*)cmd_list[command_slot].ctba;
	int i=0;
	for (i = 0; i < cmd_list->prdtl; i++){
		tbl->prdt[i].data_base_address = buffer_whole & 0xffffffff;
		tbl->prdt[i].dbau = buffer_whole >> 32;
		tbl->prdt[i].data_byte_count = (512 * count) - 1;
		tbl->prdt[i].i = 1;
		buffer += 512*count;
		buffer_whole = (uint32_t)buffer;
	}
	tbl->prdt[i].data_base_address = buffer_whole & 0xffffffff;
	tbl->prdt[i].dbau = buffer_whole >> 32;
	tbl->prdt[i].data_byte_count = (512 * count) - 1;
	tbl->prdt[i].i = 1;

	FIS_REG_H2D *fis = (FIS_REG_H2D*)tbl->cmd_fis;
	fis->fis_type = FIS_TYPE_REG_H2D;
	fis->c = 1;
	fis->command = ATA_CMD_IDENTIFY;
	fis->lba0 = lba & 0xff;
	fis->lba1 = (lba>>8) & 0xff;
	fis->lba2 = (lba>>16) & 0xff;
	fis->device = 1<<6;
	fis->lba3 = (lba>>24) & 0xff;
	fis->lba4 = (lba>>32) & 0xff;
	fis->lba5 = (lba>>40) & 0xff;
	fis->countl = count & 0xff;
	fis->counth = (count >> 8) & 0xff;

	while((port->tfd & (ATA_SR_BSY  | ATA_SR_DRQ)) && spin < 1000000) {
		spin++;
	}
	if (spin==1000000)
		printf ("[AHCI]:Port Hung\n");

	port->ci = 1<<command_slot;
	while(1) {
		if ((port->ci & (1<<command_slot)) == 0) 
			break;
		/*if (port->is & (1<<30)) 
			break;*/
	}
}

/*
 * ahci_disk_initialize -- initialize the ahci sata disk
 * @param port -- SATA Drive Port memory
 * @param slot -- slot number
 */
void ahci_disk_initialize (HBA_PORT *port) {

	/* stop the DMA engine */
	ahci_disk_stop_cmd(port);

	sata_drive_port = port;



	uint64_t phys;

	/* Allocate command list */
	phys = (uint64_t)pmmngr_alloc();
	port->clb = phys & 0xffffffff;
	port->clbu = phys >> 32;

	HBA_CMD_HEADER *cmd_list = (HBA_CMD_HEADER*)phys;
	memset((void*)phys, 0, 4096);

	/* Allocate FIS */
	phys = (uint64_t)pmmngr_alloc();
	port->fb = phys & 0xffffffff;
	port->fbu = (phys >> 32);

	HBA_FIS *fis_dev = (HBA_FIS*)phys;
	memset((void*)phys, 0, 4096);

	uint8_t cold_presence = port->cmd & (1<<20);
	if (cold_presence) {
		printf ("[AHCI]: Port Supports cold presence %d\n",cold_presence);
	}

	for (int i = 0; i < 31; i++) {
		cmd_list[i].prdtl = 1;
		phys = (uint64_t)pmmngr_alloc();
		cmd_list[i].ctba = phys & 0xffffffff;
		cmd_list[i].ctbau = phys >> 32;
		cmd_list[i].p = 1;
		cmd_list[i].cfl = 0x10;
		memset((void*)phys, 0, 4096);
	}

	port->serr = 0xffffffff;

	port->cmd &= ~HBA_PX_CMD_ICC;
	port->cmd |= PX_CMD_POD | PX_CMD_SUD | HBA_PX_CMD_ICC_ACTIVE;


	port->ie = (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) |
		(1<<7) | (1<<22) | (1<<23) | (1<<24) | (1<<26) | (1<<27) | (1<<28) | 
		(1<<29) | (1<<30) | (1<<31);

	/* start the command DMA engine */
	ahci_disk_start_cmd(port);

	uint8_t current_slot = port->cmd & (1<<8);

	uint64_t *addr = (uint64_t*)pmmngr_alloc();
	memset(addr,0,4096);
	ahci_disk_identify(port,0,1,addr);
	char ata_device_name[40];
	uint8_t *ide_buf = (uint8_t*)addr;
	for (int i= 0; i < 40; i += 2)
	{
		ata_device_name[i] = ide_buf[54 + i + 1];
		ata_device_name[i + 1] = ide_buf[54 + i];
	}
	printf ("[AHCI]: Model -> %s\n", ata_device_name);
}

/**
 * ahci_disk_get_port -- returns sata disk port
 */
HBA_PORT *ahci_disk_get_port () {
	return sata_drive_port;
}

