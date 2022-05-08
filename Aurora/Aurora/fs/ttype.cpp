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

int master_count = 1;
int slave_count = 1;

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

	AuPmmngrFree(tty);
}

/**
 * ttype_master_read -- not implemented
 * @param file -- file node
 * @param buffer -- buffer to be used
 * @param length -- length to be used
 */
void ttype_master_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {
	//!Read it from out buffer
	vfs_node_t *node = get_current_thread()->fd[get_current_thread()->master_fd];
	ttype_t *type = (ttype_t*)node->device;
	/*for (int i = 0; i < 32; i++)
		buffer[i] = type->out_buffer[i];*/

}

/**
 * ttype_master_write -- child process writes text here using its stdout, stderr
 * @param file -- file node
 * @param buffer -- actual text buffer needs to be transferred
 * @param length -- length of the text
 */
void ttype_master_write (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	x64_cli();

	//! get the master node from the child process
	//vfs_node_t *node = get_current_thread()->fd[get_current_thread()->master_fd];
	//ttype_t *type = (ttype_t*)node->device;

	//! first of all, get the registered terminal emulator
	//! id, we need to unblock it, if it is blocked by default
	/*thread_t *dest = thread_iterate_ready_list(type->pid);
	if (dest == NULL)
		dest = thread_iterate_block_list(type->pid);*/

	//! check, if another data is already written to the
	//! buffer
	//if (type->written > 0)  {
		//! yes, the buffer is in use, let's wait for the
		//! buffer usage to be finished
		//type->blocked_pid = get_current_thread()->id;

		//! unblock the terminal emulator if it is blocked cause
		//! it will get the ttype buffer usage to be finished
		//if (dest != NULL && dest->state == THREAD_STATE_BLOCKED)
		//	unblock_thread(dest);

		////! block the current thread, till the buffer usage get over
		//block_thread(get_current_thread());
		//force_sched();
	//}


     //! unblock the terminal emulator, cause - new text is available to 
	//! be processed
	//if (dest != NULL && dest->state == THREAD_STATE_BLOCKED)
	//	unblock_thread(dest);

	////! so finally we now use the type buffer to store our text data
	//for (int i = 0; i < length; i++) {
	//	circular_buf_put(type->in_buffer,buffer[i]);
	//	//type->written++; //increament the written count, cause we only
	//	// read that much of text, that actually get written
	//}


	

}

/**
 * ttype_slave_read -- terminal emulator reads child process stdout and stderr from 
 * this interface
 * @param file -- file node
 * @param buffer -- memory location to store child process texts
 * @param length -- length to be used
 */
void ttype_slave_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {
	x64_cli();

	/* get the ttype */
	/*vfs_node_t *node = get_current_thread()->fd[get_current_thread()->slave_fd];
	ttype_t *type = (ttype_t*)node->device;*/

	//! lets read everything that has been written 
	//! by child, be carefull we only read that much
	//! that have been written by child process
	//for (int i = 0; i < type->written; i++) {
	//	circular_buf_get(type->in_buffer,(uint8_t*)&buffer[i]);
	//}

	//! resate the written count, so that child process
	//! can write its next data
	//type->written = 0;

	//! check if child process is blocked
	//if (type->blocked_pid > 0) {
		//! yes, than simply unblock it
	/*	thread_t *dest = thread_iterate_ready_list(type->blocked_pid);
		if (dest == NULL)
			dest = thread_iterate_block_list(type->blocked_pid);

		if (dest != NULL && dest->state == THREAD_STATE_BLOCKED)
			unblock_thread(dest);*/
	//}

	
}

