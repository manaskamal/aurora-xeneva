/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  gui.cpp -- Graphics Drawing Functions
 *
 *  /PROJECT - Aurora Xeneva {DWM}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#include <dwm.h>
#include <stdtypes.h>
#include <sys.h>
#include <allocator.h>
#include <wm.h>
#include <menubar.h>
#include <stack.h>

static int s_width = 0;
static int s_height = 0;
uint8_t * font_data_ = NULL;
uint16_t scanline = 0;
bool update = true;
winlist *dirty_list = NULL;

static const int AMASK = 0xFF000000;
static const int RBMASK = 0x00FF00FF;
static const int GMASK = 0x0000FF00;
static const int AGMASK = AMASK | GMASK;
static const int ONEALPHA = 0x01000000;

void initialize_screen () {
	s_width = get_screen_width ();
	s_height = get_screen_height ();
	scanline = sys_get_scanline();
}
/**=====================================================
 *  G L O B A L   G R A P H I C S   F U N C T I O N S
 * =====================================================
 */
void draw_pixel (unsigned x, unsigned y, uint32_t color ) {
	uint32_t *lfb = (uint32_t*)0x0000600000000000;  // 0xFFFFF00000000000;       
	lfb[x + y * s_width] = color;
}

uint32_t get_pixel32bit (unsigned x, unsigned y)
{
	uint32_t* lfb = (uint32_t*)0x0000600000000000; //0xFFFFF00000000000; 
	return lfb[x + y * s_width];
}


void draw_pixel2 (unsigned x, unsigned y, uint32_t color ) {
	uint32_t *lfb = (uint32_t*)0xFFFFF00000000000;
	lfb[x + y * s_width] = color;
}

void draw_pixel3 (unsigned x, unsigned y, uint32_t color ) {
	uint32_t *lfb = (uint32_t*)0x0000500000000000;
	lfb[x + y * s_width] = color;
}









void copy_to_screen(uint32_t *buf, rect_t *r) {
	uint32_t* lfb = (uint32_t*)0xFFFFF00000000000;
	//uint32_t* wallp = (uint32_t*)0x0000500000000000;
	int width = get_screen_width();
	int height = get_screen_height();
	for (int i=0; i < r->w; i++) {
		for (int j=0; j < r->h; j++){
			//if (buf[(r->x + i) + (r->y + j) * width] | 0x00000000){
			uint32_t color = buf[(r->x + i) + (r->y + j) * width];
		//	uint32_t color_a = wallp[(r->x + i) + (r->y + j) * width];
			lfb[(r->x + i) + (r->y + j) * width] = color;//alpha_blend(color_a,color);
			//}
		}
	}
}

void copy_to_screen2(uint32_t *buf, rect_t *r) {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	uint32_t* wallp = (uint32_t*)0x0000500000000000;
	int width = get_screen_width();
	int height = get_screen_height();
	for (int i=0; i < r->w; i++) {
		for (int j=0; j < r->h; j++){
			if (buf[(r->x + i) + (r->y + j) * width] | 0x00000000){
			uint32_t color = buf[(r->x + i) + (r->y + j) * width];
			uint32_t color_a = wallp[(r->x + i) + (r->y + j) * width];
			lfb[(r->x + i) + (r->y + j) * width] = alpha_blend(color_a, color);
			}
		}
	}
}

void copy_to_screen2_no_geom(uint32_t *buf, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	uint32_t* wallp = (uint32_t*)0x0000500000000000;
	int width = get_screen_width();
	int height = get_screen_height();
	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			if (buf[(x + i) + (y + j) * width] | 0x00000000){
			uint32_t color = buf[(x + i) + (y + j) * width];
			uint32_t color_a = wallp[(x + i) + (y + j) * width];
			lfb[(x + i) + (y + j) * width] = alpha_blend(color_a, color);
			}
		}
	}
}


void dwm_add_alpha(uint32_t *buf, rect_t *r, uint32_t add_color) {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	//uint32_t* wallp = (uint32_t*)0x0000600000000000;
	int width = get_screen_width();
	int height = get_screen_height();
	for (int i=0; i < r->w; i++) {
		for (int j=0; j < r->h; j++){
			//uint32_t color = buf[(r->x + i) + (r->y + j) * width] & 0x993E3E3E;
			uint32_t color_a = buf[(r->x + i) + (r->y + j) * width];
			lfb[(r->x + i) + (r->y + j) * width] = alpha_blend(color_a, add_color);
		}
	}
}


