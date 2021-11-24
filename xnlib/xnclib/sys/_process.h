/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  _process.h --Standard Process Creating and Termination 
 *               header
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ========================================================
 */

#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdint.h>
#include <sys\signal.h>

#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************
 ** Creates a process
 **
 ** @filename -- Path of the process
 ** @procnm   -- Name of the process
 **
 ****************************************************************
 */
void create_process (const char* filename, char* procnm);

/****************************************************************
 ** GetCurrentPID () - returns the current process id 
 ****************************************************************
 **/
unsigned int get_current_pid ();

//! Unblocks a thread from a certain process
//! @param id -- Process thread id
void sys_unblock_id (uint16_t id);

void sys_kill (int pid, int signo);
void sys_set_signal (int signo, sig_handler handler);

uint64_t sys_get_used_ram ();

#ifdef __cplusplus
}
#endif

#endif