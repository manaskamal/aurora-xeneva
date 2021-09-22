/*
 * libsfn/sfn.c
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
 * @brief File functions: import, modify and save
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "potracelib/potracelib.h"
#include "zlib.h"
#include "stb_png.h"
#define SSFN_IMPLEMENTATION
//#include <ssfn.h>
#include "libsfn.h"
#include "vector.h"
#include <sys\_file.h>
#include "bitmap.h"

/* potrace bitmap stuff */
#define BM_WORDSIZE ((int)sizeof(potrace_word))
#define BM_WORDBITS (8*BM_WORDSIZE)
#define BM_HIBIT (((potrace_word)1)<<(BM_WORDBITS-1))
#define BM_ALLBITS (~(potrace_word)0)
#define bm_scanline(bm, y) ((bm).map + (ptrdiff_t)(y)*(ptrdiff_t)(bm).dy)
#define bm_index(bm, x, y) (&bm_scanline(bm, y)[(x)/BM_WORDBITS])
#define bm_mask(x) (BM_HIBIT >> ((x) & (BM_WORDBITS-1)))
#define BM_USET(bm, x, y) (*bm_index(bm, x, y) |= bm_mask(x))

int rs = 0, re = 0x10FFFF, replace = 0, skipundef = 0, skipcode = 0, hinting = 0, adv = 0, relul = 0;
int rasterize = 0, origwh = 0, /*lastuni = -1,*/ *fidx/*, dorounderr = 0*/;
sfnctx_t ctx;
sfnprogressbar_t pbar = NULL;

/**
 * Sort layers by type and scanline
 */
int lyrsrt(const void *a, const void *b)
{
    /* pixmap, bitmap first, then contours bigger area first */
    return ((sfnlayer_t*)a)->type != ((sfnlayer_t*)b)->type ?
        ((sfnlayer_t*)b)->type - ((sfnlayer_t*)a)->type :
        (((sfnlayer_t*)a)->miny != ((sfnlayer_t*)b)->miny ?
        ((sfnlayer_t*)a)->miny - ((sfnlayer_t*)b)->miny :
        ((sfnlayer_t*)a)->minx - ((sfnlayer_t*)b)->minx);
}

/**
 * Sort kerning pairs by next character's code point
 */
int krnsrt(const void *a, const void *b)
{
    return ((sfnkern_t*)a)->n - ((sfnkern_t*)b)->n;
}

/**
 * Sort kerning positions by list size
 */
int possrt(const void *a, const void *b)
{
    return ((sfnkpos_t*)b)->len - ((sfnkpos_t*)a)->len;
}

/**
 * Sort fragments by number of reference and type
 */
int frgsrt(const void *a, const void *b)
{
    return ((sfnfrag_t*)a)->cnt != ((sfnfrag_t*)b)->cnt ?
        ((sfnfrag_t*)b)->cnt - ((sfnfrag_t*)a)->cnt :
        (((sfnfrag_t*)a)->type != ((sfnfrag_t*)b)->type ?
        ((sfnfrag_t*)a)->type - ((sfnfrag_t*)b)->type :
        ((sfnfrag_t*)a)->w - ((sfnfrag_t*)b)->w);
}

/**
 * Sort fragment descriptors by type and scanline
 */
int frdsrt(const void *a, const void *b)
{
    return ctx.frags[fidx[((int*)a)[0]]].type != ctx.frags[fidx[((int*)b)[0]]].type ?
        ctx.frags[fidx[((int*)b)[0]]].type - ctx.frags[fidx[((int*)a)[0]]].type :
        (((int*)a)[2] != ((int*)b)[2] ? ((int*)a)[2] - ((int*)b)[2] : ((int*)a)[1] - ((int*)b)[1]);
}

/**
 * Compare two normalized contour fragments, allowing rounding errors in coordinates
 */
int frgcmp(sfncont_t *a, sfncont_t *b, int l)
{
    int i;
    if(l<1) return 0;
    for(; l; l--, a++, b++) {
        if(a->type != b->type) return a->type - b->type;
        i = a->px - b->px; if((i < 0 ? -i : i) > 1) return i;
        i = a->c1x - b->c1x; if((i < 0 ? -i : i) > 1) return i;
        i = a->c2x - b->c2x; if((i < 0 ? -i : i) > 1) return i;
    }
    return 0;
}

/**
 * Parse compressed SSFN font format (binary)
 *
 * @param ptr pointer to buffer
 * @param size size of the buffer
 */
void sfn(unsigned char *ptr, int size)
{
    ssfn_font_t *font = (ssfn_font_t*)ptr;
    sfnlayer_t *currlayer;
    unsigned char *ptr2, color, *frg, *cmd, *bitmap = NULL;
    int f, i, j, k, l, m, n, u, x, y, unicode = 0;

    /* sanity checks */
    if((unsigned int)size != font->size || memcmp((unsigned char*)font + font->size - 4, SSFN_ENDMAGIC, 4))
        { if(!quiet) { fprintf(stderr, "libsfn: missing end magic or incorrect font size\n"); } return; }
    if(!font->fragments_offs) { if(!quiet) { fprintf(stderr, "libsfn: missing fragments table\n"); } return; }
    if(!font->characters_offs) { if(!quiet) { fprintf(stderr, "libsfn: missing characters table\n"); } return; }
    if(font->characters_offs <= font->fragments_offs) {
        if(!quiet) { fprintf(stderr, "libsfn: incorrect characters table offset\n"); } return; }
    if(font->kerning_offs && (font->kerning_offs <= font->characters_offs || (font->ligature_offs &&
        font->kerning_offs <= font->ligature_offs)))
        { if(!quiet) { fprintf(stderr, "libsfn: incorrect kerning table offset\n"); } return; }
    if(font->ligature_offs && font->ligature_offs <= font->characters_offs)
        { if(!quiet) { fprintf(stderr, "libsfn: incorrect ligature table offset\n"); } return; }
    if(font->cmap_offs && ((font->size - font->cmap_offs) & 3))
        { if(!quiet) { fprintf(stderr, "libsfn: incorrect cmap table offset\n"); } return; }

    /* header */
    ctx.family = SSFN_TYPE_FAMILY(font->type);
    ctx.style = SSFN_TYPE_STYLE(font->type);
    ctx.width = font->width;
    ctx.height = font->height;
    ctx.baseline = font->baseline;
    ctx.underline = font->underline;

    /* string table */
    ptr = (unsigned char *)font + sizeof(ssfn_font_t);
    for(i = -6; ptr < (unsigned char *)font + font->fragments_offs; i++) {
        switch(i) {
            case -6: sfn_setstr(&ctx.name, (char*)ptr, 0); break;
            case -5: sfn_setstr(&ctx.familyname, (char*)ptr, 0); break;
            case -4: sfn_setstr(&ctx.subname, (char*)ptr, 0); break;
            case -3: sfn_setstr(&ctx.revision, (char*)ptr, 0); break;
            case -2: sfn_setstr(&ctx.manufacturer, (char*)ptr, 0); break;
            case -1: sfn_setstr(&ctx.license, (char*)ptr, 0); break;
            default: sfn_setstr(&ctx.ligatures[i], (char*)ptr, 0); break;
        }
        ptr += strlen((char*)ptr) + 1;
    }

    /* character mappings */
    ptr = (unsigned char *)font + font->characters_offs;
    ptr2 = (unsigned char *)font + (font->ligature_offs ? font->ligature_offs : (font->kerning_offs ?
        font->kerning_offs : (font->cmap_offs ? font->cmap_offs : font->size - 4)));
    for(unicode = 0; ptr < ptr2;) {
        if(ptr[0] == 0xFF) { unicode += 65536; ptr++; }
        else if((ptr[0] & 0xC0) == 0xC0) { k = (((ptr[0] & 0x3F) << 8) | ptr[1]) + 1; unicode += k; ptr += 2; }
        else if((ptr[0] & 0xC0) == 0x80) { k = (ptr[0] & 0x3F) + 1; unicode += k; ptr++; }
        else {
            if(pbar) (*pbar)(0, 0, unicode, 0x10FFFF, PBAR_RDFILE);
            n = ptr[1]; k = ptr[0];
            u = unicode >= rs && unicode <= re ? sfn_charadd(unicode, ptr[2], ptr[3], ptr[4], ptr[5], ptr[0] & 0x3F) : 0;
            ptr += 6; color = 0xFE;
            for(f = 0; f < n; f++) {
                if(ptr[0] == 255 && ptr[1] == 255) {
                    color = ptr[2]; ptr += k & 0x40 ? 6 : 5;
                } else {
                    x = ptr[0]; y = ptr[1];
                    if(k & 0x40) { m = (ptr[5] << 24) | (ptr[4] << 16) | (ptr[3] << 8) | ptr[2]; ptr += 6; }
                    else { m = (ptr[4] << 16) | (ptr[3] << 8) | ptr[2]; ptr += 5; }
                    if(u) {
                        if(m < font->fragments_offs || (unsigned int)m >= font->characters_offs) {
                            if(!quiet) fprintf(stderr,"libsfn: incorrect fragment offset %x\n",m);
                            return;
                        }
                        frg = (unsigned char*)font + m;
                        if(!(frg[0] & 0x80)) {
                            /* contour */
                            currlayer = sfn_layeradd(unicode, SSFN_FRAG_CONTOUR, 0, 0, 0, 0, color, NULL);
                            if(!currlayer) return;
                            j = (frg[0] & 0x3F);
                            if(frg[0] & 0x40) { j <<= 8; j |= frg[1]; frg++; }
                            j++; frg++;
                            cmd = frg; frg += (j+3)/4;
                            for(i = 0; i < j; i++) {
                                switch((cmd[i / 4] >> ((i & 3) * 2)) & 3) {
                                    case SSFN_CONTOUR_MOVE:
                                        sfn_contadd(currlayer, SSFN_CONTOUR_MOVE, frg[0]+x, frg[1]+y, 0,0, 0,0);
                                        frg += 2;
                                    break;
                                    case SSFN_CONTOUR_LINE:
                                        sfn_contadd(currlayer, SSFN_CONTOUR_LINE, frg[0]+x, frg[1]+y, 0,0, 0,0);
                                        frg += 2;
                                    break;
                                    case SSFN_CONTOUR_QUAD:
                                        sfn_contadd(currlayer, SSFN_CONTOUR_QUAD, frg[0]+x, frg[1]+y, frg[2]+x, frg[3]+y, 0,0);
                                        frg += 4;
                                    break;
                                    case SSFN_CONTOUR_CUBIC:
                                        sfn_contadd(currlayer, SSFN_CONTOUR_CUBIC, frg[0]+x, frg[1]+y, frg[2]+x, frg[3]+y,
                                            frg[4]+x, frg[5]+y);
                                        frg += 6;
                                    break;
                                }
                            }
                        } else if((frg[0] & 0x60) == 0x00) {
                            /* bitmap */
                            m = ((frg[0] & 0x1F) + 1) << 3;
                            bitmap = (unsigned char*)malloc(m * (frg[1] + 1));
                            if(!bitmap) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
                            memset(bitmap, 0xFF, m * (frg[1] + 1));
                            cmd = frg + 2;
                            for(i=l=0;i<(int)((frg[0] & 0x3F) + 1) * (frg[1] + 1);i++) {
                                for(j=1;j<=0x80;j<<=1) bitmap[l++] = (cmd[i] & j) ? 0xFE : 0xFF;
                            }
                            sfn_layeradd(unicode, SSFN_FRAG_BITMAP, x, y, m, frg[1] + 1, color, bitmap);
                            free(bitmap);
                        } else if((frg[0] & 0x60) == 0x20) {
                            /* pixel map */
                            j = (frg[2] + 1) * (frg[3] + 1);
                            bitmap = rle_dec(frg + 4, (((frg[0] & 0x1F) << 8) | frg[1]) + 1, &j);
                            if(!bitmap) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
                            sfn_layeradd(unicode, SSFN_FRAG_PIXMAP, x, y, frg[2] + 1, frg[3] + 1, 0xFE, bitmap);
                            free(bitmap);
                        } else if((frg[0] & 0x60) == 0x40) {
                            /* kerning relation */
                            j = (((frg[0] & 0x3) << 8) | frg[1]) + 1;
                            for(i = 0, frg += 2; i < j; i++, frg += 8) {
                                y = ((frg[2] & 0xF) << 16) | (frg[1] << 8) | frg[0];
                                m = ((frg[5] & 0xF) << 16) | (frg[4] << 8) | frg[3];
                                cmd = (unsigned char*)font + font->kerning_offs + ((((frg[2] >> 4) & 0xF) << 24) |
                                    (((frg[5] >> 4) & 0xF) << 16) | (frg[7] << 8) | frg[6]);
                                while(y <= m) {
                                    l = ((*cmd++) & 0x7F) + 1;
                                    if(cmd[-1] & 0x80) {
                                        if(cmd[0])
                                            while(l-- && y <= m)
                                                sfn_kernadd(unicode, y++, x ? (char)cmd[0] : 0, x ? 0 : (char)cmd[0]);
                                        else
                                            y += l;
                                        cmd++;
                                    } else while(l-- && y <= m) {
                                        if(cmd[0])
                                            sfn_kernadd(unicode, y, x ? (char)cmd[0] : 0, x ? 0 : (char)cmd[0]);
                                        y++;
                                        cmd++;
                                    }
                                }
                            }
                        } else {
                            /* hinting grid */
                            j = frg[0] & 31; frg++;
                            memset(ctx.glyphs[unicode].hintv, 0, 33);
                            memset(ctx.glyphs[unicode].hinth, 0, 33);
                            if(x > 0) {
                                ctx.glyphs[unicode].hintv[0] = j + 1;
                                ctx.glyphs[unicode].hintv[1] = x - 1;
                                for(l = 2; j && l < 33; l++, frg++, j--)
                                    ctx.glyphs[unicode].hintv[l] = ctx.glyphs[unicode].hintv[l - 1] + frg[0];
                            } else
                            if(y > 0) {
                                ctx.glyphs[unicode].hinth[0] = j + 1;
                                ctx.glyphs[unicode].hinth[1] = y - 1;
                                for(l = 2; j && l < 33; l++, frg++, j--)
                                    ctx.glyphs[unicode].hinth[l] = ctx.glyphs[unicode].hinth[l - 1] + frg[0];
                            }
                        }
                        color = 0xFE;
                    }
                }
            }
            unicode++;
        }
    }

    /* color map */
    if(font->cmap_offs) {
        memcpy(ctx.cpal, (uint8_t*)font + font->cmap_offs, font->size - font->cmap_offs - 4);
        ctx.numcpal = (font->size - font->cmap_offs - 4) / 4;
    }
}

/**
 * Parse SSFN ASCII font format (text)
 *
 * @param ptr pointer to zero terminated UTF-8 string
 * @param size size of the buffer
 */
