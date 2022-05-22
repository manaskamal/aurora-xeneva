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
#include <drivers\pcie.h>
#include <hal.h>
#include <stdio.h>
#include <arch\x86_64\mmngr\paging.h>
#include <shirq.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <sound.h>
#include <serial.h>
#include "codecs\sigmatel.h"
#include <arch\x86_64\apic.h>
#include <arch\x86_64\thread.h>

/* global variables */
hd_audio_t hd_audio;
uint16_t rirbrp = 0;
uint16_t corbwp = 0;
shirq_t *shared_device;

bool hda_first_interrupt = false;
bool debug = false;
void (*codec_initialize_output)(int codec, int nid);
void (*codec_set_volume) (uint8_t vol, int codec);

void _aud_outl_(int reg, uint32_t value) {
	 volatile uint32_t* mmio = (uint32_t*)(hd_audio.mmio + reg);
	 if (debug) {
		_debug_print_ ("OUTL: value -> %x, mmio -> %x \r\n", value, mmio);
	 }
	*mmio = value;
	if (debug) {
		_debug_print_ ("OUTL: REREAD: -> %x \r\n", *mmio);
	}
}

uint32_t _aud_inl_ (int reg) {
    volatile uint32_t* mmio = (uint32_t*)(hd_audio.mmio + reg);
	return *mmio;
}

void _aud_outw_ (int reg, uint16_t value) {
	volatile uint16_t* mmio = (uint16_t*)(hd_audio.mmio + reg);
	if (debug) {
		_debug_print_ ("OUTW: value -> %x, mmio -> %x \r\n", value, mmio);
	 }
	*mmio = value;
	if (debug) {
		_debug_print_ ("OUTW: REREAD: -> %x \r\n", _aud_inw_(reg));
	}
}

uint16_t _aud_inw_(int reg) {
	volatile uint16_t* mmio = (uint16_t*)(hd_audio.mmio + reg);
	return *mmio;
}

void _aud_outb_ (int reg, uint8_t value) {
	
	 volatile uint8_t* mmio = (uint8_t*)(hd_audio.mmio + reg);
	 if (debug) {
		_debug_print_ ("OUTB: value -> %x, mmio -> %x \r\n", value, mmio);
	 }
	*mmio = value;
	if (debug) {
		_debug_print_ ("OUTB: REREAD: -> %x \r\n", _aud_inb_(reg));
	}
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
		printf ("[driver]: hd-audio no supported corb size found \n");
	}

	_aud_outb_(CORBSIZE, reg);

	/* Set CORB Base Address */
	corb_base = (uint64_t)v2p((size_t)hd_audio.corb);

	_aud_outl_(CORBLBASE, corb_base);
	_aud_outl_(CORBUBASE, corb_base >> 32);
	
	_aud_outw_ (CORBWP, corbwp);
	_aud_outw_ (CORBRP, 0x8000);
	_aud_outw_ (CORBRP, 0x0);
	
	/* Start DMA engine */
	//_aud_outb_(CORBCTL, 0x1);
	uint8_t corbctl = _aud_inb_(CORBCTL);
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
		//hd_audio.rirb_entries = 256;
		//reg |= 0x2;
		printf ("[driver]: hdaudio no supported rirb size found \n");
	}

	_aud_outb_(RIRBSIZE,reg);
	/* Set RIRB Base address */
	rirb_base = (uint64_t)v2p((size_t)hd_audio.rirb);
	printf ("rirb base -> %x \n", rirb_base);
	_aud_outl_(RIRBLBASE, rirb_base);
	_aud_outl_(RIRBUBASE, rirb_base >> 32);
	
	_aud_outw_ (RIRBWP, 0x8000);
	_aud_outw_(RINTCNT, hd_audio.rirb_entries / 2);
	_aud_outb_ (RIRBCTL,0x1);
	/* Start DMA Engine */
	uint8_t rirbctl = _aud_inb_ (RIRBCTL);
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
	uint16_t wp = _aud_inw_(CORBWP) & 0xff;
	uint16_t rp = _aud_inw_(CORBRP) & 0xff;
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
	_aud_outl_(CORBCTL, 0);
	_aud_outl_(RIRBCTL, 0);

	while ((_aud_inl_(CORBCTL) & CORBCTL_CORBRUN) ||
		(_aud_inl_(RIRBCTL) & RIRBCTL_RIRBRUN));

	_aud_outl_(GCTL, 0);
	while((_aud_inl_(GCTL) & GCTL_RESET));

	/* Delay */
	//for (int i = 0; i < 10000000; i++)
	//	;


	_aud_outl_(GCTL, GCTL_RESET);
	while((_aud_inl_(GCTL) & GCTL_RESET) == 0);


	_aud_outw_(WAKEEN, 0xffff);
	uint32_t intctl = _aud_inl_(INTCTL);
	_aud_outl_(INTCTL, 0x800000ff);

	setup_corb();
	setup_rirb();

	for (int i = 0; i < 10000; i++)
		;
	
}


