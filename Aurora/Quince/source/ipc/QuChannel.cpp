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

//! QuChannel address
#define QU_CHANNEL_ADDRESS  0xFFFFFD0000000000


void QuChannelPut (QuMessage *msg, uint16_t to_id) {
	uint16_t from_id = 2; //get_current_pid ();
	QuMessage* channel_addr = (QuMessage*)QU_CHANNEL_ADDRESS;
	msg->from_id = from_id;
	msg->to_id = to_id;
	memcpy (channel_addr, msg, (sizeof(QuMessage)));
}



void QuChannelGet (QuMessage *msg) {
	QuMessage* data = (QuMessage*)QU_CHANNEL_ADDRESS;
	uint16_t to_id = get_current_pid ();
	if (data->to_id == to_id){
		memcpy (msg, data, sizeof (QuMessage));
		memset (data, 0, 4096);
	}
}


