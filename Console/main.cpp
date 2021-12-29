///! Copyright (C) Manas Kamal Choudhury 2021
///!
///! main.cpp -- AuTaskbar Program
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================
#include <QuBase.h>
#include <QuWindow.h>
#include <string.h>
#include <sys\_sleep.h>
#include <sys\_process.h>
#include <sys\_wait.h>
#include <sys\_thread.h>
#include <sys\_term.h>
#include <sys\_file.h>
#include <sys\_xeneva.h>
#include <sys\_kybrd.h>
#include <sys\mmap.h>
#include <sys\ioquery.h>
#include <canvas.h>
#include <acrylic.h>
#include <color.h>
#include <QuPanel.h>
#include <psf\psf.h>
#include <QuButton.h>
#include <sys\_ipc.h>
#include <sys\_time.h>
#include <QuTerminal.h>
#include <sys\_exit.h>
#include "console.h"
#include <QuIcon.h>
#include <QuScrollbar.h>
#include <stdlib.h>
#include <sys\postbox.h>
#include <font.h>
#include <ft2build.h>
#include  FT_FREETYPE_H

int timer_id = 0;
int master_fd, slave_fd;
bool focus_lost = false;


void QuActions (QuMessage *msg) {
	if (msg->type == QU_CANVAS_MOVE) {
		QuWindowMove(QuGetWindow(),msg->dword, msg->dword2);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_FOCUS_LOST) {
		focus_lost = true;
		sys_pause_timer (timer_id);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_FOCUS_GAIN) {
		sys_start_timer(timer_id);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_DESTROYED) {
		canvas_close(QuGetWindow()->ctx);
		exit(0);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_MOUSE_MOVE) {
		QuWindowHandleMouse(msg->dword, msg->dword2, msg->dword3);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_KEY_PRESSED) {
		if (msg->dword == KEY_N) 
			create_process("/dock.exe","dwm33");
		QuWindowHandleKey(msg->dword);
		memset(msg, 0, sizeof(QuMessage));
	}
	
	//QuPanelContentUpdate(QuGetWindow()->x, QuGetWindow()->y, QuGetWindow()->w, QuGetWindow()->h);

}


void PrintString (QuTerminal *text, char* string) {
	while(*string)
		QuTermPrint(text,*(string)++,WHITE);
}

bool blinked = false;
void blink_cursor () {
	if (!blinked) {
		acrylic_draw_rect_filled(QuGetWindow()->ctx, 1,23,10,15,SILVER);
		blinked = true;
	}else {
		acrylic_draw_rect_filled(QuGetWindow()->ctx, 1,23,10,15,BLACK);
		blinked = false;
	}

	QuPanelUpdate(QuGetWindow(),0,0,QuGetWindow()->w,QuGetWindow()->h,true);
}


int main (int argc, char* argv[]) {
	QuWindow* win = QuCreateWindow(300,300,500,500,"Console");
	QuSetRootWindow (win);

	canvas_t *canvas = canvas_initialize(win->w, win->h);
	win->ctx = canvas;
	QuWindowShowControls(win);

	QuWindowSetIcon(SYSTEM_ICON_CONSOLE);
	
	//! map a memory section for text 

	QuTerminal *term = QuCreateTerminal(0,0,win->w, win->h);
	QuWindowAdd(win,(QuWidget*)term);

	QuWindowShow(win);

	acrylic_font_set_size(32);
	acrylic_font_draw_string(win->ctx, "Console v1.0",10, win->h / 2 - strlen("Console")/2,32,SILVER);
	acrylic_font_set_size(18);
	acrylic_font_draw_string(win->ctx, "Copyright (C) Manas Kamal Choudhury",10,win->h / 2 + 25,32,GRAY);
	QuPanelUpdate(win,0,0,win->w, win->h, true);

	sys_ttype_create (&master_fd, &slave_fd);

	unsigned char* buffer = (unsigned char*)malloc(4096);
	memset (buffer, 0, 4096);

	/*timer_id = sys_create_timer (1000, get_current_pid());
	sys_start_timer(timer_id);*/

	int child_id = create_process("/dock.exe", "dock");
	//sys_ttype_dup(child_id, master_fd);

	UFILE slave;
	slave.size = 4096;
	slave.flags = 0;

	QuMessage qmsg;
	uint16_t app_id = QuGetAppId();
	postmsg_t msg;
	while(1) { 
	/*	post_box_receive_msg(&msg);
		if (msg.type == SYSTEM_MESSAGE_TIMER_EVENT) {
			blink_cursor();
			memset(&msg, 0, sizeof(postmsg_t));
		}*/

		QuChannelGet(&qmsg);
		if (qmsg.to_id == app_id)
			QuActions(&qmsg);

		sys_read_file (slave_fd,buffer,&slave);

	    for (int i = 0; i < 4096; i++) {
			if (buffer[i] != 0) {
				QuTermPrint(term,buffer[i],WHITE);
				QuTermFlush(term, win);
				QuPanelUpdate(win,0,0,win->w, win->h, true);
				if (buffer[i] == '\n') {
					memset(buffer, 0, 4096);
					break;
				}
			}
		}

		sys_read_file(slave_fd, buffer, &slave);
		if (buffer[0] == 0) {
			sys_wait();
		}
	}	
	return 1;
}
		