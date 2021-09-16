///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///! 
///!  QuTaskbar.cpp --- Quince Taskbar
///! 
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!================================================

#include <QuWidget\QuTaskbar.h>
#include <acrylic.h>
#include <stdint.h>
#include <canvas.h>

uint32_t task_bar_colors[35] = {0xff59584f, 0xff5f5d53, 0xff58564e, 0xff57554d, 0xff56544c, 0xff55534b, \
    0xff54524a, 0xff525049, 0xff514f48, 0xff504e47, 0xff4e4c45, 0xff4e4c45, \
        0xff4c4a44, 0xff4b4943, 0xff4a4842, 0xff484741, 0xff46453f, 0xff45443f, \
        0xff44433e, 0xff43423d, 0xff42413c, 0xff403f3a, 0xff3f3e3a, 0xff2b2a26, 0xff201f1c, 0xff1b1a16, \
        0xff161513, 0xff0f0e0b, 0xff0f0e0b, 0xff0f0e0b, 0xff0f0e0b, 0xff0f0e0b, 0xff0f0e0b, 0xff0f0e0b, \
        0xff0f0e0b};

void QuTaskbarInit () {

	unsigned y = canvas_get_height() - 35;
	for (int i = 0; i < 35; i++) {
		acrylic_draw_horizontal_line(0, y+ i, canvas_get_width(),task_bar_colors[i]);
	}

}