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

QuTextbox *tb;

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
int operator_type = 0;
int input_1 = 0;
int input_2 = 0;
int num_one[100];
int num_two[100];
int pos_input = 0;
int pos_input_2 = 0;


void RegisterObject (QuTextbox *_tb) {
	tb = _tb;
}

void OneClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb, "1");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);

	QuButtonAckAction(but);
}


void TwoClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb, "2");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);

	QuButtonAckAction(but);
}
void ThreeClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb, "3");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);

	QuButtonAckAction(but);
}
void FourClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb, "4");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);

	QuButtonAckAction(but);
}
void FiveClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb, "5");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);

	QuButtonAckAction(but);
}
void SixClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb, "6");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);

	QuButtonAckAction(but);
}
void SevenClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb, "7");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);

	QuButtonAckAction(but);
}
void EightClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb, "8");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);
	QuButtonAckAction(but);
}
void NineClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb, "9");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);

	QuButtonAckAction(but);
}
void ZeroClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	QuTextboxAppendText(tb,"0");
	QuTextboxRefresh(tb,win);
	QuTextboxInvalidate(tb,win);

	QuButtonAckAction(but);
}


void AddClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	input_1 = atoi(tb->text);
	operator_type = ADD;
	memset(tb->text, 0, 512);
	QuTextboxRefresh(tb, win);
	QuTextboxInvalidate(tb, win);

	QuButtonAckAction(but);

}

void MulClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	input_1 = atoi(tb->text);
	operator_type = MUL;
	memset(tb->text, 0, 512);
	QuTextboxRefresh(tb, win);
	QuTextboxInvalidate(tb, win);

	QuButtonAckAction(but);
}

void SubClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	input_1 = atoi(tb->text);
	operator_type = SUB;
	memset(tb->text, 0, 512);
	QuTextboxRefresh(tb, win);
	QuTextboxInvalidate(tb, win);

	QuButtonAckAction(but);
}

void DivClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	input_1 = atoi(tb->text);
	operator_type = DIV;
	memset(tb->text, 0, 512);
	QuTextboxRefresh(tb, win);
	QuTextboxInvalidate(tb, win);

	QuButtonAckAction(but);
}

void EqClicked (QuWidget *wid, QuWindow *win) {
	QuButton *but = (QuButton*)wid;

	input_2 = atoi(tb->text);
	int output = 0;
	if (input_1 != 0 && input_2 != 0) {
		switch(operator_type) {
		case ADD:
			output = input_1 + input_2;
			break;
		case SUB:
			output = input_1 - input_2;
			break;
		case MUL:
			output = input_1 * input_2;
			break;
		case DIV:
			output = input_1 / input_2;
			break;
		}
	}

	char out[250];
	memset(out, 0, 250);
	sztoa (output, out, 10);
	QuEnterText(tb, out);
	QuTextboxRefresh(tb, win);
	QuTextboxInvalidate(tb, win);
	output = 0;

	QuButtonAckAction(but);
}


void ClearClicked (QuWidget *wid, QuWindow *win){

	QuButton *but = (QuButton*)wid;

	input_1 = 0;
	input_2 = 0;
	memset(tb->text, 0, 512);
	operator_type = 0;
	QuTextboxRefresh(tb, win);
	QuTextboxInvalidate(tb, win);

	QuButtonAckAction(but);
}