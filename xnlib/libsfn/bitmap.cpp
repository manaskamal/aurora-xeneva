/*
 * libsfn/bitmap.c
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

#ifndef USE_NOFOREIGN

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef HAS_QUANT
#include "libimagequant.h"
#endif
#define STBI_IMPLEMENTATION
#include "stb_png.h"
#include <ssfn.h>
#include "libsfn.h"
#include "bitmap.h"

typedef struct {
    unsigned int magic;
    unsigned int version;
    unsigned int headersize;
    unsigned int flags;
    unsigned int numglyph;
    unsigned int bytesperglyph;
    unsigned int height;
    unsigned int width;
    unsigned char glyphs;
} __attribute__((packed)) psf_t;

/****************************** file format parsers ******************************/

/**
 * Parse PSF2 font (binary)
 */
void psf(unsigned char *ptr, int size)
{
    psf_t *psf = (psf_t*)ptr;
    uint16_t *utbl = NULL;
    uint32_t c, g=0, unicode, nc = 0, numchars = psf->numglyph;
    unsigned char *s, *e, *glyph, *bitmap;
    int i, j, k, l, n;

    s=(unsigned char*)(ptr + psf->headersize + psf->numglyph*psf->bytesperglyph);
    e=ptr + size;
    /* try to fix bad fonts */
    if(s > e) {
        for(s = e; s + 1 > ptr + psf->headersize && (s[-1] || s[0] == 0xFF); s--);
        psf->numglyph = ((int)(s - ptr) - psf->headersize) / psf->bytesperglyph;
    }
    if(s < e) {
        numchars = 0;
        utbl = (uint16_t*)malloc(0x110000*sizeof(uint16_t));
        if(!utbl) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
        memset(utbl, 0, 0x110000*sizeof(uint16_t));
        while(s<e && g<psf->numglyph) {
            c = (uint16_t)((uint8_t)s[0]);
            if(c == 0xFF) { g++; } else {
                if((c & 128) != 0) {
                    if((c & 32) == 0 ) { c=((s[0] & 0x1F)<<6)+(s[1] & 0x3F); s++; } else
                    if((c & 16) == 0 ) { c=((((s[0] & 0xF)<<6)+(s[1] & 0x3F))<<6)+(s[2] & 0x3F); s+=2; } else
                    if((c & 8) == 0 ) { c=((((((s[0] & 0x7)<<6)+(s[1] & 0x3F))<<6)+(s[2] & 0x3F))<<6)+(s[3] & 0x3F); s+=3;}
                    else c=0;
                }
                if(c<0x110000) {
                    utbl[c] = g;
                    numchars++;
                }
            }
            s++;
        }
    }
    if((psf->flags >> 24) && !ctx.baseline) ctx.baseline = (psf->flags >> 24);
    if(psf->width < 1) psf->width = 1;
    if(psf->height < 1) psf->height = 1;
    l = ((psf->width + 7) & ~7) * (psf->height + 1);
    bitmap = (unsigned char*)malloc(l);
    if(!bitmap) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
    for(unicode=rs;unicode<=(uint32_t)re;unicode++) {
        g = utbl? utbl[unicode] : unicode;
        if((!g && unicode && !iswhitespace(unicode)) || g >= psf->numglyph) continue;
        glyph = ptr + psf->headersize + g*psf->bytesperglyph;
        memset(bitmap, 0, l);
        for(i=k=0;i<(int)psf->bytesperglyph;) {
            for(n = 0; n < (int)psf->width; i++)
                for(j=0x80;j && n < (int)psf->width;j>>=1,n++)
                    bitmap[k+n] = (glyph[i] & j) ? 0xFE : 0xFF;
            k += psf->width;
        }
        if(sfn_charadd(unicode, psf->width, psf->height, 0, 0, 0))
            sfn_layeradd(unicode, SSFN_FRAG_BITMAP, 0, 0, psf->width, psf->height, 0xFE, bitmap);
        if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_BITMAP);
    }
    free(bitmap);
    free(utbl);
}

/**
 * Parse GRUB's PFF2 font (binary)
 * yet another messy, resource wasteful, extremely badly documented format...
 */
