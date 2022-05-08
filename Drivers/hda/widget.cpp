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
		/* here we should create a list of output codec and nodes */
		hda_set_output_nid(nid, codec, (amp_cap >> 8) & 0x7f);

		uint32_t eapd_ = codec_query (codec,nid, VERB_GET_EAPD_BTL);	
		codec_query (codec, nid,VERB_SET_EAPD_BTL | eapd_ | 0x2);
		break;
		}
	default:
		return;

	}	
}

void widget_init_output (uint8_t codec, uint16_t nid) {

	/* first output channel is 0x10 */
	codec_query(codec, nid,VERB_SET_STREAM_CHANNEL | 0x10);
	uint16_t format = BITS_16 | SR_48_KHZ | 2 - 1;
	codec_query(codec, nid,VERB_SET_FORMAT | format);
	_aud_outl_(REG_O0_FMT, format);
}

