///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  circ_buf -- Circular Buffer
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#include <utils\circ_buf.h>
#include <arch\x86_64\mmngr\kheap.h>

void advance_pointer (circ_buf_t *cbuf) {
	if (cbuf->full)
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;

	cbuf->head = (cbuf->head + 1) % cbuf->max;

	cbuf->full = (cbuf->head == cbuf->tail);
}


void retreat_pointer (circ_buf_t *cbuf) {
	cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->max;
}

void circ_buf_reset (circ_buf_t *cbuf) {
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->full = false;
}

circ_buf_t *circ_buf_init (uint8_t* buffer, size_t size) {
	circ_buf_t *cbuf = (circ_buf_t*)malloc(sizeof(circ_buf_t));
	cbuf->buffer = buffer;
	cbuf->max = size;
	circ_buf_reset (cbuf);

	return cbuf;
}

void circ_buf_free (circ_buf_t *cbuf) {
	free(cbuf);
}

size_t circular_buf_size(circ_buf_t *cbuf)
{
	size_t size = cbuf->max;

	if (!cbuf->full)
	{
		if (cbuf->head >= cbuf->tail)
		{
			size = (cbuf->head - cbuf->tail);
		}
		else
		{
			size = (cbuf->max + cbuf->head - cbuf->tail);
		}
	}

	return size;
}

size_t circular_buf_capacity(circ_buf_t *cbuf)
{
	return cbuf->max;
}

void circular_buf_put(circ_buf_t *cbuf, uint8_t data)
{
	cbuf->buffer[cbuf->head] = data;

	advance_pointer(cbuf);
}

int circular_buf_put2(circ_buf_t *cbuf, int data)
{
	int r = -1;

	if (!circular_buf_full(cbuf))
	{
		cbuf->buffer[cbuf->head] = data;
		advance_pointer(cbuf);
		r = 0;
	}

	return r;
}

int circular_buf_get(circ_buf_t *cbuf, uint8_t *data)
{
	int r = -1;

	if (!circular_buf_empty(cbuf))
	{
		*data = cbuf->buffer[cbuf->tail];
		retreat_pointer(cbuf);

		r = 0;
	}

	return r;
}

bool circular_buf_empty(circ_buf_t *cbuf)
{
	return (!cbuf->full && (cbuf->head == cbuf->tail));
}

bool circular_buf_full(circ_buf_t *cbuf)
{
	return cbuf->full;
}


