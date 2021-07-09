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
_BSS	ENDS
PUBLIC	?initialize_mouse@@YAXXZ			; initialize_mouse
PUBLIC	?mouse_wait@@YAXE@Z				; mouse_wait
PUBLIC	?mouse_write@@YAXE@Z				; mouse_write
PUBLIC	?mouse_read@@YAEXZ				; mouse_read
PUBLIC	?left_button_up@@YAHXZ				; left_button_up
PUBLIC	?mouse_handler@@YAX_KPEAX@Z			; mouse_handler
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	x64_inportb:PROC
EXTRN	?inportb@@YAEG@Z:PROC				; inportb
EXTRN	?outportb@@YAXGE@Z:PROC				; outportb
EXTRN	?interrupt_end@@YAXXZ:PROC			; interrupt_end
EXTRN	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z:PROC	; interrupt_set
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	memcpy:PROC
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?pmmngr_free@@YAXPEAX@Z:PROC			; pmmngr_free
EXTRN	?unblock_thread@@YAXPEAU_thread_@@@Z:PROC	; unblock_thread
EXTRN	?set_multi_task_enable@@YAX_N@Z:PROC		; set_multi_task_enable
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
EXTRN	?get_screen_width@@YAIXZ:PROC			; get_screen_width
EXTRN	?get_screen_height@@YAIXZ:PROC			; get_screen_height
EXTRN	?dwm_put_message@@YAXPEAU_dwm_message_@@@Z:PROC	; dwm_put_message
EXTRN	?create_mutex@@YAPEAUmutex_t@@XZ:PROC		; create_mutex
EXTRN	?mutex_lock@@YAXPEAUmutex_t@@@Z:PROC		; mutex_lock
EXTRN	?mutex_unlock@@YAXPEAUmutex_t@@@Z:PROC		; mutex_unlock
_BSS	SEGMENT
mouse_byte DB	04H DUP (?)
mouse	DQ	01H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?initialize_mouse@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+181
	DD	imagerel $unwind$?initialize_mouse@@YAXXZ
pdata	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$??__Emouse@@YAXXZ DD imagerel ??__Emouse@@YAXXZ
	DD	imagerel ??__Emouse@@YAXXZ+21
	DD	imagerel $unwind$??__Emouse@@YAXXZ
pdata	ENDS
pdata	SEGMENT
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
	DD	imagerel $LN28+1094
	DD	imagerel $unwind$?mouse_handler@@YAX_KPEAX@Z
pdata	ENDS
CRT$XCU	SEGMENT
mouse$initializer$ DQ FLAT:??__Emouse@@YAXXZ
CRT$XCU	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$??__Emouse@@YAXXZ DD 010401H
	DD	04204H
xdata	ENDS
xdata	SEGMENT
$unwind$?initialize_mouse@@YAXXZ DD 010401H
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
	DD	0820eH
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
mouse_in$1 = 32
status$ = 33
tv76 = 36
x$2 = 40
y$3 = 44
msg$4 = 48
thr$5 = 56
p$ = 80
param$ = 88
?mouse_handler@@YAX_KPEAX@Z PROC			; mouse_handler

