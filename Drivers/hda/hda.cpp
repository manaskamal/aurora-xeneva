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

#include "hda.h"
#include <aurora.h>
#include <drivers\pci.h>
#include <stdio.h>
#include <arch\x86_64\mmngr\paging.h>
#include <shirq.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <sound.h>
#include <arch\x86_64\apic.h>

/* global variables */
hd_audio_t hd_audio;
uint16_t rirbrp = 0;
uint16_t corbwp = 0;

bool first_interrupt = false;

void _aud_outl_(int reg, uint32_t value) {
	 volatile uint32_t* mmio = (uint32_t*)(hd_audio.mmio + reg);
	*mmio = value;
}

uint32_t _aud_inl_ (int reg) {
    volatile uint32_t* mmio = (uint32_t*)(hd_audio.mmio + reg);
	return *mmio;
}

void _aud_outw_ (int reg, uint16_t value) {
	volatile uint16_t* mmio = (uint16_t*)(hd_audio.mmio + reg);
	*mmio = value;
}

uint16_t _aud_inw_(int reg) {
	volatile uint16_t* mmio = (uint16_t*)(hd_audio.mmio + reg);
	return *mmio;
}

void _aud_outb_ (int reg, uint8_t value) {
	 volatile uint8_t* mmio = (uint8_t*)(hd_audio.mmio + reg);
	*mmio = value;
}

uint8_t _aud_inb_ (int reg) {
	volatile uint8_t* mmio = (uint8_t*)(hd_audio.mmio + reg);
	return *mmio;
}


/*
 * setup_corb -- setup the corb engine
 */
void setup_corb () {
	uint8_t reg;
	uint64_t corb_base;
	unsigned int corb_entries = 0;

	reg = _aud_inb_(CORBSIZE);
	/* Check CORB size capabilities and choose the largest size */
	if (reg & (1 << 6)) {
		hd_audio.corb_entries = 256;
		reg |= 0x2;
	} else if (reg & (1 << 5)) {
		hd_audio.corb_entries = 16;
		reg |= 0x1;
	} else if (reg & (1 << 4)) {
		hd_audio.corb_entries = 2;
		reg |= 0x0;
	} else {
		hd_audio.corb_entries = 256;
		reg |= 0x2;
	}

	_aud_outb_(CORBSIZE, reg);


	/* Set CORB Base Address */
	corb_base = (uintptr_t)v2p((size_t)hd_audio.corb);
	_aud_outl_(CORBLBASE, corb_base);
	_aud_outl_(CORBUBASE, corb_base >> 32);

	_aud_outw_ (CORBWP, corbwp);
	_aud_outw_ (CORBRP, 0x8000);
	_aud_outw_ (CORBRP, 0x0);
	
	/* Start DMA engine */
	_aud_outb_(CORBCTL, 0x1);
	uint32_t corbctl = _aud_inb_(CORBCTL);
	corbctl |= 0x2;
	_aud_outb_ (CORBCTL, corbctl);
}


/*
 * setup_rirb -- Setup the RIRB engine
 */
void setup_rirb() {
	uint8_t reg;
	uint64_t rirb_base;
	uint32_t rirb_entries = 0;

	reg = _aud_inb_ (RIRBSIZE);
	/* Check RIRB size capabilities and choose the largest size */
	if (reg & (1 << 6)) {
		hd_audio.rirb_entries = 256;
		reg |= 0x2;
	} else if (reg & (1 << 5)) {
		hd_audio.rirb_entries = 16;
		reg |= 0x1;
	}else if (reg & (1 << 4)) {
		hd_audio.rirb_entries = 2;
		reg |= 0x0;
	}else {
		hd_audio.rirb_entries = 256;
		reg |= 0x2;
	}

	_aud_outb_(RIRBSIZE,reg);
	/* Set RIRB Base address */
	rirb_base = (uint64_t)v2p((size_t)hd_audio.rirb);
	_aud_outl_(RIRBLBASE, rirb_base);
	_aud_outl_(RIRBUBASE, rirb_base >> 32);
	
	_aud_outw_ (RIRBWP, 0x8000);
	_aud_outw_(RINTCNT, hd_audio.rirb_entries / 2);
	_aud_outb_ (RIRBCTL,0x1);
	/* Start DMA Engine */
	uint32_t rirbctl = _aud_inb_ (RIRBCTL);
	rirbctl |= 0x2;
	_aud_outb_ (RIRBCTL,rirbctl);

}


