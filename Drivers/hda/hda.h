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

#ifndef __HDA_H__
#define __HDA_H__

#include <stdint.h>

//! Device Registers
#define GCAP   0x00     //Global Capabilities
#define VMIN   0x02     //Minor Version
#define VMAJ   0x03     //Major Version
#define OUTPAY 0x04     //Output Payload Capability
#define INPAY  0x06     //Input Payload Capability
#define GCTL   0x08     //Global Control
#define WAKEEN 0x0C     //Wake Enable
#define STATESTS 0x0E    //Wake Status
#define GSTS    0x10    //Global Status
#define OUTSTRMPAY  0x18  //Output Stream Payload Capability
#define INSTRMPAY   0x1A  //Input Stream Payload Capability
#define INTCTL      0x20   //Interrupt Control
#define INTSTS      0x24   //Interrupt Status
#define WALCLK      0x30   //Wall Clock Counter
#define SSYNC       0x38   //Stream Synchronization 
#define CORBLBASE   0x40   //CORB Lower Base Address
#define CORBUBASE   0x44   //CORB Upper Base Address
#define CORBWP      0x48   //CORB Write Pointer
#define CORBRP      0x4A   //CORB Read Pointer
#define CORBCTL     0x4C   //CORB Control
#define CORBSTS     0x4D   //CORB Status
#define CORBSIZE    0x4E   //CORB Size
#define RIRBLBASE   0x50   //RIRB Lower Base Address
#define RIRBUBASE   0x54   //RIRB Upper Base Address
#define RIRBWP      0x58   //RIRB Write Pointer
#define RINTCNT     0x5A   //Response Interrupt Count
#define RIRBCTL     0x5C   //RIRB Control
#define RIRBSTS     0x5D   //RIRB Status
#define RIRBSIZE    0x5E   //RIRB Size
#define ICOI        0x60   //Immediate Command Output Interface
#define ICII        0x64   //Immediate Command Input Interface
#define ICIS        0x68   //Immediate Command Status
#define DPIBLBASE   0x70   //DMA Position Buffer Lower Base
#define DPIBUBASE   0x74   //DMA Position Buffer Upper Base
#define SD0CTL      0x80   //Input Stream Descriptor 0 control
#define SD0STS      0x83   //ISD0 Status
#define SD0LPIB     0x84   //ISD0 Link position in current buffer
#define SD0CBL      0x88   //ISD0 Cyclic Buffer Length
#define SD0LVI      0x8C   //ISD0 Last valid index
#define SD0FIFOD    0x90   //ISD0 FIFO Size
#define SD0FMT      0x92   //ISD0 Format
#define SDBDPL      0x98
#define SDBDPU      0x9C


#define REG_O0_CTLL      0x100    ///< Output 0 - Control Lower
#define REG_O0_CTLU      0x102    ///< Output 0 - Control Upper
#define REG_O0_STS       0x103    ///< Output 0 - Status
#define REG_O0_CBL       0x108    ///< Output 0 - Cyclic Buffer Length
#define REG_O0_STLVI     0x10c    ///< Output 0 - Last Valid Index
#define REG_O0_FMT       0x112    ///< Output 0 - Format
#define REG_O0_BDLPL     0x118    ///< Output 0 - BDL Pointer Lower
#define REG_O0_BDLPU     0x11c    ///< Output 0 - BDL Pointer Upper


#define BDL_SIZE 4
#define BUFFER_SIZE  0x10000

/* GCTL bits */
enum reg_gctl {
	GCTL_RESET = (1 << 0),
};

/* CORBCTL bits */
enum reg_corbctl {
	CORBCTL_CORBRUN = (1 << 1),
};

/* RIRBCTL bits */
enum reg_rirbctl {
	RIRBCTL_RIRBRUN = (1 << 1),
};


enum codec_verbs {
	VERB_GET_PARAMETER      = 0xf0000,
	VERB_SET_STREAM_CHANNEL = 0x70600,
	VERB_SET_FORMAT         = 0x20000,
	VERB_GET_AMP_GAIN_MUTE  = 0xb0000,
	VERB_SET_AMP_GAIN_MUTE  = 0x30000,
	VERB_GET_CONFIG_DEFAULT = 0xf1c00,
	VERB_GET_CONN_LIST      = 0xf0200,
    VERB_GET_CONN_SELECT    = 0xf0100,
    VERB_GET_PIN_CONTROL    = 0xf0700,
    VERB_SET_PIN_CONTROL    = 0x70700,
    VERB_GET_EAPD_BTL       = 0xf0c00,
    VERB_SET_EAPD_BTL       = 0x70c00,
    VERB_GET_POWER_STATE    = 0xf0500,
    VERB_SET_POWER_STATE    = 0x70500,
	VERB_SET_BEEP_GEN       = 0x70A00,
	VERB_GET_CONV_CHANNEL_COUNT = 0xF2D00,
	VERB_SET_CONV_CHANNEL_COUNT = 0x72D00,
	VERB_GET_VOLUME_CONTROL = 0xF0F00,
	VERB_SET_VOLUME_CONTROL = 0x70F00,
};

