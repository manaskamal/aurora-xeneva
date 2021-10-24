///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuSlider.cpp -- Slider Widget
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!===============================================

#include <QuSlider.h>
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>
#include <QuPanel.h>

void QuSliderRefresh (QuWidget *wid, QuWindow *win) {
	QuSlider *slider = (QuSlider*)wid;

	if (slider->type == QU_SLIDER_VERTICAL) {
		acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y, wid->width, wid->height, LIGHTSILVER);
		acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y, wid->width, wid->height, GRAY);

		///!Slider Thumb
		acrylic_draw_rect_filled (win->x + wid->x - slider->thumb_x + (wid->width/2) - (wid->width +2)/2,   //X
			win->y + wid->y + slider->thumb_y + wid->height - 15,               //Y
			wid->width + 2, 15,LIGHTSILVER);
		acrylic_draw_rect_unfilled (win->x + wid->x - slider->thumb_x + (wid->width/2) - (wid->width +2)/2,   //X
			win->y + wid->y +slider->thumb_y + wid->height - 15,               //Y
			wid->width + 2, 15,GRAY);
	}
}


void QuSliderMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked, int x, int y) {
	QuSlider *slider = (QuSlider*)wid;
	if (code == QU_EVENT_MOUSE_ENTER){
	if (clicked) {
		slider->thumb_x = x;
		slider->thumb_y = y;
		QuSliderRefresh(wid, win);
		QuPanelUpdate(slider->wid.x, slider->wid.y, slider->wid.width, slider->wid.height, false);
	}
	}
}



QuSlider * QuCreateSlider (int x, int y, int type) {
	QuSlider *slider = (QuSlider*)malloc(sizeof(QuSlider));
	slider->wid.x = x;
	slider->wid.y = y;
	if (type == QU_SLIDER_VERTICAL) {
		slider->wid.width = 10;
		slider->wid.height = 100;
	}else if (type == QU_SLIDER_HORIZONTAL) {
		slider->wid.width = 100;
		slider->wid.height = 10;
	}
	slider->wid.MouseEvent = QuSliderMouseEvent;
	slider->wid.KeyEvent = 0;
	slider->wid.ActionEvent = 0;
	slider->wid.Refresh = QuSliderRefresh;
	slider->wid.ScrollEvent = NULL;
	slider->max = 0;
	slider->min = 0;
	slider->position = 0;
	slider->type = type;
	slider->thumb_x = 0;
	slider->thumb_y = 0;
	return slider;
}