///   Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuSlider.h -- Slider Widget
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#ifndef __QU_SLIDER_H__
#define __QU_SLIDER_H__

#include <stdint.h>
#include <QuWindow.h>

#define QU_SLIDER_HORIZONTAL 1
#define QU_SLIDER_VERTICAL   2

typedef struct _QuSlider_ {
	QuWidget wid;
	int thumb_x;
	int thumb_y;
	int last_thumb_x;
	int last_thumb_y;
	int max;
	int min;
	int unit;
	int c_val;
	int progress; //slider object position
	int type;
}QuSlider;

extern QuSlider * QuCreateSlider (int x, int y,int length, int unit, int type);
extern void QuSliderSetMaxMin (QuSlider *slider,int min, int max);
extern void QuSliderSetUnit (QuSlider *slider, int unit);
#endif