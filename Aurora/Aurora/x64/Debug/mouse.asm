; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?mouse_x@@3HA					; mouse_x
PUBLIC	?mouse_y@@3HA					; mouse_y
PUBLIC	?mouse_x_difference@@3HA			; mouse_x_difference
PUBLIC	?mouse_y_difference@@3HA			; mouse_y_difference
PUBLIC	?prev_button@@3PAEA				; prev_button
PUBLIC	?curr_button@@3PAEA				; curr_button
PUBLIC	?mouse_button_state@@3IA			; mouse_button_state
PUBLIC	?mouse_button@@3HC				; mouse_button
PUBLIC	?old_message@@3U_dwm_message_@@A		; old_message
_BSS	SEGMENT
mouse_cycle DB	01H DUP (?)
	ALIGN	4

?mouse_x@@3HA DD 01H DUP (?)				; mouse_x
?mouse_y@@3HA DD 01H DUP (?)				; mouse_y
?mouse_x_difference@@3HA DD 01H DUP (?)			; mouse_x_difference
?mouse_y_difference@@3HA DD 01H DUP (?)			; mouse_y_difference
?prev_button@@3PAEA DB 03H DUP (?)			; prev_button
	ALIGN	4

?curr_button@@3PAEA DB 03H DUP (?)			; curr_button
	ALIGN	4

?mouse_button_state@@3IA DD 01H DUP (?)			; mouse_button_state
?mouse_button@@3HC DD 01H DUP (?)			; mouse_button
?old_message@@3U_dwm_message_@@A DB 01cH DUP (?)	; old_message
_BSS	ENDS
PUBLIC	?AuInitializeMouse@@YAXXZ			; AuInitializeMouse
PUBLIC	?mouse_wait@@YAXE@Z				; mouse_wait
PUBLIC	?mouse_write@@YAXE@Z				; mouse_write
PUBLIC	?mouse_read@@YAEXZ				; mouse_read
PUBLIC	?left_button_up@@YAHXZ				; left_button_up
PUBLIC	?mouse_handler@@YAX_KPEAX@Z			; mouse_handler
PUBLIC	?mouse_register_device@@YAXXZ			; mouse_register_device
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	x64_inportb:PROC
EXTRN	inportb:PROC
EXTRN	outportb:PROC
EXTRN	AuInterruptEnd:PROC
EXTRN	AuInterruptSet:PROC
EXTRN	memset:PROC
EXTRN	memcpy:PROC
EXTRN	AuGetScreenWidth:PROC
EXTRN	AuGetScreenHeight:PROC
EXTRN	?PointDevPutMessage@@YAXPEAU_dwm_message_@@@Z:PROC ; PointDevPutMessage
_BSS	SEGMENT
mouse_byte DB	04H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?AuInitializeMouse@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+184
	DD	imagerel $unwind$?AuInitializeMouse@@YAXXZ
$pdata$?mouse_wait@@YAXE@Z DD imagerel $LN11
	DD	imagerel $LN11+131
	DD	imagerel $unwind$?mouse_wait@@YAXE@Z
$pdata$?mouse_write@@YAXE@Z DD imagerel $LN3
	DD	imagerel $LN3+52
	DD	imagerel $unwind$?mouse_write@@YAXE@Z
$pdata$?mouse_read@@YAEXZ DD imagerel $LN3
	DD	imagerel $LN3+25
	DD	imagerel $unwind$?mouse_read@@YAEXZ
$pdata$?left_button_up@@YAHXZ DD imagerel $LN5
	DD	imagerel $LN5+76
	DD	imagerel $unwind$?left_button_up@@YAHXZ
$pdata$?mouse_handler@@YAX_KPEAX@Z DD imagerel $LN28
	DD	imagerel $LN28+1032
	DD	imagerel $unwind$?mouse_handler@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuInitializeMouse@@YAXXZ DD 010401H
	DD	06204H
$unwind$?mouse_wait@@YAXE@Z DD 010801H
	DD	06208H
$unwind$?mouse_write@@YAXE@Z DD 010801H
	DD	04208H