; 70   : void mouse_handler (size_t p, void* param) {

$LN28:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 71   : 	x64_cli();

	call	x64_cli

; 72   : 	set_multi_task_enable (false);

	xor	ecx, ecx
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 73   : 	uint8_t status = inportb (MOUSE_STATUS);

	mov	cx, 100					; 00000064H
	call	?inportb@@YAEG@Z			; inportb
	mov	BYTE PTR status$[rsp], al
$LN25@mouse_hand:

; 74   : 	while ((status & MOUSE_BBIT) && (status & MOUSE_F_BIT)) {

	movzx	eax, BYTE PTR status$[rsp]
	and	eax, 1
	test	eax, eax
	je	$LN24@mouse_hand
	movzx	eax, BYTE PTR status$[rsp]
	and	eax, 32					; 00000020H
	test	eax, eax
	je	$LN24@mouse_hand

; 75   : 		int8_t mouse_in = inportb (MOUSE_PORT);

	mov	cx, 96					; 00000060H
	call	?inportb@@YAEG@Z			; inportb
	mov	BYTE PTR mouse_in$1[rsp], al

; 76   : 		switch (mouse_cycle) {

	movzx	eax, BYTE PTR mouse_cycle
	mov	BYTE PTR tv76[rsp], al
	cmp	BYTE PTR tv76[rsp], 0
	je	SHORT $LN21@mouse_hand
	cmp	BYTE PTR tv76[rsp], 1
	je	SHORT $LN19@mouse_hand
	cmp	BYTE PTR tv76[rsp], 2
	je	SHORT $LN18@mouse_hand
	cmp	BYTE PTR tv76[rsp], 3
	je	$LN16@mouse_hand
	jmp	$LN22@mouse_hand
$LN21@mouse_hand:

; 77   : 		case 0:
; 78   : 			mouse_byte[0] = mouse_in;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 79   : 			if (!(mouse_in & MOUSE_V_BIT)) break;

	movsx	eax, BYTE PTR mouse_in$1[rsp]
	and	eax, 8
	test	eax, eax
	jne	SHORT $LN20@mouse_hand
	jmp	SHORT $LN22@mouse_hand
$LN20@mouse_hand:

; 80   : 			++mouse_cycle;

	movzx	eax, BYTE PTR mouse_cycle
	inc	al
	mov	BYTE PTR mouse_cycle, al

; 81   : 			break;

	jmp	SHORT $LN22@mouse_hand
$LN19@mouse_hand:

; 82   : 		case 1:
; 83   : 			mouse_byte[1] = mouse_in;

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 84   : 			++mouse_cycle;

	movzx	eax, BYTE PTR mouse_cycle
	inc	al
	mov	BYTE PTR mouse_cycle, al

; 85   : 			break;

	jmp	SHORT $LN22@mouse_hand
$LN18@mouse_hand:

; 86   : 		case 2:
; 87   : 			mouse_byte[2] = mouse_in;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 88   : 			goto finish_packet;

	jmp	SHORT $LN17@mouse_hand
	jmp	SHORT $finish_packet$29
$LN16@mouse_hand:

; 89   : 		case 3:
; 90   : 			mouse_byte[3] = mouse_in;

	mov	eax, 1
	imul	rax, 3
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 91   : 			goto finish_packet;

	jmp	SHORT $LN15@mouse_hand
	jmp	SHORT $finish_packet$29
$LN22@mouse_hand:

; 92   : 		}
; 93   : 
; 94   : 		goto read_next;

	jmp	$LN14@mouse_hand
	jmp	$read_next$30
$LN15@mouse_hand:
$LN17@mouse_hand:
$finish_packet$29:

; 95   : 
; 96   : finish_packet:
; 97   : 		mouse_cycle = 0;

	mov	BYTE PTR mouse_cycle, 0

; 98   : 
; 99   : 		int x = mouse_byte[1];

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR x$2[rsp], eax

; 100  : 		int y = mouse_byte[2];

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR y$3[rsp], eax

; 101  : 		if (x && mouse_byte[0] & ( 1 <<  4)) {

	cmp	DWORD PTR x$2[rsp], 0
	je	SHORT $LN13@mouse_hand
	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 16
	test	eax, eax
	je	SHORT $LN13@mouse_hand

; 102  : 			x = x - 0x100;

	mov	eax, DWORD PTR x$2[rsp]
	sub	eax, 256				; 00000100H
	mov	DWORD PTR x$2[rsp], eax
$LN13@mouse_hand:

; 103  : 		}
; 104  : 
; 105  : 		if (y && mouse_byte[0] & (1 << 5)) {

	cmp	DWORD PTR y$3[rsp], 0
	je	SHORT $LN12@mouse_hand
	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 32					; 00000020H
	test	eax, eax
	je	SHORT $LN12@mouse_hand

; 106  : 			y = y - 0x100;

	mov	eax, DWORD PTR y$3[rsp]
	sub	eax, 256				; 00000100H
	mov	DWORD PTR y$3[rsp], eax
$LN12@mouse_hand:

; 107  : 		}
; 108  : 
; 109  : 		mouse_x_difference = x;

	mov	eax, DWORD PTR x$2[rsp]
	mov	DWORD PTR ?mouse_x_difference@@3HA, eax	; mouse_x_difference

; 110  : 		mouse_y_difference = y;

	mov	eax, DWORD PTR y$3[rsp]
	mov	DWORD PTR ?mouse_y_difference@@3HA, eax	; mouse_y_difference

; 111  : 		mouse_x += mouse_x_difference;

	mov	eax, DWORD PTR ?mouse_x_difference@@3HA	; mouse_x_difference
	mov	ecx, DWORD PTR ?mouse_x@@3HA		; mouse_x
	add	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x

; 112  : 		mouse_y -= mouse_y_difference;

	mov	eax, DWORD PTR ?mouse_y_difference@@3HA	; mouse_y_difference
	mov	ecx, DWORD PTR ?mouse_y@@3HA		; mouse_y
	sub	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y

; 113  : 
; 114  : 		if (mouse_x < 0)

	cmp	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x
	jge	SHORT $LN11@mouse_hand

; 115  : 			mouse_x = 0;

	mov	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x
$LN11@mouse_hand:

; 116  : 
; 117  : 		if (mouse_y < 0)

	cmp	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y
	jge	SHORT $LN10@mouse_hand

; 118  : 			mouse_y = 0;

	mov	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y
$LN10@mouse_hand:

; 119  : 
; 120  : 		if (mouse_x > get_screen_width())

	call	?get_screen_width@@YAIXZ		; get_screen_width
	cmp	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x
	jbe	SHORT $LN9@mouse_hand

; 121  : 			mouse_x = get_screen_width() - 7;

	call	?get_screen_width@@YAIXZ		; get_screen_width
	sub	eax, 7
	mov	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x
$LN9@mouse_hand:

; 122  : 
; 123  : 		if (mouse_y > get_screen_height())

	call	?get_screen_height@@YAIXZ		; get_screen_height
	cmp	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y
	jbe	SHORT $LN8@mouse_hand

; 124  : 			mouse_y = get_screen_height() - 7;

	call	?get_screen_height@@YAIXZ		; get_screen_height
	sub	eax, 7
	mov	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y
$LN8@mouse_hand:

; 125  : 
; 126  : 
; 127  : 		if (mouse_byte[0] & 0x01) {

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN7@mouse_hand

; 128  : 			curr_button[0] = 1;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 1

; 129  : 			mouse_button_state = 1;

	mov	DWORD PTR ?mouse_button_state@@3IA, 1	; mouse_button_state

; 130  : 		} else

	jmp	SHORT $LN6@mouse_hand
$LN7@mouse_hand:

; 131  : 			curr_button[0] = 0;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 0
$LN6@mouse_hand:

; 132  : 
; 133  : 		if (mouse_byte[0] & 0x02) {

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN5@mouse_hand

; 134  : 			curr_button[2] = 1;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 1

; 135  : 		}else 

	jmp	SHORT $LN4@mouse_hand
$LN5@mouse_hand:

; 136  : 			curr_button[2] = 0;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 0
$LN4@mouse_hand:

; 137  : 
; 138  : 		if (mouse_byte[0] & 0x04)

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 4
	test	eax, eax
	je	SHORT $LN3@mouse_hand

; 139  : 			mouse_button |= MOUSE_MIDDLE_CLICK;

	mov	eax, DWORD PTR ?mouse_button@@3HC	; mouse_button
	or	eax, 4
	mov	DWORD PTR ?mouse_button@@3HC, eax	; mouse_button
$LN3@mouse_hand:

; 140  : 		
; 141  : 		mutex_lock (mouse);

	mov	rcx, QWORD PTR mouse
	call	?mutex_lock@@YAXPEAUmutex_t@@@Z		; mutex_lock

; 142  : 		dwm_message_t *msg = (dwm_message_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR msg$4[rsp], rax

; 143  : 		msg->type = 1;

	mov	eax, 1
	mov	rcx, QWORD PTR msg$4[rsp]
	mov	WORD PTR [rcx], ax

; 144  : 		msg->dword = mouse_x;

	mov	rax, QWORD PTR msg$4[rsp]
	mov	ecx, DWORD PTR ?mouse_x@@3HA		; mouse_x
	mov	DWORD PTR [rax+4], ecx

; 145  : 		msg->dword2 = mouse_y;

	mov	rax, QWORD PTR msg$4[rsp]
	mov	ecx, DWORD PTR ?mouse_y@@3HA		; mouse_y
	mov	DWORD PTR [rax+8], ecx

; 146  : 		msg->dword4 = mouse_button_state;

	mov	rax, QWORD PTR msg$4[rsp]
	mov	ecx, DWORD PTR ?mouse_button_state@@3IA	; mouse_button_state
	mov	DWORD PTR [rax+16], ecx

; 147  : 		msg->dword5 = mouse_byte[1];

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	rcx, QWORD PTR msg$4[rsp]
	mov	DWORD PTR [rcx+20], eax

; 148  : 		msg->dword6 = -mouse_byte[2];

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	neg	eax
	mov	rcx, QWORD PTR msg$4[rsp]
	mov	DWORD PTR [rcx+24], eax

; 149  : 		dwm_put_message (msg);

	mov	rcx, QWORD PTR msg$4[rsp]
	call	?dwm_put_message@@YAXPEAU_dwm_message_@@@Z ; dwm_put_message

; 150  : 		pmmngr_free (msg);

	mov	rcx, QWORD PTR msg$4[rsp]
	call	?pmmngr_free@@YAXPEAX@Z			; pmmngr_free

; 151  : 		mutex_unlock (mouse);

	mov	rcx, QWORD PTR mouse
	call	?mutex_unlock@@YAXPEAUmutex_t@@@Z	; mutex_unlock

; 152  : 
; 153  : 		thread_t* thr = (thread_t*)thread_iterate_block_list (1);

	mov	ecx, 1
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR thr$5[rsp], rax

; 154  : 		if (thr != NULL){

	cmp	QWORD PTR thr$5[rsp], 0
	je	SHORT $LN2@mouse_hand

; 155  : 			thr->state = THREAD_STATE_READY;

	mov	rax, QWORD PTR thr$5[rsp]
	mov	BYTE PTR [rax+224], 1

; 156  : 			unblock_thread(thr);

	mov	rcx, QWORD PTR thr$5[rsp]
	call	?unblock_thread@@YAXPEAU_thread_@@@Z	; unblock_thread
$LN2@mouse_hand:

; 157  : 		}
; 158  : 	
; 159  : 		//!Pass here the message stream to all waiting processes
; 160  : 		if (left_button_up()) {

	call	?left_button_up@@YAHXZ			; left_button_up
	test	eax, eax
	je	SHORT $LN1@mouse_hand

; 161  : 			mouse_button_state = 0;

	mov	DWORD PTR ?mouse_button_state@@3IA, 0	; mouse_button_state
$LN1@mouse_hand:

; 162  : 			
; 163  : 		}
; 164  : 
; 165  : 		memcpy (prev_button, curr_button, 3);

	mov	r8d, 3
	lea	rdx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	lea	rcx, OFFSET FLAT:?prev_button@@3PAEA	; prev_button
	call	memcpy

; 166  : 		memset (curr_button, 0x00, 3);

	mov	r8d, 3
	xor	edx, edx
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	call	?memset@@YAXPEAXEI@Z			; memset
$LN14@mouse_hand:
$read_next$30:

; 167  : read_next:
; 168  : 		break;

	jmp	SHORT $LN24@mouse_hand

; 169  : 	}

	jmp	$LN25@mouse_hand
$LN24@mouse_hand:

; 170  : 
; 171  : 	set_multi_task_enable(true);

	mov	cl, 1
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 172  : 	interrupt_end();

	call	?interrupt_end@@YAXXZ			; interrupt_end

; 173  : 	x64_sti();

	call	x64_sti

; 174  : }

	add	rsp, 72					; 00000048H
	ret	0
?mouse_handler@@YAX_KPEAX@Z ENDP			; mouse_handler
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
tv72 = 0
?left_button_up@@YAHXZ PROC				; left_button_up

; 66   : int left_button_up() {

$LN5:
	sub	rsp, 24

; 67   : 	return prev_button[0] && !curr_button[0];

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

; 68   : }

	add	rsp, 24
	ret	0
?left_button_up@@YAHXZ ENDP				; left_button_up
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
?mouse_read@@YAEXZ PROC					; mouse_read

; 60   : uint8_t mouse_read () {

$LN3:
	sub	rsp, 40					; 00000028H

; 61   : 	mouse_wait (0);

	xor	ecx, ecx
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 62   : 	return inportb (0x60);

	mov	cx, 96					; 00000060H
	call	?inportb@@YAEG@Z			; inportb

; 63   : }

	add	rsp, 40					; 00000028H
	ret	0
?mouse_read@@YAEXZ ENDP					; mouse_read
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
write$ = 48
?mouse_write@@YAXE@Z PROC				; mouse_write

; 53   : void mouse_write (uint8_t write) {

$LN3:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H

; 54   : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 55   : 	outportb (0x64, 0xD4);

	mov	dl, 212					; 000000d4H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 56   : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 57   : 	outportb (0x60, write);

	movzx	edx, BYTE PTR write$[rsp]
	mov	cx, 96					; 00000060H
	call	?outportb@@YAXGE@Z			; outportb

; 58   : }

	add	rsp, 40					; 00000028H
	ret	0
?mouse_write@@YAXE@Z ENDP				; mouse_write
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
_timer_out_$ = 32
tv68 = 36
tv76 = 40
a_type$ = 64
?mouse_wait@@YAXE@Z PROC				; mouse_wait

; 34   : void  mouse_wait (uint8_t a_type){

$LN11:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 35   : 	uint32_t _timer_out_ = 100000;

	mov	DWORD PTR _timer_out_$[rsp], 100000	; 000186a0H

; 36   : 	if (a_type == 0) {

	movzx	eax, BYTE PTR a_type$[rsp]
	test	eax, eax
	jne	SHORT $LN8@mouse_wait
$LN7@mouse_wait:

; 37   : 		while (_timer_out_--){

	mov	eax, DWORD PTR _timer_out_$[rsp]
	mov	DWORD PTR tv68[rsp], eax
	mov	eax, DWORD PTR _timer_out_$[rsp]
	dec	eax
	mov	DWORD PTR _timer_out_$[rsp], eax
	cmp	DWORD PTR tv68[rsp], 0
	je	SHORT $LN6@mouse_wait

; 38   : 			if ((x64_inportb(0x64) & 1) == 1){

	mov	cx, 100					; 00000064H
	call	x64_inportb
	movzx	eax, al
	and	eax, 1
	cmp	eax, 1
	jne	SHORT $LN5@mouse_wait

; 39   : 				return;

	jmp	SHORT $LN9@mouse_wait
$LN5@mouse_wait:

; 40   : 			}
; 41   : 		}

	jmp	SHORT $LN7@mouse_wait
$LN6@mouse_wait:

; 42   : 		return;

	jmp	SHORT $LN9@mouse_wait

; 43   : 	}else {

	jmp	SHORT $LN4@mouse_wait
$LN8@mouse_wait:
$LN3@mouse_wait:

; 44   : 		while (_timer_out_--){

	mov	eax, DWORD PTR _timer_out_$[rsp]
	mov	DWORD PTR tv76[rsp], eax
	mov	eax, DWORD PTR _timer_out_$[rsp]
	dec	eax
	mov	DWORD PTR _timer_out_$[rsp], eax
	cmp	DWORD PTR tv76[rsp], 0
	je	SHORT $LN2@mouse_wait

; 45   : 			if ((x64_inportb(0x64) & 2) == 0){

	mov	cx, 100					; 00000064H
	call	x64_inportb
	movzx	eax, al
	and	eax, 2
	test	eax, eax
	jne	SHORT $LN1@mouse_wait

; 46   : 				return;

	jmp	SHORT $LN9@mouse_wait
$LN1@mouse_wait:

; 47   : 			}
; 48   : 		}

	jmp	SHORT $LN3@mouse_wait
$LN2@mouse_wait:
$LN4@mouse_wait:
$LN9@mouse_wait:

; 49   : 		return;
; 50   : 	}
; 51   : }

	add	rsp, 56					; 00000038H
	ret	0
?mouse_wait@@YAXE@Z ENDP				; mouse_wait
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
;	COMDAT ??__Emouse@@YAXXZ
text$yc	SEGMENT
??__Emouse@@YAXXZ PROC					; `dynamic initializer for 'mouse'', COMDAT

; 31   : static mutex_t  *mouse = create_mutex();

	sub	rsp, 40					; 00000028H
	call	?create_mutex@@YAPEAUmutex_t@@XZ	; create_mutex
	mov	QWORD PTR mouse, rax
	add	rsp, 40					; 00000028H
	ret	0
??__Emouse@@YAXXZ ENDP					; `dynamic initializer for 'mouse''
text$yc	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
status$ = 32
?initialize_mouse@@YAXXZ PROC				; initialize_mouse

; 177  : void initialize_mouse () {

$LN3:
	sub	rsp, 56					; 00000038H

; 178  : 	mouse_cycle = 0;

	mov	BYTE PTR mouse_cycle, 0

; 179  : 	mouse_x = 0;

	mov	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x

; 180  : 	mouse_y = 0;

	mov	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y

; 181  : 
; 182  : 	uint8_t status;
; 183  : 
; 184  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 185  :     outportb (0x64, 0xA8);

	mov	dl, 168					; 000000a8H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 186  : 
; 187  : 	mouse_wait(1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 188  : 	outportb (0x64, 0x20);

	mov	dl, 32					; 00000020H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 189  : 
; 190  : 	mouse_wait (0);

	xor	ecx, ecx
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 191  : 	status = (inportb (0x60) | 2);

	mov	cx, 96					; 00000060H
	call	?inportb@@YAEG@Z			; inportb
	movzx	eax, al
	or	eax, 2
	mov	BYTE PTR status$[rsp], al

; 192  : 
; 193  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 194  : 	outportb (0x64, 0x60);

	mov	dl, 96					; 00000060H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 195  : 
; 196  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 197  : 	outportb (0x60, status);

	movzx	edx, BYTE PTR status$[rsp]
	mov	cx, 96					; 00000060H
	call	?outportb@@YAXGE@Z			; outportb

; 198  : 
; 199  : 	mouse_write (0xF6);

	mov	cl, 246					; 000000f6H
	call	?mouse_write@@YAXE@Z			; mouse_write

; 200  : 	mouse_read ();

	call	?mouse_read@@YAEXZ			; mouse_read

; 201  : 
; 202  : 	mouse_write (0xF4);

	mov	cl, 244					; 000000f4H
	call	?mouse_write@@YAXE@Z			; mouse_write

; 203  : 	mouse_read ();

	call	?mouse_read@@YAEXZ			; mouse_read

; 204  : 
; 205  : 	interrupt_set (34, mouse_handler, 12);

	mov	r8b, 12
	lea	rdx, OFFSET FLAT:?mouse_handler@@YAX_KPEAX@Z ; mouse_handler
	mov	ecx, 34					; 00000022H
	call	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z	; interrupt_set

; 206  : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_mouse@@YAXXZ ENDP				; initialize_mouse
_TEXT	ENDS
END
