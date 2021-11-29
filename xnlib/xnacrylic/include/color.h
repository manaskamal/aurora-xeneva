/**
 *
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  color.h -- Color codes
 *
 *  /PROJECT - Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==================================================
 */

#ifndef __COLOR_H__
#define __COLOR_H__

#include <stdint.h>
#include <canvas.h>

//! Color codes
#define WHITE   0xFFFFFFFF
#define SILVER  0xFFC0C0C0
#define GRAY    0xFF808080
#define BLACK   0xFF000000
#define RED     0xFFFF0000
#define MAROON  0xFF800000
#define YELLOW  0xFFFFFF00
#define OLIVE   0xFF808000
#define LIME    0xFF00FF00
#define GREEN   0xFF008000
#define AQUA    0xFF00FFFF
#define TEAL    0xFF008080
#define BLUE    0xFF0000FF
#define NAVY    0xFF000080
#define FUCHSIA 0xFFFF00FF
#define PURPLE  0xFF800080

//! more colors are needed!!
#define DARKRED     0xFF8B0000
#define BROWN       0xFFA52A2A
#define FIREBRICK   0xFFB22222
#define CRIMSON     0xFFDC143C
#define TOMATO      0xFFFF6347
#define CORAL       0xFFFF7F50
#define INDIANRED   0xFFCD5C5C
#define LIGHTCORAL  0xFFF08080
#define DARKSALMON  0xFFE9967A
#define SALMON      0xFFFA8072
#define ORANGERED   0xFFFF4500
#define DARKORANGE  0xFFFF8C00
#define ORANGE      0xFFFFA500
#define GOLD        0xFFFFD700
#define DARKGOLDENROD 0xFFB8860B
#define GOLDENROD     0xFFDAA520
#define PALEGOLDENROD 0xFFEEE8AA
#define DARKKHAKI     0xFFBDB76B
#define KHAKI         0xFFF0E68C
#define DARKGREEN     0xFF006400
#define PALEGREEN     0xFF98FB98
#define LIGHTSILVER   0xFFD9D9D9
#define DESKBLUE      0xFF5B7492
#define MENUCLICKBLUE 0xFF6A7298
#define TITLEBAR_DARK  0xFF2F2F2F
#define LIGHTBLACK    0xFF3E3E3E

/** ====!Alpha Percentage Table=====
 ** 100% -- FF
 ** 95%  -- F2
 ** 90%  -- E6
 ** 85%  -- D9
 ** 80%  -- CC
 ** 75%  -- BF
 ** 70%  -- B3
 ** 65%  -- A6
 ** 60%  -- 99
 ** 55%  -- 8C
 ** 50%  -- 80
 ** 45%  -- 73
 ** 40%  -- 66
 ** 35%  -- 59
 ** 30%  -- 4D
 ** 25%  -- 40
 ** 20%  -- 33
 ** 15%  -- 26
 ** 10%  -- 1A
 ** 5%   -- 0D
 ** 0%   -- 00
 **
 ** To put transclucent effect in colors
 ** just put the alpha percentage value infront
 ** of any color, e.g. -> 0xFFFFFF {24-bit RGB White color} to 
 ** 0xD9FFFFFF {32-bit RGBA White color with 85% alpha value}
 **
 ** 0xF0E68C {24-bit RGB KHAKI Color wihout alpha} --> 0xFFF0E68C 
 **                                                   {32-bit RGBA KHAKI Color with opaque}
 **/

#define SET_ALPHA(color,alpha) (((color << 8) >> 8) | ((alpha << 24) & 0xff000000))

#define _RED(color)  ((color & 0x00FF0000) / 0x10000)
#define _GRE(color)  ((color & 0x0000FF00) / 0x100)
#define _BLU(color)  ((color & 0x000000FF) / 0x1)
#define _ALP(color)  ((color & 0xFF000000) / 0x1000000)

#define GET_ALPHA(color)  ((color >> 24) & 0x000000FF)
#define GET_RED(color)  ((color >> 16) & 0x000000FF)
#define GET_GREEN(color) ((color >> 8) & 0x000000FF)
#define GET_BLUE(color)  ((color >> 0) & 0x000000FF)


extern uint32_t alpha_blend (uint32_t color1, uint32_t color2);

extern uint32_t make_col (uint8_t red, uint8_t green, uint8_t blue);
extern uint32_t make_col_a (uint8_t red, uint8_t green, uint8_t blue, uint8_t a);
extern void radial_gradient (canvas_t *canvas,int g_w, int g_h, uint32_t c1, uint32_t c2, int x1, int y1, float r);
extern void linear_gradient (canvas_t *canvas,int x1, int y1, int x2, int y2, uint32_t col1, uint32_t col2);
#endif