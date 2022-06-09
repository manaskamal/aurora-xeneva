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

void widget_dump_connection (int codec, int nid) {
	uint32_t num_conn;
	uint32_t sel;
	int i;
	uint32_t conn_val;
	num_conn = codec_query(codec, nid, VERB_GET_PARAMETER | PARAM_CONN_LIST_LEN);

	printf ("Num Connection -> %d Long Form -> %d \n", num_conn, (num_conn & 0x80));

	for (int i = 0; i < (num_conn & 0x7f); i++) {
		uint32_t conn;
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
			printf ("%d ",conn);
		}

	
	}

	sel = codec_query(codec, nid, VERB_GET_CONN_SELECT);
	printf (" [current: %d]\n", sel);
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
		for (int i = 0; i < 100000; i++)
			;
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
		uint32_t pin_cap, ctl;
		pin_cap = codec_query(codec, nid, VERB_GET_PARAMETER | PARAM_PIN_CAP);
		if ((pin_cap & PIN_CAP_OUTPUT) == 0 || (pin_cap & PIN_CAP_INPUT) == 0) 
			return;

		ctl = codec_query(codec, nid, VERB_GET_PIN_CONTROL);
		ctl |= PIN_CTL_ENABLE_OUTPUT;
		ctl |= (1<<5); //enable input
		codec_query(codec, nid, VERB_SET_PIN_CONTROL | ctl);
		//printf ("pin complex - con length %d \n", (widget_cap >> 8 & 0xff));
		//widget_dump_connection(codec, nid);
		codec_query(codec, nid, VERB_SET_EAPD_BTL | (1<<1) | (1<<2));
		break;
	}
	case WIDGET_OUTPUT:{
		/* here we should create a list of output codec and nodes */
		uint8_t mute_val = (amp_cap >> 7) & 0xff;
		uint8_t gain_val = amp_cap & 0xff;
		hda_set_output_nid(nid, codec, gain_val);
		break;
		}

	case WIDGET_INPUT:{
		codec_query(codec, nid,VERB_SET_STREAM_CHANNEL | (1<<4));
		uint16_t format =   (1<<15) | SR_44_KHZ | (0<<11) | (0 << 8) | BITS_16 | 1;
		codec_query(codec, nid,VERB_SET_FORMAT | format);
		codec_query(codec, nid, VERB_SET_CONV_CHANNEL_COUNT | 1);
		codec_query(codec, nid, VERB_SET_EAPD_BTL | (1<<1) | (1<<2));
		break;
					  }
	default:
		return;

	}	
}


