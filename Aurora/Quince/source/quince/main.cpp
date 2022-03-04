/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  main.cpp -- The Main entry for Quince
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury 2021
 *
 *==============================================
 */

#include <sys\_term.h>
#include <sys\_sleep.h>
#include <sys\_thread.h>
#include <sys\_wait.h>
#include <sys\_ipc.h>
#include <sys\_process.h>
#include <sys\ioquery.h>
#include <sys\mmap.h>
#include <string.h>
#include <canvas.h>
#include <color.h>
#include <psf\psf.h>
#include <acrylic.h>
#include <image.h>
#include <font.h>
#include <jpg\jpeg_decoder.h>

//! Quince Own library
#include <bmp_image.h>
#include <QuEvent.h>
#include <QuCursor.h>
#include <ipc\_ipc_mouse.h>
#include <QuWidget\QuDock.h>
#include <QuWidget\QuWallpaper.h>
#include <QuWindow\QuWindowMngr.h>
#include <QuCanvas\QuCanvasMngr.h>
#include <sys\_exit.h>

canvas_t *canvas = NULL;


canvas_t *QuGetCanvas() {
	return canvas;
}


int main (int argc, char* argv[]) {
	int svga_fd = sys_open_file ("/dev/fb", NULL);
	
	uint32_t s_width = ioquery(svga_fd,SVGA_GET_WIDTH,NULL);
	uint32_t s_height = ioquery(svga_fd, SVGA_GET_HEIGHT, NULL);
	
	canvas = create_canvas (s_width,s_height);
	int w = canvas_get_width(canvas);
	int h = canvas_get_height(canvas);
	
	acrylic_initialize_font();

	//!Initialize Quince Wallpaper Manager  "a:coffee.jpg"  "/bihu.jpg""/river.jpg"
	Image * img = QuWallpaperInit("/leaf.jpg");
	QuWallpaperDraw (img);
	QuWallpaperPresent ();

	//! Initialize Taskbar Manager
	QuDockInit();

	//! Initialize the Window Manager
	QuWindowMngr_Initialize();

	////! Initialize QuCanvas Manager
	QuCanvasMngr_Initialize();

	canvas_screen_update(canvas,0,0,w, h);

    //! Initialize Cursor Manager
	QuCursorInit(0, 0, QU_CURSOR_ARROW);

	int mouse_fd = sys_open_file ("/dev/mouse", NULL);


	////!Start the mouse
//	ioquery (mouse_fd, MOUSE_IOCODE_ENABLE,NULL);
	//! Execute the Event Loop
	QuEventLoop();
}