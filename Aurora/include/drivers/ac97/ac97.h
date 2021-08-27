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

#ifndef __AC97_H__
#define __AC97_H__

#include <stdint.h>
#include <hal.h>


#define PORT_NAM_RESET                0x0000
#define PORT_NAM_MASTER_VOLUME        0x0002
#define PORT_NAM_AUX_OUT_VOLUME       0x0004
#define PORT_NAM_MONO_VOLUME          0x0006
#define PORT_NAM_MASTER_TONE          0x0008
#define PORT_NAM_PC_BEEP_VOLUME       0x000A
#define PORT_NAM_PHONE_VOLUME         0x000C
#define PORT_NAM_MIC_VOLUME           0x000E
#define PORT_NAM_LINE_IN_VOLUME       0x0010
#define PORT_NAM_CD_VOLUME            0x0012
#define PORT_NAM_VIDEO_VOLUME         0x0014
#define PORT_NAM_AUX_IN_VOLUME        0x0016
#define PORT_NAM_PCM_OUT_VOLUME       0x0018
#define PORT_NAM_RECORD_SELECT        0x001A
#define PORT_NAM_RECORD_GAIN          0x001C
#define PORT_NAM_RECORD_GAIN_MIC      0x001E
#define PORT_NAM_GENERAL_PURPOSE      0x0020
#define PORT_NAM_3D_CONTROL           0x0022
#define PORT_NAM_AUDIO_INT_PAGING     0x0024
#define PORT_NAM_POWERDOWN_CTRL_STS   0x0026

#define PORT_NAM_EXT_AUDIO_ID         0x0028
#define PORT_NAM_EXT_AUDIO_STS_CTRL   0x002A
#define PORT_NAM_FRONT_DAC_RATE       0x002C
#define PORT_NAM_SURR_DAC_RATE        0x002E
#define PORT_NAM_LFE_DAC_RATE         0x0030
#define PORT_NAM_LR_ADC_RATE          0x0032
#define PORT_NAM_MIC_ADC_RATE         0x0034
#define PORT_NAM_CENTER_LFE_VOLUME    0x0036
#define PORT_NAM_SURR_VOLUME          0x0038
#define PORT_NAM_S_PDIF_CTRL          0x003A

#define PORT_NAM_EXTENDED_MODEM_ID    0x003C
// for details of the following modem regs cf. spec table 68

#define PORT_NAM_VENDOR_RESERVED_1    0x005A
#define PORT_NAM_PAGE_REGISTERS       0x0060
#define PORT_NAM_VENDOR_RESERVED_2    0x0070
#define PORT_NAM_VENDOR_ID_1          0x007C
#define PORT_NAM_VENDOR_ID_2          0x007E

////////////////////////////////////////////
// Second Address space
// NABM - Native Audio Bus Mastering

// source: wiki at lowlevel.eu about ac97
// http://www.lowlevel.eu/wiki/AC97#Anhang
//
#define PORT_NABM_POBDBAR             0x0010
#define PORT_NABM_POLVI               0x0015
#define PORT_NABM_PICONTROL           0x000B
#define PORT_NABM_POCONTROL           0x001B
#define PORT_NABM_MCCONTROL           0x002B
#define PORT_NABM_PISTATUS            0x0006
#define PORT_NABM_POSTATUS            0x0016
#define PORT_NABM_MCSTATUS            0x0026


#define NAM_RESET				0x00
#define NAM_MASTER_VOL			0x02
#define NAM_MIC_VOL				0x0E
#define NAM_PCM_VOL				0x18
#define NAM_REC_SLC				0x1A
#define NAM_REC_GAIN			0x1C
#define NAM_MIC_GAIN			0x1E
#define NAM_EXT_ID				0x28
#define NAM_EXT_CTRL			0x2A
#define NAM_EXT_FRONT_RATE		0x2C

#define NABM_PCM_INPUT_BASE		0x00
#define NABM_PCM_OUTPUT_BASE	0x10
#define NABM_MIC_INPUT_BASE		0x20
#define NABM_GLOBAL_CTL			0x2C
#define NABM_GLOBAL_STS			0x30

#define NABM_OFFSET_BUFFER_DSC_ADDR			0x00
#define NABM_OFFSET_CUR_ENTRY_VAL			0x04
#define NABM_OFFSET_LAST_VALID_ENTRY		0x05
#define NABM_OFFSET_TRANSFER_STS			0x06
#define NABM_OFFSET_CUR_IDX_PROC_SAMPLES	0x08
#define NABM_OFFSET_PRCSD_ENTRY				0x0A
#define NABM_OFFSET_BUFFER_CNT				0x0B

#define GLOBAL_CTL_GLOBAL_INT_ENABLE		0x0001
#define GLOBAL_CTL_COLD_RESET				0x0002
#define GLOBAL_CTL_WARM_RESET				0x0004
#define GLOBAL_CTL_SHUTDOWN					0x0008

#pragma pack (push)

typedef struct _ac97_buf_desc_ {
	uint32_t buf;
	uint16_t len;
	uint16_t reserved : 14;
	uint16_t bup : 1;
	uint16_t ioc : 1;
}ac97_buffer_desc_t;

#pragma pack (pop)

typedef struct _ac97_ {
	uint16_t nambar;
	uint16_t nabmbar;
	uint16_t* buffer;
	uint32_t num_desc;
	ac97_buffer_desc_t* descs;
	uint32_t NUM;
}ac97_t;


extern void ac97_initialize ();
extern void ac97_start (unsigned char* buffer);
#endif