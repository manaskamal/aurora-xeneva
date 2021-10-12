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
#include <canvas.h>
#include <acrylic.h>
#include <color.h>
#include <QuPanel.h>
#include <psf\psf.h>
#include <QuButton.h>
#include <sys\_ipc.h>
#include <sys\_time.h>

#include "taskbar.h"


void QuActions (QuMessage *msg) {
	if (msg->type == QU_CANVAS_MOVE) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_RESIZE) {
		QuWindowSetBound(QuWindowGetWidth() + 20, QuWindowGetHeight() + 20);
		acrylic_draw_rect_filled(msg->dword, msg->dword2, QuGetWindow()->w, QuGetWindow()->h, BLUE);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_DESTROYED) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_MOUSE_LCLICKED) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_MOUSE_LRELEASE) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_MOUSE_MOVE) {
		QuWindowHandleMouse(msg->dword, msg->dword2, msg->dword3);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_KEY_PRESSED) {
		memset(msg, 0, sizeof(QuMessage));
	}
	
	//QuPanelContentUpdate(QuGetWindow()->x, QuGetWindow()->y, QuGetWindow()->w, QuGetWindow()->h);

}

void GoClicked (QuWidget *wid, QuWindow *win) {
}

int main (int argc, char* argv[]) {
	QuRegisterApplication ("au_taskbar");
	QuWindow* win = QuGetWindow();
	QuWindowSetSize(canvas_get_width(), canvas_get_height());
	QuWindowSetPos(0,0);
	QuWindowSetProperty(NULL);
	
	start_taskbar();
	

	QuMessage qmsg;
	uint16_t app_id = QuGetAppId();
	message_t msg;
	while(1) {
		message_receive(&msg);

		
		if (msg.type == NEW_TASKBAR_BUTTON) {
			add_taskbar_button(msg.buffer);
			memset (&msg, 0, sizeof(message_t));
		}
		sys_wait();
	}	
	return 1;
}
		
