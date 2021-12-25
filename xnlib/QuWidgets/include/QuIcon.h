/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  QuIcon.h -- Qu Icon object
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */

#ifndef __QU_ICON_H__
#define __QU_ICON_H__

#include <QuWindow.h>
#include <QuImage\QuBmpImage.h>

typedef struct _qu_icon_h_ {
	QuWidget wid;
	QuBmpImage *bitmap;
	uint32_t icon_w;
	uint32_t icon_h;
}QuIcon;


extern QuIcon *QuCreateIcon (int x, int y);
extern void QuLoadIcon (QuIcon *icon, char *filename);
#endif