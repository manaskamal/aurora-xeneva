; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?hw@@3PEAU_net_hw_@@EA				; hw
_BSS	SEGMENT
?hw@@3PEAU_net_hw_@@EA DQ 01H DUP (?)			; hw
_BSS	ENDS
CONST	SEGMENT
$SG2934	DB	'MAC:', 00H
	ORG $+3
$SG2939	DB	':%x', 00H
$SG2940	DB	0aH, 00H
CONST	ENDS
PUBLIC	?nethw_set_mac@@YAXPEAE@Z			; nethw_set_mac
PUBLIC	?nethw_get_mac@@YAXPEAE@Z			; nethw_get_mac
PUBLIC	?nethw_initialize@@YAXXZ			; nethw_initialize
PUBLIC	?flip_short@@YAGG@Z				; flip_short
PUBLIC	?flip_long@@YAII@Z				; flip_long
PUBLIC	?flip_byte@@YAEEH@Z				; flip_byte
PUBLIC	?htonb@@YAEEH@Z					; htonb
PUBLIC	?ntohb@@YAEEH@Z					; ntohb
PUBLIC	?htons@@YAGG@Z					; htons
PUBLIC	?htonl@@YAII@Z					; htonl
PUBLIC	?ntohs@@YAGG@Z					; ntohs
PUBLIC	?ntohl@@YAII@Z					; ntohl
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
EXTRN	memcpy:PROC
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
pdata	SEGMENT
$pdata$?nethw_set_mac@@YAXPEAE@Z DD imagerel $LN6
	DD	imagerel $LN6+121
	DD	imagerel $unwind$?nethw_set_mac@@YAXPEAE@Z
$pdata$?nethw_get_mac@@YAXPEAE@Z DD imagerel $LN3
	DD	imagerel $LN3+40
	DD	imagerel $unwind$?nethw_get_mac@@YAXPEAE@Z
$pdata$?nethw_initialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+26
	DD	imagerel $unwind$?nethw_initialize@@YAXXZ
$pdata$?flip_short@@YAGG@Z DD imagerel $LN3
	DD	imagerel $LN3+41
	DD	imagerel $unwind$?flip_short@@YAGG@Z
$pdata$?flip_long@@YAII@Z DD imagerel $LN3
	DD	imagerel $LN3+76
	DD	imagerel $unwind$?flip_long@@YAII@Z
$pdata$?flip_byte@@YAEEH@Z DD imagerel $LN3
	DD	imagerel $LN3+66
	DD	imagerel $unwind$?flip_byte@@YAEEH@Z
$pdata$?htonb@@YAEEH@Z DD imagerel $LN3
	DD	imagerel $LN3+31
	DD	imagerel $unwind$?htonb@@YAEEH@Z
$pdata$?ntohb@@YAEEH@Z DD imagerel $LN3
	DD	imagerel $LN3+38
	DD	imagerel $unwind$?ntohb@@YAEEH@Z
$pdata$?htons@@YAGG@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?htons@@YAGG@Z
$pdata$?htonl@@YAII@Z DD imagerel $LN3
	DD	imagerel $LN3+22
	DD	imagerel $unwind$?htonl@@YAII@Z
$pdata$?ntohs@@YAGG@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?ntohs@@YAGG@Z
$pdata$?ntohl@@YAII@Z DD imagerel $LN3
	DD	imagerel $LN3+22
	DD	imagerel $unwind$?ntohl@@YAII@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?nethw_set_mac@@YAXPEAE@Z DD 010901H
	DD	06209H
$unwind$?nethw_get_mac@@YAXPEAE@Z DD 010901H
	DD	04209H
$unwind$?nethw_initialize@@YAXXZ DD 010401H
	DD	04204H
$unwind$?flip_short@@YAGG@Z DD 010901H
	DD	02209H
$unwind$?flip_long@@YAII@Z DD 010801H
	DD	02208H
$unwind$?flip_byte@@YAEEH@Z DD 010c01H
	DD	0220cH
$unwind$?htonb@@YAEEH@Z DD 010c01H
	DD	0420cH
$unwind$?ntohb@@YAEEH@Z DD 010c01H
	DD	0420cH
$unwind$?htons@@YAGG@Z DD 010901H
	DD	04209H
$unwind$?htonl@@YAII@Z DD 010801H
	DD	04208H
$unwind$?ntohs@@YAGG@Z DD 010901H
	DD	04209H
$unwind$?ntohl@@YAII@Z DD 010801H
	DD	04208H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
netlong$ = 48
?ntohl@@YAII@Z PROC					; ntohl

