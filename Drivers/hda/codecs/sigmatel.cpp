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

#include <serial.h>
#include "sigmatel.h"

void sigmatel_init (int codec, int nid) {

	
	uint16_t format =  (1<<15) | SR_44_KHZ | (0<<11) | (0 << 8) | BITS_16 | 1;
	//uint16_t format =  (0<<14) | (0<<11) | (0<<8)| (1<<4) | (1<<0);
	codec_query (codec, 2, VERB_SET_FORMAT | format);
	
	codec_query (codec, 2, VERB_SET_STREAM_CHANNEL | 0x10);  //0x10
	codec_query (codec, 3, VERB_SET_STREAM_CHANNEL | 0x10);
	codec_query (codec, 4, VERB_SET_STREAM_CHANNEL | 0x10);
	codec_query (codec, 5, VERB_SET_STREAM_CHANNEL | 0x10);
	codec_query (codec, 6, VERB_SET_STREAM_CHANNEL | 0x10);

	codec_query (codec, 2, VERB_SET_CONV_CHANNEL_COUNT | 1);
	codec_query (codec, 3, VERB_SET_CONV_CHANNEL_COUNT | 1);
	codec_query (codec, 4, VERB_SET_CONV_CHANNEL_COUNT | 1);
	codec_query (codec, 5, VERB_SET_CONV_CHANNEL_COUNT | 1);
	codec_query (codec, 6, VERB_SET_CONV_CHANNEL_COUNT | 1);

	
	codec_query (codec, 3, VERB_SET_FORMAT | format);
	codec_query (codec, 4, VERB_SET_FORMAT | format);
	codec_query (codec, 5, VERB_SET_FORMAT | format);
	codec_query (codec, 6, VERB_SET_FORMAT | format);

	

    uint32_t stream = codec_query (codec, nid, 0xF0600);

	//_ihd_audio.output->sample_rate = SR_48_KHZ;
	//_ihd_audio.output->num_channels = 2;

	codec_query(codec, nid, 0x70C00 | (1<<2));
	
	//!Set Pin control : enable the output bit
	
}


//! Set volume, for output codec
void sigmatel_set_volume (uint8_t volume, int codec) {
	int meta = 0xb000;
	uint32_t amp_gain = codec_query(codec, 3,0xB8000);
	uint32_t step = amp_gain & 0x7f;

	if (volume == 0)
		volume = 0x80;  //mute bit
	else
		volume = volume * step / 255;

	//codec_query (_ihd_audio.output->codec, _ihd_audio.output->nid, VERB_SET_AMP_GAIN_MUTE | 0xb000 | volume);

	codec_query (codec, 2, 0x39000 | volume);
	codec_query (codec, 2, 0x3A000 | volume );
	codec_query (codec, 3, 0x39000 | volume);
	codec_query (codec, 3, 0x3A000 | volume);
	codec_query (codec, 4, 0x39000 | volume);
	codec_query (codec, 4, 0x3A000 | volume);
	codec_query (codec, 5, 0x39000 | volume);
	codec_query (codec, 5, 0x3A000 | volume);
	codec_query (codec, 6, 0x39000 | volume);
	codec_query (codec, 6, 0x3A000 | volume);
}

