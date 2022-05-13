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


#include <sound.h>
#include <fs\vfs.h>
#include <pmmngr.h>
#include <drivers\hdaudio\hda.h>
#include <ipc\pri_loop.h>
#include <_null.h>
#include <arch\x86_64\thread.h>
#include <stdio.h>

sound_t *registered_dev;
thread_t* registered_thr;

void AuSoundRead (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	if (registered_dev == NULL)
		return;
}

void AuSoundWrite (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	if (registered_dev == NULL)
		return;
	registered_dev->write(buffer, length);
}


int AuSoundIOQuery (vfs_node_t *node, int code, void* arg) {
	if (registered_dev == NULL)
		return 1;

	switch (code)
	{
	case SOUND_REGISTER_MEDIAPLAYER:
		registered_thr = get_current_thread();
		break;
	case SOUND_START_OUTPUT:
		registered_dev->start_output_stream();
		break;
	case SOUND_STOP_OUTPUT:
		registered_dev->stop_output_stream();
		break;
	case SOUND_START_INPUT: //Not implemented
		break;
	case SOUND_STOP_INPUT:
		break;  //Not implemented
	}

	return 0;
}


void AuSoundInitialize () {
	vfs_node_t *dsp = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy (dsp->filename, "dsp");
	dsp->size = 0;
	dsp->eof = 0;
	dsp->pos = 0;
	dsp->current = 0;
	dsp->flags = FS_FLAG_GENERAL;
	dsp->status = 0;
	dsp->open = 0;
	dsp->read = AuSoundRead;
	dsp->write = AuSoundWrite;
	dsp->read_blk = 0;
	dsp->ioquery = AuSoundIOQuery;
	vfs_mount ("/dev/dsp", dsp, 0);
}

void AuSoundRegisterDevice(sound_t * dev) {
	if (registered_dev)
		return;
	registered_dev = dev;
}


void AuSoundRequestNext (uint8_t *buffer) {

}

void AuSoundOutputStart() {
	if (registered_dev == NULL)
		return;
	registered_dev->start_output_stream();
}

void AuSoundOutputStop() {
	if (registered_dev == NULL)
		return;
	registered_dev->stop_output_stream();
}



