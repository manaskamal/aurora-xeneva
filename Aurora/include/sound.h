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
#include <arch\x86_64\thread.h>
#include <aurora.h>
#include <utils\circ_buf.h>

#define SOUND_REGISTER_MEDIAPLAYER 100
#define SOUND_START_OUTPUT  102
#define SOUND_STOP_OUTPUT  103
#define SOUND_START_INPUT  104
#define SOUND_STOP_INPUT  105
#define SOUND_SET_VOLUME  106
#define SOUND_GET_VOLUME  107
#define SOUND_MUTE_ENABLE 108
#define SOUND_MUTE_DISABLE 109

typedef struct _dsp_ {
	//uint8_t *buffer;
	circ_buf_t *buffer;
	uint16_t id;
	thread_t *registered_thr;
	thread_t *blocked_thr;
	bool available;
	struct _dsp_ *next;
	struct _dsp_* prev;
}dsp_t;

typedef struct _sound_ {
	/* the streams to read/write from/to */
	char name[32];
	void (*write) (uint8_t* buffer, size_t length);
	void (*read) (uint8_t* buffer, size_t length);
	void (*stop_output_stream) ();
	void (*start_output_stream) ();
	void (*set_volume) (uint8_t vol);
}sound_t;

/* Sound IPC message structure */
typedef struct _au_sound_callback_ {
	uint8_t uchar_1;
	uint8_t uchar_2;
	uint16_t ushort_1;
	uint16_t ushort_2;
	uint32_t uinteger_1;
	uint32_t uinteger_2;
	uint64_t ulong_1;
	uint64_t ulong_2;
}au_sound_callback_t;
	



extern void AuSoundInitialize ();
AU_EXTERN AU_EXPORT void AuSoundRegisterDevice(sound_t * dev);
AU_EXTERN AU_EXPORT void AuSoundRequestNext (uint64_t* buffer);
extern void AuSoundStart();
extern void AuSoundDeInitialize();
extern void AuSoundWrite (vfs_node_t *file, uint8_t* buffer, uint32_t length);
#endif