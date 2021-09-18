; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3372	DB	'Ethernet Protocol Received ->> ARP type', 0aH, 00H
	ORG $+7
$SG3374	DB	'Ethernet Protocol Received packet ->> IP Packet', 0aH, 00H
CONST	ENDS
PUBLIC	?ethernet_send_packet@@YAHPEAE0HG@Z		; ethernet_send_packet
PUBLIC	?ethernet_handle_packet@@YAXPEAU_ethernet_frame_@@H@Z ; ethernet_handle_packet
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
EXTRN	?mfree@@YAXPEAX@Z:PROC				; mfree
EXTRN	?nethw_get_mac@@YAXPEAE@Z:PROC			; nethw_get_mac
EXTRN	?htons@@YAGG@Z:PROC				; htons
EXTRN	?ntohs@@YAGG@Z:PROC				; ntohs
EXTRN	memcpy:PROC
EXTRN	?e1000_send_packet@@YAXPEAX_K@Z:PROC		; e1000_send_packet
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
pdata	SEGMENT
$pdata$?ethernet_send_packet@@YAHPEAE0HG@Z DD imagerel $LN3
	DD	imagerel $LN3+204
	DD	imagerel $unwind$?ethernet_send_packet@@YAHPEAE0HG@Z
$pdata$?ethernet_handle_packet@@YAXPEAU_ethernet_frame_@@H@Z DD imagerel $LN5
	DD	imagerel $LN5+119
	DD	imagerel $unwind$?ethernet_handle_packet@@YAXPEAU_ethernet_frame_@@H@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?ethernet_send_packet@@YAHPEAE0HG@Z DD 011901H
	DD	08219H
$unwind$?ethernet_handle_packet@@YAXPEAU_ethernet_frame_@@H@Z DD 010d01H
	DD	0620dH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\ethernet.cpp
_TEXT	SEGMENT
data_len$ = 32
data$ = 40
packet$ = 64
len$ = 72
?ethernet_handle_packet@@YAXPEAU_ethernet_frame_@@H@Z PROC ; ethernet_handle_packet

; 45   : void ethernet_handle_packet (ethernet_frame_t * packet, int len) {

$LN5:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 46   : 	void* data = (void*)(packet + sizeof(ethernet_frame_t));

	mov	rax, QWORD PTR packet$[rsp]
	add	rax, 196				; 000000c4H
	mov	QWORD PTR data$[rsp], rax

; 47   : 	int data_len = len - sizeof(ethernet_frame_t);

	movsxd	rax, DWORD PTR len$[rsp]
	sub	rax, 14
	mov	DWORD PTR data_len$[rsp], eax

; 48   : 	if(ntohs(packet->type) == ETHERNET_TYPE_ARP) {

	mov	rax, QWORD PTR packet$[rsp]
	movzx	ecx, WORD PTR [rax+12]
	call	?ntohs@@YAGG@Z				; ntohs
	movzx	eax, ax
	cmp	eax, 2054				; 00000806H
	jne	SHORT $LN2@ethernet_h

; 49   : 		printf ("Ethernet Protocol Received ->> ARP type\n");

	lea	rcx, OFFSET FLAT:$SG3372
	call	?printf@@YAXPEBDZZ			; printf
$LN2@ethernet_h:

; 50   : 		//arp_handle_packet
; 51   : 	}
; 52   : 
; 53   : 	//!IP packets (TCP, UDP, or others)
; 54   : 	if (ntohs(packet->type) == ETHERNET_TYPE_IP) {

	mov	rax, QWORD PTR packet$[rsp]
	movzx	ecx, WORD PTR [rax+12]
	call	?ntohs@@YAGG@Z				; ntohs
	movzx	eax, ax
	cmp	eax, 2048				; 00000800H
	jne	SHORT $LN1@ethernet_h

; 55   : 		printf ("Ethernet Protocol Received packet ->> IP Packet\n");

	lea	rcx, OFFSET FLAT:$SG3374
	call	?printf@@YAXPEBDZZ			; printf
$LN1@ethernet_h:

; 56   : 	}
; 57   : }

	add	rsp, 56					; 00000038H
	ret	0
