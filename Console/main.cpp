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
#include <sys\mmap.h>
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
#include <QuScrollbar.h>


void QuActions (QuMessage *msg) {
	if (msg->type == QU_CANVAS_MOVE) {
		QuWindowMove(QuGetWindow(),msg->dword, msg->dword2);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_RESIZE) {
		QuWindowSetBound(QuWindowGetWidth() + 20, QuWindowGetHeight() + 20);
		//acrylic_draw_rect_filled(QuGetCanvas(),msg->dword, msg->dword2, QuGetWindow()->w, QuGetWindow()->h, BLUE);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_DESTROYED) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_REPAINT) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_MOUSE_MOVE) {
		QuWindowHandleMouse(msg->dword, msg->dword2, msg->dword3);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_KEY_PRESSED) {
		QuWindowHandleKey(msg->dword);
		memset(msg, 0, sizeof(QuMessage));
	}
	
	//QuPanelContentUpdate(QuGetWindow()->x, QuGetWindow()->y, QuGetWindow()->w, QuGetWindow()->h);

}


void WindowClosed (QuWinControl *control, QuWindow *win, bool bit) {
	exit(0);
}


void PrintString (QuTerminal *text, char* string) {
	while(*string)
		QuTermPrint(text,*(string)++,WHITE);
}

int main (int argc, char* argv[]) {

	QuWindow* win = QuCreateWindow(100,100,500,500,"Hello");
	QuSetRootWindow (win);
	canvas_t *canvas = canvas_initialize(win->w, win->h);
	win->ctx = canvas;
	QuWindowShowControls(win);
	QuWindowAddControlEvent(QU_WIN_CONTROL_CLOSE, WindowClosed);

	///! map a memory section for text 

	QuTerminal *term = QuCreateTerminal(0,0,win->w, win->h);
	QuWindowAdd(win,(QuWidget*)term);	

	QuWindowShow(win);

	//int master_fd, slave_fd;
	//sys_ttype_create (&master_fd, &slave_fd);
	//unsigned char* buf = (unsigned char*)malloc(32);
	//memset(buf,'M',32);
	//sys_write_file (master_fd, buf,NULL);

	//message_t msg;
	//unsigned char* buffer = (unsigned char*)malloc(32);
	//memset (buffer, 0, 32);

	//QuPanelUpdate (0,0,win->w, win->h,true);

	QuMessage qmsg;
	uint16_t app_id = QuGetAppId();
	while(1) {
        QuChannelGet(&qmsg);
		if (qmsg.to_id == app_id)
			QuActions(&qmsg);

	//	sys_read_file (slave_fd,buffer,NULL);

	   /* for (int i = 0; i < 32; i++) {
			if (buffer[i] != 0) {
				QuTermPrint(term,buffer[i],WHITE);
				QuTermFlush(term, win);
			}
		}
	*/
		//	//
		//}

		
		sys_wait();
	}	
	return 1;
}
		
