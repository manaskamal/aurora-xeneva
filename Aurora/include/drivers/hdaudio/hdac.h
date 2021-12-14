/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  hdac.h -- HD-Audio Codec
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */

#ifndef __HDA_CODEC_H__
#define __HDA_CODEC_H__


extern void widget_init (int codec, int nid);
extern int codec_enumerate_widgets(int codec);
#endif