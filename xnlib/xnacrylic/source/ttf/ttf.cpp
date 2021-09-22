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


void ttf_load (unsigned char* data) {
	offset_table_t* off_tb = (offset_table_t*)data;
	sys_print_text ("True Type Font loaded\n");
	sys_print_text ("Apple Scaler Type -> %d\n", off_tb->apple_scaler_type);
	sys_print_text ("Number of Tables -> %d\n", off_tb->num_tables);
	table_dirent_t *dir = (table_dirent_t*)(data + sizeof(offset_table_t));
}