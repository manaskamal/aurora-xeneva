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
 * /PROJECT - Aurora's Xeneva v1.0
 * @pri_loop.h -- IPC for priwm server and clients
 *
 **/

#ifndef __PRI_LOOP_H__
#define __PRI_LOOP_H__

#include <stdint.h>

#define PRI_LOOP_CREATE 401
#define PRI_LOOP_DESTROY 402
#define PRI_LOOP_PUT_EVENT 403
#define PRI_LOOP_GET_EVENT 404
#define PRI_LOOP_CREATE_ROOT 405
#define PRI_LOOP_GET_EVENT_ROOT 406

#define PRI_LOOP_NO_MSG  -1
#define PRI_LOOP_ROOT_ID  1

/*
 * pri_event_t -- event message structure
 */
typedef struct _pri_event_ {
	uint8_t type;
	uint8_t to_id;
	uint8_t from_id;
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
	uint32_t dword7;
	uint32_t dword8;
	uint32_t *p_value;
	uint32_t *p_value2;
	char *value;
	unsigned char* value2;
	char char_values[100];
}pri_event_t;

/**
 * pri_loop_box_t -- loop_box structure
 */
typedef struct _pri_loop_box_ {
	uint64_t* address;
	uint16_t owner_id;
	int head_idx;  //Message enqueue
	int tail_idx;  //Message dequeue
	bool full;
	uint16_t size;
	struct _pri_loop_box_ *next;
	struct _pri_loop_box_ *prev;
}pri_loop_box_t;

/**
 * pri_loop_init -- initialize pri_loop_manager
 */
extern void pri_loop_init ();

/** 
 * pri_put_message -- put a message to specific pri_loop_box
 * @param event -- event message to put
 */
extern void pri_put_message (pri_event_t *event);

/*
 * pri_loop_destroy -- removes a pri_loop_box from the list
 * @param box -- box to remove
 */
extern void pri_loop_destroy (pri_loop_box_t *box);

/*
 * pri_loop_destroy_by_id -- removes a pri_loop_box from the list by its id
 * @param id -- id of the box to be removed
 */
extern void pri_loop_destroy_by_id (uint16_t id);
#endif