$unwind$?mouse_read@@YAEXZ DD 010401H
	DD	04204H
$unwind$?left_button_up@@YAHXZ DD 010401H
	DD	02204H
$unwind$?mouse_handler@@YAX_KPEAX@Z DD 010e01H
	DD	0c20eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
?mouse_register_device@@YAXXZ PROC			; mouse_register_device

; 196  : }

	ret	0
?mouse_register_device@@YAXXZ ENDP			; mouse_register_device
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
mouse_in$1 = 32
status$ = 33
tv75 = 36
x$2 = 40
y$3 = 44
tv154 = 48
tv159 = 52
msg$4 = 56
p$ = 112
param$ = 120
?mouse_handler@@YAX_KPEAX@Z PROC			; mouse_handler

; 88   : void mouse_handler (size_t p, void* param) {

$LN28:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 89   : 	uint8_t status = inportb (MOUSE_STATUS);

	mov	cx, 100					; 00000064H
	call	inportb
	mov	BYTE PTR status$[rsp], al
$LN25@mouse_hand:

; 90   : 	while ((status & MOUSE_BBIT) && (status & MOUSE_F_BIT)) {

	movzx	eax, BYTE PTR status$[rsp]
	and	eax, 1
	test	eax, eax
	je	$LN24@mouse_hand
	movzx	eax, BYTE PTR status$[rsp]
	and	eax, 32					; 00000020H
	test	eax, eax
	je	$LN24@mouse_hand

; 91   : 		int8_t mouse_in = inportb (MOUSE_PORT);

	mov	cx, 96					; 00000060H
	call	inportb
	mov	BYTE PTR mouse_in$1[rsp], al

; 92   : 		switch (mouse_cycle) {

	movzx	eax, BYTE PTR mouse_cycle
	mov	BYTE PTR tv75[rsp], al
	cmp	BYTE PTR tv75[rsp], 0
	je	SHORT $LN21@mouse_hand
	cmp	BYTE PTR tv75[rsp], 1
	je	SHORT $LN19@mouse_hand
	cmp	BYTE PTR tv75[rsp], 2
	je	SHORT $LN18@mouse_hand
	cmp	BYTE PTR tv75[rsp], 3
	je	$LN16@mouse_hand
	cmp	BYTE PTR tv75[rsp], 4
	je	$LN14@mouse_hand
	jmp	$LN22@mouse_hand
$LN21@mouse_hand:

; 93   : 		case 0:
; 94   : 			mouse_byte[0] = mouse_in;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 95   : 			if (!(mouse_in & MOUSE_V_BIT)) break;

	movsx	eax, BYTE PTR mouse_in$1[rsp]
	and	eax, 8
	test	eax, eax
	jne	SHORT $LN20@mouse_hand
	jmp	$LN22@mouse_hand
$LN20@mouse_hand:

; 96   : 			++mouse_cycle;

	movzx	eax, BYTE PTR mouse_cycle
	inc	al
	mov	BYTE PTR mouse_cycle, al

; 97   : 			break;

	jmp	SHORT $LN22@mouse_hand
$LN19@mouse_hand:

; 98   : 		case 1:
; 99   : 			mouse_byte[1] = mouse_in;

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 100  : 			++mouse_cycle;

	movzx	eax, BYTE PTR mouse_cycle
	inc	al
	mov	BYTE PTR mouse_cycle, al

; 101  : 			break;

	jmp	SHORT $LN22@mouse_hand
$LN18@mouse_hand:

; 102  : 		case 2:
; 103  : 			mouse_byte[2] = mouse_in;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 104  : 			goto finish_packet;

	jmp	SHORT $LN17@mouse_hand
	jmp	SHORT $finish_packet$29
$LN16@mouse_hand:

; 105  : 		case 3:
; 106  : 			mouse_byte[3] = mouse_in;

	mov	eax, 1
	imul	rax, 3
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 107  : 			goto finish_packet;

	jmp	SHORT $LN15@mouse_hand
	jmp	SHORT $finish_packet$29
$LN14@mouse_hand:

; 108  : 		case 4:
; 109  : 			mouse_byte[4] = mouse_in;

	mov	eax, 1
	imul	rax, 4
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 110  : 			goto finish_packet;

	jmp	SHORT $LN13@mouse_hand
	jmp	SHORT $finish_packet$29
$LN22@mouse_hand:

; 111  : 		}
; 112  : 
; 113  : 		goto read_next;

	jmp	$LN12@mouse_hand
	jmp	$read_next$30
$LN13@mouse_hand:
$LN15@mouse_hand:
$LN17@mouse_hand:
$finish_packet$29:

; 114  : 
; 115  : finish_packet:
; 116  : 		mouse_cycle = 0;

	mov	BYTE PTR mouse_cycle, 0

; 117  : 
; 118  : 		int x = mouse_byte[1];

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR x$2[rsp], eax

; 119  : 		int y = mouse_byte[2];

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR y$3[rsp], eax

; 120  : 		if (x && mouse_byte[0] & ( 1 <<  4)) {

	cmp	DWORD PTR x$2[rsp], 0
	je	SHORT $LN11@mouse_hand
	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 16
	test	eax, eax
	je	SHORT $LN11@mouse_hand

; 121  : 			x = x - 0x100;

	mov	eax, DWORD PTR x$2[rsp]
	sub	eax, 256				; 00000100H
	mov	DWORD PTR x$2[rsp], eax
$LN11@mouse_hand:

; 122  : 		}
; 123  : 
; 124  : 		if (y && mouse_byte[0] & (1 << 5)) {

	cmp	DWORD PTR y$3[rsp], 0
	je	SHORT $LN10@mouse_hand
	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 32					; 00000020H
	test	eax, eax
	je	SHORT $LN10@mouse_hand

; 125  : 			y = y - 0x100;

	mov	eax, DWORD PTR y$3[rsp]
	sub	eax, 256				; 00000100H
	mov	DWORD PTR y$3[rsp], eax
$LN10@mouse_hand:

; 126  : 		}
; 127  : 
; 128  : 		mouse_x_difference = x;

	mov	eax, DWORD PTR x$2[rsp]
	mov	DWORD PTR ?mouse_x_difference@@3HA, eax	; mouse_x_difference

; 129  : 		mouse_y_difference = y;

	mov	eax, DWORD PTR y$3[rsp]
	mov	DWORD PTR ?mouse_y_difference@@3HA, eax	; mouse_y_difference

; 130  : 		mouse_x += mouse_x_difference;

	mov	eax, DWORD PTR ?mouse_x_difference@@3HA	; mouse_x_difference
	mov	ecx, DWORD PTR ?mouse_x@@3HA		; mouse_x
	add	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x

; 131  : 		mouse_y -= mouse_y_difference;

	mov	eax, DWORD PTR ?mouse_y_difference@@3HA	; mouse_y_difference
	mov	ecx, DWORD PTR ?mouse_y@@3HA		; mouse_y
	sub	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y

; 132  : 
; 133  : 		if (mouse_x < 0)

	cmp	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x
	jge	SHORT $LN9@mouse_hand

; 134  : 			mouse_x = 0;

	mov	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x
$LN9@mouse_hand:

; 135  : 
; 136  : 		if (mouse_y < 0)

	cmp	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y
	jge	SHORT $LN8@mouse_hand

; 137  : 			mouse_y = 0;

	mov	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y
$LN8@mouse_hand:

; 138  : 
; 139  : 		if (mouse_x + 24 > AuGetScreenWidth())

	mov	eax, DWORD PTR ?mouse_x@@3HA		; mouse_x
	add	eax, 24
	mov	DWORD PTR tv154[rsp], eax
	call	AuGetScreenWidth
	mov	ecx, DWORD PTR tv154[rsp]
	cmp	ecx, eax
	jbe	SHORT $LN7@mouse_hand

; 140  : 			mouse_x = AuGetScreenWidth() - 24;

	call	AuGetScreenWidth
	sub	eax, 24
	mov	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x
$LN7@mouse_hand:

; 141  : 
; 142  : 		if (mouse_y + 24 > AuGetScreenHeight())

	mov	eax, DWORD PTR ?mouse_y@@3HA		; mouse_y
	add	eax, 24
	mov	DWORD PTR tv159[rsp], eax
	call	AuGetScreenHeight
	mov	ecx, DWORD PTR tv159[rsp]
	cmp	ecx, eax
	jbe	SHORT $LN6@mouse_hand

; 143  : 			mouse_y = AuGetScreenHeight() - 24;

	call	AuGetScreenHeight
	sub	eax, 24
	mov	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y
$LN6@mouse_hand:

; 144  : 
; 145  : 		mouse_button_state = 0;

	mov	DWORD PTR ?mouse_button_state@@3IA, 0	; mouse_button_state

; 146  : 
; 147  : 		if (mouse_byte[0] & 0x01) {    //0x01 for PS/2

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN5@mouse_hand

; 148  : 			curr_button[0] = 1;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 1

; 149  : 			mouse_button_state = 1;

	mov	DWORD PTR ?mouse_button_state@@3IA, 1	; mouse_button_state

; 150  : 		}else

	jmp	SHORT $LN4@mouse_hand
$LN5@mouse_hand:

; 151  : 			curr_button[0] = 0;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 0
$LN4@mouse_hand:

; 152  : 
; 153  : 		if (mouse_byte[0] & 0x02) {

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN3@mouse_hand

; 154  : 			curr_button[2] = 1;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 1

; 155  : 		}else 

	jmp	SHORT $LN2@mouse_hand
$LN3@mouse_hand:

; 156  : 			curr_button[2] = 0;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 0
$LN2@mouse_hand:

; 157  : 
; 158  : 		if (mouse_byte[0] & 0x04)

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 4
	test	eax, eax
	je	SHORT $LN1@mouse_hand

; 159  : 			mouse_button |= MOUSE_MIDDLE_CLICK;

	mov	eax, DWORD PTR ?mouse_button@@3HC	; mouse_button
	or	eax, 4
	mov	DWORD PTR ?mouse_button@@3HC, eax	; mouse_button
$LN1@mouse_hand:

; 160  : 
; 161  : 		//!Pass here the message stream to all waiting processes
; 162  : 	
; 163  : 		x64_cli();

	call	x64_cli

; 164  : 		dwm_message_t msg; // = (dwm_message_t*)pmmngr_alloc();
; 165  : 		msg.type = 1;

	mov	eax, 1
	mov	WORD PTR msg$4[rsp], ax

; 166  : 		msg.dword = mouse_x;

	mov	eax, DWORD PTR ?mouse_x@@3HA		; mouse_x
	mov	DWORD PTR msg$4[rsp+4], eax

; 167  : 		msg.dword2 = mouse_y;

	mov	eax, DWORD PTR ?mouse_y@@3HA		; mouse_y
	mov	DWORD PTR msg$4[rsp+8], eax

; 168  : 		msg.dword4 = mouse_button_state;

	mov	eax, DWORD PTR ?mouse_button_state@@3IA	; mouse_button_state
	mov	DWORD PTR msg$4[rsp+16], eax

; 169  : 		msg.dword5 = mouse_byte[1];

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR msg$4[rsp+20], eax

; 170  : 		msg.dword6 = -mouse_byte[2];

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	neg	eax
	mov	DWORD PTR msg$4[rsp+24], eax

; 171  : 		//dwm_put_message (&msg);
; 172  : 		PointDevPutMessage(&msg);

	lea	rcx, QWORD PTR msg$4[rsp]
	call	?PointDevPutMessage@@YAXPEAU_dwm_message_@@@Z ; PointDevPutMessage

; 173  : 		x64_sti();

	call	x64_sti

; 174  : 		//pmmngr_free (msg);
; 175  : 		//mutex_unlock (mouse);
; 176  :     /*	if (left_button_up()) {
; 177  : 			mouse_button_state |= 5;
; 178  : 		}*/
; 179  : 
; 180  : 		memcpy (prev_button, curr_button, 3);

	mov	r8d, 3
	lea	rdx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	lea	rcx, OFFSET FLAT:?prev_button@@3PAEA	; prev_button
	call	memcpy

; 181  : 		memset (curr_button, 0x00, 3);

	mov	r8d, 3
	xor	edx, edx
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	call	memset
$LN12@mouse_hand:
$read_next$30:

; 182  : read_next:
; 183  : 		break;

	jmp	SHORT $LN24@mouse_hand

; 184  : 	}

	jmp	$LN25@mouse_hand
$LN24@mouse_hand:

; 185  : 
; 186  : 	AuInterruptEnd(12);

	mov	ecx, 12
	call	AuInterruptEnd

; 187  : }

	add	rsp, 104				; 00000068H
	ret	0
