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
void (*interrupt_eoi) (uint32_t irq);
driver_param_t _param;

bool _sb16 = false;
unsigned int sb16_version_major;
unsigned int sb16_version_minor;

#define SIGNED_AUDIO  0x10
#define STERIO_MODE   0x20
#define DSP_STATUS  0x22E
#define DSP_R_ACK   0x22F

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
	for (int i = 0; i < 100; i++)
		;
	x64_outportb (SB16_DSP_MIXER_DATA_PORT, value);
}


//! Sound Blaster 16 irq handler
void sb16_handler (size_t s, void* p) {
	driver_debug ("[SB16]: IRQ fired\n");
	sb16_write_dsp (0xd5);

	x64_inportb (DSP_STATUS);
	if (sb16_version_major >= 4)
	   x64_inportw(DSP_R_ACK);

	interrupt_eoi(5);

}



void sb16_dma_start (uint64_t addr, uint32_t length) {
	const uint8_t channel = 5;

	//! Disable the channel by masking
	dma_mask_channel(channel);

	//! reset the flip flop
	dma_reset_flipflop(1);

	//! set up the transfer mode of sound
	//! 0x48 - SINGLE LOOP; 0x58 - AUTO MODE + channel / REPEAT
	dma_set_mode (channel, 0x58);

	//!Low Bits of sound data address
	uint16_t offset = (addr / 2) % 65536;
	x64_outportb (0xC4, (uint8_t)offset);
	x64_outportb (0xC4, (uint8_t)(offset >> 8));


	//!Write the transfer length
	x64_outportb (0xC6, (uint8_t)(length - 1));
	x64_outportb (0xC6, (uint8_t)((length - 1) >> 8));

	//! write the buffer
	//! Low bit of the sound data address
	x64_outportb (0x8b, addr >> 16);

	//! Enable the DMA channel
	dma_unmask_channel(channel);
}

extern "C" int _declspec(dllexport) test_num () {
	return 102;
}
//! Audio Write -- Uses sb16 play audio methods
extern "C" void _declspec(dllexport) aurora_write (unsigned char* sound_buffer, size_t length) {

//	uint64_t phys_addr = (uint64_t)(uint64_t)_param.get_phys_address((uint64_t)sound_buffer);
	//driver_debug("Physical Address for sb16 -> %x\n", phys_addr);
	//!sb16 reset the dsp first
	//sb16_reset_dsp ();
	//
	////! set up master volume
	//x64_outportb(0x22C, 0xD1);

	//sb16_set_sample_rate (44100);

	//sb16_dma_start (phys_addr, length);

	//uint8_t command = 0xB0;

	//uint16_t sample_count = length / sizeof(int16_t);
	//sample_count /= 2;

	//sample_count -= 1;

	//driver_debug ("Sample Count -> %d\n", sample_count);
	//sb16_write_dsp (command);
	//sb16_write_dsp (SIGNED_AUDIO | STERIO_MODE);
	//sb16_write_dsp ((uint8_t)sample_count);
	//sb16_write_dsp ((uint8_t)(sample_count >> 8));

	driver_debug ("Aurora sound playing started\n");

}
//! Aurora Close Driver interface
//! Free up space and perform every clean action
extern "C" void _declspec(dllexport) aurora_close_driver () {

	//[CODE]
}


/**  Mouse IOQuery function **/
int ioctl (vfs_node_t *node, int code, void* arg) {
	switch (code) {
		case 302:
			return 25;
			break;
		default:
			break;
	}

	return 1;
}


char *strcpy(char *s1, const char *s2)
{
	char *s1_p = s1;
	while (*s1++ = *s2++);
	return s1_p;
}


//! Aurora Init Driver interface
//! Perform every initializing action here
extern "C" int _declspec(dllexport) _cdecl aurora_init_driver (driver_param_t *param) {
	driver_debug = param->kdebug;
	//interrupt_eoi = param->irq_eoi;
	_param = *param;
	sb16_reset_dsp ();

	if (!_sb16){
		driver_debug ("[SB16]: Not present\n");
		return 0;
	}

	sb16_write_dsp (0xE1);
	sb16_version_major = sb16_read_dsp ();
	sb16_version_minor = sb16_read_dsp ();

	driver_debug ("[SB16]: Sound Blaster 16 card found version %d.%d\n",sb16_version_major,sb16_version_minor);
//	sb16_set_irq_register (5);*/
	//param->interrupt_set(5, sb16_handler,5);
	int bus, dev_, func;
	pci_device_info info;
	/*if (!param->pci->pci_find_device_class_p (0x02,0x00,&info,&bus, &dev_, &func)) {
		param->kdebug("[DRIVER DLL] -> ethernet not found\n");
		for(;;);
	}
*/
	vfs_node_t *node = (vfs_node_t*)param->mem->malloc_p(sizeof(vfs_node_t));
	strcpy (node->filename, "sb16");
	node->size = 0;
	node->eof = 0;
	node->pos = 0;
	node->current = 0;
	node->flags = 0x2;
	node->status = 0;
	node->open = 0;
	node->read = 0;
	node->write = 0;
	node->read_blk = 0;
	node->ioquery = ioctl;
	param->fs->vfs_mount_p("/dev/sb16", node);
	param->kdebug("[DRIVER DLL] ->ethernet founddddddd\n");
	return 1;
}