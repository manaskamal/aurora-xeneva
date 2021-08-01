/**
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *   hda -- High Definition Audio Intel
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#include <drivers\hdaudio\hda.h>
#include <stdio.h>

/**
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
	apic_local_eoi();
}



//! Setup Common Output Ring Buffer
void setup_corb () {
	
	uint8_t reg;
	uint64_t corb_base;
	unsigned int corb_entries = 0;

	reg = _aud_inb_(CORBSIZE);

	/* Check CORB size capabilities and choose the largest size */
//	if (reg & (1 << 6)) {
//		corb_entries = 256;
//		reg |= 0x2;
//	} else if (reg & (1 << 5)) {
//		corb_entries = 16;
//		reg |= 0x1;
//	} else if (reg & (1 << 4)) {
//		corb_entries = 2;
//		reg |= 0x0;
//	} else {
//		printf ("HD Audio: No Supported CORB Size!\n");
//	}
//
//	_aud_outb_(CORBSIZE, reg);
//
//	printf ("CORB Entries -> %d\n", corb_entries);
//
//	/* Set CORB Base Address */
//	corb_base = (uintptr_t)_ihd_audio.corb;
//	_aud_outl_(CORBLBASE, corb_base & 0xffffffff);
//	_aud_outl_(CORBUBASE, corb_base >> 32);
//
//	printf ("CORB BASE LO -> %x\n", corb_base & 0xffffffff);
//	printf ("CORB BASE HI -> %x\n", corb_base >> 32);
//	/* Start DMA engine */
//	_aud_outb_(CORBCTL, 1);
//}
//
//
////!Setup RIRB
//void setup_rirb() {
//
//	uint8_t reg;
//	uint64_t rirb_base;
//	uint32_t rirb_entries = 0;
//	reg = _aud_inb_ (RIRBSIZE);
//
//	/* Check RIRB size capabilities and choose the largest size */
//	if (reg & (1 << 6)) {
//		rirb_entries = 256;
//		reg |= 0x2;
//	} else if (reg & (1 << 5)) {
//		rirb_entries = 16;
//		reg |= 0x1;
//	}else if (reg & (1 << 4)) {
//		rirb_entries = 2;
//		reg |= 0x0;
//	}else {
//		printf ("HD Audio: No supported RIRB size !!\n");
//	}
//
//	_aud_outb_(RIRBSIZE,reg);
//
//	/* Set RIRB Base address */
//	rirb_base = (uintptr_t)_ihd_audio.rirb;
//	_aud_outl_(RIRBLBASE, rirb_base & 0xffffffff);
//	_aud_outl_(RIRBUBASE, rirb_base >> 32);
//
//	_aud_outb_(RINTCNT, 0x42); 
//
//	uint8_t rirb_ctl = _aud_inb_(RIRBCTL);
//	printf ("RIRB Ctl ====== -> %x\n", rirb_ctl);
//	rirb_ctl |= (1<<0);
//	rirb_ctl |= (1<<1);
//	rirb_ctl |= (1<<2);
//	/* Start DMA Engine */
//	_aud_outb_(RIRBCTL, rirb_ctl);
//
//	uint8_t rirb_ctl2 = _aud_inb_(RIRBCTL);
//	printf ("RIRB Ctl ====== -> %x\n", rirb_ctl2);
//}
//
//
////* Write Commands to corb */
//static void corb_write (uint32_t verb) {
//
//	uint16_t wp = _aud_inw_(CORBWP) & 0xff;
//	uint16_t rp;
//	uint16_t next;
//
//	/*Wait until there's a free entry in the CORB */
//	next = (wp + 1) % 256;   //corb_entries;
//
//	do {
//		rp = _aud_inw_(CORBRP) & 0xff;
//	}while (next == rp);
//
//	/* Write to CORB */
//	_ihd_audio.corb[next] = verb;
//	_aud_outw_(CORBWP, next);
//}
//
//static void rirb_read (uint64_t *response) {
//
//	uint16_t wp;
//	uint16_t rp = rirbrp;
//
//	/*Wait for an unread entry in the RIRB */
//	/*do {
//	   wp = _aud_inw_(RIRBWP) & 0xff;
//	} while (wp == rp);
//*/
//	/*Read from RIRIB */
//	rp = (rp + 1) % 256;   //rirb_entries;
//	rirbrp = rp;
//	*response = _ihd_audio.rirb[rp];
//	_aud_outb_(RIRBSTS, 0x5);
//}
//
//static uint32_t codec_query (int codec, int nid, uint32_t payload) {
//	uint64_t response;
//	uint32_t verb = ((codec & 0xf) << 28) | 
//		((nid & 0xff) << 20) | 
//		(payload & 0xfffff);
//	corb_write(verb);
//	while ((_aud_inb_(RIRBSTS) &1) == 0)
//		;
//	rirb_read(&response);
//	return response & 0xffffffff;
//}
//
//
//
//void widget_init (int codec, int nid) {
//
//	printf ("initializing widgets\n");
//	uint32_t widget_cap;
//	uint32_t type;
//	uint32_t amp_cap;
//	uint32_t eapd_btl;
//
//	widget_cap = codec_query (codec, nid, VERB_GET_PARAMETER | PARAM_AUDIO_WID_CAP);
//
//	if (widget_cap == 0) {
//		printf ("Widget capabilities 0\n");
//		return;
//	}
//
//	type = (widget_cap & WIDGET_CAP_TYPE_MASK) >> WIDGET_CAP_TYPE_SHIFT;
//	amp_cap = codec_query (codec, nid, VERB_GET_PARAMETER | PARAM_OUT_AMP_CAP);
//	eapd_btl = codec_query (codec, nid, VERB_GET_EAPD_BTL);
//
//	uint32_t amp_gain;
//	const char* s;
//
//	switch(type) {
//	case 0:  s = "output"; break;
//	case 1:  s = "input"; break;
//	case 2:  s = "mixer"; break;
//	case 3:  s = "selector"; break;
//	case 4:  s = "pin complex"; break;
//	case 5:  s = "power"; break;
//	case 6:  s = "volume knob"; break;
//	case 7:  s = "beep generator"; break;
//	case 16: s = "vendor defined"; break;
//	default: s = "unknown"; break;
//
//	}
//
//	amp_gain = codec_query(codec, nid, VERB_GET_AMP_GAIN_MUTE | 0x8000) << 8;
//	amp_gain |= codec_query(codec, nid, VERB_GET_AMP_GAIN_MUTE | 0xa000);
//
//	printf ("%s at ID %d; \n",
//		s, nid);
//
//	switch (type) {
//	case WIDGET_PIN:
//		{
//			uint32_t pin_cap, ctl;
//			uint32_t conf = codec_query(codec, nid, VERB_GET_CONFIG_DEFAULT);
//			printf ("pin config: %x\n", conf);
//
//			pin_cap = codec_query (codec, nid, VERB_GET_PARAMETER | PARAM_PIN_CAP);
//
//			if ((pin_cap & PIN_CAP_OUTPUT) == 0) {
//				return;
//			}
//
//			ctl = codec_query (codec, nid, VERB_GET_PIN_CONTROL);
//			printf ("ctl: %x\n", ctl);
//
//			ctl |= PIN_CTL_ENABLE_OUTPUT;
//			codec_query(codec, nid, VERB_SET_PIN_CONTROL | ctl);
//			codec_query(codec, nid, VERB_SET_EAPD_BTL | eapd_btl | 0x2);
//			break;
//		}
//
//	case WIDGET_OUTPUT:
//		{
//			/*if (!output.nid) {
//				kprintf ("using output at ID %d\n", nid);
//				output.codec = codec;
//				output.nid = nid;
//				output.amp_gain_steps = (amp_cap >> 8) & 0x7f;
//			}*/
//
//			codec_query (codec, nid, VERB_SET_EAPD_BTL | eapd_btl | 0x2);
//			break;
//		}
//
//	default:
//		return;
//
//	}
//
//	if (widget_cap & WIDGET_CAP_POWER_CNTRL) {
//		codec_query(codec, nid, VERB_SET_POWER_STATE | 0x0);
//	}
//}
//
//static void codec_enumerate_widgets(int codec) {
//
//	uint32_t param;
//	int num_fg, num_widgets;
//	int fg_start, widgets_start;
//	int i, j;
//
//
//	param = codec_query (codec, 0, VERB_GET_PARAMETER | PARAM_NODE_COUNT);
//
//	num_fg = param & 0xff;
//	fg_start = (param >> 16) & 0xff;
//
//	printf ("%d function groups starting at ID %d\n", num_fg, fg_start);
//
//	for (i = 0; i < num_fg; i++) {
//		printf ("Looping %d\n", num_fg);
//		param = codec_query (codec, fg_start + i, 
//			VERB_GET_PARAMETER | PARAM_NODE_COUNT);
//
//		num_widgets = param & 0xff;
//		widgets_start = (param >> 16) & 0xff;
//
//		printf ("%d widgets starting at ID %d\n", num_widgets, widgets_start);
//
//		param = codec_query (codec, fg_start + i, VERB_GET_PARAMETER | PARAM_FN_GROUP_TYPE);
//		param &= 0x7f;
//		if (param != FN_GROUP_AUDIO) {
//			printf ("Funtion group type %x\n", param);
//			continue;
//		}
//
//		codec_query (codec, fg_start + i, VERB_SET_POWER_STATE | 0x0);
//
//		for (j = 0; j < num_widgets; j++) {
//			widget_init(codec, widgets_start + j);
//		}
//	}
//
//	//return output.nid ? 0 : -2;
//}
//
//void hda_enumerate_codecs() {
//	
//	uint16_t statests;
//	int i;
//
//	printf ("HD Audio: Enumerating HDA Link Protocol\n");
//	statests = _aud_inw_(STATESTS);
//
//	//! loop
//	for (i = 0; i < 15; i++) {
//		if ((statests & (1 << i))){
//			printf ("Available Codec found at index %d\n", i);
//			//codec_enumerate_widgets(i);
//			widget_init(i,0);
//		}
//	}
//}
//
//
////! Reset the HD Audio Controller
//void hda_reset() {
//    printf ("HD Audio : Reset Controller started\n");
//
//	//! clear CORB/RIRB RUN bits before reset
//
//	//! Reset the CRST bit and wait until hardware is in reset 
//
//	//! Take Controller out of reset
//	_aud_outl_(GCTL, GCTL_RESET);
//	while((_aud_inl_(GCTL) & GCTL_RESET) == 0);
//
//	printf ("HD Audio : Controller out of reset\n");
//
//	//! We want to get all interrupts
//	uint16_t wakeen_bit = _aud_inw_ (WAKEEN);
//	wakeen_bit |= 1 << 1;
//	_aud_outw_(WAKEEN, wakeen_bit);    //0xffff
//	
//	uint32_t int_ctl = _aud_inl_ (INTCTL);
//	printf ("INT CTL -> %x\n", int_ctl);
//	int_ctl |= (1 << 0);
//	int_ctl |= (1 << 1);
//	int_ctl |= (1 << 2);
//	_aud_outl_(INTCTL, int_ctl);   //0x800000ff
//
//	uint32_t int_ctl2 = _aud_inl_ (INTCTL);
//	printf ("INT CTL2 -> %x\n", int_ctl2);
//
//	printf ("HD Audio: Reset completed\n");
//
//
//	_aud_outb_(CORBCTL, 0);
//	uint8_t rirb_ctl = _aud_inb_(RIRBCTL);
//	printf ("CORBCONTROL is fully reseted\n");
//	printf ("RIRB Ctl -> %x\n", rirb_ctl);
//	rirb_ctl |= (1<<0);
//	rirb_ctl |= (1<<1);
//	rirb_ctl |= (1<<2);
//	_aud_outb_(RIRBCTL,0);
//
//	uint8_t corb_ctl = _aud_inb_ (CORBCTL);
//	printf ("CORB CTL -> %x\n", corb_ctl);
//	setup_corb();
//	setup_rirb();
//	printf ("CORB\RIRB setup\n");
//
//	hda_enumerate_codecs();
//}
//
//
//void hda_initialize () {
//	pci_device_info pci_dev;
//	if (!pci_find_device_class (0x04, 0x03, &pci_dev)){
//		printf ("No HD-Audio was found\n");
//		return;
//	}
//
//	printf ("HD-Audio found\n");
//	printf ("HD-Base Address -> %x\n", pci_dev.device.nonBridge.baseAddress[0] & ~(0xF));
//	printf ("HD-Audio Interrupt line -> %d\n", pci_dev.device.nonBridge.interruptLine);
//	printf ("HD-Audio Interrupt pin -> %d\n", pci_dev.device.nonBridge.interruptPin);
//	printf ("HD-Audio ALL Interrupt line -> %d\n", pci_dev.device.all.interruptLine);
//
//
//	interrupt_set (pci_dev.device.nonBridge.interruptLine, hda_handler, pci_dev.device.nonBridge.interruptLine);
//	_ihd_audio.mmio = (pci_dev.device.nonBridge.baseAddress[0] & ~(0xF));
//	_ihd_audio.corb = (uint64_t*)pmmngr_alloc();   //for 256 entries only 1 kb will be used
//	_ihd_audio.rirb = (uint64_t*)pmmngr_alloc();
//
//
//	printf ("HD-MMIO -> %x\n", _ihd_audio.mmio);
//	printf ("HD-Audio CORB -> %x\n", _ihd_audio.corb);
//	hda_reset();
//
//}