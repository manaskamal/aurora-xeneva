///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuTerminal.h -- Terminal Widget 
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================

#include <QuTerminal.h>
#include <stdlib.h>
#include <ctype.h>
#include <acrylic.h>
#include <QuPanel.h>
#include <color.h>
#include <string.h>
#include <QuKeycodeHelper.h>


#define TERM_WIDTH 74
#define TERM_HEIGHT 26


void QuTermScroll (QuTerminal *term) {
	for (int i = 0; i < TERM_HEIGHT; i++)
		memcpy (term->text + i * TERM_WIDTH, term->text + ((i + 1) * TERM_WIDTH), TERM_WIDTH);

	for (int i = 0; i < TERM_WIDTH; i++)
		term->text[(TERM_HEIGHT-1)*TERM_WIDTH + i] = '\0';

	QuTermFlush(term, QuGetWindow());
	//term->wid.Refresh ((QuWidget*)term, QuGetWindow());
	QuWindowShow ();
	QuPanelUpdate ( QuGetWindow()->x,  QuGetWindow()->y,  QuGetWindow()->w,  QuGetWindow()->h, false);
}


void QuTermPrint (QuTerminal *term, char s, uint32_t color) {
	if (s == '\n'){
		term->text[term->cursor_y * TERM_WIDTH + term->cursor_x] = s;
		QuTermFlush (term, QuGetWindow());
		term->cursor_x = 0;

		if (term->cursor_y == TERM_HEIGHT - 1) 
			QuTermScroll(term);
		else {
			term->cursor_y++;
			term->ypos += 13;
		}
		term->xpos = 0;
		return;
	}

	if (s == '\b') {
		term->text[term->cursor_y * TERM_WIDTH + term->cursor_x] = '\0';
		QuTermFlush(term, QuGetWindow());
		term->cursor_x--;
		term->xpos -= 8;	
		if (term->cursor_x <= 0 && term->xpos <= 0){
			term->cursor_x = 0;
			term->xpos = 0;
		}
		return;
	}

	if (term->cursor_x == TERM_WIDTH) {
		term->cursor_x = TERM_WIDTH;
		if (term->cursor_y == TERM_HEIGHT - 1)
			QuTermScroll(term);
		else 
			term->cursor_y++;
	}

	term->text[term->cursor_y * TERM_WIDTH + term->cursor_x] = s;
	QuTermFlush(term, QuGetWindow());
	term->cursor_x++;
	term->xpos += 8;
	term->text[term->cursor_y * TERM_WIDTH + term->cursor_x] = '_';
	QuTermFlush(term, QuGetWindow());
}


void QuTermMouse (QuWidget* wid, QuWindow *win, int code, bool clicked, int x, int y) {
}


void QuTermRefresh (QuWidget* wid, QuWindow *win) {
	QuTerminal *term = (QuTerminal*)wid;
	acrylic_draw_rect_filled(win->x + wid->x, win->y + wid->y, wid->width, wid->height, BLACK);

	char tmp_str[2];
	memset(tmp_str, 0, 2);
	int xoff = 0;
	int yoff = 0;
	int ypos = 0;
	int xpos = 0;
	for (int yp = 0; yp < TERM_HEIGHT; yp++) {
		for (int xp = 0; xp < TERM_WIDTH; xp++) {
			tmp_str[0] = term->text[yoff * TERM_WIDTH + xoff];
			if (tmp_str[0] == '\n') {
				xoff = 0;
				yoff++;
				xpos = 0;
				ypos += 13;
				continue;
			}
			acrylic_draw_arr_string(win->x + wid->x + xpos, win->y + wid->y + 23 + ypos, tmp_str, WHITE);
			xoff++;
			xpos += 8;
		}
	}
}

void QuTermFlush (QuTerminal *term, QuWindow* win) {
	char c = term->text[term->cursor_y * TERM_WIDTH + term->cursor_x];
	acrylic_draw_rect_filled(win->x + term->wid.x + term->xpos + 1, win->y + term->wid.y + 23 + term->ypos,8,13,BLACK);
	if (c != '\n' && c != '\0')
		acrylic_draw_arr_font (win->x + term->wid.x + term->xpos, win->y + term->wid.y + 23 + term->ypos,c, WHITE);
	QuPanelUpdate (win->x + term->wid.x, win->y + term->wid.y + 23+ term->ypos, win->w, 14, false);
}


void QuTermKeyEvent (QuWidget* wid, QuWindow *win, int code){
	QuTerminal *term = (QuTerminal*)wid;
	if (isascii(code)){

		if (code == KEY_KP_ENTER) {
			QuTermPrint (term, '\n',WHITE);
			QuTermFlush(term, win);
			return;
		}
		if (code == KEY_BACKSPACE) {
			QuTermPrint (term, '\b', WHITE);
			QuTermFlush(term, win);
			return;
		}
		char p[1];
		memset(p,0,2);
		QuConvertKeyToString(code, p);
		QuTermPrint(term, p[0], WHITE);
		QuTermFlush(term, win);
	}
}




QuTerminal * QuCreateTerminal (int x, int y, int w, int h) {
	QuTerminal *term = (QuTerminal*)malloc(sizeof(QuTerminal));
	term->wid.x = x;
	term->wid.y = y;
	term->wid.width = w;
	term->wid.height = h;
	term->wid.MouseEvent = QuTermMouse;
	term->wid.KeyEvent = QuTermKeyEvent;
	term->wid.Refresh = QuTermRefresh;
	term->cursor_x = 0;
	term->cursor_y = 0;
	term->xpos = 0;
	term->ypos = 0;
	memset (term->text, 0, TERM_WIDTH*TERM_HEIGHT);
	return term;
}