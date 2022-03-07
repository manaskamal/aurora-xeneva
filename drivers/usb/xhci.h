/**
 *
 *   Copyright (C) Manas Kamal Choudhury 2022
 *
 *   XHCI -- extensible host controller interface
 *
 *   /PROJECT - Aurora's Xeneva v1.0
 *   /AUTHOR  - Manas Kamal Choudhury 
 *
 *===================================================
 */

#ifndef __XHCI_H__
#define __XHCI_H__

#include <stdint.h>

#define XHCI_CAPREG_CAPLENGTH  0x0
#define XHCI_CAPREG_HCIVERSION 0x2
#define XHCI_CAPREG_HCSPARAMS1 0x4
#define XHCI_CAPREG_HCSPARAMS2 0x8
#define XHCI_CAPREG_HCSPARAMS3 0xC
#define XHCI_CAPREG_HCSPARAMS1 0x10
#define XHCI_CAPREG_DBOFF      0x14
#define XHCI_CAPREG_RTSOFF     0x18
#define XHCI_CAPREG_HCCPARAMS2 0x1C

#define XHCI_OPREG_USBCMD   0x0
#define XHCI_OPREG_USBSTS   0x4
#define XHCI_OPREG_PAGESIZE 0x8
#define XHCI_OPREG_DNCTRL   0x14
#define XHCI_OPREG_CRCR     0x18
#define XHCI_OPREG_DCBAAP   0x30
#define XHCI_OPREG_CONFIG   0x38

#define XHCI_OPREG_PORTSBASE 0x400
#define XHCI_OPREG_PORTPMSCBASE 0x404
#define XHCI_OPREG_PORTLIBASE   0x408
#define XHCI_OPREG_PORTHLPMCBASE 0x40C
#define XHCI_PORTOFFSET  0x10

#define XHCI_OPREG_PORTSC(x)  \
	(XHCI_OPREG_PORTSCBASE + (x-1) * XHCI_PORTOFFSET)
#define XHCI_OPREG_PORTPMSC(x) \
	(XHCI_OPREG_PMSCBASE + (x-1) * XHCI_PORTOFFSET)

#define XHCI_OPREG_PORTLI(x) \
(XHCI_OPREG_PORTLIBASE + (x-1) * XHCI_PORTOFFSET)
#define XHCI_OPREG_PORTHLPMC(x) \
(XHCI_OPREG_PORTHLPMCBASE + (x-1) * XHCI_PORTOFFSET)

#define XHCI_PORTSC_SPEED_GET(x) \
((x >> 10) & 0xF)

#define XHCI_RUNREG_MFINDEX 0x0
#define XHCI_RUNREG_IMANBASE 0x20
#define XHCI_RUNREG_IMODBASE 0x24
#define XHCI_RUNREG_ERSTSZBASE 0x28
#define XHCI_RUNREG_ERSTBABASE 0x30
#define XHCI_RUNREG_ERDPBASE 0x38
#define XHCI_INTERRUPTEROFFSET 0x20

#define XHCI_RUNREG_IMAN(x) \
(XHCI_RUNREG_IMANBASE + x*XHCI_INTERRUPTEROFFSET)
#define XHCI_RUNREG_IMOD(x) \
(XHCI_RUNREG_IMODBASE + x*XHCI_INTERRUPTEROFFSET)
#define XHCI_RUNREG_ERSTSZ(x) \
(XHCI_RUNREG_ERSTSZBASE + x*XHCI_INTERRUPTEROFFSET)
#define XHCI_RUNREG_ERSTBA(x) \
(XHCI_RUNREG_ERSTBABASE + x*XHCI_INTERRUPTEROFFSET)
#define XHCI_RUNREG_ERDP(x) \
(XHCI_RUNREG_ERDPBASE + x*XHCI_INTERRUPTEROFFSET)

#define XHCI_ECAP_LEGSUP 1
#define XHCI_ECAP_SUPPORT 2

#define XHCI_LEGCTLSTS_DISABLE_SMI	((0x7 << 1) + (0xff << 5) + (0x7 << 17))
#define XHCI_LEGCTLSTS_EVENTS_SMI	(0x7 << 29)