; 83   : uint32_t ntohl (uint32_t netlong) {

$LN3:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 84   : 	return flip_long (netlong);

	mov	ecx, DWORD PTR netlong$[rsp]
	call	?flip_long@@YAII@Z			; flip_long

; 85   : }

	add	rsp, 40					; 00000028H
	ret	0
?ntohl@@YAII@Z ENDP					; ntohl
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
netshort$ = 48
?ntohs@@YAGG@Z PROC					; ntohs

; 79   : uint16_t ntohs (uint16_t netshort) {

$LN3:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 80   : 	return flip_short (netshort);

	movzx	ecx, WORD PTR netshort$[rsp]
	call	?flip_short@@YAGG@Z			; flip_short

; 81   : }

	add	rsp, 40					; 00000028H
	ret	0
?ntohs@@YAGG@Z ENDP					; ntohs
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
hostlong$ = 48
?htonl@@YAII@Z PROC					; htonl

; 75   : uint32_t htonl (uint32_t hostlong) {

$LN3:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 76   : 	return flip_long (hostlong);

	mov	ecx, DWORD PTR hostlong$[rsp]
	call	?flip_long@@YAII@Z			; flip_long

; 77   : }

	add	rsp, 40					; 00000028H
	ret	0
?htonl@@YAII@Z ENDP					; htonl
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
hostshort$ = 48
?htons@@YAGG@Z PROC					; htons

; 71   : uint16_t htons (uint16_t hostshort) {

$LN3:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 72   : 	return flip_short (hostshort);

	movzx	ecx, WORD PTR hostshort$[rsp]
	call	?flip_short@@YAGG@Z			; flip_short

; 73   : }

	add	rsp, 40					; 00000028H
	ret	0
?htons@@YAGG@Z ENDP					; htons
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
byte$ = 48
num_bits$ = 56
?ntohb@@YAEEH@Z PROC					; ntohb

; 66   : uint8_t ntohb (uint8_t byte, int num_bits) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H

; 67   : 	return flip_byte (byte, 8 - num_bits);

	mov	eax, 8
	sub	eax, DWORD PTR num_bits$[rsp]
	mov	edx, eax
	movzx	ecx, BYTE PTR byte$[rsp]
	call	?flip_byte@@YAEEH@Z			; flip_byte

; 68   : }

	add	rsp, 40					; 00000028H
	ret	0
?ntohb@@YAEEH@Z ENDP					; ntohb
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
byte$ = 48
num_bits$ = 56
?htonb@@YAEEH@Z PROC					; htonb

; 62   : uint8_t htonb (uint8_t byte, int num_bits) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H

; 63   : 	return flip_byte (byte, num_bits);

	mov	edx, DWORD PTR num_bits$[rsp]
	movzx	ecx, BYTE PTR byte$[rsp]
	call	?flip_byte@@YAEEH@Z			; flip_byte

; 64   : }

	add	rsp, 40					; 00000028H
	ret	0
?htonb@@YAEEH@Z ENDP					; htonb
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
t$ = 0
tv69 = 4
byte$ = 32
num_bits$ = 40
?flip_byte@@YAEEH@Z PROC				; flip_byte

; 57   : uint8_t flip_byte (uint8_t byte, int num_bits) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 24

; 58   : 	uint8_t t = byte << (8 - num_bits);

	movzx	eax, BYTE PTR byte$[rsp]
	mov	ecx, 8
	sub	ecx, DWORD PTR num_bits$[rsp]
	shl	eax, cl
	mov	BYTE PTR t$[rsp], al

; 59   : 	return t | (byte >> num_bits);

	movzx	eax, BYTE PTR t$[rsp]
	movzx	ecx, BYTE PTR byte$[rsp]
	mov	DWORD PTR tv69[rsp], ecx
	mov	edx, DWORD PTR num_bits$[rsp]
	movzx	ecx, dl
	mov	edx, DWORD PTR tv69[rsp]
	sar	edx, cl
	mov	ecx, edx
	or	eax, ecx

; 60   : }

	add	rsp, 24
	ret	0
?flip_byte@@YAEEH@Z ENDP				; flip_byte
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
first_byte$ = 0
second_byte$ = 4
third_byte$ = 8
fourth_byte$ = 12
long_int$ = 32
?flip_long@@YAII@Z PROC					; flip_long

