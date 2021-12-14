/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  procmngr -- Process Manager thread
 *
 *  /PROJECT - Aurora Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#ifndef __PROC_MNGR_H__
#define __PROC_MNGR_H__

#include <stdint.h>
#include <stdio.h>

#define PROCESS_CREATE 1
#define PROCESS_DESTROY 2
//!procmngr queue
typedef struct _procmngr_queue_ {
    char name[8];
    char path[50];
	uint8_t type;
	uint16_t id;
	struct _procmngr_queue_ *link;
}procmngr_queue;


extern void procmngr_add_process (procmngr_queue *queue);
extern procmngr_queue* procmngr_get_process ();
extern void procmngr_start ();
extern void procmngr_wakeup ();


#endif