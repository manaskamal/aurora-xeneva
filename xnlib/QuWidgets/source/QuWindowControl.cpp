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
		acrylic_draw_horizontal_line (win->ctx,control->x, control->y + (control->h /2), 11,WHITE);
		acrylic_draw_horizontal_line (win->ctx,control->x, control->y + (control->h /2) + 1, 11, WHITE);
		if (control->restore){
		    QuPanelUpdate(win,control->x, control->y, control->w, control->h,false);
			control->restore = false;
		}
	}

	if (control->hover) {
		//acrylic_draw_filled_circle(control->x, control->y, 6, DARKORANGE);
		acrylic_draw_horizontal_line (win->ctx,control->x, control->y + (control->h /2), 11,GRAY);
		acrylic_draw_horizontal_line (win->ctx,control->x, control->y + (control->h /2) + 1, 11, GRAY);
		QuPanelUpdate(win,control->x, control->y, control->w, control->h, false);
		control->hover = false;
		control->restore = true;
	}

	if (clicked) {
	}
}


void QuMaximizeButtonDraw (QuWinControl *control, QuWindow *win, bool clicked) {
	if (!control->hover) {
		//acrylic_draw_filled_circle(control->x, control->y, 6, PALEGREEN);
		acrylic_draw_rect_unfilled(win->ctx,control->x, control->y + (control->h / 2) - (12/2), control->w, 12, WHITE);
		if (control->restore){
		    QuPanelUpdate(win,control->x, control->y, control->w, control->h, false);
			control->restore = false;
		}
	}

	if (control->hover) {
		//acrylic_draw_filled_circle(control->x, control->y, 6, DARKGREEN);
		acrylic_draw_rect_unfilled(win->ctx,control->x, control->y + (control->h / 2) - (12/2), control->w, 12, GRAY);
		QuPanelUpdate(win,control->x, control->y, control->w, control->h, false);
		control->hover = false;
		control->restore = true;
	}
	if (clicked) {
		/*QuWinInfo *info = (QuWinInfo*)win->win_info_data;
		info->maximize = !info->maximize;
		win->oldx = win->x;
		win->oldy = win->y;
		win->oldw = win->w;
		win->oldh = win->h;
		win->x = 0;
		win->y = 0;
		win->w = canvas_get_width();
		win->h = canvas_get_height();*/
	}
}


void QuCloseButtonDraw (QuWinControl *control, QuWindow *win, bool clicked) {
	if (!control->hover) {
		//acrylic_draw_rect_filled(control->x, control->y, control->w, control->h, RED)
		acrylic_draw_arr_string(win->ctx,control->x, control->y + (control->h/2) - (12/2), "X",WHITE);
		if (control->restore){
		    QuPanelUpdate(win,control->x, control->y, control->w, control->h, false);
			control->restore = false;
		}
	}

	if (control->hover) {
		//acrylic_draw_filled_circle(control->x, control->y, 6, DARKRED);
		//acrylic_draw_rect_filled(control->x, control->y, control->w, control->h,DARKRED);
		acrylic_draw_arr_string(win->ctx,control->x, control->y + (control->h/2) - (12/2), "X", DARKORANGE);
		QuPanelUpdate(win,control->x, control->y, control->w, control->h, false);
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
