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
#include <ctype.h>
#include <acrylic.h>


void ttf_seek (ttf_font *font, off_t offset) {
	font->pos = (font->data + offset);
}

long ttf_tell (ttf_font *font) {
	return font->pos - font->data;
}

uint8_t ttf_read_8(ttf_font *font) {
	return *(font->pos++);
}

uint32_t ttf_read_32 (ttf_font *font) {
	int a = ttf_read_8 (font);
	int b = ttf_read_8 (font);
	int c = ttf_read_8 (font);
	int d = ttf_read_8 (font);
	if (a < 0 || b < 0 || c < 0 || d < 0) return 0;
	return ((a & 0xFF) << 24) | 
		((b & 0xFF) << 16) | 
		((c & 0xFF) << 8) | 
		((d & 0xFF) << 0);
}

uint32_t ttf_convert_32 (uint32_t a) {
	return ((a & 0xFF) << 24) | 
		((a & 0xFF) << 16) | 
		((a & 0xFF) << 8) | 
		((a & 0xFF) << 0);
}

uint16_t ttf_read_16 (ttf_font *font) {
	int a = ttf_read_8 (font);
	int b = ttf_read_8 (font);
	if ( a < 0 || b < 0) return 0;
	return (( a & 0xFF) << 8) | 
		((b & 0xFF) << 0);
}



