///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  font.h -- Font Registry class
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#include <font.h>
//#include <cff\cff.h>

Font *system_font;


void acrylic_initialize_font () {
	//system_font = LoadCFF("/Corbel.cff");
}

void acrylic_font_draw_string ( char* string, int x, int y, uint32_t color) {
	//CFFDrawString(system_font,string,x, y, color);
}

Font* acrylic_get_system_font () {
	return system_font;
}