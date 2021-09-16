///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuCanvasMngr.h -- Quince Canvas Manager
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///! ==========================================

#ifndef __QU_CANVAS_MNGR_H__
#define __QU_CANVAS_MNGR_H__

#include <stdint.h>
#include <QuRect.h>

//! QuCanvasMngr_Initialize -- Initialize the QuCanvasMngr
//! @oaram null -- No parameters
extern void QuCanvasMngr_Initialize();

//! QuCanvasCreate--- Creates a canvas for the destination
//!                   process
//!
//! @param dest_pid -- Destination process id
extern uint32_t* QuCanvasCreate (uint16_t dest_pid);

//! QuCanvasCommit -- Commits the canvas to the process
//! @param canvas -- The Canvas Address
//! @param destid -- Destination process id
extern void QuCanvasCommit (uint32_t* canvas, uint16_t destid, unsigned x, unsigned y, unsigned w, unsigned h);

//! QuCanvasBlit -- Copy pixels from another buffer to Quince Internal Buffer
//! @param canvas - External Buffer
//! @param x - X coord
//! @param y - Y coord
//! @param w - Width
//! @param h - Height
extern void QuCanvasBlit (uint32_t *canvas, unsigned x, unsigned y, unsigned w, unsigned h);

//! QuCanvasPutPixel -- Puts pixel on specific canvas
//! @param canvas -- Canvas Address
//! @param x -- X Coord
//! @param y -- Y Coord
//! @param color - Color 24 bit 
extern void QuCanvasPutPixel (uint32_t *canvas, unsigned x, unsigned y, uint32_t color);

//! QuCanvasAddDirty -- Add Dirty Areas to be updated by canvas manager
//! @param r -- Dirty Rectangle
extern void QuCanvasAddDirty (QuRect *r);

//! QuCanvasUpdate -- Update the dirty areas by background filled pixels
//! @param x -- X coord
//! @param y -- Y coord
//! @param w -- Width 
//! @param h -- Height
extern void QuCanvasUpdate (unsigned x, unsigned y, unsigned w, unsigned h);

//! QuCanvasUpdateDirty -- Update the dirty areas by iterating dirty rectangles
//! @param -- Null
extern void QuCanvasUpdateDirty();
#endif