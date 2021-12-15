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

/**
 * PostBox handles the income and redirection of messages to specific threads
 * in the system, except the GUI thread
 */

#ifndef __POST_BOX__
#define __POST_BOX__

#include <stdint.h>

/* for now, just create a timer message */
#define SYSTEM_MESSAGE_TIMER_EVENT  1
#define SYSTEM_MESSAGE_ACPI_EVENT 2


/**
 * Post box message format
 */
typedef struct _post_box_message_ {
	uint16_t type;
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
	uint16_t to_id;
}postmsg_t;

/**
 * post_box_put_msg -- Post a system message to the message box
 *
 * @param msg -- Message to post
 * @param to_id -- Thread id
 *
 */
extern void post_box_put_msg (postmsg_t *msg, uint16_t to_id);

#endif