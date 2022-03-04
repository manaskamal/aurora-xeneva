/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  serial.h -- Serial Port 
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__

extern void initialize_serial ();
extern void write_serial (char a);
extern void debug_serial (char* string);
extern void _debug_print_ (char* format, ...);
extern bool is_serial_initialized();
#endif