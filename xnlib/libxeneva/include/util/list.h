/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  list.h -- List datastructure for XNWidget Library
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ======================================================
 */

#ifndef __LIST_H__
#define __LIST_H__

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