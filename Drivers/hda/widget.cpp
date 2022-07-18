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
#include "widget.h"
#include <arch\x86_64\mmngr\kheap.h>

int last_arr = 0;
bool __mixer = false;
int widget_dump_connection (int codec, int nid, hda_audio_path_t *path);


/*
 * hda_create_widget -- creates a hd audio widget
 */
hda_widget_t *hda_create_widget () {
	hda_widget_t* wid = (hda_widget_t*)malloc(sizeof(hda_widget_t));
	memset(wid, 0, sizeof(hda_widget_t));
	return wid;
}

hda_audio_path_t* hda_create_audio_path() {
	hda_audio_path_t* p = (hda_audio_path_t*)malloc(sizeof(hda_audio_path_t));
	memset(p, 0, sizeof(hda_audio_path_t));
	return p;
}

void widget_setup_pin (int codec, int nid) {

	/* Set the pin controls */
	uint32_t ctl = codec_query(codec, nid, VERB_GET_PIN_CONTROL);
	ctl |= PIN_CTL_ENABLE_HPHN;
	ctl |= PIN_CTL_ENABLE_OUTPUT;
	codec_query(codec, nid, VERB_SET_PIN_CONTROL | ctl);

		
	//codec_query(codec, nid, VERB_SET_EAPD_BTL | (1<<2) | (1<<1) | (1<<0));

	/* now check the pin for attached device (speaker, line out, line in)
	 * and its port connectivity (jack, integrated device,...etc) 
	 */
}


void widget_parse_mixer (int codec, int nid, int pin_nid, hda_audio_path_t *p) {
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
			//_debug_print_ ("  %d ", conn);
			ret_nid = conn;
			uint32_t resp = codec_query(codec, ret_nid, VERB_GET_PARAMETER | PARAM_AUDIO_WID_CAP);
			uint8_t type = (resp >> 20) & 0xf;

			if (type == 0) {
				//_debug_print_ (" [Out Conv] ");
				/* Output Converter */
				hda_widget_t *output_conv = hda_create_widget();
				output_conv->codec = codec;
				output_conv->nid = ret_nid;
				output_conv->parent_mixer_nid = nid;
				output_conv->parent_pin_nid = pin_nid;

				if (((resp >> 2) & 0xf) != 0)
					output_conv->amp_cap = true;
				if (((resp >> 10) & 0xf) != 0)
					output_conv->power_cap = true;

				output_conv->conn_list_length = 0;
				output_conv->eapd_btl = true;
				output_conv->pcm_rates = hda_get_pcm_rates(codec, ret_nid);
				output_conv->pcm_format = hda_get_supported_stream_format(codec, ret_nid);
				output_conv->type = HDA_WIDGET_TYPE_DAC;
				//hda_add_widget(output_conv);

				if (p->root) {
					p->last->next = output_conv;
					output_conv->prev = p->last;
					output_conv->next = NULL;
					p->last = output_conv;
				}
			}
		}

		
	}
	
	/* make the 0th index entry active */
	codec_query(codec, nid, VERB_SET_CONN_SELECT | 0);
	sel = codec_query(codec, nid, VERB_GET_CONN_SELECT);
//	printf ("  [current: %d] \n", sel);
}


int widget_dump_connection (int codec, int nid, hda_audio_path_t *path) {
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
			//printf ("Long form conn -> %d ", conn);
		}else {
			/* Use short form list entry*/
			range = conn & 0x80;
			conn &= 0xff;	
			ret_nid = conn;
			//printf (" %d ", ret_nid);
			uint32_t resp = codec_query(codec, ret_nid,VERB_GET_PARAMETER | PARAM_AUDIO_WID_CAP);
			uint8_t type = (resp >> 20) & 0xf;
			if (type == 0x00) {
				//printf (" OUT CONV ");
				hda_widget_t *output_conv = hda_create_widget();
				output_conv->codec = codec;
				output_conv->nid = ret_nid;
				output_conv->parent_pin_nid = nid;
				output_conv->parent_mixer_nid = 0;
				if (((resp >> 2) & 0xf) != 0)
					output_conv->amp_cap = true;
				if (((resp >> 10) & 0xf) != 0)
					output_conv->power_cap = true;

				output_conv->conn_list_length = 0;
				output_conv->eapd_btl = true;
				output_conv->pcm_rates = hda_get_pcm_rates(codec, ret_nid);
				output_conv->pcm_format = hda_get_supported_stream_format(codec, ret_nid);
				output_conv->type = HDA_WIDGET_TYPE_DAC;
				//hda_add_widget(output_conv);

				if (path->root) {
					path->last->next = output_conv;
					output_conv->prev = path->last;
					output_conv->next = NULL;
					path->last = output_conv;
				}

			}if (type == 0x02) {
				//_debug_print_ (" [MIXER] \r\n");
				hda_widget_t *mixer = hda_create_widget();
				mixer->codec = codec;
				mixer->nid = ret_nid;
				mixer->parent_pin_nid = nid;
				mixer->parent_mixer_nid = 0;
				uint32_t conn_length = codec_query(codec, ret_nid,VERB_GET_PARAMETER | PARAM_CONN_LIST_LEN);
				mixer->conn_list_length = conn_length & 0x7f;
				mixer->eapd_btl = true;
				mixer->mute = true;
				mixer->amp_cap = true;
				mixer->pcm_format = 0;
				mixer->pcm_rates = 0;
				uint32_t mixer_cap = codec_query(codec, ret_nid, VERB_GET_PARAMETER | PARAM_AUDIO_WID_CAP);
				if (((mixer_cap >> 10) & 0xf) != 0)
					mixer->power_cap = true;
				mixer->type = HDA_WIDGET_TYPE_MIXER;
				//hda_add_widget(mixer);
				
				if (path->root) {
					path->last->next = mixer;
					mixer->prev = path->last;
					mixer->next = NULL;
					path->last = mixer;
				}

				widget_parse_mixer(codec, ret_nid, nid, path);
				 
				
			}
			if(type == 0x4) {/* Pin */
				//printf ("Pin Inside Line Out nid -> %d \n", ret_nid);
			}

			/* TODO: Create separate list of volume controls to store this
			 * line out nodes, to control the volume, NOTE: this is only for
			 * line out pins, not for speaker pins
			 */

		}
	}
	
	/* make the 0th index entry active */
	codec_query(codec, nid, VERB_SET_CONN_SELECT | 0);
	sel = codec_query(codec, nid, VERB_GET_CONN_SELECT);
	//printf ("  [current: %d] \n", sel);
	return ret_nid;
}


