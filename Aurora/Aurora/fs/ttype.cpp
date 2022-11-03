/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @ttype.cpp -- tele type driver
 *
 **/

#include <fs\ttype.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <stdio.h>
#include <arch\x86_64\thread.h>
#include <serial.h>
#include <error.h>

/**
 * DESIGN: Terminal emulator process creates a ttype object
 * which provides to file descriptor -- master and slave
 * master accept text from child processes while slave 
 * is for terminal to handle incoming text, if a new process
 * is created from inside terminal, the terminal automatically
 * copies the master to childs stdout, stderr. If child writes
 * to stdout or stderr it get transferred to master fd which is
 * transferred to slave fd of terminal emulator and finally
 * terminal emulator displays the text of written by child process
 * to screen
 */

int master_count=0;
int slave_count=0;

ttype_t *root = NULL;
ttype_t *last = NULL;


void ttype_insert (ttype_t* tty ) {
	tty->next = NULL;
	tty->prev = NULL;

	if (root == NULL) {
		last = tty;
		root = tty;
		//_debug_print_ ("**TTY ROOT WAS NULL \r\n");
	} else {
		last->next = tty;
		tty->prev = last;
	}
	last = tty;
}


void ttype_delete (ttype_t* tty) {

	if (root == NULL)
		return;

	if (tty == root) {
		root = root->next;
	} else {
		tty->prev->next = tty->next;
	}

	if (tty == last) {
		last = tty->prev;
	} else {
		tty->next->prev = tty->prev;
	}

	free(tty);
}

/**
 * ttype_master_read -- not implemented
 * @param file -- file node
 * @param buffer -- buffer to be used
 * @param length -- length to be used
 */
size_t ttype_master_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {
	//!Read it from out buffer
	ttype_t *type = (ttype_t*)file->device;

	size_t bytes_to_ret = 0;
	uint8_t* aligned_buffer = (uint8_t*)buffer;

	if (circular_buf_empty(type->master_buffer))
		return bytes_to_ret;

	for (int i = 0; i < type->master_written; i++) {
		circular_buf_get(type->master_buffer,&aligned_buffer[i]);
		bytes_to_ret++;
	}
	type->master_written = 0;

	return bytes_to_ret;
}

/**
 * ttype_master_write -- child process writes text here using its stdout, stderr
 * @param file -- file node
 * @param buffer -- actual text buffer needs to be transferred
 * @param length -- length of the text
 */
void ttype_master_write (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	x64_cli();

	uint8_t* aligned_buffer = (uint8_t*)buffer;
	//! get the master node from the child process
	ttype_t *type = (ttype_t*)file->device;

	//! so finally we now use the type buffer to store our text data
	for (int i = 0; i < length; i++) {
		circular_buf_put2(type->slave_buffer,buffer[i]);
	}
}

/**
 * ttype_slave_read -- terminal emulator reads child process stdout and stderr from 
 * this interface
 * @param file -- file node
 * @param buffer -- memory location to store child process texts
 * @param length -- length to be used
 */
size_t ttype_slave_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {
	x64_cli();
	uint8_t* aligned_buffer = (uint8_t*)buffer;
	/* get the ttype */
	ttype_t *type = (ttype_t*)file->device;

	//! lets read everything that has been written 
	//! by child, be carefull we only read that much
	//! that have been written by child process
	for (int i = 0; i < length; i++) {
		circular_buf_get(type->slave_buffer,&aligned_buffer[i]);
	}

	return 1;
}

void ttype_slave_write (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	x64_cli();
	uint8_t* aligned_buffer = (uint8_t*)buffer;
	ttype_t *type = (ttype_t*)file->device;
	if (length > 512)
		length = 512;

	if (circular_buf_full(type->master_buffer)){
		return;
	}
	for (int i = 0; i < length; i++) {
		circular_buf_put2(type->master_buffer,aligned_buffer[i]);
		type->master_written++;
	}
}

ttype_t * get_ttype (int id) {
	if (root != NULL){
		for (ttype_t* tty = root; tty != NULL; tty = tty->next) {
			if (tty->id == id) 
				return tty;
		}
	}
	return NULL;
}


/*
 * tty_ioquery -- IoQuery Commands for ttype
 * @param file -- Pointer to tty file
 * @param code -- code
 * @param arg -- Additional Arguments
 */
