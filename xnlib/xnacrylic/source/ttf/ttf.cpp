///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  ttf.cpp -- Apple True Type Font
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#include <ttf\ttf.h>
#include <sys\_term.h>
#include <string.h>
#include <limits.h>
#include <color.h>
#include <sys\mmap.h>
#include <canvas.h>

float edge_at (float y, const tt_edge *edge) {
	float u = (y - edge->start.y)/ (edge->end.y - edge->start.y);
	return edge->start.x + u * (edge->end.x - edge->start.x);
}

int edge_sorter_high_scanline (const void *a, const void* b) {
	const tt_edge *left = (tt_edge*)a;
	const tt_edge *right = (tt_edge*)b;
	if (left->start.y < right->start.y) return - 1;
	if (left->start.y > right->start.y) return 1;
	return 0;
}

void sort_edges(size_t edgeCount, tt_edge edges[]) {
	qsort(edges, edgeCount,sizeof(tt_edge),edge_sorter_high_scanline);
}


int intersection_sorter (const void* a, const void* b) {
	const tt_intersection * left = (tt_intersection*)a;
	const tt_intersection * right =(tt_intersection*) b;

	if (left->x < right->x) return -1;
	if (left->x > right->x) return 1;
	return 0;
}

void sort_intersections(size_t cnt, tt_intersection *intersections) {
	qsort(intersections, cnt, sizeof(tt_intersection), intersection_sorter);
}


size_t prune_edges (size_t edgeCount, float y, const tt_edge edges[], tt_intersection into[]) {
	size_t outWriter = 0;
	for (size_t i = 0; i < edgeCount; ++i) {
		if (y > edges[i].end.y || y <= edges[i].start.y) continue;
		into[outWriter].x = edge_at(y, &edges[i]);
		into[outWriter].affect = edges[i].direction;
		outWriter++;
	}
	return outWriter;
}

void process_scanline (float _y, const tt_shape *shape, size_t subsample_width, float subsamples[], size_t cnt,
					   const tt_intersection crosses[]) {

	int wind = 0;
	size_t j = 0;
	for (int x = shape->startx; x < shape->lastx && j < cnt; ++x) {
		while (j < cnt && x > crosses[j].x) {
			wind += crosses[j].affect;
			j++;
		}
		float last = x;
		while (j < cnt && (x+1) > crosses[j].x) {
			if (wind != 0) {
				subsamples[x - shape->startx] += crosses[j].x - last;
			}
			last = crosses[j].x;
			wind += crosses[j].affect;
			j++;
		}
		if (wind != 0) {
			subsamples[x - shape->startx] += (x+1) - last;
		}
	}
}

uint32_t tt_rgba (uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return (a << 24U) | (r << 16) | (g << 8) | (b);
}

uint32_t tt_apply_alpha (uint32_t color, uint16_t alpha) {
	uint8_t r = ((uint32_t)(_RED(color) * alpha + 0x80) * 0x101) >> 16UL;
	uint8_t g = ((uint32_t)(_GRE(color) *alpha + 0x80) * 0x101) >> 16UL;
	uint8_t b = ((uint32_t)(_BLU(color) * alpha + 0x80) * 0x101) >> 16UL;
	uint32_t a = ((uint32_t)(_ALP(color) * alpha + 0x80) * 0x101) >> 16UL;
	return tt_rgba(r,g,b,a);
}

static inline uint32_t tt_alpha_blend_rgba(uint32_t bottom, uint32_t top) {
	if (_ALP(bottom) == 0) return top;
	if (_ALP(top) == 255) return top;
	if (_ALP(top) == 0) return bottom;
	uint8_t a = _ALP(top);
	uint16_t t = 0xFF ^ a;
	uint8_t d_r = _RED(top) + (((uint32_t)(_RED(bottom) * t + 0x80) * 0x101) >> 16UL);
	uint8_t d_g = _GRE(top) + (((uint32_t)(_GRE(bottom) * t + 0x80) * 0x101) >> 16UL);
	uint8_t d_b = _BLU(top) + (((uint32_t)(_BLU(bottom) * t + 0x80) * 0x101) >> 16UL);
	uint8_t d_a = _ALP(top) + (((uint32_t)(_ALP(bottom) * t + 0x80) * 0x101) >> 16UL);
	return tt_rgba(d_r, d_g, d_b, d_a);
}


