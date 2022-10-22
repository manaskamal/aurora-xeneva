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
#include <aurora.h>

typedef struct _data_ {
	_data_ *next;
	_data_ *prev;
	void* data;
}dataentry;


typedef struct _list_ {
	unsigned int pointer;
	dataentry *entry_current;
}list_t;

AU_EXTERN AU_EXPORT list_t* initialize_list();
AU_EXTERN AU_EXPORT void list_add (list_t* list, void* data);
AU_EXTERN AU_EXPORT void* list_remove(list_t* list, unsigned int);
AU_EXTERN AU_EXPORT void * list_get_at(list_t* list, unsigned int index);
#endif