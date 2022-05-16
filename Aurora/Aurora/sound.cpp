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

uint32_t next_pos = 0;
uint8_t* data_buff = 0;

#define BUFF_SIZE  4096 //1024 //0x10000

dsp_t* dsp_first;
dsp_t* dsp_last;

/*
 * AuSoundAddDSP -- adds a dsp to the dsp list
 * @param dsp -- dsp to add
 */
void AuSoundAddDSP(dsp_t *dsp) {
	dsp->next = NULL;
	dsp->prev = NULL;
	if (dsp_first == NULL) {
		dsp_first = dsp;
		dsp_last = dsp;
	}else {
		dsp_last->next = dsp;
		dsp->prev = dsp_last;
		dsp_last = dsp;
	}
}

/*
 * AuRemoveDSP -- removes a dsp from the dsp list
 * @param dsp -- dsp to remove
 */
void AuRemoveDSP(dsp_t *dsp) {
	if (dsp_first == NULL)
		return;

	if (dsp == dsp_first) {
		dsp_first = dsp_first->next;
	} else {
		dsp->prev->next = dsp->next;
	}

	if (dsp == dsp_last) {
		dsp_last = dsp->prev;
	} else {
		dsp->next->prev = dsp->prev;
	}

}

void AuRequestNextBlock(uint16_t id) {
	pri_event_t e;
	e.to_id = id;
	e.from_id = 0;
	e.type = 400;
	pri_put_message(&e);
}

/*
 * AuSoundGetDSP -- finds a dsp from the dsp list using its registered
 * thread id
 * @param id -- thread id
 */
dsp_t* AuSoundGetDSP(uint16_t id) {
	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {
		if (dsp->id == id)
			return dsp;
	}

	return NULL;
}


void AuSoundRead (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	if (registered_dev == NULL)
		return;
}

void AuSoundWrite (vfs_node_t *file, uint8_t* buffer, uint32_t length) {
	if (registered_dev == NULL)
		return;
	uint8_t* tmp_buffer = (uint8_t*)p2v((size_t)AuPmmngrAlloc());

	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {
		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++) {
			tmp_buffer[i] = dsp->buffer[i];
		}
		
	}
	
	registered_dev->write(tmp_buffer, BUFF_SIZE);
	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {
		AuRequestNextBlock(dsp->id);
	}
	/*data_buff = buffer;
	data_buff += BUFF_SIZE;*/
	AuPmmngrFree((void*)v2p(((size_t)tmp_buffer)));
}




int AuSoundIOQuery (vfs_node_t *node, int code, void* arg) {
	x64_cli();
	if (registered_dev == NULL)
		return 1;

	switch (code)
	{
	case SOUND_REGISTER_MEDIAPLAYER:{
		registered_thr = get_current_thread();
		dsp_t *dsp = (dsp_t*)malloc(sizeof(dsp_t));
		dsp->buffer = (uint8_t*)p2v((size_t)AuPmmngrAlloc());
		memset(dsp->buffer, 0, 4096);
		dsp->id = get_current_thread()->id;
		dsp->registered_thr = get_current_thread();
		AuSoundAddDSP(dsp);
		break;
	}
	case SOUND_START_OUTPUT:{
		AuSoundWrite(node,NULL, BUFF_SIZE);
		registered_dev->start_output_stream();
		break;
	}
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

void AuFileWrite (vfs_node_t* node, uint64_t *buffer, uint32_t length) {
	x64_cli();
	dsp_t *dsp = AuSoundGetDSP(get_current_thread()->id);
	uint8_t* al = (uint8_t*)buffer;
	uint8_t* aligned_buffer = (uint8_t*)buffer;
	memcpy(dsp->buffer, aligned_buffer, BUFF_SIZE);
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
	dsp->write = AuFileWrite;
	dsp->read_blk = 0;
	dsp->ioquery = AuSoundIOQuery;
	vfs_mount ("/dev/dsp", dsp, 0);

	dsp_first = NULL;
	dsp_last = NULL;
}

void AuSoundRegisterDevice(sound_t * dev) {
	if (registered_dev)
		return;
	registered_dev = dev;
}


void AuSoundRequestNext (uint64_t *buffer) {
	//printf ("Request next ");
	int16_t* hw_buffer = (int16_t*)buffer;
	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {
		int16_t *data_bu = (int16_t*)dsp->buffer;
		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++){
			hw_buffer[i] = data_bu[i];
		}
	}

	for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++)
		hw_buffer[i] /= 2;

	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {
		AuRequestNextBlock(dsp->id);
	}

	/*int16_t *data_bu =(int16_t*)data_buff;
	for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++) 
		hw_buffer[i] = data_bu[i];

	for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++) 
		hw_buffer[i] /= 2;

	data_buff += BUFF_SIZE;*/
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



