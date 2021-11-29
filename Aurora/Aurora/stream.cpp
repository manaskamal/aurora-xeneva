///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   stream.cpp -- Stream 
///!
///!   /PROJECT - Aurora's Xeneva v1.0
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!====================================================

#include <stream.h>
#include <mm.h>
#include <string.h>
#include <fs\vfs.h>
#include <_null.h>
#include <arch\x86_64\thread.h>
#include <proc.h>
#include <fs\ttype.h>

stream_t *allocate_stream () {
	stream_t *st = (stream_t*)pmmngr_alloc();   //malloc (sizeof(stream_t));
	memset (st, 0, sizeof(stream_t));
	return st;
}


void deallocate_stream (stream_t *st) {
	mfree(st);
}



void stdout (stream_t *st, char* buff) {
	memcpy (st->out, buff, strlen(buff));
}


void stdin (stream_t* st, char* key) {
	memcpy (st->in, key, strlen(key));
}


void stderr (stream_t* st, char* err) {
	memcpy (st->err, err,sizeof(err));
}


void stdout_read (vfs_node_t *file, uint8_t* buffer,uint32_t length) {
	thread_t *p = get_current_thread();
	memcpy (buffer, p->stream->out,32);
}

void stdout_write (vfs_node_t *file, uint8_t* buffer, uint32_t length) {
	thread_t *p = get_current_thread();
	memcpy(p->stream->out,buffer, 32);
	if (p->ttype) {
		ttype_t *t = get_ttype(p->ttype);
		if (t)
			memcpy (t->in_buffer,buffer, 32);
	}
}

void stderr_read (vfs_node_t *file, uint8_t* buffer,uint32_t length) {
	thread_t *p = get_current_thread();
	memcpy (buffer, p->stream->err, 32);
}

void stderr_write (vfs_node_t *file, uint8_t* buffer, uint32_t length) {
	thread_t *p = get_current_thread();
	memcpy (p->stream->err, buffer, 32);
	if (p->ttype) {
		ttype_t *t = get_ttype(p->ttype);
		if (t) {
			memcpy (t->in_buffer,buffer, 32);
		}
	}
}

//! Initialize and register the stream device
void stream_init () {

	///! Standard Input 
	///! node
	vfs_node_t *stdin = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy(stdin->filename, "stdin");
	stdin->size = 0;
	stdin->eof = 0;
	stdin->pos = 0;
	stdin->current = 0;
	stdin->flags = FS_FLAG_GENERAL;
	stdin->status = 0;
	stdin->open = 0;
	stdin->read = 0;
	stdin->write = 0;
	stdin->read_blk = 0;
	stdin->ioquery = 0;
	vfs_mount ("/dev/stdin", stdin);

	///! Standard output 
	///! node
	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy(node->filename, "stdout");
	node->size = 0;
	node->eof = 0;
	node->pos = 0;
	node->current = 0;
	node->flags = FS_FLAG_GENERAL;
	node->status = 0;
	node->open = 0;
	node->read = stdout_read;
	node->write = stdout_write;
	node->read_blk = 0;
	node->ioquery = 0;
	vfs_mount ("/dev/stdout", node);

	///! Standard Error 
	///! node
	vfs_node_t *stderr = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy(stderr->filename, "stderr");
	stderr->size = 0;
	stderr->eof = 0;
	stderr->pos = 0;
	stderr->current = 0;
	stderr->flags = FS_FLAG_GENERAL;
	stderr->status = 0;
	stderr->open = 0;
	stderr->read = stderr_read;
	stderr->write = stderr_write;
	stderr->read_blk = 0;
	stderr->ioquery = 0;
	vfs_mount ("/dev/stderr", stderr);
}
