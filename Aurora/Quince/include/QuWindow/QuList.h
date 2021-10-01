///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuList.h -- Quince List
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================


#ifndef __QU_LIST_H__
#define __QU_LIST_H__



typedef struct _data_ {
	_data_ *next;
	_data_ *prev;
	void* data;
}dataentry;


typedef struct _qulist_ {
	unsigned int pointer;
	dataentry *entry_current;
}QuList;

extern QuList* QuListInit();
extern void QuListAdd (QuList* list, void* data);
extern void QuListRemove(QuList* list, unsigned int);
extern void * QuListGetAt(QuList* list, unsigned int index);


#endif