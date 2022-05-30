/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * _exit -- Terminates a process and return its 
 *  return code to parent process
 *
 * /PROJECT - Aurora's Xeneva
 * /AUTHOR  - Manas Kamal Choudhury 
 *
 *=============================================
 */

#ifndef __EXIT_H__
#define __EXIT_H__

#include <sys\_xeneva.h>

#pragma once

#ifdef __cplusplus
XE_EXTERN {
#endif
XE_EXPORT void sys_exit ();
#ifdef __cplusplus
}
#endif

#endif