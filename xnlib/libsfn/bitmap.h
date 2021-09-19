/*
 * libsfn/bitmap.h
 *
 * Copyright (C) 2020 bzt (bztsrc@gitlab)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * @brief File functions for bitmap and pixmap fonts
 *
 */

void hex(char *ptr, int size);          /* GNU unifont */
void bdf(char *ptr, int size);          /* X11 Bitmap Distribution Format or FontForge's SplineFontDB with bitmap font*/
void pcf(unsigned char *ptr, int size); /* X11 Portable Compiled Font */
void psf(unsigned char *ptr, int size); /* PC Screen Font (Linux Console) */
void pff(unsigned char *ptr, int size); /* GRUB's Font */
void fnt(unsigned char *ptr, int size); /* Windows Font */
void png(unsigned char *ptr, int size); /* PNG Pixmap */
void tga(unsigned char *ptr, int size); /* TGA Pixmap */

