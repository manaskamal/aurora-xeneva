///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuWallpaper.h -- Quince Wallpaper Manager
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///! =================================================

#ifndef __QU_WALLPAPER_H__
#define __QU_WALLPAPER_H__

#include <stdint.h>
#include <sys\mmap.h>
#include <sys\_file.h>
#include <image.h>

typedef struct _QuWallpaper_ {
	unsigned char* buffer;
	unsigned w;
	unsigned h;
}QuWallpaper;

//! QuWallpaperInit --> Initialize and Loads the wallpaper
//!
//! @param filename -- Path of the wallpaper
extern Image* QuWallpaperInit (const char* filename);

//! QuWallpaperDraw --> Draw the wallpaper to its 
//! internal buffer
//! @param image --> Pointer to the Image instance in memory
extern void QuWallpaperDraw (Image *image);

//! Present the wallpaper onto the screen
//! @param = none
extern void QuWallpaperPresent ();

#endif