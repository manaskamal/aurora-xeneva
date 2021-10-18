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
	int max;
	int min;
	int position; //slider object position
	int type;
}QuSlider;

extern QuSlider * QuCreateSlider (int x, int y, int type);
#endif