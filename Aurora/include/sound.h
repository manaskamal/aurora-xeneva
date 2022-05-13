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
#include <fs\vfs.h>
#include <aurora.h>

#define SOUND_REGISTER_MEDIAPLAYER 100
#define SOUND_START_OUTPUT  102
#define SOUND_STOP_OUTPUT  103
#define SOUND_START_INPUT  104
#define SOUND_STOP_INPUT  105

typedef struct _dsp_ {
	uint8_t buf[512];
	uint16_t id;
	struct _dsp_ *next;
	struct _dsp_* prev;
}dsp_t;

typedef struct _sound_ {
	/* the streams to read/write from/to */
	char name[32];
	void (*write) (uint64_t* buffer, size_t length);
	void (*read) (uint8_t* buffer, size_t length);
	void (*stop_output_stream) ();
	void (*start_output_stream) ();
}sound_t;



extern void AuSoundInitialize ();
AU_EXTERN AU_EXPORT void AuSoundRegisterDevice(sound_t * dev);
AU_EXTERN AU_EXPORT void AuSoundRequestNext (uint8_t* buffer);
extern void AuSoundOutputStart();
extern void AuSoundOutputStop();
extern void AuSoundWrite (vfs_node_t *file, uint64_t* buffer, uint32_t length);
#endif