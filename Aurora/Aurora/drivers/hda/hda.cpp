/**
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *   hda -- High Definition Audio Intel
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *  NOTE: My HD-Audio driver uses Immediate Command Interface
 *        works in QEMU :), in Virtual Box and VMware, not
 *        working
 * ================================================
 */

#include <drivers\hdaudio\hda.h>
#include <stdio.h>


hd_audio _ihd_audio;
uint16_t rirbrp = 0;
uint16_t corbrp = 0;

//! Command Transmitter and Receiver
void _aud_outl_(int reg, uint32_t value) {
	 volatile uint32_t* mmio = (uint32_t*)(_ihd_audio.mmio + reg);
	*mmio = value;
}

uint32_t _aud_inl_ (int reg) {
	volatile uint32_t* mmio = (uint32_t*)(_ihd_audio.mmio + reg);
	return *mmio;
}

void _aud_outw_ (int reg, uint16_t value) {
	uint16_t* mmio = (uint16_t*)(_ihd_audio.mmio + reg);
	*mmio = value;
}

uint16_t _aud_inw_(int reg) {
	volatile uint16_t* mmio = (uint16_t*)(_ihd_audio.mmio + reg);
	return *mmio;
}


void _aud_outb_ (int reg, uint8_t value) {
	volatile uint8_t* mmio = (uint8_t*)(_ihd_audio.mmio + reg);
	*mmio = value;
}

uint8_t _aud_inb_ (int reg) {
	volatile uint8_t* mmio = (uint8_t*)(_ihd_audio.mmio + reg);
	return *mmio;
}


void hda_handler (size_t v, void* p) {
	printf ("HD-Audio Interrupt fired++\n");
	//apic_local_eoi();
	interrupt_end(0);
}



//! Setup Common Output Ring Buffer
void setup_corb () {
	
	uint8_t reg;
	uint64_t corb_base;
	unsigned int corb_entries = 0;

	reg = _aud_inw_(CORBSIZE);
	printf ("CORB Size -> %x\n", reg);
	/* Check CORB size capabilities and choose the largest size */
	if (reg & (1 << 6)) {
		_ihd_audio.corb_entries = 256;
		printf ("CORB size -> 256\n");
		reg |= 0x2;
	} else if (reg & (1 << 5)) {
		_ihd_audio.corb_entries = 16;
		printf ("Corb size -> 16\n");
		reg |= 0x1;
	} else if (reg & (1 << 4)) {
		_ihd_audio.corb_entries = 2;
		printf ("Corb size -> 2\n");
		reg |= 0x0;
	} else {
		printf ("HD Audio: No Supported CORB Size!\n");
		_ihd_audio.corb_entries = 256;
		//reg |= 0x2;*/
	}

	_aud_outb_(CORBSIZE, reg);

	//printf ("CORB Entries -> %d\n", corb_entries);

	/* Set CORB Base Address */
	corb_base = (uintptr_t)_ihd_audio.corb;
	_aud_outl_(CORBLBASE, corb_base & 0xffffffff);
	_aud_outl_(CORBUBASE, corb_base >> 32);

	//printf ("CORB BASE LO -> %x\n", corb_base & 0xffffffff);
	//printf ("CORB BASE HI -> %x\n", corb_base >> 32);
	/* Start DMA engine */
	_aud_outl_(CORBCTL, 0x02);
}


//!Setup RIRB
void setup_rirb() {

	uint8_t reg;
	uint64_t rirb_base;
	uint32_t rirb_entries = 0;

	
	//_aud_outw_(RIRBCTL, 0);

	reg = _aud_inb_ (RIRBSIZE);
	printf ("RIRB SIZE reg -> %x\n", reg);
	/* Check RIRB size capabilities and choose the largest size */
	if (reg & (1 << 6)) {
		_ihd_audio.rirb_entries = 256;
		printf ("RIRB size -> 256\n");
		reg |= 0x2;
	} else if (reg & (1 << 5)) {
		_ihd_audio.rirb_entries = 16;
		printf ("RIRB size -> 16\n");
		reg |= 0x1;
	}else if (reg & (1 << 4)) {
		_ihd_audio.rirb_entries = 2;
		printf ("RIRB size -> 2\n");
		reg |= 0x0;
	}else {
		printf ("HD Audio: No supported RIRB size !!\n");
		//_ihd_audio.rirb_entries = 256;
		//reg |= 0x2;
	}

	_aud_outb_(RIRBSIZE,reg);

	/* Set RIRB Base address */
	rirb_base = (uintptr_t)_ihd_audio.rirb;
	_aud_outl_(RIRBLBASE, rirb_base & 0xffffffff);
	_aud_outl_(RIRBUBASE, rirb_base >> 32);

	_aud_outb_(RINTCNT, 0x42);
	/* Start DMA Engine */
	_aud_outl_(RIRBCTL, 0x1);
	_aud_outl_(RIRBCTL, (1<<1));
}


