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
#include <QuWindow.h>
#include <canvas.h>
#include <sys\_ipc.h>
#include <sys\_term.h>
#include <sys\_wait.h>
#include <sys\_sleep.h>
#include <psf\psf.h>
#include <acrylic.h>

#define QU_CHANNEL_ADDRESS   0xFFFFD00000000000  //Client Send address
#define QU_CHANNEL_RECEIVER  0xFFFFFD0000000000  //Client receiver address

uint32_t * QuCanvasAddress = NULL;
uint16_t app_id = 0;

void QuChannelPut (QuMessage *msg, uint16_t to_id) {
	uint16_t from_id = app_id;
	void* channel_addr = (void*)QU_CHANNEL_ADDRESS;
	QuMessage *msg_ = (QuMessage*)channel_addr;
	msg->from_id = from_id;
	msg->to_id = to_id;
send:
	if (msg_->type == 0){
		memcpy (channel_addr, msg, (sizeof(QuMessage)));
		return;
	}else {
		sys_sleep(2);
		goto send;
	}
	
}

void QuChannelGet (QuMessage *msg) {
	QuMessage* data = (QuMessage*)QU_CHANNEL_RECEIVER;
	uint16_t to_id = app_id;
get:
	if (data->to_id == to_id){
		memcpy (msg, data, sizeof (QuMessage));
		memset (data, 0, 4096);
		return;
	}else {
		//sys_wait();
		goto get;
	}
}

void QuRegisterApplication (char* title) {
	app_id = get_current_pid();

	QuMessage qmsg;
	qmsg.type = QU_CODE_WIN_CREATE;
	qmsg.from_id = app_id;
	qmsg.to_id = 2;
	QuChannelPut(&qmsg, 2);

	int win_def_x, win_def_y, win_def_w, win_def_h = 0;
	uint32_t* info_data;
	memset(&qmsg, 0, sizeof(QuMessage));
	while(1) {
		QuChannelGet(&qmsg);

		if (qmsg.type == QU_CANVAS_READY) {
			QuCanvasAddress = qmsg.p_value;
			win_def_x = qmsg.dword;
			win_def_y = qmsg.dword2;
			win_def_w = qmsg.dword3;
			win_def_h = qmsg.dword4;
			info_data = qmsg.p_value2;
			//memset (&qmsg, 0, sizeof(qu_message_t));
			break;
		}
	}

	message_t msg;
	msg.type = 1;
	strcpy (msg.buffer, title);
	message_send (4,&msg);
	//sys_unblock_id(4);
	sys_sleep(2);
//	canvas_set_double_buffer(e);
	create_canvas();
	canvas_set_address (QuCanvasAddress);
	QuCreateWindow (win_def_x, win_def_y, win_def_w, win_def_h, info_data, title);
	QuWindowSetCanvas (QuCanvasAddress);
}


uint16_t QuGetAppId() {
	return app_id;
}

