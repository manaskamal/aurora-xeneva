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

#ifndef __POSTBOX_H__
#define __POSTBOX_H__

#include <stdint.h>
#include <sys\_xeneva.h>


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
  post_box_receive_msg -- Receives a message from message box 
  
  @param msg -- Pointer to the memory area to write to
  */
XE_EXTERN XE_EXPORT void post_box_receive_msg (postmsg_t *msg);
#endif