//* Write Commands to corb */
static void corb_write (uint32_t verb) {

	//uint16_t wp = _aud_inw_(CORBWP) & 0xff;
	//uint16_t rp;
	//uint16_t next;

	///*Wait until there's a free entry in the CORB */
	//next = (wp + 1) % _ihd_audio.corb_entries;   //corb_entries;

	//do {
	//	rp = _aud_inw_(CORBRP) & 0xff;
	//}while (next == rp);

	///* Write to CORB */
	//_ihd_audio.corb[next] = verb;
	//_aud_outw_(CORBWP, next);
	_aud_outl_(ICOI,verb);
	_aud_outl_(ICIS,1);
}

static void rirb_read (uint64_t *response) {
	//uint16_t wp;
	//uint16_t rp = rirbrp;

	///*Wait for an unread entry in the RIRB */
	//do {
	//   wp = _aud_inw_(RIRBWP) & 0xff;
	//} while (wp == rp);

	///*Read from RIRIB */
	//rp = (rp + 1) % _ihd_audio.rirb_entries;   //rirb_entries;
	//rirbrp = rp;
	*response = _aud_inl_(ICII);             //_ihd_audio.rirb[rp];
	//printf ("RIRB WP -> %x\n", _aud_inl_(ICII));
	_aud_outl_(ICIS, ~(1<<1));
}

static uint32_t codec_query (int codec, int nid, uint32_t payload) {
	uint64_t response; //= (uint64_t*)pmmngr_alloc();
	uint32_t icount = 1000;
	uint32_t verb = ((codec & 0xf) << 28) | 
		((nid & 0xff) << 20) | 
		(payload & 0xfffff);

	corb_write(verb);
	while (( _aud_inw_(ICIS) & 1) == 1){
		if(icount == 0){
			_aud_outw_(ICIS, 0);
			break;
		}
		icount--;
	}

	rirb_read(&response);
	return response & 0xffffffff;
}



void widget_init (int codec, int nid) {

	//printf ("[HD-Audio]: initializing widgets\n");
	uint32_t widget_cap;
	uint32_t type;
	uint32_t amp_cap;
	uint32_t eapd_btl;

	widget_cap = codec_query (codec, nid, VERB_GET_PARAMETER | PARAM_AUDIO_WID_CAP);

	if (widget_cap == 0) {
		//printf ("Widget capabilities 0\n");
		return;
	}

	type = (widget_cap & WIDGET_CAP_TYPE_MASK) >> WIDGET_CAP_TYPE_SHIFT;
	amp_cap = codec_query (codec, nid, VERB_GET_PARAMETER | PARAM_OUT_AMP_CAP);
	eapd_btl = codec_query (codec, nid, VERB_GET_EAPD_BTL);

	uint32_t amp_gain;
	const char* s;

	switch(type) {
	case 0:  s = "output"; break;
	case 1:  s = "input"; break;
	case 2:  s = "mixer"; break;
	case 3:  s = "selector"; break;
	case 4:  s = "pin complex"; break;
	case 5:  s = "power"; break;
	case 6:  s = "volume knob"; break;
	case 7:  s = "beep generator"; break;
	case 16: s = "vendor defined"; break;
	default: s = "unknown"; break;

	}

	amp_gain = codec_query(codec, nid, VERB_GET_AMP_GAIN_MUTE | 0x8000) << 8;
	amp_gain |= codec_query(codec, nid, VERB_GET_AMP_GAIN_MUTE | 0xa000);

	printf ("[HD-Audio]: widget %s at node %d; \n",
		s, nid);

	switch (type) {
	case WIDGET_PIN:
		{
			uint32_t pin_cap, ctl;
			uint32_t conf = codec_query(codec, nid, VERB_GET_CONFIG_DEFAULT);
			printf ("pin config: %x\n", conf);

			pin_cap = codec_query (codec, nid, VERB_GET_PARAMETER | PARAM_PIN_CAP);

			if ((pin_cap & PIN_CAP_OUTPUT) == 0) {
				return;
			}

			ctl = codec_query (codec, nid, VERB_GET_PIN_CONTROL);
			printf ("ctl: %x\n", ctl);

			ctl |= PIN_CTL_ENABLE_OUTPUT;
			codec_query(codec, nid, VERB_SET_PIN_CONTROL | ctl);
			codec_query(codec, nid, VERB_SET_EAPD_BTL | eapd_btl | 0x2);
			break;
		}

	case WIDGET_OUTPUT:
		{
			/*if (!output.nid) {
				kprintf ("using output at ID %d\n", nid);
				output.codec = codec;
				output.nid = nid;
				output.amp_gain_steps = (amp_cap >> 8) & 0x7f;
			}*/
			printf ("Widget type Output in codec -> %d at node -> %d\n", codec, nid);
			codec_query (codec, nid, VERB_SET_EAPD_BTL | eapd_btl | 0x2);
			break;
		}

	default:
		return;

	}

	if (widget_cap & WIDGET_CAP_POWER_CNTRL) {
		codec_query(codec, nid, VERB_SET_POWER_STATE | 0x0);
	}
}

