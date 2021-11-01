///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  cff -- Cactus Font Format 
///!         Font format is directly taken from 
///!         CactusOS an gui based hobby os
///!
///!==================================================

#ifndef __CFF_H__
#define __CFF_H__

#include <stdint.h>
#include <font.h>

#pragma pack(push,1)
typedef struct _cff_header_ {
	uint32_t Magic;
	uint8_t Version;
	uint16_t FontSize;
	uint32_t FontNameOffset;

	uint32_t CharacterOffsets[127-32];
}CFFHeader_t;
#pragma pack(pop)


extern Font* LoadCFF (char *filename);
extern void CFFDrawString (Font *font, char* string, int x, int y, uint32_t color);
#endif