?mouse_handler@@YAX_KPEAX@Z ENDP			; mouse_handler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
tv72 = 0
?left_button_up@@YAHXZ PROC				; left_button_up

; 76   : int left_button_up() {

$LN5:
	sub	rsp, 24

; 77   : 	return prev_button[0] && !curr_button[0];

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?prev_button@@3PAEA	; prev_button
	movzx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	je	SHORT $LN3@left_butto
	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	movzx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	jne	SHORT $LN3@left_butto
	mov	DWORD PTR tv72[rsp], 1
	jmp	SHORT $LN4@left_butto
$LN3@left_butto:
	mov	DWORD PTR tv72[rsp], 0
$LN4@left_butto:
	mov	eax, DWORD PTR tv72[rsp]

; 78   : }

	add	rsp, 24
	ret	0
?left_button_up@@YAHXZ ENDP				; left_button_up
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
?mouse_read@@YAEXZ PROC					; mouse_read

; 70   : uint8_t mouse_read () {

$LN3:
	sub	rsp, 40					; 00000028H

; 71   : 	mouse_wait (0);

	xor	ecx, ecx
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 72   : 	return inportb (0x60);

	mov	cx, 96					; 00000060H
	call	inportb

; 73   : }

	add	rsp, 40					; 00000028H
	ret	0