void asc(char *ptr, int size)
{
    int x, y, w = 0, h = 0, o, i, par[6], unicode = -1, nc = 0, numchars, len = 0, line = 1;
    char *end = ptr + size-4, *e;
    unsigned char *bitmap = NULL, color = 0xFE;
    sfnlayer_t *currlayer = NULL;

    for(numchars = 0,e=ptr++;e < end && *e;e++)
        if(e[0]=='\n' && e[1]=='=' && e[2]=='=' && e[3]=='=') numchars++;

    while(ptr < end && *ptr) {
        /* end marker */
        if(ptr[-1] == '\n' && ptr[0] == '#' && ptr[1] == ' ' && ptr[2] == 'E') break;
        /* properties */
        if(ptr[-1] == '\n' && ptr[0] == '$' && ptr[1] >= 'a' && ptr[1] <= 'z') {
            for(e = ptr; e < end && *e && *e != ' ' && *e != '\r' && *e != '\n'; e++);
            while(*e == ' ') e++;
            switch(ptr[1]) {
                case 't': sfn_setfamilytype(atoi(e)); break;
                case 's':
                    if(ptr[2]=='u' && *e == '\"') { e++; sfn_setstr(&ctx.subname, e, 0); } else
                    if(ptr[2]=='t') {
                        for(; *e && *e != '\r' && *e != '\n'; e++)
                            if(e[-1] == ' ') {
                                if(*e == 'b') ctx.style |= SSFN_STYLE_BOLD;
                                if(*e == 'i') ctx.style |= SSFN_STYLE_ITALIC;
                                if(*e == '1') ctx.style |= SSFN_STYLE_USRDEF1;
                                if(*e == '2') ctx.style |= SSFN_STYLE_USRDEF2;
                            }
                    }
                break;
                case 'b': ctx.baseline = atoi(e); break;
                case 'u': ctx.underline = atoi(e); break;
                case 'n': if(*e == '\"') { e++; sfn_setstr(&ctx.name, e, 0); } break;
                case 'f': if(*e == '\"') { e++; sfn_setstr(&ctx.familyname, e, 0); } break;
                case 'r': if(*e == '\"') { e++; sfn_setstr(&ctx.revision, e, 0); } break;
                case 'm': if(*e == '\"') { e++; sfn_setstr(&ctx.manufacturer, e, 0); } break;
                case 'l': if(*e == '\"') { e++; sfn_setstr(&ctx.license, e, 0); } break;
                default: fprintf(stderr,"libsfn: line %d: unknown property\n",line); break;
            }
        }
        if(unicode != -1) {
            /* foreground color command */
            if(*ptr == 'f') {
                color = *ptr=='-' ? 0xFE : sfn_cpaladd(
                    gethex((char*)ptr+2, 2), gethex((char*)ptr+4, 2),
                    gethex((char*)ptr+6, 2), gethex((char*)ptr, 2));
            } else
            /* bitmap layer */
            if(*ptr == '.' || *ptr == 'X' || *ptr == 'x') {
                bitmap = (unsigned char*)realloc(bitmap, len);
                if(!bitmap) { fprintf(stderr,"libsfn: line %d: memory allocation error\n",line); return; }
                for(i = 0; i < len && ptr < end && *ptr && (*ptr == '.' || *ptr == 'X' || *ptr == 'x' ||
                    *ptr == '\r' || *ptr == '\n'); ptr++) {
                    switch(*ptr) {
                        case '\n': line++; break;
                        case 'x':
                        case 'X': bitmap[i++] = 0xFE; break;
                        case '.': bitmap[i++] = 0XFF; break;
                    }
                }
                ptr--;
                sfn_layeradd(unicode, SSFN_FRAG_BITMAP, 0, 0, w, h, color, bitmap);
                currlayer = NULL;
            } else
            /* pixmap layer */
            if((*ptr == '-' || (*ptr >= '0' && *ptr <= '9') || (*ptr >= 'A' && *ptr <= 'F') || (*ptr >= 'a' && *ptr <= 'f')) &&
                ptr[1] != ' ') {
                bitmap = (unsigned char*)realloc(bitmap, len);
                if(!bitmap) { fprintf(stderr,"libsfn: line %d: memory allocation error\n",line); return; }
                for(i = 0; i < len && ptr < end && *ptr && (*ptr == ' ' || *ptr == '-' || (*ptr >= '0' && *ptr <= '9') ||
                    (*ptr >= 'A' && *ptr <= 'F') || (*ptr >= 'a' && *ptr <= 'f') || *ptr == '\r' || *ptr == '\n'); ptr++) {
                        if(*ptr == '\n') line++; else
                        if(*ptr == '-') { bitmap[i++] = 0xFF; while(*ptr == '-') ptr++; } else
                        if((*ptr >= '0' && *ptr <= '9') || (*ptr >= 'A' && *ptr <= 'F') || (*ptr >= 'a' && *ptr <= 'f')) {
                            bitmap[i++] = sfn_cpaladd(gethex(ptr+2, 2), gethex(ptr+4, 2), gethex(ptr+6,2), gethex(ptr,2));
                            ptr += 8;
                        }
                }
                ptr--;
                sfn_layeradd(unicode, SSFN_FRAG_PIXMAP, 0, 0, w, h, color, bitmap);
                currlayer = NULL;
            } else
            /* horizontal hinting grid */
            if(*ptr == 'H') {
                for(i = 0, ptr += 2; i < 32 && ptr < end && *ptr && *ptr != '\r' && *ptr != '\n';) {
                    while(*ptr && (*ptr < '0' || *ptr > '9')) ptr++;
                    ctx.glyphs[unicode].hinth[1+i++] = atoi(ptr);
                    while(*ptr >= '0' && *ptr <= '9') ptr++;
                }
                ctx.glyphs[unicode].hinth[0] = i;
                currlayer = NULL;
            } else
            /* vertical hinting grid */
            if(*ptr == 'V') {
                for(i = 0, ptr += 2; i < 32 && ptr < end && *ptr && *ptr != '\r' && *ptr != '\n';) {
                    while(*ptr && (*ptr < '0' || *ptr > '9')) ptr++;
                    ctx.glyphs[unicode].hintv[1+i++] = atoi(ptr);
                    while(*ptr >= '0' && *ptr <= '9') ptr++;
                }
                ctx.glyphs[unicode].hintv[0] = i;
                currlayer = NULL;
            } else
            /* kerning info */
            if(*ptr == 'k') {
                for(ptr+=2, i=0; ptr < end && *ptr && ptr[1] != '\r' && ptr[1] != '\n'; i++) {
                    par[1] = par[2] = 0;
                    if((ptr[0] == 'U' || ptr[0] == 'u') && ptr[1] == '+') {
                        ptr += 2;
                        par[0] = gethex(ptr, 6);
                        while((*ptr >= '0' && *ptr <= '9') || (*ptr >= 'A' && *ptr <= 'F') || (*ptr >= 'a' && *ptr <= 'f'))
                            ptr++;
                    } else
                        par[0] = ssfn_utf8(&ptr);
                    while(*ptr == ' ') ptr++;
                    par[1] = atoi(ptr);
                    while(*ptr == '-' || (*ptr >= '0' && *ptr <= '9')) ptr++;
                    if(*ptr == ' ') {
                        while(*ptr == ' ') ptr++;
                        par[2] = atoi(ptr);
                        while(*ptr == '-' || (*ptr >= '0' && *ptr <= '9')) ptr++;
                    }
                    if(*ptr == ',') ptr++;
                    while(*ptr == ' ') ptr++;
                    if(i >= ctx.glyphs[unicode].numkern || ctx.glyphs[unicode].kern) {
                        ctx.glyphs[unicode].numkern += 512;
                        ctx.glyphs[unicode].kern = (sfnkern_t*)realloc(ctx.glyphs[unicode].kern,
                            ctx.glyphs[unicode].numkern * sizeof(sfnkern_t));
                        if(!ctx.glyphs[unicode].kern) { fprintf(stderr,"libsfn: line %d: memory allocation error\n",line); return; }
                    }
                    ctx.glyphs[unicode].kern[i].n = par[0];
                    ctx.glyphs[unicode].kern[i].x = par[1];
                    ctx.glyphs[unicode].kern[i].y = par[2];
                }
                if(!i && ctx.glyphs[unicode].kern) {
                    free(ctx.glyphs[unicode].kern);
                    ctx.glyphs[unicode].kern = NULL;
                }
                ctx.glyphs[unicode].numkern = i;
                currlayer = NULL;
            } else
            /* contour */
            if(*ptr == 'm' || *ptr == 'l' || *ptr == 'q' || *ptr == 'c') {
                e = ptr; par[0]=par[1]=par[2]=par[3]=par[4]=par[5]=0;
                for(ptr+=2, i=0; ptr < end && *ptr && *ptr != '\r' && *ptr != '\n' && i < 6; ptr++) {
                    par[i++] = atoi(ptr);
                    while(ptr < end && *ptr!=' ' && *ptr!=',' && ptr[1] && ptr[1] != '\r' && ptr[1] != '\n') ptr++;
                }
                ptr--;
                if(*e == 'm') {
                    if(i<2) {fprintf(stderr,"libsfn: line %d: too few move arguments in U+%06X\n",line,unicode);return ;}
                    currlayer = sfn_layeradd(unicode, SSFN_FRAG_CONTOUR, 0, 0, 0, 0, color, NULL);
                    sfn_contadd(currlayer, SSFN_CONTOUR_MOVE, par[0], par[1], 0,0, 0,0);
                } else if(currlayer) {
                    switch(*e) {
                        case 'l':
                            if(i<2) fprintf(stderr,"libsfn: line %d: too few line arguments in U+%06X\n",line,unicode);
                            else sfn_contadd(currlayer, SSFN_CONTOUR_LINE, par[0], par[1], 0,0, 0,0);
                        break;

                        case 'q':
                            if(i<4) fprintf(stderr,"libsfn: line %d: too few quadratic curve arguments in U+%06X\n",line,unicode);
                            else sfn_contadd(currlayer, SSFN_CONTOUR_QUAD, par[0], par[1], par[2], par[3], 0,0);
                        break;

                        case 'c':
                            if(i<6) fprintf(stderr,"libsfn: line %d: too few bezier curve arguments in U+%06X\n",line,unicode);
                            else sfn_contadd(currlayer, SSFN_CONTOUR_CUBIC, par[0], par[1], par[2], par[3], par[4], par[5]);
                        break;
                    }
                } else {
                    fprintf(stderr,"libsfn: line %d: contour path does not start with a 'move to' command in U+%06X\n",line,
                        unicode);
                    break;
                }
            }
        }
        /* characters */
        if(ptr[-1] == '\n' && ptr[0] == '=' && ptr[1] == '=' && ptr[2] == '=') {
            if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_RDFILE);
            ptr +=  5; unicode = gethex(ptr, 6);
            ptr += 10; w = atoi(ptr); while(*ptr && *ptr != '\r' && *ptr != '\n' && *ptr != '=') ptr++;
            ptr +=  2; h = atoi(ptr); while(*ptr && *ptr != '\r' && *ptr != '\n' && *ptr != '=') ptr++;
            ptr +=  2; x = atoi(ptr); while(*ptr && *ptr != '\r' && *ptr != '\n' && *ptr != '=') ptr++;
            ptr +=  2; y = atoi(ptr); while(*ptr && *ptr != '\r' && *ptr != '\n' && *ptr != '=') ptr++;
            ptr +=  2; o = atoi(ptr); while(*ptr && *ptr != '\r' && *ptr != '\n' && *ptr != '\"') ptr++;
            if(unicode >= SSFN_LIG_FIRST && unicode <= SSFN_LIG_LAST && *ptr == '\"')
                sfn_setstr(&ctx.ligatures[unicode-SSFN_LIG_FIRST], ptr, 0);
            if(w > 255) { w = 255; } if(w < 0) w = 0;
            if(h > 255) { h = 255; } if(h < 0) h = 0;
            if(x > 254) { x = 254; } if(x < 0) x = 0;
            if(y > 254) { y = 254; } if(y < 0) y = 0;
            if(o > 63) { o = 63; } if(o < 0) o = 0;
            len = (w + 1) * (h + 1);
            if(unicode < rs || unicode > re || unicode < 0 || unicode > 0x10FFFF || !sfn_charadd(unicode, w, h, x, y, o))
                unicode = -1;
            color = 0xFE;
        }
        /* go to next line */
        while(ptr < end && *ptr && *ptr != '\r' && *ptr != '\n') ptr++;
        while(*ptr == '\r' || *ptr == '\n') {
            if(*ptr == '\n') line++;
            ptr++;
        }
    }
    if(bitmap) free(bitmap);
}

/**
 * Initialize SSFN context
 *
 * @param pb progressbar callback
 */
void sfn_init(sfnprogressbar_t pb)
{
    memset(&ctx, 0, sizeof(ctx));
    pbar = pb;
}

/**
 * Free SSFN context
 */
void sfn_free()
{
    int i;

    if(ctx.name) free(ctx.name);
    if(ctx.familyname) free(ctx.familyname);
    if(ctx.subname) free(ctx.subname);
    if(ctx.revision) free(ctx.revision);
    if(ctx.manufacturer) free(ctx.manufacturer);
    if(ctx.license) free(ctx.license);
    for(i = 0; i < 0x110000; i++)
        sfn_chardel(i);
    memset(&ctx, 0, sizeof(ctx));
}

/**
 * Remove a character by deleting all of its layers
 *
 * @param unicode character to delete
 */
void sfn_chardel(int unicode)
{
    int i;

    if(unicode < 0 || unicode>0x10FFFF) return;
    if(ctx.glyphs[unicode].layers) {
        for(i = 0; i < ctx.glyphs[unicode].numlayer; i++)
            if(ctx.glyphs[unicode].layers[i].data)
                free(ctx.glyphs[unicode].layers[i].data);
        free(ctx.glyphs[unicode].layers);
    }
    if(ctx.glyphs[unicode].kern)
        free(ctx.glyphs[unicode].kern);
    memset(&ctx.glyphs[unicode], 0, sizeof(sfnglyph_t));
}

/**
 * Add a character to font
 *
 * @param unicode character to add
 * @param w width
 * @param h height
 * @param ax advance x
 * @param ay advance y
 * @param ox overlap x
 * @return true on success
 */
int sfn_charadd(int unicode, int w, int h, int ax, int ay, int ox)
{
    int i;

    if(unicode < rs || unicode > re || unicode < 0 || unicode > 0x10FFFF || (ctx.glyphs[unicode].layers && !replace) ||
        (skipundef && uniname(unicode) == UNICODE_NUMNAMES)) return 0;
    for(i = 0; i < ctx.numskip; i++)
        if(ctx.skip[i] == unicode) return 0;
    if(ctx.glyphs[unicode].layers && replace) sfn_chardel(unicode);
    else memset(&ctx.glyphs[unicode], 0, sizeof(sfnglyph_t));
    if(ax) ay = 0;
    ctx.glyphs[unicode].width = w;
    ctx.glyphs[unicode].height = h;
    ctx.glyphs[unicode].adv_x = ax + (ax ? adv : 0);
    ctx.glyphs[unicode].adv_y = ay + (!ax ? adv: 0);
    ctx.glyphs[unicode].ovl_x = ox;
    ctx.glyphs[unicode].rtl = uninames[uniname(unicode)].rtl;
    return 1;
}

/**
 * Add a layer to character
 *
 * @param unicode character to add layer to
 * @param t type of the layer (SSFN_FRAG_x)
 * @param x offset x
 * @param y offset y
 * @param w width
 * @param h height
 * @param c color index, 254 foreground
 * @param data pointer to data buffer
 * @return pointer to a layer struct or NULL on error
 */
sfnlayer_t *sfn_layeradd(int unicode, int t, int x, int y, int w, int h, int c, unsigned char *data)
{
    sfnlayer_t *lyr = NULL;
    unsigned char *data2;
    int i, j, l;

    if(unicode < rs || unicode > re || unicode < 0 || unicode > 0x10FFFF) return NULL;
    if(t != SSFN_FRAG_CONTOUR && !iswhitespace(unicode) && (!data || isempty(w * h, data))) return NULL;
    if(ctx.glyphs[unicode].numlayer >= 255) {
        if(!quiet) fprintf(stderr, "libsfn: too many layers in U+%06x character's glyph.\n", unicode);
        return NULL;
    }
    if(t != SSFN_FRAG_CONTOUR)
        for(i = 0; i < ctx.glyphs[unicode].numlayer; i++)
            if(ctx.glyphs[unicode].layers[i].type == t && (t != SSFN_FRAG_BITMAP || ctx.glyphs[unicode].layers[i].color == c))
                { lyr = &ctx.glyphs[unicode].layers[i]; break; }
    if(x + w > ctx.glyphs[unicode].width) {
        if(t != SSFN_FRAG_CONTOUR && lyr && lyr->data) {
            l = (x + w) * ctx.glyphs[unicode].height;
            data2 = (unsigned char*)malloc(l + 1);
            if(!data2) { fprintf(stderr,"libsfn: memory allocation error\n"); return NULL; }
            memset(data2, 0xFF, l + 1);
            for(j = 0; j < ctx.glyphs[unicode].height; j++)
                for(i = 0; i < ctx.glyphs[unicode].width; i++)
                    data2[j * (x + w) + i] = lyr->data[ctx.glyphs[unicode].width * j + i];
            free(lyr->data);
            lyr->data = data2;
        }
        ctx.glyphs[unicode].width = x + w;
    }
    if(y + h > ctx.glyphs[unicode].height) {
        if(t != SSFN_FRAG_CONTOUR && lyr && lyr->data) {
            l = ctx.glyphs[unicode].width * (y + h);
            lyr->data = (unsigned char*)realloc(lyr->data, l + 1);
            if(!lyr->data) { fprintf(stderr,"libsfn: memory allocation error\n"); return NULL; }
            memset(lyr->data + ctx.glyphs[unicode].width * ctx.glyphs[unicode].height, 0,
                ctx.glyphs[unicode].width * (y + h - ctx.glyphs[unicode].height));
        }
        ctx.glyphs[unicode].height = y + h;
    }
    if(!lyr) {
        ctx.glyphs[unicode].layers = (sfnlayer_t*)realloc(ctx.glyphs[unicode].layers,
            (ctx.glyphs[unicode].numlayer + 1) * sizeof(sfnlayer_t));
        if(!ctx.glyphs[unicode].layers) { fprintf(stderr,"libsfn: memory allocation error\n"); return NULL; }
        lyr = &ctx.glyphs[unicode].layers[ctx.glyphs[unicode].numlayer++];
        memset(lyr, 0, sizeof(sfnlayer_t));
        lyr->type = t;
        lyr->color = c;
        if(t != SSFN_FRAG_CONTOUR) {
            l = ctx.glyphs[unicode].width * ctx.glyphs[unicode].height;
            lyr->data = (unsigned char*)malloc(l + 1);
            if(!lyr->data) { fprintf(stderr,"libsfn: memory allocation error\n"); return NULL; }
            memset(lyr->data, 0xFF, l + 1);
        }
    }
    if(t != SSFN_FRAG_CONTOUR && data) {
        for(j = 0; j < h; j++)
            for(i = 0; i < w; i++)
                lyr->data[(y + j) * ctx.glyphs[unicode].width + (x + i)] = data[j * w + i];
        if(!ctx.glyphs[unicode].adv_x && !ctx.glyphs[unicode].adv_y) {
            if(ctx.family == SSFN_FAMILY_MONOSPACE)
                ctx.glyphs[unicode].adv_x = ctx.glyphs[unicode].width + 1 + adv;
            else {
                for(y = l = 0; y < ctx.glyphs[unicode].height; y++)
                    for(j = ctx.glyphs[unicode].width; (unsigned int)j > (unsigned int)l; j--)
                        if(lyr->data[y * ctx.glyphs[unicode].width + j]) l = j;
                ctx.glyphs[unicode].adv_x = (iswhitespace(unicode) ? ctx.glyphs[unicode].width : l) + 1 + adv;
            }
        }
    }
    ctx.lx = ctx.ly = 0;
    return lyr;
}

/**
 * Delete a layer from character
 *
 * @param unicode character to remove layer from
 * @param idx layer
 */
void sfn_layerdel(int unicode, int idx)
{
    if(unicode < 0 || unicode > 0x10FFFF || ctx.glyphs[unicode].numlayer < 1 || idx >= ctx.glyphs[unicode].numlayer) return;
    if(ctx.glyphs[unicode].layers[idx].data) free(ctx.glyphs[unicode].layers[idx].data);
    ctx.glyphs[unicode].layers[idx].data = NULL;
    ctx.glyphs[unicode].numlayer--;
    memcpy(&ctx.glyphs[unicode].layers[idx], &ctx.glyphs[unicode].layers[idx+1],
        (ctx.glyphs[unicode].numlayer - idx) * sizeof(sfnlayer_t));
}

/**
 * Add a contour command to a layer
 *
 * @param lyr pointer to layer
 * @param t type (SSFN_CONT_x)
 * @param px next point x
 * @param py next point y
 * @param c1x control point #1 x
 * @param c1y control point #1 y
 * @param c2x control point #2 x
 * @param c2y control point #2 y
 * @return true on success
 */
