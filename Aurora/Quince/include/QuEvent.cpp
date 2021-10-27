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
#include <QuCanvas\QuScreenRectList.h>
#include <QuRect.h>
#include <canvas.h>
#include <color.h>
#include <sys\_sleep.h>
#include <acrylic.h>


int x = 0;
int y = 20;
bool mouse_down = false;
const int ticks_per_second = 8;
const int skip_ticks = 1000 / ticks_per_second;
const int max_frame_skip = 10;
static int _mouse_code_ = 0;
static bool render_disable = false;
static int mouse_x, mouse_y = 0;
static int win_info_counter = 0;


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
		QuChannelGet (&q_msg);
	


		sys_get_current_time(&time);
		frame_time = sys_get_system_tick();
		diff_time = frame_time - next_tick;


		/**
		 *  Mouse Move message handle
		 */
		if (m_pack.type == _MOUSE_MOVE) {
			QuCursorNewCoord(m_pack.dword, m_pack.dword2);
			mouse_x = m_pack.dword;
			mouse_y = m_pack.dword2;
			QuMoveCursor(mouse_x, mouse_y);
			canvas_screen_update (m_pack.dword,m_pack.dword2, 24, 24);
			

			_mouse_code_ = 0;
			mouse_down = false;
			//! Mouse Clicked Bit
			if (m_pack.dword4 & 0x01) {
				mouse_down = true;
				_mouse_code_ = QU_CANVAS_MOUSE_LCLICKED;
			}

            QuWindowMngr_HandleMouse(m_pack.dword, m_pack.dword2, mouse_down, _mouse_code_);	

	
			//! Mouse Released Bit
			if (QuWindowMngrGetFocused() != NULL) {
				QuWindowMngr_SendEvent (QuWindowMngrGetFocused(), QU_CANVAS_MOUSE_MOVE,m_pack.dword, m_pack.dword2,_mouse_code_);
				
			}

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
		if (q_msg.type == QU_CODE_WIN_CREATE) {

			////!Stop the mouse
			render_disable = true;
			uint16_t dest_id = q_msg.from_id; 
			uint32_t* canvas = QuCanvasCreate(dest_id);
			QuWindow * window = QuWindowCreate(x,y,dest_id, canvas);


			uint64_t info_location = QU_WIN_INFO_START + win_info_counter * 4096;
			map_shared_memory (dest_id,info_location ,8192);
			window->win_info_location = (uint32_t*)info_location;
			win_info_counter++;

			//QuCanvasCommit(canvas, dest_id, window->x, window->y, window->width, window->height);
			QuMessage msg;
			msg.type = QU_CANVAS_READY;
			msg.from_id = get_current_pid();
			msg.to_id = dest_id;
			msg.p_value = canvas;
			msg.dword = x;
			msg.dword2 = y;
			msg.dword3 = 500;
			msg.dword4 = 500;
			msg.p_value2 = window->win_info_location;
			QuChannelPut(&msg, dest_id);

			QuWindowSetCanvas (window, canvas);

			QuScreenRectAdd(window->x, window->y, window->width, window->height);
			//QuCanvasSetUpdateBit(true);

			x += 30;
			y += 30;
			memset (&q_msg, 0, sizeof(QuMessage));
			render_disable = false;
		}

		//! Set Window Configuration
		//! for specific window
		if (q_msg.type == QU_CODE_WIN_CONFIG) {
			uint16_t from_id = q_msg.from_id;
			QuWindow* win = (QuWindow*)QuWindowMngrFindByID(from_id);
			if (q_msg.dword == QU_WIN_SET_SIZE) {
				QuWindowSetSize (win,q_msg.dword2,q_msg.dword3);
			}

			if (q_msg.dword == QU_WIN_SET_POS) {
				win->x = q_msg.dword2;
				win->y = q_msg.dword3;
			}

			if (q_msg.dword == QU_WIN_NON_DRAGGABLE) {
				win->attr = QU_WIN_NON_DRAGGABLE;
			}

			memset (&q_msg, 0, sizeof(QuMessage));
		}


		if (q_msg.type == QU_CODE_WIN_CLOSE) {
			uint16_t from_id = q_msg.from_id;
			QuWindow* win = (QuWindow*)QuWindowMngrFindByID(from_id);
			sys_unmap_sh_mem(from_id, (uint64_t)win->win_info_location, 8192);	
			win_info_counter--;
			win->mark_for_close = true;
			QuCanvasSetUpdateBit(true);
			memset (&q_msg, 0, sizeof(QuMessage));
		}


	
		//*==========================================================================
		//*==========================================================================
		if (diff_time > 15){	
			
			QuRenderTime(time.seconds, time.minutes, time.hour);
			next_tick = sys_get_system_tick();
			frame_time = 0;
		}
		QuWindowMngr_DrawAll();	

		QuScreenRectUpdate();
		//}
		//! Here We Prepare the frame that will be displayed
		sys_sleep(16);
	}
}