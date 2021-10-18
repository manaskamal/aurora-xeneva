/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  lnklist.h -- Linked list 
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 /
 /**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT - DWM {Desktop Window Manager}
 *  /AUTHOR  - Manas Kamal Choudhury
 * ===============================================
 */

#ifndef __WIN_H__
#define __WIN_H__

#include <stdint.h>

typedef struct _data_ {
	_data_ *next;
	_data_ *prev;
	void* data;
}dataentry;


typedef struct _list_ {
	unsigned int pointer;
	dataentry *entry_current;
}list_t;

extern list_t* initialize_list();
extern void list_add (list_t* list, void* data);
extern void* list_remove(list_t* list, unsigned int);
extern void * list_get_at(list_t* list, unsigned int index);
#endif