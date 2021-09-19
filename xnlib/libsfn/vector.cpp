/*
 * libsfn/vector.c
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
 * @brief File functions for vector fonts (sfd is native, otherwise using FreeType2)
 *
 */

#ifndef USE_NOFOREIGN

#include <stdlib.h>
#include <string.h>
#include "libsfn.h"
#include "vector.h"
#include "bitmap.h"

#ifdef HAS_FT
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_IMAGE_H
#include FT_BBOX_H
#include FT_SFNT_NAMES_H

#define FT_SIZE 1024

FT_Library ft = NULL;
FT_Face face;
FT_BBox *bbox;

typedef struct {
    int unicode;
    FT_BBox bbox;
} ftchr_t;
ftchr_t *ftchars;
#endif

int min_y, max_y, min_x, max_x, max_b, max_s, max_w, max_h, unicode;
sfnlayer_t *currlayer;

/**
 * Parse FontForge's SplineFontDb
 */
void sfd(char *ptr, int size)
{
    int i, j, w = -1, h = 0, b = 0, unicode = 0, nc = 0, numchars = 0, ps = 0, p[7], mx, xx, my, xy, f = 0;
    long int avg_w = 0, avg_h = 0, avg_n = 0;
    char *end = ptr + size, *endprop, *face, *name = NULL;
#define scx(x) (((x - mx) * 255 + max_s / 2) / max_s)
#define scy(y) (((max_b - y) * 255 + max_s / 2) / max_s)

    for(face = ptr; face + 11 < end && *face; face++) {
        if(!memcmp(face, "StartChar:", 10)) numchars++;
        if(!memcmp(face, "BitmapFont:", 11)) {
            /* Ooops, we have a bitmap font */
            bdf(face, end - face);
            return;
        }
    }
    face = NULL;

    while(ptr < end && *ptr) {
        if(!memcmp(ptr, "FullName: ", 10) && !face) { ptr += 10; face = ptr; }
        if(!memcmp(ptr, "Version: ", 9) && !ctx.revision) { ptr += 9; sfn_setstr(&ctx.revision, ptr, 0); }
        if(!memcmp(ptr, "FontName: ", 10) && !ctx.name && !ctx.subname) {
            ptr += 10; while(*ptr && *ptr!='-' && *ptr!='\n') { ptr++; }
            if(*ptr == '-') { ptr++; sfn_setstr(&ctx.subname, ptr, 0); }
        }
        if(!memcmp(ptr, "FamilyName: ", 12) && !ctx.manufacturer) { ptr += 12; sfn_setstr(&ctx.manufacturer, ptr, 0); }
        if(!memcmp(ptr, "FamilyName: ", 12) && !ctx.familyname) { ptr += 12; sfn_setstr(&ctx.familyname, ptr, 0); }
        if(!memcmp(ptr, "Copyright: ", 11) && !ctx.license) { ptr += 11; sfn_setstr(&ctx.license, ptr, 0); }
        if(!memcmp(ptr, "Ascent: ", 8)) {
            ptr += 8; while(*ptr == ' ') ptr++;
            b = atoi(ptr); }
        if(!memcmp(ptr, "Descent: ", 9)) {
            ptr += 9; while(*ptr == ' ') ptr++;
            ps = atoi(ptr); }
        if(!memcmp(ptr, "UnderlinePosition: ", 19)) {
            ptr += 19; while(*ptr == ' ') ptr++;
            relul = atoi(ptr); if(relul < 0) relul = -relul; }
        if(!memcmp(ptr, "ItalicAngle: ", 13)) {
            ptr += 13; while(*ptr == ' ') ptr++;
            if(ptr[0] != '0') ctx.style |= SSFN_STYLE_ITALIC; }
        if(!memcmp(ptr, "Weight: Bold", 12)) ctx.style |= SSFN_STYLE_BOLD;
        if(!memcmp(ptr, "BeginChars:", 11)) break;
        while(*ptr && *ptr!='\n') ptr++;
        while(*ptr=='\n') ptr++;
    }
    ps += b;
    if(!ctx.name) {
        if(!face) face = ctx.familyname;
        if(face && ctx.subname && ctx.subname[0]) {
            for(i = 0; face[i] && face[i] != '\"' && face[i] != '\r' && face[i] != '\n'; i++);
            j = strlen(ctx.subname);
            name = malloc(i + j + 2);
            if(!name) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
            memcpy(name, face, i);
            name[i] = ' ';
            memcpy(name + i + 1, ctx.subname, j);
            name[i + j + 1] = 0;
            sfn_setstr(&ctx.name, name, 0);
            free(name);
        } else
            sfn_setstr(&ctx.name, ctx.familyname, 0);
    }
    printf("\r  Name '%s' num_glyphs: %d, ascender: %d, underline: %d, height: %d\n", ctx.name, numchars, b, b + relul, ps);
    if(!ps) return;
    min_x = min_y = 2*ps; max_x = max_y = max_b = max_w = max_h = -2*ps; numchars = 0;
    endprop = ptr;
    while(ptr < end && *ptr) {
        if(!memcmp(ptr, "Encoding: ", 10)) {
            ptr += 10; while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            unicode = atoi(ptr); while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
            if(*ptr == '0' && (ptr[1] == '\r' || ptr[1] == '\n')) unicode = 0;
            f = 0;
        }
        if(!memcmp(ptr, "Fore", 4))  f = 1;
        if(!memcmp(ptr, "Back", 4))  f = 0;
        if(f && !memcmp(ptr, "SplineSet", 9)) {
            ptr += 9; while(*ptr && *ptr!='\n') { ptr++; } while(*ptr=='\n') ptr++;
            for(j = 0; j < ctx.numskip && ctx.skip[j] != unicode; j++);
            if(unicode >= 0 && unicode >= rs && unicode <= re && j >= ctx.numskip) {
                mx = my = 2*ps; xx = xy = -2*ps; numchars++;
                while(ptr < end && *ptr && memcmp(ptr, "EndSplineSet", 12)) {
                    for(j = 0; j < 7; j++) {
                        while(*ptr == ' ') ptr++;
                        if(!memcmp(ptr, "Spiro", 5)) while(ptr < end && *ptr && memcmp(ptr - 9, "EndSpiro", 8)) ptr++;
                        if(j >=6 || (*ptr != ' ' && *ptr != '-' && !(*ptr >= '0' && *ptr <= '9'))) break;
                        p[j] = atoi(ptr); while(*ptr && *ptr != ' ') ptr++;
                        if(j & 1) {
                            if(p[j] > max_b) max_b = p[j];
                            if(p[j] < min_y) min_y = p[j];
                            if(p[j] > max_y) max_y = p[j];
                            if(p[j] < my) my = p[j];
                            if(p[j] > xy) xy = p[j];
                        } else {
                            if(p[j] < min_x) min_x = p[j];
                            if(p[j] > max_x) max_x = p[j];
                            if(p[j] < mx) mx = p[j];
                            if(p[j] > xx) xx = p[j];
                        }
                    }
                    if(ptr[0] != 'm' && ptr[0] != 'l' && ptr[0] != 'c') {
                        if(!quiet)
                            fprintf(stderr, "\rlibsfn: bad font, unknown spline command '%c' for U+%06X    \n", ptr[0], unicode);
                        return;
                    }
                    while(*ptr && *ptr!='\n') ptr++;
                    while(*ptr=='\n') ptr++;
                }
                if(mx < xx && my < xy) {
                    xx -= mx - 1; xy -= my - 1;
                    if(xx > max_w) max_w = xx;
                    if(xy > max_h) max_h = xy;
                    avg_w += xx;
                    avg_h += xy;
                    avg_n++;
                }
            }
            while(ptr < end && *ptr && memcmp(ptr, "EndChar", 7)) ptr++;
        }
        while(*ptr && *ptr!='\n') ptr++;
        while(*ptr=='\n') ptr++;
    }
    if(avg_n > 0) {
        avg_w /= avg_n;
        avg_h /= avg_n;
    }
    if(!quiet && b != max_b) {
        fprintf(stderr, "\rlibsfn: inconsistent font: ascender %d != max(yMax) %d    \n", b, max_b);
    }
    printf("\r  Numchars: %d, Bounding box: (%d, %d), (%d, %d) dx %d dy %d, w: %d, h: %d, baseline: %d\n", numchars,
        min_x, min_y, max_x, max_y, max_x - min_x, max_y - min_y, max_w, max_h, max_b);
    max_s = max_w > max_h ? max_w : max_h;
    if(max_s > 0) {
        printf("  Scaling to %d x %d, average: %ld x %ld\n", max_s, max_s, avg_w, avg_h);
        ptr = endprop;
        while(ptr < end && *ptr) {
            if(!memcmp(ptr, "Encoding: ", 10)) {
                ptr += 10; while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
                unicode = atoi(ptr); while(*ptr && *ptr != ' ') { ptr++; } while(*ptr == ' ') ptr++;
                if(*ptr == '0' && (ptr[1] == '\r' || ptr[1] == '\n')) unicode = 0;
                w = -1; h = f = 0;
            }
            if(!memcmp(ptr, "Fore", 4))  f = 1;
            if(!memcmp(ptr, "Back", 4))  f = 0;
            if(!memcmp(ptr, "Width: ", 7)) { ptr += 7; w = atoi(ptr);  }
            if(!memcmp(ptr, "VWidth: ", 8)) { ptr += 8; h = atoi(ptr);  }
            if(!memcmp(ptr, "EndChar", 7) && iswhitespace(unicode) && (w || h))
                sfn_charadd(unicode, 0, 0, w, h, 0);
            if(f && !memcmp(ptr, "SplineSet", 9)) {
                ptr += 9; while(*ptr && *ptr!='\n') { ptr++; } while(*ptr=='\n') ptr++;
                for(j = 0; j < ctx.numskip && ctx.skip[j] != unicode; j++);
                if(unicode >= 0 && unicode >= rs && unicode <= re && j >= ctx.numskip) {
                    if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_OUTLINE);
                    mx = my = 2*ps; xx = xy = -2*ps; endprop = ptr;
                    /* sfd does not store the glyph metrics */
                    while(ptr < end && *ptr && memcmp(ptr, "EndSplineSet", 12)) {
                        for(j = 0; j < 7; j++) {
                            while(*ptr == ' ') ptr++;
                            if(!memcmp(ptr, "Spiro", 5)) while(ptr < end && *ptr && memcmp(ptr - 9, "EndSpiro", 8)) ptr++;
                            if(j >=6 || (*ptr != ' ' && *ptr != '-' && !(*ptr >= '0' && *ptr <= '9'))) break;
                            p[j] = atoi(ptr); while(*ptr && *ptr != ' ') ptr++;
                            if(j & 1) {
                                if(p[j] < my) my = p[j];
                                if(p[j] > xy) xy = p[j];
                            } else {
                                if(p[j] < mx) mx = p[j];
                                if(p[j] > xx) xx = p[j];
                            }
                        }
                        while(*ptr && *ptr!='\n') ptr++;
                        while(*ptr=='\n') ptr++;
                    }
                    if(mx < xx && my < xy) {
                        xx -= mx - 1; xy -= my - 1;
                        if(!quiet && (xx >= 2*avg_w+avg_w/2 || xy >= 2*avg_h+avg_h/2)) {
                            fprintf(stderr, "\rlibsfn: irregular dimensions in font: U+%06X", unicode);
                            if(xx >= 2*avg_w+avg_w/2) {
                                fprintf(stderr, ", width: %d ", xx);
                                if(xx >= 3*avg_w)
                                    fprintf(stderr, "(%ld times the average, can't be right!!!)", xx / avg_w);
                            }
                            if(xy >= 2*avg_h+avg_h/2) {
                                fprintf(stderr, ", height: %d ", xy);
                                if(xy >= 3*avg_h)
                                    fprintf(stderr, "(%ld times the average, can't be right!!!)", xy / avg_h);
                            }
                            fprintf(stderr, "\n");
                        }
                        /* now that we know the actual dimensions of the glyph, go once again... */
                        if(h > 0) w = 0;
                        if(w < 0) w = xx > 0 ? xx : 0;
                        if(sfn_charadd(unicode, 0, 0, w, h, !h && mx < 0 ? -mx * 255 / max_s : 0)) {
                            ptr = endprop;
                            while(ptr < end && *ptr && memcmp(ptr, "EndSplineSet", 12)) {
                                for(j = 0; j < 7; j++) {
                                    while(*ptr == ' ') ptr++;
                                    if(!memcmp(ptr, "Spiro", 5)) while(ptr < end && *ptr && memcmp(ptr - 9, "EndSpiro", 8)) ptr++;
                                    if(j >=6 || (*ptr != ' ' && *ptr != '-' && !(*ptr >= '0' && *ptr <= '9'))) break;
                                    p[j] = atoi(ptr); while(*ptr && *ptr != ' ') ptr++;
                                }
                                switch(ptr[0]) {
                                    case 'm':
                                        currlayer = sfn_layeradd(unicode, SSFN_FRAG_CONTOUR, 0, 0, 0, 0, 0xFE, NULL);
                                        sfn_contadd(currlayer, SSFN_CONTOUR_MOVE, scx(p[0]), scy(p[1]), 0,0, 0,0);
                                    break;
                                    case 'l': sfn_contadd(currlayer, SSFN_CONTOUR_LINE, scx(p[0]), scy(p[1]), 0,0, 0,0); break;
                                    case 'c':
                                        sfn_contadd(currlayer, SSFN_CONTOUR_CUBIC, scx(p[4]), scy(p[5]), scx(p[0]), scy(p[1]),
                                            scx(p[2]),scy(p[3]));
                                    break;
                                }
                                while(*ptr && *ptr!='\n') ptr++;
                                while(*ptr=='\n') ptr++;
                            }
                        }
                    }
                }
                while(ptr < end && *ptr && memcmp(ptr, "EndChar", 7)) ptr++;
            }
            while(*ptr && *ptr!='\n') ptr++;
            while(*ptr=='\n') ptr++;
        }
    } /* max_s != 0 */
    if(!ctx.baseline && max_b) ctx.baseline = max_b;
}

