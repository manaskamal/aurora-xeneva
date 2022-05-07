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

#include <net\arp.h>
#include <net\aunet.h>
#include <net\ethernet.h>

void AuARPRequestMAC() {
	arp_t arp;
	arp.hw_address_type = 0x0100; //rthernet
	arp.hw_protocol_type = 0x0008; //IPV4
	arp.hw_address_size = 6; //mac
	arp.protocol_size = 4; //ipv4
	arp.operation = ARP_OPERATION_REQUEST; 

	uint8_t *mac = AuGetNetTuple()->mac;
	memcpy(arp.src_mac,mac, 6);
	arp.src_ip[0] = 192;
	arp.src_ip[1] = 168;
	arp.src_ip[2] = 0;
	arp.src_ip[3] = 0;
	
	memset(arp.dest_mac, 0xff, 6);
	memset(arp.dest_ip, 0xff, 4);
	ethernet_send(&arp,sizeof(arp_t),ETHERNET_TYPE_ARP,arp.dest_mac);
}