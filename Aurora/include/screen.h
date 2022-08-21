/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  screen.h -- Screen Interface for Aurora
 *
 *  Screen Interface manages every graphics devices registered to the
 *  system, it can be simple VESA, GOP or other hardware accelerated
 *  graphics card. Screen interface maps the framebuffer to specific
 *  virtual address and provides interfaces for application to draw 
 *  pixel
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==============================================
 */


#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <_xnboot.h>
#include <stdint.h>
#include <stdio.h>
#include <aurora.h>

//! Standard codes for screen driver features
#define SCREEN_SETMODE     0x100
#define SCREEN_GETWIDTH    0x101
#define SCREEN_GETHEIGHT   0x102
#define SCREEN_GETBPP      0x103
#define SCREEN_SETBPP      0x104
#define SCREEN_UPDATE      0x105
#define SCREEN_MOVE_CURSOR  0x106
#define SCREEN_GET_SCANLINE 0x107
#define SCREEN_GET_PITCH    0x108


//! Display structure
typedef struct __display__ {
	uint32_t width;
	uint32_t height;
	uint32_t *buffer;
	uint32_t bpp;
	uint16_t scanline;
	uint32_t size;
	uint32_t pitch;
}display_t;

//!Simple Display Interface for User mode applications

/**
 * AuInitializeScreen -- initialize the screen
 * @param info -- the boot information pointer passed by xnldr
 */
extern void AuInitializeScreen (KERNEL_BOOT_INFO *info);

/**
 * AuScreenMap -- simply set the mode of the screen
 * and map the virtual address space to be used
 * @param width -- mode width
 * @param height -- mode height
 */
extern void AuScreenMap (uint32_t width, uint32_t height);

/**
 * AuGetScreenWidth  -- returns the current width of the screen
 * @return -- width of the screen
 */
AU_EXTERN AU_EXPORT uint32_t  AuGetScreenWidth ();

/**
 * AuGetScreenHeight -- returns the current height of the screen
 * @return -- height of the screen
 */
AU_EXTERN AU_EXPORT uint32_t  AuGetScreenHeight ();

/**
 * AuGetFramebuffer -- returns the current framebuffer address of
 * the screen
 * @return -- framebuffer address
 */
AU_EXTERN AU_EXPORT uint32_t *AuGetFramebuffer();

/**
 * AuGetScreenBPP -- returns the current bits per pixel
 * @return -- bits/pixel of the screen
 */
AU_EXTERN AU_EXPORT uint32_t  AuGetScreenBPP();

/**
 * AuGetScreenScanline -- return the current pixles per line of the screen
 * @return -- scanline of the screen
 */
AU_EXTERN AU_EXPORT uint16_t AuGetScreenScanline();

/**
 * AuGetFramebufferSize -- returns the current framebuffer size of the screen in (bytes)
 * @return -- framebuffer size
 */
AU_EXTERN AU_EXPORT uint32_t AuGetFramebufferSize();

/**
 * AuDrawPixel -- low level pixel drawing interface
 * @param x -- x position of the pixel
 * @param y -- y position of the pixel
 * @param color -- color of the pixel
 */
AU_EXTERN AU_EXPORT void AuDrawPixel(unsigned x, unsigned y, uint32_t color);

#endif