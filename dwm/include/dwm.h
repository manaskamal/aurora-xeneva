/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  dwm.h -- Desktop Window Manager {DWM}
 *
 *  /PROJECT - DWM { Desktop Window Manager}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *===============================================
 */

#ifndef __DWM_H__
#define __DWM_H__

#include <stdtypes.h>

//!rectangle structure
typedef struct _rect_ {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
}rect_t;


#pragma pack (push, 1)
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t headersize;
    uint32_t flags;
    uint32_t numglyph;
    uint32_t bytesperglyph;
    uint32_t height;
    uint32_t width;
    uint8_t glyphs;
}psf2_t;
#pragma pack (pop)


//!Messages
#define DWM_MOUSE_MOVE 1
#define DWM_CREATE_WIN 2
#define DWM_KEY_EVENT  3

#define DWM_CREATE_MENU 4
#define DWM_APPEND_MENU 5

//!Provided a rectangle, update it to screen
#define DWM_UPDATE  6
#define DWM_CLOSE 11

//!Window Messages to send
#define WM_CLOSE 6
#define WM_MAXIMIZE 7
#define WM_MINIMIZE 8



#define SET_ALPHA(color, alpha) ( ((color << 8) >> 8) | ((alpha << 24) & 0xff000000))

extern void initialize_screen ();
extern void draw_pixel (unsigned x, unsigned y, uint32_t color );
extern uint32_t get_pixel32bit (unsigned x, unsigned y);
extern void draw_pixel2 (unsigned x, unsigned y, uint32_t color );
extern void draw_pixel3 (unsigned x, unsigned y, uint32_t color );
extern void copy_to_screen(uint32_t *buf, rect_t *r);
extern void copy_to_screen2(uint32_t *buf, rect_t *r);
extern void copy_to_screen2_no_geom(uint32_t *buf, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
extern void copy_to_screen_no_geom(uint32_t *buf, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

extern void draw_rect (unsigned x, unsigned y, unsigned w, unsigned h, uint32_t col);
extern void draw_vertical_line (unsigned x, unsigned y, unsigned length, uint32_t color);
extern void draw_horizontal_line (unsigned x, unsigned y, unsigned length, uint32_t color);
extern void draw_rect_unfilled (int x, int y, int width, int height, uint32_t color);
extern uint32_t alpha_blend (uint32_t color1, uint32_t color2);

extern int dwm_get_screen_width ();
extern int dwm_get_screen_height ();

extern void register_font_library ();
extern void draw_string (const char *s,int pos_x, int pos_y, uint32_t f_color, uint32_t b_color);

extern void enable_update (bool value);
extern uint32_t refresh_screen ();
extern void prepare_screen (rect_t *update_rect) ;

extern void initialize_dirty_list ();
extern void add_dirty_rect (rect_t *rect);
extern void remove_dirty_rect (rect_t *rect);

extern bool is_enable_update();
extern void dwm_add_alpha(uint32_t *buf, rect_t *r, uint32_t add_color);
extern void set_alpha_value(uint32_t color, uint32_t alpha);

#endif