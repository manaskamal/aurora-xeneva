/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
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
 *
 **/

#ifndef __XE_RADIO_GROUP_H__
#define __XE_RADIO_GROUP_H__

#include <xewidget.h>
#include <sys\_xeneva.h>
#include <list.h>
#include <xeradiobutton.h>

typedef struct _xe_radio_group_ {
	XEWidget base;
	list_t *radio_buttons;
	XERadioButton *focused_button;
	XERadioButton *choosed_button;
	char* label;
}XERadioGroup;


/*
 * XECreateRadioButton -- creates a radio button 
 * @param x -- X location relative to window activity area
 * @param y -- Y location relative to window activity area
 * @param label -- label of the radio button
 */
XE_EXTERN XE_EXPORT XERadioGroup *XECreateRadioGroup (int x, int y, char* label);

/*
 * XERadioGroupAdd -- Add a radio button to radio group 
 * @param group -- Pointer to Radio Group
 * @param button -- Radio Button to add
 */
XE_EXTERN XE_EXPORT void XERadioGroupAdd (XERadioGroup *group , XERadioButton *button);
#endif