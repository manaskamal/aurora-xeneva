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
#include "codecs\sigmatel.h"
#include <serial.h>

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
	return response  & 0xffffffff;
}


/*
 * hda_get_pcm_rates -- collects supported PCM Size / rates 
 * @param codec -- destination codec
 * @param nid -- desired node id
 */
uint32_t hda_get_pcm_rates (int codec, int nid) {
	uint32_t pcm_rates = 0;
	pcm_rates = codec_query(codec, nid, VERB_GET_PARAMETER | 0x0A);
#ifdef _HDA_DEBUG_
	if ((pcm_rates & (1<<0)) != 0) {
		printf ("Supported 8.0 kHZ, Mult/Div-> 1/6 * 48 \n");
	}
	if ((pcm_rates & (1<<1)) != 0) {
		printf ("Supported 11.025 kHZ, Mult/Div -> 1/4 * 44.1 \n");
	}
	if ((pcm_rates & (1<<2)) != 0) {
		printf ("Suported 16.0 kHZ, Mult/Div -> 1/3 * 48 \n");
	}
	if ((pcm_rates & (1<<3)) != 0) {
		printf ("Supported 22.05 kHZ, Mult/Div -> 1/2*44.1\n");
	}
	if ((pcm_rates & (1<<4)) != 0) {
		printf ("Supported 32.0 kHZ, Mult/Div -> 2/3*48 \n");
	}
	if ((pcm_rates & (1<<5)) != 0) {
		printf ("Supported 44.1 kHZ, Mult/Div -> 0 \n");
	}
	if ((pcm_rates & (1<<6)) != 0) {
		printf ("Supported 48.0 kHZ, Mult/Div -> 0 \n");
	}
	if ((pcm_rates & (1<<7)) != 0) {
		printf ("Supported 88.2 kHZ, Mult/Div -> 2/1*44.1 \n");
	}
	if ((pcm_rates & (1<<8)) != 0) {
		printf ("Supported 96.0 kHZ, Mult/Div -> 2/1*48 \n");
	}
	if ((pcm_rates & (1<<9)) != 0) {
		printf ("Supported 176.4 kHZ, Mult/Div -> 4/1 * 44.1 \n");
	}
	if ((pcm_rates & (1<<10)) != 0) {
		printf ("Supported 192.0 kHZ, Mult/Div -> 4/1 * 48 \n");
	}else if ((pcm_rates & (1<<11)) != 0) {
		printf ("Supported 384 kHZ, Mult/Div -> 8/1 * 48 \n");
	}

	if ((pcm_rates & (1<<16)) != 0) {
		printf ("8 bit audio formats are supported \n");
	}
	if ((pcm_rates & (1<<17)) != 0) {
		printf ("16 bit audio formats are supported \n");
	}
	if ((pcm_rates & (1<<18)) != 0) {
		printf ("20 bit audio formats are supported \n");
	}
	if ((pcm_rates & (1<<19)) != 0) {
		printf ("24 bit audio formats are supported \n");
	}
	if ((pcm_rates & (1<<20)) != 0) {
		printf ("32 bit audio formats are supported \n");
	}
#endif
	return pcm_rates;
}

/*
 * hda_get_supported_stream_format -- returns the supported 
 * stream format
 * @param codec -- codec id
 * @param nid -- node id
 */
uint32_t hda_get_supported_stream_format (int codec, int nid) {
	uint32_t format = 0;
	format = codec_query(codec, nid, VERB_GET_PARAMETER | 0x0B);
#ifdef _HDA_DEBUG_
	if ((format & (1<<0)) != 0) {
		printf ("PCM is supported \n");
	}

	if ((format & (1<<1)) != 0) {
		printf ("Float32 audio is supported \n");
	}

	if ((format & (1<<2)) != 0) {
		printf ("Dolby AC-3 audio is supported \n");
	}
#endif
	return format;
}

/*
 * hda_enable_unsol -- enables unsolicited response for 
 * nodes, unsolicited response are responses send by
 * widgets to controller and finally reach the 
 * hda_interrupt_handler
 * @param codec -- codec id
 * @param nid -- node id
 */
void hda_enable_unsol (int codec, int nid) {
	/* enable unsol for this codec */
	codec_query (codec, nid,0x70800 | (1<<7) | nid); 
}

/*
 * hda_get_unsol_node -- returns the node id of
 * given unsolicited response
 * @return node_id
 */
int hda_get_unsol_node (uint32_t resp) {
	return (resp & 0xf);
}


/*
 * codec_enumerate_widgets -- enumerate every widgets
 */
int codec_enumerate_widgets(int codec) {

	uint32_t param;
	int num_fg, num_widgets;
	int fg_start, widgets_start;
	int i, j;


	param = codec_query (codec, 0, VERB_GET_PARAMETER | PARAM_NODE_COUNT);

	num_fg = param & 0x000000ff;
	fg_start = (param >> 16) & 0xff;
	param = 0;

	printf ("[driver]: hdaudio num function group -> %d, fg_start -> %d\n", num_fg, fg_start);

	uint32_t vendor_id = codec_query (codec, 0, VERB_GET_PARAMETER | PARAM_VENDOR_ID);
	uint32_t devid = vendor_id & 0xffff;
	uint32_t vendid = vendor_id >> 16;

	/*register function pointers */
	if (devid == 0x7680 && vendid == 0x8384) {  
		/* Sigmatel Codec */
		hda_set_codec_init_func(sigmatel_init);
		hda_set_volume_func(sigmatel_set_volume);
		printf ("[hda]: sigmatel codec registered \n");
	}

	printf ("[driver]: hdaudio widget device id -> 0x%x, vendor id -> 0x%x\n", devid , vendid);
	
	uint32_t rev_id = codec_query (codec, 0, VERB_GET_PARAMETER | PARAM_REV_ID);
	printf ("[driver]: widget version -> %d.%d, r0%d\n", rev_id>>20, rev_id>>16, rev_id>>8);

	
	for (i = 0; i < num_fg; i++) {

		param = codec_query (codec, fg_start + i, 
			VERB_GET_PARAMETER | PARAM_NODE_COUNT);

		num_widgets = param & 0xff;
		widgets_start = (param >> 16) & 0xff;
		printf ("Widget start -> %d, num widgets -> %d\n", widgets_start, num_widgets);
		
		param = codec_query (codec, fg_start + i, VERB_GET_PARAMETER | PARAM_FN_GROUP_TYPE);
		param &= 0x000000ff;
		if (param != FN_GROUP_AUDIO) {
			printf ("FG not audio group\n");
			continue;
		}

		codec_query(codec, fg_start + i, 0x7FF00);
		for (int i = 0; i < 100000; i++)
			;
		codec_query(codec, fg_start + i, 0x7FF00);
		for (int i = 0; i < 100000; i++)
			;

		codec_query (codec, fg_start + i, VERB_SET_POWER_STATE | 0x00000);

		uint32_t amp_param = 0;
		amp_param = codec_query(codec, fg_start + i, VERB_GET_PARAMETER | 0x12000);
		printf ("Step Size -----> %d NumStep -> %d \n", ((amp_param >> 31) & 0xff), ((amp_param >> 8)&0xff));


	//	hda_get_pcm_rates (codec, fg_start + i);
	//	hda_get_supported_stream_format(codec, fg_start + i);

		for (int j = 0; j < num_widgets; j++) {
			widget_init (codec, widgets_start + j);
		}
	}


	return 1; //_ihd_audio.output->nid ? 0 : -1;
}