?ethernet_handle_packet@@YAXPEAU_ethernet_frame_@@H@Z ENDP ; ethernet_handle_packet
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\ethernet.cpp
_TEXT	SEGMENT
src_mac_addr$ = 32
frame$ = 40
frame_data$ = 48
dst_mac_addr$ = 80
data$ = 88
len$ = 96
protocol$ = 104
?ethernet_send_packet@@YAHPEAE0HG@Z PROC		; ethernet_send_packet

; 19   : int ethernet_send_packet (uint8_t* dst_mac_addr, uint8_t *data, int len, uint16_t protocol) {

$LN3:
	mov	WORD PTR [rsp+32], r9w
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 20   : 
; 21   : 	uint8_t src_mac_addr[6];
; 22   : 	ethernet_frame_t *frame = (ethernet_frame_t*)malloc (sizeof(ethernet_frame_t) + len);

	movsxd	rax, DWORD PTR len$[rsp]
	add	rax, 14
	mov	ecx, eax
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR frame$[rsp], rax

; 23   : 	void *frame_data = (void*)(frame + sizeof(ethernet_frame_t));

	mov	rax, QWORD PTR frame$[rsp]
	add	rax, 196				; 000000c4H
	mov	QWORD PTR frame_data$[rsp], rax

; 24   : 
; 25   : 	//! get the src mac address
; 26   : 	nethw_get_mac (src_mac_addr);

	lea	rcx, QWORD PTR src_mac_addr$[rsp]
	call	?nethw_get_mac@@YAXPEAE@Z		; nethw_get_mac

; 27   : 
; 28   : 	//! fill in source and destination mac address
; 29   : 	memcpy (frame->src_mac_addr, src_mac_addr, 6);

	mov	rax, QWORD PTR frame$[rsp]
	add	rax, 6
	mov	r8d, 6
	lea	rdx, QWORD PTR src_mac_addr$[rsp]
	mov	rcx, rax
	call	memcpy

; 30   : 	memcpy (frame->dst_mac_addr, dst_mac_addr, 6);

	mov	rax, QWORD PTR frame$[rsp]
	mov	r8d, 6
	mov	rdx, QWORD PTR dst_mac_addr$[rsp]
	mov	rcx, rax
	call	memcpy

; 31   : 
; 32   : 	//!fill in data
; 33   : 	memcpy (frame_data,data, len);

	mov	r8d, DWORD PTR len$[rsp]
	mov	rdx, QWORD PTR data$[rsp]
	mov	rcx, QWORD PTR frame_data$[rsp]
	call	memcpy

; 34   : 
; 35   : 	//!fill in type
; 36   : 	frame->type = htons(protocol);

	movzx	ecx, WORD PTR protocol$[rsp]
	call	?htons@@YAGG@Z				; htons
	mov	rcx, QWORD PTR frame$[rsp]
	mov	WORD PTR [rcx+12], ax

; 37   : 
; 38   : 	//!Send packet
; 39   : 	e1000_send_packet (frame, sizeof(ethernet_frame_t) + len);

	movsxd	rax, DWORD PTR len$[rsp]
	add	rax, 14
	mov	rdx, rax
	mov	rcx, QWORD PTR frame$[rsp]
	call	?e1000_send_packet@@YAXPEAX_K@Z		; e1000_send_packet

; 40   : 	mfree (frame);

	mov	rcx, QWORD PTR frame$[rsp]
	call	?mfree@@YAXPEAX@Z			; mfree

; 41   : 	return len;

	mov	eax, DWORD PTR len$[rsp]

; 42   : }

	add	rsp, 72					; 00000048H
	ret	0
?ethernet_send_packet@@YAHPEAE0HG@Z ENDP		; ethernet_send_packet
_TEXT	ENDS
END
