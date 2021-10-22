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
#include <QuWindow\QuWindow.h>

//! QuCanvasMngr_Initialize -- Initialize the QuCanvasMngr
//! @oaram null -- No parameters
extern void QuCanvasMngr_Initialize();

//! QuCanvasCreate--- Creates a canvas for the destination
//!                   process
//!
//! @param dest_pid -- Destination process id
extern uint32_t* QuCanvasCreate (uint16_t dest_pid);


//! QuCanvasBlit -- Copy pixels from another buffer to Quince Internal Buffer
//! @param canvas - External Buffer
//! @param x - X coord
//! @param y - Y coord
//! @param w - Width
//! @param h - Height
extern void QuCanvasBlit (QuWindow* win,uint32_t *canvas, unsigned x, unsigned y, unsigned w, unsigned h);

//! QuCanvasPutPixel -- Puts pixel on specific canvas
//! @param canvas -- Canvas Address
//! @param x -- X Coord
//! @param y -- Y Coord
//! @param color - Color 24 bit 
extern void QuCanvasPutPixel (uint32_t *canvas, unsigned x, unsigned y, uint32_t color);

//! QuCanvasGetPixel -- Get Pixel from specific canvas
//! @param canvas -- Canvas Address
//! @param x -- X coordination
//! @param y -- Y Coordination
extern uint32_t QuCanvasGetPixel (uint32_t *canvas, unsigned x, unsigned y);

//! QuCanvasAddDirty -- Add Dirty Areas to be updated by canvas manager
//! @param r -- Dirty Rectangle
extern void QuCanvasAddDirty (int x, int y, int w, int h);

//! QuCanvasUpdate -- Update the dirty areas by background filled pixels
//! @param x -- X coord
//! @param y -- Y coord
//! @param w -- Width 
//! @param h -- Height
extern void QuCanvasUpdate (unsigned x, unsigned y, unsigned w, unsigned h);

//! QuCanvasUpdateDirty -- Update the dirty areas by iterating dirty rectangles
//! @param -- Null
extern void QuCanvasUpdateDirty();

//! QuCanvasSetUpdateBit -- Set the update for Screen update
//! @param value -- boolean value
extern void QuCanvasSetUpdateBit(bool value);

//! QuCanvasGetUpdateBit -- Checks the update bit
extern bool QuCanvasGetUpdateBit();

extern void QuCanvasCopyToFB(unsigned x, unsigned y, unsigned w, unsigned h);

extern void QuCanvasQuery(unsigned x, unsigned y, unsigned w, unsigned h);

extern void QuCanvasQuickPaint (uint32_t* canvas,int x, int y, int w,int h);

extern void QuCanvasUpdateDirtyFB();

extern  void QuRenderTime (uint8_t sec, uint8_t min, uint8_t hr);

extern void QuCanvasRelease (uint16_t dest_pid, QuWindow *win);


#endif