void pff(unsigned char *ptr, int size)
{
    uint32_t len = 0, unicode, nc = 0, numchars = 0;
    int16_t w = 0, h = 0, p, n, a /*, x, y, mix, miy, max, may*/;
    int i, j, k, m;
    unsigned char *end = ptr + size, *section, *data = ptr, *bitmap;

    ptr += 12;
    while(ptr < end && len < (uint32_t)size) {
        len = (ptr[4] << 24) | (ptr[5] << 16) | (ptr[6] << 8) | ptr[7];
        section = ptr + 8;
        if(!memcmp(ptr, "NAME", 4)) sfn_setstr(&ctx.name, (char*)section, len); else
        if(!memcmp(ptr, "FAMI", 4)) sfn_setstr(&ctx.familyname, (char*)section, len); else
        if(!memcmp(ptr, "WEIG", 4) && section[0]=='b') ctx.style |= SSFN_STYLE_BOLD; else
        if(!memcmp(ptr, "SLAN", 4) && section[0]=='i') ctx.style |= SSFN_STYLE_ITALIC; else
        if(!memcmp(ptr, "MAXW", 4)) w = (section[0] << 8) | section[1]; else
        if(!memcmp(ptr, "MAXH", 4)) h = (section[0] << 8) | section[1]; else
        if(!memcmp(ptr, "ASCE", 4)) ctx.baseline = (section[0] << 8) | section[1]; else
        if(!memcmp(ptr, "CHIX", 4)) {
            /*mix = miy = max = may = 0;*/
            for(end = section + len, ptr = section; ptr < end; ptr += 9) {
                if(!ptr[4]) {
                    n = (data[((ptr[5] << 24) | (ptr[6] << 16) | (ptr[7] << 8) | ptr[8]) + 0] << 8) |
                        data[((ptr[5] << 24) | (ptr[6] << 16) | (ptr[7] << 8) | ptr[8]) + 1];
                    if(n > w) w = n;
                    n = (data[((ptr[5] << 24) | (ptr[6] << 16) | (ptr[7] << 8) | ptr[8]) + 2] << 8) |
                        data[((ptr[5] << 24) | (ptr[6] << 16) | (ptr[7] << 8) | ptr[8]) + 3];
                    if(n > h) h = n;
/*
                    n = (data[((ptr[5] << 24) | (ptr[6] << 16) | (ptr[7] << 8) | ptr[8]) + 4] << 8) |
                        data[((ptr[5] << 24) | (ptr[6] << 16) | (ptr[7] << 8) | ptr[8]) + 5];
                    if(n < mix) { mix = n; } if(n > max) max = n;
                    n = (data[((ptr[5] << 24) | (ptr[6] << 16) | (ptr[7] << 8) | ptr[8]) + 6] << 8) |
                        data[((ptr[5] << 24) | (ptr[6] << 16) | (ptr[7] << 8) | ptr[8]) + 7];
                    if(n < miy) { miy = n; } if(n > may) may = n;
*/
                    numchars++;
                }
            }
            ctx.width = w/* - mix + max*/;
            ctx.height = h/* - miy + may*/;
/*            ctx.baseline -= miy; */
            printf("\r  Name '%s' num_glyphs: %d, ascender: %d, width: %d, height: %d\n", ctx.name, numchars, ctx.baseline,
                ctx.width, ctx.height);
            n = ctx.width * ctx.height;
            bitmap = (unsigned char*)malloc(n);
            if(!bitmap) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
            for(end = section + len; section < end; section += 9) {
                /* undocumented: section[4] supposed to indicate compression of some sort? grub-mkfont.c always writes 0 */
                if(!section[4]) {
                    /* undocumented: section[0] holds left and right joins (or both), not sure what to do with those */
                    unicode = (section[1] << 16) | (section[2] << 8) | section[3];
                    ptr = data + ((section[5] << 24) | (section[6] << 16) | (section[7] << 8) | section[8]);
                    memset(bitmap, 0xFF, n);
                    w = (ptr[0] << 8) | ptr[1]; h = (ptr[2] << 8) | ptr[3];
/*                    x = (ptr[4] << 8) | ptr[5]; y = (ptr[6] << 8) | ptr[7];*/
                    a = (ptr[8] << 8) | ptr[9];
                    p = w; /* + (x < 0 ? 0 : x); h -= y;*/
                    ptr += 10; /*k = (y - miy) * p;*/
                    for(j = k = 0, m = 0x80; j < h; j++, k += p)
                        for(i = 0; i < w; i++, m >>= 1) {
                            if(!m) { m = 0x80; ptr++; }
                            if(ptr[0] & m) bitmap[k + i/* + (x < 0 ? 0 : x)*/] = 0xFE;
                        }
                    if(sfn_charadd(unicode, p, h, a, 0, /*x < 0 ? -x :*/ 0))
                        sfn_layeradd(unicode, SSFN_FRAG_BITMAP, 0, 0, p, h, 0xFE, bitmap);
                    if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_BITMAP);
                }
            }
            free(bitmap);
            break;
        }
        ptr += 8 + len;
    }
}

/**
 * Parse fucked up Windows Console Font (binary)
 */
