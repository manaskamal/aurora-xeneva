///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   hwcursor.h -- Hardware accelerated cursor manager
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!==========================================================

#ifndef __HWCURSOR_H__
#define __HWCURSOR_H__

#include <stdint.h>
#include <drivers\svga\vmsvga.h>

//! hw_move_cursor -- Hardware accelerated cursor movement
//! @param mouse_image -- Cursor Image data
//! @param xcoord -- X Coordinate of the screen
//! @param ycoord -- Y Coordinate of the screen
extern void hw_move_cursor (uint32_t* mouse_image, uint32_t xcoord, uint32_t ycoord);
#endif