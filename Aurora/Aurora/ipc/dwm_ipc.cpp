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

void dwm_ipc_init () {
	void* p = AuPmmngrAlloc();
	memset(p, 0, 4096);
	AuMapPage((uint64_t)p,0xFFFFFD0000000000, PAGING_USER);
	void *p2 = AuPmmngrAlloc();
	memset(p2, 0, 4096);
	AuMapPage((uint64_t)p2,0xFFFFD00000000000,PAGING_USER);
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
}


void dwm_dispatch_message (dwm_message_t *msg) {
	x64_cli();
	dwm_message_t *tmsg = (dwm_message_t*)get_current_thread()->msg_box;
	if (tmsg->type != 0) {
		memcpy (msg,tmsg,sizeof(dwm_message_t));
		memset (get_current_thread()->msg_box, 0, 4096);
	}
	
}