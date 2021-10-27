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

	//* The Vertical slider *//
	if (slider->type == QU_SLIDER_VERTICAL) {
		acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y, wid->width, wid->height, LIGHTSILVER);
		acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y, wid->width, wid->height, GRAY);

		///!Progress
		if (slider->progress != 0)
			acrylic_draw_rect_filled (win->x + wid->x + 1, win->y + wid->y + slider->progress,
			9,(win->y + wid->y + wid->height) - (win->y + wid->y + slider->progress),DESKBLUE );

		///!Slider Thumb
		acrylic_draw_rect_filled (win->x + wid->x,   //X
			win->y + wid->y + slider->thumb_y  /*+ wid->height - 15*/,               //Y
			wid->width, 15,LIGHTBLACK);
		acrylic_draw_rect_unfilled (win->x + wid->x,   //X
			win->y + wid->y +slider->thumb_y /*+ wid->height - 15*/,               //Y
			wid->width, 15,GRAY);
	}


	//* The Horizontal Slider *//
	if (slider->type == QU_SLIDER_HORIZONTAL) {
		acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y, wid->width, wid->height, LIGHTSILVER);
		acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y, wid->width, wid->height, GRAY);

		///!Progress
		if (slider->progress != 0)
			acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y + 1,
			(win->x + wid->x + slider->progress) - (win->x + wid->x),9, DESKBLUE );

		///!Slider Thumb
		acrylic_draw_rect_filled (win->x + wid->x + slider->thumb_x,   //X
			win->y + wid->y  /*+ wid->height - 15*/,               //Y
			15, wid->height,LIGHTBLACK);
		acrylic_draw_rect_unfilled (win->x + wid->x + slider->thumb_x,   //X
			win->y + wid->y/*+ wid->height - 15*/,               //Y
			15, wid->height,GRAY);
	}
}


/*
 * QuSliderMouseEvent -- Called whenever mouse event occurs on this widget
 */
void QuSliderMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked, int x, int y) {
	QuSlider *slider = (QuSlider*)wid;

	//! check for mouse enter code
	if (code == QU_EVENT_MOUSE_ENTER){
		if (clicked) {

			/* for vertical everything is upside down */
			if (slider->type == QU_SLIDER_VERTICAL) {
				slider->thumb_y = y - (win->y + wid->y + 15 / 2);
			    slider->progress = slider->thumb_y;

				//! Update the current values
				if (slider->thumb_y < slider->last_thumb_y){
					slider->c_val += slider->unit;
					if (slider->c_val == slider->max)
						slider->c_val = slider->max;
				}else if (slider->last_thumb_y < slider->thumb_y) {
					slider->c_val -= slider->unit;
					if (slider->c_val == slider->min)
						slider->c_val = slider->min;
				}


				if ((win->y + wid->y + slider->thumb_y) <= (win->y + wid->y)){
					slider->thumb_y = 0;
				}

				if ((win->y + wid->y + slider->thumb_y + 15) >= (win->y + wid->y + wid->height)){
					slider->thumb_y = (win->y + wid->y + wid->height) - (win->y + wid->y + 15);
					slider->progress = 0;
				}

				slider->last_thumb_y = slider->thumb_y;
				QuSliderRefresh(wid, win);
				QuPanelUpdate(win->x + slider->wid.x - 12,win->y +  slider->wid.y, slider->wid.width + 12, slider->wid.height, false);
			}

			/* normal horizontal slider */
			if (slider->type == QU_SLIDER_HORIZONTAL) {
				slider->thumb_x = x - (win->x + wid->x + 15 / 2);
				slider->progress = slider->thumb_x;

				/**
				 *  Update the current values
				 */
				if (slider->thumb_x > slider->last_thumb_x) {
					slider->c_val += slider->unit;
					if (slider->c_val == slider->max)
						slider->c_val = slider->max;
				}else if (slider->last_thumb_x > slider->thumb_x) {
					slider->c_val -= slider->unit;
					if (slider->c_val == slider->min)
						slider->c_val = slider->min;
				}

				//! Limit the slider's thumb here
				if ((win->x + wid->x + slider->thumb_x) <= (win->x + wid->x)){
					slider->thumb_x = 0;
					slider->progress = 0;
				}

				if ((win->x + wid->x + slider->thumb_x + 15) >= (win->x + wid->x + wid->width)) {
					slider->thumb_x = (win->x + wid->x + wid->width) - (win->x + wid->x + 15);
				}

				//! update the last thum pos
				slider->last_thumb_x = slider->thumb_x;

				//! Refresh
				QuSliderRefresh(wid, win);
				QuPanelUpdate(win->x + slider->wid.x,win->y +  slider->wid.y, slider->wid.width, slider->wid.height, false);

			}
		}
	}

}



QuSlider * QuCreateSlider (int x, int y,int length, int unit,int type) {
	QuSlider *slider = (QuSlider*)malloc(sizeof(QuSlider));
	slider->wid.x = x;
	slider->wid.y = y;
	if (type == QU_SLIDER_VERTICAL) {
		slider->wid.width = 10;
		slider->wid.height = length;
		slider->thumb_y = slider->wid.height - 15;
	}else if (type == QU_SLIDER_HORIZONTAL) {
		slider->wid.width = length;
		slider->wid.height = 10;
		slider->thumb_x = 0;
	}
	slider->wid.MouseEvent = QuSliderMouseEvent;
	slider->wid.KeyEvent = 0;
	slider->wid.ActionEvent = 0;
	slider->wid.Refresh = QuSliderRefresh;
	slider->wid.ScrollEvent = NULL;
	slider->max = 0;
	slider->min = 0;
	slider->progress = 0;
	slider->type = type;
	slider->c_val = 0;
	slider->unit = unit;
	slider->last_thumb_x = 0;
	slider->last_thumb_y = 0;
	return slider;
}

void QuSliderSetMaxMin (QuSlider *slider,int min, int max) {
	slider->min = min;
	slider->max = max;
	slider->c_val = slider->min;
}

void QuSliderSetUnit (QuSlider *slider, int unit) {
	slider->unit = unit;
}