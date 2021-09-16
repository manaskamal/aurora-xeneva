///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!  
///!  QuCursor -- Quince Cursor
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==============================================

#ifndef __QU_CURSOR_H__
#define __QU_CURSOR_H__

#define QU_CURSOR_ARROW   100
#define QU_CURSOR_HAND    101
#define QU_CURSOR_MOVE    102


extern void QuCursorInit (unsigned x, unsigned y, int type);
extern void QuMoveCursor (unsigned x, unsigned y);
extern void QuCursorCoord (unsigned x, unsigned y);
extern unsigned QuCursorGetNewX();
extern unsigned QuCursorGetNewY();
#endif