/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  message.cpp -- IPC Message protocol
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *================================================
 */

#include <ipc\message.h>
#include <atomic\mutex.h>

#ifdef ARCH_X64
#include <arch\x86_64\mmngr\kheap.h>
#endif

static kernel_message_queue_t *top;
//! Kernel Message service initialize
void message_init () {
	//queue->prev == NULL;
}

bool is_message_queue_empty () {
	return top == NULL;
}


//!simply find the process id and send the message
void message_send (uint16_t dest_id, message_t *msg) {
	x64_cli ();

	thread_t * dest_thread = thread_iterate_ready_list (dest_id);
	if (!dest_thread) {
		thread_t * blocked_thread = thread_iterate_block_list (dest_id);
		if (blocked_thread  != NULL){
			unblock_thread (blocked_thread);
		}
	}

	msg->dest_id = dest_id;
	//!Actuall Message model
	kernel_message_queue_t * temp = (kernel_message_queue_t*)AuPmmngrAlloc();

	memcpy (&temp->msg, msg, sizeof(message_t));
	temp->link = top;
	top = temp;

}



//! simply poll the mailbox, no msg then return,
//! if message arrive simply copy to process message
//! data 
void message_receive (message_t* msg) {
	x64_cli ();

	kernel_message_queue_t *temp;

	if (top == NULL) 
		return;
	else {
		temp = top;
		if (temp->msg.dest_id == get_current_thread()->id) {
			top = top->link;
			temp->link = NULL;
			memcpy (msg, &temp->msg,sizeof(message_t));
			AuPmmngrFree(temp);
		}
	}

}