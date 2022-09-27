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
#include <serial.h>

// keyboard controller ---------------------------------------
extern void debug_print (const char* text, ...);
static bool __Au_capslock_key;
static bool __Au_numlock_key;
static bool __Au_scroll_lock_key;

void AuKeyboardSendCmd (uint8_t cmd) {
	
	while(1) 
		if ((inportb(0x64) & 0x2) == 0)
			break;
	outportb(0x60, cmd);
}

/*
 * AuKeyboardSetLight -- turn on/off led of special keys
 * @param num -- numlock key
 * @param caps -- capslock
 * @param scroll -- scroll lock key
 */
void AuKeyboardSetLight (bool num, bool caps, bool scroll) {
	uint8_t data = 0;

	data = (scroll) ? (data | 1) : (data & 1);
	data = (num) ? (num | 2) : (num & 2);
	data = (caps) ? (num | 4) : (num & 4);

	AuKeyboardSendCmd(0xED);
	AuKeyboardSendCmd(data);
}
	
/**
 * kybrd_handler -- Handles Key Events and redirects it to
 *                  Window Manager
 */
void AuKeyboardHandler(size_t v, void* p)
{
	static bool _extended = false;
	int code = 0;
	//! read scan code only if the kybrd controller output buffer is full (scan mode is in it)
	if (inportb(0x64) & 1)
	{
		int code = inportb(0x60);
		if (is_scheduler_initialized()) {
			if (code == 0x3a) {
				__Au_capslock_key = !__Au_capslock_key;
			}

			message_t *msg = (message_t*)p2v((size_t)AuPmmngrAlloc());
			msg->type = 3;
		    msg->dword = code;
		    message_send (2,msg);
			AuPmmngrFree ((void*)v2p((size_t)msg));
		} else {
			printf ("[Aurora]:Key Pressed\n");
		}

		/*thread_t* thr = (thread_t*)thread_iterate_ready_list (1);
	    if (thr != NULL){
			unblock_thread(thr);
		}*/
		//!Here we need to pass this code to window manager process {a.k.a DWM} or shell program
		//!shell will decode the scancode and will take action
	}


	//AuKeyboardSetLight(__Au_numlock_key, __Au_capslock_key, __Au_scroll_lock_key);

 end:
	//! tell apic we are done!!!
	AuInterruptEnd(1);
	return;
}



/**
 * kybrd_init -- Initialize the keyboard
 * it installs the irq_1 handler with keyboard handler function
 */
void AuKeyboardInitialize () {
	AuInterruptSet (1,AuKeyboardHandler,1, false);
	__Au_capslock_key = __Au_numlock_key = __Au_scroll_lock_key = false;
	outportb(0xF0, 1);
}