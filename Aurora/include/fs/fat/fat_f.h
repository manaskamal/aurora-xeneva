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
 * @fat_f --FAT file system's file management
 *
 **/

#ifndef __FAT_F_H__
#define __FAT_F_H__

#include <stdint.h>
#include <fs\vfs.h>
/**
 * fat32_make_file -- creates a fat32 file
 * @param parent_clust -- parent directory cluster
 * @param filename -- filename
 * @param sz -- file size
 */
extern vfs_node_t* fat32_make_file (uint32_t parent_clust, char* filename, uint32_t sz);

/**
 * fat32_write_file -- writes memory buffers to a file
 * @param file -- pointer to the file object
 * @param buffer -- pointer to the memory buffer
 * @param length -- length of the file
 */
extern void fat32_write_file (vfs_node_t *file, uint8_t* buffer, uint32_t length);


#endif