int sfn_contadd(sfnlayer_t *lyr, int t, int px, int py, int c1x, int c1y, int c2x, int c2y)
{
    sfncont_t *cont;
    int cx, cy;

    if(!lyr || lyr->type != SSFN_FRAG_CONTOUR) return 0;
    if(lyr->len >= 32767) {
        if(!quiet) fprintf(stderr, "libsfn: too many points in contour in U+%06x character's glyph.\n", unicode);
        return 0;
    }
    lyr->data = (unsigned char*)realloc(lyr->data, (lyr->len + 1) * sizeof(sfncont_t));
    if(!lyr->data) { lyr->len = 0; return 0; }
    /* clamp coordinates to prevent overflow */
    if(px<0 || px>254 || py<0 || py>254 || c1x<0 || c1x>254 || c1y<0 || c1y>254 || c2x<0 || c2x>254 || c2y<0 || c2y>254) {
        /* should never happen */
        if(!quiet && lastuni != unicode)
            fprintf(stderr,"\rlibsfn: scaling error U+%06x px %d py %d c1x %d c1y %d c2x %d c2y %d\n", unicode, px, py, c1x, c1y,
                c2x, c2y);
        lastuni = unicode;
        if(px<0) { px = 0; } if(px>254) px = 254;
        if(py<0) { py = 0; } if(py>254) py = 254;
        if(c1x<0) { c1x = 0; } if(c1x>254) c1x = 254;
        if(c1y<0) { c1y = 0; } if(c1y>254) c1y = 254;
        if(c2x<0) { c2x = 0; } if(c2x>254) c2x = 254;
        if(c2y<0) { c2y = 0; } if(c2y>254) c2y = 254;
    }
    /* convert trivial cubic curves to quadratic ones, requires less storage space in fonts */
    if(t == SSFN_CONTOUR_CUBIC) {
        if((c1x >> 1) == (c2x >> 1) && (c1y >> 1) == (c2y >> 1)) { t = SSFN_CONTOUR_QUAD; c2x = c2y = 0; } else
        if(ctx.lx > 0 && ctx.ly > 0) {
            cx = ((c1x - ctx.lx) / 2) + ctx.lx;
            cy = ((c1y - ctx.ly) / 2) + ctx.ly;
            if(((((c2x - cx) / 2) + cx) >> 1) == (px >> 1) && ((((c2y - cy) / 2) + cy) >> 1) == (py >> 1)) {
                t = SSFN_CONTOUR_QUAD; c1x = cx; c1y = cy; c2x = c2y = 0;
            }
        }
    }
    cont = &((sfncont_t *)(lyr->data))[lyr->len++];
    cont->type = t & 0xFF;
    cont->px = px; if(px + 1 > ctx.glyphs[unicode].width) ctx.glyphs[unicode].width = px + 1;
    cont->py = py; if(py + 1 > ctx.glyphs[unicode].height) ctx.glyphs[unicode].height = py + 1;
    cont->c1x = c1x; if(c1x + 1 > ctx.glyphs[unicode].width) ctx.glyphs[unicode].width = c1x + 1;
    cont->c1y = c1y; if(c1y + 1 > ctx.glyphs[unicode].height) ctx.glyphs[unicode].height = c1y + 1;
    cont->c2x = c2x; if(c2x + 1 > ctx.glyphs[unicode].width) ctx.glyphs[unicode].width = c2x + 1;
    cont->c2y = c2y; if(c2y + 1 > ctx.glyphs[unicode].height) ctx.glyphs[unicode].height = c2y + 1;
    ctx.lx = px; ctx.ly = py;
    return 1;
}

/**
 * Add a kerning relation
 *
 * @param unicode previous code point in relation
 * @param next next unicode in relation
 * @param x kerning offset x
 * @param y kerning offset y
 * @return true on success
 */
int sfn_kernadd(int unicode, int next, int x, int y)
{
    int i;

    if(unicode < rs || unicode > re || unicode < 33 || unicode > 0x10FFFF || next < rs || next > re ||
        next < 33 || next > 0x10FFFFF) return 0;
    if(x < -128) x = -128;
    if(x > 127) x = 127;
    if(y < -128) y = -128;
    if(y > 127) y = 127;
    for(i = 0; i < ctx.glyphs[unicode].numkern; i++)
        if(ctx.glyphs[unicode].kern[i].n == next) {
            if(!x && !y) {
                memcpy(&ctx.glyphs[unicode].kern[i], &ctx.glyphs[unicode].kern[i+1], (ctx.glyphs[unicode].numkern - i) *
                    sizeof(sfnkern_t));
                ctx.glyphs[unicode].numkern--;
            } else {
                ctx.glyphs[unicode].kern[i].x = x;
                ctx.glyphs[unicode].kern[i].y = y;
            }
            return 1;
        }
    if(!x && !y) return 0;
    if(ctx.glyphs[unicode].numkern >= 32767) {
        if(!quiet) fprintf(stderr,"libsfn: too many kerning pairs for U+%06x, truncated to 32767\n", unicode);
        return 1;
    }
    i = ctx.glyphs[unicode].numkern++;
    ctx.glyphs[unicode].kern = (sfnkern_t*)realloc(ctx.glyphs[unicode].kern, ctx.glyphs[unicode].numkern * sizeof(sfnkern_t));
    if(!ctx.glyphs[unicode].kern) { ctx.glyphs[unicode].numkern = 0; return 0; }
    while(i > 0 && ctx.glyphs[unicode].kern[i-1].n > next) {
        ctx.glyphs[unicode].kern[i].n = ctx.glyphs[unicode].kern[i-1].n;
        ctx.glyphs[unicode].kern[i].x = ctx.glyphs[unicode].kern[i-1].x;
        ctx.glyphs[unicode].kern[i].y = ctx.glyphs[unicode].kern[i-1].y;
        i--;
    }
    ctx.glyphs[unicode].kern[i].n = next;
    ctx.glyphs[unicode].kern[i].x = x;
    ctx.glyphs[unicode].kern[i].y = y;
    return 1;
}

/**
 * Calculate hinting grid
 *
 * @param unicode character to calculate hints to
 */
void sfn_hintgen(int unicode)
{
    int i, j, x, y, h[256], v[256], mx = 0, my = 0, limit = 3;
    sfncont_t *cont;

    if(unicode < 0 || unicode > 0x10FFFF) return;
    memset(ctx.glyphs[unicode].hintv, 0, 33);
    memset(ctx.glyphs[unicode].hinth, 0, 33);
    if(!ctx.glyphs[unicode].layers) return;
    /* look for vertical or horizontal lines in contour paths */
    memset(h, 0, sizeof(h)); memset(v, 0, sizeof(v));
    for(i = 0; i < ctx.glyphs[unicode].numlayer; i++)
        if(ctx.glyphs[unicode].layers[i].type == SSFN_FRAG_CONTOUR) {
            cont = (sfncont_t*)ctx.glyphs[unicode].layers[i].data;
            x = cont->px; y = cont->py;
            for(j = 0; j < ctx.glyphs[unicode].layers[i].len; j++, cont++) {
                if(cont->type == SSFN_CONTOUR_LINE) {
                    if(x != cont->px && y == cont->py) v[y] += x > cont->px ? x - cont->px : cont->px - x;
                    if(x == cont->px && y != cont->py) h[x] += y > cont->py ? y - cont->py : cont->py - y;
                }
                x = cont->px; y = cont->py;
                if(x > mx) mx = x;
                if(y > my) my = y;
            }
        }
    /* now lets see which coordinates have more points than the limit, those will be the grid lines */
    mx /= limit; my /= limit;
    for(i = 0; i < 256; i++) {
        if(h[i] > my && ctx.glyphs[unicode].hintv[0] < 32)
            ctx.glyphs[unicode].hintv[1 + ctx.glyphs[unicode].hintv[0]++] = i;
        if(v[i] > mx && ctx.glyphs[unicode].hinth[0] < 32)
            ctx.glyphs[unicode].hinth[1 + ctx.glyphs[unicode].hinth[0]++] = i;
    }
}

/**
 * Add a kerning position list
 *
 * @param data pointer to buffer
 * @param len length of buffer
 * @return kpos index or -1 on error
 */
int sfn_kposadd(char *data, int len)
{
    unsigned char *comp;
    int i;

    if(!data || len < 1) return -1;
    comp = rle_enc((unsigned char*)data, len, &len);
    for(i = 0; i < ctx.numkpos; i++)
        if(len == ctx.kpos[i].len && !memcmp(comp, ctx.kpos[i].data, len)) {
            free(comp);
            return i;
        }
    i = ctx.numkpos++;
    ctx.kpos = (sfnkpos_t*)realloc(ctx.kpos, ctx.numkpos * sizeof(sfnkpos_t));
    ctx.kpos[i].idx = i;
    ctx.kpos[i].len = len;
    ctx.kpos[i].data = comp;
    return i;
}

/**
 * Add a fragment to the global list
 *
 * @param type type of the fragment (SSFN_FRAG_x)
 * @param w width
 * @param h height
 * @param data pointer to buffer
 * @return fragment index or -1 on error
 */
int sfn_fragadd(int type, int w, int h, void *data)
{
    int i, l = w * h;
    unsigned char *data2;

    if(w < 1 || h < 0 || !data)
        return -1;
    if(type == SSFN_FRAG_CONTOUR) { l = w * sizeof(sfncont_t); h = 0; } else
    if(type == SSFN_FRAG_KERNING) { l = w * sizeof(sfnkgrp_t); h = 0; } else
    if(type == SSFN_FRAG_HINTING) { l = w; h = 0; }
    for(i = 0; i < ctx.numfrags; i++)
        if(ctx.frags[i].type == type && ctx.frags[i].w == w && ctx.frags[i].h == h && ctx.frags[i].len == l &&
            (type == SSFN_FRAG_CONTOUR && dorounderr ? !frgcmp((sfncont_t*)ctx.frags[i].data, (sfncont_t*)data, w) :
            !memcmp(ctx.frags[i].data, data, l))) {
            ctx.frags[i].cnt++;
            return i;
        }
    if(type != SSFN_FRAG_HINTING || l > 0) {
        data2 = (unsigned char*)malloc(l);
        if(!data2) { fprintf(stderr,"libsfn: memory allocation error\n"); return -1; }
        memcpy(data2, data, l);
    } else
        data2 = NULL;
    i = ctx.numfrags++;
    ctx.frags = (sfnfrag_t*)realloc(ctx.frags, ctx.numfrags * sizeof(sfnfrag_t));
    if(!ctx.frags) { fprintf(stderr,"libsfn: memory allocation error\n"); return -1; }
    ctx.frags[i].idx = i;
    ctx.frags[i].pos = 0;
    ctx.frags[i].cnt = 1;
    ctx.frags[i].type = type;
    ctx.frags[i].w = w;
    ctx.frags[i].h = h;
    ctx.frags[i].len = l;
    ctx.frags[i].data = data2;
    return i;
}

/**
 * Add a fragment to a character
 *
 * @param unicode character to add to
 * @param type type of the fragment (SSFN_FRAG_x)
 * @param w width
 * @param h height
 * @param x offset x
 * @param y offset y
 * @param data pointer to buffer
 * @return true on success
 */
int sfn_fragchr(int unicode, int type, int w, int h, int x, int y, void *data)
{
    int i;

    if(type == SSFN_FRAG_KERNING && w > 1024) {
        if(!quiet) fprintf(stderr, "libsfn: too many kerning groups for U+%06X, truncated to 1024.\n", unicode);
        w = 1024;
    }
    if(ctx.glyphs[unicode].numfrag >= 255) {
        if(!quiet) fprintf(stderr, "libsfn: too many fragments for U+%06X, truncated to 255.\n", unicode);
        return 1;
    }
    i = sfn_fragadd(type, w, h, data);
    if(i != -1) {
        ctx.glyphs[unicode].frags = (int*)realloc(ctx.glyphs[unicode].frags,
            (ctx.glyphs[unicode].numfrag + 1) * 3 * sizeof(int));
        if(!ctx.glyphs[unicode].frags) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
        ctx.glyphs[unicode].frags[ctx.glyphs[unicode].numfrag*3+0] = i;
        ctx.glyphs[unicode].frags[ctx.glyphs[unicode].numfrag*3+1] = x;
        ctx.glyphs[unicode].frags[ctx.glyphs[unicode].numfrag*3+2] = y;
        ctx.glyphs[unicode].numfrag++;
        return 1;
    }
    return 0;
}

/**
 * Add a color map entry
 *
 * @param r red
 * @param g green
 * @param b blue
 * @param a alpha
 * @return color map index
 */
unsigned char sfn_cpaladd(int r, int g, int b, int a)
{
    int i, dr, dg, db, m, q;
    int64_t d, dm;

    if(!r && g<2 && !b && (!a || a==0xFF)) return 0xFF;                 /* background */
    if(r == 0xFF && g == 0xFF && b == 0xFF && a == 0xFF) return 0xFE;   /* foreground */
    for(q=1; q<=8; q++) {
        m=-1; dm=256;
        for(i=0; i<ctx.numcpal && (ctx.cpal[i*4+0] || ctx.cpal[i*4+1] || ctx.cpal[i*4+2]); i++) {
            if(a==ctx.cpal[i*4+3] && b==ctx.cpal[i*4+0] && g==ctx.cpal[i*4+1] && r==ctx.cpal[i*4+2]) return i;
            if(b>>q==ctx.cpal[i*4+0]>>q && g>>q==ctx.cpal[i*4+1]>>q && r>>q==ctx.cpal[i*4+2]>>q) {
                dr = r > ctx.cpal[i*4+2] ? r - ctx.cpal[i*4+2] : ctx.cpal[i*4+2] - r;
                dg = g > ctx.cpal[i*4+1] ? g - ctx.cpal[i*4+1] : ctx.cpal[i*4+1] - g;
                db = b > ctx.cpal[i*4+0] ? b - ctx.cpal[i*4+0] : ctx.cpal[i*4+0] - b;
                d = dr*dr + dg*dg + db*db;
                if(d < dm) { dm = d; m = i; }
                if(!dm) break;
            }
        }
        if(dm>9+9+9 && i<254) {
            ctx.cpal[i*4+3] = a;
            ctx.cpal[i*4+2] = r;
            ctx.cpal[i*4+1] = g;
            ctx.cpal[i*4+0] = b;
            ctx.numcpal++;
            return i;
        }
        if(m>=0) {
            ctx.cpal[m*4+3] = ((ctx.cpal[m*4+3] + a) >> 1);
            ctx.cpal[m*4+2] = ((ctx.cpal[m*4+2] + r) >> 1);
            ctx.cpal[m*4+1] = ((ctx.cpal[m*4+1] + g) >> 1);
            ctx.cpal[m*4+0] = ((ctx.cpal[m*4+0] + b) >> 1);
            return m;
        }
    }
    if(!quiet) fprintf(stderr,"libsfn: unable to add color to color map, should never happen\n");
    return 0xFE;                                                        /* fallback to foreground */
}

/**
 * Add a UNICODE code point to skip from output
 *
 * @param unicode code point to skip
 */
void sfn_skipadd(int unicode)
{
    int i = ctx.numskip++;
    ctx.skip = (int*)realloc(ctx.skip, ctx.numskip * sizeof(int));
    if(!ctx.skip) ctx.numskip = 0;
    else ctx.skip[i] = unicode;
}

/**
 * Dump an SSFN font
 *
 * @param font pointer to an SSFN font
 * @param size size of the font buffer
 * @param dump dump level
 * @return true if font is valid and verified
 */