/*
 * corb_write -- write verb to corb
 * @param verb -- verb to write
 */
void corb_write (uint32_t verb) {

	//! Check for immediate use
	if (hd_audio.immediate_use) {
		_aud_outl_(ICOI,verb);
		_aud_outl_(ICIS,1);
		return;
	}

	//! else use standard command transmitting method
	uint16_t wp = _aud_inw_(CORBWP) & 0xffff;
	uint16_t rp = _aud_inw_(CORBRP) & 0xffff;
    corbwp = 0;
	corbwp = (rp + 1);
	corbwp %= hd_audio.corb_entries;
	
	/*Wait until there's a free entry in the CORB */
	do {
		rp = _aud_inw_(CORBRP) & 0xff;
	}while (rp == corbwp);

	
	/* Write to CORB */	
	hd_audio.corb[corbwp] = verb;	
    _aud_outw_(CORBWP, corbwp);

}


/**
 * rirb_read - read a response from RIRB
 * @param response - address to where the controller will write response
 */
void rirb_read (uint64_t *response) {
	uint16_t wp = _aud_inb_ (RIRBWP);
	uint16_t rp = rirbrp;
	uint16_t old_rp = rp;


	/*Wait for an unread entry in the RIRB */
	while (rirbrp == wp) {
		wp = _aud_inw_(RIRBWP);  //_aud_inb_(RIRBWP);
	}

	rp = (rp + 1) % hd_audio.rirb_entries;
	rirbrp = rp;
	*response = hd_audio.rirb[rp];
	_aud_outb_ (RIRBSTS, 0x5);
	return;
}

/*
 * hda_reset -- reset the hd audio controller
 */
void hda_reset () {
	_aud_outl_ (CORBCTL, 0);
	_aud_outl_ (RIRBCTL, 0);
	_aud_outw_ (RIRBWP, 0);

	while ((_aud_inl_ (CORBCTL) & CORBCTL_CORBRUN) ||
		(_aud_inl_(RIRBCTL) & RIRBCTL_RIRBRUN));

	_aud_outl_(GCTL, 0);
	while ((_aud_inl_(GCTL) & GCTL_RESET));

	_aud_outl_(GCTL, GCTL_RESET);
	while ((_aud_inl_(GCTL) & GCTL_RESET) == 0);

	_aud_outw_(WAKEEN, 0xffff);
	_aud_outl_(INTCTL, 0xffffffff);  //0x800000ff
}


/*
 * AuDriverUnload -- Frees and clear up everthing of hda driver
 * turn hda off!
 */
AU_EXTERN AU_EXPORT int AuDriverUnload(){
	return 0;
}

void hda_handler (size_t v, void* p) {
	AuDisableInterupts();
	if (first_interrupt == false)
		first_interrupt = true;

	uint32_t isr = _aud_inl_(INTSTS);
	uint8_t sts = _aud_inb_(REG_O0_STS);
	printf ("HDA Handler called \n");
	if (sts & 0x4) {
		printf ("HDA Buffer completed \n");
		//hda_output_stop();
	}
	_aud_outl_(INTSTS, isr);
	_aud_outb_ (REG_O0_STS,sts);
	apic_local_eoi();
	//AuInterruptEnd(1);
	AuEnableInterrupts();
}

/*
 * AuDriverMain -- Main entry for hda driver
 */