static void codec_enumerate_widgets(int codec) {

	uint32_t param;
	int num_fg, num_widgets;
	int fg_start, widgets_start;
	int i, j;


	param = codec_query (codec, 0, VERB_GET_PARAMETER | PARAM_NODE_COUNT);

	num_fg = (param >> 0) & 0xff;
	fg_start = (param >> 16) & 0xff;

	//printf ("Param Returned -> %x\n", param);
	//printf ("[HD_Audio]: Num Function Group -> %d, fg_start -> %d\n", num_fg, fg_start);	

	if (num_fg == 0) 
		return;
	
	for (i = 0; i < num_fg; i++) {
		param = codec_query (codec, fg_start + i, 
			VERB_GET_PARAMETER | PARAM_NODE_COUNT);

		num_widgets = param & 0xff;
		widgets_start = (param >> 16) & 0xff;


		param = codec_query (codec, fg_start + i, VERB_GET_PARAMETER | PARAM_FN_GROUP_TYPE);
		param &= 0x7f;
		if (param != FN_GROUP_AUDIO) {
			continue;
		}

		codec_query (codec, fg_start + i, VERB_SET_POWER_STATE | 0x0);

		for (j = 0; j < num_widgets; j++) {
			widget_init(codec, widgets_start + j);
		}
	}


	//return output.nid ? 0 : -2;
}




//! Reset the HD Audio Controller
void hda_reset() {
	_aud_outl_(CORBCTL, 0);
	_aud_outl_(RIRBCTL, 0);
	//_aud_outw_(RIRBWP, 0);
	_aud_outl_(GCTL, 1);
	while ((_aud_inl_ (GCTL >> 0) & 0x3) != 1)
		;

	_aud_outw_ (WAKEEN, 1);
	//_aud_outw_ (STATESTS, 1);
	
	if((_aud_inw_(ICIS) & 1)==0)
		printf ("ICIS ICB bit is clear\n");
	
	uint16_t statests = _aud_inw_ (STATESTS);

	for (int i = 0; i < 15; i++) {
		if (statests & (1 << i)){
			codec_enumerate_widgets(i);
		}
	}
}


void hda_initialize () {
	pci_device_info pci_dev;
	if (!pci_find_device_class (0x04, 0x03, &pci_dev)){
		printf ("No HD-Audio was found\n");
		return;
	}

	x64_cli();

	//printf ("HD Audio found vendor -> %x, device -> %x\n", pci_dev.device.vendorID, pci_dev.device.deviceID);

	/*uint64_t* ring_address = (uint64_t*)malloc(1024 + 2048 + BDL_BYTES_ROUNDED + 128);
	memset (ring_address, 100, 1024 + 2048 + BDL_BYTES_ROUNDED + 128);*/

	if (pci_dev.device.nonBridge.interruptLine < 255) 
		interrupt_set (pci_dev.device.nonBridge.interruptLine, hda_handler, pci_dev.device.nonBridge.interruptLine);
	_ihd_audio.mmio = pci_dev.device.nonBridge.baseAddress[0]; //& ~3);
	_ihd_audio.corb = (uint64_t*)pmmngr_alloc(); //ring_address;   //for 256 entries only 1 kb will be used
	_ihd_audio.rirb = (uint64_t*)pmmngr_alloc(); //(ring_address + 1024);
	if (_aud_inw_ (GCAP) & 1) {
		printf ("HD-Audio 64-OK\n");
	}

	printf ("HD-Audio Version - %d.%d\n", _aud_inb_(VMAJ), _aud_inb_(VMIN));
	hda_reset();
	x64_sti();
}