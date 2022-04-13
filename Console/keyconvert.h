/**
 *  Copyright (C) Manas Kamal Choudhury 2022
 *
 *  keyconvert.h -- Keyboard to ascii converter
 *  
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *====================================================
 */

#ifndef __KEY_CONVERT_H__
#define __KEY_CONVERT_H__

#include <stdint.h>
#include <ctype.h>
#include <sys\_kybrd.h>


/**
 * key_convert_to_ascii -- converts a keyboard input
 * to ascii character
 * @param code -- key code
 */
extern char key_convert_to_ascii (int code);

#endif