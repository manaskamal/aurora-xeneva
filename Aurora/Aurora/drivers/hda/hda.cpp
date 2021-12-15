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
#include <string.h>

//! static datas
hd_audio _ihd_audio;
uint16_t rirbrp = 0;
uint16_t corbwp = 0;

/** 
 *  MMIO -> Data Input / Output
 */

//! SIZE -> 4 bytes
void _aud_outl_(int reg, uint32_t value) {
	 volatile uint32_t* mmio = (uint32_t*)(_ihd_audio.mmio + reg);
	*mmio = value;
}

//! Size ->  4 bytes
uint32_t _aud_inl_ (int reg) {
    volatile uint32_t* mmio = (uint32_t*)(_ihd_audio.mmio + reg);
	return *mmio;
}

//! Size -> 2 bytes
void _aud_outw_ (int reg, uint16_t value) {
	volatile uint16_t* mmio = (uint16_t*)(_ihd_audio.mmio + reg);
	*mmio = value;
}

//! Size -> 2 bytes
uint16_t _aud_inw_(int reg) {
	volatile uint16_t* mmio = (uint16_t*)(_ihd_audio.mmio + reg);
	return *mmio;
}

//! Size -> 1 byte
void _aud_outb_ (int reg, uint8_t value) {
	 volatile uint8_t* mmio = (uint8_t*)(_ihd_audio.mmio + reg);
	*mmio = value;
}

//! Size -> 1 byte
uint8_t _aud_inb_ (int reg) {
	volatile uint8_t* mmio = (uint8_t*)(_ihd_audio.mmio + reg);
	return *mmio;
}

////!=======================================================================
////!=======================================================================
////!=======================================================================



/**
 * Interrupt handler for intel hd audio
 */
void hda_handler (size_t v, void* p) {
	uint32_t isr = _aud_inl_(INTSTS);
	uint8_t sts = _aud_inb_(REG_O0_STS(_ihd_audio));


	if (sts & 0x4) {
		//printf ("[HD-Audio]: Output stream 1 buffer completed\n");
		hda_output_stop();
	}

	_aud_outl_(INTSTS, isr);
	_aud_outb_ (REG_O0_STS(_ihd_audio),sts);
	//apic_local_eoi();
	interrupt_end(1);
}



