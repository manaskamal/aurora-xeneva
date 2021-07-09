/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT - DWM {Desktop Window Manager}
 *  /AUTHOR  - Manas Kamal Choudhury
 * ===============================================
 */

#ifndef __WIN_H__
#define __WIN_H__

#include <stdtypes.h>

typedef struct _data_ {
	_data_ *next;
	_data_ *prev;
	void* data;
}dataentry;


typedef struct _winlist_ {
	unsigned int pointer;
	dataentry *entry_current;
}winlist;

extern winlist* initialize_winlist();
extern void win_list_add (winlist* list, void* data);
extern void* win_list_remove(winlist* list, unsigned int);
extern void * win_list_get_at(winlist* list, unsigned int index);
#endif