/*
 * AuDriverUnload -- Frees and clear up everthing of hda driver
 * turn hda off!
 */
AU_EXTERN AU_EXPORT int AuDriverUnload(){
	return 0;
}

void hda_handler (size_t v, void* p) {
//	AuInterruptEnd(0);
	if (hda_first_interrupt == false){
		hda_first_interrupt = true;
	}

	uint32_t isr = _aud_inl_(INTSTS);
	uint8_t sts = _aud_inb_(REG_O0_STS);
	
	printf("HDA Handler \r\n");
	if (sts & 0x4) {
		printf ("HDA Buffer completed \r\n");
	//	hda_output_stream_stop();
	
	}

    _aud_outl_(INTSTS, isr);
	_aud_outb_ (REG_O0_STS,sts);
	
	
	AuInterruptEnd(hd_audio.irq);
	//AuFiredSharedHandler(hd_audio.irq,v,p, shared_device);
	
}


void hd_thr() {
	uint64_t* dma = (uint64_t*)hd_audio.dma_pos_buff;
	uint32_t pos = 0;
	uint32_t old_pos  = dma[4] & 0xffffffff;
	old_pos /= BUFFER_SIZE;
	while(1) {
		pos = dma[4] & 0xffffffff;
		pos /= BUFFER_SIZE;
		if (old_pos != pos) {
			AuSoundRequestNext((uint64_t*)(hd_audio.sample_buffer + old_pos * BUFFER_SIZE));
			old_pos = pos;
		}
		sleep_thread(get_current_thread(), 100);
		force_sched();
	}
}

/*
 * AuDriverMain -- Main entry for hda driver
 */