int sfn_dump(ssfn_font_t *font, int size, int dump)
{
    char *dump_fam[] = { "SERIF", "SANS", "DECOR", "MONO", "HAND", "?" };
    char *dump_str[] = { "name", "family", "subfamily", "revision", "manufacturer", "license" };
    unsigned char *ptr, *ptr2, *cmd;
    unsigned short *lig;
    ssfn_font_t *end;
    int i, j, k, m, n, o, fn = 0, *fo = NULL, *ko = NULL;

    if(!font || size < 32) return 0;
    end = (ssfn_font_t*)((uint8_t*)font + font->size);
    if(!memcmp(font->magic, SSFN_COLLECTION, 4)) {
        printf("font/x-ssfont Scalable Screen Font Collection\n\n---Header---\nmagic: '%c%c%c%c'\nsize:  %d\n",
            font->magic[0], font->magic[1], font->magic[2], font->magic[3], font->size);
        printf("\n---Fonts---\n");
        for(font = (ssfn_font_t*)((uint8_t*)font + 8); font < end; font = (ssfn_font_t*)((uint8_t*)font + font->size)) {
            if(!memcmp(font->magic, "SSFN", 4)) printf("(obsolete SSFN1.0 font) %s\n", (char*)font + 64);
            else printf("%c%c%c%c %d %3d %s\n", SSFN_TYPE_STYLE(font->type) & SSFN_STYLE_BOLD ? 'b':'.',
                SSFN_TYPE_STYLE(font->type) & SSFN_STYLE_ITALIC ? 'i':'.',
                SSFN_TYPE_STYLE(font->type) & SSFN_STYLE_USRDEF1 ? 'u':'.',
                SSFN_TYPE_STYLE(font->type) & SSFN_STYLE_USRDEF2 ? 'U':'.',
                SSFN_TYPE_FAMILY(font->type), font->height,
                (char*)font + sizeof(ssfn_font_t));
        }
        return 1;
    } else
    if(!memcmp(font->magic, "SSFN", 4)) {
        printf("font/x-ssfont Obsolete Scalable Screen Font 1.0 Format\n");
        return 0;
    } else
    if(!memcmp(font->magic, "# Scalab", 8)) {
        printf("text/x-ssfont Scalable Screen Font ASCII Format\n");
        return 1;
    } else
    if(!memcmp(font->magic, SSFN_MAGIC, 4)) {
        printf("font/x-ssfont Scalable Screen Font\n\n---Header---\nmagic:           '%c%c%c%c'\nsize:            %d\n",
            font->magic[0], font->magic[1], font->magic[2], font->magic[3], font->size);
        printf("type:            %02x SSFN_FAMILY_%s%s%s%s%s\n", font->type, dump_fam[SSFN_TYPE_FAMILY(font->type)],
            SSFN_TYPE_STYLE(font->type) & SSFN_STYLE_BOLD ? ", SSFN_STYLE_BOLD" : "",
            SSFN_TYPE_STYLE(font->type) & SSFN_STYLE_ITALIC ? ", SSFN_STYLE_ITALIC" : "",
            SSFN_TYPE_STYLE(font->type) & SSFN_STYLE_USRDEF1 ? ", SSFN_STYLE_USRDEF1" : "",
            SSFN_TYPE_STYLE(font->type) & SSFN_STYLE_USRDEF2 ? ", SSFN_STYLE_USRDEF2" : "");
        ptr = (unsigned char *)font + sizeof(ssfn_font_t);
        printf("features:        %02x rev %d\n", font->features, font->features & 0xF);
        printf("width, height:   %d %d\n", font->width, font->height);
        printf("baseline:        %d\n", font->baseline);
        printf("underline:       %d\n", font->underline);
        i = font->fragments_offs && font->characters_offs ? font->characters_offs - font->fragments_offs : 0;
        printf("fragments_offs:  0x%08x (%d bytes)\n", font->fragments_offs, i);
        i = font->characters_offs ? (font->ligature_offs ? font->ligature_offs : (font->kerning_offs ?
            font->kerning_offs : (font->cmap_offs ? font->cmap_offs : font->size - 4))) - font->characters_offs : 0;
        printf("characters_offs: 0x%08x (%d bytes)\n", font->characters_offs, i);
        i = font->ligature_offs ? (font->kerning_offs ?
            font->kerning_offs : (font->cmap_offs ? font->cmap_offs : font->size - 4)) - font->ligature_offs : 0;
        printf("ligature_offs:   0x%08x (%d bytes)\n", font->ligature_offs, i);
        i = font->kerning_offs ? (font->cmap_offs ? font->cmap_offs : font->size - 4) - font->kerning_offs : 0;
        printf("kerning_offs:    0x%08x (%d bytes)\n", font->kerning_offs, i);
        i = font->cmap_offs ? font->size - 4 - font->cmap_offs : 0;
        printf("cmap_offs:       0x%08x (%d bytes)\n", font->cmap_offs, i);
        if(dump != 2 && dump != 99)
            printf("name:            \"%s\"%s\n", (unsigned char *)font + sizeof(ssfn_font_t),
                dump < 2 ? " (use -dd to see all strings)" : "");
        if((unsigned int)size != font->size || memcmp((unsigned char*)font + font->size - 4, SSFN_ENDMAGIC, 4))
            { fprintf(stderr, "libsfn: missing end magic or incorrect font size\n"); return 0; }
        if(dump != 99) {
            if(!font->fragments_offs) { fprintf(stderr, "libsfn: missing fragments table\n"); return 0; }
            if(!font->characters_offs) { fprintf(stderr, "libsfn: missing characters table\n"); return 0; }
            if(font->characters_offs <= font->fragments_offs)
                { fprintf(stderr, "libsfn: incorrect characters table offset\n"); return 0; }
            if(font->kerning_offs && (font->kerning_offs <= font->characters_offs || (font->ligature_offs &&
                font->kerning_offs <= font->ligature_offs)))
                { fprintf(stderr, "libsfn: incorrect kerning table offset\n"); return 0; }
            if(font->ligature_offs && font->ligature_offs <= font->characters_offs)
                { fprintf(stderr, "libsfn: incorrect ligature table offset\n"); return 0; }
            if(font->cmap_offs && ((font->size - font->cmap_offs) & 3))
                { fprintf(stderr, "libsfn: incorrect cmap table offset\n"); return 0; }
        }
        if(dump == 2 || dump == 99) {
            printf("\n---String Table---\n");
            ptr = (unsigned char *)font + sizeof(ssfn_font_t);
            for(i=0;i<6;i++) { printf("%d. %-12s \"%s\"\n", i, dump_str[i], ptr); ptr += strlen((char*)ptr)+1; }
            ptr2 = (unsigned char *)font + font->fragments_offs;
            for(i=0;ptr<ptr2;i++) { printf("%d. LIGATURE \"%s\"\n", i, ptr); ptr += strlen((char*)ptr)+1; }
            if(ptr != ptr2) { fprintf(stderr, "libsfn: incorrect string table size\n"); return 0; }
        }
        if(dump == 3 || dump == 4 || dump == 99) {
            if(dump != 4) printf("\n---Fragments Table---");
            if(!font->fragments_offs) { if(dump != 4) printf("\nnot present\n"); }
            else {
                ptr = (unsigned char *)font + font->fragments_offs;
                ptr2 = (unsigned char *)font + font->characters_offs;
                while(ptr < ptr2) {
                    fo = (int*)realloc(fo, (fn+1)*sizeof(int));
                    fo[fn++] = (int)(ptr - (unsigned char *)font);
                    if(dump != 4) printf("\n%06x: %02x ", (uint32_t)((uint8_t*)ptr-(uint8_t*)font), ptr[0]);
                    if(!(ptr[0] & 0x80)) {
                        j = (ptr[0] & 0x3F);
                        if(ptr[0] & 0x40) {
                            j <<= 8; j |= ptr[1]; j++;
                            if(dump != 4) printf("%02x SSFN_FRAG_CONTOUR n=%d\n",ptr[1],j);
                            ptr += 2;
                        } else {
                            j++;
                            if(dump != 4) printf(" SSFN_FRAG_CONTOUR n=%d\n",j);
                            ptr++;
                        }
                        cmd = ptr; ptr += (j+3)/4;
                        for(i = 0; i < j; i++) {
                            k = (cmd[i / 4] >> ((i & 3) * 2)) & 3;
                            if(dump != 4) printf(" %02x:%d=%d", cmd[i / 4], (i & 3) * 2, k);
                            switch(k) {
                                case SSFN_CONTOUR_MOVE:
                                    if(dump != 4) printf(" SSFN_CONTOUR_MOVE  p=%3d,%3d\n",ptr[0],ptr[1]);
                                    ptr += 2;
                                break;
                                case SSFN_CONTOUR_LINE:
                                    if(dump != 4) printf(" SSFN_CONTOUR_LINE  p=%3d,%3d\n",ptr[0],ptr[1]);
                                    ptr += 2;
                                break;
                                case SSFN_CONTOUR_QUAD:
                                    if(dump != 4) printf(" SSFN_CONTOUR_QUAD  p=%3d,%3d c1=%3d,%3d\n",ptr[0],ptr[1],ptr[2],ptr[3]);
                                    ptr += 4;
                                break;
                                case SSFN_CONTOUR_CUBIC:
                                    if(dump != 4) printf(" SSFN_CONTOUR_CUBIC p=%3d,%3d c1=%3d,%3d c2=%3d,%3d\n",ptr[0],ptr[1],
                                        ptr[2],ptr[3],ptr[4],ptr[5]);
                                    ptr += 6;
                                break;
                            }
                        }
                    } else
                    if((ptr[0] & 0x60) == 0) {
                        j = (ptr[0] & 0x1F) + 1;
                        if(dump != 4) printf("%02x SSFN_FRAG_BITMAP p=%d h=%d\n",ptr[1],j,ptr[1]+1);
                        j *= ptr[1] + 1;
                        for(ptr += 2, i = 0; i < j && i < 16; i++)
                            if(dump != 4) printf(" %02x", ptr[i]);
                        if(dump != 4) printf("%s\n", j > 15 ? "..." : "");
                        ptr += j;
                    } else
                    if((ptr[0] & 0x60) == 0x20) {
                        j = (((ptr[0] & 0x1F) << 8) | ptr[1]) + 1;
                        if(dump != 4) printf("%02x %02x %02x SSFN_FRAG_PIXMAP s=%d w=%d h=%d\n",ptr[1],ptr[2],ptr[3],j,
                            ptr[2]+1,ptr[3]+1);
                        for(ptr += 4, i = 0; i < j && i < 16; i++)
                            if(dump != 4) printf(" %02x", ptr[i]);
                        if(dump != 4) printf("%s\n", j > 15 ? "..." : "");
                        ptr += j;
                    } else
                    if((ptr[0] & 0x60) == 0x40) {
                        if(!font->kerning_offs) { fprintf(stderr, "libsfn: kerning fragment without kerning table\n"); return 0; }
                        j = (((ptr[0] & 0x3) << 8) | ptr[1]) + 1;
                        if(dump != 4) printf("%02x %02x SSFN_FRAG_KERNING n=%d c=%d\n", ptr[1], ptr[2], j, (ptr[2] >> 2) & 7);
                        for(ptr += 2, i = 0; i < j; i++, ptr += 8) {
                            k = (((ptr[2] >> 4) & 0xF) << 24) | (((ptr[5] >> 4) & 0xF) << 16) | (ptr[7] << 8) | ptr[6];
                            if(dump != 4) {
                                printf(" %02x %02x %02x %02x %02x %02x %02x %02x  U+%06X..U+%06X o=%06x\n",
                                    ptr[0],ptr[1],ptr[2],ptr[3],ptr[4],ptr[5],ptr[6],ptr[7],
                                    ((ptr[2] & 0xF) << 16) | (ptr[1] << 8) | ptr[0],
                                    ((ptr[5] & 0xF) << 16) | (ptr[4] << 8) | ptr[3],
                                    k + font->kerning_offs);
                            }
                        }
                    } else {
                        j = (ptr[0] & 0x1F) + 1;
                        if(dump != 4) printf("SSFN_FRAG_HINTING n=%d\n", j);
                        for(ptr++, i = 0; i < j; i++, ptr++)
                            if(dump != 4) printf(" %02x (%d)", ptr[0], ptr[0]);
                        if(dump != 4) printf("\n");
                    }
                }
                if(ptr != ptr2) { fprintf(stderr, "libsfn: incorrect fragments table size\n"); return 0; }
            }
        }
        if(dump == 4 || dump == 99) {
            printf("\n---Characters Table---\n");
            if(!font->characters_offs) printf("not present\n");
            else {
                ptr = (unsigned char *)font + font->characters_offs;
                ptr2 = (unsigned char *)font + (font->ligature_offs ? font->ligature_offs : (font->kerning_offs ?
                    font->kerning_offs : (font->cmap_offs ? font->cmap_offs : font->size - 4)));
                for(j = 0; ptr < ptr2;) {
                    printf("%06lx:", (unsigned long int)ptr - (unsigned long int)font);
                    if(ptr[0] == 0xFF) { printf(" ff                 --- skip 65536 code points ---\n"); j += 65536; ptr++; }
                    else
                    if((ptr[0] & 0xC0) == 0xC0) {
                        k = (((ptr[0] & 0x3F) << 8) | ptr[1]) + 1;
                        printf(" %02x %02x              --- skip %5d code points ---\n", ptr[0], ptr[1], k);
                        j += k; ptr += 2;
                    } else
                    if((ptr[0] & 0xC0) == 0x80) {
                        k = (ptr[0] & 0x3F) + 1;
                        printf(" %02x                 --- skip %5d code point%s ---\n", ptr[0], k, k>1?"s":"");
                        j += k; ptr++;
                    } else {
                        n = ptr[1]; k = ptr[0];
                        printf(" %02x %02x %02x %02x %02x %02x  --- U+%06X n=%d f=%d o=%d w=%d h=%d ax=%d ay=%d ---\n",
                            ptr[0],ptr[1],ptr[2],ptr[3],ptr[4],ptr[5],j,n,k&0x40?1:0,k&0x3F,
                            ptr[2],ptr[3],ptr[4],ptr[5]);
                        ptr += 6;
                        for(i = 0; i < n; i++) {
                            if(ptr[0] == 255 && ptr[1] == 255) {
                                printf("           ff ff %02x 00 00 %scolor %d\n",ptr[2],k & 0x40 ? "00 " : "",ptr[2]);
                                if(!font->cmap_offs || font->cmap_offs + ptr[2] * 4 >= font->size - 4)
                                    { printf("\n"); fprintf(stderr, "libsfn: incorrect color index %d for U+%06X\n",
                                            ptr[2], j); return 0; }
                                ptr += k & 0x40 ? 6 : 5;
                            } else {
                                if(k & 0x40) {
                                    m = (ptr[5] << 24) | (ptr[4] << 16) | (ptr[3] << 8) | ptr[2];
                                    printf("           %02x %02x %02x %02x %02x %02x x=%3d y=%3d frag=%06x ",ptr[0],ptr[1],
                                        ptr[2],ptr[3],ptr[4],ptr[5], ptr[0],ptr[1],m);
                                    ptr += 6;
                                } else {
                                    m = (ptr[4] << 16) | (ptr[3] << 8) | ptr[2];
                                    printf("           %02x %02x %02x %02x %02x x=%3d y=%3d frag=%06x ",ptr[0],ptr[1],ptr[2],
                                        ptr[3],ptr[4], ptr[0],ptr[1],m);
                                    ptr += 5;
                                }
                                for(o = 0; o < fn && m != fo[o]; o++);
                                if(o >= fn)
                                    { printf("\n"); fprintf(stderr, "libsfn: incorrect fragment offset %x for U+%06X\n", m, j);
                                      return 0; }
                                printf(" SSFN_FRAG_");
                                cmd = (unsigned char*)font + m;
                                if(!(cmd[0] & 0x80)) printf("CONTOUR");
                                else if((cmd[0] & 0x60) == 0x00) printf("BITMAP");
                                else if((cmd[0] & 0x60) == 0x20) printf("PIXMAP");
                                else if((cmd[0] & 0x60) == 0x40) printf("KERNING");
                                else printf("HINTING");
                                printf("\n");
                            }
                        }
                        j++;
                    }
                }
                if(ptr != ptr2)
                    { fprintf(stderr, "libsfn: incorrect characters table size\n"); return 0; }
            }
            printf("\n---Ligatures Table---\n");
            if(!font->ligature_offs) printf("not present\n");
            else {
                lig = (unsigned short*)((unsigned char *)font + font->ligature_offs);
                for(i = 0; i < SSFN_LIG_LAST - SSFN_LIG_FIRST + 1 && lig[i]; i++) {
                    if(lig[i] >= font->fragments_offs) { fprintf(stderr, "libsfn: incorrect ligature offset\n"); return 0; }
                    printf(" U+%04X: \"%s\"\n", SSFN_LIG_FIRST + lig[i], (char*)font + lig[i]);
                }
            }
        }
        if(dump == 5 || dump == 99) {
            printf("\n---Kerning Table---\n");
            if(!font->kerning_offs) { printf("not present\n"); }
            else {
                ptr = (unsigned char *)font + font->kerning_offs;
                ptr2 = (unsigned char *)font + (font->cmap_offs ? font->cmap_offs : font->size - 4);
                while(ptr < ptr2) {
                    printf("%06x: %02x", (int)(ptr - (unsigned char *)font), ptr[0]);
                    i = ((*ptr++) & 0x7F) + 1;
                    if(ptr[-1] & 0x80) {
                        printf(" %02x", ptr[0]);
                        ptr++;
                    } else
                        while(i--) printf(" %02x", *ptr++);
                    printf("\n");
                }
                if(ptr != ptr2) { fprintf(stderr, "libsfn: incorrect kerning table size\n"); return 0; }
            }
        }
        if(dump == 6 || dump == 99) {
            printf("\n---Color Map Table---\n");
            if(!font->cmap_offs) printf("not present\n");
            else {
                ptr = (unsigned char *)font + font->cmap_offs;
                printf("number of colors: %d\n", (int)((((unsigned char*)end - 4) - ptr) / 4));
                printf("   "); for(i=0;i<16;i++) printf("       %02X",i);
                for(i=0;i<254 && ptr < (unsigned char*)end - 4;i++) {
                    if(!(i&15)) printf("\n%02X: ", i);
                    printf("%02x%02x%02x%02x ",ptr[3],ptr[2],ptr[1],ptr[0]);
                    ptr += 4;
                }
                printf("\n");
            }
        }
        if(fo) free(fo);
        if(ko) free(ko);
        printf("\nFont parsed OK.\n");
        return 1;
    } else
        printf("unknown format\n");
    return 0;
}

/**
 * Load / import a font into SSFN context
 *
 * @param filename file to load
 * @param dump dump level (0 no dump)
 * @return true on success
 */
