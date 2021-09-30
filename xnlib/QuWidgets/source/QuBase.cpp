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
		sys_sleep(16);
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
		sys_wait();
		goto get;
	}
}

void QuRegisterApplication () {
	canvas_set_double_buffer(false);
	create_canvas();
	//psf_register_font_lib();


	app_id = get_current_pid();
	QuMessage qmsg;
	qmsg.type = QU_CODE_WIN_CREATE;
	QuChannelPut (&qmsg, 2);
	/*message_t msg;
	msg.type = QU_CODE_WIN_CREATE;
	msg.dword = app_id;
	message_send (2,&msg);*/
	memset (&qmsg, 0, sizeof(QuMessage));
	for (;;) {
		QuChannelGet(&qmsg);

		if (qmsg.type == QU_CANVAS_READY) {
			QuCanvasAddress = qmsg.p_value;
			canvas_set_address(QuCanvasAddress);
			QuCreateWindow (qmsg.dword, qmsg.dword2, qmsg.dword3, qmsg.dword4);
			QuWindowSetCanvas(QuCanvasAddress);
			memset (&qmsg, 0, sizeof(QuMessage));
			break;
		}
	}
}


uint16_t QuGetAppId() {
	return app_id;
}