void paint_scanline(int y, const tt_shape * shape, float * subsamples, uint32_t color) {
	for (int x = shape->startx < 0 ? 0 : shape->startx; x < shape->lastx && x  < canvas_get_width(); ++x) {
		uint16_t na = (int)(255 * subsamples[x - shape->startx]) >> 2;
		uint32_t nc = tt_apply_alpha(color, na);
		//sys_print_text ("Painting scanline\n");
		//GFX(ctx, x, y) = tt_alpha_blend_rgba(GFX(ctx, x, y), nc);
		canvas_get_framebuffer()[x + y * canvas_get_width()] = color; //tt_alpha_blend_rgba(canvas_get_pixel(x, y), color);
		subsamples[x-shape->startx] = 0;
	}
}

void tt_path_paint(const tt_shape * shape, uint32_t color) {
	size_t size = shape->edge_count;
	tt_intersection * crosses = (tt_intersection*)malloc(sizeof(tt_intersection) * size);
	memset(crosses, 0, sizeof(tt_intersection) * size);

	size_t subsample_width = shape->lastx - shape->startx;
	/*sys_print_text ("Shape startx-> %d\n", shape->startx);
	sys_print_text ("Shape lastx-> %d\n", shape->lastx);
	sys_print_text ("Subsample width -> %d\n",subsample_width);
	sys_print_text ("Size -> %d\n", size);*/
	float * subsamples = (float*)malloc(sizeof(float)*subsample_width);
	memset(subsamples, 0,sizeof(float)*subsample_width);
	
	int startY = shape->starty < 0 ? 0 : shape->starty;
	int endY = shape->lasty <= canvas_get_height() ? shape->lasty : canvas_get_height();
	for (int y = startY; y < endY; ++y) {
		float _y = y + 0.0001;
		for (int l = 0; l < 4; ++l) {
			size_t cnt;
			if ((cnt = prune_edges(size, _y, shape->edges, crosses))) {
			//	//sort_intersections(cnt, crosses);
				process_scanline(_y, shape, subsample_width, subsamples, cnt, crosses);
			}
			_y += 1.0/4.0;
		}
		paint_scanline(y, shape, subsamples, color);
	}

	free(subsamples);
 	free(crosses);
}


