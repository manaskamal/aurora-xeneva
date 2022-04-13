

#include <daisy.h>
#include <daisy_priwm_window.h>
#include <daisy_window.h>
#include <daisy_widget_panel.h>
#include <daisy_widget_button.h>
#include <daisy_widget_label.h>
#include <daisy_widget_slider.h>
#include <daisy_widget_onoff.h>
#include <daisy_scroll_view.h>
#include <daisy_widget_scrollbar.h>
#include <daisy_widget_list.h>
#include <font.h>

#include <sys\_file.h>
#include <acrylic.h>
#include <sys\_ipc.h>
#include <sys\_time.h>
#include <sys\_xeneva.h>
#include <sys\_thread.h>
#include <sys\_process.h>
#include <sys\_wait.h>
#include <sys\_sleep.h>
#include <sys\mmap.h>
#include <string.h>
#include <color.h>
#include <sys\_term.h>
#include <sys\ioquery.h>

#include "dock_base.h"
#include "dock_button.h"

#define CLOCK_MESSAGE 10


void dock_paint_time (canvas_t *ctx,int x, int y,uint32_t hour, uint32_t min, uint32_t second) {
	acrylic_draw_rect_filled(ctx,x,y,78,30,0xFFBDB9B9);
	acrylic_draw_rect_unfilled(ctx,x,y,78,30,BLACK);

	char _sec[2];
	char _min[2];
	char _hour[2];
	memset (_sec, 0, 2);
	memset (_min, 0, 2);
	memset (_hour, 0, 2);

	if (hour > 12)
		hour = hour - 12;

	sztoa(second,_sec,10);
	sztoa(min,_min, 10);
	sztoa(hour,_hour, 10);

	//sys_print_text ("Hour -> %d, Min -> %d \r\n", hour,min);
	
	acrylic_draw_arr_string(ctx,x + strlen(_hour)*8/2 + 2,y + 16/2,_hour,BLACK);
	acrylic_draw_arr_string(ctx,x + strlen(_min)*8/2 + 2*8 + 1,y + 16/2,_min,BLACK);
	acrylic_draw_arr_string(ctx,x + strlen(_sec)*8/2 + 5*8  + 1, y + 16/2, _sec,BLACK);
}
/**
 * main entry point of the dock
 */
