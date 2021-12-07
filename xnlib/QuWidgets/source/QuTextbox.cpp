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
#include <ctype.h>
#include <QuKeycodeHelper.h>

void QuTextboxRefresh (QuWidget *wid, QuWindow *win) {
	QuTextbox *tb = (QuTextbox*)wid;

	acrylic_draw_rect_filled (win->ctx,wid->x, wid->y, wid->width, wid->height,WHITE);
	acrylic_draw_rect_unfilled (win->ctx, wid->x,  wid->y,wid->width, wid->height,SILVER);
	acrylic_draw_arr_string (win->ctx,wid->x + 2,
		 wid->y + (wid->height/2) - 12/2,tb->text,BLACK);

	/*if (tb->hover)  {
		acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y, wid->width, wid->height, DESKBLUE);
		tb->hover = false;
	}*/
}


void QuTextboxMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked, int x, int y) {
}


void QuTextBoxKeyEvent (QuWidget *wid, QuWindow *win, int code) {
	QuTextbox *tb = (QuTextbox*)wid;
	if (isascii(code)){
		if (code != 0){
		//uint8_t key = code;
		char p[1];
		memset(p,0,2);
		QuConvertKeyToString(code, p);
		QuTextboxAppendText(tb,p);	
		QuTextboxRefresh(tb,win);
		QuTextboxInvalidate(tb,win);
		}
	}
}


QuTextbox * QuCreateTextbox (int x, int y, int width, int height) {
	QuTextbox *tb = (QuTextbox*)malloc(sizeof(QuTextbox));
	tb->wid.x = x;
	tb->wid.y = y;
	tb->wid.width = width;
	tb->wid.height = height;
	tb->wid.ActionEvent = 0;
	tb->wid.MouseEvent = QuTextboxMouseEvent;
	tb->wid.KeyEvent = QuTextBoxKeyEvent;
	tb->wid.Refresh = QuTextboxRefresh;
	tb->wid.ScrollEvent = NULL;
	tb->editable = false;
	tb->cursor_pos_x = 0;
	tb->cursor_pos_y = 0;
	tb->hover = false;
	tb->clicked = false;
	tb->text_paint = false;
	tb->multiline = false;
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
	QuPanelUpdate (win,tb->wid.x,tb->wid.y,tb->wid.width, tb->wid.height, false);
}

void QuTextboxRefresh (QuTextbox *tb, QuWindow* win) {
	tb->wid.Refresh ((QuWidget*)tb,win);
}

void QuTextboxAppendText (QuTextbox *tb, char* text) {
	char original_offset = strlen(tb->text);
	tb->cursor_pos_x += original_offset*8;
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
		if (original_length + j == tb->wid.width) 
			original_length = 0;
		new_value[original_length + j] = text[j];
	}

	for (int i = 0; i < 250; i++)
		tb->text[i] = new_value[i];
}