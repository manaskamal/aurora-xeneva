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
#include <stdio.h>
#include <serial.h>

int last_arr = 0;

int widget_dump_connection (int codec, int nid) {
	uint32_t num_conn = 0;
	uint32_t sel;
	int i;
	uint32_t conn_val;
	int ret_nid;
	num_conn = codec_query(codec, nid, VERB_GET_PARAMETER | PARAM_CONN_LIST_LEN);


	for (int i = 0; i < (num_conn & 0x7f); i++) {
		uint32_t conn = 0;
		bool range;
		int idx, shift;

		if (num_conn & 0x80){
			idx = i & ~3;
			shift = 8 * (i & 3);
		}else {
			idx = i & ~1;
			shift = 8 * (i & 1);
		}

		conn = codec_query(codec, nid, VERB_GET_CONN_LIST | idx);
		conn >>= shift;
		
		if (num_conn & 0x80) {
			/* Use long form list entry */
			range = conn & 0x8000;
			conn  &= 0x7fff;
		}else {
			/* Use short form list entry*/
			range = conn & 0x80;
			conn &= 0x7f;	
			_debug_print_ (" %d ", conn);
			ret_nid = conn;
	
			/* TODO: Create separate list of volume controls to store this
			 * line out nodes, to control the volume, NOTE: this is only for
			 * line out pins, not for speaker pins
			 */
			codec_query(codec, ret_nid, VERB_SET_AMP_GAIN_MUTE | 0xb000 | 127);
		
		}
	}

	/* make the 0th index entry active */
	codec_query(codec, nid, VERB_SET_CONN_SELECT | 0);
	sel = codec_query(codec, nid, VERB_GET_CONN_SELECT);
	//printf ("[current: %d] \n", sel);
	return ret_nid;
}


bool pin_dump_default_device (int codec, int nid) {
	bool value = false;

	uint32_t val = codec_query(codec, nid,VERB_GET_PARAMETER | VERB_GET_CONFIG_DEFAULT);

	uint16_t port = (val >> 30) & 0xf;
	uint8_t location = (val >> 24) & 0xff;
	
	/*switch(port) {
	case 0:
		printf ("Port Connectivity is a jack \n");
		break;
	case 1:
		printf ("Port Connectivity -- No Phys conn \n");
		break;
	case 2:
		printf ("Port Connectivity -- Integrated Device \n");
		break;
	case 3:
		printf ("Port Connectivity -- both jack and internal dev \n");
		break;
	}
*/
	/*if ((location & 0xf) == 0) {
		printf ("Location N/A \n");
	}else if ((location & 0xf) == 0x1) {
		printf ("Location Rear \n");
	}else if ((location & 0xf) == 0x2) {
		printf ("Location Front \n");
	}else if ((location & 0xf) == 0x3) {
		printf ("Location Left \n");
	}else if ((location & 0xf) == 0x4) {
		printf ("Location Right \n");
	}else if ((location & 0xf) == 0x5) {
		printf ("Location Top \n");
	}else if ((location & 0xf) == 0x6) {
		printf ("Location Bottom \n");
	}else if ((location & 0xf) == 0x7) {
		printf ("Location Special \n");
	}*/

	uint8_t default_dev = (val >> 20) & 0xf;
	switch(default_dev) {
	case 0:
		printf ("Line Out \n");
		value = true;
		break;
	case 1:
		printf ("Speaker \n");
		value = true;
		break;
	case 2:
		//printf ("HP Out \n");
		break;
	case 3:
		//printf ("CD \n");
		break;
	case 4:
		//printf ("SPDIF Out \n");
		break;
	case 5:
		//printf ("Digital Other Out \n");
		break;
	case 6:
		//printf ("Modem Line Side \n");
		break;
	case 7:
		//printf ("Modem Handset Side \n");
		break;
	case 8:
		//printf ("Line In \n");
		break;
	case 9:
		//printf ("AUX \n");
		break;
	case 10:
		//printf ("Mic In \n");
		break;
	case 11:
		//printf ("Telephony \n");
		break;
	case 12:
		//printf ("SPDIF In \n");
		break;
	case 13:
		//printf ("Digital Other In \n");
		break;
	}

	return value;
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
		codec_query(codec, nid, VERB_SET_POWER_STATE | 0x00000);
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

	amp_gain = codec_query(codec, nid, VERB_GET_AMP_GAIN_MUTE | ((1<<15) | (1<<13)));
	amp_gain |= codec_query(codec, nid, VERB_GET_AMP_GAIN_MUTE | ((1<<15) | (0<<13)));

	eapd_btl = codec_query (codec, nid, VERB_GET_EAPD_BTL);	
	
	
	switch (type) {
	case WIDGET_PIN:{
		uint32_t pin_cap, ctl = 0;
		uint32_t sel = 0;

		pin_cap = codec_query(codec, nid, VERB_GET_PARAMETER | PARAM_PIN_CAP);
		if ((pin_cap & PIN_CAP_OUTPUT) == 0)
			return;

		/* Set the pin controls */
		ctl = codec_query(codec, nid, VERB_GET_PIN_CONTROL);
		ctl |= (1<<7);
		ctl |= PIN_CTL_ENABLE_OUTPUT;
		ctl |= (1<<5);
		codec_query(codec, nid, VERB_SET_PIN_CONTROL | ctl);

		
		codec_query(codec, nid, VERB_SET_EAPD_BTL | (1<<2) | (1<<1) | (1<<0));

		/* now check the pin for attached device (speaker, line out, line in)
		 * and its port connectivity (jack, integrated device,...etc) 
		 */
		if (pin_dump_default_device(codec, nid)) {
			int ret_nid = widget_dump_connection(codec, nid);
		}
		
		break;
	}
	case WIDGET_OUTPUT:{
		//_debug_print_ ("Output Node -> %d \r\n", nid);
		//hda_get_supported_stream_format(codec, nid);
		/* here we should create a list of output codec and nodes */

		/* WIDGET_OUTPUT -- contains all the DACs that needed to 
		 * configured to use specific output stream, NOTE that this DACs
		 * are further part of any lineout or speaker pins, after
		 * configuring each DACs, pins are needed to configured */
		hda_set_output_nid(nid,codec,0);
		break;
		}

	case WIDGET_INPUT:{
		//_debug_print_ ("Input nid -> %d \r\n", nid);
		/* Not Implemented */
		break;
	}

	case WIDGET_VOLUME_KNOB:{

		/* Not implemented fully */
		_debug_print_ ("Volume knob widget found \r\n", nid);

		codec_query(codec, nid, 0x70f00 | (1<<7) | 100);
	
		uint32_t volume = codec_query(codec, nid, VERB_GET_PARAMETER | 0xF0F00);
		_debug_print_ ("Volume is direct -> %d, Volume -> %d \r\n", ((volume >> 7) & 0xff), 
			(volume & 0xff));
		break;
	}
	default:
		return;

	}	
}