AU_EXTERN AU_EXPORT int AuDriverMain(){

	pci_device_info pci_dev;
	int bus, dev, func;

	if (!pci_find_device_class (0x04, 0x03, &pci_dev, &bus, &dev, &func)){
		printf ("[driver]: intel hda not found\n");
		return 1;
	}

	pci_enable_bus_master(bus,dev,func);
	pci_enable_interrupt(bus,dev,func);


	printf ("[drivers]: hda interrupt line -> %d \n", pci_dev.device.nonBridge.interruptLine);
	shirq_t *shared_device = (shirq_t*)malloc(sizeof(shirq_t));
	shared_device->irq = pci_dev.device.nonBridge.interruptLine;
	shared_device->device_id = pci_dev.device.deviceID;
	shared_device->vendor_id = pci_dev.device.vendorID;
	shared_device->IrqHandler = hda_handler;
	AuSharedDeviceRegister(shared_device);

	if (!AuCheckSharedDevice(shared_device->irq,pci_dev.device.deviceID))
		AuInterruptSet(shared_device->irq, hda_handler,shared_device->irq);
	else
		AuInstallSharedHandler(shared_device->irq);

	//AuInterruptSet(pci_dev.device.nonBridge.interruptLine, hda_handler,pci_dev.device.nonBridge.interruptLine); 

	uintptr_t mmio = pci_dev.device.nonBridge.baseAddress[0] & ~3;
	hd_audio.mmio = (size_t)AuMapMMIO(mmio,8);
	hd_audio.corb = (uint32_t*)p2v((size_t)AuPmmngrAlloc());
	hd_audio.rirb = (uint64_t*)p2v((size_t)AuPmmngrAlloc());

	/* Avoid immediate use */
	hd_audio.immediate_use = false; 
	hd_audio.output_nid = 0;
	
	hda_reset();
	setup_corb();
	setup_rirb();

	uint16_t statests = _aud_inw_ (STATESTS);
	for (int i = 0; i < 15; i++) {
		if (statests & (1 >> i)){
			if (codec_enumerate_widgets(i)) {
				printf ("[driver]: hdaudio device found at index ->%d\n", i);
				break;
			}
		}
	} 

	widget_init_output(hd_audio.output_codec_id, hd_audio.output_nid);
	hda_init_output_stream();
	hda_set_volume(255);

	sound_t *sound = (sound_t*)malloc(sizeof(sound_t));
	strcpy(sound->name, "intel hd audio");
	sound->write = 0;
	sound->read = 0;
	sound->start_output_stream = hda_output_stream_start;
	sound->stop_output_stream = hda_output_stream_stop;
	sound->write = output_stream_write;
	AuSoundRegisterDevice(sound);


	printf ("[driver]: intel hda audio initialized vendor: %x device: %x\n", pci_dev.device.vendorID, pci_dev.device.deviceID);
	return 0;
}


/*
 * hda_set_output_nid -- set output nid
 * @param nid -- node id
 * @param codec -- output codec id
 * @param amp_gain -- amp gain step
 */
void hda_set_output_nid(uint16_t nid, uint8_t codec, uint32_t amp_gain) {
	if (hd_audio.output_nid == 0) {
		hd_audio.output_nid = nid;
		hd_audio.output_codec_id = codec;
		hd_audio.output_amp_gain_step = amp_gain;
	}
}

/*
 * hda_set_volume -- sets volume to output codec
 * @param volume -- volume level 
 */
void hda_set_volume (uint8_t volume) {
	int meta = 0xb000;
	if (volume == 0)
		volume = 0x80;
	else
		volume = volume * hd_audio.output_amp_gain_step / 255;

	codec_query(hd_audio.output_codec_id, hd_audio.output_nid, VERB_SET_AMP_GAIN_MUTE | meta | volume);
}


/*
 * hda_output_stream_start -- starts the output stream
 */
void hda_output_stream_start () {
	uint32_t value = _aud_inl_(REG_O0_CTLL);
	value |= 0x4;
	value |= 0x2;
    _aud_outw_(REG_O0_CTLL,value);
}

/*
 * hda_output_stream_stop -- stops the output stream
 */
void hda_output_stream_stop() {
	uint32_t value = _aud_inl_(REG_O0_CTLL);
	value &= ~0x2;
    _aud_outw_(REG_O0_CTLL,value);
}