//! Setup Common Output Ring Buffer
void setup_corb () {
	
	uint8_t reg;
	uint64_t corb_base;
	unsigned int corb_entries = 0;

	reg = _aud_inb_(CORBSIZE);
	/* Check CORB size capabilities and choose the largest size */
	if (reg & (1 << 6)) {
		_ihd_audio.corb_entries = 256;
		reg |= 0x2;
	} else if (reg & (1 << 5)) {
		_ihd_audio.corb_entries = 16;
		reg |= 0x1;
	} else if (reg & (1 << 4)) {
		_ihd_audio.corb_entries = 2;
		reg |= 0x0;
	} else {
		_ihd_audio.corb_entries = 256;
		reg |= 0x2;
	}

	_aud_outb_(CORBSIZE, reg);


	/* Set CORB Base Address */
	corb_base = (uintptr_t)_ihd_audio.corb;
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


//!Setup RIRB
void setup_rirb() {

	uint8_t reg;
	uint64_t rirb_base;
	uint32_t rirb_entries = 0;

	
	//_aud_outw_(RIRBCTL, 0);

	reg = _aud_inb_ (RIRBSIZE);
	/* Check RIRB size capabilities and choose the largest size */
	if (reg & (1 << 6)) {
		_ihd_audio.rirb_entries = 256;
		reg |= 0x2;
	} else if (reg & (1 << 5)) {
		_ihd_audio.rirb_entries = 16;
		reg |= 0x1;
	}else if (reg & (1 << 4)) {
		_ihd_audio.rirb_entries = 2;
		reg |= 0x0;
	}else {
		printf ("HD Audio: No supported RIRB size !!\n");
		_ihd_audio.rirb_entries = 256;
		reg |= 0x2;
	}

	_aud_outb_(RIRBSIZE,reg);

	/* Set RIRB Base address */
	rirb_base = (uint64_t)_ihd_audio.rirb;
	_aud_outl_(RIRBLBASE, rirb_base);
	_aud_outl_(RIRBUBASE, rirb_base >> 32);

	_aud_outw_ (RIRBWP, 0x8000);

	_aud_outw_(RINTCNT, _ihd_audio.rirb_entries / 2);

	_aud_outb_ (RIRBCTL,0x1);
	/* Start DMA Engine */
	uint32_t rirbctl = _aud_inb_ (RIRBCTL);
	rirbctl |= 0x2;
	_aud_outb_ (RIRBCTL,rirbctl);

}


/** Send a command to controller through CORB 
 * @param verb --> Command
 */
static void corb_write (uint32_t verb) {

	//! Check for immediate use
	if (_ihd_audio.immediate_use) {
		_aud_outl_(ICOI,verb);
		_aud_outl_(ICIS,1);
		return;
	}

	//! else use standard command transmitting method
	uint16_t wp = _aud_inw_(CORBWP) & 0xff;
	uint16_t rp = _aud_inw_(CORBRP) & 0xff;
    corbwp = 0;
	corbwp = (rp + 1);
	corbwp %= _ihd_audio.corb_entries;
	
	/*Wait until there's a free entry in the CORB */
	do {
		rp = _aud_inw_(CORBRP) & 0xff;
	}while (rp == corbwp);

	
	/* Write to CORB */	
	_ihd_audio.corb[corbwp] = verb;	
    _aud_outw_(CORBWP, corbwp);

}


/**
 * Read a response from RIRB
 *
 * @param response - > address to where the controller will write response
 */
static void rirb_read (uint64_t *response) {
	uint16_t wp = _aud_inb_ (RIRBWP);
	uint16_t rp = rirbrp;
	uint16_t old_rp = rp;


	/*Wait for an unread entry in the RIRB */
	while (rirbrp == wp) {
		wp = _aud_inw_(RIRBWP);  //_aud_inb_(RIRBWP);
	}

	rp = (rp + 1) % _ihd_audio.rirb_entries;
	rirbrp = rp;
	*response = _ihd_audio.rirb[rp];
	_aud_outb_ (RIRBSTS, 0x5);
	return;
}


/**
 * one time function for sending command and reading response
 */
uint32_t codec_query (int codec, int nid, uint32_t payload) {
	uint64_t response;// = (uint32_t)pmmngr_alloc();
	uint32_t icount = 10000;
	uint32_t verb = ((codec & 0xf) << 28) | 
		((nid & 0xff) << 20) | 
		(payload & 0xfffff);

	corb_write(verb);
	uint8_t rirb_status;
	do {
		rirb_status = _aud_inb_(RIRBSTS);
	}while ((rirb_status & 1) == 0);


	rirb_read(&response);
	return response & 0xffffffff;
}



//! Set volume, for output codec
void hda_set_volume (uint8_t volume) {
	int meta = 0xb000;
	if (volume == 0)
		volume = 0x80;  //mute bit
	/*else
		volume = volume * 127 / 255;*/
	//codec_query (_ihd_audio.output->codec, _ihd_audio.output->nid, VERB_SET_AMP_GAIN_MUTE | 0xb000 | volume);
		
	codec_query (_ihd_audio.output->codec, 2, 0x39000 | volume);
	codec_query (_ihd_audio.output->codec, 2, 0x3A000 | volume );
	codec_query (_ihd_audio.output->codec, 3, 0x39000 | volume);
	codec_query (_ihd_audio.output->codec, 3, 0x3A000 | volume);
	codec_query (_ihd_audio.output->codec, 4, 0x39000 | volume);
	codec_query (_ihd_audio.output->codec, 4, 0x3A000 | volume);
	codec_query (_ihd_audio.output->codec, 5, 0x39000 | volume);
	codec_query (_ihd_audio.output->codec, 5, 0x3A000 | volume);
	codec_query (_ihd_audio.output->codec, 6, 0x39000 | volume);
	codec_query (_ihd_audio.output->codec, 6, 0x3A000 | volume);

}

//! Start a Stream !!! Errors are there, needs fixing
//! not completed yet
void hda_init_output_stream () {
	_aud_outl_ (REG_O0_CTLL(_ihd_audio), 1); //clear the run bit
	for (int i = 0; i < 1000; i++)
		;

	_aud_outl_ (REG_O0_CTLL(_ihd_audio), 0);
	for (int i = 0; i < 1000; i++)
		;
	uint64_t bdl_base = (uint64_t)pmmngr_alloc();   //get_physical_address  ((uint64_t) 0x0000000000000000);
	ihda_bdl_entry *bdl = (ihda_bdl_entry*)bdl_base;  //(_ihd_audio.corb + 3072);
	int j = 0;
	for (j = 0; j < 16; j++) {
		bdl[j].paddr = (uint64_t)get_physical_address((uint64_t)_ihd_audio.buffer + j * 0x10000);
		bdl[j].length = 0x10000;
		bdl[j].flags = 0;
	}

	bdl[j-1].flags = 1;

	_aud_outl_ (REG_O0_CTLL(_ihd_audio),(1<<20)); 
	_aud_outl_ (REG_O0_CTLU(_ihd_audio),(1<<20));

	_aud_outl_ (REG_O0_CBL(_ihd_audio),16*0x10000);
	_aud_outw_(REG_O0_STLVI(_ihd_audio), 16-1);

	_aud_outl_ (REG_O0_BDLPL(_ihd_audio), bdl_base);
	_aud_outl_ (REG_O0_BDLPU(_ihd_audio), bdl_base >> 32);

	uint16_t format = (0<<14)  | (1<<4) | 1;  // (0<<14) | (0<<11) | (0<<8) | (1<<4) | 1;
	_aud_outw_ (REG_O0_FMT(_ihd_audio), format);

	_aud_outb_(REG_O0_STS(_ihd_audio), (1<<2) | (1<<3) | (1<<4));

	uint64_t* dma_pos = (uint64_t*)pmmngr_alloc();
	for (int i = 0; i < 8; i++) {
		dma_pos[i] = 0;
	}

	_aud_outl_ (DPIBLBASE, (uint32_t)dma_pos | 0x1);
	_aud_outl_ (DPIBUBASE, (uint32_t)dma_pos >> 32);

}

/**
 * Initialize the output !!
 * for now it uses Sigmatel registers
 */
void hda_init_output () {
	uint16_t format =  (0<<14)  | (1<<4) | 1;
	codec_query (_ihd_audio.output->codec, 2, VERB_SET_FORMAT | format);
	codec_query (_ihd_audio.output->codec, 3, VERB_SET_FORMAT | format);
	codec_query (_ihd_audio.output->codec, 4, VERB_SET_FORMAT | format);
	codec_query (_ihd_audio.output->codec, 5, VERB_SET_FORMAT | format);
	codec_query (_ihd_audio.output->codec, 6, VERB_SET_FORMAT | format);

	codec_query (_ihd_audio.output->codec, 2, VERB_SET_STREAM_CHANNEL | 0x10);
	codec_query (_ihd_audio.output->codec, 3, VERB_SET_STREAM_CHANNEL | 0x10);
	codec_query (_ihd_audio.output->codec, 4, VERB_SET_STREAM_CHANNEL | 0x10);
	codec_query (_ihd_audio.output->codec, 5, VERB_SET_STREAM_CHANNEL | 0x10);
	codec_query (_ihd_audio.output->codec, 6, VERB_SET_STREAM_CHANNEL | 0x10);

    uint32_t stream = codec_query (_ihd_audio.output->codec, _ihd_audio.output->nid, 0xF0600);

	_ihd_audio.output->sample_rate = SR_48_KHZ;
	_ihd_audio.output->num_channels = 2;


	uint32_t eapd_btl1 = codec_query (_ihd_audio.output->codec, 2, VERB_GET_EAPD_BTL);	
	codec_query (_ihd_audio.output->codec, 2,VERB_SET_EAPD_BTL |eapd_btl1 | 0x2);
	uint32_t eapd_btl2 = codec_query (_ihd_audio.output->codec, 3, VERB_GET_EAPD_BTL);	
	codec_query (_ihd_audio.output->codec, 3,VERB_SET_EAPD_BTL |eapd_btl2 | 0x2);
	uint32_t eapd_btl3 = codec_query (_ihd_audio.output->codec, 4, VERB_GET_EAPD_BTL);	
	codec_query (_ihd_audio.output->codec, 4,VERB_SET_EAPD_BTL |eapd_btl3 | 0x2);
	uint32_t eapd_btl4 = codec_query (_ihd_audio.output->codec, 5, VERB_GET_EAPD_BTL);	
	codec_query (_ihd_audio.output->codec, 5,VERB_SET_EAPD_BTL |eapd_btl4 | 0x2);
	uint32_t eapd_btl5 = codec_query (_ihd_audio.output->codec, 6, VERB_GET_EAPD_BTL);	
	codec_query (_ihd_audio.output->codec, 6,VERB_SET_EAPD_BTL |eapd_btl5 | 0x2);

	//!Set Pin control : enable the output bit
	uint32_t ctl = codec_query(_ihd_audio.output->codec, _ihd_audio.output->nid, VERB_GET_PIN_CONTROL);
	ctl |= (1<<6);
	ctl |= (1<<7);

	codec_query (_ihd_audio.output->codec, 2, VERB_SET_PIN_CONTROL | 0xc0);
	codec_query (_ihd_audio.output->codec, 3, VERB_SET_PIN_CONTROL | 0xc0);
	codec_query (_ihd_audio.output->codec, 4, VERB_SET_PIN_CONTROL | 0xc0);
	codec_query (_ihd_audio.output->codec, 5, VERB_SET_PIN_CONTROL | 0xc0);
	codec_query (_ihd_audio.output->codec, 6, VERB_SET_PIN_CONTROL | 0xc0);

}



/**
 *  Initializes widgets for a codec and node
 *  @param codec-> codec id
 *  @param nid --> node id
 */
void widget_init (int codec, int nid) {

	uint32_t widget_cap;
	uint32_t type;
	uint32_t amp_cap;
	uint32_t eapd_btl;

	//! send a command for audio widget capabilites
	widget_cap = codec_query (codec, nid, VERB_GET_PARAMETER | PARAM_AUDIO_WID_CAP);
	if (widget_cap == 0) {
		//! serious problem occured
		return;
	}

	type = (widget_cap & WIDGET_CAP_TYPE_MASK) >> WIDGET_CAP_TYPE_SHIFT;
	amp_cap = codec_query (codec, nid, VERB_GET_PARAMETER | PARAM_OUT_AMP_CAP);
	eapd_btl = codec_query (codec, nid, VERB_GET_EAPD_BTL);

	if (widget_cap & WIDGET_CAP_POWER_CNTRL) {
		codec_query(codec, nid, VERB_SET_POWER_STATE | 0x0);
	}

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

	eapd_btl = codec_query (codec, nid, VERB_GET_EAPD_BTL);	
	
	switch (type) {
	case WIDGET_OUTPUT:{
		if (!_ihd_audio.output->nid) {
			_ihd_audio.output->codec = codec;
			_ihd_audio.output->nid = nid;
			_ihd_audio.output->amp_gain_steps = (amp_cap >> 8) & 0x7f;
		}

		uint32_t eapd_ = codec_query (codec,nid, VERB_GET_EAPD_BTL);	
		codec_query (codec, nid,VERB_SET_EAPD_BTL | eapd_ | 0x2);
		break;
		}
	default:
		return;

	}

	
}

//! Enumerate through the codec for available widgets
static int codec_enumerate_widgets(int codec) {

	uint32_t param;
	int num_fg, num_widgets;
	int fg_start, widgets_start;
	int i, j;


	param = codec_query (codec, 0, VERB_GET_PARAMETER | PARAM_NODE_COUNT);

	num_fg = param & 0x000000ff;
	fg_start = (param & 0x00ff0000) >> 16;


	printf ("[HD_Audio]: Num Function Group -> %d, fg_start -> %d\n", num_fg, fg_start);

	uint32_t vendor_id = codec_query (codec, 0, VERB_GET_PARAMETER | PARAM_VENDOR_ID);
	printf ("[HD-Audio]:Widget device id -> %x, vendor id -> %x\n", vendor_id & 0xffff , (vendor_id >> 16 ));
	
	uint32_t rev_id = codec_query (codec, 0, VERB_GET_PARAMETER | PARAM_REV_ID);
	printf ("[HD-Audio]:Widget version -> %d.%d, r0%d\n", rev_id>>20, rev_id>>16, rev_id>>8);

	
	for (i = 0; i < num_fg; i++) {

		param = codec_query (codec, fg_start + i, 
			VERB_GET_PARAMETER | PARAM_NODE_COUNT);

		num_widgets = param & 0xff;
		widgets_start = (param >> 16) & 0xff;
		printf ("Widget start -> %d, num widhets -> %d\n", widgets_start, num_widgets);
		
		param = codec_query (codec, fg_start + i, VERB_GET_PARAMETER | PARAM_FN_GROUP_TYPE);
		param &= 0x000000ff;
		if (param != FN_GROUP_AUDIO) {
			printf ("FG not audio group\n");
			continue;
		}

		//codec_query (codec, fg_start + i, VERB_SET_POWER_STATE | 0x0);

		for (int j = 0; j < num_widgets; j++) {
			widget_init (codec, widgets_start + j);
		}
		
	}


	return _ihd_audio.output->nid ? 0 : -1;
}


//! Reset the HD Audio Controller
void hda_reset() {
	_aud_outl_(CORBCTL, 0);
	_aud_outl_(RIRBCTL, 0);
	_aud_outw_(RIRBWP, 0);
	while ((_aud_inl_(CORBCTL) & CORBCTL_CORBRUN) ||
		(_aud_inl_(RIRBCTL) & RIRBCTL_RIRBRUN));

	_aud_outl_(GCTL, 0);
	while ((_aud_inl_(GCTL) & GCTL_RESET));

	_aud_outl_ (GCTL, GCTL_RESET);
	while ((_aud_inl_(GCTL) & GCTL_RESET) == 0);

	_aud_outw_(WAKEEN, 0xffff);
	_aud_outl_(INTCTL,0x800000ff);
	setup_corb();
	setup_rirb();
}

//! Start Output
void hda_output_start () {
	//_aud_outb_(REG_O0_STS(_ihd_audio), (1<<2) | (1<<3) | (1<<4));

	uint32_t value = _aud_inl_(REG_O0_CTLL(_ihd_audio));
	value |= 0x4;
	value |= 0x2;
    _aud_outw_(REG_O0_CTLL(_ihd_audio),value);
}

//! Stop Output
void hda_output_stop () {
	uint32_t value = _aud_inl_(REG_O0_CTLL(_ihd_audio));
	_aud_outw_ (REG_O0_CTLL(_ihd_audio),0);
}

/**
 * Initialize the HD Audio Controller
 */
void hda_initialize () {
	pci_device_info pci_dev;
	int bus, dev, func;

	if (!pci_find_device_class (0x04, 0x03, &pci_dev, &bus, &dev, &func)){
		printf ("No HD-Audio was found\n");
		return;
	}

	uint16_t command = 0;
	read_config_16 (0,bus,dev,func,0x4,&command);
	if (((command >> 10) & 0xff) != 0) {
		printf ("[HD-Audio]: Interrupt disabled in PCI Config_Space %x\n", command);
	}

	command |= 0<<10;
	command |= 0x2;
	write_config_16 (0,bus,dev,func, 0x4,command);

	uint16_t command2 = 0;
	read_config_16 (0,bus,dev,func,0x4,&command2);


	_ihd_audio.output = (hda_output*)pmmngr_alloc();
	_ihd_audio.vol = (hda_volume*)pmmngr_alloc();
	memset (_ihd_audio.output, 0, 4096);


	bool pci_status = pci_alloc_msi (func, dev, bus, hda_handler);
	if (pci_status) 
		printf ("[HD-Audio]: Supports MSI\n");
	if (!pci_status) {
		interrupt_set (11, hda_handler,11);
	}


	_ihd_audio.mmio = pci_dev.device.nonBridge.baseAddress[0] & ~3;
	_ihd_audio.corb = (uint32_t*)pmmngr_alloc(); 
	_ihd_audio.rirb = (uint64_t*)pmmngr_alloc(); 
	memset (_ihd_audio.corb, 0, 4096);
	memset (_ihd_audio.rirb, 0, 4096);


	//! Allocate the main audio buffer area
	//! for now, only allocate 1MB of area, at a fixed location
	uint64_t pos = 0xFFFFE00000100000;
	for (int i = 0; i < 16*0x10000 / 4096; i++) {
		map_page ((uint64_t)pmmngr_alloc(),pos + i * 4096, 0);
	}

	_ihd_audio.buffer = (uint64_t*)0xFFFFE00000100000;
	memset (_ihd_audio.buffer, 0, 16*0x10000);


	if (_aud_inw_ (GCAP) & 1) {
		printf ("HD-Audio 64-OK\n");
	}


	hda_reset();

     uint16_t gcap = _aud_inw_(GCAP);
	_ihd_audio.num_oss = HDA_GCAP_OSS(gcap);
	_ihd_audio.num_iss = HDA_GCAP_ISS(gcap);
	_ihd_audio.stream_0_x = 0x80 + (_ihd_audio.num_iss * 0x20);
	_ihd_audio.stream_0_y = 0x80 + (_ihd_audio.num_iss * 0x20) + (_ihd_audio.num_oss * 0x20);
	

	uint16_t statests = _aud_inw_ (STATESTS);
	for (int i = 0; i < 15; i++) {
		if (statests & (1 >> i)){
			if (codec_enumerate_widgets(i)) {
				break;
			}
		}
	} 
	
	hda_init_output();
	hda_init_output_stream();
	
	printf ("IHD-Audio Initialized successfully\n");


}


//! Transfer PCM Audio Data to internal buffer of HD-Audio
void hda_audio_add_pcm (unsigned char *data, uint32_t length) {
	memcpy (_ihd_audio.buffer, data,length);
}

//! Finally play the audio
void hda_audio_play () {
	hda_output_start();
	hda_set_volume (119); //mute
}