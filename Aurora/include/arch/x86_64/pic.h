/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  pic.h -- Programmable Interrupt Controller
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury 2021
 *
 * ==============================================
 */

#ifndef __PIC_H__
#define __PIC_H__

#include <stdint.h>
#include <hal.h>

#define ICW1_ICW4  0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4  0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT  0x10

#define ICW4_8086 0x01
#define ICW4_AUTO  0x02
#define ICW4_BUF_SLAVE  0x08
#define ICW4_BUF_MASTER  0x0C
#define ICW4_SFNM  0x10

#define PIC1  0x20
#define PIC2  0xA0
#define PIC1_COMMAND  PIC1
#define PIC1_DATA   (PIC1+1)
#define PIC2_COMMAND  PIC2
#define PIC2_DATA  (PIC2+1)

#define PIC_EOI  0x20


extern void pic_interrupt_eoi (unsigned int intno);
extern void initialize_pic ( uint8_t base0, uint8_t base1);
extern void pic_set_mask (uint8_t irq);
extern void pic_clear_mask (unsigned char irq);
#endif