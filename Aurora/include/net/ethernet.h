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

#ifndef __ETHERNET_H__
#define __ETHERNET_H__

#include <stdint.h>

#define ETHERNET_TYPE_IPV4  0x0800
#define ETHERNET_TYPE_ARP   0x0806
#define ETHERNET_TYPE_WAKE_ON_LAN 0x0842
#define ETHERNET_TYPE_AVTP  0x22F0
#define ETHERNET_TYPE_IETF_TRILL_PROTOCOL 0x22F3
#define ETHERNET_TYPE_STREAM_RESV_PROTOCOL 0x22EA


typedef struct _ethernet_ {
	uint8_t dest[6];
	uint8_t src[6];
	uint16_t type_len;
}ethernet_t;


/*
 * ethernet_send -- sends ethernet packets
 * @param data -- pointer to data
 * @param len -- length of the buffer
 * @param type -- type of the packet
 * @param dest -- destination MAC address
 */
extern void ethernet_send (void* data, size_t len, uint16_t type, uint8_t* dest);

#endif