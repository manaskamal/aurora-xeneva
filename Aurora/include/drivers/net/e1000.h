/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  e1000.h -- Intel Ethernet i217 driver
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#ifndef __E1000_H__
#define __E1000_H__

#include <stdint.h>
#include <drivers\pci.h>

#define E1000_INTEL_VEND   0x8086
#define E1000_DEV          0x100E
#define E1000_I217         0x153A
#define E1000_82577LM      0x10EA

#define REG_CTRL    0x0000
#define REG_STATUS  0x00008
#define REG_EEPROM  0x0014
#define REG_CTRL_EXT  0x0018
#define REG_IMASK 0x00D0
#define REG_IMC   0x00D8
#define REG_ICR   0x00C0
#define REG_ITR   0x00C4
#define REG_RCTRL 0x0100
#define REG_RXDESCLO  0x2800
#define REG_RXDESCKHI  0x2804
#define REG_RXDESCLEN   0x2808
#define REG_RXDESCHEAD  0x2810
#define REG_RXDESCTAIL  0x2818
 
#define REG_TCTRL       0x0400
#define REG_TXDESCLO    0x3800
#define REG_TXDESCHI    0x3804
#define REG_TXDESCLEN   0x3808
#define REG_TXDESCHEAD  0x3810
#define REG_TXDESCTAIL  0x3818
 
 
#define REG_RDTR         0x2820 // RX Delay Timer Register
#define REG_RXDCTL       0x3828 // RX Descriptor Control
#define REG_RADV         0x282C // RX Int. Absolute Delay Timer
#define REG_RSRPD        0x2C00 // RX Small Packet Detect Interrupt
#define REG_MTA          0x5200 
 
 
#define REG_TIPG         0x0410      // Transmit Inter Packet Gap
#define REG_FCAL         0x00028
#define REG_FCAH         0x0002c
#define REG_FCT          0x00030
#define REG_FCTTV        0x02800
#define REG_CRCERRS      0x04000

#define ECTRL_SLU        0x40        //set link up
 
 
#define RCTL_EN                         (1 << 1)    // Receiver Enable
#define RCTL_SBP                        (1 << 2)    // Store Bad Packets
#define RCTL_UPE                        (1 << 3)    // Unicast Promiscuous Enabled
#define RCTL_MPE                        (1 << 4)    // Multicast Promiscuous Enabled
#define RCTL_LPE                        (1 << 5)    // Long Packet Reception Enable
#define RCTL_LBM_NONE                   (0 << 6)    // No Loopback
#define RCTL_LBM_PHY                    (3 << 6)    // PHY or external SerDesc loopback
#define RTCL_RDMTS_HALF                 (0 << 8)    // Free Buffer Threshold is 1/2 of RDLEN
#define RTCL_RDMTS_QUARTER              (1 << 8)    // Free Buffer Threshold is 1/4 of RDLEN
#define RTCL_RDMTS_EIGHTH               (2 << 8)    // Free Buffer Threshold is 1/8 of RDLEN
#define RCTL_MO_36                      (0 << 12)   // Multicast Offset - bits 47:36
#define RCTL_MO_35                      (1 << 12)   // Multicast Offset - bits 46:35
#define RCTL_MO_34                      (2 << 12)   // Multicast Offset - bits 45:34
#define RCTL_MO_32                      (3 << 12)   // Multicast Offset - bits 43:32
#define RCTL_BAM                        (1 << 15)   // Broadcast Accept Mode
#define RCTL_VFE                        (1 << 18)   // VLAN Filter Enable
#define RCTL_CFIEN                      (1 << 19)   // Canonical Form Indicator Enable
#define RCTL_CFI                        (1 << 20)   // Canonical Form Indicator Bit Value
#define RCTL_DPF                        (1 << 22)   // Discard Pause Frames
#define RCTL_PMCF                       (1 << 23)   // Pass MAC Control Frames
#define RCTL_SECRC                      (1 << 26)   // Strip Ethernet CRC
#define RCTL_BSEX                       0x02000000
#define REG_IAM  0x000E0 /* Interrupt Acknowledge Auto Mask */

