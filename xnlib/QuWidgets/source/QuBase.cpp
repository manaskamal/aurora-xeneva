///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuBase.cpp -- Quince Base Object
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#include <QuBase.h>
#include <sys\_process.h>
#include <string.h>
#include <canvas.h>
#include <sys\_ipc.h>
#include <sys\_term.h>
#include <sys\_wait.h>
#include <sys\_sleep.h>
#include <psf\psf.h>
#include <acrylic.h>
#include <font.h>

uint16_t app_id = 0;
QuWindow *max_window[50];
int win_pointer = 0;


void QuChannelPut (QuMessage *msg, uint16_t to_id) {
	uint16_t from_id = get_current_pid(); //app_id;
	void* channel_addr = (void*)QU_CHANNEL_ADDRESS;
	QuMessage *msg_ = (QuMessage*)channel_addr;
	msg->from_id = from_id;
	msg->to_id = to_id;
send:
	if (msg_->type == 0){
		memcpy (channel_addr, msg, (sizeof(QuMessage)));
		sys_unblock_id(2);
		return;
	}else {
		//sys_sleep(2);
		goto send;
	}
	
}

void QuChannelGet (QuMessage *msg) {
	QuMessage* data = (QuMessage*)QU_CHANNEL_RECEIVER;
	uint16_t to_id = get_current_pid();//app_id;
get:
	if (data->to_id == to_id){
		memcpy (msg, data, sizeof (QuMessage));
		memset (data, 0, 4096);
		sys_unblock_id (2);
		return;
	}else {
		//sys_wait();
		goto get;
	}
}

void QuRegisterApplication (QuWindow *win) {
	app_id = get_current_pid();
    int window_id = 0;
	uint32_t* info_data;
	uint32_t* canvas_address = 0;

	QuMessage qmsg;
	qmsg.type = QU_CODE_WIN_CREATE;
	qmsg.from_id = app_id;
	qmsg.to_id = 2;
	qmsg.dword = win->temp_x;
	qmsg.dword2 = win->temp_y;
	qmsg.dword3 = win->w;
	qmsg.dword4 = win->h;
	QuChannelPut(&qmsg, 2);
	memset(&qmsg, 0, sizeof(QuMessage));
	while(1) {
		QuChannelGet(&qmsg);

		if (qmsg.type == QU_CANVAS_READY) {
			canvas_address = qmsg.p_value;
			window_id = qmsg.dword;
			info_data = qmsg.p_value2;
			memset (&qmsg, 0, sizeof(qu_message_t));
			break;
		}
	}

	win->winid = window_id;
	win->win_info_data = info_data;
	win->canvas = canvas_address;	
}


uint16_t QuGetAppId() {
	return get_current_pid();
}


void QuApplicationRegisterWindow (QuWindow *win) {
	max_window[win_pointer] = win;
	win_pointer++;
}


QuWindow* QuApplicationWindowGet (int id) {
	for (int i = 0; i < 50; i++) {
		QuWindow* win = max_window[i];
		if (win->winid == id)
			return win;
	}
}