#ifdef HAS_FT
/**
 * Transform and scale coordinates
 */
int sx(int i)
{
    return ((i - bbox->xMin) * 255 + max_s / 2) / max_s;
}

int sy(int i)
{
    return ((max_b - i) * 255 + max_s / 2) / max_s;
}

/*** contour command callbacks for FT2 ***/

int move(const FT_Vector *to, void *ptr)
{
    (void)ptr;
    currlayer = sfn_layeradd(unicode, SSFN_FRAG_CONTOUR, 0, 0, 0, 0, 0xFE, NULL);
    sfn_contadd(currlayer, SSFN_CONTOUR_MOVE, sx(to->x), sy(to->y), 0,0, 0,0);
    return 0;
}

int line(const FT_Vector *to, void *ptr)
{
    (void)ptr;
    sfn_contadd(currlayer, SSFN_CONTOUR_LINE, sx(to->x), sy(to->y), 0,0, 0,0);
    return 0;
}

int quad(const FT_Vector *control, const FT_Vector *to, void *ptr)
{
    (void)ptr;
    sfn_contadd(currlayer, SSFN_CONTOUR_QUAD, sx(to->x), sy(to->y), sx(control->x), sy(control->y), 0,0);
    return 0;
}

int cubic(const FT_Vector *control1, const FT_Vector *control2, const FT_Vector *to, void *ptr)
{
    (void)ptr;
    sfn_contadd(currlayer, SSFN_CONTOUR_CUBIC, sx(to->x), sy(to->y), sx(control1->x), sy(control1->y),
        sx(control2->x), sy(control2->y));
    return 0;
}