#define XHCI_TRB_TYPE_NOOP 8
#define XHCI_TRB_TYPE_ENABLE_SLOT 9
#define XHCI_TRB_TYPE_ADDRESS_DEVICE 11
#define XHCI_TRB_TYPE_EVALUATE_CONTEXT 13
#define XHCI_TRB_TYPE_RESET_ENDPOINT 14
#define XHCI_TRB_TYPE_TRANSFER_EVENT 32
#define XHCI_TRB_TYPE_COMMAND_COMPLETE 33
#define XHCI_TRB_TYPE_PORT_STATUS_CHANGE 34
#define XHCI_TRB_TYPE_SETUP_STAGE 2
#define XHCI_TRB_TYPE_DATA_STAGE 3
#define XHCI_TRB_TYPE_STATUS_STAGE 4

#define XHCI_TRB_TYPE(x) ((uint64_t)x << 42)
#define XHCI_TRB_SLOTID(x) ((uint64_t)x << 56)

#define XHCI_GET_TRB_TYPE(x) \
((x >> 42) & 0x3F)

#define XHCI_TRB_ADDRESS_BSR ((uint64_t)1<<41)
#define XHCI_TRB_ENABLED 0x100000000
#define XHCI_TRB_ENT 0x200000000
#define XHCI_TRB_ISP 0x400000000
#define XHCI_TRB_IOC 0x2000000000
#define XHCI_TRB_IDT 0x4000000000
#define XHCI_TRB_TRT(x) ((uint64_t)x << 48)
#define XHCI_TRB_DIR_IN ((uint64_t)1 << 48)

#define XHCI_DOORBELL_HOST 0x0
#define XHCI_DOORBELL_HOST_COMMAND 0
#define XHCI_DOORBELL_ENPOINT0 1

#define XHCI_DOORBELL(slot) \
(XHCI_DOORBELL_HOST+slot*4)

#define XHCI_COMPLETION_SUCCESS 1
#define XHCI_COMPLETION_STALL 6


// Global things
#define XHCI_PCI_PROGIF				0x30
#define XHCI_MAX_DEV_SLOTS			16
#define XHCI_MAX_ROOTPORTS			255
#define XHCI_COMMANDRING_SIZE		16
#define XHCI_EVENTRING_SIZE			16
#define XHCI_TRANSRING_SIZE			32
#define XHCI_TRB_MAXBYTES			0x10000

// Bitfields for the HCSPARAMS1 register
#define XHCI_HCSP1_MAXPORTS			0xFF000000
#define XHCI_HCSP1_MAXINTRPTRS		0x0007FF00
#define XHCI_HCSP1_MAXDEVSLOTS		0x000000FF

// Bitfields for the HCSPARAMS2 register
#define XHCI_HCSP2_MAXSCRPBUFFSLO	0xF8000000
#define XHCI_HCSP2_SCRATCHPREST		0x04000000
#define XHCI_HCSP2_MAXSCRPBUFFSHI	0x03E00000
#define XHCI_HCSP2_ERSTMAX			0x000000F0
#define XHCI_HCSP2_ISOCSCHDTHRS		0x0000000F

// Bitfields for the HCSPARAMS3 register
#define XHCI_HCSP3_U2DEVLATENCY		0xFFFF0000
#define XHCI_HCSP3_U1DEVLATENCY		0x000000FF

// Bitfields for the HCCPARAMS register
#define XHCI_HCCP_EXTCAPPTR			0xFFFF0000
#define XHCI_HCCP_MAXPRISTRARSZ		0x0000F000
#define XHCI_HCCP_NOSECSIDSUP		0x00000080
#define XHCI_HCCP_LATTOLMESSCAP		0x00000040
#define XHCI_HCCP_LIGHTHCRESET		0x00000020
#define XHCI_HCCP_PORTIND			0x00000010
#define XHCI_HCCP_PORTPOWER			0x00000008
#define XHCI_HCCP_CONTEXTSIZE		0x00000004
#define XHCI_HCCP_BANDNEGCAP		0x00000002
#define XHCI_HCCP_64ADDRCAP			0x00000001

// Extended capability types
#define XHCI_EXTCAP_RESERVED		0x00
#define XHCI_EXTCAP_LEGACYSUPP		0x01
#define XHCI_EXTCAP_SUPPPROTO		0x02
#define XHCI_EXTCAP_EXTPOWERMAN		0x03
#define XHCI_EXTCAP_IOVIRT			0x04
#define XHCI_EXTCAP_MESSAGEINT		0x05
#define XHCI_EXTCAP_LOCALMEM		0x06
#define XHCI_EXTCAP_USBDEBUG		0x0A
#define XHCI_EXTCAP_EXTMESSINT		0x11