void fnt(unsigned char *ptr, int size)
{
    int i, j, k, l, m, w, h, p, mn, mx, defchar;
    unsigned char *data = ptr, *bit, map[8192], *bitmap = NULL, ver;
    /* skip over executable header... */
    if(ptr[0] == 'M' && ptr[1] == 'Z') {
        ptr += ((ptr[0x3D] << 8) | ptr[0x3C]); if(ptr[0] != 'N' || ptr[1] != 'E') return;
        ptr += ((ptr[37] << 8) | ptr[36]); j = ((ptr[1] << 8) | ptr[0]); ptr += 2; if(j > 16) return;
        for(i = 0; i < 16 && (ptr[0] || ptr[1]); i++) {
            if(ptr[0] == 0x08 && ptr[1] == 0x80) {
                if(((ptr[3] << 8) | ptr[2]) < 1) { return; } ptr += 8; ptr = data + (((ptr[1] << 8) | ptr[0]) << j); break;
            } else ptr += ((ptr[3] << 8) | ptr[2]) * 12 + 8;
        }
    }
    /* parse Windows resource file */
    if(ptr[0] || (ptr[1] != 2 && ptr[1] != 3) || ((ptr[4] << 16) | (ptr[3] << 8) | ptr[2]) > size ||
        (ptr[66] & 1)) return;
    sfn_setstr(&ctx.name, (char*)(ptr + ((ptr[107] << 16) | (ptr[106] << 8) | ptr[105])), 0);
    sfn_setstr(&ctx.license, (char*)(ptr + 6), 0);
    h = ((ptr[89] << 8) | ptr[88]);
    mn = ptr[95]; mx = ptr[96]; defchar = ptr[97]; ctx.baseline = ((ptr[75] << 8) | ptr[74]);
    if(ptr[80]) ctx.style |= SSFN_STYLE_ITALIC;
    if(((ptr[84] << 8) | ptr[83]) > 400) ctx.style |= SSFN_STYLE_BOLD;
    switch(ptr[90] >> 4) {
        case 2: ctx.family = SSFN_FAMILY_SANS; break;
        case 3: ctx.family = SSFN_FAMILY_MONOSPACE; break;
        case 4: ctx.family = SSFN_FAMILY_HAND; break;
        case 5: ctx.family = SSFN_FAMILY_DECOR; break;
        default: ctx.family = SSFN_FAMILY_SERIF; break;
    }
    printf("\r  Name '%s' num_glyphs: %d, ascender: %d, height: %d\n", ctx.name, mx - mn + 1, ctx.baseline, h);
    if(!h || mn >= mx) return;
    ver = ptr[1]; data = ptr; ptr += (ptr[1] == 3 ? 148 : 118);

    /* get bitmaps */
    for(unicode = mn; unicode <= mx; unicode++, ptr += ver == 3 ? 6 : 4) {
        w = ptr[0]; bit = data + ((ver == 3 ? (ptr[4] << 16) : 0) | (ptr[3] << 8) | ptr[2]);
        p = ((w - 1) >> 3) + 1;
        if(p * h > (int)sizeof(map)) continue;
        bitmap = realloc(bitmap, w * h);
        if(!bitmap) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
        /* I'm fed up. I can't properly get the bytes, so lets copy them into correct order before I get crazy. Ugly, but works */
        for(j = 0; j < p; j++)
            for(k = 0; k < h; k++)
                map[k * p + j] = *bit++;
        for(i = k = l = 0; k < h; k++)
            for(j = 0, l = k * p, m = 0x80; j < w; j++, m >>= 1) {
                if(!m) { m = 0x80; l++; }
                bitmap[i++] = map[l] & m ? 0xFE : 0xFF;
            }
        if(sfn_charadd(unicode, w, h, 0, 0, 0))
            sfn_layeradd(unicode, SSFN_FRAG_BITMAP, 0, 0, w, h, 0xFE, bitmap);
        if(defchar && defchar >= mn && unicode == defchar) {
            sfn_chardel(0);
            if(sfn_charadd(0, w, h, 0, 0, 0))
                sfn_layeradd(0, SSFN_FRAG_BITMAP, 0, 0, w, h, 0xFE, bitmap);
        }
    }
    free(bitmap);
}


/**
 * Parse GNU unifont hex format (text)
 */
void hex(char *ptr, int size)
{
    uint32_t i, j, c, unicode, nc = 0, numchars;
    int w;
    char *end = ptr + size;
    unsigned char bitmap[256];

    numchars = 0;
    for(numchars=0;ptr < end && *ptr;ptr++) if(*ptr=='\n') numchars++;
    ptr = end - size;
    while(ptr < end && *ptr) {
        unicode = gethex(ptr, 6);
        while(*ptr && *ptr!=':') ptr++;
        if(!*ptr) return;
        ptr++;
        while(*ptr && (*ptr==' '||*ptr=='\t')) ptr++;
        if(!*ptr) return;
        memset(bitmap, 0, 256);
        for(i = 0;i<256 && *ptr && *ptr!='\n' && *ptr!='\r';ptr += 2) {
            c = gethex(ptr, 2);
            for(j=0x80;j;j>>=1) bitmap[i++] = (c & j) ? 0xFE : 0xFF;
        }
        while(*ptr && *ptr!='\n' && *ptr!='\r') ptr++;
        while(*ptr && (*ptr=='\n' || *ptr=='\r')) ptr++;
        w = i > 128 ? 16 : 8;
        if(sfn_charadd(unicode, w, 16, 0, 0, 0))
            sfn_layeradd(unicode, SSFN_FRAG_BITMAP, 0, 0, w, 16, 0xFE, bitmap);
        if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_BITMAP);
    }
}

/**
 * Parse X11 BDF font format and FontForge's SplineFontDB with bitmaps (text)
 */
