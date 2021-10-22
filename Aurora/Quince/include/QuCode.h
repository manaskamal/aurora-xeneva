///!
///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuCode -- Quince Message Codes
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!==================================================


#ifndef __QU_CODE_H__
#define __QU_CODE_H__

//! Codes that are being send to Quince
#define QU_CODE_WIN_CREATE   100
#define QU_CODE_WIN_DESTROY  101
#define QU_CODE_WIN_MINIMIZE 102
#define QU_CODE_WIN_MAXIMIZE 103
#define QU_CODE_DIRTY_UPDATE 104
#define QU_CODE_WIN_CONFIG   105
#define QU_CODE_REPAINT      106
#define QU_CODE_WIN_CLOSE    107

//! Codes that are sent by Quince to clients
#define QU_CANVAS_READY  200
#define QU_CANVAS_DESTROYED 201
#define QU_CANVAS_MOVE  202
#define QU_CANVAS_MOUSE_MOVE 203
#define QU_CANVAS_MOUSE_LCLICKED 204
#define QU_CANVAS_MOUSE_LRELEASE 205
#define QU_CANVAS_KEY_PRESSED  206
#define QU_CANVAS_KEY_RELEASED 207
#define QU_CANVAS_RESIZE 208
#define QU_CANVAS_REPAINT 209
#endif