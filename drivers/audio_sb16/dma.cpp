/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  DMA.cpp -- ISA DMA source
 *
 *  /PROJECT - Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===================================================
 */

#include "dma.h"
#include <cpu.h>

//! Mask a channel
void dma_mask_channel (uint8_t channel) {

	if (channel <= 4)
		x64_outportb(DMA0_CHANMASK_REG, (1 << (channel-1)));
	else
		x64_outportb(DMA1_CHANMASK_REG, (1 << (channel-5)));
}

//! Unmask a channel
void dma_unmask_channel (uint8_t channel) {
	
	if (channel <= 4)
		x64_outportb (DMA0_CHANMASK_REG, channel);
	else
		x64_outportb (DMA1_CHANMASK_REG, channel);
}

//! unmask all channels
void dma_unmask_all (int dma) {

	//! it doesn;t matter what is written to this register
	x64_outportb (DMA1_UNMASK_ALL_REG, 0xff);
}

//! reset controller to defaults
void dma_reset (int dma) {
	
	x64_outportb (DMA0_TEMP_REG, 0xff);
}

//! resets flip flop
void dma_reset_flipflop (int dma) {

	if (dma < 2)
		return;
	
	//! it doesn't matter what is written to this register
	x64_outportb ((dma == 0) ? DMA0_CLEARBYTE_FLIPFLOP_REG : DMA1_CLEARBYTE_FLIPFLOP_REG, 0xff);
}

//! sets the address of a channel
void dma_set_address (uint8_t channel, uint8_t low, uint8_t high) {

	if (channel > 8) 
		return;

	unsigned short port = 0;
	switch (channel ) {

	case 0: {port = DMA0_CHAN0_ADDR_REG; break;}
	case 1: {port = DMA0_CHAN1_ADDR_REG; break;}
	case 2: {port = DMA0_CHAN2_ADDR_REG; break;}
	case 3: {port = DMA0_CHAN3_ADDR_REG; break;}
	case 4: {port = DMA1_CHAN4_ADDR_REG; break;}
	case 5: {port = DMA1_CHAN5_ADDR_REG; break;}
	case 6: {port = DMA1_CHAN6_ADDR_REG; break;}
	case 7: {port = DMA1_CHAN7_ADDR_REG; break;}
	}

	x64_outportb (port, low);
	x64_outportb (port, high);
}

//! sets the counter of a channel
void dma_set_count (uint8_t channel, uint8_t low, uint8_t high) {

	if (channel > 8)
		return;

	unsigned short port = 0;
	switch (channel) {
	case 0: {port = DMA0_CHAN0_COUNT_REG; break;}
	case 1: {port = DMA0_CHAN1_COUNT_REG; break;}
	case 2: {port = DMA0_CHAN2_COUNT_REG; break;}
	case 3: {port = DMA0_CHAN3_COUNT_REG; break;}
	case 4: {port = DMA1_CHAN4_COUNT_REG; break;}
	case 5: {port = DMA1_CHAN5_COUNT_REG; break;}
	case 6: {port = DMA1_CHAN6_COUNT_REG; break;}
	case 7: {port = DMA1_CHAN7_COUNT_REG; break;}
	}

	x64_outportb(port, low);
	x64_outportb(port, high);
}


void dma_set_mode (uint8_t channel, uint8_t mode) {

	int dma = (channel < 4) ? 0 : 1;
	int chan = (dma==0) ? channel : channel-4;

	dma_mask_channel (channel);
	x64_outportb ((channel < 4) ? (DMA0_MODE_REG) : DMA1_MODE_REG, chan | (mode));
	dma_unmask_all (dma);
}

//! prepares a channel for read
void dma_set_read (uint8_t channel) {
	dma_set_mode (channel, DMA_MODE_READ_TRANSFER | DMA_MODE_TRANSFER_SINGLE);
}

//! prepares a channel for write
void dma_set_write (uint8_t channel) {
	dma_set_mode (channel, DMA_MODE_WRITE_TRANSFER | DMA_MODE_TRANSFER_SINGLE);
}

//! writes to an external page register
void dma_set_external_page_register (uint8_t reg, uint8_t val) {

	if (reg > 14)
		return;

	unsigned short port = 0;
	switch ( reg ) {

	case 1: {port = DMA_PAGE_CHAN1_ADDRBYTE2; break;}
	case 2: {port = DMA_PAGE_CHAN2_ADDRBYTE2; break;}
	case 3: {port = DMA_PAGE_CHAN3_ADDRBYTE2; break;}
	case 4: {return;}//! nothing should ever write to register 4
	case 5: {port = DMA_PAGE_CHAN5_ADDRBYTE2; break;}
	case 6: {port = DMA_PAGE_CHAN6_ADDRBYTE2; break;}
	case 7: {port = DMA_PAGE_CHAN7_ADDRBYTE2; break;}
	}

	x64_outportb(port, val);
}