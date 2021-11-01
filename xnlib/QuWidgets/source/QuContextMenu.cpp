///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuContextMenu.h -- Quince Context (Popup) Menu
///!
///!  /PROJECT - Aurora's Xeneva v1.0
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!====================================================

#include <QuContextMenu.h>
#include <stdlib.h>

QuContextMenu *QuCreateContextMenu(char *title) {
	QuContextMenu *ctx = (QuContextMenu*)malloc(sizeof(QuContextMenu));
	ctx->title = title;
	return ctx;
}