// Bitfields for the legacy support capability register
#define XHCI_LEGSUPCAP_BIOSOWND		0x00010000
#define XHCI_LEGSUPCAP_OSOWNED		0x01000000

// Bitfields for the command register
#define XHCI_CMD_ENBLU3MFIDXSTP		0x00000800
#define XHCI_CMD_ENBLWRAPEVENT		0x00000400
#define XHCI_CMD_CTRLRESTSTATE		0x00000200
#define XHCI_CMD_CTRLSAVESTATE		0x00000100
#define XHCI_CMD_LIGHTHCRESET		0x00000080
#define XHCI_CMD_HOSTSYSERRENBL		0x00000008
#define XHCI_CMD_INTERUPTRENBL		0x00000004
#define XHCI_CMD_HCRESET			0x00000002
#define XHCI_CMD_RUNSTOP			0x00000001

// Bitfields for the status register
#define XHCI_STAT_HOSTCTRLERR		0x00001000	// RO
#define XHCI_STAT_CTRLNOTREADY		0x00000800	// RO
#define XHCI_STAT_SAVERESTERR		0x00000400	// RW1C
#define XHCI_STAT_RESTSTATE			0x00000200	// RO
#define XHCI_STAT_SAVESTATE			0x00000100	// RO
#define XHCI_STAT_PORTCHANGE		0x00000010	// RW1C
#define XHCI_STAT_EVENTINTR			0x00000008	// RW1C
#define XHCI_STAT_HOSTSYSERROR		0x00000004	// RW1C
#define XHCI_STAT_HCHALTED			0x00000001	// RO
#define XHCI_STAT_INTERRUPTMASK \
	(XHCI_STAT_PORTCHANGE | \
	XHCI_STAT_EVENTINTR | \
	XHCI_STAT_HOSTSYSERROR)
#define XHCI_STAT_ROMASK \
	(XHCI_STAT_HOSTCTRLERR | \
	XHCI_STAT_CTRLNOTREADY | \
	XHCI_STAT_RESTSTATE | \
	XHCI_STAT_SAVESTATE | \
	XHCI_STAT_HCHALTED)
#define XHCI_STAT_RW1CMASK \
	(XHCI_STAT_SAVERESTERR | \
	XHCI_STAT_PORTCHANGE | \
	XHCI_STAT_EVENTINTR | \
	XHCI_STAT_HOSTSYSERROR)

// Bitfields for the command ring control register
#define XHCI_CRCR_CMDRNGRUNNING		0x00000008
#define XHCI_CRCR_COMMANDABORT		0x00000004
#define XHCI_CRCR_COMMANDSTOP		0x00000002
#define XHCI_CRCR_RINGCYCSTATE		0x00000001

// Bitfields for port status/control registers
#define XHCI_PORTSC_WARMRESET		0x80000000	// RW1S
#define XHCI_PORTSC_DEVNOTREMV		0x40000000	// RO
#define XHCI_PORTSC_WAKEOVCREN		0x08000000	// RWS
#define XHCI_PORTSC_WAKEDISCEN		0x04000000	// RWS
#define XHCI_PORTSC_WAKECONNEN		0x02000000	// RWS
#define XHCI_PORTSC_COLDATTACH		0x01000000	// RO
#define XHCI_PORTSC_CHANGES			0x00FE0000	// (all RW1CS)
#define XHCI_PORTSC_CONFERR_CH		0x00800000	// RW1CS
#define XHCI_PORTSC_LINKSTAT_CH		0x00400000	// RW1CS
#define XHCI_PORTSC_RESET_CH		0x00200000	// RW1CS
#define XHCI_PORTSC_OVERCURR_CH		0x00100000	// RW1CS
#define XHCI_PORTSC_WARMREST_CH		0x00080000	// RW1CS
#define XHCI_PORTSC_ENABLED_CH		0x00040000	// RW1CS
#define XHCI_PORTSC_CONNECT_CH		0x00020000	// RW1CS
#define XHCI_PORTSC_LINKWSTROBE		0x00010000	// RW
#define XHCI_PORTSC_PORTIND			0x0000C000	// RWS
#define XHCI_PORTSC_PORTSPEED		0x00003C00	// ROS
#define XHCI_PORTSC_PORTPOWER		0x00000200	// RWS
#define XHCI_PORTSC_LINKSTATE		0x000001E0	// RWS
#define XHCI_PORTSC_PORTRESET		0x00000010	// RW1S
#define XHCI_PORTSC_OVERCURRENT		0x00000008	// RO
#define XHCI_PORTSC_PORTENABLED		0x00000002	// RW1CS
#define XHCI_PORTSC_CONNECTED		0x00000001	// ROS
#define XHCI_PORTSC_ROMASK \
	(XHCI_PORTSC_DEVNOTREMV | \
	XHCI_PORTSC_COLDATTACH | \
	XHCI_PORTSC_PORTSPEED | \
	XHCI_PORTSC_OVERCURRENT | \
	XHCI_PORTSC_CONNECTED)
