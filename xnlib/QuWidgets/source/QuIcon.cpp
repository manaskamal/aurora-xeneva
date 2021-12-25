/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  QuIcon.h -- Qu Icon object
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */

#include <QuIcon.h>
#include <stdlib.h>
#include <sys\_file.h>
#include <QuImage\QuBmpImage.h>
#include <acrylic.h>
#include <color.h>


void QuIconMouseEvent (QuWidget *wid, QuWindow *win,int code, bool clicked, int x, int y) {

}

void QuIconKeyEvent (QuWidget *wid, QuWindow *win, int code) {
}

void QuIconRefresh (QuWidget *wid, QuWindow *win) {
	QuIcon *icon = (QuIcon*)wid;
	QuDrawBMP (win->ctx, icon->bitmap, icon->wid.x, icon->wid.y);
}


QuIcon *QuCreateIcon (int x, int y) {
	QuIcon * ico = (QuIcon*)malloc(sizeof(QuIcon));
	ico->wid.x = x;
	ico->wid.y = y;
	ico->wid.ActionEvent = 0;
	ico->wid.MouseEvent = QuIconMouseEvent;
	ico->wid.ScrollEvent = 0;
	ico->wid.KeyEvent = QuIconKeyEvent;
	ico->wid.Refresh = QuIconRefresh;
	ico->wid.width = 0;
	ico->wid.height = 0;
	ico->bitmap = NULL;
	ico->icon_w = 0;
	ico->icon_h = 0;
	return ico;
}

void QuLoadIcon (QuIcon *icon, char *filename) {
	UFILE f;
	int fd = sys_open_file(filename,&f);
	unsigned char* data = (unsigned char*)malloc(f.size);
	sys_read_file(fd, data,&f);
	QuBmpImage *image = QuGetBMP(data);
	icon->bitmap = image;
	icon->icon_w = image->w;
	icon->icon_h = image->h;
	icon->wid.width = icon->icon_w;
	icon->wid.height = icon->icon_h;
}