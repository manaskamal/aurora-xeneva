; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?arp_table@@3PEAU_arp_table_@@EA		; arp_table
PUBLIC	?arp_table_size@@3HA				; arp_table_size
PUBLIC	?arp_table_curr@@3HA				; arp_table_curr
PUBLIC	?broadcast_mac_address@@3PAEA			; broadcast_mac_address
_BSS	SEGMENT
?arp_table@@3PEAU_arp_table_@@EA DQ 01H DUP (?)		; arp_table
?arp_table_size@@3HA DD 01H DUP (?)			; arp_table_size
?arp_table_curr@@3HA DD 01H DUP (?)			; arp_table_curr
_BSS	ENDS
CONST	SEGMENT
$SG2990	DB	'Address Resolution Protocol Initialized', 0aH, 00H
CONST	ENDS
_DATA	SEGMENT
?broadcast_mac_address@@3PAEA DB 0ffH			; broadcast_mac_address
	DB	0ffH
	DB	0ffH
	DB	0ffH
	DB	0ffH
	DB	0ffH
_DATA	ENDS
PUBLIC	?arp_initialize@@YAXXZ				; arp_initialize
PUBLIC	?arp_send_packet@@YAXPEAE0@Z			; arp_send_packet
PUBLIC	?arp_broadcast@@YAXXZ				; arp_broadcast
PUBLIC	?arp_lookup_add@@YAXPEAE0@Z			; arp_lookup_add
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
EXTRN	?ethernet_send_packet@@YAHPEAE0HG@Z:PROC	; ethernet_send_packet
EXTRN	?nethw_get_mac@@YAXPEAE@Z:PROC			; nethw_get_mac
EXTRN	?htons@@YAGG@Z:PROC				; htons
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	memcpy:PROC
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
pdata	SEGMENT
$pdata$?arp_initialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+89
	DD	imagerel $unwind$?arp_initialize@@YAXXZ
$pdata$?arp_send_packet@@YAXPEAE0@Z DD imagerel $LN3
	DD	imagerel $LN3+282
	DD	imagerel $unwind$?arp_send_packet@@YAXPEAE0@Z
$pdata$?arp_broadcast@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+348
	DD	imagerel $unwind$?arp_broadcast@@YAXXZ
$pdata$?arp_lookup_add@@YAXPEAE0@Z DD imagerel $LN5
	DD	imagerel $LN5+152
	DD	imagerel $unwind$?arp_lookup_add@@YAXPEAE0@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?arp_initialize@@YAXXZ DD 010401H
	DD	06204H
$unwind$?arp_send_packet@@YAXPEAE0@Z DD 010e01H
	DD	0620eH
$unwind$?arp_broadcast@@YAXXZ DD 010401H
	DD	06204H
$unwind$?arp_lookup_add@@YAXPEAE0@Z DD 010e01H
	DD	0420eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\arp.cpp
_TEXT	SEGMENT
ret_hardware_addr$ = 48
ip_addr$ = 56
?arp_lookup_add@@YAXPEAE0@Z PROC			; arp_lookup_add

