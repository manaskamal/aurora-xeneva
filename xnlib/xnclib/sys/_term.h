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

#ifdef __cplusplus
extern "C" {
#endif
void sys_print_text (const char* text, ...);
void sys_ttype_create (int* master_fd, int* slave_fd);
void sys_attach_tty (int id);
#ifdef __cplusplus
}
#endif

#endif