FT_Outline_Funcs funcs = { move, line, quad, cubic, 0, 0 };

/**
 * Parse a TTF (or any other vector font that FT2 supports)
 */
void ttf()
{
    FT_UInt agi;
    FT_ULong cp;
    FT_Vector v;
    FT_Error error;
    int i, j, n, x, y, numchars = 0;
    long int avg_w = 0, avg_h = 0, avg_n = 0;
    ftchr_t *c;

    /* unbeliveable, FT2 lib does not return the number of characters in the font... */
    for(cp = FT_Get_First_Char(face, &agi); agi; cp = FT_Get_Next_Char(face, cp, &agi)) numchars++;

    c = ftchars = (ftchr_t*)malloc((numchars + 1) * sizeof(ftchr_t));
    if(!ftchars) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }
    memset(ftchars, 0, (numchars + 1) * sizeof(ftchr_t));

    /* ...and it returns incorrect bounding box. Never trust FT2's scaling. */
    min_x = min_y = face->units_per_EM*2; max_x = max_y = max_b = max_w = max_h = -face->units_per_EM*2;
    for(cp = FT_Get_First_Char(face, &agi), i = 0; i <= numchars && agi; i++) {
        if(pbar) (*pbar)(1, 3, i, numchars, PBAR_MEASURE);
        for(j = 0; j < ctx.numskip && ctx.skip[j] != (int)cp; j++);
        if(j >= ctx.numskip) {
            c->unicode = (int)cp;
            c->bbox.xMin = c->bbox.xMax = c->bbox.yMin = c->bbox.yMax = 0;
            if(FT_Load_Glyph(face, FT_Get_Char_Index(face, cp), FT_LOAD_NO_SCALE) ||
                (i && !face->glyph->glyph_index)) continue;
            if(!origwh) {
                FT_Outline_Get_BBox(&face->glyph->outline, &c->bbox);
            } else {
                if(!face->glyph->metrics.vertBearingX && !face->glyph->metrics.vertBearingY) {
                    c->bbox.xMin = face->glyph->metrics.horiBearingX;
                    c->bbox.xMax = face->glyph->metrics.horiBearingX + face->glyph->metrics.width;
                    c->bbox.yMin = face->glyph->metrics.horiBearingY - face->glyph->metrics.height;
                    c->bbox.yMax = face->glyph->metrics.horiBearingY;
                } else {
                    c->bbox.xMin = face->glyph->metrics.vertBearingX;
                    c->bbox.xMax = face->glyph->metrics.vertBearingX + face->glyph->metrics.width;
                    c->bbox.yMin = face->glyph->metrics.vertBearingY - face->glyph->metrics.height;
                    c->bbox.yMax = face->glyph->metrics.vertBearingY;
                }
            }
            if(face->glyph->metrics.width > max_w) max_w = face->glyph->metrics.width;
            if(face->glyph->metrics.height > max_h) max_h = face->glyph->metrics.height;
            if(c->bbox.yMax > max_b) max_b = c->bbox.yMax;
            if(c->bbox.xMin < min_x) min_x = c->bbox.xMin;
            if(c->bbox.xMax > max_x) max_x = c->bbox.xMax;
            if(c->bbox.yMin < min_y) min_y = c->bbox.yMin;
            if(c->bbox.yMax > max_y) max_y = c->bbox.yMax;
            avg_w += face->glyph->metrics.width;
            avg_h += face->glyph->metrics.height;
            avg_n++;
/*
if(cp==0x21) {
    printf("\n%ld UUUUU Bounding box (%ld, %ld), (%ld, %ld)\n", cp,c->bbox.xMin, c->bbox.yMin, c->bbox.xMax, c->bbox.yMax);
    printf("metrics w %ld h %ld horiAdv %ld vertAdv %ld hbear %ld %ld vbear %ld %ld\n", face->glyph->metrics.width, face->glyph->metrics.height,
        face->glyph->metrics.horiAdvance, face->glyph->metrics.vertAdvance, face->glyph->metrics.horiBearingX, face->glyph->metrics.horiBearingY,
        face->glyph->metrics.vertBearingX, face->glyph->metrics.vertBearingY);
}
*/
            if(!quiet && (c->bbox.xMin != face->glyph->metrics.horiBearingX ||
                c->bbox.yMin != face->glyph->metrics.horiBearingY - face->glyph->metrics.height ||
                c->bbox.xMax != c->bbox.xMin + face->glyph->metrics.width ||
                c->bbox.yMax != c->bbox.yMin + face->glyph->metrics.height)) {
                    fprintf(stderr, "\rlibsfn: inconsistent font: U+%06lX", cp);
                    if(c->bbox.xMin != face->glyph->metrics.horiBearingX)
                        fprintf(stderr, ", xMin %ld != hBX %ld", c->bbox.xMin, face->glyph->metrics.horiBearingX);
                    if(c->bbox.yMin != face->glyph->metrics.horiBearingY - face->glyph->metrics.height)
                        fprintf(stderr, ", yMin %ld != hBY-h %ld", c->bbox.yMin,
                            face->glyph->metrics.horiBearingY - face->glyph->metrics.height);
                    if(c->bbox.xMax != c->bbox.xMin + face->glyph->metrics.width)
                        fprintf(stderr, ", xMax %ld != xMin+w %ld", c->bbox.xMax,
                            c->bbox.xMin + face->glyph->metrics.width);
                    if(c->bbox.yMax != c->bbox.yMin + face->glyph->metrics.height)
                        fprintf(stderr, ", yMax %ld != yMin+h %ld", c->bbox.yMax,
                            c->bbox.yMin + face->glyph->metrics.height);
                    fprintf(stderr, "    \n");
            }
            c++;
        }
        cp = FT_Get_Next_Char(face, cp, &agi);
    }
    if(avg_n > 0) {
        avg_w /= avg_n;
        avg_h /= avg_n;
    }
    /* due to optionally skipped characters */
    numchars = (int)((unsigned long int)c - (unsigned long int)ftchars) / sizeof(ftchr_t);
    if(min_x >= max_x || min_y >= max_y) min_x = max_x = min_y = max_y = max_w = max_h = max_b = 0;

    if(!quiet && face->ascender != max_b) {
        fprintf(stderr, "\rlibsfn: inconsistent font: ascender %d != max(yMax) %d    \n", face->ascender, max_b);
    }
    if(origwh) {
        if(max_x - min_x > max_w) max_w = max_x - min_x;
        if(max_y - min_y > max_h) max_h = max_y - min_y;
    }
    printf("\r  Numchars: %d, Bounding box: (%d, %d), (%d, %d) dx %d dy %d, w: %d, h: %d, baseline: %d\n", numchars,
        min_x, min_y, max_x, max_y, max_x - min_x, max_y - min_y, max_w, max_h, max_b);
    max_s = max_w > max_h ? max_w : max_h;
    if(max_s > 0) {
        printf("  Scaling to %d x %d, average: %ld x %ld\n", max_s, max_s, avg_w, avg_h);

        /* get font style */
        if(face->style_flags & FT_STYLE_FLAG_BOLD) ctx.style |= SSFN_STYLE_BOLD;
        if(face->style_flags & FT_STYLE_FLAG_ITALIC) ctx.style |= SSFN_STYLE_ITALIC;

        /* baseline and underline */
        ctx.baseline = (max_b * 255 + max_s - 1) / max_s;
        ctx.underline = ((max_b - face->underline_position) * 255 + max_s - 1) / max_s;

        /* iterate on characters and contour outlines */
        lastuni = -1;
        for(i = 0; i < numchars; i++) {
            unicode = ftchars[i].unicode;
            if(pbar) (*pbar)(2, 3, i, numchars, PBAR_OUTLINE);
            if(FT_Load_Glyph(face, FT_Get_Char_Index(face, unicode), FT_LOAD_NO_SCALE) ||
                (i && !face->glyph->glyph_index)) continue;
            bbox = &ftchars[i].bbox;
            if(face->glyph->metrics.horiAdvance /* !face->glyph->metrics.vertBearingX && !face->glyph->metrics.vertBearingY*/) {
                x = face->glyph->metrics.horiAdvance - bbox->xMin + 1; y = 0;
                if(x < 0) x = 1;
                x = (x * 255 + max_s - 1) / max_s;
            } else {
                x = 0; y = face->glyph->metrics.vertAdvance - bbox->yMin + 1;
                if(y < 0) y = 1;
                y = (y * 255 + max_s - 1) / max_s;
            }
            if(!quiet && (face->glyph->metrics.width >= 2*avg_w+avg_w/2 || face->glyph->metrics.height >= 2*avg_h+avg_h/2)) {
                fprintf(stderr, "\rlibsfn: irregular dimensions in font: U+%06X", unicode);
                if(face->glyph->metrics.width >= 2*avg_w+avg_w/2) {
                    fprintf(stderr, ", width: %ld ", face->glyph->metrics.width);
                    if(face->glyph->metrics.width >= 3*avg_w)
                        fprintf(stderr, "(%ld times the average, can't be right!!!)", face->glyph->metrics.width / avg_w);
                }
                if(face->glyph->metrics.height >= 2*avg_h+avg_h/2) {
                    fprintf(stderr, ", height: %ld ", face->glyph->metrics.height);
                    if(face->glyph->metrics.height >= 3*avg_h)
                        fprintf(stderr, "(%ld times the average, can't be right!!!)", face->glyph->metrics.height / avg_h);
                }
                fprintf(stderr, "\n");
            }
            /* don't trust FT2's width and height, we'll recalculate them from the coordinates */
            if(sfn_charadd(unicode, 0, 0, x, y, !y && bbox->xMin < 0 ? (-bbox->xMin * 255 + max_s - 1) / max_s : 0)) {
                error = FT_Outline_Decompose(&face->glyph->outline, &funcs, NULL);
                if(error && !quiet) { fprintf(stderr, "libsfn: FreeType2 decompose error %x\n", error); }
            }
        }

        /* get kerning information */
        if(face->face_flags & FT_FACE_FLAG_KERNING) {
            for(i = n = 0; i < numchars; i++) {
                if(pbar) (*pbar)(3, 3, i, numchars, PBAR_GETKERN);
                for(j = 0; j < numchars; j++) {
                    if(ftchars[i].unicode<33 || ftchars[j].unicode<33) continue;
                    v.x = v.y = 0;
                    FT_Get_Kerning(face, ftchars[i].unicode, ftchars[j].unicode, FT_KERNING_UNSCALED, &v);
                    if(v.x) { v.x = (v.x * 255 + max_s - 1) / max_s; v.y = 0; }
                    else { v.x = 0; v.y = (v.y * 255 + max_s - 1) / max_s; }
                    if(v.x >= -1 && v.x <= 1 && v.y >= -1 && v.x <= 1) continue;
                    sfn_kernadd(ftchars[i].unicode, ftchars[j].unicode, v.x, v.y);
                    n++;
                }
            }
            printf("\r\x1b[K  Kerning %d pairs\n", n);
        } else
            printf("\r\x1b[K  No kerning information\n");
    }
    free(ftchars);
}

