/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @QuButton.h -- QuButton Widget
 *
 **/

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
	int  m_x;
	int  m_y;
	int  title_length;
	int title_height;
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