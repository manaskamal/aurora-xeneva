///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuButton.h -- Quince Button object
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#include <QuButton.h>
#include <acrylic.h>
#include <stdlib.h>
#include <string.h>
#include <color.h>
#include <QuPanel.h>

//================================================================================
// Default Button Colors
//================================================================================

uint32_t button_colors[30] = {0xff59584f, 0xff5f5d53, 0xff58564e, 0xff57554d, 0xff56544c, 0xff55534b, \
    0xff54524a, 0xff525049, 0xff514f48, 0xff504e47, 0xff4e4c45, 0xff4e4c45, \
        0xff4c4a44, 0xff4b4943, 0xff4a4842, 0xff484741, 0xff46453f, 0xff45443f, \
        0xff44433e, 0xff43423d, 0xff42413c, 0xff403f3a, 0xff3f3e3a,  0xff3f3e3a, 0xff3f3e3a, \
        0xff3f3e3a,  0xff3f3e3a,  0xff3f3e3a,  0xff3f3e3a,  0xff3f3e3a};

uint32_t button_hover_colors[30] = {0x7359584f, 0x735f5d53, 0x7358564e, 0x7357554d, 0x7356544c, 0x7355534b, \
    0x7354524a, 0x73525049, 0x73514f48, 0x73504e47, 0x734e4c45, 0x734e4c45, \
        0x734c4a44, 0x734b4943, 0x734a4842, 0x73484741, 0x7346453f, 0x7345443f, \
        0x7344433e, 0x7343423d, 0x7342413c, 0x73403f3a, 0x733f3e3a,  0x733f3e3a, 0x733f3e3a, \
		0x733f3e3a,  0x733f3e3a,  0x733f3e3a,  0x733f3e3a,  0x733f3e3a};


/**
 * QuButtonRefresh -- This method is called whenever the widget
 * needs to be redrawn
 *
 * @param  wid -- Pointer to the widget itself 
 * @param  win -- The Root Window
 *
 * ===============================================================
 */
void QuButtonRefresh (QuWidget *wid, QuWindow* win) {
	QuButton *but = (QuButton*)wid;

	//!Draw the gradient colors
	for (int i = 0; i < 30; i++)
		acrylic_draw_horizontal_line (win->x + wid->x, win->y + wid->y + i,but->widget.width, button_colors[i]);

	//! Check for hover bit
	if (!but->hover) {
		acrylic_draw_arr_string (win->x + wid->x + (wid->width/2) - ((strlen(but->text)*8)/2),
		win->y + wid->y + (wid->height/2) - 12/2
		,(char*)but->text, WHITE);

		//! check for clicked bit
		if (but->clicked) {
			acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y , but->widget.width, but->widget.height,LIGHTBLACK);
			acrylic_draw_arr_string (win->x + wid->x + (wid->width/2) - ((strlen(but->text)*8)/2),
				win->y + wid->y + (wid->height/2) - 12/2
				,(char*)but->text, SILVER);

			acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y,but->widget.width, but->widget.height, SILVER); 
			acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y,but->widget.width + 1, but->widget.height + 1, DESKBLUE); 
			but->clicked = false;
		}

	}
	/**
	 * hover bit, then simply draw its hover state
	 */
	else if (but->hover)  {

		acrylic_draw_arr_string (win->x + wid->x + (wid->width/2) - ((strlen(but->text)*8)/2),
		win->y + wid->y + (wid->height/2) - 12/2
		,(char*)but->text, LIGHTSILVER);
		acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y,but->widget.width, but->widget.height, SILVER); 
		acrylic_draw_rect_unfilled (win->x + wid->x, win->y + wid->y,but->widget.width + 1, but->widget.height + 1, DESKBLUE); 
		but->hover = false;

	}
}


/**
 * QuButtonMouseEvent -- Calls whenever new Mouse events occurs
 *
 * @param wid -- Pointer to the widget itself
 * @param win -- Pointer to the root window 
 * @param code -- The mouse code that needs to be processed
 * @param clicked -- Click bit
 *====================================================================
 */
void QuButtonMouseEvent (QuWidget *wid, QuWindow* win, int code, bool clicked, int x, int y) {
	QuButton *but = (QuButton*)wid;
	/**
	 * The mouse enter event
	 */
	if (code == QU_EVENT_MOUSE_ENTER) {
		but->hover = true;
	
		QuButtonRefresh(wid, win);
        QuPanelUpdate (win->x + but->widget.x, win->y + but->widget.y, but->widget.width, but->widget.height, false);

		/* Make the difference between clicking & dragging here */
		if (clicked && but->m_x == x && but->m_y == y) {
			but->clicked = true;
			but->hover = false;
			QuButtonRefresh(wid, win);
			QuPanelUpdate (win->x + but->widget.x, win->y + but->widget.y, but->widget.width, but->widget.height, false);
			//but->default_state = true;
		}
		but->default_state = true;

		/* 
		 * Make the difference between clicking & dragging here, before 
		 * calling the action event */

		if (clicked && but->m_x == x && but->m_y == y) {
			if (but->swap_bit == 0) {
				//!Call the action handler
				but->swap_bit = 1;
				if (but->widget.ActionEvent)
					but->widget.ActionEvent(wid,win);
			}
		}
		
	}

	if (code == QU_EVENT_MOUSE_LEAVE) {
		if (but->default_state) {
			but->hover = false;
			QuButtonRefresh(wid, win);
			but->default_state = false;
			QuPanelUpdate (win->x + but->widget.x, win->y + but->widget.y, but->widget.width, but->widget.height, false);
		}
	}

	/*
	 * Store the mouse coord
	 * next mouse events
	 */
	but->m_x = x;
	but->m_y = y;
}


/**
 *  QuCreateButton -- Create a new Button Widget and return to the caller
 *
 *  @param x -- X coord
 *  @param y -- Y coord
 *
 *============================================================================
 */
QuButton * QuCreateButton(int x, int y) {
	QuButton *but = (QuButton*)malloc(sizeof(QuButton));
	but->widget.x = x;
	but->widget.y = y;
	but->widget.width = QU_BUTTON_DEFAULT_WIDTH;
	but->widget.height = QU_BUTTON_DEFAULT_HEIGHT;
	but->widget.Refresh = QuButtonRefresh;
	but->widget.MouseEvent = QuButtonMouseEvent;
	but->widget.KeyEvent = 0;
	but->widget.ActionEvent = NULL;
	but->text = NULL;
	but->hover = false;
	but->clicked = false;
	but->default_state = false;
	but->swap_bit = 0;
	but->m_x = 0;
	but->m_y = 0;
	return but;
}


/**
 * QuButtonSetText -- Set the label of the button
 *
 * @param but -- Pointer to the button
 * @param text -- the text to be labelled
 *=======================================================
 */
void QuButtonSetText (QuButton* but, const char* text) {
	but->text = text;
}


/**
 * QuButtonSetSize -- Set the size of the button
 *
 * @param but -- Pointer to the button
 * @param width -- New Width 
 * @param height -- New Height
 */
void QuButtonSetSize (QuButton* but,int width, int height) {
	but->widget.width = width;
	but->widget.height = height;
}


/**
 * QuButtonSetActionHandler -- Set Action Handler for the button
 *
 * @param but -- Pointer to the button itself
 * @param ActionHandler -- Handler Function
 *
 */
void QuButtonSetActionHandler (QuButton* but, void(*ActionHandler)(QuWidget* wid, QuWindow* win)) {
	but->widget.ActionEvent = ActionHandler;
}


void QuButtonAckAction (QuButton* but) {
	but->swap_bit = 0;
}



