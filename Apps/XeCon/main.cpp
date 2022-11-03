#include <stdint.h>
#include <stdarg.h>
#include <sys\_ipc.h>
#include <sys\_file.h>
#include <sys\_term.h>
#include <sys\_process.h>
#include <string.h>
#include <sys\_sleep.h>
#include <sys\ioquery.h>
#include <sys\_wait.h>
#include <sys\shm.h>
#include <sys\_thread.h>
#include <sys\_kybrd.h>
#include <sys\ioquery.h>
#include <stdlib.h>
#include <acrylic.h>
#include <font.h>
#include <sys\_xeneva.h>

#include <xewidgets.h>
#include <canvas.h>
#include <stdlib.h>
#include "XeTerm.h"


void HandleSignal (int signo) {
	if (signo == 10)
		sys_print_text ("\r\n Yes it's 10 \r\n");
	sys_print_text ("Hey Signal %d \r\n", signo);
}

extern "C" void _asm_test();
/*
 * main -- the main entry point of priwm
 */
XE_EXTERN int XeMain (int argc, char* argv[]) {

	XeApp *app = XeStartApplication(argc, argv);
	int event_fd = app->event_fd;

	canvas_t * canvas = create_canvas(app->buffer_width, app->buffer_height);


	XEWindow *win = XECreateWindow(app,canvas, 1,"XeConsole",canvas->width/2 - 400/2,canvas->height/2 - 400/2);
	win->color = 0xFF3E3E3E;

	XETerm *term = XECreateTerm(0,23, app->buffer_width, app->buffer_height - 23);

	XEWindowAddWidget(win, (XEWidget*)term);

	win->shwin->alpha = false;
	XEShowWindow(win);

	sys_set_signal(SIGINT, HandleSignal);

	int master_fd, slave_fd = 0;
	sys_ttype_create(&master_fd, &slave_fd);

	winsize_t sz;
	sz.ws_col = term->ws_col;
	sz.ws_row = term->ws_row;
	sz.ws_xpixel = term->ws_xpixels;
	sz.ws_ypixel = term->ws_ypixels;
	ioquery(master_fd, TIOCSWINSZ, &sz);


	int pid = create_process("/ptest.exe", "ptest");
	sys_print_text ("PTEST PID -> %d \r\n", pid);
	sys_copy_fd(pid, slave_fd, 0);

	pri_event_t ev;
	int bytes_ret = 0;
	int ret_code = 0;
	for(;;) {
		bytes_ret = sys_read_file(master_fd,term->buffer, NULL);
		for (int i = 0; i < bytes_ret; i++)
			sys_print_text ("%c",term->buffer[i]);

		if (bytes_ret > 0){
			sys_print_text ("Bytes ret -> %d \r\n", bytes_ret);
			term->base.painter((XEWidget*)term,win);
			XEUpdateWindow(win,term->base.x, term->base.y, term->base.w, term->base.h, true);
		}

		ret_code = ioquery(event_fd,PRI_LOOP_GET_EVENT, &ev);
		if (ev.type != 0) {
			if (ev.type == 201) {
				XEWindowMouseHandle(win,ev.dword,ev.dword2,ev.dword3,0);
				memset(&ev, 0, sizeof(pri_event_t));
			}

			if (ev.type == 204) {
				if (ev.dword == KEY_C)
					_asm_test();
				memset(&ev.type, 0, sizeof(pri_event_t));
			}

		}
		
		if (ret_code == -1)
			sys_sleep(100);
	}
}