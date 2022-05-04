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
 **/

#include <net\aunet.h>
#include <fs\vfs.h>
#include <_null.h>

vfs_node_t *net_hw_file;
static uint8_t aunet_mac[6];
AuNet_t *first_net_hw;

/*
 * AuNetInitialize -- initialize the net hardware
 */
void AuNetInitialize () {
	first_net_hw = NULL;
	net_hw_file = NULL;
}

/*
 * AuNetAddAdapter -- add an NIC to NetHW
 * @param hw_file -- hardware file
 * @param aunet -- AuNet structure
 */
void AuNetAddAdapter (vfs_node_t *hw_file, AuNet_t *aunet) {
	if (!net_hw_file)
		net_hw_file = hw_file;

	first_net_hw = aunet;
}

/*
 * AuNetWrite -- Writes data to net hardware
 * @param buffer -- buffer to write
 * @param length -- length of the buffer
 */
void AuNetWrite (uint8_t* buffer, size_t length) {
	if (!net_hw_file)
		return;
	net_hw_file->write (net_hw_file, buffer, length);
}

/*
 * AuGetNetTuple -- returns the net structure
 */
AuNet_t* AuGetNetTuple () {
	return first_net_hw;
}