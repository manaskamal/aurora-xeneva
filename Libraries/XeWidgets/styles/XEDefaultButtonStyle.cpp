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
 *
 **/

#include <styles\XEDefaultButtonStyle.h>
#include <acrylic.h>
#include <canvas.h>
#include <color.h>
#include <font.h>
#include <xebutton.h>

#define BUTTON_NORMAL_DARK 0xFF908988
#define BUTTON_NORMAL_LIGHT 0xFFD9D7D7
#define BUTTON_HOVER_DARK  0xFF9F9A9A
#define BUTTON_HOVER_LIGHT 0xFFCACACA


void XEDefaultButtonPainter(XEWidget *widget, XEWindow *window) {
	XEButton *but = (XEButton*)widget;

	uint32_t color1 = BUTTON_NORMAL_LIGHT;
	uint32_t color2 = BUTTON_NORMAL_DARK;
	uint32_t color3 = color2;

	if (but->base.hover) {
		color1 = BUTTON_HOVER_LIGHT;
		color2 = BUTTON_HOVER_DARK;
		color3 = color2;
	}

	if (but->base.clicked) {
		color1 = BUTTON_HOVER_DARK;
		color2 = BUTTON_NORMAL_LIGHT;
		color3 = BUTTON_HOVER_DARK;
	}

	acrylic_draw_vertical_gradient(window->ctx,widget->x, widget->y, widget->w, widget->h,color1, color2);
	acrylic_font_set_size(11);
	int font_w = acrylic_font_get_length(but->title);
	int font_h = acrylic_font_get_height(but->title);
	acrylic_font_draw_string(window->ctx, but->title, widget->x + (widget->w/2) - font_w/2,widget->y + (widget->h/2)-font_h/2,
		11,BLACK);
	acrylic_draw_rect_unfilled(window->ctx, widget->x, widget->y, widget->w, widget->h, color3);
}