; 50   : void arp_lookup_add (uint8_t *ret_hardware_addr, uint8_t* ip_addr) {

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 51   : 	memcpy (&arp_table[arp_table_curr].ip_addr, ip_addr, 4);

	movsxd	rax, DWORD PTR ?arp_table_curr@@3HA	; arp_table_curr
	imul	rax, 16
	mov	rcx, QWORD PTR ?arp_table@@3PEAU_arp_table_@@EA ; arp_table
	add	rcx, rax
	mov	rax, rcx
	mov	r8d, 4
	mov	rdx, QWORD PTR ip_addr$[rsp]
	mov	rcx, rax
	call	memcpy

; 52   : 	memcpy (&arp_table[arp_table_curr].mac_addr, ret_hardware_addr, 6);

	movsxd	rax, DWORD PTR ?arp_table_curr@@3HA	; arp_table_curr
	imul	rax, 16
	mov	rcx, QWORD PTR ?arp_table@@3PEAU_arp_table_@@EA ; arp_table
	lea	rax, QWORD PTR [rcx+rax+8]
	mov	r8d, 6
	mov	rdx, QWORD PTR ret_hardware_addr$[rsp]
	mov	rcx, rax
	call	memcpy

; 53   : 	if (arp_table_size < 512)

	cmp	DWORD PTR ?arp_table_size@@3HA, 512	; arp_table_size, 00000200H
	jge	SHORT $LN2@arp_lookup

; 54   : 		arp_table_size++;

	mov	eax, DWORD PTR ?arp_table_size@@3HA	; arp_table_size
	inc	eax
	mov	DWORD PTR ?arp_table_size@@3HA, eax	; arp_table_size
$LN2@arp_lookup:

; 55   : 	if (arp_table_curr >= 512)

	cmp	DWORD PTR ?arp_table_curr@@3HA, 512	; arp_table_curr, 00000200H
	jl	SHORT $LN1@arp_lookup

; 56   : 		arp_table_curr = 0;

	mov	DWORD PTR ?arp_table_curr@@3HA, 0	; arp_table_curr
$LN1@arp_lookup:

; 57   : }

	add	rsp, 40					; 00000028H
	ret	0
?arp_lookup_add@@YAXPEAE0@Z ENDP			; arp_lookup_add
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\arp.cpp
_TEXT	SEGMENT
pack$ = 32
?arp_broadcast@@YAXXZ PROC				; arp_broadcast

; 71   : void arp_broadcast() {

$LN3:
	sub	rsp, 56					; 00000038H

; 72   : 	arp_packet_t *pack = (arp_packet_t*)malloc(sizeof(arp_packet_t));

	mov	ecx, 28
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR pack$[rsp], rax

; 73   : 	pack->hw_type = 0x0100;

	mov	eax, 256				; 00000100H
	mov	rcx, QWORD PTR pack$[rsp]
	mov	WORD PTR [rcx], ax

; 74   : 	pack->protocol = 0x0008; //ipv4

	mov	eax, 8
	mov	rcx, QWORD PTR pack$[rsp]
	mov	WORD PTR [rcx+2], ax

; 75   : 	pack->hw_addr_len = 6;

	mov	rax, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rax+4], 6

; 76   : 	pack->protocol_addr_len = 4;

	mov	rax, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rax+5], 4

; 77   : 	pack->opcode = 0x0200; //"response"

	mov	eax, 512				; 00000200H
	mov	rcx, QWORD PTR pack$[rsp]
	mov	WORD PTR [rcx+6], ax

; 78   : 	
; 79   : 
; 80   : 	nethw_get_mac(pack->src_hw_addr);

	mov	rax, QWORD PTR pack$[rsp]
	add	rax, 8
	mov	rcx, rax
	call	?nethw_get_mac@@YAXPEAE@Z		; nethw_get_mac

; 81   : 	pack->src_protocol_addr[0] = 10;

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+14], 10

; 82   : 	pack->src_protocol_addr[1] = 0;

	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+14], 0

; 83   : 	pack->src_protocol_addr[2] = 2;

	mov	eax, 1
	imul	rax, 2
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+14], 2

; 84   : 	pack->src_protocol_addr[3] = 14;

	mov	eax, 1
	imul	rax, 3
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+14], 14

; 85   : 
; 86   : 	pack->dst_hw_addr[0] = 0xFF;

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+18], 255		; 000000ffH

; 87   : 	pack->dst_hw_addr[1] = 0xFF;

	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+18], 255		; 000000ffH

; 88   : 	pack->dst_hw_addr[2] = 0xFF;

	mov	eax, 1
	imul	rax, 2
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+18], 255		; 000000ffH

