///! Copyright (C) Manas Kamal Choudhury 2021
///! 
///! QuPanel -- Main Client Area where GUI Object sits
///!
///! /PROJECT - Aurora's Xeneva
///! /AUTHOR  - Manas Kamal Choudhury
///!
///!====================================================

#ifndef __QU_PANEL_H__
#define __QU_PANEL_H__

#include <stdint.h>

typedef struct _QuPanel_ {
	unsigned x;
	unsigned y;
	unsigned w;
	unsigned h;
	uint32_t* panel_data;
}QuPanel;

extern QuPanel *QuCreatePanel();
extern void QuPanelUpdate(unsigned x, unsigned y, unsigned w, unsigned h);


#endif