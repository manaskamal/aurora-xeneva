/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  _term.h -- Kernel Debug Terminal Calls
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ============================================
 */

#ifndef __TERM_H__
#define __TERM_H__

#include <sys\_xeneva.h>

//#ifdef __cplusplus
//XE_EXTERN {
//#endif
XE_EXTERN XE_EXPORT void sys_print_text (const char* text, ...);
XE_EXTERN XE_EXPORT int sys_ttype_create (int* master_fd, int* slave_fd);
XE_EXTERN XE_EXPORT void sys_attach_tty (int id);
XE_EXTERN XE_EXPORT void _term_putchar_ (unsigned char *c);
//#ifdef __cplusplus
//}
//#endif

#endif