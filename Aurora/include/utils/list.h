/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  lnklist.h -- Linked list 
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <stdint.h>
#include <_null.h>

typedef struct _listnode_ {
	struct _listnode_ *prev;
	struct _listnode_ *next;
	void* val;
}listnode_t;

typedef struct _Llist_ {
	listnode_t* head;
	listnode_t* tail;
	uint32_t size;
}Llist_t;


#define foreach(t, list)  for(listnode_t * t = list->head; t != NULL; t = t->next)

Llist_t * list_create();

uint32_t list_size(Llist_t * list);

listnode_t * list_insert_front(Llist_t * list, void * val);

void list_insert_back(Llist_t * list, void * val);

void * list_remove_node(Llist_t * list, listnode_t * node);

void * list_remove_front(Llist_t * list);

void * list_remove_back(Llist_t * list);

void list_push(Llist_t * list, void * val);

listnode_t * list_pop(Llist_t * list);

void list_enqueue(Llist_t * list, void * val);

listnode_t * list_dequeue(Llist_t * list);

void * list_peek_front(Llist_t * list);

void * list_peek_back(Llist_t * list);

void list_destroy(Llist_t * list);

void listnode_destroy(listnode_t * node);

int list_contain(Llist_t * list, void * val);

listnode_t * list_get_node_by_index(Llist_t * list, int index);

void * list_remove_by_index(Llist_t * list, int index);

#endif