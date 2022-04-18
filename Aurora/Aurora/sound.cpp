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

#include <sound.h>
#include <fs\vfs.h>
#include <pmmngr.h>
#include <drivers\hdaudio\hda.h>
#include <ipc\pri_loop.h>
#include <_null.h>

#define PLAY_STARTUP  12
#define SOUND_LOOP_ENABLE  13
#define SOUND_PLAY 14
#define SOUND_ADD_PCM 15
#define SOUND_CREATE_CLIENT 16

#define SND_REQUEST_NEXT   0x5


static bool _sound_loop_prop_ = false;

dsp_t *dsp_head = NULL;
dsp_t *dsp_last = NULL;


/**
 * Insert a dsp to dsp list
 * @param dsp -- new dsp address
 */
void dsp_insert (dsp_t* dsp) {
	dsp->next = NULL;
	dsp->prev = NULL;

	if (dsp_head == NULL) {
		dsp_last = dsp;
		dsp_head = dsp;
	} else {
		dsp_last->next = dsp;
		dsp->prev = dsp_last;
	}
	dsp_last = dsp;
}

/**
 * remove a dsp from dsp list
 * @param dsp -- dsp address to remove
 */
void dsp_delete (dsp_t* dsp) {

	if (dsp_head == NULL)
		return;

	if (dsp == dsp_head) {
		dsp_head = dsp_head->next;
	} else {
		dsp->prev->next = dsp->next;
	}

	if (dsp == dsp_last) {
		dsp_last = dsp->prev;
	} else {
		dsp->next->prev = dsp->prev;
	}

	AuPmmngrFree (dsp);
}
/**
 * sound_create_client -- create a client node
 * @param node -- virtual file system node
 */
void sound_create_client (vfs_node_t *node) {
	dsp_t *dsp = (dsp_t*)AuPmmngrAlloc();
	memset(dsp,0,4096);
	node->device = dsp;
	dsp_insert (dsp);
}


int snd_io_query (vfs_node_t* node, int code, void* arg) {
	switch(code) {
	case PLAY_STARTUP:
		hda_audio_play();
		break;
	case SOUND_LOOP_ENABLE: 
		_sound_loop_prop_ = true;
		break;
	case SOUND_PLAY:
		hda_audio_play();
		break;
	case SOUND_CREATE_CLIENT:
		sound_create_client (node);
		break;
	}

	return 1;
}


void sound_write (vfs_node_t *file, uint8_t* buffer, uint32_t length) {
	/* it will write the audio content to hda descriptor buffers */
	if (file->device) {
		dsp_t *dsp = (dsp_t*)file->device;
		memcpy (dsp->buf,buffer, 512);
	}
}


void sound_request_next (uint8_t* usable_buffer) {
	for (dsp_t *c_dsp = dsp_head; c_dsp != NULL; c_dsp = c_dsp->next) {
		for (int i = 0; i < SAMPLES_PER_BUFFER; i++) {
			usable_buffer[i] = c_dsp->buf[i];
			usable_buffer[i] /= 2;
		}
		//memcpy (usable_buffer,c_dsp->buf,512/);
	}
}

//! For now simply make interface to hdaudio!!
void sound_initialize () {
	dsp_last = NULL;
	dsp_last = NULL;

	vfs_node_t * snd = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy (snd->filename, "snd");
	snd->size = 0;
	snd->eof = 0;
	snd->pos = 0;
	snd->current = 0;
	snd->flags = FS_FLAG_GENERAL;
	snd->status = 0;
	snd->open = 0;
	snd->read = 0;
	snd->write = sound_write;
	snd->read_blk = 0;
	snd->ioquery = snd_io_query;
	vfs_mount ("/dev/snd", snd, 0);
}



