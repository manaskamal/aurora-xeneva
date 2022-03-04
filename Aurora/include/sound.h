/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  sound.h -- Controls entire sounds of the system
 *             it requires a proper audio controller to be
 *             configured
 *             
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */

#ifndef __SOUND_H__
#define __SOUND_H__

#include <stdint.h>

typedef struct _dsp_ {
	uint8_t buf[512];
	uint16_t id;
	struct _dsp_ *next;
	struct _dsp_* prev;
}dsp_t;

typedef struct _sound_ {
	/* the streams to read/write from/to */
	void *output;
	void *input;
	uint32_t strm_size;
	int vol;
}sound_t;



extern void sound_initialize ();
extern void sound_request_next (uint8_t* usable_buffer);
#endif