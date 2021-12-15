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

#include <ipc\postbox.h>
#include <arch\x86_64\thread.h>

/**
 * post_box_put_msg -- Post a system message to the message box
 *
 * @param msg -- Message to post
 * @param to_id -- Thread id
 *
 */
void post_box_put_msg (postmsg_t *msg, uint16_t to_id) {

	/* check, if multitasking is initialized,
	   if not, just return
	   */
	if (!is_multi_task_enable())
		return;

	thread_t *t  = thread_iterate_ready_list (to_id);   //!ready list
	if (t == NULL) {
		t = thread_iterate_block_list(to_id);
	}

	postmsg_t *tmsg = (postmsg_t*)t->msg_box;
	if (tmsg->type == 0)
		memcpy (t->msg_box,msg,sizeof(postmsg_t));

	if (t->state == THREAD_STATE_BLOCKED){
		unblock_thread(t);
	}
}

/**
 * The receiving part is handled in user-space as this reduces the number of system call
 * Every Message box is mapped to a higher memory area with user accessible bit on, so
 * user space can simply copy the message and clear the message box from user level
 */