int sfn_load(char *filename, int dump)
{
    unsigned char *data = NULL, *data2 = NULL, *o, c;
    int r, size;
	FILE f;
	sys_open_file(&f,filename);
	size = f.size;
    data = (unsigned char*)malloc(size + 1);
    if(!data) { return 0; }
	sys_read_file(&f,data,f.size);
   
    ctx.total += (long int)size;
    ctx.filename = filename;

    if(data[0] == 0x1f && data[1] == 0x8b) {
        o = data; data += 2;
        if(*data++ != 8 || !size) { free(o); return 0; }
        c = *data++; data += 6;
        if(c & 4) { r = *data++; r += (*data++ << 8); data += r; }
        if(c & 8) { while(*data++ != 0); }
        if(c & 16) { while(*data++ != 0); }
        data2 = (unsigned char*)stbi_zlib_decode_malloc_guesssize_headerflag((const char*)data, size, 4096, &size, 0);
        free(o);
        if(!data2) return 0;
        data2 = (unsigned char*)realloc(data2, size + 1);
        if(!data2) return 0;
        data = data2;
    }
    data[size] = 0;

    if(dump > 0) {
        printf("Dumping '%s'\n\n", filename);
        return sfn_dump((ssfn_font_t *)data, size, dump);
    }

    r = 1;
    if(data[0]=='S' && data[1]=='F' && data[2]=='N' && data[3]=='C') {
        fprintf(stderr, "libsfn: file '%s' is a collection with multiple fonts. Extract fonts first.\n", filename);
        r = 0;
    } else if(data[0]=='S' && data[1]=='F' && data[2]=='N' && data[3]=='2') {
        printf("Loaded '%s' (SSFN BIN, %X - %X)\n", filename, rs, re);
        sfn(data, size);
    } else if(data[0]=='#' && data[1]==' ' && data[2]=='S' && data[3]=='c') {
        printf("Loaded '%s' (SSFN ASCII, %X - %X)\n", filename, rs, re);
        asc((char*)data, size);
#ifndef USE_NOFOREIGN
    } else if(data[0]==0x72 && data[1]==0xB5 && data[2]==0x4A && data[3]==0x86) {
        printf("Loaded '%s' (PSF2, %X - %X)\n", filename, rs, re);
        psf(data, size);
    } else if(data[8]=='P' && data[9]=='F' && data[10]=='F' && data[11]=='2') {
        printf("Loaded '%s' (PFF2, %X - %X)\n", filename, rs, re);
        pff(data, size);
    } else if((data[0]=='M' && data[1]=='Z') || (!data[0] && (data[1] == 2 || data[1] == 3) && !data[5] && (data[6] > ' ' &&
        data[6] < 127))) {
        printf("Loaded '%s' (WinFNT, %X - %X)\n", filename, rs, re);
        fnt(data, size);
    } else if(data[0]=='S' && data[1]=='T' && data[2]=='A' && data[3]=='R') {
        printf("Loaded '%s' (X11 BDF, %X - %X)\n", filename, rs, re);
        bdf((char*)data, size);
    } else if(data[0]==1 && data[1]=='f' && data[2]=='c' && data[3]=='p') {
        printf("Loaded '%s' (X11 PCF, %X - %X)\n", filename, rs, re);
        pcf(data, size);
    } else if(data[0]=='S' && data[1]=='p' && data[2]=='l' && data[3]=='i' && data[4]=='n') {
        printf("Loaded '%s' (SplineFontDB, %X - %X)\n", filename, rs, re);
        sfd((char*)data, size);
    } else if(data[0]==0x89 && data[1]=='P' && data[2]=='N' && data[3]=='G') {
        printf("Loaded '%s' (PNG, %X - %X)\n", filename, rs, re);
        png(data, size);
    } else if(data[0]==0 && (data[1]==0 || data[1]==1) &&
        (data[2]==1 || data[2]==2 || data[2]==9 || data[2]==10) &&
        (data[16]==8 || data[16]==24 || data[16]==32)) {
            printf("Loaded '%s' (TARGA, %X - %X)\n", filename, rs, re);
            tga(data, size);
    } else if((data[0]>='0' && data[0]<='9') || (data[0]>='A' && data[0]<='F')) {
        printf("Loaded '%s' (GNU unifont hex, %X - %X)\n", filename, rs, re);
        hex((char*)data, size);
#ifdef HAS_FT
    } else if(ft2_read(data, size)) {
        printf("Loaded '%s' (FreeType2, %X - %X)\n", filename, rs, re);
        ft2_parse();
#endif
#endif
    } else {
        fprintf(stderr, "libsfn: unknown format '%s'\n", filename);
        r = 0;
    }

    free(data);
    rs = 0; re = 0x10FFFF;
    return r;
}

/**
 * Serialize an SSFN context into a file
 *
 * @param filename file to save to
 * @param ascii true if saving to ASC
 * @param comp true if file should be gzipped
 * @return true on success
 */
