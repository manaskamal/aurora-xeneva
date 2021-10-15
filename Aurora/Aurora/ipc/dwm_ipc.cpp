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

uint64_t dwm_queue[512];
static mutex_t *msg_mutex = create_mutex ();
static mutex_t *msg_rcv_mutex = create_mutex();

void dwm_ipc_init () {
	map_page((uint64_t)pmmngr_alloc(),0xFFFFFD0000000000);
}

uint64_t* get_dwm_message_q_address () {
	return 0;
}
void dwm_put_message (dwm_message_t *msg) {
	//x64_cli ();
	mutex_lock (msg_mutex);
	thread_t *t  = thread_iterate_ready_list (2);   //!ready list
	if (t == NULL) {
		t = thread_iterate_block_list(2);
	}

	dwm_message_t *tmsg = (dwm_message_t*)t->mouse_box;
	if (tmsg->type == 0)
		memcpy (t->mouse_box,msg,sizeof(dwm_message_t));
	mutex_unlock (msg_mutex);

}


void dwm_dispatch_message (dwm_message_t *msg) {
	x64_cli();
	mutex_lock (msg_rcv_mutex);
	dwm_message_t *tmsg = (dwm_message_t*)get_current_thread()->mouse_box;
	if (tmsg->type != 0) {
		memcpy (msg,tmsg,sizeof(dwm_message_t));
	}

	memset (get_current_thread()->mouse_box, 0, 4096);
	mutex_unlock (msg_rcv_mutex);
}