/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @priwm.h -- priyanshi's window manager header
 *
 **/

#include "priwm.h"
#include <stdint.h>

#include <sys/_wait.h>
#include <sys/_xeneva.h>
#include <sys/_file.h>
#include <sys/ioquery.h>
#include <acrylic.h>
#include <canvas.h>
#include <font.h>
#include <color.h>
#include <sys/_term.h>

canvas_t* canvas;

int main (int argc, char* argv[]) {
	int svga_fd = sys_open_file ("/dev/fb", NULL);
	
	uint32_t s_width = ioquery(svga_fd,SCREEN_GETWIDTH,NULL);
	uint32_t s_height = ioquery(svga_fd, SCREEN_GETHEIGHT, NULL);
	
	canvas = create_canvas (s_width,s_height);
	int w = canvas_get_width(canvas);
	int h = canvas_get_height(canvas);
	
	acrylic_initialize_font();

	acrylic_draw_rect_filled (canvas, 0,0,s_width, s_height, WHITE);
	acrylic_font_set_size (20);
	int length = acrylic_font_get_length ("PriWM 1.0");
	int height = acrylic_font_get_height ("PriWM 1.0");
	acrylic_font_draw_string (canvas, "PriWM 1.0", s_width / 2 - length / 2, s_height / 2 - height / 2,20,BLACK);

	canvas_screen_update(canvas, 0, 0, s_width, s_height);

	while (1) {
		sys_wait();
	}
}