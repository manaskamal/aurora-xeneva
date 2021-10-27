///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  //PROJECT - Aurora's Xeneva
///!  //AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#ifndef __QU_KEY_CODE_HELPER_H__
#define __QU_KEY_CODE_HELPER_H__

#include <sys\_kybrd.h>

enum KEYCHARS {
    KEY_C_DOT               = '.',
	KEY_C_COMMA             = ',',
	KEY_C_COLON             = ':',
	KEY_C_SEMICOLON         = ';',
	KEY_C_SLASH             = '/',
	KEY_C_BACKSLASH         = '\\',
	KEY_C_PLUS              = '+',
	KEY_C_MINUS             = '-',
	KEY_C_ASTERISK          = '*',
	KEY_C_EXCLAMATION       = '!',
	KEY_C_QUESTION          = '?',
	KEY_C_QUOTEDOUBLE       = '\"',
	KEY_C_QUOTE             = '\'',
	KEY_C_EQUAL             = '=',
	KEY_C_HASH              = '#',
	KEY_C_PERCENT           = '%',
	KEY_C_AMPERSAND         = '&',
	KEY_C_UNDERSCORE        = '_',
	KEY_C_LEFTPARENTHESIS   = '(',
	KEY_C_RIGHTPARENTHESIS  = ')',
	KEY_C_LEFTBRACKET       = '[',
	KEY_C_RIGHTBRACKET      = ']',
	KEY_C_LEFTCURL          = '{',
	KEY_C_RIGHTCURL         = '}',
	KEY_C_DOLLAR            = '$',
	KEY_C_POUND             = '£',
	KEY_C_EURO              = '$',
	KEY_C_LESS              = '<',
	KEY_C_GREATER           = '>',
	KEY_C_BAR               = '|',
	KEY_C_GRAVE             = '`',
	KEY_C_TILDE             = '~',
	KEY_C_AT                = '@',
	KEY_C_CARRET            = '^',
};

extern void QuConvertKeyToString (int code, char *c);

#endif