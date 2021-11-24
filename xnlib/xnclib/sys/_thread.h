/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  _thread.h -- Thread Creation and Termination header
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ========================================================
 */

#ifndef __THREAD_H__
#define __THREAD_H__

/**********************************************************
 ** Create a user level thread
 **
 ** @entry --> entry of the function
 ** @name  --> Name of the thread
 **
 **********************************************************
 */
#ifdef __cplusplus
extern "C" {
#endif
void create_uthread (void (*entry)(), char* name);
#ifdef __cplusplus
}
#endif
#endif