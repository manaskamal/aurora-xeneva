///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury 2021
///!
///!=============================================

#include <QuBase.h>
#include <QuWindow.h>
#include <sys\_ipc.h>
#include <string.h>
#include <stdlib.h>
#include <acrylic.h>
#include <sys\_wait.h>
#include <QuButton.h>
#include <color.h>
#include <QuPanel.h>
#include <QuTextbox.h>
#include "actions.h"



void QuActions (QuMessage *msg) {
	if (msg->type == QU_CANVAS_MOVE) {
		QuWindowMove(msg->dword, msg->dword2);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_RESIZE) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_DESTROYED) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_MOUSE_LCLICKED) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_MOUSE_LRELEASE) {
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_MOUSE_MOVE) {
		QuWindowHandleMouse(msg->dword, msg->dword2, msg->dword3);
		memset(msg, 0, sizeof(QuMessage));
	}

	if (msg->type == QU_CANVAS_KEY_PRESSED) {
		memset(msg, 0, sizeof(QuMessage));
	}
	
	//QuPanelContentUpdate(QuGetWindow()->x, QuGetWindow()->y, QuGetWindow()->w, QuGetWindow()->h);

}

void AboutClicked (QuWidget *wid, QuWindow *win) {
}

int main (int argc, char* argv[]) {
	QuRegisterApplication ("Calculator");
	QuWindow* win = QuGetWindow();
	win->title = "Calculator-beta";

	QuPanel *panel = QuCreatePanel();
	QuPanelSetBackground (panel, 0x59FFFFFF);
	QuWindowAdd((QuWidget*)panel);

	QuTextbox *text = QuCreateTextbox(10,28, win->w - 20,30);
	QuWindowAdd((QuWidget*)text);
	
	RegisterObject(text);


	QuButton *one = QuCreateButton (10,80);
	QuButtonSetText(one,"1");
	QuButtonSetActionHandler (one, OneClicked);
	QuWindowAdd ((QuWidget*)one);

	QuButton *two = QuCreateButton (170, 80);
	QuButtonSetText(two, "2");
	QuButtonSetActionHandler (two, TwoClicked);
	QuWindowAdd ((QuWidget*)two);

	QuButton *three = QuCreateButton (165 + 165, 80);
	QuButtonSetText(three, "3");
	QuButtonSetActionHandler (three, ThreeClicked);
	QuWindowAdd ((QuWidget*)three);

	QuButton *four = QuCreateButton (10, 120);
	QuButtonSetText(four, "4");
	QuButtonSetActionHandler (four, FourClicked);
	QuWindowAdd ((QuWidget*)four);

	QuButton *five = QuCreateButton (170, 120);
	QuButtonSetText(five, "5");
	QuButtonSetActionHandler (five, FiveClicked);
	QuWindowAdd ((QuWidget*)five);

	QuButton *six = QuCreateButton (165 + 165, 120);
	QuButtonSetText(six, "6");
	QuButtonSetActionHandler (six, SixClicked);
	QuWindowAdd ((QuWidget*)six);

	QuButton *seven = QuCreateButton (10, 160);
	QuButtonSetText(seven, "7");
	QuButtonSetActionHandler (seven, SevenClicked);
	QuWindowAdd ((QuWidget*)seven);

	QuButton *eight = QuCreateButton (170, 160);
	QuButtonSetText(eight, "8");
	QuButtonSetActionHandler (eight, EightClicked);
	QuWindowAdd ((QuWidget*)eight);

	QuButton *nine= QuCreateButton (165 + 165, 160);
	QuButtonSetText(nine, "9");
	QuButtonSetActionHandler (nine, NineClicked);
	QuWindowAdd ((QuWidget*)nine);

	QuButton *zero = QuCreateButton (170, 200);
	QuButtonSetText(zero, "0");
	QuButtonSetActionHandler (zero, ZeroClicked);
	QuWindowAdd ((QuWidget*)zero);


	QuButton *mult = QuCreateButton (10, 200);
	QuButtonSetText(mult, "*");
	QuButtonSetActionHandler (mult, MulClicked);
	QuWindowAdd ((QuWidget*)mult);

	QuButton *div = QuCreateButton (165 + 165, 200);
	QuButtonSetText(div, "/");
	QuButtonSetActionHandler (div, DivClicked);
	QuWindowAdd ((QuWidget*)div);

	QuButton *add = QuCreateButton (10, 250);
	QuButtonSetText(add, "+");
	QuButtonSetActionHandler (add, AddClicked);
	QuWindowAdd ((QuWidget*)add);

	QuButton *sub = QuCreateButton (170, 250);
	QuButtonSetText(sub, "-");
	QuButtonSetActionHandler (sub, SubClicked);
	QuWindowAdd ((QuWidget*)sub);


	QuButton *eq = QuCreateButton (165 + 165, 250);
	QuButtonSetText(eq, "=");
	QuButtonSetActionHandler (eq, EqClicked);
	QuWindowAdd ((QuWidget*)eq);


	QuButton *clear = QuCreateButton (170, 290);
	QuButtonSetText(clear, "C");
	QuButtonSetActionHandler (clear, ClearClicked);
	QuWindowAdd ((QuWidget*)clear);


	QuWindowShow();

	QuMessage qmsg;
	uint16_t app_id = QuGetAppId();
	message_t msg;
	while(1) {
		QuChannelGet(&qmsg);

		if (qmsg.to_id == app_id)
			QuActions(&qmsg);
		
		sys_wait();
	}	
	return 1;
}