AU_EXTERN AU_EXPORT int AuDriverMain(){

	hda_first_interrupt = false;

	uint64_t device = pci_express_scan_class (0x04, 0x03);
	if (device == 0xFFFFFFFF){
		printf ("[driver]: intel hda not found\n");
		return 1;
	}
	

	/*uint8_t tcsel;
	tcsel = pci_express_read(device,0x44);
	pci_express_write(device,0x44,(tcsel & 0xf8));*/

	codec_initialize_output = NULL;
	codec_set_volume = NULL;


	uint32_t command = pci_express_read(device ,PCI_COMMAND);
	command |= (1<<2);
	command |= (1<<1);
	command &= ~(1<<10);
	 //clear the Interrupt disable
	pci_express_write(device, PCI_COMMAND, command);

	uint32_t com2 = pci_express_read2(device, PCI_COMMAND, 4);

	printf ("Comm -> %x, comm2-> %x \n", command, com2);
	if ((com2 & (1<<10)) ){
		printf ("Interrupt not disabled \n");
	}

	uint32_t stat = pci_express_read(device, PCI_STATUS);
	if ((stat & (1<<3) != 0) && (command & (1<<10) != 1)){
		printf ("HDA supports interrupt \n");
	}

	if (stat & (1<<4)){
		printf ("HDA supports cap list\n");
	}
	
	shared_device = (shirq_t*)malloc(sizeof(shirq_t));
	shared_device->irq = pci_express_read(device, PCI_INTERRUPT_LINE);
	shared_device->device_id = pci_express_read(device,PCI_DEVICE_ID);
	shared_device->vendor_id = pci_express_read(device,PCI_VENDOR_ID);
	shared_device->IrqHandler = hda_handler;
	AuSharedDeviceRegister(shared_device);

	hd_audio.irq = shared_device->irq;

	AuInterruptSet(3, hda_handler, 3, false);
	AuInterruptSet(4, hda_handler, 4, false);
	AuInterruptSet(5, hda_handler, 5, false);
	AuInterruptSet(6, hda_handler, 6, false);
	AuInterruptSet(10, hda_handler, 10, false);
	AuInterruptSet(11, hda_handler, 11, false);
	AuInterruptSet(14, hda_handler, 14, false);
	AuInterruptSet(15, hda_handler, 15, false);
	//AuInterruptSet(7, hda_handler, 7, false);

	uintptr_t mmio = pci_express_read(device, PCI_BAR0);
	printf ("HDA base address -> %x , irq -> %d\n", mmio, hd_audio.irq);
	hd_audio.mmio = (uint64_t)AuMapMMIO(mmio,2);
	/*uint64_t phys = (uint64_t)AuPmmngrAlloc();
	uint64_t dma_buffer_virt = (uint64_t)AuMapMMIO(phys,1);
	hd_audio.dma_buffer_phys = (uint64_t)phys;*/
	hd_audio.corb = (uint32_t*)p2v((size_t)AuPmmngrAlloc());
	hd_audio.rirb = (uint64_t*)p2v((size_t)AuPmmngrAlloc());
	memset((void*)hd_audio.corb, 0, 4096);
	memset((void*)hd_audio.rirb, 0, 4096);
	

	printf ("[drivers]: hda interrupt line -> %d \n", shared_device->irq);
	/* Avoid immediate use */
	hd_audio.immediate_use = false; 
	hd_audio.output_ptr = 0;
	
	

	 uint16_t gcap = _aud_inw_(GCAP);
	 uint16_t num_oss = HDA_GCAP_OSS(gcap);
	 uint16_t num_iss = HDA_GCAP_ISS(gcap);

	 hd_audio.num_iss = num_iss;
	 hd_audio.num_oss = num_oss;
	 
	 hda_reset();

	 printf ("Reset completed \n");
	

	uint16_t statests = _aud_inw_ (STATESTS);
	for (int i = 0; i < 15; i++) {
		if (statests & (1 >> i)){
			if (codec_enumerate_widgets(i)) {
				printf ("[driver]: hdaudio device found at index ->%d\n", i);
				break;
			}
		}
	} 

	
	hda_init_output_stream();
	widget_init_output();
	hda_set_volume(255);

	sound_t *sound = (sound_t*)malloc(sizeof(sound_t));
	strcpy(sound->name, "intel hd audio");
	sound->read = 0;
	sound->start_output_stream = hda_output_stream_start;
	sound->stop_output_stream = hda_output_stream_stop;
	sound->write = output_stream_write;
	AuSoundRegisterDevice(sound);

	thread_t *t = create_kthread(hd_thr,(uint64_t)p2v((size_t)AuPmmngrAlloc() + 4096),(uint64_t)AuGetRootPageTable(),"hda",1);

	printf ("[driver]: intel hda audio initialized vendor: %x device: %x\n", shared_device->vendor_id, shared_device->device_id);
	//

	return 0;
}


/*
 * hda_set_output_nid -- set output nid
 * @param nid -- node id
 * @param codec -- output codec id
 * @param amp_gain -- amp gain step
 */
void hda_set_output_nid(uint16_t nid, uint8_t codec, uint32_t amp_gain) {

	if(hd_audio.output[hd_audio.output_ptr] == NULL){
		hd_output_t *output = (hd_output_t*)malloc(sizeof(hd_output_t));
		output->output_codec_id = codec;
		output->output_nid = nid;
		output->output_amp_gain_step = amp_gain;
		hd_audio.output[hd_audio.output_ptr] = output;
		hd_audio.output_ptr++;
	}
}

