///! Copyright (C) Manas Kamal Choudhury 2021
///!
///! main.cpp -- console
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#include <color.h>
#include <acrylic.h>
#include <sys/ioquery.h>
#include <sys/_wait.h>
#include <sys/_term.h>
#include <sys/_kybrd.h>
#include <string.h>

#include <daisy.h>
#include <daisy_window.h>
#include <daisy_widget_panel.h>

#include "console.h"


int main (int argc, char* argv[]) {
	daisy_application();

	daisy_window_t *win = daisy_window_create (100,200,500,300,DAISY_WIN_NORMAL,"Console");
	daisy_win_info_t *info = daisy_get_window_info(win);
	daisy_window_set_theme (win, DAISY_THEME_90S);
	
	daisy_widget_panel_t *panel = daisy_widget_create_panel(win,BLACK);
	daisy_window_add_widget (win,(daisy_widget_t*)panel);
	daisy_window_set_back_color(win,panel->color);

	daisy_window_add_widget(win,(daisy_widget_t*)panel);

	console_t *con = create_console_widget(1,23,info->width - 1, info->height -23);
	daisy_widget_panel_add(panel,(daisy_widget_t*)con);

	daisy_window_show(win);

	int slave_fd, master_fd;
	int ret_code = sys_ttype_create(&slave_fd, &master_fd);
	if (ret_code == -1) {
		daisy_window_destroy(win);
		daisy_application_exit(0);
	}

	int event_fd = daisy_get_event_fd();
	pri_event_t e;
	while(1) { 
		ioquery (event_fd,PRI_LOOP_GET_EVENT,&e);
		if (e.type != 0) {
			if (e.type == DAISY_CURSOR_MOVED) {
				daisy_window_handle_mouse(win,e.dword, e.dword2, e.dword3);
				memset(&e, 0, sizeof(pri_event_t));
			}

			if (e.type == DAISY_KEY_EVENT) {
				if (e.dword == KEY_Q) {
					daisy_window_destroy(win);
					daisy_application_exit(0);
				}
				con->base.key_event((daisy_widget_t*)con,win,e.dword);
				memset(&e, 0, sizeof(pri_event_t));
			}
		}
		sys_wait();
	}	
	return 1;
}
		
