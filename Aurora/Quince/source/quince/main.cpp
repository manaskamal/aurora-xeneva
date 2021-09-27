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
#include <jpg\jpeg_decoder.h>

//! Quince Own library
#include <bmp_image.h>
#include <QuEvent.h>
#include <QuCursor.h>
#include <ipc\_ipc_mouse.h>
#include <QuWidget\QuTaskbar.h>
#include <QuWidget\QuWallpaper.h>
#include <QuWindow\QuWindowMngr.h>
#include <QuCanvas\QuCanvasMngr.h>


int main (int argc, char* argv[]) {
	create_canvas ();
	uint32_t w = canvas_get_width();
	uint32_t h = canvas_get_height();
    psf_register_font_lib();

	//!Initialize Quince Wallpaper Manager
	Image * img = QuWallpaperInit("a:nature.jpg");
	QuWallpaperDraw (img);
	QuWallpaperPresent ();


	//! Initialize Taskbar Manager
	//QuTaskbarInit();

	//! Initialize the Window Manager
	QuWindowMngr_Initialize();

	////! Initialize QuCanvas Manager
	QuCanvasMngr_Initialize();

	canvas_screen_update(0,0,w, h);

    //! Initialize Cursor Manager
	QuCursorInit(0, 0, QU_CURSOR_ARROW);

	////!Start the mouse
	ioquery (IO_QUERY_MOUSE, MOUSE_IOCODE_ENABLE,NULL);
	//! Execute the Event Loop
	QuEventLoop();
}