?mouse_read@@YAEXZ ENDP					; mouse_read
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
write$ = 48
?mouse_write@@YAXE@Z PROC				; mouse_write

; 60   : void mouse_write (uint8_t write) {

$LN3:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H

; 61   : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 62   : 	outportb (0x64, 0xD4);

	mov	dl, 212					; 000000d4H
	mov	cx, 100					; 00000064H
	call	outportb

; 63   : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 64   : 	outportb (0x60, write);

	movzx	edx, BYTE PTR write$[rsp]
	mov	cx, 96					; 00000060H
	call	outportb

; 65   : }

	add	rsp, 40					; 00000028H
	ret	0
?mouse_write@@YAXE@Z ENDP				; mouse_write
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
_timer_out_$ = 32
tv68 = 36
tv76 = 40
a_type$ = 64
?mouse_wait@@YAXE@Z PROC				; mouse_wait

; 38   : void  mouse_wait (uint8_t a_type){

$LN11:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 39   : 	uint32_t _timer_out_ = 100000;

	mov	DWORD PTR _timer_out_$[rsp], 100000	; 000186a0H

; 40   : 	if (a_type == 0) {

	movzx	eax, BYTE PTR a_type$[rsp]
	test	eax, eax
	jne	SHORT $LN8@mouse_wait
$LN7@mouse_wait:

; 41   : 		while (_timer_out_--){

	mov	eax, DWORD PTR _timer_out_$[rsp]
	mov	DWORD PTR tv68[rsp], eax
	mov	eax, DWORD PTR _timer_out_$[rsp]
	dec	eax
	mov	DWORD PTR _timer_out_$[rsp], eax
	cmp	DWORD PTR tv68[rsp], 0
	je	SHORT $LN6@mouse_wait

; 42   : 			if ((x64_inportb(0x64) & 1) == 1){

	mov	cx, 100					; 00000064H
	call	x64_inportb
	movzx	eax, al
	and	eax, 1
	cmp	eax, 1
	jne	SHORT $LN5@mouse_wait

; 43   : 				return;

	jmp	SHORT $LN9@mouse_wait
$LN5@mouse_wait:

; 44   : 			}
; 45   : 		}

	jmp	SHORT $LN7@mouse_wait
$LN6@mouse_wait:

; 46   : 		return;

	jmp	SHORT $LN9@mouse_wait

; 47   : 	}else {

	jmp	SHORT $LN4@mouse_wait
$LN8@mouse_wait:
$LN3@mouse_wait:

; 48   : 		while (_timer_out_--){

	mov	eax, DWORD PTR _timer_out_$[rsp]
	mov	DWORD PTR tv76[rsp], eax
	mov	eax, DWORD PTR _timer_out_$[rsp]
	dec	eax
	mov	DWORD PTR _timer_out_$[rsp], eax
	cmp	DWORD PTR tv76[rsp], 0
	je	SHORT $LN2@mouse_wait

; 49   : 			if ((x64_inportb(0x64) & 2) == 0){

	mov	cx, 100					; 00000064H
	call	x64_inportb
	movzx	eax, al
	and	eax, 2
	test	eax, eax
	jne	SHORT $LN1@mouse_wait

; 50   : 				return;

	jmp	SHORT $LN9@mouse_wait
$LN1@mouse_wait:

; 51   : 			}
; 52   : 		}

	jmp	SHORT $LN3@mouse_wait
$LN2@mouse_wait:
$LN4@mouse_wait:
$LN9@mouse_wait:

; 53   : 		return;
; 54   : 	}
; 55   : }

	add	rsp, 56					; 00000038H
	ret	0