#define CTRL_PHY_RST (1UL << 31UL)
#define CTRL_RST     (1UL << 26UL)
#define CTRL_SLU     (1UL << 6UL)
#define CTRL_LRST    (1UL << 3UL)


 
// Buffer Sizes
#define RCTL_BSIZE_256                  (3 << 16)
#define RCTL_BSIZE_512                  (2 << 16)
#define RCTL_BSIZE_1024                 (1 << 16)
#define RCTL_BSIZE_2048                 (0 << 16)
#define RCTL_BSIZE_4096                 ((3 << 16) | (1 << 25))
#define RCTL_BSIZE_8192                 ((2 << 16) | (1 << 25))
#define RCTL_BSIZE_16384                ((1 << 16) | (1 << 25))
 
// Transmit Command
 
#define CMD_EOP                         (1 << 0)    // End of Packet
#define CMD_IFCS                        (1 << 1)    // Insert FCS
#define CMD_IC                          (1 << 2)    // Insert Checksum
#define CMD_RS                          (1 << 3)    // Report Status
#define CMD_RPS                         (1 << 4)    // Report Packet Sent
#define CMD_VLE                         (1 << 6)    // VLAN Packet Enable
#define CMD_IDE                         (1 << 7)    // Interrupt Delay Enable
 
 
// TCTL Register
 
#define TCTL_EN                         (1 << 1)    // Transmit Enable
#define TCTL_PSP                        (1 << 3)    // Pad Short Packets
#define TCTL_CT_SHIFT                   4           // Collision Threshold
#define TCTL_COLD_SHIFT                 12          // Collision Distance
#define TCTL_SWXOFF                     (1 << 22)   // Software XOFF Transmission
#define TCTL_RTLC                       (1 << 24)   // Re-transmit on Late Collision
 
#define TSTA_DD                         (1 << 0)    // Descriptor Done
#define TSTA_EC                         (1 << 1)    // Excess Collisions
#define TSTA_LC                         (1 << 2)    // Late Collision
#define LSTA_TU                         (1 << 3)    // Transmit Underrun

#define E1000_IMS_TXDW   (1<<0)
#define E1000_IMS_TXQE   (1<<1)
#define E1000_IMS_LSC    (1<<2)
#define E1000_IMS_RXO    (1<<6)
#define E1000_IMS_RXT    (1<<7)
enum {
	CTL_AUTO_SPEED = (1 << 5),
	CTL_LINK_UP = (1 << 6),
	CTL_RESET = (1 << 26),
	CTL_PHY_RESET = (1 << 32),
};

enum {
	RCTL_BROADCAST = (1 <<15),
	RCTL_2K_BUFSIZE = (0 << 16),
};

#define E1000_NUM_RX_DESC 32
#define E1000_NUM_TX_DESC 8

#define E1000_ICR_TRANSMIT  (1<<0)
#define E1000_ICR_LINK_CHANGE  (1<<2)
#define E1000_ICR_RECEIVE   (1<<7)
#define STATUS_LINK_UP (1<<31)
 
#pragma pack(push,1)
struct e1000_rx_desc {
        volatile uint64_t addr;
        volatile uint16_t length;
        volatile uint16_t checksum;
        volatile uint8_t status;
        volatile uint8_t errors;
        volatile uint16_t special;
};
#pragma pack(pop)
 
#pragma pack(push,1)
struct e1000_tx_desc {
        volatile uint64_t addr;
        volatile uint16_t length;
        volatile uint8_t cso;
        volatile uint8_t cmd;
        volatile uint8_t status;
        volatile uint8_t css;
        volatile uint16_t special;
};
#pragma pack(pop)


typedef struct _e1000_dev_ {
	size_t e1000_base;
	uint64_t e1000_mem_base;
	bool eerprom_exists;
	uint32_t e1000_irq;
	uint8_t mac[6];
	uint64_t *rx_desc_base;
	uint64_t* tx_desc_base;
	uint16_t tx_tail;
	uint16_t rx_tail;
	e1000_rx_desc *rx_desc[E1000_NUM_RX_DESC];
	e1000_tx_desc *tx_desc[E1000_NUM_TX_DESC];
}e1000_dev;

extern void e1000_initialize ();
extern void e1000_send_packet (void* data, size_t size);
#endif