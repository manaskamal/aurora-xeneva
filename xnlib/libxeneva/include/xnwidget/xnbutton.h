/**
 ** Copyright (C) Manas Kamal Choudhury 2021
 **
 ** xnbutton.h -- Xeneva Button Widget
 **
 ** /PROJECT - Aurora {Xeneva}
 ** /AUTHOR  - Manas Kamal Choudhury
 **
 ** ===========================================
 **/

#ifndef __XN_BUTTON_H__
#define __XN_BUTTON_H__

#include <xnwidget\xnwidget.h>
#include <xnwidget\xnwindow.h>


typedef void (*button_action) (struct _xn_button_ *button);

typedef struct _xn_button_ {
	xn_widget base;
	button_action on_button_pressed;
	bool button_toogle;
	char *text;
}xn_button_t;

extern xn_button_t *xn_create_button (int x, int y, int w, int h, char* title);


#endif