int sfn_save(char *filename, int ascii, int comp)
{
    //char *fam[] = { "Serif", "Sans", "Decorative", "Monospace", "Handwriting", "?" }, *c;
    //int unicode, i, j, k, l, o, x, y, h, nc = 0, mc = 0, ml = 0, fs = 0, cs = 0, ks = 0, ls = 0;
    //unsigned char *frg = NULL, *chr = NULL, *krn = NULL, *tmp, hint[32], *gz;
    //unsigned short int lig[SSFN_LIG_LAST-SSFN_LIG_FIRST+1];
    //unsigned long int gzs;
    //char *strs = NULL, *crd = NULL;
    //sfnkgrp_t kgrp, *kgrpf = NULL;
    //ssfn_font_t *hdr;
    //sfncont_t *cont, *norm;
    //FILE *f;
    //uint32_t crc;
    //z_stream stream;

    //for(i = 0; i < 0x110000; i++) {
    //    ml += ctx.glyphs[i].numlayer;
    //    if((iswhitespace(i) && (ctx.glyphs[i].adv_x || ctx.glyphs[i].adv_y)) || ctx.glyphs[i].layers) mc++;
    //}
    //if(!mc || !ml) {
    //    fprintf(stderr, "libsfn: no layers in font???\n");
    //    return 0;
    //}
    //printf(" Numchars: %d, Numlayers: %d\n", mc, ml);

    //if(ascii) {
    //    /* ----------------------------- output in text format ----------------------------- */
    //    f = fopen(filename, "w");
    //    if(f) {
    //        ctx.filename = filename;
    //        /* header */
    //        fprintf(f, "# Scalable Screen Font #\r\n\r\n");
    //        fprintf(f, "$glyphdim %d %d numchars %d numlayers %d\r\n", ctx.width, ctx.height, mc, ml);
    //        fprintf(f, "$type %d (%s)\r\n", ctx.family, fam[ctx.family < 5 ? ctx.family : 5]);
    //        fprintf(f, "$style%s%s%s%s\r\n", !ctx.style ? " regular" : (ctx.style & SSFN_STYLE_BOLD ? " bold" : ""),
    //            ctx.style & SSFN_STYLE_ITALIC ? " italic" : "", ctx.style & SSFN_STYLE_USRDEF1 ? "usrdef1" : "",
    //            ctx.style & SSFN_STYLE_USRDEF2 ? "usrdef2" : "");
    //        fprintf(f,"$baseline %d\r\n$underline %d\r\n", ctx.baseline, ctx.underline);
    //        fprintf(f,"$name \"%s\"\r\n", ctx.name ? ctx.name : "");
    //        fprintf(f,"$family \"%s\"\r\n", ctx.familyname ? ctx.familyname : "");
    //        fprintf(f,"$subfamily \"%s\"\r\n", ctx.subname ? ctx.subname : "");
    //        fprintf(f,"$revision \"%s\"\r\n", ctx.revision ? ctx.revision : "");
    //        fprintf(f,"$manufacturer \"%s\"\r\n", ctx.manufacturer ? ctx.manufacturer : "");
    //        fprintf(f,"$license \"%s\"\r\n", ctx.license ? ctx.license : "");
    //        /* characters */
    //        for(unicode = 0; unicode <= 0x10FFFF; unicode++)
    //            if((iswhitespace(unicode) && (ctx.glyphs[unicode].adv_x || ctx.glyphs[unicode].adv_y)) ||
    //                ctx.glyphs[unicode].layers) {
    //                fprintf(f,"\r\n===U+%06X===w%d=h%d=x%d=y%d=o%d=%s%s%s==%s===\r\n", unicode,
    //                    ctx.glyphs[unicode].width, ctx.glyphs[unicode].height,
    //                    ctx.glyphs[unicode].adv_x, ctx.glyphs[unicode].adv_y, ctx.glyphs[unicode].ovl_x,
    //                    unicode < 32 ? "" : (unicode == '\"' ? "\"\\" : "\""), unicode < 32 ? "" :
    //                        (unicode >= SSFN_LIG_FIRST && unicode <= SSFN_LIG_LAST ? (ctx.ligatures[unicode-SSFN_LIG_FIRST] ?
    //                        ctx.ligatures[unicode-SSFN_LIG_FIRST] : "") : utf8(unicode)), unicode < 32 ? "" : "\"=",
    //                    uninames[uniname(unicode)].name);
    //                /* layers */
    //                if(!iswhitespace(unicode) && ctx.glyphs[unicode].layers && ctx.glyphs[unicode].numlayer) {
    //                    /* hinting grid */
    //                    if(hinting) {
    //                        if(!ctx.glyphs[unicode].hintv[0] && !ctx.glyphs[unicode].hinth[0]) sfn_hintgen(unicode);
    //                        if(ctx.glyphs[unicode].hintv[0]) {
    //                            fprintf(f,"V");
    //                            for(i = 0; i < ctx.glyphs[unicode].hintv[0] && ctx.glyphs[unicode].hintv[i+1]; i++)
    //                                fprintf(f," %d", ctx.glyphs[unicode].hintv[i+1]);
    //                            fprintf(f,"\r\n");
    //                        }
    //                        if(ctx.glyphs[unicode].hinth[0]) {
    //                            fprintf(f,"H");
    //                            for(i = 0; i < ctx.glyphs[unicode].hinth[0] && ctx.glyphs[unicode].hinth[i+1]; i++)
    //                                fprintf(f," %d", ctx.glyphs[unicode].hinth[i+1]);
    //                            fprintf(f,"\r\n");
    //                        }
    //                        if(ctx.glyphs[unicode].hintv[0] || ctx.glyphs[unicode].hinth[0])
    //                            fprintf(f,"\r\n");
    //                    }
    //                    for(i = 0; i < ctx.glyphs[unicode].numlayer; i++) {
    //                        if(pbar) (*pbar)(0, 0, ++nc, ml, PBAR_WRTCHARS);
    //                        if(i) fprintf(f,"\r\n");
    //                        if(ctx.glyphs[unicode].layers[i].color < 0xFE) {
    //                            fprintf(f,"f %02X%02X%02X%02X\r\n",
    //                                ctx.cpal[ctx.glyphs[unicode].layers[i].color*4+3],
    //                                ctx.cpal[ctx.glyphs[unicode].layers[i].color*4+2],
    //                                ctx.cpal[ctx.glyphs[unicode].layers[i].color*4+1],
    //                                ctx.cpal[ctx.glyphs[unicode].layers[i].color*4]);
    //                        }
    //                        /* layer type */
    //                        switch(ctx.glyphs[unicode].layers[i].type) {
    //                            case SSFN_FRAG_BITMAP:
    //                                for(y = j = 0; y < ctx.glyphs[unicode].height; y++) {
    //                                    for(x = 0; x < ctx.glyphs[unicode].width; x++, j++)
    //                                        fprintf(f,"%c", ctx.glyphs[unicode].layers[i].data[j] == 0xFE ? 'X' : '.');
    //                                    fprintf(f,"\r\n");
    //                                }
    //                            break;
    //                            case SSFN_FRAG_PIXMAP:
    //                                for(y = j = 0; y < ctx.glyphs[unicode].height; y++) {
    //                                    for(x = 0; x < ctx.glyphs[unicode].width; x++, j++) {
    //                                        k = ctx.glyphs[unicode].layers[i].data[j] * 4;
    //                                        if(k == 0xFE) k = 0;
    //                                        if(ctx.glyphs[unicode].layers[i].data[j] > 0xFE || !ctx.cpal[k+3])
    //                                            fprintf(f,"%s--------", x ? " " : "");
    //                                        else
    //                                            fprintf(f,"%s%02X%02X%02X%02X", x ? " " : "", ctx.cpal[k+3], ctx.cpal[k+2],
    //                                                ctx.cpal[k+1], ctx.cpal[k]);
    //                                    }
    //                                    fprintf(f,"\r\n");
    //                                }
    //                            break;
    //                            case SSFN_FRAG_CONTOUR:
    //                                cont = (sfncont_t*)ctx.glyphs[unicode].layers[i].data;
    //                                for(j = 0; j < ctx.glyphs[unicode].layers[i].len; j++, cont++)
    //                                    switch(cont->type) {
    //                                        case SSFN_CONTOUR_MOVE: fprintf(f,"m %d,%d\r\n", cont->px, cont->py); break;
    //                                        case SSFN_CONTOUR_LINE: fprintf(f,"l %d,%d\r\n", cont->px, cont->py); break;
    //                                        case SSFN_CONTOUR_QUAD: fprintf(f,"q %d,%d %d,%d\r\n", cont->px, cont->py,
    //                                            cont->c1x, cont->c1y); break;
    //                                        case SSFN_CONTOUR_CUBIC: fprintf(f,"c %d,%d %d,%d %d,%d\r\n", cont->px, cont->py,
    //                                            cont->c1x, cont->c1y, cont->c2x, cont->c2y); break;
    //                                    }
    //                            break;
    //                        }
    //                    }
    //                    /* kerning layer */
    //                    if(ctx.glyphs[unicode].numkern && ctx.glyphs[unicode].kern) {
    //                        if(i) fprintf(f,"\r\n");
    //                        for(i = j = 0; i < ctx.glyphs[unicode].numkern; i++) {
    //                            if(!ctx.glyphs[unicode].kern[i].x && !ctx.glyphs[unicode].kern[i].y) continue;
    //                            c = utf8(ctx.glyphs[unicode].kern[i].n);
    //                            if(ctx.glyphs[unicode].kern[i].n >= SSFN_LIG_FIRST &&
    //                                ctx.glyphs[unicode].kern[i].n <= SSFN_LIG_LAST)
    //                                    sprintf(c, "U+%06X", ctx.glyphs[unicode].kern[i].n);
    //                            fprintf(f,"%s %s %d", !j ? "k" : ",", c, ctx.glyphs[unicode].kern[i].x);
    //                            if(ctx.glyphs[unicode].kern[i].y)
    //                                fprintf(f," %d", ctx.glyphs[unicode].kern[i].y);
    //                            j++;
    //                        }
    //                        if(j) fprintf(f,"\r\n");
    //                    }
    //                }
    //            }
    //        fprintf(f,"\r\n# End #\r\n");
    //        fclose(f);
    //        return 1;
    //    } else
    //        return 0;
    //} else {
    //    /* ----------------------------- output to optionally gzip compressed binary ----------------------------- */
    //    ctx.numfrags = 0;
    //    if(ctx.frags) { free(ctx.frags); ctx.frags = NULL; }
    //    /* generate fragments */
    //    for(unicode = 0; unicode <= 0x10FFFF; unicode++) {
    //        if(ctx.glyphs[unicode].layers) {
    //            /* hints first (if exists) */
    //            if(hinting) {
    //                if(!ctx.glyphs[unicode].hintv[0] && !ctx.glyphs[unicode].hinth[0]) sfn_hintgen(unicode);
    //                if(ctx.glyphs[unicode].hintv[0]) {
    //                    memset(hint, 0, 32);
    //                    x = ctx.glyphs[unicode].hintv[1];
    //                    for(i = 1; i < ctx.glyphs[unicode].hintv[0] && ctx.glyphs[unicode].hintv[1+i]; i++)
    //                        hint[i-1] = ctx.glyphs[unicode].hintv[1+i] - ctx.glyphs[unicode].hintv[i];
    //                    sfn_fragchr(unicode, SSFN_FRAG_HINTING, ctx.glyphs[unicode].hintv[0] - 1, 0, x + 1, 0, hint);
    //                }
    //                if(ctx.glyphs[unicode].hinth[0]) {
    //                    memset(hint, 0, 32);
    //                    y = ctx.glyphs[unicode].hinth[1];
    //                    for(i = 1; i < ctx.glyphs[unicode].hinth[0] && ctx.glyphs[unicode].hinth[1+i]; i++)
    //                        hint[i-1] = ctx.glyphs[unicode].hinth[1+i] - ctx.glyphs[unicode].hinth[i];
    //                    sfn_fragchr(unicode, SSFN_FRAG_HINTING, ctx.glyphs[unicode].hinth[0] - 1, 0, 0, y + 1, hint);
    //                }
    //            }
    //            /* then kerning (if exists) */
    //            if(ctx.glyphs[unicode].kern) {
    //                /* vertical kerning */
    //                memset(&kgrp, 0, sizeof(sfnkgrp_t));
    //                l = o = 0; kgrpf = NULL;
    //                for(i = 0; i < ctx.glyphs[unicode].numkern; i++) {
    //                    if(ctx.glyphs[unicode].kern[i].x) {
    //                        if(!kgrp.first) {
    //                            kgrp.first = kgrp.last = ctx.glyphs[unicode].kern[i].n;
    //                            l = 1;
    //                            crd = realloc(crd, l);
    //                            if(!crd) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                            crd[0] = ctx.glyphs[unicode].kern[i].x;
    //                        } else {
    //                            if(kgrp.last + 127 < ctx.glyphs[unicode].kern[i].n) {
    //                                kgrp.idx = sfn_kposadd(crd, l);
    //                                kgrpf = (sfnkgrp_t*)realloc(kgrpf, (o+1)*sizeof(sfnkgrp_t));
    //                                if(!kgrpf) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                                memcpy(&kgrpf[o++], &kgrp, sizeof(sfnkgrp_t));
    //                                kgrp.first = kgrp.last = ctx.glyphs[unicode].kern[i].n;
    //                                l = 1;
    //                                crd = realloc(crd, l);
    //                                if(!crd) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                                crd[0] = ctx.glyphs[unicode].kern[i].x;
    //                            } else {
    //                                crd = realloc(crd, l + ctx.glyphs[unicode].kern[i].n - kgrp.last);
    //                                if(!crd) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                                for(k = 0; k < ctx.glyphs[unicode].kern[i].n - kgrp.last - 1; k++, l++)
    //                                    crd[l] = 0;
    //                                crd[l++] = ctx.glyphs[unicode].kern[i].x;
    //                                kgrp.last = ctx.glyphs[unicode].kern[i].n;
    //                            }
    //                        }
    //                    }
    //                }
    //                if(kgrp.first) {
    //                    kgrp.idx = sfn_kposadd(crd, l);
    //                    kgrpf = (sfnkgrp_t*)realloc(kgrpf, (o+1)*sizeof(sfnkgrp_t));
    //                    if(!kgrpf) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                    memcpy(&kgrpf[o++], &kgrp, sizeof(sfnkgrp_t));
    //                }
    //                if(crd) { free(crd); crd = NULL; }
    //                if(o && kgrpf) {
    //                    if(!sfn_fragchr(unicode, SSFN_FRAG_KERNING, o, 0, 1, 0, kgrpf)) return 0;
    //                    free(kgrpf);
    //                }
    //                /* horizontal kerning */
    //                memset(&kgrp, 0, sizeof(sfnkgrp_t));
    //                l = o = 0; kgrpf = NULL;
    //                for(i = 0; i < ctx.glyphs[unicode].numkern; i++) {
    //                    if(ctx.glyphs[unicode].kern[i].y) {
    //                        if(!kgrp.first) {
    //                            kgrp.first = kgrp.last = ctx.glyphs[unicode].kern[i].n;
    //                            l = 1;
    //                            crd = realloc(crd, l);
    //                            if(!crd) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                            crd[0] = ctx.glyphs[unicode].kern[i].y;
    //                        } else {
    //                            if(kgrp.last + 127 < ctx.glyphs[unicode].kern[i].n) {
    //                                kgrp.idx = sfn_kposadd(crd, l);
    //                                kgrpf = (sfnkgrp_t*)realloc(kgrpf, (o+1)*sizeof(sfnkgrp_t));
    //                                if(!kgrpf) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                                memcpy(&kgrpf[o++], &kgrp, sizeof(sfnkgrp_t));
    //                                kgrp.first = kgrp.last = ctx.glyphs[unicode].kern[i].n;
    //                                l = 1;
    //                                crd = realloc(crd, l);
    //                                if(!crd) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                                crd[0] = ctx.glyphs[unicode].kern[i].y;
    //                            } else {
    //                                crd = realloc(crd, l + ctx.glyphs[unicode].kern[i].n - kgrp.last);
    //                                if(!crd) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                                for(k = 0; k < ctx.glyphs[unicode].kern[i].n - kgrp.last - 1; k++, l++)
    //                                    crd[l] = 0;
    //                                crd[l++] = ctx.glyphs[unicode].kern[i].y;
    //                                kgrp.last = ctx.glyphs[unicode].kern[i].n;
    //                            }
    //                        }
    //                    }
    //                }
    //                if(kgrp.first) {
    //                    kgrp.idx = sfn_kposadd(crd, l);
    //                    kgrpf = (sfnkgrp_t*)realloc(kgrpf, (o+1)*sizeof(sfnkgrp_t));
    //                    if(!kgrpf) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                    memcpy(&kgrpf[o++], &kgrp, sizeof(sfnkgrp_t));
    //                }
    //                if(crd) { free(crd); crd = NULL; }
    //                if(o && kgrpf) {
    //                    if(!sfn_fragchr(unicode, SSFN_FRAG_KERNING, o, 0, 0, 1, kgrpf)) return 0;
    //                    free(kgrpf);
    //                }
    //            }
    //            /* layers to fragments */
    //            for(j = 0; j < ctx.glyphs[unicode].numlayer; j++) {
    //                if(pbar) (*pbar)(1, 5, ++nc, ml, PBAR_GENFRAG);
    //                if(ctx.glyphs[unicode].layers[j].color < 0xFE) {
    //                        if(ctx.glyphs[unicode].numfrag == 255) {
    //                            if(!quiet) fprintf(stderr, "libsfn: too many fragments for U+%06X, truncated to 255.\n", unicode);
    //                        } else {
    //                            ctx.glyphs[unicode].frags = (int*)realloc(ctx.glyphs[unicode].frags,
    //                                (ctx.glyphs[unicode].numfrag + 1) * 3 * sizeof(int));
    //                            if(!ctx.glyphs[unicode].frags) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                            ctx.glyphs[unicode].frags[ctx.glyphs[unicode].numfrag*3+0] =
    //                                ctx.glyphs[unicode].layers[j].color;
    //                            ctx.glyphs[unicode].frags[ctx.glyphs[unicode].numfrag*3+1] = 255;
    //                            ctx.glyphs[unicode].frags[ctx.glyphs[unicode].numfrag*3+2] = 255;
    //                            ctx.glyphs[unicode].numfrag++;
    //                        }
    //                }
    //                switch(ctx.glyphs[unicode].layers[j].type) {
    //                    case SSFN_FRAG_CONTOUR:
    //                        /* normalize coordinates */
    //                        cont = (sfncont_t*)ctx.glyphs[unicode].layers[j].data;
    //                        for(i = 0, x = y = 256; i < ctx.glyphs[unicode].layers[j].len; i++, cont++) {
    //                            if(x > cont->px) x = cont->px;
    //                            if(y > cont->py) y = cont->py;
    //                            if(cont->type >= SSFN_CONTOUR_QUAD) {
    //                                if(x > cont->c1x) x = cont->c1x;
    //                                if(y > cont->c1y) y = cont->c1y;
    //                                if(cont->type >= SSFN_CONTOUR_CUBIC) {
    //                                    if(x > cont->c2x) x = cont->c2x;
    //                                    if(y > cont->c2y) y = cont->c2y;
    //                                }
    //                            }
    //                        }
    //                        if(x > 254) x = 254;
    //                        norm = (sfncont_t*)malloc(ctx.glyphs[unicode].layers[j].len * sizeof(sfncont_t));
    //                        if(!norm) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                        memset(norm, 0, ctx.glyphs[unicode].layers[j].len * sizeof(sfncont_t));
    //                        /* add to fragments list */
    //                        cont = (sfncont_t*)ctx.glyphs[unicode].layers[j].data;
    //                        for(i = 0; i < ctx.glyphs[unicode].layers[j].len; i++, cont++) {
    //                            norm[i].type = cont->type;
    //                            norm[i].px = cont->px - x;
    //                            norm[i].py = cont->py - y;
    //                            if(cont->type >= SSFN_CONTOUR_QUAD) {
    //                                norm[i].c1x = cont->c1x - x;
    //                                norm[i].c1y = cont->c1y - y;
    //                                if(cont->type >= SSFN_CONTOUR_CUBIC) {
    //                                    norm[i].c2x = cont->c2x - x;
    //                                    norm[i].c2y = cont->c2y - y;
    //                                }
    //                            }
    //                        }
    //                        if(!sfn_fragchr(unicode, SSFN_FRAG_CONTOUR, ctx.glyphs[unicode].layers[j].len, 0, x, y, norm))
    //                            return 0;
    //                        free(norm);
    //                    break;
    //                    case SSFN_FRAG_BITMAP:
    //                    case SSFN_FRAG_PIXMAP:
    //                        h = ctx.glyphs[unicode].height; x = 1;
    //                        for(y = 0; y < h; y += x) {
    //                            for(;y < h && isempty(ctx.glyphs[unicode].width,
    //                                ctx.glyphs[unicode].layers[j].data + (h - 1) * ctx.glyphs[unicode].width); h--);
    //                            for(;y < h && isempty(ctx.glyphs[unicode].width,
    //                                ctx.glyphs[unicode].layers[j].data + y * ctx.glyphs[unicode].width); y++);
    //                            for(x = 0; (y + x) < h && !isempty(ctx.glyphs[unicode].width,
    //                                ctx.glyphs[unicode].layers[j].data + (y + x) * ctx.glyphs[unicode].width); x++);
    //                            if(x > 0 && !sfn_fragchr(unicode, ctx.glyphs[unicode].layers[j].type, ctx.glyphs[unicode].width,
    //                                x, 0, y, ctx.glyphs[unicode].layers[j].data + y * ctx.glyphs[unicode].width))
    //                                    return 0;
    //                        }
    //                    break;
    //                }
    //            }
    //            /* should never reached, just to be on the safe side */
    //            if(ctx.glyphs[unicode].numfrag > 255) {
    //                if(!quiet) fprintf(stderr, "libsfn: too many fragments for U+%06X, truncated to 255.\n", unicode);
    //                ctx.glyphs[unicode].numfrag = 255;
    //            }
    //        }
    //    }

    //    /* serialize kerning positions */
    //    qsort(ctx.kpos, ctx.numkpos, sizeof(sfnkpos_t), possrt);
    //    for(i = ks = 0; i < ctx.numkpos; i++) {
    //        ctx.kpos[i].pos = -1;
    //        for(j = 0; krn && j < ks - ctx.kpos[i].len; j++)
    //            if(!memcmp(krn, ctx.kpos[i].data, ctx.kpos[i].len)) { ctx.kpos[i].pos = j; break; }
    //        if(ctx.kpos[i].pos == -1) {
    //            ctx.kpos[i].pos = ks;
    //            krn = (unsigned char *)realloc(krn, ks + ctx.kpos[i].len);
    //            if(!krn) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //            memcpy(krn + ks, ctx.kpos[i].data, ctx.kpos[i].len);
    //            ks += ctx.kpos[i].len;
    //        }
    //    }

    //    /* generate header and string table */
    //    memset(lig, 0, sizeof(lig));
    //    o = y = sizeof(ssfn_font_t) + (ctx.name ? strlen(ctx.name) : 0) + 1 + (ctx.familyname ? strlen(ctx.familyname) : 0) + 1 +
    //        (ctx.subname ? strlen(ctx.subname) : 0) + 1 + (ctx.revision ? strlen(ctx.revision) : 0) + 1 +
    //        (ctx.manufacturer ? strlen(ctx.manufacturer) : 0) + 1 + (ctx.license ? strlen(ctx.license) : 0) + 1;
    //    for(ls = 0; ls < SSFN_LIG_LAST-SSFN_LIG_FIRST+1 && ctx.ligatures[ls] && ctx.ligatures[ls][0]; ls++) {
    //        if(o + strlen(ctx.ligatures[ls]) + 1 > 65535) break;
    //        o += strlen(ctx.ligatures[ls]) + 1;
    //    }
    //    hdr = (ssfn_font_t*)malloc(o);
    //    if(!hdr) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //    memset(hdr, 0, o);
    //    memcpy(hdr->magic, SSFN_MAGIC, 4);
    //    hdr->size = o + 4;
    //    hdr->type = (ctx.family & 0x0F) | ((ctx.style & 0x0F) << 4);
    //    hdr->width = ctx.width;
    //    hdr->height = ctx.height;
    //    hdr->baseline = ctx.baseline;
    //    hdr->underline = ctx.underline;
    //    strs = ((char*)hdr) + sizeof(ssfn_font_t);
    //    if(ctx.name) { j = strlen(ctx.name) + 1; memcpy(strs, ctx.name, j); strs += j; } else strs++;
    //    if(ctx.familyname) { j = strlen(ctx.familyname) + 1; memcpy(strs, ctx.familyname, j); strs += j; } else strs++;
    //    if(ctx.subname) { j = strlen(ctx.subname) + 1; memcpy(strs, ctx.subname, j); strs += j; } else strs++;
    //    if(ctx.revision) { j = strlen(ctx.revision) + 1; memcpy(strs, ctx.revision, j); strs += j; } else strs++;
    //    if(ctx.manufacturer) { j = strlen(ctx.manufacturer) + 1; memcpy(strs, ctx.manufacturer, j); strs += j; } else strs++;
    //    if(ctx.license) { j = strlen(ctx.license) + 1; memcpy(strs, ctx.license, j); strs += j; } else strs++;
    //    for(j = 0; j < ls; j++) {
    //        lig[j] = y;
    //        x = strlen(ctx.ligatures[j]) + 1;
    //        memcpy(strs, ctx.ligatures[j], x);
    //        strs += x; y += x;
    //    }

    //    /* compress fragments */
    //    for(i = 0; i < ctx.numfrags; i++) {
    //        if(pbar) (*pbar)(2, 5, i, ctx.numfrags, PBAR_COMPFRAG);
    //    }

    //    /* serialize fragments */
    //    fidx = (int*)malloc(ctx.numfrags * sizeof(int));
    //    qsort(ctx.frags, ctx.numfrags, sizeof(sfnfrag_t), frgsrt);
    //    for(i = 0; i < ctx.numfrags; i++)
    //        fidx[ctx.frags[i].idx] = i;
    //    hdr->fragments_offs = o;
    //    for(i = 0; i < ctx.numfrags; i++) {
    //        if(pbar) (*pbar)(3, 5, i, ctx.numfrags, PBAR_SERFRAG);
    //        ctx.frags[i].pos = o + fs;
    //        frg = (unsigned char*)realloc(frg, fs + 5 + ctx.frags[i].len);
    //        if(!frg) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //        switch(ctx.frags[i].type) {
    //            case SSFN_FRAG_CONTOUR:
    //                if(ctx.frags[i].w>64)
    //                    frg[fs++] = (((ctx.frags[i].w - 1) >> 8) & 0x3F) | 0x40;
    //                frg[fs++] = (ctx.frags[i].w - 1) & 0xFF;
    //                k = fs; fs += (ctx.frags[i].w + 3) / 4;
    //                memset(frg + k, 0, fs - k);
    //                for(j = 0, cont = (sfncont_t*)ctx.frags[i].data; j < ctx.frags[i].w; j++, cont++) {
    //                    frg[k + (j / 4)] |= cont->type << ((j & 3) * 2);
    //                    frg[fs++] = cont->px;
    //                    frg[fs++] = cont->py;
    //                    if(cont->type >= SSFN_CONTOUR_QUAD) {
    //                        frg[fs++] = cont->c1x;
    //                        frg[fs++] = cont->c1y;
    //                        if(cont->type >= SSFN_CONTOUR_CUBIC) {
    //                            frg[fs++] = cont->c2x;
    //                            frg[fs++] = cont->c2y;
    //                        }
    //                    }
    //                }
    //            break;
    //            case SSFN_FRAG_BITMAP:
    //                k = ((ctx.frags[i].w + 7) >> 3) & 0x1F;
    //                frg[fs++] = 0x80 | (k - 1);
    //                frg[fs++] = ctx.frags[i].h - 1;
    //                for(y = 0; y < ctx.frags[i].h; y++) {
    //                    memset(frg + fs, 0, k);
    //                    for(x = 0; x < ctx.frags[i].w; x++) {
    //                        if(ctx.frags[i].data[y * ctx.frags[i].w + x] != 0xFF)
    //                            frg[fs + (x >> 3)] |= 1 << (x & 7);
    //                    }
    //                    fs += k;
    //                }
    //            break;
    //            case SSFN_FRAG_PIXMAP:
    //                tmp = rle_enc(ctx.frags[i].data, ctx.frags[i].w * ctx.frags[i].h, &k);
    //                if(!tmp || k < 2) return 0;
    //                frg = (unsigned char*)realloc(frg, fs + 5 + k);
    //                if(!frg) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //                frg[fs++] = 0xA0 | (((k - 1) >> 8) & 0x1F);
    //                frg[fs++] = (k - 1) & 0xFF;
    //                frg[fs++] = ctx.frags[i].w - 1;
    //                frg[fs++] = ctx.frags[i].h - 1;
    //                memcpy(frg + fs, tmp, k);
    //                fs += k;
    //                free(tmp);
    //            break;
    //            case SSFN_FRAG_KERNING:
    //                frg[fs++] = (((ctx.frags[i].w - 1) >> 8) & 0x3) | 0xC0 | /*kerning context*/((0 & 7) << 2);
    //                frg[fs++] = (ctx.frags[i].w - 1) & 0xFF;
    //                for(j = 0, kgrpf = (sfnkgrp_t*)ctx.frags[i].data; j < ctx.frags[i].w; j++, kgrpf++) {
    //                    /* this is not efficient, but fast enough */
    //                    for(k = x = 0; k < ctx.numkpos; k++)
    //                        if(ctx.kpos[k].idx == kgrpf->idx) { x = ctx.kpos[k].pos; break; }
    //                    frg[fs++] = kgrpf->first & 0xFF;
    //                    frg[fs++] = (kgrpf->first >> 8) & 0xFF;
    //                    frg[fs++] = ((kgrpf->first >> 16) & 0x0F) | ((x >> 20) & 0xF0);
    //                    frg[fs++] = kgrpf->last & 0xFF;
    //                    frg[fs++] = (kgrpf->last >> 8) & 0xFF;
    //                    frg[fs++] = ((kgrpf->last >> 16) & 0x0F) | ((x >> 12) & 0xF0);
    //                    frg[fs++] = x & 0xFF;
    //                    frg[fs++] = (x >> 8) & 0xFF;
    //                }
    //            break;
    //            case SSFN_FRAG_HINTING:
    //                if(ctx.frags[i].w && ctx.frags[i].data) {
    //                    frg[fs++] = ((ctx.frags[i].w & 31) | 0xE0);
    //                    memcpy(frg + fs, ctx.frags[i].data, ctx.frags[i].w);
    //                    fs += ctx.frags[i].w;
    //                } else
    //                    frg[fs++] = 0xE0;
    //            break;
    //        }
    //    }
    //    hdr->size += fs;
    //    o += fs;

    //    /* serialize character map */
    //    hdr->characters_offs = o;
    //    unicode = -1;
    //    for(i = nc = 0; i <= 0x10FFFF; i++) {
    //        if((iswhitespace(i) && (ctx.glyphs[i].adv_x || ctx.glyphs[i].adv_y)) ||
    //            ctx.glyphs[i].layers) {
    //            if(pbar) (*pbar)(4, 5, ++nc, mc, PBAR_WRTCHARS);
    //            j = i - unicode - 1;
    //            chr = (unsigned char*)realloc(chr, cs+256+ctx.glyphs[i].numfrag*6);
    //            if(!chr) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //            while(j > 0) {
    //                if(j <= 64) { chr[cs++] = ((j-1) & 0x3F) | 0x80; break; }
    //                else {
    //                    while(j > 65536) { chr[cs++] = 0xFF; j -= 65536; }
    //                    while(j > 16128) { chr[cs++] = 0xFE; chr[cs++] = 0xFF; j -= 16128; }
    //                    if(j > 64) { chr[cs++] = (((j-1) >> 8) & 0x3F) | 0xC0; chr[cs++] = (j-1) & 0xFF; break; }
    //                }
    //            }
    //            k = (ctx.glyphs[i].ovl_x & 0x3F);
    //            for(j = 0; j < ctx.glyphs[i].numfrag; j++)
    //                if(ctx.frags[fidx[ctx.glyphs[i].frags[j*3]]].pos > 0xFFFFFF) { k |= 0x40; break; }
    //            qsort(ctx.glyphs[i].frags, ctx.glyphs[i].numfrag, 3*sizeof(int), frdsrt);
    //            chr[cs++] = k;
    //            chr[cs++] = ctx.glyphs[i].numfrag;
    //            chr[cs++] = ctx.glyphs[i].width;
    //            chr[cs++] = ctx.glyphs[i].height;
    //            chr[cs++] = ctx.glyphs[i].adv_x;
    //            chr[cs++] = ctx.glyphs[i].adv_y;
    //            for(j = 0; j < ctx.glyphs[i].numfrag; j++) {
    //                chr[cs++] = ctx.glyphs[i].frags[j*3+1];
    //                if(ctx.glyphs[i].frags[j*3+1] == 255) {
    //                    memcpy(chr + cs, &ctx.glyphs[i].frags[j*3+0], 4);
    //                    cs += 4;
    //                    if(k & 0x40)
    //                        chr[cs++] = 0;
    //                } else {
    //                    chr[cs++] = ctx.glyphs[i].frags[j*3+2];
    //                    x = ctx.frags[fidx[ctx.glyphs[i].frags[j*3+0]]].pos;
    //                    chr[cs++] = x & 0xFF;
    //                    chr[cs++] = (x >> 8) & 0xFF;
    //                    chr[cs++] = (x >> 16) & 0xFF;
    //                    if(k & 0x40)
    //                        chr[cs++] = (x >> 24) & 0xFF;
    //                }
    //            }
    //            unicode = i;
    //        }
    //    }
    //    free(fidx);
    //    j = 0x110000 - unicode;
    //    chr = (unsigned char*)realloc(chr, cs+256);
    //    if(!chr) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //    while(j > 0) {
    //        if(j <= 64) { chr[cs++] = ((j-1) & 0x3F) | 0x80; break; }
    //        else {
    //            while(j > 65536) { chr[cs++] = 0xFF; j -= 65536; }
    //            while(j > 16128) { chr[cs++] = 0xFE; chr[cs++] = 0xFF; j -= 16128; }
    //            if(j > 64) { chr[cs++] = (((j-1) >> 8) & 0x3F) | 0xC0; chr[cs++] = (j-1) & 0xFF; break; }
    //        }
    //    }
    //    hdr->size += cs;
    //    o += cs;

    //    /* ligatures */
    //    if(ls) {
    //        hdr->ligature_offs = o;
    //        hdr->size += ls*2;
    //        o += ls*2;
    //    }

    //    /* kerning table */
    //    if(ks) {
    //        hdr->kerning_offs = o;
    //        hdr->size += ks;
    //        o += ks;
    //    }

    //    /* color map */
    //    if(ctx.numcpal) {
    //        hdr->cmap_offs = o;
    //        hdr->size += ctx.numcpal * 4;
    //    }

    //    /* write out file */
    //    x = 0;
    //    if(comp) {
    //        gzs = hdr->fragments_offs + fs + cs + ls*2 + ks + ctx.numcpal*4 + 4;
    //        stream.avail_out = compressBound(gzs) + 16;
    //        gz = malloc(stream.avail_out);
    //        if(!gz) { fprintf(stderr,"libsfn: memory allocation error\n"); return 0; }
    //        stream.zalloc = (alloc_func)0;
    //        stream.zfree = (free_func)0;
    //        stream.opaque = (voidpf)0;

    //        if(deflateInit(&stream, 9) != Z_OK) { fprintf(stderr,"libsfn: deflate error\n"); return 0; }

    //        stream.next_out = (z_const Bytef *)gz + 8;

    //        if(pbar) (*pbar)(5, 5, 0, 5, PBAR_WRTFILE);
    //        stream.avail_in = hdr->fragments_offs;
    //        stream.next_in = (z_const Bytef *)hdr;
    //        crc = crc32(0, stream.next_in, stream.avail_in);
    //        deflate(&stream, Z_NO_FLUSH);

    //        if(pbar) (*pbar)(5, 5, 1, 5, PBAR_WRTFILE);
    //        stream.avail_in = fs;
    //        stream.next_in = (z_const Bytef *)frg;
    //        crc = crc32(crc, stream.next_in, stream.avail_in);
    //        deflate(&stream, Z_NO_FLUSH);

    //        if(pbar) (*pbar)(5, 5, 2, 5, PBAR_WRTFILE);
    //        stream.avail_in = cs;
    //        stream.next_in = (z_const Bytef *)chr;
    //        crc = crc32(crc, stream.next_in, stream.avail_in);
    //        deflate(&stream, Z_NO_FLUSH);

    //        if(ls) {
    //            if(pbar) (*pbar)(5, 5, 3, 5, PBAR_WRTFILE);
    //            stream.avail_in = ls*2;
    //            stream.next_in = (z_const Bytef *)lig;
    //            crc = crc32(crc, stream.next_in, stream.avail_in);
    //            deflate(&stream, Z_NO_FLUSH);
    //        }
    //        if(ks) {
    //            if(pbar) (*pbar)(5, 5, 4, 5, PBAR_WRTFILE);
    //            stream.avail_in = ks;
    //            stream.next_in = (z_const Bytef *)krn;
    //            crc = crc32(crc, stream.next_in, stream.avail_in);
    //            deflate(&stream, Z_NO_FLUSH);
    //        }
    //        if(ctx.numcpal) {
    //            if(pbar) (*pbar)(5, 5, 5, 5, PBAR_WRTFILE);
    //            stream.avail_in = ctx.numcpal*4;
    //            stream.next_in = (z_const Bytef *)ctx.cpal;
    //            crc = crc32(crc, stream.next_in, stream.avail_in);
    //            deflate(&stream, Z_NO_FLUSH);
    //        }
    //        stream.avail_in = 4;
    //        stream.next_in = (z_const Bytef *)SSFN_ENDMAGIC;
    //        crc = crc32(crc, stream.next_in, stream.avail_in);
    //        deflate(&stream, Z_FINISH);

    //        memset(gz, 0, 10);
    //        gz[0] = 0x1f; gz[1] = 0x8b; gz[2] = 0x8; gz[9] = 3;

    //        f = fopen(filename, "wb");
    //        if(f) {
    //            ctx.filename = filename;
    //            fwrite(gz, stream.total_out + 4, 1, f);
    //            fwrite(&crc, 4, 1, f);
    //            fwrite(&gzs, 4, 1, f);
    //            fclose(f);
    //            x = stream.total_out + 12;
    //        } else {
    //            fprintf(stderr, "libsfn: unable to write '%s'\n", filename);
    //        }
    //        free(gz);
    //    } else {
    //        f = fopen(filename, "wb");
    //        if(f) {
    //            ctx.filename = filename;
    //            if(pbar) (*pbar)(5, 5, 0, 5, PBAR_WRTFILE);
    //            fwrite(hdr, hdr->fragments_offs, 1, f);
    //            if(pbar) (*pbar)(5, 5, 1, 5, PBAR_WRTFILE);
    //            if(fs) fwrite(frg, fs, 1, f);
    //            if(pbar) (*pbar)(5, 5, 2, 5, PBAR_WRTFILE);
    //            if(cs) fwrite(chr, cs, 1, f);
    //            if(pbar) (*pbar)(5, 5, 3, 5, PBAR_WRTFILE);
    //            if(ls) fwrite(lig, ls*2, 1, f);
    //            if(pbar) (*pbar)(5, 5, 4, 5, PBAR_WRTFILE);
    //            if(ks) fwrite(krn, ks, 1, f);
    //            if(pbar) (*pbar)(5, 5, 5, 5, PBAR_WRTFILE);
    //            if(ctx.numcpal) fwrite(ctx.cpal, ctx.numcpal*4, 1, f);
    //            fwrite(SSFN_ENDMAGIC, 4, 1, f);
    //            fclose(f);
    //            x = hdr->size;
    //        } else {
    //            fprintf(stderr, "libsfn: unable to write '%s'\n", filename);
    //        }
    //    }

    //    /* free resources */
    //    for(unicode = 0; unicode <= 0x10FFFF; unicode++) {
    //        if(ctx.glyphs[unicode].frags) {
    //            free(ctx.glyphs[unicode].frags);
    //            ctx.glyphs[unicode].frags = NULL;
    //        }
    //        ctx.glyphs[unicode].numfrag = 0;
    //    }
    //    if(ctx.frags) {
    //        for(i = 0; i < ctx.numfrags; i++)
    //            free(ctx.frags[i].data);
    //        free(ctx.frags);
    //        ctx.frags = NULL;
    //    }
    //    if(ctx.kpos) {
    //        for(i = 0; i < ctx.numkpos; i++)
    //            free(ctx.kpos[i].data);
    //        free(ctx.kpos);
    //        ctx.kpos = NULL;
    //    }
    //    if(frg) free(frg);
    //    if(krn) free(krn);
    //    if(chr) free(chr);
    //    free(hdr);
    //    ctx.numfrags = 0;
    //}
    //return x;
     return NULL;
}

