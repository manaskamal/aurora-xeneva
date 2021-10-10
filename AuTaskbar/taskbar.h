///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   taskbar.h -- Taskbar feature
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================

#ifndef __TASKBAR_H__
#define __TASKBAR_H__

#include <stdint.h>

#define NEW_TASKBAR_BUTTON 1
#define DESTROY_TASKBAR_BUTTON 2
#define CLOCK_MESSAGE     10 

extern void start_taskbar ();
extern void add_taskbar_button(char *text);
extern void taskbar_print_date_time (uint8_t sec, uint8_t min, uint8_t hr);
#endif