void draw_rect (unsigned x, unsigned y, unsigned w, unsigned h, uint32_t col) {
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			draw_pixel(x + i, y + j, col);
}

void draw_vertical_line (unsigned x, unsigned y, unsigned length, uint32_t color) {
	draw_rect(x,y,1,length,color);
}

void draw_horizontal_line (unsigned x, unsigned y, unsigned length, uint32_t color) {
	draw_rect (x,y,length,1,color);
}


void draw_rect_unfilled (int x, int y, int width, int height, uint32_t color) {
	draw_horizontal_line ( x, y, width, color); //top
	draw_vertical_line( x, y+1, height -2, color); //left
    draw_horizontal_line(x, y + height - 1, width, color); //bottom
	draw_vertical_line (x + width - 1, y + 1, height - 2, color); //right
}

void set_alpha_value(uint32_t color, uint32_t alpha) {
	 ( ((color << 8) >> 8) | ((alpha << 24) & 0xff000000));
}

uint32_t alpha_blend (uint32_t color1, uint32_t color2) {

	uint32_t a = (color2 & AMASK) >> 24;

	if (a == 0)
		return color1;
	else if (a == 255)
		return color2;
	else {
		uint32_t na = 255 - a;
		uint32_t rb = ((na * (color1 & RBMASK)) + (a * (color2 & RBMASK))) >> 8;
		uint32_t ag = (na * ((color1 & AGMASK) >> 8)) + (a * (ONEALPHA | ((color2 & GMASK) >> 8)));

		return ((rb & RBMASK) | (ag & AGMASK));
	}
}


int dwm_get_screen_width () {
	return s_width;
}

int dwm_get_screen_height () {
	return s_height;
}


void register_font_library () {
	FILE file;
	sys_open_file (&file, "font.psf");
	font_data_ = (uint8_t*)dalloc(8096);
	sys_read_file (&file,font_data_,file.size);
}

//! Put a character to console output
void draw_string (const char *s,int pos_x, int pos_y, uint32_t f_color, uint32_t b_color) {
	psf2_t *font = (psf2_t*)font_data_;
    int x,y,kx=0,line,mask,offs;
    int bpl=(font->width+7)/8;
	uint32_t *lfb = (uint32_t*)0x0000600000000000;


	while(*s) {
		unsigned char *glyph = (unsigned char*)font_data_ + font->headersize + 
				(*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;
		offs = kx * (font->width + 1);
		for(y=0;y<font->height;y++) {
			line=offs; mask=1<<(font->width-1);
			for(x=0;x<font->width;x++) {
				lfb[line + pos_x + pos_y* s_width ]=((int)*glyph) & (mask)?f_color:b_color;
				mask>>=1; line+=1;
			}
			lfb[line + pos_x + pos_y * s_width]=b_color; glyph+=bpl; offs+=scanline;
		}
		s++; 
		pos_x++;
		kx++;
    }
}


void enable_update (bool value) {
	update = value;
}

bool is_enable_update() {
	return update;
}

void prepare_screen (rect_t *update_rect) {
	if (update) {
		copy_to_screen2((uint32_t*)0x0000500000000000,update_rect);
		
		enable_update(false);
	}
}

void refresh_screen (rect_t *update_rect) {
	
	//wm_paint_windows (update_rect);
	//add_dirty_rect (update_rect);
	/*********************************************************
	! If no event, simply composite everything and
	! prepare the screen for user
	*/
	//copy_to_screen ((uint32_t*)0x0000600000000000, update_rect);
	uint32_t *buffer = NULL;
	//prepare_screen ();
	unsigned int id = 0;
	rect_t *r = stack_get_rect (&id);
	if (r == NULL)
		return;
	else {
		copy_to_screen ((uint32_t*)0x0000600000000000, r);
		dfree (r);
		sys_fb_update();
	}
}


void initialize_dirty_list () {
	dirty_list = initialize_winlist();
}

void add_dirty_rect (rect_t *rect) {
	win_list_add (dirty_list, rect);
}

void remove_dirty_rect (rect_t *rect) {
	for (int i = 0; i < dirty_list->pointer; i++) {
		rect_t *r = (rect_t*)win_list_get_at (dirty_list, i);
		if (r == rect){
			win_list_remove (dirty_list, i);
			break;
		}
	}
}