void bdf(char *ptr, int size)
{
    uint32_t c;
    int w = 0, h = 0, i, j, a, b = 0, unicode = 0, nc = 0, numchars = 0, defchar = 0, ps = 0, mx, xx, my, xy, k;
    char *end = ptr + size, *face, *name = NULL, *style = NULL, *manu = NULL;
    unsigned char *bitmap = NULL, sfd = 0, dec[4];

    for(face = ptr; face + 12 < end && *face; face++) {
        if(!memcmp(face, "ENCODING ", 9)) numchars++;
        if(!memcmp(face, "BDFChar:", 8)) { numchars++; sfd = 1; }
        if(!memcmp(face, "BitmapFont: ", 12)) {
            ptr += 12; while(*ptr == ' ') ptr++;
            ps = atoi(ptr); while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            b = atoi(ptr); if(!ctx.baseline) ctx.baseline = b;
            sfd = 1;
        }
    }
    face = NULL;

    while(ptr < end && *ptr) {
        if(!memcmp(ptr, "FACE_NAME ", 10) && !face) {
            ptr += 10; while(*ptr && *ptr!='\"') { ptr++; } ptr++; face = ptr;
        }
        if(!memcmp(ptr, "FONT_NAME ", 10) && !face) {
            ptr += 10; while(*ptr && *ptr!='\"') { ptr++; } ptr++; face = ptr;
        }
        if(!memcmp(ptr, "FONT_VERSION ", 13) && !ctx.revision) {
            ptr += 13; while(*ptr && *ptr!='\"') { ptr++; } ptr++;
            sfn_setstr(&ctx.revision, ptr, 0);
        }
        if(!memcmp(ptr, "ADD_STYLE_NAME ", 15) && !ctx.name && !style) {
            ptr += 15; while(*ptr && *ptr!='\"') { ptr++; } ptr++; style = ptr;
        }
        if(!memcmp(ptr, "FOUNDRY ", 8) && !ctx.manufacturer) {
            ptr += 8; while(*ptr && *ptr!='\"') { ptr++; } ptr++; manu = ptr;
        }
        if(!memcmp(ptr, "HOMEPAGE ", 9) && !ctx.manufacturer && !manu) {
            ptr += 9; while(*ptr && *ptr!='\"') { ptr++; } ptr++; manu = ptr;
        }
        if(!memcmp(ptr, "FAMILY_NAME ", 12) && !ctx.familyname) {
            ptr += 12; while(*ptr && *ptr!='\"') { ptr++; } ptr++;
            sfn_setstr(&ctx.familyname, ptr, 0);
        }
        if(!memcmp(ptr, "WEIGHT_NAME ", 12) && !ctx.subname) {
            ptr += 12; while(*ptr && *ptr!='\"') { ptr++; } ptr++;
            sfn_setstr(&ctx.subname, ptr, 0);
        }
        if(!memcmp(ptr, "COPYRIGHT ", 10) && !ctx.license) {
            ptr += 10; while(*ptr && *ptr!='\"') { ptr++; } ptr++;
            sfn_setstr(&ctx.license, ptr, 0);
        }
        if(!memcmp(ptr, "FONT_ASCENT ", 12)) {
            ptr += 12; if(sfd) { while(*ptr && *ptr != ' ') ptr++; } while(*ptr == ' ') ptr++;
            b = atoi(ptr); if(!ctx.baseline) ctx.baseline = b; }
        if(!memcmp(ptr, "UNDERLINE_POSITION ", 19)) {
            ptr += 19; if(sfd) { while(*ptr && *ptr != ' ') ptr++; } while(*ptr == ' ') ptr++;
            relul = atoi(ptr); if(relul < 0) relul = -relul; }
        if(!memcmp(ptr, "DEFAULT_CHAR ", 13)) {
            ptr += 13; if(sfd) { while(*ptr && *ptr != ' ') ptr++; } while(*ptr == ' ') ptr++;
            defchar = atoi(ptr); }
        if(!memcmp(ptr, "PIXEL_SIZE ", 11) && !ps) {
            ptr += 11; if(sfd) { while(*ptr && *ptr != ' ') ptr++; } while(*ptr == ' ') ptr++;
            ps = atoi(ptr); }
        if(!memcmp(ptr, "ENDPROPERTIES", 13) || !memcmp(ptr, "BDFEndProperties", 16)) break;
        while(*ptr && *ptr!='\n') ptr++;
        while(*ptr=='\n') ptr++;
    }
    if(!ctx.name) {
        if(!face) face = ctx.familyname;
        if(face && style && style[0]) {
            for(i = 0; face[i] && face[i] != '\"' && face[i] != '\r' && face[i] != '\n'; i++);
            for(j = 0; style[j] && style[i] != '\"' && style[i] != '\r' && style[i] != '\n'; j++);
            name = malloc(i + j + 2);
            if(!name) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
            memcpy(name, face, i);
            name[i] = ' ';
            memcpy(name + i + 1, style, j);
            name[i + j + 1] = 0;
            sfn_setstr(&ctx.name, name, 0);
            free(name);
        } else
            sfn_setstr(&ctx.name, ctx.familyname, 0);
    }
    if(!ctx.manufacturer && manu)
        sfn_setstr(&ctx.manufacturer, manu, 0);
    printf("\r  Name '%s' num_glyphs: %d, ascender: %d, underline: %d, height: %d\n", ctx.name, numchars, b, b + relul, ps);

    while(ptr < end && *ptr) {
        if(!sfd) {
            if(!memcmp(ptr, "ENCODING ", 9)) { ptr += 9; unicode = atoi(ptr); }
            if(!memcmp(ptr, "BBX ", 4)) {
                ptr += 4; w = atoi(ptr);
                while(*ptr && *ptr!=' ') ptr++;
                ptr++; h = atoi(ptr);
            }
            if(!memcmp(ptr, "BITMAP", 6)) {
                ptr += 6; while(*ptr && *ptr!='\n') ptr++;
                ptr++;
                if(skipcode && uniname(unicode) == UNICODE_NUMNAMES && !memcmp(ptr,"0000\n7FFE", 9) &&
                    !memcmp(ptr + 35,"7FFE\n7FFE", 9)) ptr += 16*5;
                else if(w > 0 && h > 0 && w * h <= 65536) {
                    bitmap = realloc(bitmap, ((w + 7) & ~7) * (h + 1));
                    if(!bitmap) { fprintf(stderr,"libsfn: memory allocation error\n"); }
                    else {
                        for(i = 0;i < w * h && *ptr; ptr += 2) {
                            while(*ptr=='\n' || *ptr=='\r') ptr++;
                            c = gethex(ptr, 2);
                            for(j=0x80,k=0;j && k < w && i < w * h;k++,j>>=1) bitmap[i++] = c & j ? 0xFE : 0xFF;
                        }
                        while(i < ((w + 7) & ~7) * (h + 1)) bitmap[i++] = 0xFF;
                        if(!skipcode && unicode == defchar) { sfn_chardel(0); unicode = 0; }
                        if(sfn_charadd(unicode, w, h, 0, 0, 0))
                            sfn_layeradd(unicode, SSFN_FRAG_BITMAP, 0, 0, w, h, 0xFE, bitmap);
                    }
                }
                if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_BITMAP);
            }
        } else
        if(!memcmp(ptr, "BDFChar:", 8)) {
            ptr += 8; while(*ptr == ' ') ptr++;
            while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            unicode = atoi(ptr); while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            w = atoi(ptr); while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            mx = atoi(ptr); while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            xx = atoi(ptr); while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            my = atoi(ptr); while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            xy = atoi(ptr); while(*ptr && *ptr != ' ' && *ptr != '\n') { ptr++; } while(*ptr == ' ') ptr++;
            if(*ptr != '\n') a = atoi(ptr); else a = w;
            while(*ptr && *ptr != '\n') { ptr++; } ptr++;
            h = ps; xx -= mx - 1; xy -= my - 1;
            xx = (xx + 7) & ~7;
            if(xx * xy < 65536) {
                bitmap = realloc(bitmap, xx * xy);
                if(!bitmap) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
                for(i = 0, k = 4; i < xx * xy;) {
                    if(k > 3) {
                        if(!*ptr || *ptr == '\r' || *ptr == '\n') break;
                        k = 0;
                        if(*ptr == 'z') { dec[0] = dec[1] = dec[2] = dec[3] = 0; ptr++; }
                        else {
                            c = ((((ptr[0]-'!')*85 + ptr[1]-'!')*85 + ptr[2]-'!')*85 + ptr[3]-'!')*85 + ptr[4]-'!';
                            dec[0] = (c >> 24) & 0xFF; dec[1] = (c >> 16) & 0xFF; dec[2] = (c >> 8) & 0xFF; dec[3] = c & 0xFF;
                            ptr += 5;
                        }
                    }
                    c = dec[k++];
                    for(j = 0x80; j; j >>= 1) bitmap[i++] = c & j ? 0xFE : 0xFF;
                }
                while(i < xx * xy) bitmap[i++] = 0xFF;
                if(!skipcode && unicode == defchar) { sfn_chardel(0); unicode = 0; }
                if(sfn_charadd(unicode, w, h, a, 0, mx < 0 ? -mx : 0))
                    sfn_layeradd(unicode, SSFN_FRAG_BITMAP, 0, 0, xx, xy, 0xFE, bitmap);
            }
            if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_BITMAP);
        }
        while(*ptr && *ptr!='\n') ptr++;
        while(*ptr=='\n') ptr++;
    }
    if(bitmap) free(bitmap);
}