; 89   : 	pack->dst_hw_addr[3] = 0xFF;

	mov	eax, 1
	imul	rax, 3
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+18], 255		; 000000ffH

; 90   : 	pack->dst_hw_addr[4] = 0xFF;

	mov	eax, 1
	imul	rax, 4
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+18], 255		; 000000ffH

; 91   : 	pack->dst_hw_addr[5] = 0xFF;

	mov	eax, 1
	imul	rax, 5
	mov	rcx, QWORD PTR pack$[rsp]
	mov	BYTE PTR [rcx+rax+18], 255		; 000000ffH

; 92   : 	
; 93   : 	memset(pack->dst_protocol_addr, 0xff, 4); 

	mov	rax, QWORD PTR pack$[rsp]
	add	rax, 24
	mov	r8d, 4
	mov	dl, 255					; 000000ffH
	mov	rcx, rax
	call	?memset@@YAXPEAXEI@Z			; memset

; 94   : 
; 95   : 	ethernet_send_packet (pack->dst_hw_addr, (uint8_t*)pack, sizeof(arp_packet_t),ETHERNET_TYPE_ARP);

	mov	rax, QWORD PTR pack$[rsp]
	add	rax, 18
	mov	r9w, 2054				; 00000806H
	mov	r8d, 28
	mov	rdx, QWORD PTR pack$[rsp]
	mov	rcx, rax
	call	?ethernet_send_packet@@YAHPEAE0HG@Z	; ethernet_send_packet

; 96   : }

	add	rsp, 56					; 00000038H
	ret	0
?arp_broadcast@@YAXXZ ENDP				; arp_broadcast
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\arp.cpp
_TEXT	SEGMENT
arp_packet$ = 32
dst_hardware_addr$ = 64
dst_protocol_addr$ = 72
?arp_send_packet@@YAXPEAE0@Z PROC			; arp_send_packet

; 25   : void arp_send_packet (uint8_t *dst_hardware_addr, uint8_t* dst_protocol_addr) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 26   : 	arp_packet_t *arp_packet = (arp_packet_t*)malloc(sizeof(arp_packet_t));

	mov	ecx, 28
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR arp_packet$[rsp], rax

; 27   : 
; 28   : 	nethw_get_mac (arp_packet->src_hw_addr);

	mov	rax, QWORD PTR arp_packet$[rsp]
	add	rax, 8
	mov	rcx, rax
	call	?nethw_get_mac@@YAXPEAE@Z		; nethw_get_mac

; 29   : 	arp_packet->src_protocol_addr[0] = 10;

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR arp_packet$[rsp]
	mov	BYTE PTR [rcx+rax+14], 10

; 30   : 	arp_packet->src_protocol_addr[1] = 0;

	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR arp_packet$[rsp]
	mov	BYTE PTR [rcx+rax+14], 0

; 31   : 	arp_packet->src_protocol_addr[2] = 2;

	mov	eax, 1
	imul	rax, 2
	mov	rcx, QWORD PTR arp_packet$[rsp]
	mov	BYTE PTR [rcx+rax+14], 2

; 32   : 	arp_packet->src_protocol_addr[3] = 14;

	mov	eax, 1
	imul	rax, 3
	mov	rcx, QWORD PTR arp_packet$[rsp]
	mov	BYTE PTR [rcx+rax+14], 14

; 33   : 
; 34   : 	memcpy (arp_packet->dst_hw_addr, dst_hardware_addr, 6);

	mov	rax, QWORD PTR arp_packet$[rsp]
	add	rax, 18
	mov	r8d, 6
	mov	rdx, QWORD PTR dst_hardware_addr$[rsp]
	mov	rcx, rax
	call	memcpy

; 35   : 	memcpy (arp_packet->dst_protocol_addr, dst_protocol_addr, 4);

	mov	rax, QWORD PTR arp_packet$[rsp]
	add	rax, 24
	mov	r8d, 4
	mov	rdx, QWORD PTR dst_protocol_addr$[rsp]
	mov	rcx, rax
	call	memcpy