int tty_ioquery (vfs_node_t *file, int code, void *arg){
	x64_cli();
	ttype_t *tty = (ttype_t*)file->device;

	switch(code) {
	case TIOCSWINSZ: {
		winsize_t *sz = (winsize_t*)arg;
		tty->size.ws_col = sz->ws_col;
		tty->size.ws_row = sz->ws_row;
		tty->size.ws_xpixel = sz->ws_xpixel;
		tty->size.ws_ypixel = sz->ws_ypixel;
		break;
    }
	case TIOCGWINSZ:{
		winsize_t *sz = (winsize_t*)arg;
		sz->ws_col = tty->size.ws_col;
		sz->ws_row = tty->size.ws_row;
		sz->ws_xpixel = tty->size.ws_xpixel;
		sz->ws_ypixel = tty->size.ws_ypixel;
		break;
	}

	case TIOSPGRP: {
		tty->slave_pid = get_current_thread()->id;
		break;
	}
	}

	return AU_SUCCESS;
}

/*
 * ttype_create_master -- creates a master device file
 * @param tty -- Pointer to ttype structure
 */
vfs_node_t* ttype_create_master (ttype_t *tty) {

	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	char mname[10];
	strcpy (mname, "/dev/");
	strcpy (mname+5, "ttym");
	sztoa (master_count,mname+9,10);
	master_count++;
	strcpy(node->filename, mname+5);

	node->size = 512;
	node->eof = 0;
	node->pos = 0;
	node->current = 0;
	node->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;
	node->status = 0;
	node->open = 0;
	node->device = tty;
	node->read = ttype_master_read;
	node->write = ttype_master_write;
	node->read_blk = 0;
	node->ioquery = tty_ioquery;

	vfs_mount(mname,node,0);
	return node;
}


/*
 * ttype_create_slave -- creates a slave device file
 * @param tty -- Pointer to ttype structure
 */
vfs_node_t* ttype_create_slave (ttype_t *tty) {

	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	char sname[10];
	strcpy (sname, "/dev/");
	strcpy (sname+5, "ttys");
	sztoa (slave_count,sname+9,10);
	slave_count++;
	strcpy(node->filename, sname+5);

	node->size = 512;
	node->eof = 0;
	node->pos = 0;
	node->current = 0;
	node->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;
	node->status = 0;
	node->open = 0;
	node->device = tty;
	node->read = ttype_slave_read;
	node->write = ttype_slave_write;
	node->read_blk = 0;
	node->ioquery = tty_ioquery;

	vfs_mount(sname,node,0);
	return node;
}


/*
 * ttype_create -- creates a new tele type structure
 * @param master_fd -- master file descriptor
 * @param slave_fd -- slave file descriptor
 */
int ttype_create (int* master_fd, int* slave_fd) {
	x64_cli();

	ttype_t *tty= (ttype_t*)malloc(sizeof(ttype_t)); 
	void* inbuffer = malloc(512);
	memset(inbuffer, 0, 512);
	void* outbuffer = malloc(512);
	memset(outbuffer, 0, 512);

	tty->master_buffer = circ_buf_init((uint8_t*)inbuffer,512);
	tty->slave_buffer = circ_buf_init((uint8_t*)outbuffer,512);
	tty->id = slave_count;
	tty->master_written = 0;
	tty->slave_written = 0;

	tty->term.c_iflag = ICRNL | BRKINT;
	tty->term.c_oflag = ONLCR | OPOST;
	tty->term.c_lflag = ECHO | ECHOE | ECHOK | ICANON | ISIG | IEXTEN;
	tty->term.c_cflag = CREAD | CS8;
	tty->term.c_cc[VEOF] = 4;
	tty->term.c_cc[VEOL] = 0;
	tty->term.c_cc[VERASE] = 0x7f;
	tty->term.c_cc[VINTR] = 3;
	tty->term.c_cc[VKILL] = 21;
	tty->term.c_cc[VMIN] = 1;
	tty->term.c_cc[VQUIT] = 28;
	tty->term.c_cc[VSTART] = 17;
	tty->term.c_cc[VSTOP] = 19;
	tty->term.c_cc[VSUSP] = 26;
	tty->term.c_cc[VTIME] = 0;
	tty->term.c_cc[VLNEXT] = 22;
	tty->term.c_cc[VWERASE] = 23;

	tty->size.ws_col = 25;
	tty->size.ws_row = 80;

	tty->master_pid = get_current_thread()->id;
	tty->slave_pid = 0;

	vfs_node_t * master = ttype_create_master(tty);
	vfs_node_t * slave = ttype_create_slave(tty);

	//! Allocate fd for master
	int m_fd = get_current_thread()->fd_current;
	get_current_thread()->fd[m_fd] = master;
	get_current_thread()->fd_current++;

	//! Allocate fd for slave
	int s_fd = get_current_thread()->fd_current;
	get_current_thread()->fd[s_fd] = slave;
	get_current_thread()->fd_current++;


	get_current_thread()->fd[1] = master;
	get_current_thread()->fd[2] = master;

	ttype_insert (tty);
	*master_fd = m_fd;
	*slave_fd = s_fd;
	return 0;
}


void AuTTypeInit () {
	root = NULL;
	last = NULL;
	master_count = 1;
	slave_count = 1;
}