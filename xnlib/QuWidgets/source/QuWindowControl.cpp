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
		info->maximize = true;
		win->maximized = true;
		win->oldx = info->x;
		win->oldy = info->y;
		win->oldw = win->w;
		win->oldh = win->h;
		win->w = win->ctx->width;
		win->h = win->ctx->height - 40;
		QuMessage msg;
		msg.type = QU_CODE_WIN_MAXIMIZE;
		QuChannelPut(&msg, 2);
		memset(&msg, 0, sizeof(QuMessage));*/
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
			if (control->ControlEvent)
				control->ControlEvent(control, win, clicked);


			QuMessage msg;
			msg.type = QU_CODE_WIN_CLOSE;
			QuChannelPut(&msg, 2);
			memset(&msg, 0, sizeof(QuMessage));
			
		}
		
	}
}

void QuMinimizeButtonRearrange (QuWinControl *ctrl, QuWindow *win) {
	ctrl->x = win->w - 43;
}

void QuMaximizeButtonRearrange (QuWinControl *ctrl, QuWindow* win) {
	ctrl->x = win->w - 28;
}

void QuCloseButtonRearrange (QuWinControl *ctrl, QuWindow* win) {
	ctrl->x = win->w - 13;
}