#define XHCI_PORTSC_RW1CMASK \
	(XHCI_PORTSC_CHANGES | \
	XHCI_PORTSC_PORTENABLED)

// Bitfields for the interrupter register set
#define XHCI_IMAN_INTSENABLED		0x00000002
#define XHCI_IMAN_INTPENDING		0x00000001
#define XHCI_IMOD_COUNTER			0xFFFF0000
#define XHCI_IMOD_INTERVAL			0x0000FFFF
#define XHCI_ERSTSZ_TABLESIZE		0x0000FFFF
#define XHCI_ERDP_HANDLERBUSY		0x00000008
#define XHCI_ERDP_SEGINDEX			0x00000007

// Endpoint types
#define XHCI_EPTYPE_INVALID			0
#define XHCI_EPTYPE_ISOCH_OUT		1
#define XHCI_EPTYPE_BULK_OUT		2
#define XHCI_EPTYPE_INTR_OUT		3
#define XHCI_EPTYPE_CONTROL			4
#define XHCI_EPTYPE_ISOCH_IN		5
#define XHCI_EPTYPE_BULK_IN			6
#define XHCI_EPTYPE_INTR_IN			7

// Bitfields for the slot context structure
#define XHCI_SLTCTXT_CTXTENTS		0xF8000000
#define XHCI_SLTCTXT_HUB			0x04000000
#define XHCI_SLTCTXT_MTT			0x02000000
#define XHCI_SLTCTXT_SPEED			0x00F00000
#define XHCI_SLTCTXT_ROUTESTRNG		0x000FFFFF
#define XHCI_SLTCTXT_NUMPORTS		0xFF000000
#define XHCI_SLTCTXT_ROOTPRTNUM		0x00FF0000
#define XHCI_SLTCTXT_MAXEXITLAT		0x0000FFFF
#define XHCI_SLTCTXT_INTRTARGET		0xFFC00000
#define XHCI_SLTCTXT_TTT			0x00030000
#define XHCI_SLTCTXT_TTPORTNUM		0x0000FF00
#define XHCI_SLTCTXT_TTHUBSLOT		0x000000FF
#define XHCI_SLTCTXT_SLOTSTATE		0xF8000000
#define XHCI_SLTCTXT_USBDEVADDR		0x000000FF

// Bitfields for the endpoint context structure
#define XHCI_EPCTXT_INTERVAL		0x00FF0000
#define XHCI_EPCTXT_LINSTRARRAY		0x00008000
#define XHCI_EPCTXT_MAXPRIMSTR		0x00007C00
#define XHCI_EPCTXT_MULT			0x00000300
#define XHCI_EPCTXT_EPSTATE			0x00000007
#define XHCI_EPCTXT_MAXPKTSIZE		0xFFFF0000
#define XHCI_EPCTXT_MAXBRSTSIZE		0x0000FF00
#define XHCI_EPCTXT_HSTINITDSBL		0x00000080
#define XHCI_EPCTXT_ENDPNTTYPE		0x00000038
#define XHCI_EPCTXT_CERR			0x00000006
#define XHCI_EPCTXT_MAXESITPAYL		0xFFFF0000
#define XHCI_EPCTXT_AVGTRBLEN		0x0000FFFF

