/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * KeyEvent.cpp -- Keyboard Event handling 
 *
 * /PROJECT - Aurora Xeneva
 * /AUTHOR  - Manas Kamal Choudhury
 *
 *=============================================
 */

#include <input\KeyEvent.h>
#include <xnsys.h>

static char _scancode;

//! lock keys
static bool _numlock, _scrolllock, _capslock;

//! shift, alt, and ctrl keys current state
static bool _shift, _alt, _ctrl;

//! set if keyboard error
static int _kkybrd_error = 0;

//! set if the Basic Assurance Test (BAT) failed
static bool _kkybrd_bat_res = false;

//! set if diagnostics failed
static bool _kkybrd_diag_res = false;

//! set if system should resend last command
static bool _kkybrd_resend_res = false;


const int INVALID_SCANCODE = 0;

static int _kkybrd_scancode_std [] = {

	//! key			scancode
	KEY_UNKNOWN,	//0
	KEY_ESCAPE,		//1
	KEY_1,			//2
	KEY_2,			//3
	KEY_3,			//4
	KEY_4,			//5
	KEY_5,			//6
	KEY_6,			//7
	KEY_7,			//8
	KEY_8,			//9
	KEY_9,			//0xa
	KEY_0,			//0xb
	KEY_MINUS,		//0xc
	KEY_EQUAL,		//0xd
	KEY_BACKSPACE,	//0xe
	KEY_TAB,		//0xf
	KEY_Q,			//0x10
	KEY_W,			//0x11
	KEY_E,			//0x12
	KEY_R,			//0x13
	KEY_T,			//0x14
	KEY_Y,			//0x15
	KEY_U,			//0x16
	KEY_I,			//0x17
	KEY_O,			//0x18
	KEY_P,			//0x19
	KEY_LEFTBRACKET,//0x1a
	KEY_RIGHTBRACKET,//0x1b
	KEY_RETURN,		//0x1c
	KEY_LCTRL,		//0x1d
	KEY_A,			//0x1e
	KEY_S,			//0x1f
	KEY_D,			//0x20
	KEY_F,			//0x21
	KEY_G,			//0x22
	KEY_H,			//0x23
	KEY_J,			//0x24
	KEY_K,			//0x25
	KEY_L,			//0x26
	KEY_SEMICOLON,	//0x27
	KEY_QUOTE,		//0x28
	KEY_GRAVE,		//0x29
	KEY_LSHIFT,		//0x2a
	KEY_BACKSLASH,	//0x2b
	KEY_Z,			//0x2c
	KEY_X,			//0x2d
	KEY_C,			//0x2e
	KEY_V,			//0x2f
	KEY_B,			//0x30
	KEY_N,			//0x31
	KEY_M,			//0x32
	KEY_COMMA,		//0x33
	KEY_DOT,		//0x34
	KEY_SLASH,		//0x35
	KEY_RSHIFT,		//0x36
	KEY_KP_ASTERISK,//0x37
	KEY_RALT,		//0x38
	KEY_SPACE,		//0x39
	KEY_CAPSLOCK,	//0x3a
	KEY_F1,			//0x3b
	KEY_F2,			//0x3c
	KEY_F3,			//0x3d
	KEY_F4,			//0x3e
	KEY_F5,			//0x3f
	KEY_F6,			//0x40
	KEY_F7,			//0x41
	KEY_F8,			//0x42
	KEY_F9,			//0x43
	KEY_F10,		//0x44
	KEY_KP_NUMLOCK,	//0x45
	KEY_SCROLLLOCK,	//0x46
	KEY_HOME,		//0x47
	KEY_KP_8,		//0x48	//keypad up arrow
	KEY_PAGEUP,		//0x49
	KEY_KP_2,		//0x50	//keypad down arrow
	KEY_KP_3,		//0x51	//keypad page down
	KEY_KP_0,		//0x52	//keypad insert key
	KEY_KP_DECIMAL,	//0x53	//keypad delete key
	KEY_UNKNOWN,	//0x54
	KEY_UNKNOWN,	//0x55
	KEY_UNKNOWN,	//0x56
	KEY_F11,		//0x57
	KEY_F12			//0x58
};


enum KYBRD_ERROR {

	KYBRD_ERR_BUF_OVERRUN			=	0,
	KYBRD_ERR_ID_RET				=	0x83AB,
	KYBRD_ERR_BAT					=	0xAA,	//note: can also be L. shift key make code
	KYBRD_ERR_ECHO_RET				=	0xEE,
	KYBRD_ERR_ACK					=	0xFA,
	KYBRD_ERR_BAT_FAILED			=	0xFC,
	KYBRD_ERR_DIAG_FAILED			=	0xFD,
	KYBRD_ERR_RESEND_CMD			=	0xFE,
	KYBRD_ERR_KEY					=	0xFF
};



void xn_handle_key_event (int code) {
	static bool _extended = false;
	//! is this an extended code? if yes, set it and return
		if (code == 0xE0 || code == 0xE1)
			_extended = true;
		else 
		{
			//! either the second byte of an extended scan code or a single byte scan code
			_extended = false;

			//! test if this is a break code (Original XT scan code set specific)
			if (code & 0x80)
			{
				//! convert the break code into its make code equivelant
				code -= 0x80;

				//! grab the key
				int key = _kkybrd_scancode_std [code];

				//! test if a special key has been released & set it
				switch (key)
				{
				case KEY_LCTRL:
				case KEY_RCTRL:
					_ctrl = false;
					break;

				case KEY_LSHIFT:
				case KEY_RSHIFT:
					_shift = false;
					break;

				case KEY_LALT:
				case KEY_RALT:
					_alt = false;
					break;
				}
			}
			else
			{
				_scancode = code;

				//! grab the key
				int key = _kkybrd_scancode_std [code];

				switch (key)
				{
				case KEY_LCTRL:
				case KEY_RCTRL:
					_ctrl = true;
					break;

				case KEY_LSHIFT:
				case KEY_RSHIFT:
					_shift = true;
					break;

				case KEY_LALT:
				case KEY_RALT:
					_alt = true;
					break;

				case KEY_CAPSLOCK:
					_capslock = (_capslock) ? false : true;
					break;

				case KEY_KP_NUMLOCK:
					_numlock = (_numlock) ? false : true;
				//	kybrd_set_leds (_numlock, _capslock, _scrolllock);
					break;

				case KEY_SCROLLLOCK:
					_scrolllock = (_scrolllock) ? false : true;
					//kybrd_set_leds (_numlock, _capslock, _scrolllock);
					break;
				}
			}
		}

		switch (code)
		{
		case KYBRD_ERR_BAT_FAILED:
			_kkybrd_bat_res = false;
			break;

		case KYBRD_ERR_DIAG_FAILED:
			_kkybrd_diag_res = false;
			break;

		case KYBRD_ERR_RESEND_CMD:
			_kkybrd_resend_res = true;
			break;

		}
}


//! get last key stroke
KEYCODE xn_get_last_key (){
	return (_scancode != INVALID_SCANCODE) ? ((KEYCODE) _kkybrd_scancode_std [_scancode]) : (KEY_UNKNOWN);
}

//! discards last scan
void  xn_discard_last_key (){
	_scancode = INVALID_SCANCODE;
}


//! get a keystoke
KEYCODE getch (){
	KEYCODE key = KEY_UNKNOWN;
	//while (key == KEY_UNKNOWN)
	key = xn_get_last_key ();
	xn_discard_last_key ();
	return key;
}