/**
 * Set the family type
 *
 * @param t family type
 */
void sfn_setfamilytype(int t)
{
    if(t >= 0 && t <= SSFN_FAMILY_HAND) ctx.family = t;
}

/**
 * Set one of the string attributes
 *
 * @param s pointer to a string pointer
 * @param n new string
 * @param len length of the string if not zero terminated
 */
void sfn_setstr(char **s, char *n, int len)
{
    int i;

    if(!n) return;
    if(*s) free(*s);
    while(*n == ' ' || *n == '\t') { n++; if(len) len--; }
    for(i = 0; (!len || i < len) && n[i] && n[i] != '\"' && n[i] != '\r' && n[i] != '\n'; i++);
    while(i && (n[i-1] == ' ' || n[i-1] == '\t')) i--;
    *s = (char*)malloc(i + 1);
    memcpy(*s, n, i);
    *(*s + i) = 0;
}

/**
 * Sanitize context, make sure dimensions and positions are valid
 */
void sfn_sanitize(int unicode)
{
    sfncont_t *cont;
    int i, j, k, l, m = 0, h, s, e;

    if(unicode == -1) { s = 0; e = 0x110000; } else { s = unicode; e = unicode + 1; }
    for(i = s; i < e; i++) {
        if(ctx.glyphs[i].layers) {
            h = 0;
            for(j = 0; j < ctx.glyphs[i].numlayer; j++)
                if(ctx.glyphs[i].layers[j].type == SSFN_FRAG_CONTOUR) {
                    ctx.glyphs[i].width = ctx.glyphs[i].height = 0;
                    break;
                }
            for(j = 0; j < ctx.glyphs[i].numlayer; j++) {
                if(ctx.glyphs[i].layers[j].type == SSFN_FRAG_CONTOUR) {
                    ctx.glyphs[i].layers[j].minx = ctx.glyphs[i].layers[j].miny = 256;
                    for(k = 0, cont = (sfncont_t*)ctx.glyphs[i].layers[j].data; k < ctx.glyphs[i].layers[j].len; k++, cont++) {
                        if(cont->px > m) m = cont->px;
                        if(cont->px + 1 > ctx.glyphs[i].width) ctx.glyphs[i].width = cont->px + 1;
                        if(cont->py + 1 > ctx.glyphs[i].height) ctx.glyphs[i].height = cont->py + 1;
                        if(cont->px < ctx.glyphs[i].layers[j].minx) ctx.glyphs[i].layers[j].minx = cont->px;
                        if(cont->py < ctx.glyphs[i].layers[j].miny) ctx.glyphs[i].layers[j].miny = cont->py;
                        if(cont->type >= SSFN_CONTOUR_QUAD) {
                            if(cont->c1x > m) m = cont->c1x;
                            if(cont->c1x + 1 > ctx.glyphs[i].width) ctx.glyphs[i].width = cont->c1x + 1;
                            if(cont->c1y + 1 > ctx.glyphs[i].height) ctx.glyphs[i].height = cont->c1y + 1;
                            if(cont->c1x < ctx.glyphs[i].layers[j].minx) ctx.glyphs[i].layers[j].minx = cont->c1x;
                            if(cont->c1y < ctx.glyphs[i].layers[j].miny) ctx.glyphs[i].layers[j].miny = cont->c1y;
                            if(cont->type >= SSFN_CONTOUR_CUBIC) {
                                if(cont->c2x > m) m = cont->c2x;
                                if(cont->c2x + 1 > ctx.glyphs[i].width) ctx.glyphs[i].width = cont->c2x + 1;
                                if(cont->c2y + 1 > ctx.glyphs[i].height) ctx.glyphs[i].height = cont->c2y + 1;
                                if(cont->c2x < ctx.glyphs[i].layers[j].minx) ctx.glyphs[i].layers[j].minx = cont->c2x;
                                if(cont->c2y < ctx.glyphs[i].layers[j].miny) ctx.glyphs[i].layers[j].miny = cont->c2y;
                            }
                        }
                    }
                } else {
                    ctx.glyphs[i].layers[j].minx = ctx.glyphs[i].layers[j].miny = 256;
                    for(l = 0; l < ctx.glyphs[i].height; l++)
                        for(k = 0; k < ctx.glyphs[i].width; k++)
                            if(ctx.glyphs[i].layers[j].data[l * ctx.glyphs[i].width + k] != 0xFF) {
                                if(k > m) m = k;
                                if(k < ctx.glyphs[i].layers[j].minx) ctx.glyphs[i].layers[j].minx = k;
                                if(l < ctx.glyphs[i].layers[j].miny) ctx.glyphs[i].layers[j].miny = l;
                            }
                }
                if(ctx.glyphs[i].layers[j].color >= ctx.numcpal || ctx.glyphs[i].layers[j].type == SSFN_FRAG_PIXMAP)
                    ctx.glyphs[i].layers[j].color = 0xFE;
                /* try to autodetect base line */
                if(!ctx.baseline && (ctx.glyphs[i].layers[j].type == SSFN_FRAG_BITMAP || ctx.glyphs[i].layers[j].type ==
                    SSFN_FRAG_PIXMAP) && ((i >= '0' && i <= '9') || (i >= 'A' && i < 'Q') || (i >= 'a' && i < 'g') ||
                    i == 'h' || i == 'i' || (i >= 'k' && i < 'p') || (i >= 'r' && i < 'y') || i == 'z')) {
                        if(ctx.glyphs[i].layers[j].type == SSFN_FRAG_CONTOUR) {
                            if(ctx.glyphs[i].height > h + 1) h = ctx.glyphs[i].height - 1;
                        } else {
                            l = ctx.glyphs[i].height - 1;
                            for(;0 < l && isempty(ctx.glyphs[i].width,
                                ctx.glyphs[i].layers[j].data + l * ctx.glyphs[i].width); l--);
                            if(l > h) h = l;
                        }
                    }
            }
            if(!ctx.baseline) ctx.baseline = h;
            qsort(ctx.glyphs[i].layers, ctx.glyphs[i].numlayer, sizeof(sfnlayer_t), lyrsrt);
        }
        if(ctx.glyphs[i].kern)
            qsort(ctx.glyphs[i].kern, ctx.glyphs[i].numkern, sizeof(sfnkern_t), krnsrt);
        if(ctx.glyphs[i].ovl_x > 63) ctx.glyphs[i].ovl_x = 63;
        if(!ctx.glyphs[i].adv_x && !ctx.glyphs[i].adv_y && m)
            ctx.glyphs[i].adv_x = m + 2 + adv;
        if(ctx.glyphs[i].adv_x) ctx.glyphs[i].adv_y = 0;
        if(ctx.family == SSFN_FAMILY_MONOSPACE) {
            if(ctx.glyphs[i].adv_x) ctx.glyphs[i].adv_x = ((ctx.glyphs[i].width + 7) & ~7) + adv;
            else ctx.glyphs[i].adv_y = ctx.height + adv;
        }
    }
    ctx.width = ctx.height = 0;
    for(i = 0; i < 0x110000; i++) {
        if(ctx.glyphs[i].width > ctx.width) ctx.width = ctx.glyphs[i].width;
        if(ctx.glyphs[i].height > ctx.height) ctx.height = ctx.glyphs[i].height;
    }
    if(!ctx.baseline || ctx.baseline > ctx.height) ctx.baseline = ctx.height * 80 / 100;
    if(relul) ctx.underline = ctx.baseline + relul;
    if(ctx.underline <= ctx.baseline || ctx.underline > ctx.height)
        ctx.underline = ctx.baseline + (ctx.height - ctx.baseline - 1) / 2;
    if(ctx.family > SSFN_FAMILY_HAND) ctx.family = SSFN_FAMILY_HAND;
}

/* add a line to contour */
static void _sfn_l(int p, int h, int x, int y)
{
    if(x < 0 || y < 0 || x >= p || y >= h || (
        ((ctx.lx + (1 << (SSFN_PREC-1))) >> SSFN_PREC) == ((x + (1 << (SSFN_PREC-1))) >> SSFN_PREC) &&
        ((ctx.ly + (1 << (SSFN_PREC-1))) >> SSFN_PREC) == ((y + (1 << (SSFN_PREC-1))) >> SSFN_PREC))) return;
    if(ctx.ap <= ctx.np) {
        ctx.ap = ctx.np + 512;
        ctx.p = (uint16_t*)realloc(ctx.p, ctx.ap * sizeof(uint16_t));
        if(!ctx.p) { ctx.ap = ctx.np = 0; return; }
    }
    if(!ctx.np) {
        ctx.p[0] = ctx.mx;
        ctx.p[1] = ctx.my;
        ctx.np += 2;
    }
    ctx.p[ctx.np+0] = x;
    ctx.p[ctx.np+1] = y;
    ctx.np += 2;
    ctx.lx = x; ctx.ly = y;
}

/* add a Bezier curve to contour */
static void _sfn_b(int p,int h, int x0,int y0, int x1,int y1, int x2,int y2, int x3,int y3, int l)
{
    int m0x, m0y, m1x, m1y, m2x, m2y, m3x, m3y, m4x, m4y,m5x, m5y;
    if(l<4 && (x0!=x3 || y0!=y3)) {
        m0x = ((x1-x0)/2) + x0;     m0y = ((y1-y0)/2) + y0;
        m1x = ((x2-x1)/2) + x1;     m1y = ((y2-y1)/2) + y1;
        m2x = ((x3-x2)/2) + x2;     m2y = ((y3-y2)/2) + y2;
        m3x = ((m1x-m0x)/2) + m0x;  m3y = ((m1y-m0y)/2) + m0y;
        m4x = ((m2x-m1x)/2) + m1x;  m4y = ((m2y-m1y)/2) + m1y;
        m5x = ((m4x-m3x)/2) + m3x;  m5y = ((m4y-m3y)/2) + m3y;
        _sfn_b(p,h, x0,y0, m0x,m0y, m3x,m3y, m5x,m5y, l+1);
        _sfn_b(p,h, m5x,m5y, m4x,m4y, m2x,m2y, x3,y3, l+1);
    } else
    if(l) _sfn_l(p,h, x3, y3);
}

/**
 * Rasterize a layer or glyph
 *
 * @param size size
 * @param unicode code point
 * @param layer layer index or -1 for all
 * @param postproc do postprocess for bitmaps
 * @param g glyph data to return
 */
