; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?advance_pointer@@YAXPEAU_circ_buf_@@@Z		; advance_pointer
PUBLIC	?retreat_pointer@@YAXPEAU_circ_buf_@@@Z		; retreat_pointer
PUBLIC	?circ_buf_reset@@YAXPEAU_circ_buf_@@@Z		; circ_buf_reset
PUBLIC	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z	; circ_buf_init
PUBLIC	?circ_buf_free@@YAXPEAU_circ_buf_@@@Z		; circ_buf_free
PUBLIC	?circular_buf_size@@YA_KPEAU_circ_buf_@@@Z	; circular_buf_size
PUBLIC	?circular_buf_capacity@@YA_KPEAU_circ_buf_@@@Z	; circular_buf_capacity
PUBLIC	?circular_buf_put@@YAXPEAU_circ_buf_@@H@Z	; circular_buf_put
PUBLIC	?circular_buf_put2@@YAHPEAU_circ_buf_@@H@Z	; circular_buf_put2
PUBLIC	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z	; circular_buf_get
PUBLIC	?circular_buf_empty@@YA_NPEAU_circ_buf_@@@Z	; circular_buf_empty
PUBLIC	?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z	; circular_buf_full
EXTRN	?malloc@@YAPEAX_K@Z:PROC			; malloc
EXTRN	?free@@YAXPEAX@Z:PROC				; free
pdata	SEGMENT
$pdata$?advance_pointer@@YAXPEAU_circ_buf_@@@Z DD imagerel $LN6
	DD	imagerel $LN6+145
	DD	imagerel $unwind$?advance_pointer@@YAXPEAU_circ_buf_@@@Z
$pdata$?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z DD imagerel $LN3
	DD	imagerel $LN3+76
	DD	imagerel $unwind$?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z
$pdata$?circ_buf_free@@YAXPEAU_circ_buf_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?circ_buf_free@@YAXPEAU_circ_buf_@@@Z
$pdata$?circular_buf_size@@YA_KPEAU_circ_buf_@@@Z DD imagerel $LN6
	DD	imagerel $LN6+122
	DD	imagerel $unwind$?circular_buf_size@@YA_KPEAU_circ_buf_@@@Z
$pdata$?circular_buf_put@@YAXPEAU_circ_buf_@@H@Z DD imagerel $LN3
	DD	imagerel $LN3+53
	DD	imagerel $unwind$?circular_buf_put@@YAXPEAU_circ_buf_@@H@Z
$pdata$?circular_buf_put2@@YAHPEAU_circ_buf_@@H@Z DD imagerel $LN4
	DD	imagerel $LN4+90
	DD	imagerel $unwind$?circular_buf_put2@@YAHPEAU_circ_buf_@@H@Z
$pdata$?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z DD imagerel $LN4
	DD	imagerel $LN4+94
	DD	imagerel $unwind$?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z
$pdata$?circular_buf_empty@@YA_NPEAU_circ_buf_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+67
	DD	imagerel $unwind$?circular_buf_empty@@YA_NPEAU_circ_buf_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?advance_pointer@@YAXPEAU_circ_buf_@@@Z DD 010901H
	DD	02209H
$unwind$?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z DD 010e01H
	DD	0620eH
$unwind$?circ_buf_free@@YAXPEAU_circ_buf_@@@Z DD 010901H
	DD	04209H
$unwind$?circular_buf_size@@YA_KPEAU_circ_buf_@@@Z DD 010901H
	DD	02209H
$unwind$?circular_buf_put@@YAXPEAU_circ_buf_@@H@Z DD 010d01H
	DD	0420dH
$unwind$?circular_buf_put2@@YAHPEAU_circ_buf_@@H@Z DD 010d01H
	DD	0620dH
$unwind$?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z DD 010e01H
	DD	0620eH
$unwind$?circular_buf_empty@@YA_NPEAU_circ_buf_@@@Z DD 010901H
	DD	02209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
cbuf$ = 8
?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z PROC		; circular_buf_full

