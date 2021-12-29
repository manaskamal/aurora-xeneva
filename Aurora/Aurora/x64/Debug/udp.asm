; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG2983	DB	'UDP Packet sent', 0aH, 00H
CONST	ENDS
PUBLIC	?udp_send_packet@@YAXPEAEGGPEAXH@Z		; udp_send_packet
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
EXTRN	?htons@@YAGG@Z:PROC				; htons
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	memcpy:PROC
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
pdata	SEGMENT
$pdata$?udp_send_packet@@YAXPEAEGGPEAXH@Z DD imagerel $LN3
	DD	imagerel $LN3+181
	DD	imagerel $unwind$?udp_send_packet@@YAXPEAEGGPEAXH@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?udp_send_packet@@YAXPEAEGGPEAXH@Z DD 011901H
	DD	06219H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\udp.cpp
_TEXT	SEGMENT
length$ = 32
packet$ = 40
dst_ip$ = 64
src_port$ = 72
dst_port$ = 80
data$ = 88
len$ = 96
?udp_send_packet@@YAXPEAEGGPEAXH@Z PROC			; udp_send_packet

; 19   : void udp_send_packet (uint8_t* dst_ip, uint16_t src_port, uint16_t dst_port, void* data, int len) {

$LN3:
	mov	QWORD PTR [rsp+32], r9
	mov	WORD PTR [rsp+24], r8w
	mov	WORD PTR [rsp+16], dx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 20   : 	int length = sizeof(udp_packet_t) + len;

	movsxd	rax, DWORD PTR len$[rsp]
	add	rax, 8
	mov	DWORD PTR length$[rsp], eax

; 21   : 	udp_packet_t *packet = (udp_packet_t*)malloc(length);

	mov	ecx, DWORD PTR length$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR packet$[rsp], rax

; 22   : 	memset(packet, 0, sizeof(udp_packet_t));

	mov	r8d, 8
	xor	edx, edx
	mov	rcx, QWORD PTR packet$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 23   : 	packet->src_port = htons (src_port);

	movzx	ecx, WORD PTR src_port$[rsp]
	call	?htons@@YAGG@Z				; htons
	mov	rcx, QWORD PTR packet$[rsp]
	mov	WORD PTR [rcx], ax

; 24   : 	packet->dst_port = htons (dst_port);

	movzx	ecx, WORD PTR dst_port$[rsp]
	call	?htons@@YAGG@Z				; htons
	mov	rcx, QWORD PTR packet$[rsp]
	mov	WORD PTR [rcx+2], ax

; 25   : 	packet->length = htons (length);

	movzx	ecx, WORD PTR length$[rsp]
	call	?htons@@YAGG@Z				; htons
	mov	rcx, QWORD PTR packet$[rsp]
	mov	WORD PTR [rcx+4], ax

; 26   : 	packet->checksum = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR packet$[rsp]
	mov	WORD PTR [rcx+6], ax

; 27   : 
; 28   : 	memcpy ((void*)(packet + sizeof(udp_packet_t)), data, len);

	mov	rax, QWORD PTR packet$[rsp]
	add	rax, 64					; 00000040H
	mov	r8d, DWORD PTR len$[rsp]
	mov	rdx, QWORD PTR data$[rsp]
	mov	rcx, rax
	call	memcpy

; 29   : 	printf ("UDP Packet sent\n");

	lea	rcx, OFFSET FLAT:$SG2983
	call	?printf@@YAXPEBDZZ			; printf

; 30   : 	//not completed
; 31   : }

	add	rsp, 56					; 00000038H
	ret	0
?udp_send_packet@@YAXPEAEGGPEAXH@Z ENDP			; udp_send_packet
_TEXT	ENDS
END
