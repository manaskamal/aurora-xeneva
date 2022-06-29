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

#include <styles\XEDefaultRadioButtonStyle.h>
#include <acrylic.h>
#include <color.h>
#include <canvas.h>
#include "xeradiobutton.h"
#include <font.h>

/* XEDefaultRadioButtonPainter -- Paints  radio buttons in default style
 * @param widget -- Pointer to the Button Widget
 * @param window -- Pointer to main activity window
 */
void XEDefaultRadioButtonPainter (XEWidget *widget, XEWindow *window) {
	XERadioButton *radio = (XERadioButton*)widget;
	acrylic_draw_filled_circle(window->ctx, widget->x, widget->y, widget->w, LIGHTSILVER);
	acrylic_draw_circle(window->ctx, widget->x, widget->y, widget->w, BLACK);
	acrylic_draw_circle(window->ctx, widget->x, widget->y, widget->w-1, BLACK);

	if (radio->is_true) {
		acrylic_draw_filled_circle (window->ctx, widget->x, widget->y, widget->w - 4, BLUE);
	}

	acrylic_font_set_size(9);
	acrylic_font_draw_string(window->ctx, radio->label, widget->x + 12, widget->y + 6, 9,BLACK);
	//acrylic_draw_rect_unfilled(window->ctx,widget->x-widget->w, widget->y-widget->h, widget->w*2 + length+10, widget->h*2, BLACK);

}