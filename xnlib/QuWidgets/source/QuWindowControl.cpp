///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!  
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================

#include <QuWindowControl.h>
#include <color.h>
#include <sys\_sleep.h>
#include <string.h>


void QuMinimizeButtonDraw (QuWinControl *control, QuWindow *win, bool clicked) {
	if (!control->hover){
		//acrylic_draw_filled_circle(control->x, control->y, 6, ORANGE);
	//	QuPanelUpdate(control->x, control->y, control->w, control->h);
		acrylic_draw_horizontal_line (control->x, control->y + (control->h /2), 11,WHITE);
		acrylic_draw_horizontal_line (control->x, control->y + (control->h /2) + 1, 11, WHITE);
		if (control->restore){
		    QuPanelUpdate(control->x, control->y, control->w, control->h,true);
			control->restore = false;
		}
	}

	if (control->hover) {
		//acrylic_draw_filled_circle(control->x, control->y, 6, DARKORANGE);
		acrylic_draw_horizontal_line (control->x, control->y + (control->h /2), 11,GRAY);
		acrylic_draw_horizontal_line (control->x, control->y + (control->h /2) + 1, 11, GRAY);
		QuPanelUpdate(control->x, control->y, control->w, control->h, true);
		control->hover = false;
		control->restore = true;
	}

	if (clicked) {
	}
}


void QuMaximizeButtonDraw (QuWinControl *control, QuWindow *win, bool clicked) {
	if (!control->hover) {
		//acrylic_draw_filled_circle(control->x, control->y, 6, PALEGREEN);
		acrylic_draw_rect_unfilled(control->x, control->y + (control->h / 2) - (12/2), control->w, 12, WHITE);
		if (control->restore){
		    QuPanelUpdate(control->x, control->y, control->w, control->h, true);
			control->restore = false;
		}
	}

	if (control->hover) {
		//acrylic_draw_filled_circle(control->x, control->y, 6, DARKGREEN);
		acrylic_draw_rect_unfilled(control->x, control->y + (control->h / 2) - (12/2), control->w, 12, GRAY);
		QuPanelUpdate(control->x, control->y, control->w, control->h, true);
		control->hover = false;
		control->restore = true;
	}
	if (clicked) {
		
	}
}


void QuCloseButtonDraw (QuWinControl *control, QuWindow *win, bool clicked) {
	if (!control->hover) {
		//acrylic_draw_rect_filled(control->x, control->y, control->w, control->h, RED)
		acrylic_draw_arr_string(control->x, control->y + (control->h/2) - (12/2), "X",WHITE);
		if (control->restore){
		    QuPanelUpdate(control->x, control->y, control->w, control->h, true);
			control->restore = false;
		}
	}

	if (control->hover) {
		//acrylic_draw_filled_circle(control->x, control->y, 6, DARKRED);
		//acrylic_draw_rect_filled(control->x, control->y, control->w, control->h,DARKRED);
		acrylic_draw_arr_string(control->x, control->y + (control->h/2) - (12/2), "X", DARKORANGE);
		QuPanelUpdate(control->x, control->y, control->w, control->h, true);
		control->hover = false;
		control->restore = true;
	}

	if (clicked) {
		
		if (control->type == QU_WIN_CONTROL_CLOSE) {
			QuMessage msg;
			msg.type = QU_CODE_WIN_CLOSE;
			QuChannelPut(&msg, 2);
			memset(&msg, 0, sizeof(QuMessage));
			if (control->ControlEvent)
				control->ControlEvent(control, win, clicked);
			
		}
		
	}
}
