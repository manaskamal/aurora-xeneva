/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  _sleep.h -- Put the process into sleep mode for
 *              certain period of time
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ======================================================
 */

#ifndef __SLEEP_H__
#define __SLEEP_H__

#include <sys\_xeneva.h>

/************************************************
 *  Put process into sleep mode
 *
 *  @ms -- time period in milliseconds
 *
 *===============================================
 */

#ifdef __cplusplus
XE_EXTERN {
#endif
XE_EXPORT void sys_sleep (unsigned long long ms);
#ifdef __cplusplus
}
#endif
#endif