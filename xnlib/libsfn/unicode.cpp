/*
 * libsfn/unicode.c
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
 * @brief UNICODE functions
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define _UNICODE_BLOCKSDATA
#define _UNICODE_NAMESDATA
#include "unicode.h"
#include "stb_png.h" /* to get stbi_zlib_decode_malloc_guesssize_headerflag() */

static char *unicodedb = NULL, ut[10];

/**
 * Initialize UNICODE names data
 */
void uniname_init()
{
    int i, j;
    char *ptr, *end;

    ptr = unicodedb = (char *)stbi_zlib_decode_malloc_guesssize_headerflag((const char*)&unicode_dat,
        UNICODE_DAT_SIZE, 4096, (int*)&i, 1);
    if(!ptr) return;
    end = ptr + i;

    for(i=j=0;i < UNICODE_NUMNAMES && ptr < end;i++) {
        while(*((uint16_t*)ptr) & 0x8000) {
            j += -(*((int16_t*)ptr));
            ptr += 2;
        }
        uninames[i].unicode = j++;
        uninames[i].rtl = *ptr++;
        uninames[i].name = ptr;
        while(*ptr && ptr < end) ptr++;
        ptr++;
    }

    uninames[0].name = "NOGLYPH";
    uninames[UNICODE_NUMNAMES].name = "";
}

/**
 * Return the UNICODE name data index for UNICODE
 */
int uniname(int unicode)
{
    register int i=0, j=UNICODE_NUMNAMES-1, k, l=22;

    if(!unicodedb) uniname_init();
    if(!unicode) return 0;
    if(unicode > 0x10FFFF) return UNICODE_NUMNAMES;
    while(l--) {
        k = i + ((j-i) >> 1);
        if(uninames[k].unicode == unicode) return k;
        if(i >= j) break;
        if(uninames[k].unicode < unicode) i = k + 1; else j = k;
    }
    return UNICODE_NUMNAMES;
}

/**
 * Free resources
 */
void uniname_free()
{
    if(unicodedb)
        free(unicodedb);
}

/**
 * Convert UNICODE code point into UTF-8 sequence
 */
char *utf8(int i)
{
    if(i<0x80) { ut[0]=i; ut[1]=0;
    } else if(i<0x800) {
        ut[0]=((i>>6)&0x1F)|0xC0;
        ut[1]=(i&0x3F)|0x80;
        ut[2]=0;
    } else if(i<0x10000) {
        ut[0]=((i>>12)&0x0F)|0xE0;
        ut[1]=((i>>6)&0x3F)|0x80;
        ut[2]=(i&0x3F)|0x80;
        ut[3]=0;
    } else {
        ut[0]=((i>>18)&0x07)|0xF0;
        ut[1]=((i>>12)&0x3F)|0x80;
        ut[2]=((i>>6)&0x3F)|0x80;
        ut[3]=(i&0x3F)|0x80;
        ut[4]=0;
    }
    return ut;
}

/**
 * Block name comparition according to UNICODE Inc.
 */
int unicmp(char *a, char *b)
{
    for(;*a && *b;a++,b++) {
        while(*a==' ' || *a=='-' || *a=='_') a++;
        while(*b==' ' || *b=='-' || *b=='_') b++;
        if(tolowercase(*a) != tolowercase(*b)) return 1;
    }
    return *a || *b;
}