/**
 * Parse X11 PCF font format (binary)
 */
void pcf(unsigned char *ptr, int size)
{
    uint32_t i, j, n, *iptr=(uint32_t*)ptr, fmt, mf=0, bf=0, bs=0, ef=0, offs, mn=0, mx=0, mg=0, siz;
    uint32_t boffs = 0, bitmaps = 0, metrics = 0, encodings = 0;
    unsigned char *bitmap = NULL, *bm;
    char *face = NULL, *name = NULL, *style = NULL, *manu = NULL;
    char *str, *s, *v;
    int x, y, o, a, b = 0, k, w, h = 0, p = 1, r, sx = 1, m, defchar = 0;
#define pcf32(f,o) (f&(1<<2)? (ptr[o+0]<<24)|(ptr[o+1]<<16)|(ptr[o+2]<<8)|ptr[o+3] : \
    (ptr[o+3]<<24)|(ptr[o+2]<<16)|(ptr[o+1]<<8)|ptr[o+0])
#define pcf16(f,o) (f&(1<<2)? (ptr[o+0]<<8)|ptr[o+1] : (ptr[o+1]<<8)|ptr[o+0])

    /* parse tables */
    for(i = 0; i < iptr[1]; i++) {
        fmt = iptr[i*4+3]; offs = iptr[i*4+5];
        if(offs + iptr[i*4+4] >= (uint32_t)size) continue;
        switch(iptr[i*4+2]) {
            case (1<<0): /* PCF_PROPERTIES */
                n = pcf32(fmt,offs+4); str = (char*)ptr + offs + ((n * 9 + 3)/4 + 3)*4;
                for(j = 0; j < n; j++) {
                    s = str + pcf32(fmt,offs + 8 + j * 9); v = str + pcf32(fmt,offs + 13 + j * 9);
                    if(!strcmp(s, "FACE_NAME") && !face) face = v; else
                    if(!strcmp(s, "FONT_NAME") && !face) face = v; else
                    if(!strcmp(s, "FONT_VERSION") && !ctx.revision) sfn_setstr(&ctx.revision, v, 0); else
                    if(!strcmp(s, "ADD_STYLE_NAME") && !ctx.name && !style) style = v; else
                    if(!strcmp(s, "FOUNDRY") && !ctx.manufacturer) manu = v; else
                    if(!strcmp(s, "HOMEPAGE") && !ctx.manufacturer && !manu) manu = v; else
                    if(!strcmp(s, "FAMILY_NAME") && !ctx.familyname) sfn_setstr(&ctx.subname, v, 0); else
                    if(!strcmp(s, "WEIGHT_NAME") && !ctx.subname) sfn_setstr(&ctx.subname, v, 0); else
                    if(!strcmp(s, "COPYRIGHT") && !ctx.license) sfn_setstr(&ctx.license, v, 0); else
                    if(!strcmp(s, "PIXEL_SIZE")) { k = pcf32(fmt,offs + 13 + j * 9); if(k > h) h = k; } else
                    if(!strcmp(s, "UNDERLINE_POSITION")) {
                        relul = (int)pcf32(fmt,offs + 13 + j * 9); if(relul < 0) relul = -relul;
                    }
                }
            break;
            case (1<<2): /* PCF_METRICS */
                metrics = offs; mf = fmt; b = 0;
                if(fmt & 0x100) {
                    n = pcf16(fmt,offs + 4);
                    for(j=0; j<n; j++) { k = (int)ptr[offs+3+6+j*5]-0x80; if(k > b) b = k; }
                    for(j=0; j<n; j++) { k = (int)ptr[offs+4+6+j*5]-0x80 + b; if(k > h) h = k; }
                } else {
                    n = pcf32(fmt,offs + 4);
                    for(j = 0; j < n; j++) { k = pcf16(fmt,offs+6+8+j*12); if(k > b) b = k; }
                    for(j = 0; j < n; j++) { k = pcf16(fmt,offs+8+8+j*12) + b; if(k > h) h = k; }
                }
                if(!mn && !mx && n) mx = n - 1;
                if(!mg || n < mg) mg = n;
            break;
            case (1<<3): /* PCF_BITMAPS */
                boffs = offs + 8; bf = fmt; n = pcf32(fmt,offs+4);
                bitmaps = boffs + n * 4 + 16; bs = iptr[i*4+4] + offs - bitmaps;
                p = 1 << (fmt & 3); sx = fmt & (1 << 2) ? 1 : -1;
                if(!mg || n < mg) mg = n;
            break;
            case (1<<5): /* PCF_BDF_ENCODINGS */
                encodings = offs + 14; ef = fmt;
                mn = (pcf16(fmt, offs + 8)<<8) | pcf16(fmt, offs + 4);
                mx = (pcf16(fmt, offs + 10)<<8) | pcf16(fmt, offs + 6);
                defchar = pcf16(fmt, offs + 12);
            break;
        }
    }
    if(!ctx.name) {
        if(!face) face = ctx.familyname;
        if(face && style && style[0]) {
            i = strlen(face); j = strlen(style);
            name = malloc(i + j + 2);
            if(!name) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
            memcpy(name, face, i);
            name[i] = ' ';
            memcpy(name + i + 1, style, j);
            name[i + j + 1] = 0;
            sfn_setstr(&ctx.name, name, 0);
            free(name);
        } else
            sfn_setstr(&ctx.name, ctx.familyname, 0);
    }
    if(!ctx.manufacturer && manu)
        sfn_setstr(&ctx.manufacturer, manu, 0);
    printf("\r  Name '%s' num_glyphs: %d, ascender: %d, underline: %d, height: %d\n", face, mg, b, b + relul, h);
    if(!b || !h || !mg || !mx || !bitmaps) return;
    if(mg > 65534) mg = 65534;
    ctx.baseline = b;
    ctx.underline = b + relul;
    ctx.height = h;

    /* parse bitmaps and add glyphs. Encoding table must be handled as optional */
    for(unicode = mn; (uint32_t)unicode <= mx; unicode++) {
        if(pbar) (*pbar)(0, 0, unicode, mx - mn + 1, PBAR_BITMAP);
        i = encodings ? pcf16(ef, encodings + unicode * 2) : unicode;
        if(i >= mg) continue;
        offs = pcf32(bf, boffs + i * 4); siz = (i >= mg - 1 ? bs : (uint32_t)pcf32(bf, boffs + i * 4 + 4)) - offs;
        if(mf & 0x100) {
            x = (int)ptr[metrics+6+i*5]-0x80; a = (int)ptr[metrics+3+6+i*5]-0x80;
            w = (int)ptr[metrics+2+6+i*5]-0x80; r = (int)ptr[metrics+1+6+i*5]-0x80;
        } else {
            x = (int16_t)pcf16(mf,metrics+8+i*12); a = pcf16(mf,metrics+6+8+i*12);
            w = pcf16(mf,metrics+4+8+i*12); r = pcf16(mf,metrics+2+8+i*12);
        }
        /* do some heuristics and validation because PCF fonts are *usually* buggy... */
        if(x < 0) { o = -x; x = 0; } else o = 0;
        if(w < r) r = w;
        if(p < 1) p = 1;
        n = (siz / p); y = b - a;
        if(n > (uint32_t)h) n = h;
        if(y < 0) y = 0;
        if(y + n > (uint32_t)h) y = h - n;
        k = n * r; if(k < 1 || k > 65536) continue;
        bitmap = realloc(bitmap, k);
        if(!bitmap) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
        memset(bitmap, 0xFF, k);
        if(siz > n * p) siz = n * p;
        for(j = 0; siz; siz -= p, offs += p) {
            /* seriously, who have thought even for a moment that messing with both byte and bit endianess is sane? */
            bm = ptr + bitmaps + offs + (sx < 0 ? p - 1 : 0); m = bf & (1 << 3) ? 1 << 7 : 1;
            for(k = 0; k < r; k++) {
                bitmap[j++] = bm[0] & m ? 0xFE : 0xFF;
                if(bf & (1 << 3)) { m >>= 1; if(!m) { m = 1 << 7; bm += sx; } }
                else { m <<= 1; if(m > 0x80) { m = 1; bm += sx; } }
            }
        }
        if(unicode == defchar) {
            sfn_chardel(0);
            j = 0;
        } else j = unicode;
        if(sfn_charadd(j, w, h, x+r, 0, o))
            sfn_layeradd(j, SSFN_FRAG_BITMAP, x, y, r, n, 0xFE, bitmap);
    }
    if(bitmap) free(bitmap);
}

