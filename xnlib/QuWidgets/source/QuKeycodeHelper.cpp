///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuKeycodeHelper.cpp -- Converts Keycodes to String
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=========================================================


#include <QuKeycodeHelper.h>
#include <ctype.h>

bool shift = false;
bool capslock = false;

char kbdus[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b',   /* Backspace */
    '\t',           /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',       /* Enter key */
    0,          /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',   /* 39 */
    '\'', '`',   0,     /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',         /* 49 */
    'm', ',', '.', '/',   0,                    /* Right shift */
    '*',
    0,  /* Alt */
    ' ',    /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
    '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
    '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};


void QuConvertKeyToString (int code, char *p) {

	if (code == KEY_CAPSLOCK) {
		capslock = !capslock;
		return;
	}


	if (shift ) {
		switch (code) {
		case KEY_0:
			*p = KEY_C_RIGHTPARENTHESIS;
			shift = !shift;
			return;
		case KEY_1:
			*p = KEY_C_EXCLAMATION;
			shift = !shift;
			return;
		case KEY_2:
			*p = KEY_C_AT;
			shift = !shift;
			return;
		case KEY_3:
			*p = KEY_C_HASH;
			shift = !shift;
			return;
		case KEY_4:
			*p = KEY_C_EURO;
			shift = !shift;
			return;
		case KEY_5:
			*p = KEY_C_PERCENT;
			shift = !shift;
			return;
		case KEY_6:
			*p = KEY_C_CARRET;
			shift = !shift;
			return;
		case KEY_7:
			*p = KEY_C_AMPERSAND;
			shift = !shift;
			return;
		case KEY_8:
			*p = KEY_C_ASTERISK;
			shift = !shift;
			return;
		case KEY_9:
			*p = KEY_C_LEFTPARENTHESIS;
			shift = !shift;
			return;
		case KEY_MINUS:
			*p = KEY_C_UNDERSCORE;
			shift = !shift;
			return;
		case KEY_EQUAL:
			*p = KEY_C_PLUS;
			shift = !shift;
			return;
		case KEY_LEFTBRACKET:
			*p = KEY_C_LEFTCURL;
			shift = !shift;
			return;
		case KEY_RIGHTBRACKET:
			*p = KEY_C_RIGHTCURL;
			shift = !shift;
			return;
		case KEY_BACKSLASH:
			*p = KEY_C_BAR;
			shift = !shift;
			return;
		case KEY_SEMICOLON:
			*p = KEY_C_COLON;
			shift = !shift;
			return;
		case KEY_QUOTE:
			*p = KEY_C_QUOTEDOUBLE;
			shift = !shift;
			return;
		case KEY_COMMA:
			*p = KEY_C_LESS;
			shift = !shift;
			return;
		case KEY_DOT:
			*p = KEY_C_GREATER;
			shift = !shift;
			return;
		case KEY_SLASH:
			*p = KEY_C_QUESTION;
			shift = !shift;
			return;
		case KEY_GRAVE:
			*p = KEY_C_TILDE;
			shift = !shift;
			return;
		}
	} 


	if (code == KEY_LSHIFT || code == KEY_RSHIFT) {
		shift = true;
		return;
	}
	

	if (capslock) 
		*p = toupper(kbdus[code]);
	else 
		*p = kbdus[code];
}