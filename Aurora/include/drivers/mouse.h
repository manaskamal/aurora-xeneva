/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  mouse.h -- PS/2 Mouse Device Driver
 *
 *  /PROJECT - Aurora {Xeneva v1.0}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===========================================
 */

#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <stdint.h>
#include <hal.h>
#include <stdio.h>

#define MOUSE_PORT   0x60
#define MOUSE_STATUS 0x64
#define MOUSE_ABIT   0x02
#define MOUSE_BBIT   0x01
#define MOUSE_WRITE  0xD4
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08

#define MOUSE_DEFAULT 0
#define MOUSE_SCROLLWHEEL 1
#define MOUSE_BUTTONS 2

#define MOUSE_LEFT_CLICK   		0x01
#define MOUSE_RIGHT_CLICK  		0x02
#define MOUSE_MIDDLE_CLICK 		0x04
#define MOUSE_MOUSE_SCROLL_UP   0x10
#define MOUSE_MOUSE_SCROLL_DOWN 0x20

//! Mouse Code
#define MOUSE_IOCODE_DISABLE   300
#define MOUSE_IOCODE_ENABLE    301

extern void AuInitializeMouse ();
#endif