/**
 * Parse bitmap font (any format that FT2 supports)
 * I know, this is not vector font related, but since all the other FT2 functions are here I didn't wanted
 * to move this function with all the includes into bitmap.c
 */
void ft2()
{
    int i, j, k, l, n, a = 0, w = 8, h = 16, nc = 0, numchars = 0, ft2bug = 0;
    unsigned char *glyph, *bitmap;
    FT_UInt agi;
    FT_ULong cp;

    /* unbeliveable, FT2 lib can't iterate on characters in the font if there's no encoding... */
    for(cp = FT_Get_First_Char(face, &agi); agi; cp = FT_Get_Next_Char(face, cp, &agi)) numchars++;

    for(i = 0; i < face->num_fixed_sizes; i++)
        if(face->available_sizes[i].height > h) {
            h = face->available_sizes[i].height;
            w = face->available_sizes[i].width;
        }
    printf("\r  Numchars: %d, num_fixed_sizes: %d, selected: %d x %d\n", numchars, face->num_fixed_sizes, w, h);
    if(!numchars) {
        printf("  FreeType2 bug, FT_Get_Next_char didn't work, trying to render ALL code points one-by-one...\n");
        ft2bug = 1; numchars = 0x10FFFF;
    }
    FT_Set_Pixel_Sizes(face, w, h);
    n = 2*h*h;
    bitmap = (unsigned char*)malloc(n);
    if(!bitmap) { fprintf(stderr,"libsfn: memory allocation error\n"); return; }

    if(ft2bug) { cp = 0; agi = 1; } else cp = FT_Get_First_Char(face, &agi);
    while(agi) {
        if(pbar) (*pbar)(0, 0, ++nc, numchars, PBAR_BITMAP);
        for(j = 0; j < ctx.numskip && ctx.skip[j] != (int)cp; j++);
        if(j < ctx.numskip) goto cont;
        if(cp < (FT_ULong)rs || cp > (FT_ULong)re || FT_Load_Glyph(face, FT_Get_Char_Index(face, cp), FT_LOAD_NO_SCALE) ||
            (cp && !face->glyph->glyph_index)) goto cont;
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);
        if(face->glyph->bitmap.pixel_mode != FT_PIXEL_MODE_MONO) goto cont;
        memset(bitmap, 0, n);
        glyph = face->glyph->bitmap.buffer;
        w = ((int)(face->glyph->bitmap.width+7) & ~7);
        for(i = k = 0; i < (int)face->glyph->bitmap.rows; i++) {
            for(j = 0; j < (int)(face->glyph->bitmap.width+7)/8; j++)
                for(l=0x80;l && k < n;l>>=1)
                    bitmap[k++] = (glyph[j] & l) ? 0xFE : 0xFF;
            glyph += face->glyph->bitmap.pitch;
        }
        a += face->glyph->bitmap_top;
        if(sfn_charadd(cp, w, face->glyph->bitmap.rows, face->glyph->advance.x >> 6, face->glyph->advance.y >> 6,
            face->glyph->bitmap_left))
                sfn_layeradd(cp, SSFN_FRAG_BITMAP, 0, 0, w, face->glyph->bitmap.rows, 0xFE, bitmap);
cont:   if(ft2bug) { cp++; if(cp > 0x10FFFF) break; } else cp = FT_Get_Next_Char(face, cp, &agi);
    }

    ctx.baseline = numchars ? a / numchars : a;
    ctx.underline = ctx.baseline + (h - ctx.baseline) / 2;

    free(bitmap);
}

