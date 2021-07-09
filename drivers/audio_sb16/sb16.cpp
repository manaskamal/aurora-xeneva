/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  sb16.cpp -- Sound Blaster 16 Audio Driver
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#include <stdint.h>
#include "audio_sb16.h"
#include <cpu.h>
#include "dma.h"
#include <sys.h>



void (*driver_debug) (const char* str, ...);
void (*apic_local_eoi) ();

bool _sb16 = false;

void sb16_reset_dsp () {
	x64_outportb (SB16_DSP_RESET, 1);
	for (int i =0; i < 1000; i++)
		;
	x64_outportb (SB16_DSP_RESET, 0);
	for (int i=0; i < 1000; i++)
		;

	if (x64_inportb (SB16_DSP_READ)==0xAA)
		_sb16 = true;
}

void sb16_write_dsp (int value) {

	unsigned int status = 0;
	status = x64_inportb (SB16_DSP_WRITE);
	x64_outportb (SB16_DSP_WRITE, value);
}

int sb16_read_dsp () {
	return x64_inportb (SB16_DSP_READ);
}


void sb16_set_sample_rate (uint16_t hz) {

	sb16_write_dsp (0x41);
	sb16_write_dsp ((uint8_t)(hz >> 8));
	sb16_write_dsp ((uint8_t)hz);
	sb16_write_dsp (0x42);
	sb16_write_dsp ((uint8_t)(hz >> 8));
	sb16_write_dsp ((uint8_t)hz);
}

void sb16_set_irq_register (uint8_t irq_number) {

	uint8_t value;
	switch(irq_number) {
	case 2:
		value = 0x01;
		break;
	case 5:
		value = 0x02;
		break;
	case 7:
		value = 0x04;
		break;
	case 10:
		value = 0x08;
		break;
	default:
		value = 0x02;
		break;
	}

	x64_outportb (SB16_DSP_MIXER, 0x80);
	x64_outportb (SB16_DSP_MIXER_DATA_PORT, value);
}


//! Sound Blaster 16 irq handler
void sb16_handler (size_t s, void* p) {
	driver_debug ("[SB16]: IRQ fired\n");
	apic_local_eoi();
}



void sb16_dma_start (uint64_t addr, uint32_t length) {
	const uint8_t channel = 5;

	//! Disable the channel by masking
	dma_mask_channel(channel);

	//! reset the flip flop
	dma_reset_flipflop(1);

	//! set up the transfer mode of sound
	//! 0x48 - SINGLE LOOP; 0x58 - AUTO MODE + channel / REPEAT
	dma_set_mode (channel, 0x48);

	uint16_t offset = (addr / 2) % 65536;
	x64_outportb (0xC4, (uint8_t)offset);
	x64_outportb (0xC4, (uint8_t)(offset >> 8));

	//!Write the transfer length
	x64_outportb (0xC6, (uint8_t)(length - 1));
	x64_outportb (0xC6, (uint8_t)((length - 1) >> 8));

	//! write the buffer
	x64_outportb (0x8b, addr >> 16);

	//! Enable the DMA channel
	dma_unmask_channel(channel);
}

//! Aurora Close Driver interface
//! Free up space and perform every clean action
extern "C" void _declspec(dllexport) aurora_close_driver () {

	//[CODE]
}

//! Aurora Init Driver interface
//! Perform every initializing action here
extern "C" int _declspec(dllexport) _cdecl aurora_init_driver (driver_param_t *param) {
	driver_debug = param->kdebug;
	apic_local_eoi = param->irq_eoi;

	sb16_reset_dsp ();

	if (!_sb16){
		driver_debug ("[SB16]: Not present\n");
		return 0;
	}

	sb16_write_dsp (0xE1);
	unsigned int sb16_version_major = sb16_read_dsp ();
	unsigned int sb16_version_minor = sb16_read_dsp ();

	driver_debug ("[SB16]: Sound Blaster 16 card found version %d.%d\n",sb16_version_major,sb16_version_minor);
	sb16_set_irq_register (5);
	param->interrupt_set(5, sb16_handler,5);
	driver_debug ("[SB16]: Sound Blaster 16 initialized\n");

	//! DRIVER RETURN CODE
	return 1;
}