// TRB types
#define XHCI_TRBTYPE_MASK			0xFC00
#define XHCI_TRBTYPE_RESERVED		(0 << 10)
#define XHCI_TRBTYPE_NORMAL			(1 << 10)	// Transfer ring
#define XHCI_TRBTYPE_SETUPSTG		(2 << 10)	// "
#define XHCI_TRBTYPE_DATASTG		(3 << 10)	// "
#define XHCI_TRBTYPE_STATUSSTG		(4 << 10)	// "
#define XHCI_TRBTYPE_ISOCH			(5 << 10)	// "
#define XHCI_TRBTYPE_LINK			(6 << 10)	// "
#define XHCI_TRBTYPE_EVENTDATA		(7 << 10)	// "
#define XHCI_TRBTYPE_TRANSNOOP		(8 << 10)	// "
#define XHCI_TRBTYPE_ENABLESLOT		(9 << 10)	// Command ring
#define XHCI_TRBTYPE_DISBLESLOT		(10 << 10)	// "
#define XHCI_TRBTYPE_ADDRESSDEV		(11 << 10)	// "
#define XHCI_TRBTYPE_CFGENDPT		(12 << 10)	// "
#define XHCI_TRBTYPE_EVALCNTXT		(13 << 10)	// "
#define XHCI_TRBTYPE_RESETENDPT		(14 << 10)	// "
#define XHCI_TRBTYPE_STOPENDPT		(15 << 10)	// "
#define XHCI_TRBTYPE_SETTRDQ		(16 << 10)	// "
#define XHCI_TRBTYPE_RESETDEV		(17 << 10)	// "
#define XHCI_TRBTYPE_FORCEEVNT		(18 << 10)	// "
#define XHCI_TRBTYPE_NEGBNDWDTH		(19 << 10)	// "
#define XHCI_TRBTYPE_SETLATTVAL		(20 << 10)	// "
#define XHCI_TRBTYPE_GETPORTBW		(21 << 10)	// "
#define XHCI_TRBTYPE_FORCEHDR		(22 << 10)	// "
#define XHCI_TRBTYPE_CMDNOOP		(23 << 10)	// "
#define XHCI_TRBTYPE_TRANSFER		(32 << 10)	// Event ring
#define XHCI_TRBTYPE_CMDCOMP		(33 << 10)	// "
#define XHCI_TRBTYPE_PRTSTATCHG		(34 << 10)	// "
#define XHCI_TRBTYPE_BANDWREQ		(35 << 10)	// "
#define XHCI_TRBTYPE_DOORBELL		(36 << 10)	// "
#define XHCI_TRBTYPE_HOSTCONT		(37 << 10)	// "
#define XHCI_TRBTYPE_DEVNOTIFY		(38 << 10)	// "
#define XHCI_TRBTYPE_MFIDXWRAP		(39 << 10)	// "

// TRB completion codes
#define XHCI_TRBCOMP_MASK			(0xFF << 24)
#define XHCI_TRBCOMP_INVALID		(0 << 24)
#define XHCI_TRBCOMP_SUCCESS		(1 << 24)
#define XHCI_TRBCOMP_DATABUFF		(2 << 24)
#define XHCI_TRBCOMP_BABBLE			(3 << 24)
#define XHCI_TRBCOMP_TRANS			(4 << 24)
#define XHCI_TRBCOMP_TRB			(5 << 24)
#define XHCI_TRBCOMP_STALL			(6 << 24)
#define XHCI_TRBCOMP_RESOURCE		(7 << 24)
#define XHCI_TRBCOMP_BANDWIDTH		(8 << 24)
#define XHCI_TRBCOMP_NOSLOTS		(9 << 24)
#define XHCI_TRBCOMP_INVALIDSTREAM	(10 << 24)
#define XHCI_TRBCOMP_SLOTNOTENAB	(11 << 24)
#define XHCI_TRBCOMP_ENDPTNOTENAB	(12 << 24)
#define XHCI_TRBCOMP_SHORTPACKET	(13 << 24)
#define XHCI_TRBCOMP_RINGUNDERRUN	(14 << 24)
#define XHCI_TRBCOMP_RINGOVERRUN	(15 << 24)
#define XHCI_TRBCOMP_VFEVNTRINGFULL	(16 << 24)
#define XHCI_TRBCOMP_PARAMETER		(17 << 24)
#define XHCI_TRBCOMP_BANDWOVERRUN	(18 << 24)
#define XHCI_TRBCOMP_CONTEXTSTATE	(19 << 24)
#define XHCI_TRBCOMP_NOPINGRESPONSE	(20 << 24)
#define XHCI_TRBCOMP_EVNTRINGFULL	(21 << 24)
#define XHCI_TRBCOMP_INCOMPATDEVICE	(22 << 24)
#define XHCI_TRBCOMP_MISSEDSERVICE	(23 << 24)
#define XHCI_TRBCOMP_CMDRINGSTOPPED	(24 << 24)
#define XHCI_TRBCOMP_COMMANDABORTED	(25 << 24)
#define XHCI_TRBCOMP_STOPPED		(26 << 24)
#define XHCI_TRBCOMP_STOPPEDLENGTH	(27 << 24)
#define XHCI_TRBCOMP_MAXLATTOOLARGE	(29 << 24)
#define XHCI_TRBCOMP_ISOCHBUFFOVER	(31 << 24)
#define XHCI_TRBCOMP_EVENTLOST		(32 << 24)
#define XHCI_TRBCOMP_UNDEFINED		(33 << 24)
#define XHCI_TRBCOMP_INVSTREAMID	(34 << 24)
#define XHCI_TRBCOMP_SECBANDWIDTH	(35 << 24)
#define XHCI_TRBCOMP_SPLITTRANS		(36 << 24)