/**
 * Check if FT2 can read the font
 */
int ft2_read(unsigned char *data, int size)
{
    if(!ft && FT_Init_FreeType(&ft)) { fprintf(stderr, "libsfn: unable to initialize FreeType2\n"); return 0; }
    face = NULL;
    return (!FT_New_Memory_Face(ft, data, size, 0, &face) && face) ? 1 : 0;
}

/**
 * Parse a FT2 font
 */
void ft2_parse()
{
    FT_SfntName name;
    if(!ft || !face) return;

    FT_Select_Charmap(face, FT_ENCODING_UNICODE);
    printf("\r  Name '%s' num_glyphs: %ld, units_per_EM: %d, ascender: %d, underline: %d, %s\n",
        face->family_name, face->num_glyphs, face->units_per_EM, face->ascender, face->underline_position,
        face->face_flags & FT_FACE_FLAG_SCALABLE ? "vector" : "bitmap");

    if(face->face_flags & FT_FACE_FLAG_SCALABLE) ttf(); else ft2();

    /* unique font name */
    if(!ctx.name) {
        if(!FT_Get_Sfnt_Name(face, 3, &name)) sfn_setstr(&ctx.name, (char*)name.string, name.string_len); else
        if(!FT_Get_Sfnt_Name(face, 20, &name)) sfn_setstr(&ctx.name, (char*)name.string, name.string_len);
    }
    /* fallback */
    if(!ctx.name) sfn_setstr(&ctx.name, face->family_name, 0);

    /* family name */
    if(!ctx.familyname && !FT_Get_Sfnt_Name(face, 1, &name)) sfn_setstr(&ctx.familyname, (char*)name.string, name.string_len);

    /* subfamily name */
    if(!ctx.subname && !FT_Get_Sfnt_Name(face, 2, &name)) sfn_setstr(&ctx.subname, (char*)name.string, name.string_len);

    /* version / revision */
    if(!ctx.revision && !FT_Get_Sfnt_Name(face, 5, &name)) sfn_setstr(&ctx.revision, (char*)name.string, name.string_len);

    /* manufacturer */
    if(!ctx.manufacturer) {
        if(!FT_Get_Sfnt_Name(face, 8, &name)) sfn_setstr(&ctx.manufacturer, (char*)name.string, name.string_len); else
        if(!FT_Get_Sfnt_Name(face, 9, &name)) sfn_setstr(&ctx.manufacturer, (char*)name.string, name.string_len);
    }

    /* copyright */
    if(!ctx.license) {
        if(!FT_Get_Sfnt_Name(face, 0, &name)) sfn_setstr(&ctx.license, (char*)name.string, name.string_len); else
        if(!FT_Get_Sfnt_Name(face, 7, &name)) sfn_setstr(&ctx.license, (char*)name.string, name.string_len);
    }

    FT_Done_Face(face); face = NULL;
    FT_Done_FreeType(ft); ft = NULL;
}

#endif
#endif
