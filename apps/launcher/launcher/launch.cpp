/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @launch -- launcher
 *
 **/

#include <acrylic.h>
#include <color.h>
#include <daisy.h>
#include <daisy_window.h>
#include <daisy_widget_button.h>
#include <daisy_widget_panel.h>
#include <string.h>

#include <sys\ioquery.h>
#include <sys\_wait.h>
#include <sys\_term.h>
#include <sys\_process.h>

void terminal_button_action (daisy_widget_t *widget, daisy_window_t *win) {
	sys_print_text ("Terminal Button clicked \r\n");
	create_process ("/cnsl.exe", "cnsl");
}

void snake_button_action (daisy_widget_t *widget, daisy_window_t *win) {
	sys_print_text ("snake Button clicked \r\n");
	create_process ("/snake.exe", "snake");
}

int main (int argc, char* argv[]) {
	daisy_application();

	daisy_window_t *win = daisy_window_create (40,60,300,180,DAISY_WIN_NORMAL,"Launcher");
	//daisy_window_set_theme(win,DAISY_THEME_90S);

	daisy_widget_panel_t *panel = daisy_widget_create_panel (win,LIGHTSILVER);
	daisy_window_add_widget(win,(daisy_widget_t*)panel);

	daisy_widget_button_t *button = daisy_widget_create_button (win,"Terminal");
	daisy_widget_button_set_dimension (button,2,23, 78,30);
	button->base.action_event = terminal_button_action;


	daisy_widget_button_t *snake = daisy_widget_create_button (win, "Snake");
	daisy_widget_button_set_dimension (snake, 78 + 2, 23,78,30);
	snake->base.action_event = snake_button_action;
	
	daisy_widget_panel_add(panel, (daisy_widget_t*)button);
	daisy_widget_panel_add(panel, (daisy_widget_t*)snake);

	daisy_window_show(win);

	int event_fd = daisy_get_event_fd();
	pri_event_t e;
	while(1) { 
		ioquery (event_fd,PRI_LOOP_GET_EVENT,&e);
		if (e.type != 0) {
			if (e.type == DAISY_CURSOR_MOVED) {
				daisy_window_handle_mouse(win,e.dword, e.dword2, e.dword3);
				memset(&e, 0, sizeof(pri_event_t));
			}
		}
		sys_wait();
	}	
	return 1;
}

