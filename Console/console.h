/**
 *  Copyright (C) Manas Kamal Choudhury 2022
 *
 *  console.h -- Console widget
 *
 */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdint.h>
#include <daisy_widget.h>
#include <daisy_window.h>

#define NUMBER_OF_COLUMN  80
#define NUMBER_OF_ROW     25
#define DEFAULT_BUF_SZ    (NUMBER_OF_COLUMN*NUMBER_OF_ROW)


typedef struct _console_ {
	daisy_widget_t base;
	int cell_width;    
	int cell_height;
	char* buffer;
	int cursor_x;
	int cursor_y;
	int font_x;
	int font_y;
}console_t;


extern console_t * create_console_widget (int x, int y, int w, int h);


#endif