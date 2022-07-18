/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
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

#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <stdint.h>

#define HDA_WIDGET_TYPE_LINE_OUT  0x0
#define HDA_WIDGET_TYPE_DAC   0x1
#define HDA_WIDGET_TYPE_HP_OUT    0x2
#define HDA_WIDGET_TYPE_MIXER 0x3
#define HDA_WIDGET_TYPE_PIN 0x4


typedef struct _widget_ {
	uint8_t type;
	uint32_t nid;
	uint32_t codec;
	uint32_t parent_pin_nid;
	uint32_t parent_mixer_nid;
	bool amp_cap;
	bool mute;
	int conn_list_length;
	bool eapd_btl;
	bool power_cap;
	uint32_t pcm_rates;
	uint32_t pcm_format;
	_widget_ *next;
	_widget_ *prev;
}hda_widget_t;

typedef struct _audio_path_ {
	hda_widget_t *root;
	hda_widget_t *last;
	_audio_path_ *next;
	_audio_path_* prev;
}hda_audio_path_t;


/*
 * hda_create_widget -- creates a hd audio widget
 */
extern hda_widget_t *hda_create_widget ();
extern hda_audio_path_t* hda_create_audio_path();
extern void widget_setup_pin (int codec, int nid);
#endif