; 114  : {

	mov	QWORD PTR [rsp+8], rcx

; 115  : 	return cbuf->full;

	mov	rax, QWORD PTR cbuf$[rsp]
	movzx	eax, BYTE PTR [rax+32]

; 116  : }

	ret	0
?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z ENDP		; circular_buf_full
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
tv70 = 0
cbuf$ = 32
?circular_buf_empty@@YA_NPEAU_circ_buf_@@@Z PROC	; circular_buf_empty

; 109  : {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 110  : 	return (!cbuf->full && (cbuf->head == cbuf->tail));

	mov	rax, QWORD PTR cbuf$[rsp]
	movzx	eax, BYTE PTR [rax+32]
	test	eax, eax
	jne	SHORT $LN3@circular_b
	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR [rcx+16]
	cmp	QWORD PTR [rax+8], rcx
	jne	SHORT $LN3@circular_b
	mov	DWORD PTR tv70[rsp], 1
	jmp	SHORT $LN4@circular_b
$LN3@circular_b:
	mov	DWORD PTR tv70[rsp], 0
$LN4@circular_b:
	movzx	eax, BYTE PTR tv70[rsp]

; 111  : }

	add	rsp, 24
	ret	0
?circular_buf_empty@@YA_NPEAU_circ_buf_@@@Z ENDP	; circular_buf_empty
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
r$ = 32
cbuf$ = 64
data$ = 72
?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z PROC	; circular_buf_get

