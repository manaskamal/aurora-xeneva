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
static kernel_message_queue_t *queue;
static kernel_message_queue_t *head_pointer;
//! Kernel Message service initialize
void message_init () {
	queue = (kernel_message_queue_t*)pmmngr_alloc();
	head_pointer = queue;
	memset (queue,0,4096);
	memset (&queue->msg,0,sizeof (message_t));
	queue->next == NULL;
	//queue->prev == NULL;
}


//!simply find the process id and send the message
void message_send (uint16_t dest_id, message_t *msg) {
	x64_cli ();
	mutex_lock (ipc_mutex_msg);
	thread_t * dest_thread = thread_iterate_ready_list (dest_id);
	if (!dest_thread) {
		thread_t * blocked_thread = thread_iterate_block_list (dest_id);
		if (blocked_thread  != NULL)
			unblock_thread (blocked_thread);
		else
			goto end;
	}
	
	if (queue->msg.type == 0 ) {
		kernel_message_queue_t *km = (kernel_message_queue_t*)pmmngr_alloc();
		memcpy (&km->msg, msg,sizeof(message_t));
		km->next = NULL;
		memcpy (queue, km,sizeof (kernel_message_queue_t));
		pmmngr_free(km);
	} else if (queue->msg.type != 0){
		kernel_message_queue_t *tmsgq = queue;
		do {
			tmsgq = tmsgq->next;
		}while (tmsgq->next != NULL);
		kernel_message_queue_t *km = (kernel_message_queue_t*)pmmngr_alloc();
		memcpy (&km->msg,msg,sizeof(message_t));
		km->next = NULL;
		tmsgq->next = km;
	}
end:
	mutex_unlock (ipc_mutex_msg);
}



//! simply poll the mailbox, no msg then return,
//! if message arrive simply copy to process message
//! data 
void message_receive (message_t* msg) {
	x64_cli ();
	mutex_lock(ipc_rcv_msg);

	kernel_message_queue_t *kq = (kernel_message_queue_t*)queue;

	memcpy (msg,&kq->msg,sizeof (message_t));
	queue = queue->next;
	
	//!FIXME: Some buggy
	if (queue == NULL) {
		if (queue->next == 0x0) {
			memset (kq,0,sizeof(kernel_message_queue_t));
			queue = head_pointer;
			goto end;
		}
		queue = queue->next;	
	}
	memset (kq,0,sizeof(kernel_message_queue_t));

end:
	mutex_unlock(ipc_rcv_msg);
}