?mouse_wait@@YAXE@Z ENDP				; mouse_wait
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
status$ = 32
?AuInitializeMouse@@YAXXZ PROC				; AuInitializeMouse

; 202  : void AuInitializeMouse () {

$LN3:
	sub	rsp, 56					; 00000038H

; 203  : 	mouse_cycle = 0;

	mov	BYTE PTR mouse_cycle, 0

; 204  : 	mouse_x = 0;

	mov	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x

; 205  : 	mouse_y = 0;

	mov	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y

; 206  : 
; 207  : 	uint8_t status;
; 208  : 
; 209  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 210  :     outportb (0x64, 0xA8);

	mov	dl, 168					; 000000a8H
	mov	cx, 100					; 00000064H
	call	outportb

; 211  : 
; 212  : 	mouse_wait(1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 213  : 	outportb (0x64, 0x20);

	mov	dl, 32					; 00000020H
	mov	cx, 100					; 00000064H
	call	outportb

; 214  : 
; 215  : 	mouse_wait (0);

	xor	ecx, ecx
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 216  : 	status = (inportb (0x60) | 2);

	mov	cx, 96					; 00000060H
	call	inportb
	movzx	eax, al
	or	eax, 2
	mov	BYTE PTR status$[rsp], al

; 217  : 
; 218  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 219  : 	outportb (0x64, 0x60);

	mov	dl, 96					; 00000060H
	mov	cx, 100					; 00000064H
	call	outportb

; 220  : 
; 221  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 222  : 	outportb (0x60, status);

	movzx	edx, BYTE PTR status$[rsp]
	mov	cx, 96					; 00000060H
	call	outportb

; 223  : 
; 224  : 	mouse_write (0xF6);

	mov	cl, 246					; 000000f6H
	call	?mouse_write@@YAXE@Z			; mouse_write

; 225  : 	mouse_read ();

	call	?mouse_read@@YAEXZ			; mouse_read

; 226  : 
; 227  : 	mouse_write (0xF4);

	mov	cl, 244					; 000000f4H
	call	?mouse_write@@YAXE@Z			; mouse_write

; 228  : 	mouse_read ();

	call	?mouse_read@@YAEXZ			; mouse_read

; 229  : 
; 230  : 	AuInterruptSet (34, mouse_handler, 12, false);  //34

	xor	r9d, r9d
	mov	r8b, 12
	lea	rdx, OFFSET FLAT:?mouse_handler@@YAX_KPEAX@Z ; mouse_handler
	mov	ecx, 34					; 00000022H
	call	AuInterruptSet

; 231  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuInitializeMouse@@YAXXZ ENDP				; AuInitializeMouse
_TEXT	ENDS
END
