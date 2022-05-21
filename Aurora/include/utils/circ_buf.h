///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  circ_buf -- Circular Buffer
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#ifndef __CIRC_BUF_H__
#define __CIRC_BUF_H__

#include <stdint.h>

typedef struct _circ_buf_ {
	uint8_t *buffer;
	size_t head;
	size_t tail;
	size_t max;
	bool full;
}circ_buf_t;

extern void advance_pointer (circ_buf_t *cbuf);
extern void retreat_pointer (circ_buf_t *cbuf);
extern void circ_buf_reset (circ_buf_t *cbuf);
extern circ_buf_t *circ_buf_init (unsigned char* buffer, size_t size);
extern void circ_buf_free (circ_buf_t *cbuf);
extern size_t circular_buf_size(circ_buf_t *cbuf);
extern size_t circular_buf_capacity(circ_buf_t *cbuf);
extern void circular_buf_put(circ_buf_t *cbuf,uint8_t data);
extern int circular_buf_put2(circ_buf_t *cbuf, uint8_t data);
extern int circular_buf_get(circ_buf_t *cbuf, uint8_t *data);
extern int circular_buf_get2(circ_buf_t *cbuf, int *data);
extern bool circular_buf_empty(circ_buf_t *cbuf);
extern bool circular_buf_full(circ_buf_t *cbuf);


#endif