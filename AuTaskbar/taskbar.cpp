///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   taskbar.h -- Taskbar feature
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================

#include <acrylic.h>
#include "taskbar.h"
#include <QuPanel.h>
#include <string.h>
#include <color.h>

int pos_x = 20;

void start_taskbar () {
	acrylic_draw_rect_filled (0, canvas_get_height() - 40, canvas_get_width(), 40, 0x8C3E3E3E);
	QuPanelUpdate (0, canvas_get_height() - 40, canvas_get_width(), 40);	
}

void add_taskbar_button(char *text) {
	acrylic_draw_rect_filled (pos_x, canvas_get_height() - 35,100,30,0x8C3E3E3E);
	acrylic_draw_rect_unfilled (pos_x, canvas_get_height() - 35, 100, 30,0xD9FFFFFF);

	acrylic_draw_arr_string (pos_x + 100/2 - (strlen(text)*8)/2,
		canvas_get_height() - 35 + 30/2 - 12/2,
		text, 
		0xD9FFFFFF);

	QuPanelUpdate (pos_x, canvas_get_height() - 35,100,30);
	pos_x += 130;
}

void taskbar_print_date_time (uint8_t sec, uint8_t min, uint8_t hr) {
	acrylic_draw_rect_filled (canvas_get_width() - 100, canvas_get_height() - 35,100,30,0x8C3E3E3E);
	acrylic_draw_rect_unfilled (canvas_get_width() - 100, canvas_get_height() - 35, 100, 30,0xD9FFFFFF);

	char _sec[2];
	char _min[2];
	char _hour[2];

	sztoa(sec,_sec,10);
	sztoa(min,_min, 10);
	sztoa(hr,_hour, 10);


	acrylic_draw_arr_string (canvas_get_width() - 100 + 100/2 - (strlen(_hour)*8)/2 - 16,
		canvas_get_height() - 35 + 30/2 - 12/2,
		_hour, 
		0xD9FFFFFF);

	acrylic_draw_arr_string (canvas_get_width() - 100 + 100/2 - (strlen(_min)*8)/2,
		canvas_get_height() - 35 + 30/2 - 12/2,
		_min, 
		0xD9FFFFFF);

	acrylic_draw_arr_string (canvas_get_width() - 100 + 100/2 - (strlen(_sec)*8)/2 + 19,
		canvas_get_height() - 35 + 30/2 - 12/2,
		_sec, 
		0xD9FFFFFF);

	QuPanelUpdate (canvas_get_width() - 100, canvas_get_height() - 35,100,30);
}