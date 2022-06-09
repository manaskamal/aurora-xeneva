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

#include "hda.h"
#include <hal.h>
#include <arch\x86_64\mmngr\paging.h>
#include <string.h>
#include <stdio.h>

uint64_t* stream_buffer = 0;

//! Start a Stream !!! Errors are there, needs fixing
//! not completed yet
void hda_init_output_stream () {

	uint64_t pos = 0xFFFFD00004000000;
	uint64_t phys_buf = 0;
	stream_buffer = (uint64_t*)pos;
	for (int i = 0; i < (BDL_SIZE*BUFFER_SIZE/ 4096); i++) {
		void *p = AuPmmngrAlloc();
		if (phys_buf == 0)
			phys_buf = (uint64_t)p;
		AuMapPage ((uint64_t)p,pos + i * 4096, (1<<4));
	}


	hda_set_sample_buffer(pos);

	
	/* Now reset the stream */
	_aud_outl_ (REG_O0_CTLL, 1); //reset
	//while((_aud_inl_(REG_O0_CTLL) & 0x1) == 0);
	for (int i = 0; i < 1000000; i++)
		;

	_aud_outl_ (REG_O0_CTLL, 0);
	//while((_aud_inl_(REG_O0_CTLL) & 0x1));


	for (int i = 0; i < 100000; i++)
		;
	uint64_t bdl_base = (uint64_t)AuPmmngrAlloc();   //get_physical_address  ((uint64_t) 0x0000000000000000);
	hda_bdl_entry *bdl = (hda_bdl_entry*)bdl_base;  //(_ihd_audio.corb + 3072);

	int j = 0;
	for (j = 0; j < BDL_SIZE; j++) {
		bdl[j].paddr = (uint64_t)(phys_buf + j * BUFFER_SIZE);
		bdl[j].length = BUFFER_SIZE;
		bdl[j].flags = 1;
	}
	

	_aud_outb_ (REG_O0_CTLU, (1<<4));

	_aud_outl_ (REG_O0_CBL,BDL_SIZE*BUFFER_SIZE);
	_aud_outw_(REG_O0_STLVI, BDL_SIZE-1);

	_aud_outl_ (REG_O0_BDLPL, bdl_base);
	_aud_outl_ (REG_O0_BDLPU, bdl_base >> 32);

	//uint16_t format =  (1<<14) | (0<<11)  | (1<<4) | 1;
	uint16_t format =  (1<<15) | SR_44_KHZ | (0<<11) | (0 << 8) | BITS_16 | 1;
	_aud_outw_ (REG_O0_FMT, format);

	_aud_outb_ (REG_O0_STS, HDAC_SDSTS_DESE | HDAC_SDSTS_FIFOE | HDAC_SDSTS_BCIS);

	uint64_t* dma_pos = (uint64_t*)p2v((size_t)AuPmmngrAlloc());
	for (int i = 0; i < 8; i++) {
		dma_pos[i] = 0;
	}

	//_ihd_audio.dma_pos = dma_pos;
	uint64_t dma_val = (uint64_t)v2p((size_t)dma_pos);


	_aud_outl_ (DPIBLBASE, dma_val | 0x1);
	_aud_outl_ (DPIBUBASE, dma_val >> 32);

	hda_audio_set_dma_pos((uint64_t)dma_pos);
	
	uint32_t strm = _aud_inl_(REG_O0_CTLL);

}

void output_stream_write(uint8_t* buffer, size_t length) {
	int16_t* buf = (int16_t*)buffer;
	int16_t* strm_buff = (int16_t*)stream_buffer;

	for (int i = 0; i < BUFFER_SIZE / sizeof(int16_t); i++) 
		strm_buff[i] = buf[i];

	for (int i = 0; i < BUFFER_SIZE / sizeof(int16_t); i++) 
		strm_buff[i] /= 2;
}


