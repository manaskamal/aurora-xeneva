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
 * /PROJECT - Aurora's Xeneva v1.0
 * @pri_loop.h -- IPC for priwm server and clients
 *
 **/

#include <ipc\pri_loop.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <arch\x86_64\thread.h>
#include <serial.h>
#include <stdio.h>
#include <fs\vfs.h>

pri_loop_box_t *first_loop = NULL;
pri_loop_box_t *last_loop = NULL;
/**
 * pri_loop_create -- create a new pri_loop_box 
 */
void pri_loop_create () {
	pri_loop_box_t *loop = (pri_loop_box_t*)malloc(sizeof(pri_loop_box_t));
	loop->address = (void*)p2v((size_t)AuPmmngrAlloc());//malloc(sizeof(pri_event_t));
	memset(loop->address,0, sizeof(pri_event_t));
	loop->owner_id = get_current_thread()->id;
	loop->pending_msg_count = 0;
	loop->message_pending = 0;
	loop->next = NULL;
	loop->prev = NULL;

	if (first_loop == NULL)  {
		first_loop = loop;
		last_loop = loop;
	} else {
		last_loop->next = loop;
		loop->prev = last_loop;
		last_loop = loop;
	}
}

/*
 * pri_loop_destroy -- removes a pri_loop_box from the list
 * @param box -- box to remove
 */
void pri_loop_destroy (pri_loop_box_t *box) {
	if (first_loop == NULL)
		return;

	if (box == first_loop) {
		first_loop = first_loop->next;
	} else {
		box->prev->next = box->next;
	}

	if (box == last_loop) {
		last_loop = box->prev;
	} else {
		box->next->prev = box->prev;
	}

	AuPmmngrFree((void*)v2p((size_t)box->address));
	//AuPmmngrFree(box);
	free(box);
}

/*
 * pri_loop_destroy_by_id -- removes a pri_loop_box from the list by its id
 * @param id -- id of the box to be removed
 */
void pri_loop_destroy_by_id (uint16_t id) {
	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {
		if (loop->owner_id == id) {
			pri_loop_destroy (loop);
			break;
		}
	}

	return;
}

/** 
 * pri_put_message -- put a message to specific pri_loop_box
 * @param event -- event message to put
 */
void pri_put_message (pri_event_t *event) {
	x64_cli();
	bool hunged = false;
	uint16_t owner_id = event->to_id;
	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {
		if (loop->owner_id == owner_id) {
			if (loop->message_pending)
				break;
			memcpy (loop->address, event, sizeof(pri_event_t));
			loop->message_pending = 1;
			loop->pending_msg_count++;
			break;
		}
	}

	//! check if the destination thread is blocked or not
	//! if blocked, wake it up, cause new message is pending
	thread_t *thread = thread_iterate_ready_list(owner_id);	
	if (thread == NULL) 
		thread = thread_iterate_block_list(owner_id);
	if (thread != NULL && thread->state == THREAD_STATE_BLOCKED) {
		unblock_thread(thread);
	}
ret:
	x64_sti();
	return;
}

/*
 * pri_get_message -- pops a message from specific pri_loop_box
 * @param event -- pointer where to store the specific message
 */
void pri_get_message (pri_event_t *event) {
	x64_cli ();

	uint16_t owner_id = get_current_thread()->id;
	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {
		if (loop->owner_id == owner_id) {
			if (loop->message_pending){
				memcpy (event,loop->address, sizeof(pri_event_t));
				memset (loop->address, 0, sizeof(pri_event_t));
				loop->pending_msg_count--;
				if (loop->pending_msg_count == 0) {
					loop->message_pending = false;
				}
			}
			memset (loop->address, 0, sizeof(pri_event_t));
			break;
		}
	}

	x64_sti();
	return;
}

/**
 * pri_loop_ioquery -- ioquery installation for pri_loop_manager
 * @param file -- handled by system
 * @param code -- passed by user to the system
 * @param arg -- extra argument passed by user
 */
int pri_loop_ioquery (vfs_node_t *file, int code, void *arg) {
	switch (code) {
	case PRI_LOOP_CREATE: {
		pri_loop_create();
		break;
	}
	case PRI_LOOP_DESTROY: {
		pri_loop_box_t *box;
		for (box = first_loop; box != NULL; box = box->next) {
			if (box->owner_id == get_current_thread()->id) {
				pri_loop_destroy(box);
				break;
			}
		}
		break;
	}
	case PRI_LOOP_PUT_EVENT: {
		pri_event_t *event = (pri_event_t*)arg;
		pri_put_message(event);
		break;
	}

	case PRI_LOOP_GET_EVENT: {
		pri_event_t e;
		pri_get_message(&e);
		memcpy (arg,&e,sizeof(pri_event_t));
		break;
	}
	}

	return 1;
}

/**
 * pri_loop_init -- initialize pri_loop_manager
 */
void pri_loop_init () {
	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy (node->filename, "pri_loop");
	node->size = 0;
	node->eof = 0;
	node->pos = 0;
	node->current = 0;
	node->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;
	node->status = 0;
	node->open = 0;
	node->read = 0;
	node->write = 0;
	node->read_blk = 0;
	node->ioquery = pri_loop_ioquery;
	vfs_mount ("/dev/pri_loop", node, 0);
}