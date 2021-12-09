/**
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *   hda -- High Definition Audio Intel
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#ifndef __HD_AUDIO_H__
#define __HD_AUDIO_H__

#include <stdint.h>
#include <drivers\pci.h>
#include <mm.h>
#include <hal.h>


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

#define INTCTL_CIE  0x40000000
#define INTCTL_GIE  0x80000000
#define INTCTL_SIE_MASK  0x3fffffff
#define INTCTL_SIE_SHIFT 0

#define REG_O0_CTLL(hd)   (hd.stream_0_x)   ///< Output 0 - Control Lower
#define REG_O0_CTLU(hd)   (hd.stream_0_x + 0x02)   ///< Output 0 - Control Upper
#define REG_O0_STS(hd)    (hd.stream_0_x + 0x03)    ///< Output 0 - Status
#define REG_O0_CBL(hd)    (hd.stream_0_x + 0x08)  ///< Output 0 - Cyclic Buffer Length
#define REG_O0_STLVI(hd)  (hd.stream_0_x + 0x0C)    ///< Output 0 - Last Valid Index
#define REG_O0_FMT(hd)    (hd.stream_0_x + 0x12)    ///< Output 0 - Format
#define REG_O0_BDLPL(hd)  (hd.stream_0_x + 0x18)    ///< Output 0 - BDL Pointer Lower
#define REG_O0_BDLPU(hd)  (hd.stream_0_x + 0x1C)    ///< Output 0 - BDL Pointer Upper

#define HDA_GCAP_OSS_MASK  0xf000
#define HDA_GCAP_OSS_SHIFT  12
#define HDA_GCAP_ISS_SHIFT  8
#define HDA_GCAP_ISS_MASK  0x0f00
#define HDA_GCAP_BSS_SHIFT 3
#define HDA_GCAP_BSS_MASK  0x00f8
#define HDA_GCAP_NSD0_SHIFT  1
#define HDA_GCAP_NSD0_MASK  0x0006

#define HDA_GCAP_BSS(gcap)  (((gcap) & HDA_GCAP_BSS_MASK) >> HDA_GCAP_BSS_SHIFT)
#define HDA_GCAP_ISS(gcap)  (((gcap) & HDA_GCAP_ISS_MASK) >> HDA_GCAP_ISS_SHIFT)
#define HDA_GCAP_OSS(gcap)  (((gcap) & HDA_GCAP_OSS_MASK) >> HDA_GCAP_OSS_SHIFT)


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

#pragma pack (push,1)
typedef struct _bdl_ {
	uint64_t paddr;
	uint32_t length;
	uint32_t flags;
}ihda_bdl_entry;
#pragma pack(pop)

typedef struct _output_ {
	uint8_t codec;
	uint16_t nid;

	uint32_t sample_rate;
	int amp_gain_steps;
	int num_channels;
}ihd_audio_output;


#define BDL_SIZE 4
#define BUFFER_SIZE  0x10000

#define BDL_BYTES_ROUNDED   \
	((BDL_SIZE * sizeof(ihda_bdl_entry) + 127) & ~127)

#define SAMPLES_PER_BUFFER (BUFFER_SIZE / 2)

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

//! DAC Output	
typedef struct _hda_output_ {
	uint8_t codec;
	uint16_t nid;
	uint32_t sample_rate;
	int amp_gain_steps;
	int num_channels;
} hda_output;


typedef struct _hda_vol_knob_ {
	uint8_t codec;
	uint16_t nid;
}hda_volume;

#pragma pack (push, 1)
typedef struct _hd_audio_ {
	size_t mmio;
	uint32_t *corb;
	uint64_t *rirb;
	uint32_t rirb_entries;
	uint32_t corb_entries;
	bool immediate_use;
	hda_output *output;
	hda_volume *vol;
	uint16_t num_iss;  //Total number of Input Stream
	uint16_t num_oss;  //Total number of Output Stream
	int stream_0_x;  //first output stream 
	int stream_0_y;  //first bidirectional stream
	uint64_t *buffer; 
	uint64_t *dma_pos; 
}hd_audio;
#pragma pack (pop)

typedef struct _rirb_ {
	uint32_t response;
	uint32_t response_ex;
}hda_rirb;


//! Initialize the High-Definition Audio Controller
extern void hda_initialize ();
extern void hda_set_volume (uint8_t volume);
extern void hda_audio_add_pcm (void *data, size_t length);
#endif