int sfn_glyph(int size, int unicode, int layer, int postproc, sfngc_t *g)
{
    uint8_t ci = 0, cb = 0;
    uint16_t r[640];
    int i, j, k, l, p, m, n, o, w, h, a, A, b, B, nr, x;
    sfncont_t *cont;

    if(unicode < 0 || unicode > 0x10FFFF || !ctx.glyphs[unicode].numlayer || layer >= ctx.glyphs[unicode].numlayer ||
        ctx.height < 1) return 0;
    h = (size > ctx.height ? (size + 4) & ~3 : ctx.height);
    w = ctx.glyphs[unicode].width * h / ctx.height;
    p = w + (ci ? h / SSFN_ITALIC_DIV : 0) + cb;
    g->p = p;
    g->h = h;
    if(p * h >= (260 + 260 / SSFN_ITALIC_DIV) << 8) return 0;
    g->x = ctx.glyphs[unicode].adv_x * h / ctx.height;
    g->y = ctx.glyphs[unicode].adv_y * h / ctx.height;
    g->o = ctx.glyphs[unicode].ovl_x * h / ctx.height;
    memset(&g->data, 0xFF, p * h);
    ctx.lx = ctx.ly = 0;
    for(n = (layer == -1 ? 0 : layer); n < (layer == -1 ? ctx.glyphs[unicode].numlayer : layer + 1); n++) {
        switch(ctx.glyphs[unicode].layers[n].type) {
            case SSFN_FRAG_CONTOUR:
                for(i = 0, ctx.np = 0, cont = (sfncont_t*)ctx.glyphs[unicode].layers[n].data;
                    i < ctx.glyphs[unicode].layers[n].len; i++, cont++) {
                        k = (cont->px << SSFN_PREC) * h / ctx.height; m = (cont->py << SSFN_PREC) * h / ctx.height;
                        switch(cont->type) {
                            case SSFN_CONTOUR_MOVE: ctx.mx = ctx.lx = k; ctx.my = ctx.ly = m; break;
                            case SSFN_CONTOUR_LINE: _sfn_l(p << SSFN_PREC, h << SSFN_PREC, k, m); break;
                            case SSFN_CONTOUR_QUAD:
                                a = (cont->c1x << SSFN_PREC) * h / ctx.height;
                                A = (cont->c1y << SSFN_PREC) * h / ctx.height;
                                _sfn_b(p << SSFN_PREC,h << SSFN_PREC, ctx.lx,ctx.ly, ((a-ctx.lx)/2)+ctx.lx,
                                    ((A-ctx.ly)/2)+ctx.ly, ((k-a)/2)+a,((m-A)/2)+A, k,m, 0);
                            break;
                            case SSFN_CONTOUR_CUBIC:
                                a = (cont->c1x << SSFN_PREC) * h / ctx.height;
                                A = (cont->c1y << SSFN_PREC) * h / ctx.height;
                                b = (cont->c2x << SSFN_PREC) * h / ctx.height;
                                B = (cont->c2y << SSFN_PREC) * h / ctx.height;
                                _sfn_b(p << SSFN_PREC,h << SSFN_PREC, ctx.lx,ctx.ly, a,A, b,B, k,m, 0);
                            break;
                        }
                }
                if(ctx.mx != ctx.lx || ctx.my != ctx.ly) _sfn_l(p << SSFN_PREC, h << SSFN_PREC, ctx.mx, ctx.my);
                if(ctx.np > 4) {
                    for(b = A = B = o = 0; b < h; b++, B += p) {
                        a = b << SSFN_PREC;
                        for(nr = 0, i = 0; i < ctx.np - 3; i += 2) {
                            if( (ctx.p[i+1] < a && ctx.p[i+3] >= a) ||
                                (ctx.p[i+3] < a && ctx.p[i+1] >= a)) {
                                    if((ctx.p[i+1] >> SSFN_PREC) == (ctx.p[i+3] >> SSFN_PREC))
                                        x = (((int)ctx.p[i]+(int)ctx.p[i+2])>>1);
                                    else
                                        x = ((int)ctx.p[i]) + ((a - (int)ctx.p[i+1])*
                                            ((int)ctx.p[i+2] - (int)ctx.p[i])/
                                            ((int)ctx.p[i+3] - (int)ctx.p[i+1]));
                                    x >>= SSFN_PREC;
                                    if(ci) x += (h - b) / SSFN_ITALIC_DIV;
                                    if(cb && !o) {
                                        if(g->data[B + x] == 0xFF) { o = -cb; A = cb; }
                                        else { o = cb; A = -cb; }
                                    }
                                    for(k = 0; k < nr && x > r[k]; k++);
                                    for(l = nr; l > k; l--) r[l] = r[l-1];
                                    r[k] = x;
                                    nr++;
                            }
                        }
                        if(nr > 1 && nr & 1) { r[nr - 2] = r[nr - 1]; nr--; }
                        if(nr) {
                            for(i = 0; i < nr - 1; i += 2) {
                                l = r[i] + o; m = r[i + 1] + A;
                                if(l < 0) l = 0;
                                if(m > p) m = p;
                                if(i > 0 && l < r[i - 1] + A) l = r[i - 1] + A;
                                for(; l < m; l++)
                                    g->data[B + l] = g->data[B + l] == ctx.glyphs[unicode].layers[n].color ?
                                        0xFF : ctx.glyphs[unicode].layers[n].color;
                            }
                        }
                    }
                }
            break;
            case SSFN_FRAG_BITMAP:
            case SSFN_FRAG_PIXMAP:
                B = ctx.glyphs[unicode].width; A = ctx.glyphs[unicode].height;
                b = B * h / ctx.height; a = A * h / ctx.height;
                for(j = 0; j < a; j++) {
                    k = j * A / a * B;
                    for(i = 0; i < b; i++) {
                        l = ctx.glyphs[unicode].layers[n].data[k + i * B / b];
                        if(l != 0xFF)
                            g->data[j * p + i] =
                                ctx.glyphs[unicode].layers[n].type == SSFN_FRAG_BITMAP ? ctx.glyphs[unicode].layers[n].color : l;
                    }
                }
                if(postproc && ctx.glyphs[unicode].layers[n].type == SSFN_FRAG_BITMAP) {
                    B = ctx.glyphs[unicode].layers[n].color;
                    m = B == 0xFD ? 0xFC : 0xFD;
                    for(k = h; k > ctx.height + 4; k -= 2*ctx.height) {
                        for(j = 1; j < a - 1; j++)
                            for(i = 1; i < b - 1; i++) {
                                l = j * p + i;
                                if(g->data[l] == 0xFF && (g->data[l - p] == B ||
                                    g->data[l + p] == B) && (g->data[l - 1] == B ||
                                    g->data[l + 1] == B)) g->data[l] = m;
                            }
                        for(j = 1; j < a - 1; j++)
                            for(i = 1; i < b - 1; i++) {
                                l = j * p + i;
                                if(g->data[l] == m) g->data[l] = B;
                            }
                    }
                }
            break;
        }
    }
    return 1;
}

/**
 * Convert vector layers into bitmaps of size SIZE
 *
 * @param size size in pixels to rasterize to
 */
void sfn_rasterize(int size)
{
    uint32_t P;
    unsigned long int sA;
    int i, j, k, m, n, w, x, y, y0, y1, Y0, Y1, x0, x1, X0, X1, X2, xs, ys, yp, pc, nc = 0, numchars = 0;
    sfngc_t g;

    if(size < 8) size = 8;
    if(size > 255) size = 255;
    if(ctx.height < 1) ctx.height = 1;

    for(i = 0; i < 0x110000; i++)
        if(ctx.glyphs[i].numlayer) numchars++;

    for(i = 0; i < 0x110000; i++) {
        /* we must rescale characters without glyphs too, like white spaces */
        ctx.glyphs[i].adv_x = ctx.glyphs[i].adv_x * size / ctx.height;
        ctx.glyphs[i].adv_y = ctx.glyphs[i].adv_y * size / ctx.height;
        ctx.glyphs[i].ovl_x = ctx.glyphs[i].ovl_x * size / ctx.height;
        if(!ctx.glyphs[i].numlayer) {
            ctx.glyphs[i].width = ctx.glyphs[i].width * size / ctx.height;
            ctx.glyphs[i].height = ctx.glyphs[i].height * size / ctx.height;
            continue;
        }
        if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_RASTERIZE);
        n = sfn_glyph(size, i, -1, 0, &g);
        for(j = 0; j < ctx.glyphs[i].numlayer; j++)
            if(ctx.glyphs[i].layers[j].data)
                free(ctx.glyphs[i].layers[j].data);
        for(j = 0; j < ctx.glyphs[i].numkern; j++) {
            ctx.glyphs[i].kern[j].x = ctx.glyphs[i].kern[j].x * size / ctx.height;
            ctx.glyphs[i].kern[j].y = ctx.glyphs[i].kern[j].y * size / ctx.height;
        }
        ctx.glyphs[i].numlayer = ctx.glyphs[i].width = ctx.glyphs[i].height = 0;
        if(n) {
            w = g.p * size / g.h;
            n = size > 16 ? 2 : 1;
            if(w < n) w = n;
            ctx.glyphs[i].layers = (sfnlayer_t*)realloc(ctx.glyphs[i].layers, sizeof(sfnlayer_t));
            if(!ctx.glyphs[i].layers) continue;
            memset(ctx.glyphs[i].layers, 0, sizeof(sfnlayer_t));
            ctx.glyphs[i].layers[0].data = (unsigned char*) malloc(w * size);
            if(!ctx.glyphs[i].layers[0].data) { sfn_chardel(i); continue; }
            ctx.glyphs[i].numlayer = 1;
            ctx.glyphs[i].width = w;
            ctx.glyphs[i].height = size;
            ctx.glyphs[i].layers[0].type = SSFN_FRAG_BITMAP;
            ctx.glyphs[i].layers[0].len = w * size;
            ctx.glyphs[i].layers[0].color = 0xFE;
            for (y = j = 0; y < size; y++) {
                y0 = (y << 8) * g.h / size; Y0 = y0 >> 8; y1 = ((y + 1) << 8) * g.h / size; Y1 = y1 >> 8;
                for (x = 0; x < w; x++, j++) {
                    m = 0; sA = 0;
                    x0 = (x << 8) * g.p / w; X0 = x0 >> 8; x1 = ((x + 1) << 8) * g.p / w; X1 = x1 >> 8;
                    for(ys = y0; ys < y1; ys += 256) {
                        if(ys >> 8 == Y0) { yp = 256 - (ys & 0xFF); ys &= ~0xFF; if(yp > y1 - y0) yp = y1 - y0; }
                        else if(ys >> 8 == Y1) yp = y1 & 0xFF;
                        else yp = 256;
                        X2 = (ys >> 8) * g.p;
                        for(xs = x0; xs < x1; xs += 256) {
                            if (xs >> 8 == X0) {
                                k = 256 - (xs & 0xFF); xs &= ~0xFF; if(k > x1 - x0) k = x1 - x0;
                                pc = k == 256 ? yp : (k * yp) >> 8;
                            } else
                            if (xs >> 8 == X1) { k = x1 & 0xFF; pc = k == 256 ? yp : (k * yp) >> 8; }
                            else pc = yp;
                            m += pc;
                            k = g.data[X2 + (xs >> 8)];
                            if(k == 0xFF) continue;
                            P = *((uint32_t*)(ctx.cpal + (k << 2)));
                            sA += (k == 0xFE || !P ? 255 : ((P >> 24) & 0xFF)) * pc;
                        }
                    }
                    if(m) sA /= m; else sA >>= 8;
                    ctx.glyphs[i].layers[0].data[j] = sA > 64 ? 0xFE : 0xFF;
                }
            }
        }
    }
    ctx.width = ctx.height = ctx.baseline = ctx.underline = 0;
    sfn_sanitize(-1);
}

/**
 * Convert bitmap layers into vector contours
 */
void sfn_vectorize()
{
    int i, j, k, s, n, old = ctx.height, nc = 0, numchars = 0;
    potrace_bitmap_t bm;
    potrace_param_t *param;
    potrace_path_t *p;
    potrace_state_t *st;
    potrace_dpoint_t (*c)[3];
    sfngc_t g;
    sfnlayer_t *lyr;

    param = potrace_param_default();
    if(!param) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
    param->turnpolicy = POTRACE_TURNPOLICY_MINORITY;
    param->turdsize = 2;                            /* curve threshold */
    param->alphamax = 1.3;                          /* 0.0 polygon, 1.3333 no corners */
    param->opttolerance = 0.5;                      /* bigger: less accurate, fewer segments */

    for(i = 0; i < 0x110000; i++)
        if(ctx.glyphs[i].numlayer) numchars++;

    memset(&bm, 0, sizeof(potrace_bitmap_t));
    for(i = 0; i < 0x110000; i++) {
        if(!ctx.glyphs[i].numlayer) continue;
        if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_VECTORIZE);
        n = sfn_glyph(254, i, -1, 0, &g);
        for(j = 0; j < ctx.glyphs[i].numlayer; j++)
            if(ctx.glyphs[i].layers[j].data)
                free(ctx.glyphs[i].layers[j].data);
        ctx.glyphs[i].numlayer = ctx.glyphs[i].width = ctx.glyphs[i].height = 0;
        if(n) {
            s = g.p > g.h ? g.p : g.h;
            bm.w = g.p;
            bm.h = g.h;
            bm.dy = (g.p + BM_WORDBITS - 1) / BM_WORDBITS;
            n = bm.h * bm.dy * BM_WORDSIZE;
            bm.map = (potrace_word *)realloc(bm.map, n);
            if(!bm.map) { fprintf(stderr,"libsfn: memory allocation error\n"); continue; }
            memset(bm.map, 0, n);
            for(n = k = 0; n < g.h; n++)
                for(j = 0; j < g.p; j++, k++)
                    if(g.data[k] != 0xFF) BM_USET(bm, j, n);
            st = potrace_trace(param, &bm);
            if (!st || st->status != POTRACE_STATUS_OK) { fprintf(stderr,"libsfn: error tracing bitmap U+%06X\n", i); continue; }
            p = st->plist;
            while (p != NULL) {
                n = p->curve.n;
                c = p->curve.c;
                unicode = i;
                lyr = sfn_layeradd(i, SSFN_FRAG_CONTOUR, 0, 0, 0, 0, 0xFE, NULL);
                if(!lyr) { fprintf(stderr,"libsfn: memory allocation error\n"); break; }
                sfn_contadd(lyr, SSFN_CONTOUR_MOVE, c[n-1][2].x * 254 / s, c[n-1][2].y * 254 / s, 0,0, 0,0);
                for(j = 0; j < n; j++)
                    switch(p->curve.tag[j]) {
                        case POTRACE_CORNER:
                            sfn_contadd(lyr, SSFN_CONTOUR_LINE, c[j][1].x * 254 / s, c[j][1].y * 254 / s, 0,0, 0,0);
                            sfn_contadd(lyr, SSFN_CONTOUR_LINE, c[j][2].x * 254 / s, c[j][2].y * 254 / s, 0,0, 0,0);
                        break;
                        case POTRACE_CURVETO:
                            sfn_contadd(lyr, SSFN_CONTOUR_CUBIC, c[j][2].x * 254 / s, c[j][2].y * 254 / s,
                                c[j][0].x * 254 / s, c[j][0].y * 254 / s, c[j][1].x * 254 / s, c[j][1].y * 254 / s);
                        break;
                    }
                p = p->next;
            }
            potrace_state_free(st);
        }
    }
    if(bm.map) free(bm.map);
    potrace_param_free(param);
    ctx.width = ctx.height = ctx.baseline = ctx.underline = 0;
    sfn_sanitize(-1);
    if(ctx.height > 0 && old > 0) {
        for(i = 0; i < 0x110000; i++) {
            ctx.glyphs[i].adv_x = ctx.glyphs[i].adv_x * ctx.height / old;
            ctx.glyphs[i].adv_y = ctx.glyphs[i].adv_y * ctx.height / old;
            ctx.glyphs[i].ovl_x = ctx.glyphs[i].ovl_x * ctx.height / old;
            for(j = 0; j < ctx.glyphs[i].numkern; j++) {
                ctx.glyphs[i].kern[j].x = ctx.glyphs[i].kern[j].x * ctx.height / old;
                ctx.glyphs[i].kern[j].y = ctx.glyphs[i].kern[j].y * ctx.height / old;
            }
        }
    }
}

/**
 * Print out a UNICODE blocks coverage report
 */
void sfn_coverage()
{
    int i, j, m, n, a, b, d;

    printf("| Coverage | NumChar | Start  | End    | Description                                    |\n"
           "| -------: | ------: | ------ | ------ | ---------------------------------------------- |\n");
    for(i = 0; i < UNICODE_NUMBLOCKS; i++)
        ublocks[i].cnt = 0;
    for(i = m = 0; i < 0x110000; i++)
        if(ctx.glyphs[i].numlayer) {
            m++;
            for(j = 0; j < UNICODE_NUMBLOCKS; j++)
                if(i >= ublocks[j].start && i <= ublocks[j].end) { ublocks[j].cnt++; m--; break; }
        }
    for(i = a = b = d = 0; i < UNICODE_NUMBLOCKS; i++) {
        if(ublocks[i].cnt) {
            n = ublocks[i].end - ublocks[i].start + 1 - ublocks[i].undef;
            if(ublocks[i].cnt > n) { m += ublocks[i].cnt - n; ublocks[i].cnt = n; };
            a += ublocks[i].cnt; b += n;
            d = ublocks[i].cnt * 1000 / n;
            printf("|   %3d.%d%% | %7d | %06X | %06X | %-46s |\n", d/10, d%10,
                ublocks[i].cnt, ublocks[i].start, ublocks[i].end, ublocks[i].name);
        }
    }
    if(m)
        printf("|        - | %7d | 000000 | 10FFFF | No Block                                       |\n", m);
    d = a * 1000 / b;
    printf("| -------- | ------- | ---------------------------------------------------------------- |\n"
        "|   %3d.%d%% | %7d |       = = = = = = = =   Overall Coverage   = = = = = = = =       |\n", d/10, d%10, a);
}
