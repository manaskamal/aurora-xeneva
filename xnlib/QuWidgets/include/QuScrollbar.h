///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuScrollbar.h -- Quince Scrollbars 
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==============================================

#ifndef __QU_SCROLLBAR_H__
#define __QU_SCROLLBAR_H__

#include <stdint.h>
#include <QuWindow.h>
#include <QuBase.h>
 
/**
 * Scrollbar types
 */
#define QU_SCROLLBAR_HORIZONTAL  1
#define QU_SCROLLBAR_VERTICAL    2

/**
 * Scrollbar widget format
 */
typedef struct _qu_scrollbar_ {
	QuWidget wid;
	QuWidget *content;
	int type;
	int thumb_x;
	int thumb_y;
	int thumb_sz;
	int last_thumb_x;
	int last_thumb_y;
	int scroll_xoff;
	int scroll_yoff;
	bool update_off;
}QuScrollBar;

/**
 * QuCreateScrollbar -- Creates a scrollbar 
 * @param type -- Type of the scrollbar {QU_SCROLLBAR_HORIZONTAL or QU_SCROLLBAR_VERTICAL}
 * @param content -- The scrolling content
 */
extern QuScrollBar * QuCreateScrollbar (QuWidget* content, int type);

/**
 * QuScrollbar_SetThumbPos -- Set the button positions within the scrollbar
 *
 * @param scroll -- Pointer to Scrollbar widget
 * @param pos    -- position of the thumb within the bar
 */
extern void QuScrollbar_SetThumbPos (QuScrollBar *scroll, int pos);

/**
 * QuScrollBar_SetContent -- Set the contents which needs scrolling
 *
 * @param scroll -- Pointer to Scrollbar widget
 * @param content -- Pointer to content  widget
 *                   {Every contents do not support scrollbars,
 *                    supported by -- EditBox, ListView & ImageView                                    
 */
extern void QuScrollbar_SetContent (QuScrollBar *scroll, QuWidget *content);
#endif