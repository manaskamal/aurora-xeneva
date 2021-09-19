/*
 * libsfn/libsfn.h
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
 * @brief SSFN Utility functions
 *
 */

#include <stdint.h>
#include "ssfn.h"

#define iswhitespace(x) ((x)==0x20||(x)==0xA0)

/**
 * Messages for progress bar and progress bar callback prototype
 */
enum {
    PBAR_NONE = 0,
    PBAR_MEASURE,
    PBAR_OUTLINE,
    PBAR_GETKERN,
    PBAR_QUANT,
    PBAR_RDFILE,
    PBAR_BITMAP,
    PBAR_TALLPIX,
    PBAR_WIDEPIX,
    PBAR_GENFRAG,
    PBAR_COMPFRAG,
    PBAR_SERFRAG,
    PBAR_WRTCHARS,
    PBAR_WRTFILE,
    PBAR_RASTERIZE,
    PBAR_VECTORIZE,
    PBAR_COPY
};
typedef void (*sfnprogressbar_t)(int step, int numstep, int curr, int total, int msg);

/**
 * Glyph cache structure, private (same as ssfn_glyph_t but with larger bit widths)
 */
typedef struct {
    uint16_t p;                         /* data buffer pitch, bytes per line */
    uint16_t h;                         /* data buffer height */
    uint16_t o;                         /* overlap of glyph, scaled to size */
    uint16_t x;                         /* advance x, scaled to size */
    uint16_t y;                         /* advance y, scaled to size */
    uint16_t a;                         /* ascender, scaled to size */
    uint16_t d;                         /* descender, scaled to size */
    uint8_t data[(260 + 260 / SSFN_ITALIC_DIV) << 8];        /* data buffer */
} sfngc_t;

/**
 * Fragments structure, private
 */
typedef struct {
    unsigned char type;
    int w, h;
    int pos;
    int len;
    int cnt;
    int idx;
    unsigned char *data;
} sfnfrag_t;

/**
 * Kerning group, private
 */
typedef struct {
    int first;
    int last;
    int idx;
} sfnkgrp_t;

/**
 * Kerning position, private
 */
typedef struct {
    int idx;
    int pos;
    int len;
    unsigned char *data;
} sfnkpos_t;


/**
 * Contour command
 */
typedef struct {
    unsigned char type;         /* one of SSFN_CONTOUR_x defines */
    unsigned char px;           /* on curve point coordinates */
    unsigned char py;
    unsigned char c1x;          /* control point #1 coordinates */
    unsigned char c1y;
    unsigned char c2x;          /* control point #2 coordinates */
    unsigned char c2y;
} sfncont_t;

/**
 * One glyph layer
 */
typedef struct {
    unsigned char type;         /* one of SSFN_FRAG_x defines */
    unsigned char color;        /* color palette index, 0xFE foreground, 0xFF background */
    int len, miny, minx;        /* private properties, len = sfncont_t array length */
    unsigned char *data;        /* either color index map, or sfncont_t array */
} sfnlayer_t;

/**
 * One kerning relation
 */
typedef struct {
    int n;                      /* next code point in relation */
    char x;                     /* relative horizontal offset */
    char y;                     /* relative vertical offset */
} sfnkern_t;

/**
 * One glyph
 */
typedef struct {
    unsigned char width;        /* glyph width */
    unsigned char height;       /* glyph height */
    unsigned char ovl_x;        /* overlay x */
    unsigned char adv_x;        /* horizontal advance */
    unsigned char adv_y;        /* vertical advance */
    unsigned char numlayer;     /* number of layers */
    sfnlayer_t *layers;         /* the layers */
    int numkern, kgrp;          /* private, number of kerning relations and groups */
    sfnkern_t *kern;            /* kerning relations array */
    unsigned char rtl, hintv[33], hinth[33]; /* right-toleft flag and hinting */
    int numfrag;                /* private, used by sfn_save() */
    int *frags;
} sfnglyph_t;

/**
 * In-memory font structure
 */
typedef struct {
    unsigned char family;       /* font family type, see sfn_setfamilytype() */
    unsigned char style;        /* ORd SSFN_STYLE_x defines */
    unsigned char width;        /* overall font width */
    unsigned char height;       /* overall font height */
    unsigned char baseline;     /* baseline (ascent) */
    unsigned char underline;    /* underline position */
    char *filename;             /* filename */
    char *name;                 /* unique name of the font */
    char *familyname;           /* font family name */
    char *subname;              /* font family sub-name */
    char *revision;             /* font revision / version string */
    char *manufacturer;         /* font designer / creator / foundry */
    char *license;              /* font license */
    sfnglyph_t glyphs[0x110000];/* glyphs array */
    int numcpal;                /* number of color palette entries */
    unsigned char cpal[1024];   /* color palette */
    char *ligatures[SSFN_LIG_LAST-SSFN_LIG_FIRST+1]; /* ligatures, UTF-8 strings for U+F000 .. U+F8FF */
    int numskip;                /* code points to skip on load, see sfn_skipadd() */
    int *skip;
    int numfrags;               /* private, used by sfn_save() and sfn_glyph() */
    sfnfrag_t *frags;
    int numkpos;
    sfnkpos_t *kpos;
    long int total;
    uint16_t *p;
    int np, ap, mx, my, lx, ly;
} sfnctx_t;
/**
 * The global font context
 */
extern sfnctx_t ctx;
/**
 * Progress bar callback
 */
extern sfnprogressbar_t pbar;

/*** arguments ***/
extern int rs, re, replace, skipundef, skipcode, hinting, adv, relul, rasterize, dump, origwh;
extern int unicode, lastuni, quiet, dorounderr;

/*** unicode.c ***/
#include "unicode.h"

/*** util.c ***/
#include "util.h"

/*** sfn.c ***/
void sfn_init(sfnprogressbar_t pb);
void sfn_setfamilytype(int t);
void sfn_setstr(char **s, char *n, int len);
void sfn_chardel(int unicode);
int sfn_charadd(int unicode, int w, int h, int ax, int ay, int ox);
sfnlayer_t *sfn_layeradd(int unicode, int t, int x, int y, int w, int h, int c, unsigned char *data);
void sfn_layerdel(int unicode, int idx);
int sfn_contadd(sfnlayer_t *lyr, int t, int px, int py, int c1x, int c1y, int c2x, int c2y);
int sfn_kernadd(int unicode, int next, int x, int y);
void sfn_hintgen(int unicode);
unsigned char sfn_cpaladd(int r, int g, int b, int a);
void sfn_skipadd(int unicode);
int sfn_load(char *filename, int dump);
int sfn_save(char *filename, int ascii, int compress);
void sfn_sanitize(int unicode);
int sfn_glyph(int size, int unicode, int layer, int postproc, sfngc_t *g);
void sfn_rasterize(int size);
void sfn_vectorize();
void sfn_coverage();
void sfn_free();