/**
 * Parse a pixel map in memory
 */
void pixmap_parse(unsigned char *data, int w, int h)
{
    unsigned char *data2;
    unsigned int i, j, k, x, y, m, o;
    int unicode;

    if(rs==0 && re==0x10FFFF)
        re = h > w ? h / w : w / h;
    if(h > w ) {
        m = h / (re - rs + 1);
        if(m < 8 || w < 8) { fprintf(stderr, "libsfn: unable to determine glyph size\n"); return; }
        for(unicode=rs, i=0; unicode<=re; unicode++, i += w*m) {
            for(y=k=0;y<m;y++)
                for(j=w-1;j>k;j--)
                    if(data[i+y*w+j] < 0xFE) k=j;
            if(sfn_charadd(unicode, w, m, k+1, 0, 0))
                sfn_layeradd(unicode, SSFN_FRAG_PIXMAP, 0, 0, w, m, 0xFE, data + i);
            if(pbar) (*pbar)(0, 0, unicode, re - rs, PBAR_TALLPIX);
        }
    } else {
        m = w / (re - rs + 1);
        if(m < 8 || h < 8) { fprintf(stderr, "libsfn: unable to determine glyph size\n"); return; }
        data2 = (unsigned char*)malloc(m*h);
        if(!data2) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
        for(unicode=rs; unicode<=re; unicode++) {
            for(y=o=k=0;y<(unsigned int)h;y++) {
                i = y*w + (unicode-rs)*m;
                for(x=0;x<m;x++) {
                    if(data[i] < 0xFE && k < x) k = x;
                    data2[o++] = data[i++];
                }
            }
            if(sfn_charadd(unicode, m, h, k+1, 0, 0))
                sfn_layeradd(unicode, SSFN_FRAG_PIXMAP, 0, 0, m, h, 0xFE, data2);
            if(pbar) (*pbar)(0, 0, unicode, re - rs, PBAR_WIDEPIX);
        }
        free(data2);
    }
}

