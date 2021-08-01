/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ac97.h -- Audio Codec 97 
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==================================================
 */

#include <drivers\ac97\ac97.h>
#include <drivers\pci.h>
#include <stdio.h>
#include <mm.h>

/**ac97_t _ac97;


void wait (int ms) {
	while(ms > 0) {
		ms--;
	}
}


void ac97_handler (size_t i, void* p) {
	printf ("AC97 interrupt fired++\n");
	apic_local_eoi();
}

void ac97_set_volume (int left_percent, int right_percent) {
	int left = left_percent * 10 / 32;
	int right = right_percent * 10 / 32;

	uint16_t vol = left | (right << 8);
	x64_outportw (_ac97.nambar + NAM_MASTER_VOL, vol);
	x64_outportw (_ac97.nambar + NAM_PCM_VOL, vol);
}

void ac97_set_sample_rate(int hertz) {
	x64_outportw (_ac97.nambar + 0x2A, x64_inportw(_ac97.nambar + 0x2A));
	/*for(int i = 0; i < 100; i++)
		;*/
//	wait(100);
//	x64_outportw (_ac97.nambar + 0x2C, hertz);
//	x64_outportw (_ac97.nambar + 0x32, hertz);
//	/*for (int i = 0; i < 100; i++)
//		;*/
//	wait(100);
//}
//
//
//void ac97_initialize (unsigned char *buffer) {
//	
//	pci_device_info *addr = (pci_device_info*)malloc(sizeof(pci_config_space));
//	if (!pci_find_device_class (0x04,0x01,addr)) {
//		printf ("No AC97 device found\n");
//		return;
//	}
//
//	printf ("AC97 Device found with device id -> %x, vendor id -> %x\n", addr->device.deviceID, addr->device.vendorID);
//
//	_ac97.nambar = (uint16_t)addr->device.nonBridge.baseAddress[0];
//	_ac97.nabmbar = (uint16_t)addr->device.nonBridge.baseAddress[1];
//	printf ("AC97 interrupt line -> %d\n", addr->device.nonBridge.interruptPin);
//
//	interrupt_set(addr->device.nonBridge.interruptLine, ac97_handler, addr->device.nonBridge.interruptLine);
//
//	printf ("AC97 NAMBAR -> %x, NABMBAR -> %x\n", _ac97.nambar, _ac97.nabmbar + 0x2C);
//	printf ("AC97 NAMBAR -> %x, NABMBAR -> %x\n", addr->device.nonBridge.baseAddress[0],addr->device.nonBridge.baseAddress[1]);
//	//! Reset
//	x64_outportd (_ac97.nabmbar + 0x2C, 0x3);
//	x64_outportw (_ac97.nambar + PORT_NAM_RESET, 42);
//
//	uint32_t cap = x64_inportd (_ac97.nabmbar + 0x30);
//	printf ("AC97 channels: %d\n", 2 + 2 * ((cap >> 20) & 3));
//	if (((cap >> 22) & 3) == 1)
//		printf ("20 bit sound supported\n");
//
//	
//	//!reset output channel
//	uint8_t val = x64_inportb(_ac97.nabmbar + NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);
//	x64_outportb(_ac97.nabmbar + NABM_OFFSET_BUFFER_CNT, 0x2);
//	//for (int i = 0; i < 2500; i++)
//	//	;
//	wait(2500);
//	if (x64_inportb(_ac97.nabmbar + NABM_OFFSET_BUFFER_CNT) & 2) {
//		printf ("Bit could not be cleared\n");
//	}
//
//	ac97_set_volume(100, 100);
//
//
//	printf ("AC97 Sample Rate -> %d Hz\n",  x64_inportw (_ac97.nambar +0x2A));
//
//	bool tick = false;
//	
//	/*size_t *buffer_1 = (size_t*)malloc(40960 * 2);
//	size_t *buffer_2 = (size_t*)malloc(40960 * 2);
//	size_t *buffer_3 = (size_t*)malloc(40960 * 2);*/
//
//	printf ("Buffers allocated\n");
//
//	/*ac97_buffer_desc_t *desc = (ac97_buffer_desc_t*)pmmngr_alloc();
//	for (int i = 0; i <32; i++) {
//		desc[i].buf = (uint32_t)buff;
//		desc[i].len = 0xFFFE;
//		desc[i].ioc = 1;
//		desc[i].bup = 0;
//	}*/
//
//	//desc[31].bup = 1;
//
//	/*for (int i = 0; i < 65535; i++) {
//		data_1++ = buffer;
//	}*/
//
//	//uint16_t* data_2 = (uint16_t*)get_physical_address(buffer_2);
//	//for (int i = 0; i < 65535; i++) {
//	//	*data_2++ = 0;
//	//}
//
//	/*uint16_t* data_3 = (uint16_t*)get_physical_address(buffer_3);
//	for (int i = 0; i < 65535; i++) {
//		*data_3++ = 0;
//	}
//*/
//
//	//// ("BDL Allocated address -> %x -> %x\n", bdl, (uint32_t)get_physical_address((uint64_t)bdl));
//	//x64_outportd (_ac97.nabmbar + 0x10, (uint32_t)desc);
//	//x64_outportb (_ac97.nabmbar + 0x15, 32);
//
//	printf("AC97 initialized\n");
//}
//
//
//void ac97_start (unsigned char* buffer) {
//	//memcpy (_ac97.buffer, buffer, 4096);
//
//	//ac97_set_sample_rate (44100);
//
//	uint8_t val = x64_inportb (_ac97.nabmbar + NABM_OFFSET_BUFFER_CNT);
//	val = (val & ~0x1F) | 0x1D;
//	printf ("VAL = %x\n", val);
//	x64_outportb (_ac97.nabmbar  + 0x0B, 0x1);
	/*for(int i = 0; i < 100000000; i++)
		;*/
	//x64_sti();
//}*/