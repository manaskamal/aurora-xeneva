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

#define QU_CHANNEL_ADDRESS  0xFFFFFD0000000000
uint32_t * QuCanvasAddress = NULL;
uint16_t app_id = 0;

void QuChannelPut (QuMessage *msg, uint16_t to_id) {
	uint16_t from_id = get_current_pid ();
	QuMessage* channel_addr = (QuMessage*)QU_CHANNEL_ADDRESS;
	msg->from_id = from_id;
	msg->to_id = to_id;
	if (channel_addr->type == 0)
		memcpy (channel_addr, msg, (sizeof(QuMessage)));
}

void QuChannelGet (QuMessage *msg) {
	QuMessage* data = (QuMessage*)QU_CHANNEL_ADDRESS;
	uint16_t to_id = app_id;
	if (data->to_id == to_id){
		memcpy (msg, data, sizeof (QuMessage));
		memset (data, 0, 4096);
	}
}

void QuRegisterApplication () {
	create_canvas();
	app_id = get_current_pid();
	QuMessage qmsg;
	//qmsg.type = QU_CODE_WIN_CREATE;
	//QuChannelPut (&qmsg, 2);*/
	message_t msg;
	msg.type = QU_CODE_WIN_CREATE;
	msg.dword = app_id;
	message_send (2,&msg);
	memset (&msg, 0, sizeof(message_t));
	for (;;) {
		QuChannelGet(&qmsg);

		if (qmsg.type == QU_CANVAS_READY) {
			QuCanvasAddress = qmsg.p_value;
			QuCreateWindow (qmsg.dword, qmsg.dword2, qmsg.dword3, qmsg.dword4);
			QuWindowSetCanvas(QuCanvasAddress);
			memset (&qmsg, 0, sizeof(QuMessage));
			break;
		}
	}
}