uint32_t ttf_read_32 (uint32_t val) {
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

uint16_t ttf_read_16 (uint16_t val) {
	return (val << 8) | (val >> 8);
}


int ttf_xadvance_for_glyph(ttf_font *font, unsigned int ind) {
	uint16_t *data = (uint16_t*)(font->data + font->hhea_ptr.offset + 2 * 17);
	uint16_t numLong = ttf_read_16 (*data);

	if (ind < numLong) {
		uint16_t *data2 = (uint16_t*)(font->data + font->hmtx_ptr.offset + ind * 4);
		return ttf_read_16(*data2);
	}

	uint16_t *data3 = (uint16_t*)(font->data + font->hmtx_ptr.offset + (numLong - 1) * 4);
	return ttf_read_16(*data3);
}


void ttf_set_size (ttf_font *font, float size) {
	font->scale = size / font->em_size;
}

void ttf_set_size_px (ttf_font *font, float size) {
	ttf_set_size (font, size * 4.0 / 3.0);
}


off_t ttf_get_glyph_offset (ttf_font * font, unsigned int glyph) {
	if (font->loca_type == 0) {
		uint16_t *data = (uint16_t*)(font->data + font->loca_ptr.offset + glyph * 2);
		return ttf_read_16(*data) * 2;
	} else {
		uint32_t* data = (uint32_t*)(font->data + font->loca_ptr.offset + glyph * 4);
		return ttf_read_32 (*data);
	}
}

tt_contour * tt_contour_start (float x, float y) {
	tt_contour *shape = (tt_contour*)malloc(sizeof(tt_contour) + sizeof(tt_edge)* 2);
	shape->edge_count = 0;
	shape->next_alloc = 2;
	shape->flags = 0;
	shape->last_start = 0;
	shape->edges[shape->edge_count].start.x = x;
	shape->edges[shape->edge_count].start.y = y;
	shape->last_start = shape->edge_count;
	shape->flags |= 1;
	return shape;
}


tt_shape* tt_contour_finish (tt_contour* in) {
	size_t size = in->edge_count + 1;
	tt_shape* tmp = (tt_shape*)malloc(sizeof(tt_shape) + sizeof(tt_edge)* size);
	memcpy (tmp->edges, in->edges, sizeof(tt_edge) * in->edge_count);

	if (in->flags & 1) {
		size--;
	}else {
		tmp->edges[in->edge_count].start.x = in->edges[in->edge_count-1].end.x;
		tmp->edges[in->edge_count].start.y = in->edges[in->edge_count-1].end.y;
		tmp->edges[in->edge_count].end.x = in->edges[in->last_start].start.x;
		tmp->edges[in->edge_count].end.y = in->edges[in->last_start].start.y;
	}

	for (size_t i = 0; i < size; ++i) {
		if (tmp->edges[i].start.y < tmp->edges[i].end.y) {
			tmp->edges[i].direction = 1;
		}else {
			tmp->edges[i].direction = -1;
			tt_coord j = tmp->edges[i].start;
			tmp->edges[i].start = tmp->edges[i].end;
			tmp->edges[i].end = j;
		}
	}

	tmp->edge_count = size;
	tmp->starty = INT_MAX;
	tmp->lasty = INT_MIN;
	tmp->startx = INT_MAX;
	tmp->lastx = INT_MIN;
	for (size_t i = 0; i < size; ++i) {
		if (tmp->edges[i].end.y + 1 > tmp->lasty) tmp->lasty = tmp->edges[i].end.y + 1;
		if (tmp->edges[i].start.y + 1 > tmp->lasty) tmp->lasty = tmp->edges[i].start.y + 1;
		if (tmp->edges[i].end.y < tmp->starty) tmp->starty = tmp->edges[i].end.y;
		if (tmp->edges[i].start.y < tmp->starty) tmp->starty = tmp->edges[i].start.y;

		if (tmp->edges[i].end.x + 2 > tmp->lastx) tmp->lastx = tmp->edges[i].end.x + 2;
		if (tmp->edges[i].start.x + 2 > tmp->lastx) tmp->lastx = tmp->edges[i].start.x + 2;
		if (tmp->edges[i].end.x < tmp->startx) tmp->startx = tmp->edges[i].end.x;
		if (tmp->edges[i].start.x < tmp->startx) tmp->startx = tmp->edges[i].start.x;

	}

	if (tmp->lasty < tmp->starty) tmp->starty = tmp->lasty;
	if (tmp->lastx < tmp->startx) tmp->startx = tmp->lastx;

	return tmp;
}



tt_contour * tt_contour_line_to (tt_contour * shape, float x, float y) {
	if (shape->flags & 1) {
		shape->edges[shape->edge_count].end.x = x;
		shape->edges[shape->edge_count].end.y = y;
		shape->edge_count++;
		shape->flags &= ~1;
		
	}else {
		if (shape->edge_count + 1 == shape->next_alloc) {
			shape->next_alloc *= 2;
			shape = (tt_contour*)realloc (shape, sizeof(tt_contour) + sizeof(tt_edge) * (shape->next_alloc));
			
		}
		shape->edges[shape->edge_count].start.x = shape->edges[shape->edge_count-1].end.x;
		shape->edges[shape->edge_count].start.y = shape->edges[shape->edge_count-1].end.y;
		shape->edges[shape->edge_count].end.x = x;
		shape->edges[shape->edge_count].end.y = y;
		shape->edge_count++;
		shape->flags &= ~1;
		//sys_print_text ("Line to -> %x\n", shape);
	}
	return shape;
}

tt_contour * ttf_contour_move_to (tt_contour *shape, float x, float y) {
	if (!(shape->flags & 1) && shape->edge_count) {
		shape = tt_contour_line_to (shape, shape->edges[shape->last_start].start.x, shape->edges[shape->last_start].start.y);
	}
	if (shape->edge_count + 1 == shape->next_alloc) {
		shape->next_alloc *= 2;
		shape = (tt_contour*)realloc(shape, sizeof(tt_contour) + sizeof(tt_edge) * (shape->next_alloc));
	}

	shape->edges[shape->edge_count].start.x = x;
	shape->edges[shape->edge_count].start.y = y;
	shape->last_start = shape->edge_count;
	shape->flags |= 1;
	return shape;
}

void ttf_midpoint (float x_0, float y_0, float cx, float cy, float x_1, float y_1, float t, float *outx, float *outy) {
	float t2 = t * t;
	float nt = 1.0 - t;
	float nt2 = nt * nt;
	*outx = nt2 * x_0 + 2 * t * nt * cx + t2 * x_1;
	*outy = nt2 * y_0 + 2 * t * nt * cy + t2 * y_1;
}

tt_contour * ttf_draw_glyph_into (tt_contour* contour, ttf_font *font, float x_offset, float y_offset,
								  unsigned int glyph) {
	 off_t glyf_offset = ttf_get_glyph_offset (font, glyph);

	 if (ttf_get_glyph_offset (font, glyph + 1) == glyf_offset) return contour;

	 int16_t *data = (int16_t*)(font->data + font->glyf_ptr.offset + glyf_offset);
	 int16_t numContour = ttf_read_16(*data);
     uint16_t *data1 = (uint16_t*)(font->data + font->glyf_ptr.offset + glyf_offset + 10);
	 if (numContour > 0) {
		 uint16_t endPt;
		 for (int i = 0; i < numContour; i++) {
			 endPt = ttf_read_16 (*data1);		
			 data1++;
		 }

		 data1 = 0;
		 data1 = (uint16_t*)(font->data + font->glyf_ptr.offset + glyf_offset + 10 + (numContour*sizeof(uint16_t)));
		 uint16_t numInstr = ttf_read_16(*data1);
		 data1++;
		 uint8_t *instr = (uint8_t*)data1;
		 for (unsigned int i = 0; i < numInstr; ++i) 
			 instr++;
		 tt_vertex *vertices = (tt_vertex*)malloc(sizeof(tt_vertex) * (endPt + 1));
		 memset (vertices, 0, sizeof(tt_vertex) * (endPt + 1));
		 for (int i = 0; i < endPt; ) {
			 uint8_t v = *instr;
			 vertices[i].flags = v;
			/* if (v & (1<<0))
				 sys_print_text ("On Curve\n");
			 else if (v & (1<<1))
				 sys_print_text ("x-Short Value\n");
			 else if (v & (1<<2))
				 sys_print_text ("y-Short Value\n");
			 else if (v & (1<<3))
				 sys_print_text ("Repeat\n");
			 else if (v & (1<<4))
				 sys_print_text ("Positive x-Short vector\n");
			 else if (v & (1 <<5))
				 sys_print_text ("Positive y-Short vector\n");*/
			
			 i++;
			 instr++;
		 }
		 int last_x = 0;
		 int last_y = 0;
		 int16_t *data2 = (int16_t*)instr;  //convert into signed 16 bit
		 for (int i = 0; i < endPt ; i++) {
			 unsigned char flags = vertices[i].flags;
			 if (flags & (1 << 1)) {
				 //! x-coord bytes are 1 byte long
				 if (flags & (1 << 4)) {
					 vertices[i].x = last_x + *instr;
					 instr++;
					// sys_print_text ("Vertices -> %d\n", vertices[i].x);
				 }else {
					 vertices[i].x = last_x - *instr;
					 instr++;
					 //sys_print_text ("Vertices -> %d\n", vertices[i].x);
				 }
			 }else {
				 if (flags & (1 << 4)) {
					 vertices[i].x = last_x;
					 // sys_print_text ("Vertices -> %d\n", vertices[i].x);
				 } else {
					 int16_t diff = ttf_read_16 (*instr);
					 instr++;
					 instr++;
					 vertices[i].x = last_x + diff; 
					 // sys_print_text ("Vertices -> %d\n", vertices[i].x);
				 }
			 }
			 last_x = vertices[i].x;
			// instr++;
		 }

		 for (int i = 0; i < endPt; i++) {
			 unsigned char flags = vertices[i].flags;
			 if (flags & (1 << 2)) {
				 //! One byte 
				 if (flags & (1 << 5)) {
					 vertices[i].y = last_y + *instr;
					// sys_print_text ("Vertices -> %d\n", vertices[i].y);
					 instr++;
				 }else {
					 vertices[i].y = last_y - *instr; 
					 instr++;
					// sys_print_text ("Vertices -> %d\n", vertices[i].y);
				 }
			 } else {
				 if (flags & (1 << 5)) {
					 vertices[i].y = last_y;
					/* if (vertices[i].y > 4294966000)
						 vertices[i].y = 0;*/
					// sys_print_text ("Vertices -> %d\n", vertices[i].y);
				 } else {
					// int16_t *data3 = (int16_t*)instr;
					 int16_t diff = ttf_read_16 (*instr);
					 instr++;
					 instr++;
					 vertices[i].y = last_y + diff; 
					  //sys_print_text ("Vertices -> %d\n", vertices[i].y);
					/* if (vertices[i].y > 4294966000)
						 vertices[i].y = 0;
					*/
				 }
			 } 
			 last_y = vertices[i].y;
			 //instr++;
		 }

		 int move_next = 1;
		 uint16_t *data3 = (uint16_t*)(font->data + font->glyf_ptr.offset + glyf_offset + 10);
		 uint16_t  next_end = ttf_read_16 (*data3);
		 data3++;

		 float lx = 0, ly = 0, cx = 0, cy = 0, x = 0, y = 0;
		 float sx = 0, sy = 0;
		 int wasControl = 0;

		 for (int i = 0; i < endPt + 1; ++i) {
			 x = ((float)vertices[i].x) * font->scale + x_offset;
			 y = (-(float)vertices[i].y) * font->scale + y_offset;
			 int isCurve = !(vertices[i].flags & (1 << 0));
			 if (move_next) {
				 contour = ttf_contour_move_to (contour, x, y); 
				 if (isCurve) {
					 float px = (float)vertices[next_end].x * font->scale + x_offset;
					 float py = (-(float)vertices[next_end].y) * font->scale + y_offset;
					 if (vertices[next_end].flags & (1 << 0)) {
						 sx = px;
						 sy = py;
						 lx = px;
						 ly = py;
					 } else {
						 float dx = (px + x) / 2.0;
						 float dy = (py + y) / 2.0;
						 lx = dx;
						 ly = dy;
						 sx = dx;
						 sy = dy;
					 }
					 cx = x;
					 cy = y;
					 wasControl = 1;
				 } else {
					 lx = x;
					 ly = y;
					 sx = x;
					 sy = y;
					 wasControl = 0;
				 }
				 move_next = 0;
				
			 }else {
				 if (isCurve) {
					 if (wasControl) {
						 float dx = (cx + x) / 2.0;
						 float dy = (cy + y) / 2.0;
						 for (int i = 1; i < 10; ++i) {
							 float mx, my;
							 ttf_midpoint (lx, ly, cx, cy, dx, dy, (float)i / 10.0, &mx, &my);
							 contour = tt_contour_line_to(contour, mx, my);
						 }
						 contour = tt_contour_line_to (contour, dx, dy);
						 lx = dx;
						 ly = dy;
					 }
					 cx = x;
					 cy = y;
					 wasControl = 1;
				 }else {
					 if (wasControl) {
						 for (int i = 1; i < 10; ++i) {
							 float mx, my;
							 ttf_midpoint(lx, ly, cx, cy, x, y, (float)i / 10.0, &mx, &my);
							 contour = tt_contour_line_to(contour, mx, my);
						 }
					 }
					 contour = tt_contour_line_to (contour, x, y);
					 lx = x;
					 ly = y;
					 wasControl = 0;
				 }
			 }
			 if (i == next_end) {
				 if (wasControl) {
					 for (int i = 1; i < 10; ++i) {
						 float mx, my;
						 ttf_midpoint(lx,ly, cx, cy, sx, sy,(float)i / 10.0, &mx, &my);
						 contour = tt_contour_line_to(contour, mx, my);
					 }
				 }
				 contour = tt_contour_line_to (contour, sx, sy);
				 move_next = 1;
				 next_end = ttf_read_16(*data3);
				 data3++;
			 }
		 }
		 free(vertices);

	}else if (numContour < 0) {
		while(1) {
			uint16_t flags = ttf_read_16(*data1);
			data1++;
			uint16_t ind = ttf_read_16(*data1);
			data1++;
			int16_t x, y;
			if (flags & (1 << 0)) {
				x = ttf_read_16(*data1);
				data1++;
				y = ttf_read_16(*data1);
				data1++;
			}else {
				uint8_t *data2 = (uint8_t*)data1;
				x = *data2;
				data2++;
				y = *data2;
				data2++;
			}

			float x_f = x_offset;
			float y_f = y_offset;
			if (flags & (1 << 1)) {
				x_f = x_offset + x * font->scale;
				y_f = y_offset - y * font->scale;
			}

			if (flags & (1 << 3)) {
				data1++;
			}else if (flags & (1 << 6)) {
				data1++;
				data1++;
			} else if (flags & (1 << 7)) {
				data1++;
				data1++;
				data1++;
				data1++;
			} else {
			    unsigned char *cvalue = (unsigned char*)data1;
				long o = font->data - cvalue;
				contour = ttf_draw_glyph_into (contour, font, x_f, y_f, ind);
				//seek (font, 0);
			}
			if (!(flags & (1 << 5))) break;
		}
	}

	return contour;
}


int ttf_glyph_for_code (ttf_font *font, unsigned int code) {
	if (font->cmap_type == 12) {
		ttf_cmap_format12 *format = (ttf_cmap_format12*)(font->data + font->cmap_start);
		uint32_t ngroups = ttf_read_32 (format->nGroups);
		ttf_group_table12 *group = (ttf_group_table12*)(font->data + font->cmap_start + sizeof(ttf_cmap_format12));
		for (unsigned int i = 0; i < ngroups; ++i) {
			uint32_t start = ttf_read_32 (group[i].startCharCode);
			uint32_t end = ttf_read_32(group[i].endCharCode);
			uint32_t index = ttf_read_32 (group[i].startGlyphCode);

			if (code >= start && code <= end) {
				return index + (code - start);
			}
		}
	} else if (font->cmap_type == 4) {
		if (code > 0xFFFF) return 0;
		uint32_t *segc = (uint32_t*)(font->data + font->cmap_start + 6);
		uint16_t segCount = ttf_read_16 (*segc) / 2;
		for (int i = 0; i < segCount; ++i) {
			uint32_t *data = (uint32_t*)(font->data + font->cmap_start + 12 + 2 * i);
			uint16_t endCode = ttf_read_16(*data);
			if (endCode >= code) {
				uint32_t *data2 = (uint32_t*)(font->data + font->cmap_start + 12 + 2 * segCount + 2 + 2 * i);
				uint16_t startCode = ttf_read_16(*data2);
				if (startCode > code) {
					return 0;
				}

				uint32_t *data3 = (uint32_t*)(font->data + font->cmap_start + 12 + 4 * segCount + 2 + 2 * i);
				int16_t idDelta = ttf_read_16(*data3);
				uint32_t *data4 = (uint32_t*)(font->data + font->cmap_start + 12 + 6 * segCount + 2 + 2 * i);
				uint16_t idRangeOffset = ttf_read_16(*data4);
				if (idRangeOffset == 0) {
					return idDelta + code;
				} else {
					uint32_t *data5 = (uint32_t*)(font->data + font->cmap_start + 12 + 6 * segCount + 2 + 2 * i + 
						idRangeOffset + (code - startCode) * 2);
					uint16_t ret_index = ttf_read_16 (*data5);
				}
			}
		}
	}

	return 0;
}


int tt_draw_string(ttf_font * font, int x, int y, const char * s, uint32_t color) {
	tt_contour * contour = tt_contour_start(0, 0);

	float x_offset = x;
	uint32_t cp = 0;
	uint32_t istate = 0;

	for (const unsigned char * c = (const unsigned char*)s; *c; ++c) {
		if (!decode(&istate, &cp, *c)) {
			cp = *c;
			unsigned int glyph = ttf_glyph_for_code(font, cp);
			contour = ttf_draw_glyph_into(contour,font,x_offset,y,glyph);
			x_offset += ttf_xadvance_for_glyph(font, glyph) * font->scale;
		}
	}

	if (contour->edge_count) {
		tt_shape * shape = tt_contour_finish(contour);
		tt_path_paint(shape, color);
		free(shape);
	}
	free(contour);

	return x_offset - x;
}

ttf_font * ttf_load (unsigned char* data) {
	ttf_font *font = (ttf_font*)malloc(sizeof(ttf_font));
	font->data = data;
	offset_table_t *poff = (offset_table_t*)data;
	poff->apple_scaler_type = ttf_read_32(poff->apple_scaler_type);
	uint16_t num_tables = ttf_read_16 (poff->num_tables);
	table_dirent_t *tbl = (table_dirent_t*)(poff + 1);

	for (int i = 0; i < num_tables; i++) {
		uint32_t tag = ttf_read_32(tbl[i].tag);
		uint32_t offset = ttf_read_32(tbl[i].offset);
		uint32_t length = ttf_read_32(tbl[i].length);

		switch(tag) {
		case TAG_HEAD:
			font->head_ptr.offset = offset;
			font->head_ptr.length = length;
			break;
		case TAG_CMAP:
			font->cmap_ptr.offset = offset;
			font->cmap_ptr.length = length;
			break;
		case TAG_GLYF:
			font->glyf_ptr.offset = offset;
			font->glyf_ptr.length = length;
			break;
		case TAG_LOCA:
			font->loca_ptr.offset = offset;
			font->loca_ptr.length = length;
			break;
		case TAG_HHEA:
			font->hhea_ptr.offset = offset;
			font->hhea_ptr.length = length;
			break;
		case TAG_HMTX:
			font->hmtx_ptr.offset = offset;
			font->hmtx_ptr.length = length;
			break;
		case TAG_NAME:
			font->name_ptr.offset = offset;
			font->name_ptr.length = length;
			break;
		}
	}

	ttf_head *head = (ttf_head*)(data + font->head_ptr.offset);
	uint16_t unitsPerEm = ttf_read_16(head->unitsPerEm);
	font->em_size = unitsPerEm; //unitsPerEm;
	sys_print_text ("EM Size -> %d\n", font->em_size);
	font->loca_type = head->indexToLocFormat;
	sys_print_text ("Loca type -> %d\n", font->loca_type);
	ttf_cmap_index *cmap_i = (ttf_cmap_index*)(data + font->cmap_ptr.offset);
	ttf_cmap_subtable *cmap_sub_tab = (ttf_cmap_subtable*)(data + font->cmap_ptr.offset + sizeof(ttf_cmap_index));
	int best_cmap_offset = 0;
	int platform_spec_id = 0;
	for (int i = 0;  i < ttf_read_16(cmap_i->numberSubTables); i++) {
		uint16_t platform = ttf_read_16(cmap_sub_tab[i].platformId);
		uint16_t type = ttf_read_16(cmap_sub_tab[i].platformSpecificId);
		uint32_t offset = ttf_read_32(cmap_sub_tab[i].offset);

		switch(platform) {
		case PLATFORM_ID_UNICODE:
			//currently unsupported
			break;
		case PLATFORM_ID_MACINTOSH:
			//skip
			break;
		case PLATFORM_ID_MICROSOFT:
			best_cmap_offset = offset;  //! Only use Microsofts platform id
			switch(type) {
			case 0:
				platform_spec_id = type;
				break;
			case 1:
				platform_spec_id = type;
				break;
			case 2:
				platform_spec_id = type;
				break;
			case 3:
				platform_spec_id = type;
				break;
			case 4:
				platform_spec_id = type;
				break;
			case 5:
			    platform_spec_id = type;
				break;
			case 10:
				platform_spec_id = type;
				break;
			}
			break;
		}
	}

	font->cmap_start = (off_t)(font->cmap_ptr.offset + best_cmap_offset);

	uint16_t *format = (uint16_t*)(data + font->cmap_ptr.offset + best_cmap_offset);
	uint16_t cmap_format = ttf_read_16 (*format);
	font->cmap_type = cmap_format;

	ttf_set_size_px(font, 2.1f);

	tt_contour *contour = tt_contour_start(0,0);
	unsigned int glyph = ttf_glyph_for_code(font, 'P');

	contour = ttf_draw_glyph_into(contour,font,0,0,glyph);
//	x_offset += ttf_xadvance_for_glyph(font, glyph) * font->scale;
	//		sys_print_text ("XOff-> %d\n", x_offset);
	//	}
	//}

	sys_print_text ("Contour edgeC -> %d\n",contour->edge_count);
	if (contour->edge_count) {
		tt_shape * shape = tt_contour_finish(contour);
		tt_path_paint(shape, WHITE);
		free(shape);
	}
	return font;
}