// TRB flags
#define XHCI_TRBFLAG_BLKSETADDR		0x0200
#define XHCI_TRBFLAG_IMMEDDATA		0x0040
#define XHCI_TRBFLAG_INTONCOMP		0x0020
#define XHCI_TRBFLAG_CHAIN			0x0010
#define XHCI_TRBFLAG_INTONSHORT		0x0004
#define XHCI_TRBFLAG_EVALNEXT		0x0002
#define XHCI_TRBFLAG_TOGGLECYCL		0x0002
#define XHCI_TRBFLAG_CYCLE			0x0001



// Bit of symbolism to improve readability when manipulating anonymous bits,
// because I don't like constants in the code
#define BIT(num) (1 << (num))

typedef enum {
	xhcispeed_unknown = 0,
	xhcispeed_full = 1,
	xhcispeed_low = 2,
	xhcispeed_high = 3,
	xhcispeed_super = 4

} xhciDevSpeed;

#pragma pack (push,1)
// Slot context structures
typedef volatile struct {
	unsigned entFlagsSpeedRoute;
	unsigned numPortsPortLat;
	unsigned targetTT;
	unsigned slotStateDevAddr;
	unsigned res[4];

}xhciSlotCtxt32;

#pragma pack (pop)

#pragma pack (push,1)

typedef volatile struct {
	unsigned entFlagsSpeedRoute;
	unsigned numPortsPortLat;
	unsigned targetTT;
	unsigned slotStateDevAddr;
	unsigned res[12];

}xhciSlotCtxt64;

#pragma pack (pop)

#pragma pack (push,1)
// Endpoint context structures
typedef volatile struct {
	unsigned intvlLsaMaxPstrMultEpState;
	unsigned maxPSizeMaxBSizeEpTypeCerr;
	unsigned trDeqPtrLo;
	unsigned trDeqPtrHi;
	unsigned maxEpEsitAvTrbLen;
	unsigned res[3];
}xhciEndpointCtxt32;

#pragma pack (pop)

#pragma pack (push,1)
typedef volatile struct {
	unsigned intvlLsaMaxPstrMultEpState;
	unsigned maxPSizeMaxBSizeEpTypeCerr;
	unsigned trDeqPtrLo;
	unsigned trDeqPtrHi;
	unsigned maxEpEsitAvTrbLen;
	unsigned res[11];
} xhciEndpointCtxt64;
#pragma pack (pop)

#pragma pack (push,1)
// Input control context structures
typedef volatile struct {
	unsigned drop;
	unsigned add;
	unsigned res[6];

}xhciInputCtrlCtxt32;
#pragma pack (pop)

#pragma pack (push,1)
typedef volatile struct {
	unsigned drop;
	unsigned add;
	unsigned res[14];
}xhciInputCtrlCtxt64;
#pragma pack (pop)

#pragma pack (push,1)
// Device context structures
typedef volatile struct {
	xhciSlotCtxt32 slotCtxt;
	xhciEndpointCtxt32 endpointCtxt[31];
}xhciDevCtxt32;

#pragma pack (pop)

#pragma pack (push,1)
typedef volatile struct {
	xhciSlotCtxt64 slotCtxt;
	xhciEndpointCtxt64 endpointCtxt[31];
}xhciDevCtxt64;
#pragma pack (pop)

#pragma pack (push,1)
// Input context structures
typedef volatile struct {
	xhciInputCtrlCtxt32 inputCtrlCtxt;
	xhciDevCtxt32 devCtxt;
} xhciInputCtxt32;
#pragma pack (pop)

