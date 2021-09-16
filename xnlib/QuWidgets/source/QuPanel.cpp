///! Copyright (C) Manas Kamal Choudhury 2021
///! 
///! QuPanel -- Main Client Area where GUI Object sits
///!
///! /PROJECT - Aurora's Xeneva
///! /AUTHOR  - Manas Kamal Choudhury
///!
///!====================================================

#include <QuPanel.h>
#include <stdlib.h>
#include <QuWindow.h>
#include <QuRect.h>
#include <canvas.h>
#include <QuBase.h>
#include <sys\_ipc.h>
#include <sys\_process.h>



QuPanel* QuCreatePanel () {
	QuPanel* panel = (QuPanel*)malloc(sizeof(QuPanel));
	panel->x = QuGetWindow()->x;
	panel->y = QuGetWindow()->y;
	panel->w = QuGetWindow()->w;
	panel->h = QuGetWindow()->h;
	panel->panel_data = (uint32_t*)0x0000600000000000;
	return panel;
}


void QuPanelUpdate(unsigned x, unsigned y, unsigned w, unsigned h) {
	uint32_t* lfb = (uint32_t*)QuGetWindow()->canvas;
	uint32_t* dbl_canvas = (uint32_t*)0x0000600000000000;
	int width = canvas_get_width();
	int height = canvas_get_height();
	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = dbl_canvas[(x + i) + (y + j) * width];
			lfb[(x + i) + (y + j) * width] = color;
		}
	}

	/*QuMessage msg;
	msg.type = QU_CODE_DIRTY_UPDATE;
	msg.dword = x;
	msg.dword2 = y;
	msg.dword3 = w;
	msg.dword4 = h;
	QuChannelPut(&msg, 2);*/
	message_t msg;
	msg.type = QU_CODE_DIRTY_UPDATE;
	msg.dword = x;
	msg.dword2 = y;
	msg.dword3 = w;
	msg.dword4 = h;
	msg.dword5 = get_current_pid();
	message_send(2, &msg);
}