; 94   : {

$LN4:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 95   : 	int r = -1;

	mov	DWORD PTR r$[rsp], -1

; 96   : 
; 97   : 	if (!circular_buf_empty(cbuf))

	mov	rcx, QWORD PTR cbuf$[rsp]
	call	?circular_buf_empty@@YA_NPEAU_circ_buf_@@@Z ; circular_buf_empty
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN1@circular_b

; 98   : 	{
; 99   : 		*data = cbuf->buffer[cbuf->tail];

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR [rcx]
	mov	rdx, QWORD PTR data$[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	mov	BYTE PTR [rdx], al

; 100  : 		retreat_pointer(cbuf);

	mov	rcx, QWORD PTR cbuf$[rsp]
	call	?retreat_pointer@@YAXPEAU_circ_buf_@@@Z	; retreat_pointer

; 101  : 
; 102  : 		r = 0;

	mov	DWORD PTR r$[rsp], 0
$LN1@circular_b:

; 103  : 	}
; 104  : 
; 105  : 	return r;

	mov	eax, DWORD PTR r$[rsp]

; 106  : }

	add	rsp, 56					; 00000038H
	ret	0
?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z ENDP	; circular_buf_get
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
r$ = 32
cbuf$ = 64
data$ = 72
?circular_buf_put2@@YAHPEAU_circ_buf_@@H@Z PROC		; circular_buf_put2

; 80   : {

$LN4:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 81   : 	int r = -1;

	mov	DWORD PTR r$[rsp], -1

; 82   : 
; 83   : 	if (!circular_buf_full(cbuf))

	mov	rcx, QWORD PTR cbuf$[rsp]
	call	?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z ; circular_buf_full
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN1@circular_b

; 84   : 	{
; 85   : 		cbuf->buffer[cbuf->head] = data;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR [rcx]
	movzx	edx, BYTE PTR data$[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 86   : 		advance_pointer(cbuf);

	mov	rcx, QWORD PTR cbuf$[rsp]
	call	?advance_pointer@@YAXPEAU_circ_buf_@@@Z	; advance_pointer

; 87   : 		r = 0;

	mov	DWORD PTR r$[rsp], 0
$LN1@circular_b:

; 88   : 	}
; 89   : 
; 90   : 	return r;

	mov	eax, DWORD PTR r$[rsp]

; 91   : }

	add	rsp, 56					; 00000038H
	ret	0
?circular_buf_put2@@YAHPEAU_circ_buf_@@H@Z ENDP		; circular_buf_put2
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
cbuf$ = 48
data$ = 56
?circular_buf_put@@YAXPEAU_circ_buf_@@H@Z PROC		; circular_buf_put

; 73   : {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 74   : 	cbuf->buffer[cbuf->head] = data;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR [rcx]
	movzx	edx, BYTE PTR data$[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 75   : 
; 76   : 	advance_pointer(cbuf);

	mov	rcx, QWORD PTR cbuf$[rsp]
	call	?advance_pointer@@YAXPEAU_circ_buf_@@@Z	; advance_pointer

; 77   : }

	add	rsp, 40					; 00000028H
	ret	0
?circular_buf_put@@YAXPEAU_circ_buf_@@H@Z ENDP		; circular_buf_put
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
cbuf$ = 8
?circular_buf_capacity@@YA_KPEAU_circ_buf_@@@Z PROC	; circular_buf_capacity

; 68   : {

	mov	QWORD PTR [rsp+8], rcx

; 69   : 	return cbuf->max;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rax, QWORD PTR [rax+24]

; 70   : }

	ret	0
?circular_buf_capacity@@YA_KPEAU_circ_buf_@@@Z ENDP	; circular_buf_capacity
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
size$ = 0
cbuf$ = 32
?circular_buf_size@@YA_KPEAU_circ_buf_@@@Z PROC		; circular_buf_size

; 49   : {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 50   : 	size_t size = cbuf->max;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR size$[rsp], rax

; 51   : 
; 52   : 	if (!cbuf->full)

	mov	rax, QWORD PTR cbuf$[rsp]
	movzx	eax, BYTE PTR [rax+32]
	test	eax, eax
	jne	SHORT $LN3@circular_b

; 53   : 	{
; 54   : 		if (cbuf->head >= cbuf->tail)

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR [rcx+16]
	cmp	QWORD PTR [rax+8], rcx
	jb	SHORT $LN2@circular_b

; 55   : 		{
; 56   : 			size = (cbuf->head - cbuf->tail);

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR [rcx+16]
	mov	rax, QWORD PTR [rax+8]
	sub	rax, rcx
	mov	QWORD PTR size$[rsp], rax

; 57   : 		}
; 58   : 		else

	jmp	SHORT $LN1@circular_b
$LN2@circular_b:

; 59   : 		{
; 60   : 			size = (cbuf->max + cbuf->head - cbuf->tail);

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR cbuf$[rsp]
	add	rax, QWORD PTR [rcx+8]
	mov	rcx, QWORD PTR cbuf$[rsp]
	sub	rax, QWORD PTR [rcx+16]
	mov	QWORD PTR size$[rsp], rax
$LN1@circular_b:
$LN3@circular_b:

; 61   : 		}
; 62   : 	}
; 63   : 
; 64   : 	return size;

	mov	rax, QWORD PTR size$[rsp]

; 65   : }

	add	rsp, 24
	ret	0
?circular_buf_size@@YA_KPEAU_circ_buf_@@@Z ENDP		; circular_buf_size
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
cbuf$ = 48
?circ_buf_free@@YAXPEAU_circ_buf_@@@Z PROC		; circ_buf_free

; 44   : void circ_buf_free (circ_buf_t *cbuf) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 45   : 	free(cbuf);

	mov	rcx, QWORD PTR cbuf$[rsp]
	call	?free@@YAXPEAX@Z			; free

; 46   : }

	add	rsp, 40					; 00000028H
	ret	0
?circ_buf_free@@YAXPEAU_circ_buf_@@@Z ENDP		; circ_buf_free
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
cbuf$ = 32
buffer$ = 64
size$ = 72
?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z PROC		; circ_buf_init

; 35   : circ_buf_t *circ_buf_init (uint8_t* buffer, size_t size) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 36   : 	circ_buf_t *cbuf = (circ_buf_t*)malloc(sizeof(circ_buf_t));

	mov	ecx, 40					; 00000028H
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	QWORD PTR cbuf$[rsp], rax

; 37   : 	cbuf->buffer = buffer;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR buffer$[rsp]
	mov	QWORD PTR [rax], rcx

; 38   : 	cbuf->max = size;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR size$[rsp]
	mov	QWORD PTR [rax+24], rcx

; 39   : 	circ_buf_reset (cbuf);

	mov	rcx, QWORD PTR cbuf$[rsp]
	call	?circ_buf_reset@@YAXPEAU_circ_buf_@@@Z	; circ_buf_reset

; 40   : 
; 41   : 	return cbuf;

	mov	rax, QWORD PTR cbuf$[rsp]

; 42   : }

	add	rsp, 56					; 00000038H
	ret	0
?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z ENDP		; circ_buf_init
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
cbuf$ = 8
?circ_buf_reset@@YAXPEAU_circ_buf_@@@Z PROC		; circ_buf_reset

; 29   : void circ_buf_reset (circ_buf_t *cbuf) {

	mov	QWORD PTR [rsp+8], rcx

; 30   : 	cbuf->head = 0;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	QWORD PTR [rax+8], 0

; 31   : 	cbuf->tail = 0;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	QWORD PTR [rax+16], 0

; 32   : 	cbuf->full = false;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	BYTE PTR [rax+32], 0

; 33   : }

	ret	0
?circ_buf_reset@@YAXPEAU_circ_buf_@@@Z ENDP		; circ_buf_reset
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
cbuf$ = 8
?retreat_pointer@@YAXPEAU_circ_buf_@@@Z PROC		; retreat_pointer

; 24   : void retreat_pointer (circ_buf_t *cbuf) {

	mov	QWORD PTR [rsp+8], rcx

; 25   : 	cbuf->full = false;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	BYTE PTR [rax+32], 0

; 26   : 	cbuf->tail = (cbuf->tail + 1) % cbuf->max;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rax, QWORD PTR [rax+16]
	inc	rax
	xor	edx, edx
	mov	rcx, QWORD PTR cbuf$[rsp]
	div	QWORD PTR [rcx+24]
	mov	rax, rdx
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	QWORD PTR [rcx+16], rax

; 27   : }

	ret	0
?retreat_pointer@@YAXPEAU_circ_buf_@@@Z ENDP		; retreat_pointer
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\circ_buf.cpp
_TEXT	SEGMENT
tv81 = 0
cbuf$ = 32
?advance_pointer@@YAXPEAU_circ_buf_@@@Z PROC		; advance_pointer

; 14   : void advance_pointer (circ_buf_t *cbuf) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 15   : 	if (cbuf->full)

	mov	rax, QWORD PTR cbuf$[rsp]
	movzx	eax, BYTE PTR [rax+32]
	test	eax, eax
	je	SHORT $LN1@advance_po

; 16   : 		cbuf->tail = (cbuf->tail + 1) % cbuf->max;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rax, QWORD PTR [rax+16]
	inc	rax
	xor	edx, edx
	mov	rcx, QWORD PTR cbuf$[rsp]
	div	QWORD PTR [rcx+24]
	mov	rax, rdx
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	QWORD PTR [rcx+16], rax
$LN1@advance_po:

; 17   : 
; 18   : 	cbuf->head = (cbuf->head + 1) % cbuf->max;

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rax, QWORD PTR [rax+8]
	inc	rax
	xor	edx, edx
	mov	rcx, QWORD PTR cbuf$[rsp]
	div	QWORD PTR [rcx+24]
	mov	rax, rdx
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 19   : 
; 20   : 	cbuf->full = (cbuf->head == cbuf->tail);

	mov	rax, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR cbuf$[rsp]
	mov	rcx, QWORD PTR [rcx+16]
	cmp	QWORD PTR [rax+8], rcx
	jne	SHORT $LN4@advance_po
	mov	DWORD PTR tv81[rsp], 1
	jmp	SHORT $LN5@advance_po
$LN4@advance_po:
	mov	DWORD PTR tv81[rsp], 0
$LN5@advance_po:
	mov	rax, QWORD PTR cbuf$[rsp]
	movzx	ecx, BYTE PTR tv81[rsp]
	mov	BYTE PTR [rax+32], cl

; 21   : }

	add	rsp, 24
	ret	0
?advance_pointer@@YAXPEAU_circ_buf_@@@Z ENDP		; advance_pointer
_TEXT	ENDS
END