void widget_init_output () {
	int codec, nid = 0;
	if (codec_initialize_output) {
		codec_initialize_output(hd_audio.output[0]->output_codec_id,hd_audio.output[0]->output_nid);
		return;
	}

	for (int i = 0; i < hd_audio.output_ptr; i++) {
		codec = hd_audio.output[i]->output_codec_id;
		nid = hd_audio.output[i]->output_nid;
		/* first output channel is 0x10 */
		codec_query(codec, nid,VERB_SET_STREAM_CHANNEL | (1<<4) | 1);
		uint32_t stream = codec_query(codec, nid, VERB_GET_STREAM_CHANNEL);
		uint16_t format =   (1<<15) | SR_44_KHZ | (0<<11) | (0 << 8) | BITS_16| 1;
		codec_query(codec, nid,VERB_SET_FORMAT | format);
		codec_query(codec, nid,VERB_SET_PIN_CONTROL | (1<<6));

		codec_query(codec, nid, VERB_SET_CONV_CHANNEL_COUNT | 1);
		stream = codec_query(codec, nid, VERB_GET_CONV_CHANNEL_COUNT);


		uint32_t eapd_ = codec_query (codec,nid, VERB_GET_EAPD_BTL);	
		codec_query (codec, nid,VERB_SET_EAPD_BTL | eapd_ | 0x2);

		codec_query(codec, nid,VERB_SET_POWER_STATE | 0x1);
		//_aud_outw_(REG_O0_FMT, format);
	}
}


/*
 * hda_set_volume -- sets volume to output codec
 * @param volume -- volume level 
 */
void hda_set_volume (uint8_t volume) {
	if (codec_set_volume) {
		codec_set_volume(volume,hd_audio.output[0]->output_codec_id);
		return;
	}
	
	int meta = 0xb000;
	int codec, nid = 0;

	for (int i = 0; i < hd_audio.output_ptr; i++) {
		codec = hd_audio.output[i]->output_codec_id;
		nid = hd_audio.output[i]->output_nid;
		if (volume == 0)
			volume = 0x80;
		else
			volume = 255; //volume * hd_audio.output[0]->output_amp_gain_step / 255;*/
		//_debug_print_ ("AMP Gain %d \r\n",hd_audio.output[0]->output_amp_gain_step );
		uint32_t vol = codec_query(codec, nid, VERB_GET_AMP_GAIN_MUTE);
		vol |= (1<<15);
		vol |= (1<<13);
		vol |= (1<<12);
		vol &= ~(1<<7);
		vol |= volume;
		codec_query(codec,nid, VERB_SET_AMP_GAIN_MUTE | meta | volume);
	}
	
}



/*
 * hda_output_stream_start -- starts the output stream
 */
void hda_output_stream_start () {
	uint32_t ssync = _aud_inl_ (SSYNC);
	ssync &= ~(1<<4);
	_aud_outl_(SSYNC, ssync);

	uint8_t value = _aud_inb_(REG_O0_CTLL);
	value |= HDAC_SDCTL_IOCE; // | HDAC_SDCTL_RUN;
	value |= (1<<1);
    _aud_outb_(REG_O0_CTLL,value);
}

/*
 * hda_output_stream_stop -- stops the output stream
 */
void hda_output_stream_stop() {
	uint32_t value = _aud_inl_(REG_O0_CTLL);
	value &= ~(1<<1);
    _aud_outw_(REG_O0_CTLL,value);
}

/*
 * hda_set_codec_init_func -- sets function pointer to each codecs
 * initialisation code
 */
void hda_set_codec_init_func (void (*init_func)(int codec, int nid)) {
	if (codec_initialize_output)
		return;
	codec_initialize_output = init_func;
}

/*
 * hda_set_volume_func -- sets function pointer to each codecs volume 
 * function
 */
void hda_set_volume_func (void (*set_vol) (uint8_t volume, int codec)) {
	if (codec_set_volume)
		return;
	codec_set_volume = set_vol;
}

void hda_audio_set_dma_pos (uint64_t dma_buff) {
	hd_audio.dma_pos_buff = dma_buff;
}

uint64_t hda_get_dma_pos_buffer () {
	return hd_audio.dma_pos_buff;
}

void hda_set_sample_buffer(uint64_t buffer) {
	hd_audio.sample_buffer = buffer;
}