; 49   : uint32_t flip_long (uint32_t long_int) {

$LN3:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 24

; 50   : 	uint32_t first_byte = *((uint8_t*)(&long_int));

	movzx	eax, BYTE PTR long_int$[rsp]
	mov	DWORD PTR first_byte$[rsp], eax

; 51   : 	uint32_t second_byte = *((uint8_t*)(&long_int) + 1);

	movzx	eax, BYTE PTR long_int$[rsp+1]
	mov	DWORD PTR second_byte$[rsp], eax

; 52   : 	uint32_t third_byte = *((uint8_t*)(&long_int) + 2);

	movzx	eax, BYTE PTR long_int$[rsp+2]
	mov	DWORD PTR third_byte$[rsp], eax

; 53   : 	uint32_t fourth_byte = *((uint8_t*)(&long_int) + 3);

	movzx	eax, BYTE PTR long_int$[rsp+3]
	mov	DWORD PTR fourth_byte$[rsp], eax

; 54   : 	return (first_byte << 24) | (second_byte << 16) | (third_byte << 8) | (fourth_byte);

	mov	eax, DWORD PTR first_byte$[rsp]
	shl	eax, 24
	mov	ecx, DWORD PTR second_byte$[rsp]
	shl	ecx, 16
	or	eax, ecx
	mov	ecx, DWORD PTR third_byte$[rsp]
	shl	ecx, 8
	or	eax, ecx
	or	eax, DWORD PTR fourth_byte$[rsp]

; 55   : }

	add	rsp, 24
	ret	0
?flip_long@@YAII@Z ENDP					; flip_long
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
first_byte$ = 0
second_byte$ = 4
short_int$ = 32
?flip_short@@YAGG@Z PROC				; flip_short

; 43   : uint16_t flip_short (uint16_t short_int) {

$LN3:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 24

; 44   : 	uint32_t first_byte = *((uint8_t*)(&short_int));

	movzx	eax, BYTE PTR short_int$[rsp]
	mov	DWORD PTR first_byte$[rsp], eax

; 45   : 	uint32_t second_byte = *((uint8_t*)(&short_int) + 1);

	movzx	eax, BYTE PTR short_int$[rsp+1]
	mov	DWORD PTR second_byte$[rsp], eax

; 46   : 	return (first_byte << 8) | (second_byte);

	mov	eax, DWORD PTR first_byte$[rsp]
	shl	eax, 8
	or	eax, DWORD PTR second_byte$[rsp]

; 47   : }

	add	rsp, 24
	ret	0
?flip_short@@YAGG@Z ENDP				; flip_short
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
?nethw_initialize@@YAXXZ PROC				; nethw_initialize

; 35   : void nethw_initialize () {

$LN3:
	sub	rsp, 40					; 00000028H

; 36   : 	hw = (net_hw_t*)malloc (sizeof(net_hw_t));

	mov	ecx, 6
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR ?hw@@3PEAU_net_hw_@@EA, rax	; hw

; 37   : }

	add	rsp, 40					; 00000028H
	ret	0
?nethw_initialize@@YAXXZ ENDP				; nethw_initialize
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
dst_mac$ = 48
?nethw_get_mac@@YAXPEAE@Z PROC				; nethw_get_mac

; 30   : void nethw_get_mac (uint8_t* dst_mac) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 31   : 	memcpy (dst_mac, hw->mac, 6);

	mov	rax, QWORD PTR ?hw@@3PEAU_net_hw_@@EA	; hw
	mov	r8d, 6
	mov	rdx, rax
	mov	rcx, QWORD PTR dst_mac$[rsp]
	call	memcpy

; 32   : }

	add	rsp, 40					; 00000028H
	ret	0
?nethw_get_mac@@YAXPEAE@Z ENDP				; nethw_get_mac
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\net\nethw.cpp
_TEXT	SEGMENT
i$1 = 32
mac$ = 64
?nethw_set_mac@@YAXPEAE@Z PROC				; nethw_set_mac

; 21   : void nethw_set_mac (uint8_t* mac) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 22   : 	memcpy (hw->mac, mac, 6);

	mov	rax, QWORD PTR ?hw@@3PEAU_net_hw_@@EA	; hw
	mov	r8d, 6
	mov	rdx, QWORD PTR mac$[rsp]
	mov	rcx, rax
	call	memcpy

; 23   : 	printf ("MAC:");

	lea	rcx, OFFSET FLAT:$SG2934
	call	?printf@@YAXPEBDZZ			; printf

; 24   : 	for (int i = 0; i < 6; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@nethw_set_
$LN2@nethw_set_:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@nethw_set_:
	cmp	DWORD PTR i$1[rsp], 6
	jge	SHORT $LN1@nethw_set_

; 25   : 		printf (":%x", mac[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR mac$[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG2939
	call	?printf@@YAXPEBDZZ			; printf
	jmp	SHORT $LN2@nethw_set_
$LN1@nethw_set_:

; 26   : 	printf ("\n");

	lea	rcx, OFFSET FLAT:$SG2940
	call	?printf@@YAXPEBDZZ			; printf

; 27   : }

	add	rsp, 56					; 00000038H
	ret	0
?nethw_set_mac@@YAXPEAE@Z ENDP				; nethw_set_mac
_TEXT	ENDS
END