bool pin_dump_default_device (int codec, int nid) {
	bool value = false;

	uint32_t val = codec_query(codec, nid,VERB_GET_PARAMETER | VERB_GET_CONFIG_DEFAULT);

	uint8_t port = (val >> 30) & 0xf;
	uint8_t location = (val >> 24) & 0xff;
	bool port_conn = false;
	switch(port) {
	case 0:
	//	printf ("Port Connectivity is a jack \n");
		port_conn = true;
		break;
	case 1:
		//printf ("Port Connectivity -- No Phys conn \n");
		break;
	case 2:
		//printf ("Port Connectivity -- Integrated Device \n");
		port_conn = true;
		break;
	case 3:
		//printf ("Port Connectivity -- both jack and internal dev \n");
		port_conn = true;
		break;
	}

	/*uint8_t conn = ((val >>16) & 0xf);
	switch(conn) {
	case 0:
		printf ("Unknown \n");
		break;
	case 1:
		printf ("1/8 stereo/mono\n");
		break;
	case 2:
		printf ("1/4 stereo/mono \n");
		break;
	case 3:
		printf ("ATAPI internal \n");
		break;
	case 4:
		printf ("RCA \n");
		break;
	case 5:
		printf ("Optical \n");
		break;
	case 6:
		printf ("Other digital \n");
		break;
	case 7:
		printf ("Other analog \n");
		break;
	case 8:
		printf ("Multichannel Analog (DIN) \n");
		break;
	case 9:
		printf ("XLR/Professional \n");
		break;
	case 10:
		printf ("RJ-11(Modem)\n");
		break;
	case 11:
		printf("Combination \n");
		break;
	case 15:
		printf ("Other \n");
		break;
	}*/

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
		//printf ("Line Out nid -> %d \n", nid);
		if (port_conn)
			value = true;
		break;
	case 1:
		//printf ("Speaker nid -> %d \n", nid);
		value = true;
		break;
	case 2:
		printf ("HP Out \n");
		value = true;
		break;
	case 3:
		printf ("CD \n");
		break;
	case 4:
		printf ("\n SPDIF Out \n");
		value = true;
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
		printf ("Line In \n");
	/*	if (port_conn)
			value = true;*/
		break;
	case 9:
		//printf ("AUX \n");
		break;
	case 10:
		printf ("Mic In \n");
	/*	if (port_conn)
			value = true;*/
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
		//_debug_print_ ("Pin Complex nid -> 0x%x \r\n", nid);
		pin_cap = codec_query(codec, nid, VERB_GET_PARAMETER | PARAM_PIN_CAP);
		
		if ((pin_cap & PIN_CAP_OUTPUT) == 0)
			return;

		
		/* now check the pin for attached device (speaker, line out, line in)
		 * and its port connectivity (jack, integrated device,...etc) 
		 */
		if (pin_dump_default_device(codec, nid)) {
			hda_audio_path_t *path = hda_create_audio_path();
			hda_widget_t *pin = hda_create_widget();
			pin->type = HDA_WIDGET_TYPE_PIN;
			pin->codec = codec;
			pin->nid = nid;
			pin->parent_pin_nid = 0;
			pin->parent_mixer_nid = 0;
			path->root = pin;
			path->last = path->root;
			hda_add_path(path);
			int ret_nid = widget_dump_connection(codec, nid, path);
		}
		
		break;
	}
	case WIDGET_OUTPUT:{
		_debug_print_ ("Output Node -> %d \r\n", nid);
		//hda_get_supported_stream_format(codec, nid);
		/* here we should create a list of output codec and nodes */
		/* WIDGET_OUTPUT -- contains all the DACs that needed to 
		 * configured to use specific output stream, NOTE that this DACs
		 * are further part of any lineout or speaker pins, after
		 * configuring each DACs, pins are needed to configured */
		
		break;
		}

	case WIDGET_INPUT:{
		//_debug_print_ ("Input nid -> %d \r\n", nid);
		/* Not Implemented */
		break;
	}

	case WIDGET_BEEP_GEN:
		printf ("Beep Gen widget \r\n");
		break;
	case WIDGET_POWER :
		printf ("PowerWidget \r\n");
		break;

	case WIDGET_MIXER:
		//codec_query(codec, nid, VERB_SET_POWER_STATE | 0x00000);
		//codec_query(codec, nid, VERB_SET_AMP_GAIN_MUTE | 0xb000 | 127);
		break;

	case WIDGET_VENDOR_DEFINED:
		break;

	case WIDGET_SELECTOR:
		/*codec_query(codec, nid,VERB_SET_POWER_STATE | 0x00000);
		codec_query(codec,nid, VERB_SET_AMP_GAIN_MUTE | 0xb000 | 127);*/
		break;
	

	case WIDGET_VOLUME_KNOB:{

		/* Not implemented fully */
		_debug_print_ ("Volume knob widget found \r\n", nid);
		break;
	}
	default:
		return;

	}

}


