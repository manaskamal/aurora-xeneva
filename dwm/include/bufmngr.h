/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  bufmngr.h -- Buffer Manager
 *
 *  /PROJECT - DWM {Desktop Window Manager}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#ifndef __BUFMNGR_H__
#define __BUFMNGR_H__

#include <stdtypes.h>

//initialize the buffer manager
extern void initialize_buffer_manager ();
//! request a buffer 
extern uint32_t* request_buffer (uint16_t dest_id);
#endif