/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xnmenu.h -- XN Menu Object
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#ifndef __XNMENU_H__
#define __XNMENU_H__

#include <xnwidget\xnwidget.h>
#include <xnwidget\geom_rect.h>
#include <gui\drawer.h>
#include <gui\colors.h>
#include <gui\font.h>

typedef struct _xn_menu_ {
	char *popup_title;
}xn_menu_t;

extern xn_menu_t *xn_create_menu (char* popup_title);

#endif