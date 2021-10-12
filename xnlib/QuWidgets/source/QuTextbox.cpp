///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuTextbox -- Quince Textbox widget
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury 
///!
///!==================================================

#include <QuTextbox.h>
#include <QuPanel.h>
#include <stdlib.h>
#include <string.h>
#include <color.h>

void QuTextboxRefresh (QuWidget *wid, QuWindow *win) {
	QuTextbox *tb = (QuTextbox*)wid;
	acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y, wid->width, wid->height,WHITE);
	acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y,wid->width, wid->height,SILVER);
	acrylic_draw_arr_string (win->x + wid->x + 2,
		win->y + wid->y + (wid->height/2) - 12/2,tb->text,BLACK);

	/*if (tb->hover)  {
		acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y, 240, 150, DESKBLUE);
		tb->hover = false;
	}*/
}


void QuTextboxMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked) {
	//QuTextbox *tb = (QuTextbox*)wid;

	/*if (code == QU_EVENT_MOUSE_ENTER) {
		tb->hover = true;
		QuTextboxRefresh (wid, win);
		QuPanelUpdate(win->x + wid->x, win->y + wid->y, wid->width,wid->height);
	}else if (code == QU_EVENT_MOUSE_LEAVE) {
		QuTextboxRefresh (wid, win);
		QuPanelUpdate(win->x + wid->x, win->y + wid->y, wid->width,wid->height);
	}*/

}


QuTextbox * QuCreateTextbox (int x, int y, int width, int height) {
	QuTextbox *tb = (QuTextbox*)malloc(sizeof(QuTextbox));
	tb->wid.x = x;
	tb->wid.y = y;
	tb->wid.width = width;
	tb->wid.height = height;
	tb->wid.ActionEvent = 0;
	tb->wid.MouseEvent = QuTextboxMouseEvent;
	tb->wid.Refresh = QuTextboxRefresh;
	tb->editable = false;
	tb->cursor_pos_x = 0;
	tb->hover = false;
	tb->clicked = false;
	tb->text_paint = false;
	memset(tb->text, 0, 512);
	return tb;
}


void QuEnterText (QuTextbox* tb, char* text) {
	for (int i = 0; i < strlen(text); i++)
		tb->text[i] = text[i];
	tb->cursor_pos_x += strlen(text)*8;
	tb->text_paint = true;
}

void QuTextboxInvalidate (QuTextbox *tb, QuWindow* win) {
	QuPanelUpdate (win->x + tb->wid.x, win->y + tb->wid.y,tb->wid.width, tb->wid.height);
}

void QuTextboxRefresh (QuTextbox *tb, QuWindow* win) {
	tb->wid.Refresh ((QuWidget*)tb,win);
}

void QuTextboxAppendText (QuTextbox *tb, char* text) {
	char original_offset = strlen(tb->text);
	char* original_text = tb->text;
	int original_length = 0;
	int new_length = 0;

	while(tb->text[original_length])
		original_length++;

	while(text[new_length])
		new_length++;


	char new_value[250];
	memset (new_value, 0, 250);

	for (int i = 0; i < original_length; i++) 
		new_value[i] = original_text[i];

	for (int j = 0; j < new_length; j++) {
		if (original_length + j == 250) 
			original_length = 0;
		new_value[original_length + j] = text[j];
	}

	for (int i = 0; i < 250; i++)
		tb->text[i] = new_value[i];
}