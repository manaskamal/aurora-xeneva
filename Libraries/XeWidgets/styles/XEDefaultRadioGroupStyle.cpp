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

#include <styles\XEDefaultRadioGroupStyle.h>
#include <acrylic.h>
#include <color.h>
#include <xeradiogroup.h>
#include <string.h>
#include <font.h>

/* XEDefaultRadioGroupPainter -- Paints  radio buttons in default style
 * @param widget -- Pointer to the Button Widget
 * @param window -- Pointer to main activity window
 */
void XEDefaultRadioGroupPainter (XEWidget *widget, XEWindow *window) {
	XERadioGroup *rg = (XERadioGroup*)widget;

	/* Calculate the width and height of radio group along with
	 * boundary height and width of radio buttons*/
	if (widget->w == 0 && widget->h == 0) {
		if (rg->radio_buttons->pointer > 0) {
			for (int i = 0; i < rg->radio_buttons->pointer; i++) {
				XERadioButton *rb = (XERadioButton*)list_get_at(rg->radio_buttons, i);
				int length = acrylic_font_get_length(rb->label);
				int height = acrylic_font_get_height(rb->label);
				/* w*2 and h*2 because radio button holds the radius
				 * of the circle which is converted to diameter of 
				 * the button */
				rb->bound_width = rb->base.w*2 + length + 10;
				rb->bound_height = rb->base.h*2 + 1;
				if (rb->base.w*2 + length + 10 > widget->w) 
					widget->w = rb->base.w*2 + length + 10;
				widget->h += rb->base.h*2 + height + 16;
			}
		}
	}

	/* Finally calculate the x-position and y-position of each
	 * radio buttons related to the radio group box
	 */
	int radio_button_pos_x = widget->x + widget->w / 2;
	int radio_button_pos_y = widget->y + 16;
	for (int i = 0; i < rg->radio_buttons->pointer; i++) {
		XERadioButton *rb = (XERadioButton*)list_get_at(rg->radio_buttons, i);
		int label_length = acrylic_font_get_length(rb->label);
		rb->base.x = radio_button_pos_x - rb->bound_width/2 + rb->base.w*2;
		rb->base.y = radio_button_pos_y  + rb->base.h;
		radio_button_pos_y += rb->base.h * 2 + 4;
		rb->base.painter((XEWidget*)rb,window);
	}

	/* Draw the radio group label and radio group box */
	acrylic_font_set_size(9);
	int label_l = acrylic_font_get_length(rg->label);
	int label_h = acrylic_font_get_height(rg->label);
	acrylic_draw_rect_unfilled(window->ctx, widget->x, widget->y, widget->w, widget->h, LIGHTSILVER);
	acrylic_font_draw_string(window->ctx, rg->label, widget->x + widget->w/2 - label_l/2,widget->y + label_h,9,GRAY);
	
}
