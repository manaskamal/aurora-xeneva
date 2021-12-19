/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  dwm_ipc.cpp -- Desktop Window Manager Client to Server Protocol
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =====================================================================
 */

#include <ipc\dwm_ipc.h>
#include <atomic\mutex.h>
#include <utils\lnklist.h>
#include <utils\circ_buf.h>

uint64_t dwm_queue[512];
static mutex_t *msg_mutex = create_mutex ();
static mutex_t *msg_rcv_mutex = create_mutex();

void dwm_ipc_init () {
	void* p = pmmngr_alloc();
	memset(p, 0, 4096);
	map_page((uint64_t)p,0xFFFFFD0000000000, PAGING_USER);
	void *p2 = pmmngr_alloc();
	memset(p2, 0, 4096);
	map_page((uint64_t)p2,0xFFFFD00000000000,PAGING_USER);
}

uint64_t* get_dwm_message_q_address () {
	return 0;
}
void dwm_put_message (dwm_message_t *msg) {

	if (!is_multi_task_enable())
		return;

	thread_t *t  = thread_iterate_ready_list (2);   //!ready list
	if (t == NULL) {
		t = thread_iterate_block_list(2);
	}

	dwm_message_t *tmsg = (dwm_message_t*)t->msg_box;
	if (tmsg->type == 0)
		memcpy (t->msg_box,msg,sizeof(dwm_message_t));

	if (t->state == THREAD_STATE_BLOCKED){
		unblock_thread(t);
	}
}


void dwm_dispatch_message (dwm_message_t *msg) {
	x64_cli();
	mutex_lock (msg_rcv_mutex);
	dwm_message_t *tmsg = (dwm_message_t*)get_current_thread()->msg_box;
	if (tmsg->type != 0) {
		memcpy (msg,tmsg,sizeof(dwm_message_t));
	}

	memset (get_current_thread()->msg_box, 0, 4096);
	mutex_unlock (msg_rcv_mutex);
}