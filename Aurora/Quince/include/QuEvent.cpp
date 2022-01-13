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
#include <sys\_xeneva.h>
#include <font.h>
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
#include <QuWidget\QuDock.h>
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
bool alt_modifier = false;

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
	int fd = 0;
	//! Just play the startup sound
	//int snd_fd = sys_open_file ("/dev/snd", NULL);
	//ioquery(snd_fd,12,NULL);
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
			if (msg.dword == KEY_A) {
				create_process ("/dwm3.exe", "hello");
			}


			if (msg.dword == KEY_D) {
				create_process ("/dwm2.exe", "snake");
			}
		
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
			int winx = q_msg.dword;
			int winy = q_msg.dword2;
			int winw = q_msg.dword3;
			int winh = q_msg.dword4;

			//!Stop the mouse
			uint16_t dest_id = q_msg.from_id; 
			uint32_t* canvas = QuCanvasCreate(dest_id, winw, winh);
			QuWindow * window = QuWindowCreate(0,0,dest_id,canvas);
			window->width = winw;
			window->height = winh;

			uint64_t info_location = QU_WIN_INFO_START + win_info_counter * 4096;
			map_shared_memory (dest_id,info_location ,8192);
			window->win_info_location = (uint32_t*)info_location;
			QuWindowInfo *info = (QuWindowInfo*)window->win_info_location;
			info->x = winx;
			info->y = winy;
			win_info_counter++;

				
			QuMessage msg;
			msg.type = QU_CANVAS_READY;
			msg.from_id = get_current_pid();
			msg.to_id = dest_id;
			msg.p_value = canvas;
			msg.dword = window->id;
			msg.p_value2 = window->win_info_location;
			QuChannelPut(&msg, dest_id);

			QuWindowSetCanvas (window, canvas);

			QuScreenRectAdd(info->x, info->y, window->width, window->height);
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

			if (q_msg.dword == QU_WIN_SET_ICON) {
				QuDockEntry *dock = (QuDockEntry*)malloc(sizeof(QuDockEntry));
				if(q_msg.dword2 == SYSTEM_ICON_CONSOLE)
					dock->icon_path = "/cnsl.bmp";
				else if (q_msg.dword2 == SYSTEM_ICON_APPLICATION)
					dock->icon_path = "/app.bmp";

				dock->title = "app0/";  //TODO:Get the Window title
				win->dock = dock;
				QuDockAdd(dock);
				QuDockRepaint();
			}

			if (q_msg.dword == QU_WIN_NON_DRAGGABLE) {
				win->attr = QU_WIN_NON_DRAGGABLE;
			}

			memset (&q_msg, 0, sizeof(QuMessage));
		}

		if (q_msg.type == QU_CODE_WIN_CLOSE) {
			uint16_t from_id = q_msg.from_id;
			QuWindow* win = (QuWindow*)QuWindowMngrFindByID(from_id);
			//win_info_counter--;
			win->mark_for_close = true;
			memset (&q_msg, 0, sizeof(QuMessage));
		}

		if (q_msg.type == QU_CODE_WIN_MAXIMIZE) {
			memset (&q_msg,0, sizeof(QuMessage));
		}

		
		QuCursorFixDamage(mouse_x, mouse_y);
		//*==========================================================================
		//*==========================================================================
	
		QuWindowMngr_DrawAll();
	
        QuRenderTime(time.seconds, time.minutes, time.hour);
		//QuRamWidget();
       
		QuUpdateCursor (mouse_x, mouse_y);
		
		QuScreenRectUpdate();
		
		//}
		//! Here We Prepare the frame that will be displayed
		sys_sleep(16);
	}
}