; 36   : 
; 37   : 	arp_packet->opcode = htons(ARP_REQUEST);

	mov	cx, 1
	call	?htons@@YAGG@Z				; htons
	mov	rcx, QWORD PTR arp_packet$[rsp]
	mov	WORD PTR [rcx+6], ax

; 38   : 
; 39   : 	arp_packet->hw_addr_len = 6;

	mov	rax, QWORD PTR arp_packet$[rsp]
	mov	BYTE PTR [rax+4], 6

; 40   : 	arp_packet->protocol_addr_len = 4;

	mov	rax, QWORD PTR arp_packet$[rsp]
	mov	BYTE PTR [rax+5], 4

; 41   : 
; 42   : 	arp_packet->hw_type = htons(HARDWARE_TYPE_ETHERNET);

	mov	cx, 1
	call	?htons@@YAGG@Z				; htons
	mov	rcx, QWORD PTR arp_packet$[rsp]
	mov	WORD PTR [rcx], ax

; 43   : 
; 44   : 	//! Set protocol ipv4
; 45   : 	arp_packet->protocol = htons(ETHERNET_TYPE_IP);

	mov	cx, 2048				; 00000800H
	call	?htons@@YAGG@Z				; htons
	mov	rcx, QWORD PTR arp_packet$[rsp]
	mov	WORD PTR [rcx+2], ax

; 46   : 
; 47   : 	ethernet_send_packet (broadcast_mac_address, (uint8_t*)arp_packet, sizeof(arp_packet_t), ETHERNET_TYPE_ARP);

	mov	r9w, 2054				; 00000806H
	mov	r8d, 28
	mov	rdx, QWORD PTR arp_packet$[rsp]
	lea	rcx, OFFSET FLAT:?broadcast_mac_address@@3PAEA ; broadcast_mac_address
	call	?ethernet_send_packet@@YAHPEAE0HG@Z	; ethernet_send_packet

; 48   : }

	add	rsp, 56					; 00000038H
	ret	0
?arp_send_packet@@YAXPEAE0@Z ENDP			; arp_send_packet
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\arp.cpp
_TEXT	SEGMENT
broadcast_ip$ = 32
broadcast_mac$ = 36
?arp_initialize@@YAXXZ PROC				; arp_initialize

; 59   : void arp_initialize () {

$LN3:
	sub	rsp, 56					; 00000038H

; 60   : 	arp_table = (arp_table_entry_t*)malloc(512);

	mov	ecx, 512				; 00000200H
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR ?arp_table@@3PEAU_arp_table_@@EA, rax ; arp_table

; 61   : 	uint8_t broadcast_ip[4];
; 62   : 	uint8_t broadcast_mac[6];
; 63   : 
; 64   : 	memset(broadcast_ip, 0xff, 4);

	mov	r8d, 4
	mov	dl, 255					; 000000ffH
	lea	rcx, QWORD PTR broadcast_ip$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 65   : 	memset(broadcast_mac, 0xff, 6);

	mov	r8d, 6
	mov	dl, 255					; 000000ffH
	lea	rcx, QWORD PTR broadcast_mac$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 66   : 	arp_lookup_add (broadcast_mac, broadcast_ip);

	lea	rdx, QWORD PTR broadcast_ip$[rsp]
	lea	rcx, QWORD PTR broadcast_mac$[rsp]
	call	?arp_lookup_add@@YAXPEAE0@Z		; arp_lookup_add

; 67   : 	printf ("Address Resolution Protocol Initialized\n");

	lea	rcx, OFFSET FLAT:$SG2990
	call	?printf@@YAXPEBDZZ			; printf

; 68   : }

	add	rsp, 56					; 00000038H
	ret	0
?arp_initialize@@YAXXZ ENDP				; arp_initialize
_TEXT	ENDS
END
