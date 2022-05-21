

#include <ipc\pointdev.h>
#include <atomic\mutex.h>
#include <utils\lnklist.h>
#include <utils\circ_buf.h>
#include <stdio.h>

thread_t *window_manager_thr = NULL;

//! Mouse Code
#define MOUSE_IOCODE_DISABLE   300
#define MOUSE_IOCODE_ENABLE    301
#define MOUSE_REGISTER_WM      302

/**  Mouse IOQuery function **/
int mouse_ioquery (vfs_node_t *node, int code, void* arg) {
	x64_cli();
	switch (code) {
		case MOUSE_IOCODE_DISABLE:
			AuIrqMask(12,true);
			break;
		case MOUSE_IOCODE_ENABLE:
			AuIrqMask(12, false);
			break;
		case MOUSE_REGISTER_WM:
			window_manager_thr = get_current_thread();
			break;
		default:
			break;
	}

	return 1;
}


/*
 *  Read current pointer message
 */
void AuPointerRead (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	x64_cli();
	printf ("Reading Pointer \n");
	thread_t* t = get_current_thread();
	memcpy (buffer, t->msg_box, sizeof(dwm_message_t));
}


/*
 * AuPointDevInitialize -- Initialize the Pointer Manager
 */
void AuPointDevInitialize () {
	void* p = AuPmmngrAlloc();
	memset(p, 0, 4096);
	AuMapPage((uint64_t)p,0xFFFFFD0000000000, PAGING_USER);
	void *p2 = AuPmmngrAlloc();
	memset(p2, 0, 4096);
	AuMapPage((uint64_t)p2,0xFFFFD00000000000,PAGING_USER);
	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy (node->filename, "mouse");
	node->size = 0;
	node->eof = 0;
	node->pos = 0;
	node->current = 0;
	node->flags = FS_FLAG_GENERAL;
	node->status = 0;
	node->open = 0;
	node->read = AuPointerRead;
	node->write = 0;
	node->read_blk = 0;
	node->ioquery = mouse_ioquery;
	vfs_mount ("/dev/mouse", node, 0);
	window_manager_thr = NULL;
}


/*
 * PointDevPutMessage -- puts a mouse message window manager
 * @param msg -- mouse msg
 */
void PointDevPutMessage(dwm_message_t *msg) {
	if (!is_multi_task_enable())
		return;

	if (window_manager_thr == NULL)
		return;

	thread_t *t  = thread_iterate_ready_list (window_manager_thr->id);   //!ready list
	if (t == NULL) {
		t = thread_iterate_block_list(window_manager_thr->id);
	}
	dwm_message_t *tmsg = (dwm_message_t*)t->msg_box;
	if (tmsg->type == 0)
		memcpy (t->msg_box,msg,sizeof(dwm_message_t));
}