int edge_at (int y, const tt_edge *edge) {
	int u = (y - edge->start.y)/ (edge->end.y - edge->start.y);
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


size_t prune_edges (size_t edgeCount, int y, const tt_edge edges[], tt_intersection into[]) {
	size_t outWriter = 0;
	for (size_t i = 0; i < edgeCount; ++i) {
		if (y > edges[i].end.y || y <= edges[i].start.y) continue;
		into[outWriter].x = edge_at(y, &edges[i]);
		into[outWriter].affect = edges[i].direction;
		outWriter++;
	}
	return outWriter;
}

void process_scanline (int _y, const tt_shape *shape, size_t subsample_width, int *subsamples, size_t cnt,
					   const tt_intersection *crosses) {

	int wind = 0;
	size_t j = 0;
	for (int x = shape->startx; x < shape->lastx && j < cnt; ++x) {
		while (j < cnt && x > crosses[j].x) {
			wind += crosses[j].affect;
			j++;
		}
		int last = x;
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


void paint_scanline(int y, const tt_shape * shape, int * subsamples, uint32_t color) {
	for (int x = shape->startx < 0 ? 0 : shape->startx; x < shape->lastx && x  < canvas_get_width(); ++x) {
		uint16_t na = (255 * subsamples[x - shape->startx]) >> 2;
		uint32_t nc = tt_apply_alpha(color,na);
		//sys_print_text ("Painting scanline\n");
		//GFX(ctx, x, y) = tt_alpha_blend_rgba(GFX(ctx, x, y), nc);
		canvas_get_framebuffer()[x + y * canvas_get_width()] = tt_alpha_blend_rgba(canvas_get_pixel(x,y),nc);
		subsamples[x-shape->startx] = 0;
	}
}

void tt_path_paint(const tt_shape * shape, uint32_t color) {
	size_t size = shape->edge_count;
	tt_intersection * crosses = (tt_intersection*)malloc(sizeof(tt_intersection) * size);
	memset(crosses, 0, sizeof(tt_intersection) * size);

	size_t subsample_width = shape->lastx - shape->startx;
	sys_print_text ("SubSample wid -> %d\n", subsample_width);
	int * subsamples = (int*)malloc(sizeof(int)*subsample_width);
	memset(subsamples, 0,sizeof(int)*subsample_width);
	sys_print_text ("Painting\n");

	int startY = shape->starty < 0 ? 0 : shape->starty;
	int endY = shape->lasty <= canvas_get_height() ? shape->lasty : canvas_get_height();
	sys_print_text ("StartY -> %d\n", startY);
	sys_print_text ("LastY -> %d\n", endY);
	for (int y = startY; y < endY; ++y) {
		int _y = y + 0.0001;
		for (int l = 0; l < 4; ++l) {
			size_t cnt;
			if ((cnt = prune_edges(size, _y, shape->edges, crosses))) {
			    sort_intersections(cnt, crosses);
				process_scanline(_y, shape, subsample_width, subsamples, cnt, crosses);
			}
			_y += 1.0/4.0;
		}
		paint_scanline(y, shape, subsamples, color);
	}

	free(subsamples);
 	free(crosses);
}


int ttf_xadvance_for_glyph(ttf_font *font, unsigned int ind) {
	ttf_seek(font, font->hhea_ptr.offset + 2 * 17);
	uint16_t numLong = ttf_read_16 (font);

	if (ind < numLong) {
		ttf_seek (font, font->hmtx_ptr.offset + ind * 4);
		return ttf_read_16(font);
	}

	ttf_seek (font, font->hmtx_ptr.offset + (numLong - 1) * 4);
	return ttf_read_16(font);
}


void ttf_set_size (ttf_font *font, float size) {
	font->scale = size / font->em_size;
}

void ttf_set_size_px (ttf_font *font, float size) {
	ttf_set_size (font, size * 4.0 / 3.0);
}


off_t ttf_get_glyph_offset (ttf_font * font, unsigned int glyph) {
	if (font->loca_type == 0) {
		ttf_seek (font, font->loca_ptr.offset + glyph * 2);
		return ttf_read_16(font) * 2;
	} else {
		ttf_seek (font, font->loca_ptr.offset + glyph * 4);
		return ttf_read_32 (font);
	}
}

tt_contour * tt_contour_start (int x, int y) {
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



tt_contour * tt_contour_line_to (tt_contour * shape, int x, int y) {
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

tt_contour * ttf_contour_move_to (tt_contour *shape, int x, int y) {
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

void ttf_midpoint (int x_0, int y_0, int cx, int cy, int x_1, int y_1, int t, int *outx, int *outy) {
	int t2 = t * t;
	int nt = 1.0 - t;
	int nt2 = nt * nt;
	*outx = nt2 * x_0 + 2 * t * nt * cx + t2 * x_1;
	*outy = nt2 * y_0 + 2 * t * nt * cy + t2 * y_1;
}




tt_contour * ttf_draw_glyph_into (tt_contour* contour, ttf_font *font, int x_offset, int y_offset,
								  unsigned int glyph, uint32_t color) {
	 off_t glyf_offset = ttf_get_glyph_offset (font, glyph);

	 if (ttf_get_glyph_offset (font, glyph + 1) == glyf_offset) return contour;

	 ttf_seek (font, font->glyf_ptr.offset + glyf_offset);
	
	 int16_t numContour = ttf_read_16(font);
	 int16_t xMin = ttf_read_16 (font);
	 int16_t yMin = ttf_read_16 (font);
	 int16_t xMax = ttf_read_16 (font);
	 int16_t yMax = ttf_read_16 (font);
	 int h = yMax - yMin;
	 if (font->height == 0)
		 font->height = h * font->scale + 12;

	 ttf_seek (font, font->glyf_ptr.offset + glyf_offset + 10);

	 if (numContour > 0) {
		 uint16_t endPt;
		 for (int i = 0; i < numContour; i++) {
			 endPt = ttf_read_16 (font);		
		 }

		 uint16_t numInstr = ttf_read_16(font);
		
		 for (unsigned int i = 0; i < numInstr; ++i) 
			 ttf_read_8 (font);

		 tt_vertex *vertices = (tt_vertex*)malloc(sizeof(tt_vertex) * (endPt + 1));
		 memset (vertices, 0, sizeof(tt_vertex) * (endPt + 1));
		 for (int i = 0; i < endPt + 1; ) {
			 uint8_t v = ttf_read_8 (font);
			 vertices[i].flags = v;
			 i++;
			 if (v & 8) {
				 uint8_t repC = ttf_read_8 (font);
				 while (repC) {
					 vertices[i].flags = v;
					 repC--;
					 i++;
				 }
			 }
		 }
		 int last_x = 0;
		 int last_y = 0;
		 for (int i = 0; i < endPt + 1 ; i++) {
			 unsigned char flags = vertices[i].flags;
			 if (flags & (1 << 1)) {
				 //! x-coord bytes are 1 byte long
				 if (flags & (1 << 4)) {
					 vertices[i].x = last_x + ttf_read_8 (font);
					// sys_print_text ("Vertices x -> %d\n", vertices[i].x);
				 }else {
					 vertices[i].x = last_x - ttf_read_8 (font);
					 //sys_print_text ("Vertices x -> %d\n", vertices[i].x);
				 }
			 }else {
				 if (flags & (1 << 4)) {
					 vertices[i].x = last_x;
					// sys_print_text ("Vertices x -> %d\n", vertices[i].x);
				 } else {
					 int16_t diff = ttf_read_16 (font);
					 vertices[i].x = last_x + diff; 
					// sys_print_text ("Vertices x-> %d\n", vertices[i].x);
				 }
			 }
			 last_x = vertices[i].x;
			// instr++;
		 }

		 for (int i = 0; i < endPt + 1; i++) {
			 unsigned char flags = vertices[i].flags;
			 if (flags & (1 << 2)) {
				 //! One byte 
				 if (flags & (1 << 5)) {
					 vertices[i].y = last_y + ttf_read_8(font);
					// sys_print_text ("Vertices y -> %d\n", vertices[i].y);
				 }else {
					 vertices[i].y = last_y - ttf_read_8 (font); 
					// sys_print_text ("Vertices y -> %d\n", vertices[i].y);
				 }
			 } else {
				 if (flags & (1 << 5)) {
					 vertices[i].y = last_y;
					/* if (vertices[i].y > 4294966000)
						 vertices[i].y = 0;*/
					// sys_print_text ("Vertices y -> %d\n", vertices[i].y);
				 } else {
					// int16_t *data3 = (int16_t*)instr;
					 int16_t diff = ttf_read_16 (font);
					 vertices[i].y = last_y + diff; 
					// sys_print_text ("Vertices y -> %d\n", vertices[i].y);
					/* if (vertices[i].y > 4294966000)
						 vertices[i].y = 0;
					*/
				 }
			 } 
			 last_y = vertices[i].y;
			 //instr++;
		 }

		 int move_next = 1;
		 ttf_seek (font, font->glyf_ptr.offset + glyf_offset + 10);
		 uint16_t  next_end = ttf_read_16 (font);
		
		 int x, y,lx,ly,cx,cy = 0;
		 int sx,sy=0;
		 int wasControl = 0;
		 int x_pos;
		 int y_pos;
		 bool draw_curve = false;
		 for (int i = 0; i < endPt + 1; ++i) {
			 x = vertices[i].x * font->scale + x_offset;
			 y =  (-vertices[i].y) * font->scale + y_offset;
			 int isCurve = !(vertices[i].flags & (1 << 0));
			
			 if (move_next) {
				 x_pos = x;
				 y_pos = y;
				 move_next = 0;
				 canvas_draw_pixel (x, y,color);
			 }else {
				 acrylic_draw_line (x_pos, y_pos, x, y, color);
				// acrylic_draw_line (x_pos, y_pos, x, y,WHITE);
				 x_pos = x;
				 y_pos = y;
				 
			 }
			 
			 if (i == next_end) {
				 next_end = ttf_read_16(font);
				 move_next = 1;
			 }

			
		 }

	}else if (numContour < 0) {
		while(1) {
			uint16_t flags = ttf_read_16(font);
			uint16_t ind = ttf_read_16(font);
			int16_t x, y;
			if (flags & (1 << 0)) {
				x = ttf_read_16(font);
				y = ttf_read_16(font);
			}else {
				x = ttf_read_8(font);
				y = ttf_read_8(font);
			}

			int x_f = x_offset;
			int y_f = y_offset;
			if (flags & (1 << 1)) {
				x_f = x_offset + x * font->scale;
				y_f = y_offset - y * font->scale;
			}

			if (flags & (1 << 3)) {
				ttf_read_16(font);
			}else if (flags & (1 << 6)) {
				ttf_read_16(font);
				ttf_read_16(font);
			} else if (flags & (1 << 7)) {
				ttf_read_16(font);
				ttf_read_16(font);
				ttf_read_16(font);
				ttf_read_16(font);
			} else {
				long o = ttf_tell(font);
				contour = ttf_draw_glyph_into (contour, font, x_f, y_f, ind, color);
				ttf_seek (font, o);
			}
			if (!(flags & (1 << 5))) break;
		}
	}

	return contour;
}


int ttf_glyph_for_code (ttf_font *font, unsigned int code) {
	if (font->cmap_type == 12) {
		ttf_seek (font, font->cmap_start + 4 + 8);
		uint32_t ngroups = ttf_read_32 (font);

		for (unsigned int i = 0; i < ngroups; ++i) {
			uint32_t start = ttf_read_32 (font);
			uint32_t end = ttf_read_32(font);
			uint32_t index = ttf_read_32 (font);

			if (code >= start && code <= end) {
				return index + (code - start);
			}
		}
	} else if (font->cmap_type == 4) {
		if (code > 0xFFFF) return 0;

		ttf_seek (font, font->cmap_start + 6);
		uint16_t segCount = ttf_read_16(font) / 2;

		for (int i = 0; i < segCount; ++i) {
			ttf_seek (font, font->cmap_start + 12 + 2 * i);
			uint16_t endCode = ttf_read_16(font);
			if (endCode >= code) {
				ttf_seek (font, font->cmap_start + 12 + 2 * segCount + 2 + 2 * i);
				uint16_t startCode = ttf_read_16(font);
				if (startCode > code) {
					return 0;
				}
				ttf_seek (font, font->cmap_start + 12 + 4 * segCount + 2 + 2 * i);
				int16_t idDelta = ttf_read_16 (font);
				ttf_seek (font, font->cmap_start + 12 + 6 * segCount + 2 + 2 * i);
				uint16_t idRangeOffset = ttf_read_16(font);
				if (idRangeOffset == 0) {
					return idDelta + code;
				} else {
					ttf_seek (font, font->cmap_start + 12 + 6 * segCount + 2 + 2 * i + idRangeOffset + (code - startCode) * 2);
					return ttf_read_16(font);
				}
			}
		}
	}

	return 0;
}


void tt_draw_string (ttf_font *font, int x, int y, const char* s, uint32_t color) {
	tt_contour *con = tt_contour_start(x,y);
	uint32_t state = 0;
	uint32_t cp = 0;

	for (const unsigned char* c = (const unsigned char*)s; *c; ++c) {
		if (!decode (&state, &cp, *c)) {
			int code = ttf_glyph_for_code (font,cp);
			con = ttf_draw_glyph_into (con, font, x,y,code, color);
			x += ttf_xadvance_for_glyph(font, code) * font->scale;
		}
	}
	free (con);
}

ttf_font * ttf_load (unsigned char* data) {
	ttf_font *font = (ttf_font*)malloc(sizeof(ttf_font));
	font->data = data;
	font->pos = font->data;
	font->height = 0;

	uint32_t scaler_type  = ttf_read_32 (font);
	uint16_t num_tables = ttf_read_16 (font);
	uint16_t search_range = ttf_read_16 (font);
	uint16_t entry_select = ttf_read_16 (font);
	uint16_t range_shift = ttf_read_16 (font);

	for (unsigned int i = 0; i < num_tables; i++) {
		uint32_t tag = ttf_read_32 (font);
		uint32_t checksum = ttf_read_32(font);
		uint32_t offset = ttf_read_32 (font);
		uint32_t length = ttf_read_32(font);

		switch (tag) {
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

	ttf_seek (font, font->head_ptr.offset + 18);
	font->em_size = ttf_read_16 (font);

	ttf_seek (font, font->head_ptr.offset + 50);
	font->loca_type = ttf_read_16 (font);
	
	ttf_seek (font, font->cmap_ptr.offset);

	uint32_t best = 0;
	int best_score = 0;
	uint16_t cmap_version = ttf_read_16(font);
	uint16_t cmap_size = ttf_read_16 (font);

	for (unsigned int i = 0; i < cmap_size; ++i) {
		uint16_t platform = ttf_read_16 (font);
		uint16_t type = ttf_read_16 (font);
		uint32_t offset = ttf_read_32 (font);

		if ((platform == 3 || platform == 0) && type == 10) {
			best = offset;
			best_score = 4;
		}else if (platform == 0 && type == 4) {
			best = offset;
			best_score = 4;
		}else if (((platform == 0 && type == 3) || (platform == 3 && type == 1)) && best_score < 2) {
			best = offset;
			best_score = 2;
		}
	}

	ttf_set_size (font, 20);

	ttf_seek (font, font->cmap_ptr.offset + best);

	font->cmap_type = ttf_read_16 (font);
	font->cmap_start = font->cmap_ptr.offset + best;

	return font;
}