#pragma pack (push,1)
typedef volatile struct {
	xhciInputCtrlCtxt64 inputCtrlCtxt;
	xhciDevCtxt64 devCtxt;
}xhciInputCtxt64;
#pragma pack (pop)


typedef volatile struct {
	unsigned baseAddrLo;
	unsigned baseAddrHi;
	unsigned segSize;
	unsigned res;

}xhciEventRingSegTable;

// TRB (Transfer Request Block) structure
typedef volatile struct {
	unsigned paramLo;
	unsigned paramHi;
	unsigned status;
	unsigned short typeFlags;
	unsigned short control;

}xhciTrb;

// Setup TRB for control transfers
//typedef volatile struct {
//	usbDeviceRequest request;
//	unsigned intTargetTransLen;
//	unsigned short typeFlags;
//	unsigned short control;
//
//} xhciSetupTrb;

// Port register set
typedef volatile struct {
	unsigned portsc;
	unsigned portpmsc;
	unsigned portli;
	unsigned res;

} xhciPortRegSet;

// Interrupter register set
typedef volatile struct {
	unsigned intrMan;
	unsigned intrMod;
	unsigned evtRngSegTabSz;
	unsigned res;
	unsigned evtRngSegBaseLo;
	unsigned evtRngSegBaseHi;
	unsigned evtRngDeqPtrLo;
	unsigned evtRngDeqPtrHi;

}  xhciIntrRegSet;

// Runtime register set
typedef volatile struct {
	unsigned mfindex;
	char res[28];
	xhciIntrRegSet intrReg[];

} xhciRuntimeRegs;

// Doorbell register set
typedef volatile struct {
	unsigned doorbell[256];

} xhciDoorbellRegs;

// Extended capability pointer register
typedef volatile struct {
	unsigned char id;
	unsigned char next;
	unsigned short capSpec;

}  xhciExtendedCaps;

// Legacy support capability register set
typedef volatile struct {
	unsigned legSuppCap;
	unsigned legSuppContStat;

}xhciLegacySupport;

typedef volatile struct {
	unsigned suppProtCap;
	unsigned suppProtName;
	unsigned suppProtPorts;

}xhciSupportedProtocol;

#pragma pack (push,1)

typedef volatile struct {
	unsigned port_sc;
	unsigned port_pmsc;
	unsigned port_li;
	unsigned res;
} xhci_port_reg_set;
#pragma pack(pop)

#pragma pack (push,1)
typedef  struct {
	unsigned cmd;
	unsigned stat;
	unsigned pagesz;
	char res1[8];
	unsigned dncntrl;
	unsigned cmdrctrlLo;
	unsigned cmdrctrlHi;
	char res2[16];
	unsigned dcbaapLo;
	unsigned dcbaapHi;
	unsigned config;
	char res3[964];
	xhci_port_reg_set port_reg_set[256];
}xhci_op_regs;

#pragma pack (pop)


#pragma pack (push,1)

typedef struct _cap_reg_{
	unsigned caps_len_hciver;
	unsigned hcsparams1;
	unsigned hcsparams2;
	unsigned hcsparams3;
	unsigned hccparams;
	unsigned dboffset;
	unsigned runtime_offset;
} xhci_cap_reg;

#pragma pack(pop)

typedef struct {
	int numTrbs;
	int nextTrb;
	int cycleState;
	unsigned trbsPhysical;
	xhciTrb *trbs;

} xhciTrbRing;

//// A structure to store information about a device slot
//typedef struct {
//	int num;
//	usbDevice *usbDev;
//	xhciInputCtxt32 *inputCtxt32;
//	xhciInputCtxt64 *inputCtxt64;
//	unsigned inputCtxtPhysical;
//	xhciDevCtxt32 *devCtxt32;
//	xhciDevCtxt64 *devCtxt64;
//	unsigned devCtxtPhysical;
//	xhciTrbRing *transRings[USB_MAX_ENDPOINTS << 1];
//
//} xhciSlot;

// For keeping track of interrupt registrations
//typedef struct {
//	usbDevice *usbDev;
//	int interface;
//	int endpoint;
//	xhciSlot *slot;
//	void *buffer;
//	unsigned dataLen;
//	xhciTrb trb;
//	xhciTrb *queuedTrb;
//	//void (*callback)(usbDevice *, int, void *, unsigned);
//
//} xhciIntrReg;


#endif