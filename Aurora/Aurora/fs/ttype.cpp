
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
#include <mm.h>
#include <stdio.h>
#include <arch\x86_64\thread.h>



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

	pmmngr_free (tty);
}

void ttype_master_read (vfs_node_t *file, uint8_t* buffer,uint32_t length) {
	//!Read it from out buffer
	vfs_node_t *node = get_current_thread()->fd[get_current_thread()->master_fd];
	ttype_t *type = (ttype_t*)node->device;
	for (int i = 0; i < 32; i++)
		buffer[i] = type->out_buffer[i];

}

void ttype_master_write (vfs_node_t *file, uint8_t* buffer, uint32_t length) {
	vfs_node_t *node = get_current_thread()->fd[get_current_thread()->master_fd];
	ttype_t *type = (ttype_t*)node->device;
	for (int i = 0; i < 32; i++)
		type->in_buffer[i] = buffer[i];
	
	thread_t *dest = thread_iterate_ready_list(type->pid);
	if (dest == NULL)
		dest = thread_iterate_block_list(type->pid);

	if (dest != NULL && dest->state == THREAD_STATE_BLOCKED)
		unblock_thread(dest);
}

void ttype_slave_read (vfs_node_t *file, uint8_t* buffer,uint32_t length) {
	vfs_node_t *node = get_current_thread()->fd[get_current_thread()->slave_fd];
	ttype_t *type = (ttype_t*)node->device;
	for (int i = 0; i < 32; i++) {
		buffer[i] = type->in_buffer[i];
		//type->in_buffer[i] = 0;
	}
	/*if (buffer[1] != 0)*/
	memset(type->in_buffer, 0, 32);
}

void ttype_slave_write (vfs_node_t *file, uint8_t* buffer, uint32_t length) {
	vfs_node_t *node = get_current_thread()->fd[get_current_thread()->slave_fd];
	ttype_t *type = (ttype_t*)node->device;
	for (int i = 0; i < 32; i++)
		type->out_buffer[i] = buffer[i];
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

void ttype_create (int* master_fd, int* slave_fd) {
	ttype_t *tty= (ttype_t*)pmmngr_alloc();
	memset (tty, 0, 4096);
	memset (tty->in_buffer, 0, 32);
	memset (tty->out_buffer, 0, 32);
	tty->id = slave_count;
	tty->pid = get_current_thread()->id;
	///! Create the namings
	char m_value[2];
	char s_value[2];

	sztoa(master_count, m_value,10);
	sztoa(slave_count, s_value,10);

	char master_name[10];
	strcpy(master_name, "ttym");
	strcpy (master_name + strlen(master_name)-1, m_value);
	
	char mname[10];
	strcpy (mname, "/dev/");
	strcpy (mname + strlen(mname)-1, master_name);
	

	///! Master node
	vfs_node_t *mn = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy(mn->filename, master_name);
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
	vfs_mount (mname, mn);

	char slave_name[10];
	strcpy(slave_name, "ttys");
	strcpy (slave_name + strlen(slave_name)-1,s_value);

	char sname[10];
	strcpy(sname, "/dev/");
	strcpy (sname + strlen(sname)-1, slave_name);

	vfs_node_t *sn = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy(sn->filename, slave_name);
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
	vfs_mount (sname, sn);

	for (int i = 0; i < 32; i++) {
		tty->m_path[i] = mname[i];
		tty->s_path[i] = sname[i];
	}
		

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

	ttype_insert (tty);
	master_count++;
	slave_count++;
	*master_fd = m_fd;
	*slave_fd = s_fd;
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