///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!  
///!  QuChannel --- Quince Communication Channel
///! 
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury 
///!
///! =================================================

#include <ipc\QuChannel.h>
#include <sys\_process.h>
#include <string.h>
#include <sys\_term.h>
#include <stdlib.h>

//! QuChannel address
#define QU_CHANNEL_ADDRESS  0xFFFFFD0000000000  //Quince send address
#define QU_CHANNEL_RECEIVER 0xFFFFD00000000000  //Quince Receiver address

//!Stack for window compositor
typedef struct _Msgstack_ {
	QuMessage *msg;
	struct _Msgstack_ *link;
}QuMessageStack;

static QuMessageStack *msg_top = NULL;
static uint32_t msg_count = 0;


void QuChannelPut (QuMessage *msg, uint16_t to_id) {
	uint16_t from_id = 2; //get_current_pid ();
	QuMessage* channel_addr = (QuMessage*)QU_CHANNEL_ADDRESS;
	msg->from_id = from_id;
	msg->to_id = to_id;
	memcpy (channel_addr, msg, (sizeof(QuMessage)));
}

void QuChannelPushMessage (QuMessage *msg){
	QuMessageStack * s= (QuMessageStack*)malloc(sizeof(QuMessageStack));
	s->msg = msg;
	s->link = msg_top;
	msg_top = s;
	msg_count++;
}

//! Get a rect from stack
void QuMessageStackGetMsg(QuMessage *r) {
	if (msg_top == NULL)
		return;

	//QuMessage *r;
	QuMessageStack *temp;
	
	temp = msg_top;
	msg_top = msg_top->link;
	temp->link = NULL;
	r = temp->msg;
	free(temp);
	msg_count--;
}

uint32_t QuStackGetMsgCount () {
	return msg_count;
}

void QuChannelGet (QuMessage *msg) {
	QuMessage* data = (QuMessage*)QU_CHANNEL_RECEIVER;
	uint16_t to_id = get_current_pid ();
	if (data->to_id == to_id){
		memcpy (msg, data, sizeof(QuMessage));
		memset (data, 0, 4096);
	}
}


