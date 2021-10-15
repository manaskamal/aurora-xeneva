///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuButton.h -- Quince Button object
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#ifndef __QU_BUTTON_H__
#define __QU_BUTTON_H__

#include <stdint.h>
#include <QuWindow.h>

#define QU_BUTTON_DEFAULT_WIDTH 140
#define QU_BUTTON_DEFAULT_HEIGHT 30


//Button structure
typedef struct _QuButton_ {
	QuWidget widget;
	const char* text;
	bool hover;
	bool clicked;
	bool default_state;
	bool swap_bit;
}QuButton;



/**
 *  QuCreateButton -- Create a new Button Widget and return to the caller
 *
 *  @param x -- X coord
 *  @param y -- Y coord
 *
 *============================================================================
 */
extern QuButton * QuCreateButton (int x, int y);

/**
 * QuButtonSetText -- Set the label of the button
 *
 * @param but -- Pointer to the button
 * @param text -- the text to be labelled
 *=======================================================
 */
extern void QuButtonSetText (QuButton *but, const char* text);

/**
 * QuButtonSetSize -- Set the size of the button
 *
 * @param but -- Pointer to the button
 * @param width -- New Width 
 * @param height -- New Height
 */
extern void QuButtonSetSize (QuButton* but,int width, int height);


/**
 * QuButtonSetActionHandler -- Set Action Handler for the button
 *
 * @param but -- Pointer to the button itself
 * @param ActionHandler -- Handler Function
 */
extern void QuButtonSetActionHandler (QuButton* but, void(*ActionHandler)(QuWidget* wid, QuWindow* win));


extern void QuButtonAckAction (QuButton* but);
#endif