/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  evntsh -- Shared Event for Mouse enhancement
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#include <ipc\evntsh.h>
#include <pmmngr.h>

void initialize_event_shared () {
	uint64_t *physical_frame = (uint64_t*)pmmngr_alloc();
	map_page((uint64_t)physical_frame,0xFFFFD00000000000);

}

//!share a data packet
void event_shared_push_data(mail_t data) {
	uint64_t* data_ = (uint64_t*)0xFFFFD00000000000;
	//!Prepare the message packet to transfer
	data_[1] = data.byte;  
	data_[2] = data.byte2;
	data_[3] = data.dword;
	data_[4] = data.dword2;
	data_[5] = data.quad;
	data_[6] = data.quad2;
	data_[7] = data.quad3;
	data_[8] = data.quad4;
	data_[9] = data.quad5;
	data_[10] = data.quad6;
}
