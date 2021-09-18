///!  
///!  Copyright (C) Manas Kamal Choudhury 2021
///! 
///!  QuEventLoop -- Quince Event Loop
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury 
///!
///! =================================================

#include <QuEvent.h>
#include <sys\_ipc.h>
#include <sys\_term.h>
#include <sys\_wait.h>
#include <sys\_exit.h>
#include <stdlib.h>

//! Quince Library
#include <ipc\_ipc_mouse.h>
#include <ipc\QuChannel.h>
#include <string.h>
#include <QuCursor.h>
#include <QuCode.h>
#include <QuCanvas\QuCanvasMngr.h>
#include <QuWindow\QuWindow.h>
#include <QuWindow\QuWindowMngr.h>
#include <QuRect.h>
#include <canvas.h>
#include <color.h>
#include <sys\_sleep.h>


int x , y = 100;

void QuHandleQuinceMsg (QuMessage *qu_msg) {
	if (qu_msg->type == QU_CODE_WIN_CREATE) {
		uint16_t dest_id = qu_msg->from_id;
		uint32_t* canvas = QuCanvasCreate(dest_id);
		memset (qu_msg, 0, sizeof(QuMessage));
		for (int i = 0; i < canvas_get_width(); i++)
			for (int j = 0; j < canvas_get_height(); j++)
				QuCanvasPutPixel (canvas, 0 + i, 0 + j, WHITE);
		
		QuWindow * window = QuWindowCreate(x,y,dest_id);
		QuWindowSetCanvas (window, canvas);
		QuRect *r = (QuRect*)malloc(sizeof(QuRect));
		r->x = window->x;
		r->y = window->y;
		r->w = window->width;
		r->h = window->height;
		QuWindowAddDirtyArea(window, r);
		QuCanvasCommit(canvas, dest_id, window->x, window->y, window->width, window->height);
		x += 100;
		y += 100;
	}

	if (qu_msg->type == QU_CODE_DIRTY_UPDATE) {
		QuRect *r = (QuRect*)malloc(sizeof(QuRect));
		r->x = qu_msg->dword;
		r->y = qu_msg->dword2;
		r->w = qu_msg->dword3;
		r->h = qu_msg->dword4;
		QuWindow* win = (QuWindow*)QuWindowMngrFindByID(qu_msg->from_id);
		QuWindowAddDirtyArea(win,r);
		memset(qu_msg, 0, sizeof(QuMessage));
	}
}

//! Event Loop
void QuEventLoop() {
	message_t msg;
	mouse_message_t m_pack;
	QuMessage qu_msg;
	while(1) {
		message_receive(&msg);
		_ipc_mouse_dispatch (&m_pack);
		

		//!System Messages
		if (m_pack.type == _MOUSE_MOVE) {
			QuMoveCursor(m_pack.dword, m_pack.dword2);
			canvas_screen_update (QuCursorGetNewX(), QuCursorGetNewY(), 24, 24);
			QuCursorNewCoord(m_pack.dword, m_pack.dword2);

			QuWindow * focus_win = QuWindowMngrGetFocused();
			//! Mouse Clicked Bit
			if (m_pack.dword4 & 0x01) {
				QuWindowMngr_HandleMouseDown(m_pack.dword, m_pack.dword2);
			}

			//! Mouse Released Bit
			if (m_pack.dword4 & 0x5) {
				QuWindowMngr_HandleMouseUp (m_pack.dword, m_pack.dword2);
			}

			memset (&m_pack, 0, sizeof(mouse_message_t));
		}
		if (msg.type == 3) {
			//sys_print_text ("Quince: Key Pressed\n");
			memset(&msg, 0, sizeof(message_t));
		}

		if (msg.type == QU_CODE_WIN_CREATE) {
			uint16_t dest_id = msg.dword;
			uint32_t* canvas = QuCanvasCreate(dest_id);
		
			QuWindow * window = QuWindowCreate(x,y,dest_id);
			QuCanvasCommit(canvas, dest_id, window->x, window->y, window->width, window->height);
			QuWindowSetCanvas (window, canvas);
			QuRect *r = (QuRect*)malloc(sizeof(QuRect));
			r->x = window->x;
			r->y = window->y;
			r->w = window->width;
			r->h = window->height;
			QuWindowAddDirtyArea(window, r);
			
			x += 200;
			y += 200;
			memset (&msg, 0, sizeof(message_t));
		}
		if (msg.type == QU_CODE_DIRTY_UPDATE) {
			QuRect *r = (QuRect*)malloc(sizeof(QuRect));
			r->x = msg.dword;
			r->y = msg.dword2;
			r->w = msg.dword3;
			r->h = msg.dword4;
			uint16_t from_id = msg.dword5;
			QuWindow* win = (QuWindow*)QuWindowMngrFindByID(from_id);
			QuWindowAddDirtyArea(win,r);
			memset(&msg, 0, sizeof(message_t));
		}

		
		QuWindowMngr_DrawAll();	
		/*if (QuCanvasGetUpdateBit()) {
			canvas_screen_update(0,0,canvas_get_width(), canvas_get_height());
			QuCanvasSetUpdateBit(false);
		}*/
		sys_sleep(25);
	
	}
}