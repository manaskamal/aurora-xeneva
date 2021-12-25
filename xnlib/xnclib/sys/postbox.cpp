/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  postbox.h -- Thread specific post box
 *
 *  NOTE: - IPC-System in xeneva is such that, each thread get
 *          a message box. System specific messages are put on the
 *          message box. But the mouse sends its messages to a special 
 *          thread's message box, the GUI handler thread, means the GUI
 *          thread only receive mouse specific datas from the thread box,
 *          no system message are received by the GUI thread
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *=================================================================================
 */

#include <stdint.h>
#include <sys\postbox.h>
#include <sys\_process.h>
#include <string.h>

/**
  post_box_receive_msg -- Receives a message from message box 
  
  @param msg -- Pointer to the memory area to write to
  */
void post_box_receive_msg (postmsg_t *msg) {
	uint16_t app_id = get_current_pid();
	postmsg_t *tmsg = (postmsg_t*)0xFFFFFFFFB0000000;
	if (tmsg->type != 0 && tmsg->to_id == app_id) {
		memcpy (msg,tmsg,sizeof(postmsg_t));
		memset ((void*)0xFFFFFFFFB0000000, 0, sizeof(postmsg_t));
	}
}