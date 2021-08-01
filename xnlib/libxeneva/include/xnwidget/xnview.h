/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xnview.h -- XnView widget 
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===================================================
 */

#ifndef __XN_VIEW_H__
#define __XN_VIEW_H__

#include <xnwidget\xnwidget.h>
#include <xnwidget\geom_rect.h>
#include <gui\drawer.h>
#include <gui\colors.h>


#define XN_VIEW_FLAT  1
#define XN_VIEW_IMAGE 2


typedef struct _xn_view_ {
	xn_widget base;
	uint8_t type;
	unsigned char* image_data;
}xn_view_t;

extern xn_view_t * xn_create_view (uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t type, unsigned char* data);


#endif