/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * imgpng24.cpp -- Image PNG-24 codec
 *
 * /PROJECT - DWM {Aurora's Xeneva}
 * /AUTHOR  - Manas Kamal Choudhury
 *
 * ===========================================
 */

#include <imgpng24.h>


png_chunk_ihdr_t * png_header (void *png_data){
	return (png_chunk_ihdr_t*) ((uint8_t*)png_data + 8);
}