void ttype_slave_write (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	vfs_node_t *node = get_current_thread()->fd[get_current_thread()->slave_fd];
	ttype_t *type = (ttype_t*)node->device;
	/*for (int i = 0; i < 32; i++)
		type->out_buffer[i] = buffer[i];*/
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

int ttype_create (int* master_fd, int* slave_fd) {
	x64_cli();

	/** The malloc needs fixings, that's why there
	 ** are limited number of pty
	 **/
	/*if (master_count > 3)
		return -1;*/

	ttype_t *tty= (ttype_t*)malloc(sizeof(ttype_t));  //pmmngr_alloc();

	void* inbuffer = AuPmmngrAlloc();
	memset(inbuffer, 0, 4096);
	void* outbuffer = AuPmmngrAlloc();
	memset(outbuffer, 0, 4096);

	tty->in_buffer = circ_buf_init((uint8_t*)inbuffer,4095);
	tty->out_buffer = circ_buf_init((uint8_t*)outbuffer, 4095);
	//
	tty->id = slave_count;

	//! tty->pid -- stores the current terminal emulator id

	//! Create the namings
	char mname[10];
	strcpy (mname, "/dev/");
	strcpy (mname+5, "ttym");
	sztoa (master_count,mname+9,10);



	//////! Master node
	vfs_node_t *mn = (vfs_node_t*)malloc(sizeof(vfs_node_t));  //pmmngr_alloc();
	strcpy(mn->filename, mname+5);
	mn->size = 0;
	mn->eof = 0;
	mn->pos = 0;
	mn->current = 0;
	mn->flags = FS_FLAG_GENERAL;
	mn->status = 0;
	mn->open = 0;
	mn->device = tty;
	mn->read = ttype_master_read;
	mn->write = ttype_master_write;
	mn->read_blk = 0;
	mn->ioquery = 0;

	_debug_print_ ("[TTY]: Master node mounted at -> %s  \r\n", mname);

	char sname[10];
	strcpy (sname, "/dev/");
	strcpy (sname+5, "ttys");
	sztoa (slave_count,sname+9,10);

	vfs_node_t *sn = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy(sn->filename, sname);
	sn->size = 0;
	sn->eof = 0;
	sn->pos = 0;
	sn->current = 0;
	sn->flags = FS_FLAG_GENERAL;
	sn->status = 0;
	sn->open = 0;
	sn->device = tty;
	sn->read = ttype_slave_read;
	sn->write = ttype_slave_write;
	sn->read_blk = 0;
	sn->ioquery = 0;
	vfs_mount (sname, sn, 0);

	_debug_print_ ("[TTY]: Slave node mounted at %s \r\n", sname);
	
	/*for (int i = 0; i < 32; i++) {
		tty->m_path[i] = mname[i];
		tty->s_path[i] = sname[i];
	}*/
		
	tty->controlling_pid = 0;
	tty->foreground_pid = 0;

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

	//! Allocate fd for master
	int m_fd = get_current_thread()->fd_current;
	get_current_thread()->fd[m_fd] = mn;
	get_current_thread()->fd_current++;

	//! Allocate fd for slave
	int s_fd = get_current_thread()->fd_current;
	get_current_thread()->fd[s_fd] = sn;
	get_current_thread()->fd_current++;

	get_current_thread()->master_fd = m_fd;
	get_current_thread()->slave_fd = s_fd;

	get_current_thread()->fd[1] = mn;
	get_current_thread()->fd[2] = mn;

	//tty->master_fd = 0; //m_fd;
	//tty->slave_fd = 0; //s_fd;

	//_debug_print_ ("TTY Created \r\n");

	_debug_print_ ("Used RAM -> %d MB/ Total RAM %d MB\r\n", pmmngr_get_used_ram() / 1024 / 1024, pmmngr_get_total_ram() / 1024 / 1024);

	ttype_insert (tty);
	master_count++;
	slave_count++;
	*master_fd = m_fd;
	*slave_fd = s_fd;
	return 0;
}

void ttype_dup_master (int task_id, int master_fd) {
	x64_cli();
	vfs_node_t *node = get_current_thread()->fd[master_fd];
	thread_t *dest = thread_iterate_ready_list(task_id);
	if (dest == NULL) {
		dest = thread_iterate_block_list(task_id);
	}
	if (dest != NULL) {
		dest->fd[1] = node;
		dest->fd[2] = node;
	}
	dest->master_fd = 1;
}


void ttype_init () {
	root = NULL;
	last = NULL;
	master_count = 1;
	slave_count = 1;
}