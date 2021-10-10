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

static mutex_t *ipc_mutex_msg = create_mutex();
static mutex_t *ipc_rcv_msg = create_mutex();
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
	mutex_lock (ipc_mutex_msg);
	thread_t * dest_thread = thread_iterate_ready_list (dest_id);
	if (!dest_thread) {
		thread_t * blocked_thread = thread_iterate_block_list (dest_id);
		if (blocked_thread  != NULL){
			unblock_thread (blocked_thread);
		}
	}

	msg->dest_id = dest_id;
	//!Actuall Message model
	kernel_message_queue_t * temp = (kernel_message_queue_t*)pmmngr_alloc();

	memcpy (&temp->msg, msg, sizeof(message_t));
	temp->link = top;
	top = temp;
end:
	mutex_unlock (ipc_mutex_msg);
}



//! simply poll the mailbox, no msg then return,
//! if message arrive simply copy to process message
//! data 
void message_receive (message_t* msg) {
	x64_cli ();
	mutex_lock(ipc_rcv_msg);

	kernel_message_queue_t *temp;

	if (top == NULL) 
		goto end;
	else {
		temp = top;
		if (temp->msg.dest_id == get_current_thread()->id) {
			top = top->link;
			temp->link = NULL;
			memcpy (msg, &temp->msg,sizeof(message_t));
			pmmngr_free(temp);
		}
	}

end:
	mutex_unlock(ipc_rcv_msg);
}