enum codec_parameters {
	PARAM_VENDOR_ID         = 0x00,
	PARAM_REV_ID            = 0x02,
    PARAM_NODE_COUNT        = 0x04,
    PARAM_FN_GROUP_TYPE     = 0x05,
    PARAM_AUDIO_WID_CAP     = 0x09,
    PARAM_PIN_CAP           = 0x0c,
    PARAM_CONN_LIST_LEN     = 0x0e,
    PARAM_OUT_AMP_CAP       = 0x12,
};

enum fn_group_type {
    FN_GROUP_AUDIO          = 0x01,
};

enum widget_type {
    WIDGET_OUTPUT           = 0x0,
    WIDGET_INPUT            = 0x1,
    WIDGET_MIXER            = 0x2,
    WIDGET_SELECTOR         = 0x3,
    WIDGET_PIN              = 0x4,
    WIDGET_POWER            = 0x5,
    WIDGET_VOLUME_KNOB      = 0x6,
    WIDGET_BEEP_GEN         = 0x7,
    WIDGET_VENDOR_DEFINED   = 0xf,
};

enum widget_capabilities {
    WIDGET_CAP_POWER_CNTRL  = (1 << 10),

    WIDGET_CAP_TYPE_SHIFT   = 20,
    WIDGET_CAP_TYPE_MASK    = (0xf << 20),
};

enum pin_capabilities {
    PIN_CAP_OUTPUT          = (1 << 4),
    PIN_CAP_INPUT           = (1 << 5),
};

enum pin_ctl_flags {
    PIN_CTL_ENABLE_OUTPUT   = (1 << 6),
};

enum sample_format {
    SR_48_KHZ               = 0,
    SR_44_KHZ               = (1 << 14),
    BITS_32                 = (4 <<  4),
    BITS_16                 = (1 <<  4),
};


#pragma pack (push,1)
typedef struct _bdl_ {
	uint64_t paddr;
	uint32_t length;
	uint32_t flags;
}hda_bdl_entry;
#pragma pack(pop)


typedef struct _hd_audio_ {
	size_t mmio;
	uint32_t* corb;
	uint64_t* rirb;
	uint32_t rirb_entries;
	uint32_t corb_entries;
	bool immediate_use;
	uint16_t output_nid;
	uint8_t  output_codec_id;
	uint32_t output_amp_gain_step;
}hd_audio_t;


/*  MMIO audio */
extern void _aud_outl_(int reg, uint32_t value);
extern uint32_t _aud_inl_ (int reg);
extern void _aud_outw_ (int reg, uint16_t value);
extern uint16_t _aud_inw_(int reg);
extern void _aud_outb_ (int reg, uint8_t value);
extern uint8_t _aud_inb_ (int reg);


/**
 * rirb_read - read a response from RIRB
 * @param response - address to where the controller will write response
 */
extern void rirb_read (uint64_t *response);
/*
 * corb_write -- write verb to corb
 * @param verb -- verb to write
 */
extern void corb_write (uint32_t verb);

/*
 * hda_set_output_nid -- set output nid
 * @param nid -- node id
 * @param codec -- output codec id
 * @param amp_gain -- amp gain step
 */
void hda_set_output_nid(uint16_t nid, uint8_t codec, uint32_t amp_gain);

/*
 * hda_set_volume -- sets volume to output codec
 * @param volume -- volume level 
 */
extern void hda_set_volume (uint8_t volume);

/*
 * hda_output_stream_start -- starts the output stream
 */
extern void hda_output_stream_start ();

/*
 * hda_output_stream_stop -- stops the output stream
 */
extern void hda_output_stream_stop();

/*==========================================
 * CODEC functions
 * =========================================
 */

/**
 * one time function for sending command and reading response
 */
extern uint32_t codec_query (int codec, int nid, uint32_t payload);
/*
 * codec_enumerate_widgets -- enumerate every widgets
 */
extern int codec_enumerate_widgets(int codec);


/*============================================
 * WIDGET functions
 *============================================
 */
/**
 *  Initializes widgets for a codec and node
 *  @param codec-> codec id
 *  @param nid --> node id
 */
extern void widget_init (int codec, int nid);
extern void widget_init_output (uint8_t codec, uint16_t nid);

/**
 *=============================================
 * Streams functions
 *=============================================
 */
/*
 * hda_init_output_stream -- initialize the output stream
 */
extern void hda_init_output_stream ();
extern void output_stream_write(uint8_t* buffer, size_t length);

#endif