///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuEditBox.cpp -- Quince Edit box widget
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================


#include <QuEditbox.h>
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>
#include <QuScrollbar.h>
#include <QuPanel.h>
#include <sys\mmap.h>
#include <sys\_term.h>
#include <fastcpy.h>
#include <font.h>
#include <clientctx.h>

#define EDIT_BOX_WIDTH  74
#define EDIT_BOX_HEIGHT 36

void CopyToFB (QuWidget* wid, QuWindow* win, int x, int y, int w, int h, canvas_t* ctx) {
	uint32_t *dbl_buffer = (uint32_t*)win->ctx->address;
	uint32_t *backstr = (uint32_t*)ctx->address;
	for (int i = 0; i < h; i++)
		fastcpy (dbl_buffer + (wid->y + i) * canvas_get_width(win->ctx) + wid->x,
		backstr + (y + i) * canvas_get_width(win->ctx) + x, w * 4);
}


void QuEditBoxRefresh (QuWidget *wid, QuWindow *win) {
	QuEditBox *eb = (QuEditBox*)wid;
	
	CopyToFB (wid,win,
			0 + eb->last_scroll_diffx,  
			0 + eb->last_scroll_diffy,
			wid->width - 15, wid->height - 15,eb->ctx);	
	acrylic_draw_rect_unfilled (win->ctx,wid->x,wid->y, wid->width, wid->height, GRAY);
}


void QuEditBoxMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked, int m_x, int m_y) {
}

void QuEditBoxScrollEvent (QuWidget *wid, QuWidget *scroll, QuWindow *win) {
	QuScrollBar *sb = (QuScrollBar*)scroll;
	QuEditBox *eb = (QuEditBox*)wid;
  
	if (sb->type == QU_SCROLLBAR_HORIZONTAL)
		eb->last_scroll_diffx = sb->scroll_xoff;

	if (sb->type == QU_SCROLLBAR_VERTICAL)
		eb->last_scroll_diffy = sb->scroll_yoff;

	if (sb->type == QU_SCROLLBAR_HORIZONTAL){  
		
		CopyToFB (wid,win,
			0 + eb->last_scroll_diffx,  
			0 + eb->last_scroll_diffy,
			wid->width - 15, wid->height - 15,eb->ctx);	
	}

	if (sb->type == QU_SCROLLBAR_VERTICAL) {
		CopyToFB (wid,win,
			0 + eb->last_scroll_diffx,
			0 + eb->last_scroll_diffy,
			wid->width - 15, wid->height - 15,eb->ctx);	
	}

	acrylic_draw_rect_unfilled (win->ctx,wid->x,wid->y, wid->width, wid->height, GRAY);

	//QuPanelUpdate (win->x + wid->x, win->y + wid->y, wid->width - 15, wid->height - 15, false);
}


QuEditBox *QuCreateEditBox (int x, int y, int w, int h) {
	QuEditBox *eb = (QuEditBox*)malloc(sizeof(QuEditBox));
	eb->wid.x = x;
	eb->wid.y = y;
	eb->wid.width = w;
	eb->wid.height = h;
	eb->wid.Refresh = QuEditBoxRefresh;
	eb->wid.MouseEvent = QuEditBoxMouseEvent;
	eb->wid.KeyEvent = NULL;
	eb->wid.ActionEvent = NULL;
	eb->wid.ScrollEvent = QuEditBoxScrollEvent;
	eb->last_scroll_diffx = 0;
	eb->last_scroll_diffy = 0;
	//! This should be much larger memory allocation
	//! this mappings should be moved to another object
	//! called QuStringBuffer...  for now
	//! let's create it here
	eb->ctx = create_canvas(1024,720);
	eb->buffer = (uint8_t*)malloc(65536);
	
	return eb;
}


void QuEditBoxSetVisible (QuEditBox *eb) {
	for (int i = 0; i < 1024; i++)
		for (int j = 0; j < 720; j++)
			canvas_draw_pixel(eb->ctx, 0 + i, 0 + j, LIGHTSILVER);

}

void QuEditBoxFlush (QuEditBox *eb, QuWindow *win) {
	char c = eb->buffer[eb->cursor_y * EDIT_BOX_WIDTH + eb->cursor_x];
	//cc_draw_rect_filled(eb->xpos + 1, eb->ypos,8,13,WHITE);
	if (c != '\n' && c != '\0')
		acrylic_draw_arr_font (eb->ctx,eb->xpos, eb->ypos,c, BLACK);
	//QuPanelUpdate (win->x + eb->wid.x, win->y + eb->wid.y + 23+ eb->ypos, win->w, 14, false);
}


void QuEditBoxSetChar (QuEditBox *eb, char s, uint32_t color) {
	if (s == '\n'){
		eb->buffer[eb->cursor_y * EDIT_BOX_WIDTH + eb->cursor_x] = s;
		QuEditBoxFlush (eb, QuGetWindow());
		eb->cursor_x = 0;

		eb->cursor_y++;
		eb->ypos += 12;
		
		eb->xpos = 0;
		return;
	}

	if (s == '\b') {
		eb->buffer[eb->cursor_y * EDIT_BOX_WIDTH + eb->cursor_x] = '\0';
		QuEditBoxFlush(eb, QuGetWindow());
		eb->cursor_x--;
		eb->xpos -= acrylic_get_system_font()->width;	
		if (eb->cursor_x <= 0 && eb->xpos <= 0){
			eb->cursor_x = 0;
			eb->xpos = 0;
		}
		return;
	}

	if (eb->cursor_x == EDIT_BOX_WIDTH) {
		eb->cursor_x = EDIT_BOX_WIDTH;
		/*if (eb->cursor_y == EDIT_BOX_HEIGHT - 1)
			QuTermScroll(term);
		else */
		eb->cursor_y++;
	}

	eb->buffer[eb->cursor_y * EDIT_BOX_WIDTH + eb->cursor_x] = s;
	QuEditBoxFlush(eb, QuGetWindow());
	eb->cursor_x++;
	eb->xpos += 8;
	//eb->buffer[eb->cursor_y * EDIT_BOX_WIDTH + eb->cursor_x] = '_';
	//QuEditBoxFlush(eb, QuGetWindow());
}


void QuEditSetText (QuEditBox *eb, char* string) {
	while(*string)
		QuEditBoxSetChar(eb,*(string)++,BLACK);
}