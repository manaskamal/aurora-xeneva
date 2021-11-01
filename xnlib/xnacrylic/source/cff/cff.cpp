///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  cff -- Cactus Font Format 
///!         Font format is directly taken from 
///!         CactusOS an gui based hobby os
///!
///!==================================================


#include <cff\cff.h>
#include <sys\_file.h>
#include <sys\mmap.h>
#include <sys\_term.h>
#include <canvas.h>
#include <color.h>

Font* LoadCFF (char *filename) {

	FILE f;
	int fd = sys_open_file (filename,&f);

	for (int i = 0; i < f.size / 4096; i++) {
		valloc(0xFFFFFFFFA0000000 + i * 4096);
	}
	unsigned char* buffer = (unsigned char*)0xFFFFFFFFA0000000;

	sys_read_file (fd, buffer, &f);

	CFFHeader_t *cff = (CFFHeader_t*)buffer;
	Font* result = new Font();
	result->data = buffer;
	result->name = (char*)(buffer + cff->FontNameOffset);
	result->offsetTable = cff->CharacterOffsets;
	result->size = cff->FontSize;

	const uint8_t* charData = (uint8_t*)(result->data + result->offsetTable[(int)'A' - 32]);
	const uint8_t width = charData[0];
	const uint8_t height = charData[1];
	result->width = width;
	result->height = height;
	return result;
}

void CFFDrawString (Font *font, char* string, int x, int y, uint32_t color) {

	int xoff = x;
	int yoff = y;

	while(*string) {
		char c = *string++;

		const uint8_t* charData = (uint8_t*)(font->data + font->offsetTable[(int)c - 32]);
		const uint8_t width = charData[0];
		const uint8_t height = charData[1];

		for (uint8_t px = 0; px < width; px++) {
			for (uint8_t py = 0; py < height; py++) {

				uint8_t d = charData[py * width + px + 2];

				if (d == 0)
					continue;

				if (d == 255)
					canvas_draw_pixel (px + xoff, py + yoff, color);
				else
					canvas_draw_pixel (px + xoff, py + yoff, alpha_blend(WHITE,color));
				//}
			}
		}
		xoff += width;
	}

}