/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  kybrd.h -- PS/2 Keybaord driver
 *
 *  /PROJECT - Aurora v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *=================================================
 */

#include <drivers\kybrd.h>
#include <ipc\message.h>

// keyboard controller ---------------------------------------


void kybrd_handler(size_t v, void* p)
{
	static bool _extended = false;
	int code = 0;
	//! read scan code only if the kybrd controller output buffer is full (scan mode is in it)
	if (inportb(0x64) & 1)
	{
		int code = inportb(0x60);
		message_t *msg = (message_t*)pmmngr_alloc();
		msg->type = 3;
		msg->dword = code;
		message_send (1,msg);
		pmmngr_free (msg);

		//thread_t* thr = (thread_t*)thread_iterate_ready_list (3);
		////thr->rsp = thr->blocked_stack_resv;
	 //   if (thr != NULL){
		//	//printf ("Unblocking thread stack -> %x\n", thr->rsp);
		//   // printf ("Unblocking thread name -> %s\n", thr->name);
		//	thr->state = THREAD_STATE_READY;
		//	unblock_thread(thr);
		//}
		//!Here we need to pass this code to window manager process {a.k.a DWM} or shell program
		//!shell will decode the scancode and will take action
	}

  
	//! tell apic we are done!!!
	interrupt_end();
	return;
}

void kybrd_init () {
	interrupt_set (1,kybrd_handler,1);
	//irq_mask(1, true);
}