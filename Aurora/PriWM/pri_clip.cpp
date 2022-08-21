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
 * @priwm.h -- pri_window manager
 *
 **/

#include "pri_clip.h"
#include "pri_rect.h"
#include <string.h>


bool pri_value_in_range (int value, int min, int max) {
	return (value >= min) && (value <= max);
}

/* Check if two rectangle intersects
 * @param r1 -- rectangle one
 * @param r2 -- rectangle two
 */
bool pri_check_intersect (pri_rect_t *r1, pri_rect_t *r2) {

	bool xOverlap = pri_value_in_range(r1->x, r2->x, r2->x + r2->w) ||
		pri_value_in_range(r2->x, r1->x, r1->x + r1->w);

	bool yOverlap = pri_value_in_range(r1->y, r2->y, r2->y + r2->h) ||
		pri_value_in_range(r2->y, r1->y, r1->y + r1->h);

	return xOverlap && yOverlap;

}

/*
 * pri_calculate_clip_rects -- calculate visible rectanlges of current window
 * @param sub_rect -- subject rectangle
 * @param cut_rect -- cutting rectangle
 * @param list -- pointer to the list, where to store all
 * visible rectangles
 * @param count -- number of rectangles stored in the list
 */
void pri_calculate_clip_rects (pri_rect_t *sub_rect, pri_rect_t* cut_rect, pri_rect_t *list, int *count) {
	int s_top = sub_rect->y;
	int s_left = sub_rect->x;
	int s_bottom = sub_rect->y + sub_rect->h;
	int s_right = sub_rect->x + sub_rect->w;

	int c_top = cut_rect->y;
	int c_left = cut_rect->x;
	int c_bottom = cut_rect->y + cut_rect->h;
	int c_right = cut_rect->x + cut_rect->w;

	int r_count = 0;

	if (pri_rect_get_left(cut_rect) >= pri_rect_get_left(sub_rect) &&
		pri_rect_get_left(cut_rect) <= pri_rect_get_right(sub_rect)) {
		pri_rect_t r;
		pri_rect_set_top(&r, pri_rect_get_top(sub_rect));
		pri_rect_set_left(&r, pri_rect_get_left(sub_rect));
		pri_rect_set_bottom(&r, pri_rect_get_bottom(sub_rect));
		pri_rect_set_right(&r, pri_rect_get_left(cut_rect));


		list[r_count].x = r.x;
		list[r_count].y = r.y;
		list[r_count].w = r.w;
		list[r_count].h = r.h;
		r_count++;

		pri_rect_set_left(sub_rect,pri_rect_get_left(cut_rect));
	}

	if (pri_rect_get_top(cut_rect) >= pri_rect_get_top(sub_rect) && 
		pri_rect_get_top(cut_rect) <= pri_rect_get_bottom(sub_rect)) {

		pri_rect_t r;
		pri_rect_set_top(&r, pri_rect_get_top(sub_rect));
		pri_rect_set_left (&r, pri_rect_get_left(sub_rect));
		pri_rect_set_bottom(&r, pri_rect_get_top(cut_rect));
		pri_rect_set_right(&r, pri_rect_get_right(sub_rect));

		pri_rect_set_top(sub_rect, pri_rect_get_top(cut_rect));

		list[r_count].x = r.x;
		list[r_count].y = r.y;
		list[r_count].w = r.w;
		list[r_count].h = r.h;
		r_count++;
		s_top = c_top;
	}

	if (pri_rect_get_right(cut_rect) >= pri_rect_get_left(sub_rect)
		&& pri_rect_get_right(cut_rect) < pri_rect_get_right(sub_rect)) {

		pri_rect_t r;
		pri_rect_set_top(&r, pri_rect_get_top(sub_rect));
		pri_rect_set_left (&r, pri_rect_get_right(cut_rect));
		pri_rect_set_bottom(&r, pri_rect_get_bottom(sub_rect));
		pri_rect_set_right(&r, pri_rect_get_right(sub_rect));

		pri_rect_set_right(sub_rect, pri_rect_get_right(cut_rect));


		list[r_count].x = r.x;
		list[r_count].y = r.y;
		list[r_count].w = r.w;
		list[r_count].h = r.h;
		r_count++;
		s_right = c_right;
	}

	if (pri_rect_get_bottom(cut_rect) >= pri_rect_get_top(sub_rect)
		&& pri_rect_get_bottom(cut_rect) <= pri_rect_get_bottom(sub_rect)) {
		pri_rect_t r;
		pri_rect_set_top(&r, pri_rect_get_bottom(cut_rect));
		pri_rect_set_left (&r, pri_rect_get_left(sub_rect));
		pri_rect_set_bottom(&r, pri_rect_get_bottom(sub_rect));
		pri_rect_set_right(&r, pri_rect_get_right(sub_rect));

		pri_rect_set_bottom(sub_rect, pri_rect_get_bottom(cut_rect));

		list[r_count].x = r.x;
		list[r_count].y = r.y;
		list[r_count].w = r.w;
		list[r_count].h = r.h;
		r_count++;
		s_bottom = c_bottom;
	}

	*count = r_count;
}

void pri_blit_clip (canvas_t* dest, canvas_t* src, pri_rect_t * rect) {
	int xOffset = rect->x;
	int yOffset = rect->y;

	pri_rect_t copy_rect;
	memcpy(&copy_rect, rect, sizeof(pri_rect_t));
	if (rect->x < 0) {
		pri_rect_set_left(&copy_rect,copy_rect.x - rect->x);
		xOffset = 0;
	}

	if (rect->y < 0) {
		pri_rect_set_top(&copy_rect, copy_rect.y - rect->y);
		yOffset = 0;
	}

	/*int sourceXoffset = max(copy_rect.x, 0);
	int sourceXoffset = max(copy_rect.y, 0);*/

	//int effectiveWidth = min({
}