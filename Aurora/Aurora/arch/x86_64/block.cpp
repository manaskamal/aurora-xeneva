/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  block -- Block list of threads
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */

#include <arch\x86_64\block.h>
#include <arch\x86_64\thread.h>

thread_t *block_list_head = NULL;
thread_t *block_list_last = NULL;