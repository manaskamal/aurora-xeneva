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


#define PLAY_STARTUP  12

int snd_io_query (vfs_node_t* node, int code, void* arg) {
	switch(code) {
	case PLAY_STARTUP:
		hda_audio_play();
		break;
	}

	return 1;
}
//! For now simply make interface to hdaudio!!
void sound_initialize () {
	vfs_node_t * snd = (vfs_node_t*)pmmngr_alloc(); //malloc(sizeof(vfs_node_t));
	strcpy (snd->filename, "fb");
	snd->size = 0;
	snd->eof = 0;
	snd->pos = 0;
	snd->current = 0;
	snd->flags = FS_FLAG_GENERAL;
	snd->status = 0;
	snd->open = 0;
	snd->read = 0;
	snd->write = 0;
	snd->read_blk = 0;
	snd->ioquery = snd_io_query;
	vfs_mount ("/dev/snd", snd);
}



