#include <QuWindow.h>
#include <QuBase.h>
#include <QuIcon.h>
#include <QuPanel.h>
#include <QuImage\QuBmpImage.h>

#include <sys\_file.h>
#include <acrylic.h>
#include <sys\_ipc.h>
#include <sys\_time.h>
#include <sys\_xeneva.h>
#include <sys\_thread.h>
#include <sys\_process.h>
#include <sys\_wait.h>
#include <sys\_sleep.h>
#include <string.h>
#include <color.h>

void QuActions (QuMessage *msg) {
	if (msg->type == QU_CANVAS_FOCUS_LOST) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_FOCUS_GAIN) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_DESTROYED) {
		canvas_close(QuGetWindow()->ctx);
		exit(0);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_MOUSE_MOVE) {
		QuWindowHandleMouse(msg->dword, msg->dword2, msg->dword3);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_REPAINT) {
		QuWinInfo *info = (QuWinInfo*)QuGetWindow()->win_info_data;
		if (QuGetWindow()->maximized  == true && 
			info->maximize == false) {
			QuGetWindow()->w = QuGetWindow()->oldw;
			QuGetWindow()->h = QuGetWindow()->oldh;
			QuGetWindow()->maximized = false;
		}
		QuWindowRepaint(QuGetWindow());
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_KEY_PRESSED) {
		QuWindowHandleKey(msg->dword);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_RESIZE) {
		QuGetWindow()->w = msg->dword;
		QuGetWindow()->h = msg->dword2;
		QuWindowRepaint(QuGetWindow());
		memset(msg, 0, sizeof(QuMessage));
	}
}

QuWindow* win;
QuBmpImage *bmp;


void render() {	
	int x = 0;
	while(1) {
		acrylic_draw_rect_filled(win->ctx,0,23,win->w,win->h-23,0x40808080);
		if (x + 100 >= win->w)
			x = 0;
		//acrylic_draw_rect_filled(win->ctx,x, win->h/2, 100,100,RED);
		QuDrawBMP(win->ctx,bmp,x,win->h/2);
		QuPanelUpdate(win,0,0,win->w, win->h, true);
		x += 20;
		sys_sleep(16);
	}
}

int main (int argc, char* argv[]) {
	win = QuCreateWindow(300,300,500,500,"Snake");
	QuSetRootWindow (win);

	canvas_t *canvas = canvas_initialize(win->w, win->h);
	win->ctx = canvas;
	QuWindowShowControls(win);

	QuWindowSetIcon(SYSTEM_ICON_CONSOLE);

	QuWindowSetTransparency(true);
	QuWindowShow(win);

	
	UFILE f;
	int fd = sys_open_file("/fun.bmp",&f);
	unsigned char* buffer = (unsigned char*)malloc(f.size);
	sys_read_file(fd, buffer, &f);

	bmp = QuGetBMP(buffer);

	create_uthread(render,"render");
	QuMessage qmsg;
	uint16_t app_id = get_current_pid();
	while(1) { 

		QuChannelGet(&qmsg);
		if (qmsg.to_id == app_id)
			QuActions(&qmsg);

		sys_wait();
	}

}