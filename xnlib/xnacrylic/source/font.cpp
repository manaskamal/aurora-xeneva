///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  font.h -- Font Registry class (currently handles true type fonts)
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#include <font.h>
#include <sys\_file.h>
#include <sys\mmap.h>
#include <sys\_term.h>
#include <ft2build.h>
#include <freetype\ftglyph.h>
#include <canvas.h>
#include <color.h>
#include FT_FREETYPE_H


Font system_font;
static FT_Library lib = 0;
static FT_Error err;
static FT_Face face;
static FT_GlyphSlot slot;

/**
 * acrylic_initialize_font -- initializes font library
 */
void acrylic_initialize_font () {
	UFILE f;
	int fd = sys_open_file("/roboto.ttf", &f);
	for (int i = 0; i < 1024*1024/4096; i++)
		valloc(0xFFFFFFFFC0000000 + i * 4096);

	uint8_t* buff = (uint8_t*)0xFFFFFFFFC0000000;
	sys_read_file (fd,buff,&f);
	uint8_t* buffer = (uint8_t*)buff;
	system_font.data = buffer;
	system_font.name = "roboto";
	system_font.size = f.size;
	
	err = FT_Init_FreeType (&lib);
	err = FT_New_Memory_Face(lib,system_font.data,system_font.size,0,&face);
	err = FT_Set_Pixel_Sizes(face,0,32);
	slot = face->glyph;
	
}


void acrylic_font_set_size (uint32_t sz) {
	err = FT_Set_Pixel_Sizes(face,0,sz / 72.f * 96);
}

void acrylic_font_draw_string (canvas_t *canvas, char* string, int penx, int peny, uint32_t sz, uint32_t color) {
	
	int w = face->glyph->metrics.width;
	int h = face->glyph->metrics.height;
	FT_Bool use_kerning = FT_HAS_KERNING(face);
	uint32_t previous = 0;
	FT_UInt glyph_index;
	while(*string) {
		glyph_index = FT_Get_Char_Index(face,*string);
		err = FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER);
		if (err)
			continue;

		if (use_kerning && previous && glyph_index) {
			FT_Vector delta;
			FT_Get_Kerning(face, previous,glyph_index, FT_KERNING_DEFAULT, &delta);
			penx += delta.x >> 6;
		}

		int x_v = penx + face->glyph->bitmap_left;
		int y_v = peny - face->glyph->bitmap_top;

		for (int i = x_v, p = 0; i < x_v + face->glyph->bitmap.width; i++, p++) {
			for (int j = y_v,q = 0; j < y_v + face->glyph->bitmap.rows; j++, q++) {
				if (face->glyph->bitmap.buffer[q * face->glyph->bitmap.width + p] > 0)
					canvas_get_framebuffer(canvas)[i + j * canvas_get_width(canvas)] = color;
			}
		}
		penx += face->glyph->advance.x >> 6;
		peny += face->glyph->advance.y >> 6;
		previous = glyph_index;
		string++;
	}
}

Font* acrylic_get_system_font () {
	return &system_font;
}

int acrylic_font_get_length(char *string) {
	size_t penx = 0;
	int string_width = 0;
	while(*string) {
		err = FT_Load_Char(face,*string, FT_LOAD_ADVANCE_ONLY);
		if (err)
			continue;
		penx += face->glyph->advance.x >> 6;
		string++;
	}
	return penx;
}

int acrylic_font_get_height(char* string) {
	size_t peny = 0;
	int string_width = 0;
	while(*string) {
		err = FT_Load_Char(face,*string, FT_LOAD_ADVANCE_ONLY);
		if (err)
			continue;
		peny += face->glyph->advance.y >> 6;
		string++;
	}
	return peny;
}

void acrylic_close_font () {
	FT_Done_Face(face);
	FT_Done_FreeType(lib);
	for (int i = 0; i < system_font.size/4096; i++)
		vfree(0xFFFFFFFFC0000000 + i * 4096);
}