int main (int argc, char*argv[]) {
	daisy_application();

	sys_print_text ("initializing dock \r\n");

	int svga_fd = sys_open_file ("/dev/fb", NULL);
	uint32_t s_width = ioquery(svga_fd,SCREEN_GETWIDTH,NULL);
	uint32_t s_height = ioquery(svga_fd, SCREEN_GETHEIGHT, NULL);
	uint32_t bpp = ioquery(svga_fd, SCREEN_GETBPP, NULL);
	uint16_t scanline = ioquery(svga_fd, SCREEN_GET_SCANLINE, NULL);

	/**
	 * initialize internal variables 
	 */
	int _button_x_off_padding_ = 10;
	int _button_x_off_ = 0;


	daisy_window_t *win = daisy_window_create(0,s_height - 30,s_width,30,DAISY_WIN_UNMOVABLE, "Dock");
	win->paint = 0;
	daisy_win_info_t *info = daisy_get_window_info(win);
	
	/** create the main dockbar */
	dock_t *dock = dock_create_dock_base (win->ctx,0, info->height - 30,info->width, 30);
	dock->buttons_xoff = _button_x_off_;
	dock->buttons_padding = _button_x_off_padding_;
	
	dock_button_t *button = dock_create_button (dock->buttons_xoff + dock->buttons_padding,2,78,30,"Xeneva");
	dock_add_button (dock, button);
	dock->buttons_xoff += 78 + 10;

	/* paint the dock window */
	dock_repaint(dock);

	daisy_window_show(win);

	sys_print_text ("Dock running \r\n");

	create_process ("/lnch.exe", "lnch");

	dock_button_t *prev_focused_button = NULL;
	int pri_event_fd = daisy_get_event_fd();

	pri_event_t e;
	while(1) {
		ioquery (pri_event_fd,PRI_LOOP_GET_EVENT, &e);
		if (e.type == DAISY_NEW_WINDOW_INFO) {
				if(prev_focused_button) 
					prev_focused_button->focused = false;

				acrylic_font_set_size(12);
				char* title = (char*)malloc(100);
				memset(title, 0, 100);
				strcpy(title,e.char_values);
				int width = acrylic_font_get_length(title) + 20;
				dock_button_t *button = dock_create_button(dock->buttons_xoff + dock->buttons_padding,2,width,30,title);
				button->win_id = e.dword;
				button->focused = true;
				dock->buttons_xoff += width + 10;
				dock_add_button (dock, button);
				prev_focused_button = button;

				dock_repaint (dock);
				daisy_window_update_rect_area(win, 0, 0, info->width, 30);
				memset(&e, 0, sizeof(pri_event_t));
			}

			if (e.type == DAISY_CURSOR_MOVED) {
				int mouse_x = e.dword;
				int mouse_y = e.dword2;
				int button = e.dword3;

				bool _repaint_dock_ = false;
				if (button) {
					for (int i = 0; i < dock->dock_buttons->pointer; i++) {
						dock_button_t *buttons = (dock_button_t*)list_get_at(dock->dock_buttons, i);
						if (mouse_x >= buttons->x && mouse_x < (buttons->x + buttons->width)) {
							if (prev_focused_button == buttons) {
								_repaint_dock_ = false;
								break;
							}

							if (prev_focused_button)
								prev_focused_button->focused = false;
								buttons->focused = true;
								prev_focused_button = buttons;
								_repaint_dock_ = true;
								break;
						}
					}
				}

				if (_repaint_dock_) {
					dock_repaint(dock);
					daisy_window_update_rect_area(win, 0, 0, info->width, 30);
				}
				memset(&e, 0, sizeof(pri_event_t));
			}

			if (e.type == DAISY_NOTIFY_WIN_FOCUS_CHANGED) {
				bool _repaint_dock_ = false;

				for (int i = 0; i < dock->dock_buttons->pointer; i++) {
					dock_button_t *buttons = (dock_button_t*)list_get_at(dock->dock_buttons, i);
					if (buttons->win_id == e.dword) {
						if (prev_focused_button == buttons){
							break;
						}
						if (prev_focused_button)
							prev_focused_button->focused = false;
						buttons->focused = true;
						prev_focused_button = buttons;
						_repaint_dock_ = true;
						break;
					}
				}

				if (_repaint_dock_) {
					dock_repaint(dock);
					daisy_window_update_rect_area(win, 0, 0, info->width, 30);
				}

				memset(&e, 0, sizeof(pri_event_t));
			}


			if (e.type == DAISY_NOTIFY_WIN_REMOVE) {
				bool _repaint_dock_ = false;
				sys_print_text ("DOCK Received REMOVE msg \r\n");
				for (int i = 0; i < dock->dock_buttons->pointer; i++) {
					dock_button_t *buttons = (dock_button_t*)list_get_at(dock->dock_buttons, i);
					if (buttons->win_id == e.dword) {
						dock->buttons_xoff -= buttons->width - 10;
						list_remove (dock->dock_buttons, i);
						prev_focused_button = NULL;
						free(buttons);
						_repaint_dock_ = true;
						break;
					}
				}

				if (_repaint_dock_) {
					dock_repaint(dock);
					daisy_window_update_rect_area(win, 0, 0, info->width, 30);
				}

				memset(&e, 0, sizeof(pri_event_t));
			}

			if (e.type == CLOCK_MESSAGE) {
				dock_paint_time(win->ctx,info->width - 78,info->height - 30 + 2,e.dword3,e.dword2,e.dword);
				daisy_window_update_rect_area(win,info->width - 78,info->height - 30,78,30);
				memset(&e,0,sizeof(pri_event_t));
			}

			sys_wait();
	}
}