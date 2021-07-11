/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * xnlabel.h -- XNLabel widget
 *
 * /PROJECT - Aurora Xeneva v1.0
 * /AUTHOR  - Manas Kamal Choudhury
 *
 *=================================================
 */

#ifndef __XNLABEL_H__
#define __XNLABEL_H__

#include <xnwidget\xnwidget.h>
#include <gui\drawer.h>
#include <gui\font.h>
#include <xnwidget\geom_rect.h>
#include <xnwidget\xnwindow.h>

#define LABEL_OUTLINE_FILLED 1
#define LABEL_OUTLINE_UNFILLED 2

typedef struct _xn_label_ {
	xn_widget base;
	char *label;
	int outline_type;
}xn_label_t;

extern xn_label_t *xn_create_label (int x, int y, int w, int h,int outline_type, char *label);

#endif