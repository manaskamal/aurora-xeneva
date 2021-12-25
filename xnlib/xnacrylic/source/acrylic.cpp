/**
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *  acrylic.cpp -- Acrylic 2d Graphics library
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#include <acrylic.h>
#include <image.h>
#include <color.h>
#include <psf\psf.h>
#include <arrayfont.h>
#include <math.h>


#define sign(x)  ((x < 0) ? -1 :((x > 0) ? 1 : 0))


void acrylic_draw_rect_filled (canvas_t * canvas,unsigned x, unsigned y, unsigned w, unsigned h, uint32_t col) {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			canvas_draw_pixel(canvas,x + i, y + j, col);
		}
		
	}
}


void acrylic_draw_vertical_line (canvas_t * canvas,unsigned x, unsigned y, unsigned length, uint32_t color) {
	acrylic_draw_rect_filled(canvas,x,y,1,length,color);
}

void acrylic_draw_horizontal_line (canvas_t * canvas,unsigned x, unsigned y, unsigned length, uint32_t color) {
	acrylic_draw_rect_filled (canvas,x,y,length,1,color);
}

void acrylic_draw_rect_unfilled (canvas_t * canvas,int x, int y, int width, int height, uint32_t color) {
	acrylic_draw_horizontal_line (canvas, x, y, width, color); //top
	acrylic_draw_vertical_line(canvas, x, y+1, height -2, color); //left
	acrylic_draw_horizontal_line(canvas,x, y + height - 1, width, color); //bottom
	acrylic_draw_vertical_line (canvas,x + width - 1, y + 1, height - 2, color); //right
}


void acrylic_draw_filled_circle (canvas_t * canvas,int o_x, int o_y, int radius, uint32_t fill_color) {
	for(int y = -radius; y <= radius; y++)
		for (int x = -radius; x <= radius; x++)
			if(x * x +y*y <= radius * radius)
				canvas_draw_pixel (canvas,o_x + x, o_y + y, fill_color);
}


void acrylic_draw_image (canvas_t * canvas,Image *img, unsigned x, unsigned y) {
	uint8_t* data = img->image;
	uint32_t w = img->width;
	uint32_t h = img->height;
	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			int j = k + i * w;
			uint8_t r = data[j * 3];        //data[i * 3];
			uint8_t g = data[j * 3 + 1];        //data[i * 3 + 1];
			uint8_t b = data[j * 3 + 2];       //data[i * 3 + 2];
			//uint8_t a = data[j * 3 + 3];
			uint32_t rgba =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
			rgba = rgba | 0xff000000;
			canvas_draw_pixel (canvas,x + k, y + i,rgba);
			j++;
		}
	}
}

void acrylic_draw_string (canvas_t *canvas,unsigned x, unsigned y, char *text, uint32_t b_color, uint32_t f_color) {
	psf_draw_string (canvas,text, x, y, f_color, b_color);
}


void acrylic_draw_arr_font (canvas_t * canvas,unsigned x, unsigned y, char c, uint32_t color) {
	uint8_t shift_line;
	for (int i = 0; i < 12; i++) { //h
		shift_line = font_array[i * 128 + c];
		
		for (int j = 0; j < 8; j++) { //w

			if (shift_line & 0x80)
				canvas_get_framebuffer(canvas)[(i + y) * canvas_get_width(canvas) + (j + x)] = color;
			shift_line <<= 1;
		}
	}

}

void acrylic_draw_arr_string (canvas_t * canvas,unsigned x, unsigned y, char *text, uint32_t color) {
	for (; *text; x += 8)
		acrylic_draw_arr_font(canvas,x, y, *(text)++, color);
}

void acrylic_draw_line (canvas_t * canvas,int x1, int y1, int x2, int y2, uint32_t color) {
	int dx = x2-x1;
    int dy = y2-y1;
    int dxabs = abs(dx);
    int dyabs = abs(dy);
    int sdx = sign(dx);
    int sdy = sign(dy);
    int x = 0;
    int y = 0;
    int px = x1;
    int py = y1;

    canvas_draw_pixel(canvas,px, py, color);
    if (dxabs>=dyabs) {
        for(int i=0;i<dxabs;i++){
            y+=dyabs;
            if (y>=dxabs)
            {
                y-=dxabs;
                py+=sdy;
            }
            px+=sdx;
            canvas_draw_pixel(canvas,px, py, color);
        }
    }
    else {
        for(int i=0;i<dyabs;i++)
        {
            x+=dxabs;
            if (x>=dyabs)
            {
                x-=dyabs;
                px+=sdx;
            }
            py+=sdy;
            canvas_draw_pixel(canvas,px, py, color);
        }
    }
}


void acrylic_draw_circle (canvas_t * canvas,int xc, int yc, int x, int y, uint32_t color) {
	canvas_draw_pixel (canvas,xc + x, yc + y, color);
	canvas_draw_pixel (canvas,xc - x, yc + y, color);
	canvas_draw_pixel (canvas,xc + x, yc - y, color);
	canvas_draw_pixel (canvas,xc - x, yc - y, color);
	canvas_draw_pixel (canvas,xc + y, yc + x, color);
	canvas_draw_pixel (canvas,xc - y, yc + y, color);
	canvas_draw_pixel (canvas,xc + y, yc-x, color);
	canvas_draw_pixel (canvas,xc - y, yc - x, color);
}


void acrylic_circ_bres (canvas_t * canvas,int xc, int yc, int r, uint32_t color) {
	int x = 0, y = r;
	int d = 3 - 2 * r;

	while (y >= x) {
		acrylic_draw_circle (canvas,xc,yc, x, y,color);
		x++;

		if (d > 0) {
			y--;
			d = d + 4 * (x - y) + 10;
		} else 
			d = d + 4 * x + 6;

		acrylic_draw_circle (canvas,xc, yc, x, y, color);
	}
}

void acrylic_draw_bezier (canvas_t * canvas,int x[], int y[], uint32_t color) {

	double xu = 0.0, yu = 0.0, u = 0.0;
	int i = 0;
	for (u = 0.0; u <= 1.0; u += 0.0001) {
		xu = pow(1-u,3)*x[0]+3*u*pow(1-u,2)*x[1]+3*pow(u,2)*(1-u)*x[2]
		    + pow(u,3)*x[3];
		yu= pow(1-u,3)*y[0]+3*u*pow(1-u,2)*y[1]+3*pow(u,2)*(1-u)*y[2] +
			pow(u,3)*y[3];
		canvas_draw_pixel(canvas,(uint32_t)xu, (uint32_t)yu,color);
	}
}


//!FX
void acrylic_set_tint (canvas_t * canvas,float value, uint32_t* img,int w, int h, int x, int y) {
	float div = 1/value;
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++) {

			float r = GET_RED(img[x+i+y+j*canvas_get_scanline(canvas)]);
			float g = GET_GREEN(img[x+i+y+j*canvas_get_scanline(canvas)]);
			float b = GET_BLUE(img[x+i+y+j*canvas_get_scanline(canvas)]);

			r *= div;
			g *= div;
			b *= div;

			uint32_t color = make_col(r,g,b);
			img[x+i+y+j*canvas_get_scanline(canvas)] = color;
		}
	}
}

void acrylic_set_tone (canvas_t * canvas,uint32_t color, uint32_t *img, int x, int y, int w, int h) {
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++) {

			float r = GET_RED(img[x+i+y+j*canvas_get_scanline(canvas)]);
			float g = GET_GREEN(img[x+i+y+j*canvas_get_scanline(canvas)]);
			float b = GET_BLUE(img[x+i+y+j*canvas_get_scanline(canvas)]);
			float a = GET_ALPHA(img[x+i+y+j*canvas_get_scanline(canvas)]);

			r *= GET_RED(color);
			g *= GET_GREEN(color);
			b *= GET_BLUE(color);
			a *= GET_ALPHA(color);

			uint32_t color = make_col_a(r,g,b,a);

			img[x+i+y+j*canvas_get_scanline(canvas)] = color;
		}
	}
}


/**
 * acrylic_box_blur -- Adds box blur filter to a given image using 3x3 matrix kernel
 * @param canvas -- current canvas where to draw
 * @param input -- input image buffer
 * @param output -- output image buffer
 * @param cx -- current x position to focus
 * @param cy -- current y position to focus
 * @param w -- box boundary width 
 * @param h -- box boundary height
 */
