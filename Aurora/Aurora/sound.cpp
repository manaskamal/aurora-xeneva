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

#define BUFF_SIZE  4096

dsp_t* dsp_first;
dsp_t* dsp_last;
bool _audio_started_;
bool _audio_stoped_;
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
	e.type = 10;
	pri_put_message(&e);
	//thread_t *t = thread_iterate_ready_list(id);
	//if (t == NULL)
	//	t = thread_iterate_block_list(id);

	//if (t->state == THREAD_STATE_BLOCKED)
	//	unblock_thread(t);
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


size_t AuSoundRead (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	if (registered_dev == NULL)
		return -1;
	return 0;
}

/*
 * AuSoundWrite -- Writes to Sound Cards internal buffer
 * @param file -- pointer to sound card file
 * @param buffer -- Pointer to buffer
 * @param length -- maximum sound samples to write
 */
void AuSoundWrite (vfs_node_t *file, uint8_t* buffer, uint32_t length) {
	if (registered_dev == NULL)
		return;
	int16_t* tmp_buffer = (int16_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));
	uint8_t* buff = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));
	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

		for (int i = 0; i < BUFF_SIZE; i++)
			circular_buf_get(dsp->buffer,buff); 

		int16_t* aligned_buff = (int16_t*)buff;
		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++) {
			tmp_buffer[i] = aligned_buff[i];
		}
		//AuRequestNextBlock(dsp->id);
	}
	
	registered_dev->write((uint8_t*)tmp_buffer, BUFF_SIZE);
	AuPmmngrFreeBlocks((void*)v2p((size_t)buff), BUFF_SIZE/4096);
	AuPmmngrFreeBlocks((void*)v2p((size_t)tmp_buffer), BUFF_SIZE/4096);
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
		uint8_t* buffer = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));
		dsp->buffer = circ_buf_init(buffer, BUFF_SIZE); //(uint8_t*)
		dsp->id = get_current_thread()->id;
		dsp->registered_thr = get_current_thread();
		AuSoundAddDSP(dsp);
		break;
	}
	case SOUND_START_OUTPUT:{
		/* This Code should be removed */
		break;
	}
	case SOUND_STOP_OUTPUT:{
		/* This Code should be removed */
		break;
						   }
	case SOUND_START_INPUT: //Not implemented
		break;
	case SOUND_STOP_INPUT:
		break;  //Not implemented
	case SOUND_SET_VOLUME: {
		if (!registered_dev)
			return -1;
		au_sound_callback_t *callbk = (au_sound_callback_t*)arg;
		registered_dev->set_volume(callbk->uchar_1);
		break;
	}	
	}

	return 0;
}

void AuFileWrite (vfs_node_t* node, uint64_t *buffer, uint32_t length) {
	x64_cli();
	dsp_t *dsp = AuSoundGetDSP(get_current_thread()->id);
	uint8_t* al = (uint8_t*)buffer;
	uint8_t* aligned_buffer = (uint8_t*)buffer;
	if (circular_buf_full(dsp->buffer)) {
		dsp->blocked_thr = get_current_thread();
		block_thread(get_current_thread());
		force_sched();
	}
	for (int i = 0; i < BUFF_SIZE; i++) 
		circular_buf_put2(dsp->buffer, aligned_buffer[i]);
	
}

/*
 * AuSoundInitialize -- Initialized the Aurora sound system
 */
void AuSoundInitialize () {
	vfs_node_t *dsp = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy (dsp->filename, "dsp");
	dsp->size = 0;
	dsp->eof = 0;
	dsp->pos = 0;
	dsp->current = 0;
	dsp->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;
	dsp->status = 0;
	dsp->open = 0;
	dsp->read = AuSoundRead;
	dsp->write = AuFileWrite;
	dsp->read_blk = 0;
	dsp->ioquery = AuSoundIOQuery;
	vfs_mount ("/dev/dsp", dsp, 0);

	dsp_first = NULL;
	dsp_last = NULL;
	_audio_started_ = false;
	_audio_stoped_ = false;
}

/*
 * AuSoundRegisterDevice -- Registeres a sound card device
 * to Aurora Sound System
 * @param dev -- Sound card device
 */
void AuSoundRegisterDevice(sound_t * dev) {
	if (registered_dev)
		return;
	registered_dev = dev;
}

/*
 * AuSoundRequestNext -- Requests next sound block
 * by Sound card
 * @param buffer -- Buffer to be filled with sound samples
 */
void AuSoundRequestNext (uint64_t *buffer) {
	if (dsp_first == NULL)
		return;
	int16_t* hw_buffer = (int16_t*)(buffer);

	for (int i = 0; i < BUFF_SIZE /sizeof(int16_t); i++)
		hw_buffer[i] = 0;
	

	uint8_t *buff = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	for (dsp_t *dsp = dsp_last; dsp != NULL; dsp = dsp->prev) {

		for (int i = 0; i < BUFF_SIZE; i++)
			circular_buf_get(dsp->buffer,buff);
		
		int16_t *data_bu = (int16_t*)buff;

		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++)
			data_bu[i] /= 2;

		for (int i = 0; i < BUFF_SIZE /sizeof(int16_t); i++){
			hw_buffer[i] += data_bu[i];
		}

	}


	for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++)
		hw_buffer[i] /= 2;

	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {
		AuRequestNextBlock(dsp->id);
	}

	AuPmmngrFreeBlocks((void*)v2p((size_t)buff),BUFF_SIZE/4096);
}

/*
 * AuSoundStart -- Starts the Sound card
 */
void AuSoundStart() {
	if (registered_dev == NULL)
		return;
	registered_dev->start_output_stream();
}

/*
 * AuSoundDeInitialize -- Stops the Sound card
 */
void AuSoundDeInitialize() {
	if (registered_dev == NULL)
		return;
	registered_dev->stop_output_stream();
}


/*
 * AuSoundDestroyDSP -- finds and destroys a registered
 * dsp by its thread id
 * @param id -- thread id
 */
void AuSoundDestroyDSP(uint16_t id) {
	dsp_t* target_dsp = NULL;
	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {
		if (dsp->id == id) {
			target_dsp = dsp;
			break;
		}
	}

	if (target_dsp == NULL)
		return;

	AuPmmngrFreeBlocks((void*)v2p((uint64_t)target_dsp->buffer->buffer),
		BUFF_SIZE/4096);

	circ_buf_free(target_dsp->buffer);
	AuRemoveDSP(target_dsp);
	free(target_dsp);
}



