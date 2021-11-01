///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///! ttf.h -- True Type Font
///!
///! /PROJECT - Aurora's Xeneva
///! /AUTHOR  - Manas Kamal Choudhury
///!
///!==============================================

#ifndef __TRUE_TYPE_FONT_H__
#define __TRUE_TYPE_FONT_H__

#include <stdint.h>
#include <stdlib.h>
#include <sys\types.h>
#include <stddef.h>
#include <sys\utf.h>
#include <endian.h>

//! 'True Type font used data types
typedef int32_t Fixed;
typedef int16_t shortFrac;
typedef int16_t FWord;
typedef uint16_t uFWord;
typedef int16_t F2Dot14;
typedef int64_t longDateTime;

#define TAG_HEAD  0x68656164
#define TAG_CMAP  0x636d6170
#define TAG_GLYF  0x676c7966
#define TAG_LOCA  0x6c6f6361
#define TAG_HHEA  0x68686561
#define TAG_HMTX  0x686d7478
#define TAG_NAME  0x6e616d65

#define PLATFORM_ID_UNICODE 0
#define PLATFORM_ID_MACINTOSH  1
#define PLATFORM_ID_MICROSOFT  3

#pragma pack (push,1)
typedef struct _ttf_off_table_ {
	uint32_t apple_scaler_type;
	uint16_t num_tables;
	uint16_t search_range;
	uint16_t entry_selector;
	uint16_t range_shift;
}offset_table_t;

#pragma pack (push,1)
typedef struct _table_dir_entry_ {
	uint32_t tag;
	uint32_t checksum;
	uint32_t offset;
	uint32_t length;
}table_dirent_t;

struct tt_table {
	off_t offset;
	size_t length;
};

struct tt_coord {
	float x;
	float y;
};

struct tt_edge {
	tt_coord start;
	tt_coord end;
	int direction;
};

struct tt_contour {
	size_t edge_count;
	size_t next_alloc;
	size_t flags;
	size_t last_start;
	tt_edge edges[];
};

struct tt_intersection {
	float x;
	int affect;
};

struct tt_shape {
	size_t edge_count;
	int lasty;
	int starty;
	int lastx;
	int startx;
	tt_edge edges[];
};

struct tt_vertex {
	unsigned char flags;
	int x;
	int y;
};

typedef struct _ttf_table_ {
	off_t offset;
	size_t length;
}ttf_table_t;

typedef struct _ttf_font_ {
	unsigned char* data;
	ttf_table_t head_ptr;
	ttf_table_t cmap_ptr;
	ttf_table_t glyf_ptr;
	ttf_table_t loca_ptr;
	ttf_table_t hhea_ptr;
	ttf_table_t hmtx_ptr;
	ttf_table_t name_ptr;
	uint16_t    em_size;
	off_t cmap_start;
	int loca_type;
	uint16_t  cmap_type;
	float scale;
}ttf_font;

#pragma pack (push,1)
typedef struct _ttf_head_ {
	Fixed version;
	Fixed font_rev;
	uint32_t checkSumAdjustment;
	uint32_t magicNumber;
	uint16_t flags;
	uint16_t unitsPerEm;
	longDateTime created;
	longDateTime modified;
	FWord xMin;
	FWord yMin;
	FWord xMax;
	FWord yMax;
	uint16_t macStyle;
	uint16_t lowestRecPPEM;
	int16_t fontDirectionHint;
	int16_t indexToLocFormat;
	int16_t glyphDataFormat;
}ttf_head;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _ttf_cmap_index_ {
	uint16_t version;
	uint16_t numberSubTables;
}ttf_cmap_index;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _ttf_cmap_subtable_ {
	uint16_t platformId;
	uint16_t platformSpecificId;
	uint32_t offset;
}ttf_cmap_subtable;
#pragma pack(pop)

#pragma pack(push,1) 
typedef struct _ttf_cmap_format12_ {
	uint16_t format;
	uint16_t reserved;
	uint32_t length;
	uint32_t language;
	uint32_t nGroups;
}ttf_cmap_format12;


typedef struct _ttf_group_table12_ {
	uint32_t startCharCode;
	uint32_t endCharCode;
	uint32_t startGlyphCode;
}ttf_group_table12;

#pragma pack(pop)

#pragma pack(push,1)


extern ttf_font * ttf_load (unsigned char *data);
extern int tt_draw_string(ttf_font * font, int x, int y, const char * s, uint32_t color);
#endif