void acrylic_box_blur (canvas_t * canvas,unsigned int* input, unsigned int* output, int cx, int cy, int w, int h) {

	for (int j = 0; j < h; j++){
		for (int i = 0; i < w; i++) {
			
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;
			int alphaTotal = 0;

			for (int row=-1; row <= 1; row++) {
				for (int col =-1; col <=1; col++) {
					int currentX = cx + i + col;
					int currentY = cy + j + row;

					if (currentX >= 0 && currentX < canvas_get_width(canvas) && 
						currentY >= 0 && currentY < canvas_get_height(canvas)) {
							uint32_t color = input [(currentY * canvas_get_width(canvas) + currentX)];

							uint8_t red = GET_RED(color);
							uint8_t green = GET_GREEN(color);
							uint8_t blue = GET_BLUE(color);
					
							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
					}
				}
			}

			uint8_t red = redTotal / 9;
			uint8_t green = greenTotal /9;
			uint8_t blue = blueTotal / 9;

			output[(cy + j ) *canvas_get_width(canvas) + (cx + i)] = make_col(red,green,blue);
		}
	}
}


void acrylic_blit_alpha (canvas_t * canvas,unsigned int* dest, unsigned int* src, int x, int y, int w, int h, int sx, int sy) {
	uint32_t * dest_row_start = dest + y * canvas_get_width(canvas) + x;
	uint32_t* row_start = src + 0 * canvas_get_width(canvas) + 0;

	for (int i = 0; i < h; i++) {
		uint32_t *dest_px = dest_row_start;
		uint32_t *row_px = row_start;

		for (int j = 0; j < w; j++) {
			*dest_px = (*dest_px + *row_px++) / 2;
			dest_px++;
			*dest_px = (*dest_px + *row_px++) / 2;
			dest_px++;
			*dest_px = (*dest_px + *row_px++) /2;
			dest_px++;
		}

		dest_row_start += w * canvas_get_width(canvas);
		row_start += w * canvas_get_width(canvas);
	}

}