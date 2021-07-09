/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  dwmmsg.h -- Desktop Window Manager Message sender
 *
 *  /PROJECT - DWM {Desktop Window Manager}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *======================================================
 */

#ifndef __DWMMSG_H__
#define __DWMMSG_H__

#include <stdtypes.h>
#include <sys.h>


extern void dwmmsg_send(message_t* data);
extern void dwmmsg_receive (void* store);
#endif