/**
 * Parse PNG format for pixel fonts (binary)
 */
void png(unsigned char *ptr, int size)
{
    unsigned char *data, *data2;
    unsigned int i, w, h, f;
    stbi__context s;
    stbi__result_info ri;
#ifdef HAS_QUANT
    liq_attr *handle = NULL;
    liq_image *input_image = NULL;
    liq_result *quantization_result;
    const liq_palette *liqpalette;
    unsigned char pal[256];
#endif

    s.read_from_callbacks = 0;
    s.img_buffer = s.img_buffer_original = ptr;
    s.img_buffer_end = s.img_buffer_original_end = ptr+size;
    w = h = size = 0;
    ri.bits_per_channel = 8;
    data = (uint8_t*)stbi__png_load(&s, (int*)&w, (int*)&h, (int*)&f, 0, &ri);
    if(!data || (f != STBI_rgb_alpha && f != STBI_rgb) || w < 1 || h < 1)
        { fprintf(stderr,"libsfn: unsupported PNG format\n"); return; }
    data2 = (unsigned char*)malloc(w * h);
    if(!data2) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
#ifdef HAS_QUANT
    handle = liq_attr_create();
    liq_set_max_colors(handle, 254);
    if(f == STBI_rgb_alpha)
        input_image = liq_image_create_rgba(handle, data, w, h, 0);
    if(pbar) (*pbar)(0, 0, 0, 1, PBAR_QUANT);
    if (f == STBI_rgb_alpha && liq_image_quantize(input_image, handle, &quantization_result) == LIQ_OK) {
        liq_set_dithering_level(quantization_result, 1.0);
        liqpalette = liq_get_palette(quantization_result);
        liq_write_remapped_image(quantization_result, input_image, data, w * h);
        for(i = 0; i < liqpalette->count && i < 254; i++) {
            pal[i] = sfn_cpaladd(liqpalette->entries[i].r, liqpalette->entries[i].g,
                liqpalette->entries[i].b, liqpalette->entries[i].a);
        }
        for(i = 0; i < w * h; i++)
            data2[i] = pal[data[i]];
        liq_result_destroy(quantization_result);
    } else
#endif
    {
        if(f == STBI_rgb_alpha)
            for(i = 0; i < w * h; i++) {
                if(pbar) (*pbar)(0, 0, i, w * h, PBAR_QUANT);
                data2[i] = sfn_cpaladd(data[i*4], data[i*4+1], data[i*4+2], data[i*4+3]);
            }
        else
            for(i = 0; i < w * h; i++) {
                if(pbar) (*pbar)(0, 0, i, w * h, PBAR_QUANT);
                data2[i] = sfn_cpaladd(data[i*3], data[i*3+1], data[i*3+2], 255);
            }
    }
#ifdef HAS_QUANT
    if(input_image) liq_image_destroy(input_image);
    liq_attr_destroy(handle);
#endif
    free(data);
    pixmap_parse(data2, w, h);
    free(data2);
}

