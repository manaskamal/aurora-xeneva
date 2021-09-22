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

extern void ttf_load (unsigned char *data);
#endif