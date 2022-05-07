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

#include <net\ethernet.h>
#include <net\aunet.h>
#include <arch\x86_64\mmngr\kheap.h>

/*
 * ethernet_send -- sends ethernet packets
 * @param data -- pointer to data
 * @param len -- length of the buffer
 * @param type -- type of the packet
 * @param dest -- destination MAC address
 */
void ethernet_send (void* data, size_t len, uint16_t type, uint8_t* dest) {
	size_t total_sz = sizeof(ethernet_t) + len;
	ethernet_t* packet = (ethernet_t*)malloc(total_sz);
	memcpy(packet + 1, data, len);
	memcpy(packet->dest, dest,6);
	uint8_t *src_mac = AuGetNetTuple()->mac;
	memcpy(packet->src,src_mac,6);
	packet->type_len = htons(type);
	AuNetWrite((uint8_t*)packet,total_sz);
	free(packet);
}