/**
 * Parse TGA format for pixel fonts (binary)
 */
void tga(unsigned char *ptr, int size)
{
    unsigned char *data;
    int i, j, k, x, y, w, h, o, m;

    o = (ptr[11] << 8) + ptr[10];
    w = (ptr[13] << 8) + ptr[12];
    h = (ptr[15] << 8) + ptr[14];
    if(w<1 || h<1) {
tgaerr: fprintf(stderr,"libsfn: unsupported TGA file format\n");
        return;
    }
    m = ((ptr[1]? (ptr[7]>>3)*ptr[5] : 0) + 18);
    data = (unsigned char*)malloc(w*h);
    if(!data) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
    switch(ptr[2]) {
        case 1:
            if(ptr[6]!=0 || ptr[4]!=0 || ptr[3]!=0 || (ptr[7]!=24 && ptr[7]!=32)) goto tgaerr;
            for(y=i=0; y<h; y++) {
                k = ((!o?h-y-1:y)*w);
                for(x=0; x<w; x++) {
                    j = ptr[m + k++]*(ptr[7]>>3) + 18;
                    data[i++] = sfn_cpaladd(ptr[j+2], ptr[j+1], ptr[j], ptr[7]==32?ptr[j+3]:0xFF);
                }
            }
        break;

        case 2:
            if(ptr[5]!=0 || ptr[6]!=0 || ptr[1]!=0 || (ptr[16]!=24 && ptr[16]!=32)) goto tgaerr;
            for(y=i=0; y<h; y++) {
                j = ((!o?h-y-1:y)*w*(ptr[16]>>3));
                for(x=0; x<w; x++) {
                    data[i++] = sfn_cpaladd(ptr[j+2], ptr[j+1], ptr[j], ptr[16]==32?ptr[j+3]:0xFF);
                    j += ptr[16]>>3;
                }
            }
        break;

        case 9:
            if(ptr[6]!=0 || ptr[4]!=0 || ptr[3]!=0 || (ptr[7]!=24 && ptr[7]!=32)) goto tgaerr;
            y = i = 0;
            for(x=0; x<w*h && m<size;) {
                k = ptr[m++];
                if(k > 127) {
                    k -= 127; x += k;
                    j = ptr[m++]*(ptr[7]>>3) + 18;
                    while(k--) {
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[i++] = sfn_cpaladd(ptr[j+2], ptr[j+1], ptr[j], ptr[7]==32?ptr[j+3]:0xFF);
                    }
                } else {
                    k++; x += k;
                    while(k--) {
                        j = ptr[m++]*(ptr[7]>>3) + 18;
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[i++] = sfn_cpaladd(ptr[j+2], ptr[j+1], ptr[j], ptr[7]==32?ptr[j+3]:0xFF);
                    }
                }
            }
        break;

        case 10:
            if(ptr[5]!=0 || ptr[6]!=0 || ptr[1]!=0 || (ptr[16]!=24 && ptr[16]!=32)) goto tgaerr;
            y = i = 0;
            for(x=0; x<w*h && m<size;) {
                k = ptr[m++];
                if(k > 127) {
                    k -= 127; x += k;
                    while(k--) {
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[i++] = sfn_cpaladd(ptr[m+2], ptr[m+1], ptr[m], ptr[16]==32?ptr[m+3]:0xFF);
                    }
                    m += ptr[16]>>3;
                } else {
                    k++; x += k;
                    while(k--) {
                        if(!(i%w)) { i=((!o?h-y-1:y)*w); y++; }
                        data[i++] = sfn_cpaladd(ptr[m+2], ptr[m+1], ptr[m], ptr[16]==32?ptr[m+3]:0xFF);
                        m += ptr[16]>>3;
                    }
                }
            }
        break;
    }
    pixmap_parse(data, w, h);
    free(data);
}

#endif
