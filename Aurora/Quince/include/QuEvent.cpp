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
#include <sys\_time.h>
#include <sys\_kybrd.h>
#include <sys\_process.h>
#include <sys\ioquery.h>
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
#include <QuWidget\QuWallpaper.h>
#include <QuCanvas\QuScreenStack.h>
#include <QuRect.h>
#include <canvas.h>
#include <color.h>
#include <sys\_sleep.h>
#include <acrylic.h>


int x , y = 20;
bool mouse_down = false;
const int ticks_per_second = 8;
const int skip_ticks = 1000 / ticks_per_second;
const int max_frame_skip = 10;
static int _mouse_code_ = 0;

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
		x += 10;
		y += 10;
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
	QuMessage q_msg;
	sys_time time;
	uint32_t next_tick = 0; //sys_get_system_tick();
	uint32_t frame_time = 0;
	uint32_t diff_time = 0;
	int loops;
	char fps_str[60];

	while(1) {
		message_receive(&msg);
		_ipc_mouse_dispatch (&m_pack);
		QuChannelGet(&q_msg);
	


		sys_get_current_time(&time);
		frame_time = sys_get_system_tick();
		diff_time = frame_time - next_tick;


		/**
		 *  Mouse Move message handle
		 */
		if (m_pack.type == _MOUSE_MOVE) {
			//QuCursorNewCoord(m_pack.dword, m_pack.dword2);
			QuMoveCursor(m_pack.dword, m_pack.dword2);
			canvas_screen_update (m_pack.dword,m_pack.dword2, 24, 24);
			
			mouse_down = false;
			_mouse_code_ = 0;
			//! Mouse Clicked Bit
			if (m_pack.dword4 & 0x01) {
				mouse_down = true;
				_mouse_code_ = QU_CANVAS_MOUSE_LCLICKED;
			}

            QuWindowMngr_HandleMouse(m_pack.dword, m_pack.dword2, mouse_down);


			if (QuWindowMngrGetFocused() != NULL) {
				QuWindowMngr_SendEvent (QuWindowMngrGetFocused(), QU_CANVAS_MOUSE_MOVE,m_pack.dword, m_pack.dword2,_mouse_code_);
			}
			//! Mouse Released Bit
			if (m_pack.dword4 & 0x5) {
				QuWindowMngr_HandleMouseUp (m_pack.dword, m_pack.dword2);
				_mouse_code_ = QU_CANVAS_MOUSE_LRELEASE;
			}

			
			memset (&m_pack, 0, sizeof(mouse_message_t));
		}



		/**
		 * Handle Key Pressed Events!! 
		 * Quince sends the key event to currently focused window
		 */
		if (msg.type == 3) {
			//! Send the key event
			if (QuWindowMngrGetFocused() != NULL) {
				QuWindowMngr_SendEvent (QuWindowMngrGetFocused(), QU_CANVAS_KEY_PRESSED,NULL, NULL,msg.dword);
			}
			memset(&msg, 0, sizeof(message_t));
		}


		/** ===================================================================================
		 ** Quince Clients Messages
		 ** ===================================================================================
		 **/

		//! Create Window Request
		if (msg.type == QU_CODE_WIN_CREATE) {
			////!Stop the mouse
			ioquery (IO_QUERY_MOUSE, MOUSE_IOCODE_DISABLE,NULL);

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
			
			x += 30;
			y += 30;
			memset (&msg, 0, sizeof(message_t));

			ioquery (IO_QUERY_MOUSE, MOUSE_IOCODE_ENABLE,NULL);
		}


		//! Dirty Update Request
		if (msg.type == QU_CODE_DIRTY_UPDATE) {
			QuRect *r = (QuRect*)malloc(sizeof(QuRect));
			r->x = msg.dword;
			r->y = msg.dword2;
			r->w = msg.dword3;
			r->h = msg.dword4;
			uint16_t from_id = msg.dword5;
			QuWindow* win = (QuWindow*)QuWindowMngrFindByID(from_id);
			QuWindowAddDirtyArea(win,r);
			//memset(&msg, 0, sizeof(message_t));
			memset (&msg, 0, sizeof(message_t));
		}



		//! Set Window Configuration
		//! for specific window
		if (msg.type == QU_CODE_WIN_CONFIG) {
			uint16_t from_id = msg.dword5;
			QuWindow* win = (QuWindow*)QuWindowMngrFindByID(from_id);
			if (msg.dword == QU_WIN_CONFIG_AUTO_INVALIDATE){
				QuWindowSetAutoInvalidation(win, true);
			}
			if (msg.dword == QU_WIN_SET_SIZE) {
				QuWindowSetSize (win,msg.dword2,msg.dword3);
			}

			if (q_msg.dword == QU_WIN_AUTO_INVALIDATE_RGN) {
				QuRect *r = (QuRect*)malloc(sizeof(QuRect));
				r->x = msg.dword2; 
				r->y = msg.dword3;
				r->w = msg.dword4;
				r->h = msg.dword6;
				QuWindowAddDirtyArea (win, r);
				QuWindowSetAutoInvalidation(win,true);
			}

			memset (&msg, 0, sizeof(QuMessage));
		}




		//*==========================================================================
		//*==========================================================================

		//! Here We Prepare the frame that will be displayed
	
		if (diff_time > 15){
			QuWindowMngr_DrawAll();	
			QuWindowMngr_DisplayWindow();
			next_tick = sys_get_system_tick();
			frame_time = 0;
		}
	
	
		if (QuCanvasGetUpdateBit()) {
			canvas_screen_update(0,0,canvas_get_width(), canvas_get_height());
			QuCanvasSetUpdateBit(false);
		}


		sys_sleep(16);
	}
}