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
CONST	SEGMENT
$SG6068	DB	'IOMOUSE', 00H
CONST	ENDS
PUBLIC	?initialize_mouse@@YAXXZ			; initialize_mouse
PUBLIC	?mouse_wait@@YAXE@Z				; mouse_wait
PUBLIC	?mouse_write@@YAXE@Z				; mouse_write
PUBLIC	?mouse_read@@YAEXZ				; mouse_read
PUBLIC	?left_button_up@@YAHXZ				; left_button_up
PUBLIC	?mouse_handler@@YAX_KPEAX@Z			; mouse_handler
PUBLIC	?mouse_ioquery@@YAHHPEAX@Z			; mouse_ioquery
PUBLIC	?mouse_register_device@@YAXXZ			; mouse_register_device
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	x64_inportb:PROC
EXTRN	?inportb@@YAEG@Z:PROC				; inportb
EXTRN	?outportb@@YAXGE@Z:PROC				; outportb
EXTRN	?interrupt_end@@YAXI@Z:PROC			; interrupt_end
EXTRN	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z:PROC	; interrupt_set
EXTRN	?irq_mask@@YAXE_N@Z:PROC			; irq_mask
EXTRN	?strcpy@@YAPEADPEADPEBD@Z:PROC			; strcpy
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
EXTRN	?vfs_register@@YAXHPEAU_file_system_@@@Z:PROC	; vfs_register
_BSS	SEGMENT
mouse_byte DB	04H DUP (?)
mouse	DQ	01H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?initialize_mouse@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+195
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
	DD	imagerel $LN28+1119
	DD	imagerel $unwind$?mouse_handler@@YAX_KPEAX@Z
$pdata$?mouse_ioquery@@YAHHPEAX@Z DD imagerel $LN8
	DD	imagerel $LN8+73
	DD	imagerel $unwind$?mouse_ioquery@@YAHHPEAX@Z
$pdata$?mouse_register_device@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+109
	DD	imagerel $unwind$?mouse_register_device@@YAXXZ
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
$unwind$?mouse_ioquery@@YAHHPEAX@Z DD 010d01H
	DD	0620dH
$unwind$?mouse_register_device@@YAXXZ DD 010401H
	DD	06204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
mouse_file$ = 32
?mouse_register_device@@YAXXZ PROC			; mouse_register_device

; 202  : void mouse_register_device () {

$LN3:
	sub	rsp, 56					; 00000038H

; 203  : 	file_system_t *mouse_file = (file_system_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR mouse_file$[rsp], rax

; 204  : 	strcpy (mouse_file->name, "IOMOUSE");

	mov	rax, QWORD PTR mouse_file$[rsp]
	lea	rdx, OFFSET FLAT:$SG6068
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 205  : 	mouse_file->sys_open = NULL;

	mov	rax, QWORD PTR mouse_file$[rsp]
	mov	QWORD PTR [rax+8], 0

; 206  : 	mouse_file->sys_read = NULL;

	mov	rax, QWORD PTR mouse_file$[rsp]
	mov	QWORD PTR [rax+16], 0

; 207  : 	mouse_file->sys_read_blk = NULL;

	mov	rax, QWORD PTR mouse_file$[rsp]
	mov	QWORD PTR [rax+24], 0

; 208  : 	mouse_file->ioquery = mouse_ioquery;

	mov	rax, QWORD PTR mouse_file$[rsp]
	lea	rcx, OFFSET FLAT:?mouse_ioquery@@YAHHPEAX@Z ; mouse_ioquery
	mov	QWORD PTR [rax+32], rcx

; 209  : 	vfs_register (3,mouse_file);

	mov	rdx, QWORD PTR mouse_file$[rsp]
	mov	ecx, 3
	call	?vfs_register@@YAXHPEAU_file_system_@@@Z ; vfs_register

; 210  : }

	add	rsp, 56					; 00000038H
	ret	0
?mouse_register_device@@YAXXZ ENDP			; mouse_register_device
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
tv64 = 32
code$ = 64
arg$ = 72
?mouse_ioquery@@YAHHPEAX@Z PROC				; mouse_ioquery

; 183  : int mouse_ioquery (int code, void* arg) {

$LN8:
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 184  : 	switch (code) {

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv64[rsp], eax
	cmp	DWORD PTR tv64[rsp], 300		; 0000012cH
	je	SHORT $LN3@mouse_ioqu
	cmp	DWORD PTR tv64[rsp], 301		; 0000012dH
	je	SHORT $LN2@mouse_ioqu
	jmp	SHORT $LN1@mouse_ioqu
$LN3@mouse_ioqu:

; 185  : 		case MOUSE_IOCODE_DISABLE:
; 186  : 			irq_mask(12,true);

	mov	dl, 1
	mov	cl, 12
	call	?irq_mask@@YAXE_N@Z			; irq_mask

; 187  : 			break;

	jmp	SHORT $LN4@mouse_ioqu
$LN2@mouse_ioqu:

; 188  : 		case MOUSE_IOCODE_ENABLE:
; 189  : 			irq_mask(12, false);

	xor	edx, edx
	mov	cl, 12
	call	?irq_mask@@YAXE_N@Z			; irq_mask
$LN1@mouse_ioqu:
$LN4@mouse_ioqu:

; 190  : 			break;
; 191  : 		default:
; 192  : 			break;
; 193  : 	}
; 194  : 
; 195  : 	return 1;

	mov	eax, 1

; 196  : }

	add	rsp, 56					; 00000038H
	ret	0
?mouse_ioquery@@YAHHPEAX@Z ENDP				; mouse_ioquery
_TEXT	ENDS
; Function compile flags: /Odtpy
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

; 71   : void mouse_handler (size_t p, void* param) {

$LN28:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 72   : 	x64_cli();

	call	x64_cli

; 73   : 	set_multi_task_enable (false);

	xor	ecx, ecx
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 74   : 	uint8_t status = inportb (MOUSE_STATUS);

	mov	cx, 100					; 00000064H
	call	?inportb@@YAEG@Z			; inportb
	mov	BYTE PTR status$[rsp], al
$LN25@mouse_hand:

; 75   : 	while ((status & MOUSE_BBIT) && (status & MOUSE_F_BIT)) {

	movzx	eax, BYTE PTR status$[rsp]
	and	eax, 1
	test	eax, eax
	je	$LN24@mouse_hand
	movzx	eax, BYTE PTR status$[rsp]
	and	eax, 32					; 00000020H
	test	eax, eax
	je	$LN24@mouse_hand

; 76   : 		int8_t mouse_in = inportb (MOUSE_PORT);

	mov	cx, 96					; 00000060H
	call	?inportb@@YAEG@Z			; inportb
	mov	BYTE PTR mouse_in$1[rsp], al

; 77   : 		switch (mouse_cycle) {

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

; 78   : 		case 0:
; 79   : 			mouse_byte[0] = mouse_in;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 80   : 			if (!(mouse_in & MOUSE_V_BIT)) break;

	movsx	eax, BYTE PTR mouse_in$1[rsp]
	and	eax, 8
	test	eax, eax
	jne	SHORT $LN20@mouse_hand
	jmp	SHORT $LN22@mouse_hand
$LN20@mouse_hand:

; 81   : 			++mouse_cycle;

	movzx	eax, BYTE PTR mouse_cycle
	inc	al
	mov	BYTE PTR mouse_cycle, al

; 82   : 			break;

	jmp	SHORT $LN22@mouse_hand
$LN19@mouse_hand:

; 83   : 		case 1:
; 84   : 			mouse_byte[1] = mouse_in;

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 85   : 			++mouse_cycle;

	movzx	eax, BYTE PTR mouse_cycle
	inc	al
	mov	BYTE PTR mouse_cycle, al

; 86   : 			break;

	jmp	SHORT $LN22@mouse_hand
$LN18@mouse_hand:

; 87   : 		case 2:
; 88   : 			mouse_byte[2] = mouse_in;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 89   : 			goto finish_packet;

	jmp	SHORT $LN17@mouse_hand
	jmp	SHORT $finish_packet$29
$LN16@mouse_hand:

; 90   : 		case 3:
; 91   : 			mouse_byte[3] = mouse_in;

	mov	eax, 1
	imul	rax, 3
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 92   : 			goto finish_packet;

	jmp	SHORT $LN15@mouse_hand
	jmp	SHORT $finish_packet$29
$LN22@mouse_hand:

; 93   : 		}
; 94   : 
; 95   : 		goto read_next;

	jmp	$LN14@mouse_hand
	jmp	$read_next$30
$LN15@mouse_hand:
$LN17@mouse_hand:
$finish_packet$29:

; 96   : 
; 97   : finish_packet:
; 98   : 		mouse_cycle = 0;

	mov	BYTE PTR mouse_cycle, 0

; 99   : 
; 100  : 		int x = mouse_byte[1];

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR x$2[rsp], eax

; 101  : 		int y = mouse_byte[2];

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR y$3[rsp], eax

; 102  : 		if (x && mouse_byte[0] & ( 1 <<  4)) {

	cmp	DWORD PTR x$2[rsp], 0
	je	SHORT $LN13@mouse_hand
	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 16
	test	eax, eax
	je	SHORT $LN13@mouse_hand

; 103  : 			x = x - 0x100;

	mov	eax, DWORD PTR x$2[rsp]
	sub	eax, 256				; 00000100H
	mov	DWORD PTR x$2[rsp], eax
$LN13@mouse_hand:

; 104  : 		}
; 105  : 
; 106  : 		if (y && mouse_byte[0] & (1 << 5)) {

	cmp	DWORD PTR y$3[rsp], 0
	je	SHORT $LN12@mouse_hand
	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 32					; 00000020H
	test	eax, eax
	je	SHORT $LN12@mouse_hand

; 107  : 			y = y - 0x100;

	mov	eax, DWORD PTR y$3[rsp]
	sub	eax, 256				; 00000100H
	mov	DWORD PTR y$3[rsp], eax
$LN12@mouse_hand:

; 108  : 		}
; 109  : 
; 110  : 		mouse_x_difference = x;

	mov	eax, DWORD PTR x$2[rsp]
	mov	DWORD PTR ?mouse_x_difference@@3HA, eax	; mouse_x_difference

; 111  : 		mouse_y_difference = y;

	mov	eax, DWORD PTR y$3[rsp]
	mov	DWORD PTR ?mouse_y_difference@@3HA, eax	; mouse_y_difference

; 112  : 		mouse_x += mouse_x_difference;

	mov	eax, DWORD PTR ?mouse_x_difference@@3HA	; mouse_x_difference
	mov	ecx, DWORD PTR ?mouse_x@@3HA		; mouse_x
	add	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x

; 113  : 		mouse_y -= mouse_y_difference;

	mov	eax, DWORD PTR ?mouse_y_difference@@3HA	; mouse_y_difference
	mov	ecx, DWORD PTR ?mouse_y@@3HA		; mouse_y
	sub	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y

; 114  : 
; 115  : 		if (mouse_x < 0)

	cmp	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x
	jge	SHORT $LN11@mouse_hand

; 116  : 			mouse_x = 0;

	mov	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x
$LN11@mouse_hand:

; 117  : 
; 118  : 		if (mouse_y < 0)

	cmp	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y
	jge	SHORT $LN10@mouse_hand

; 119  : 			mouse_y = 0;

	mov	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y
$LN10@mouse_hand:

; 120  : 
; 121  : 		if (mouse_x > get_screen_width())

	call	?get_screen_width@@YAIXZ		; get_screen_width
	cmp	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x
	jbe	SHORT $LN9@mouse_hand

; 122  : 			mouse_x = get_screen_width() - 7;

	call	?get_screen_width@@YAIXZ		; get_screen_width
	sub	eax, 7
	mov	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x
$LN9@mouse_hand:

; 123  : 
; 124  : 		if (mouse_y > get_screen_height())

	call	?get_screen_height@@YAIXZ		; get_screen_height
	cmp	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y
	jbe	SHORT $LN8@mouse_hand

; 125  : 			mouse_y = get_screen_height() - 7;

	call	?get_screen_height@@YAIXZ		; get_screen_height
	sub	eax, 7
	mov	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y
$LN8@mouse_hand:

; 126  : 
; 127  : 		mouse_button_state = 0;

	mov	DWORD PTR ?mouse_button_state@@3IA, 0	; mouse_button_state

; 128  : 
; 129  : 		if (mouse_byte[0] & 0x01) {    //0x01 for PS/2

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN7@mouse_hand

; 130  : 			curr_button[0] = 1;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 1

; 131  : 			mouse_button_state |= 1;

	mov	eax, DWORD PTR ?mouse_button_state@@3IA	; mouse_button_state
	or	eax, 1
	mov	DWORD PTR ?mouse_button_state@@3IA, eax	; mouse_button_state

; 132  : 		}else

	jmp	SHORT $LN6@mouse_hand
$LN7@mouse_hand:

; 133  : 			curr_button[0] = 0;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 0
$LN6@mouse_hand:

; 134  : 
; 135  : 		if (mouse_byte[0] & 0x02) {

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN5@mouse_hand

; 136  : 			curr_button[2] = 1;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 1

; 137  : 		}else 

	jmp	SHORT $LN4@mouse_hand
$LN5@mouse_hand:

; 138  : 			curr_button[2] = 0;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 0
$LN4@mouse_hand:

; 139  : 
; 140  : 		if (mouse_byte[0] & 0x04)

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 4
	test	eax, eax
	je	SHORT $LN3@mouse_hand

; 141  : 			mouse_button |= MOUSE_MIDDLE_CLICK;

	mov	eax, DWORD PTR ?mouse_button@@3HC	; mouse_button
	or	eax, 4
	mov	DWORD PTR ?mouse_button@@3HC, eax	; mouse_button
$LN3@mouse_hand:

; 142  : 		
; 143  : 		//!Pass here the message stream to all waiting processes
; 144  : 	
; 145  : 
; 146  : 
; 147  : 		mutex_lock (mouse);

	mov	rcx, QWORD PTR mouse
	call	?mutex_lock@@YAXPEAUmutex_t@@@Z		; mutex_lock

; 148  : 		dwm_message_t *msg = (dwm_message_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR msg$4[rsp], rax

; 149  : 		msg->type = 1;

	mov	eax, 1
	mov	rcx, QWORD PTR msg$4[rsp]
	mov	WORD PTR [rcx], ax

; 150  : 		msg->dword = mouse_x;

	mov	rax, QWORD PTR msg$4[rsp]
	mov	ecx, DWORD PTR ?mouse_x@@3HA		; mouse_x
	mov	DWORD PTR [rax+4], ecx

; 151  : 		msg->dword2 = mouse_y;

	mov	rax, QWORD PTR msg$4[rsp]
	mov	ecx, DWORD PTR ?mouse_y@@3HA		; mouse_y
	mov	DWORD PTR [rax+8], ecx

; 152  : 		msg->dword4 = mouse_button_state;

	mov	rax, QWORD PTR msg$4[rsp]
	mov	ecx, DWORD PTR ?mouse_button_state@@3IA	; mouse_button_state
	mov	DWORD PTR [rax+16], ecx

; 153  : 		msg->dword5 = mouse_byte[1];

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	rcx, QWORD PTR msg$4[rsp]
	mov	DWORD PTR [rcx+20], eax

; 154  : 		msg->dword6 = -mouse_byte[2];

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	neg	eax
	mov	rcx, QWORD PTR msg$4[rsp]
	mov	DWORD PTR [rcx+24], eax

; 155  : 		dwm_put_message (msg);

	mov	rcx, QWORD PTR msg$4[rsp]
	call	?dwm_put_message@@YAXPEAU_dwm_message_@@@Z ; dwm_put_message

; 156  : 		pmmngr_free (msg);

	mov	rcx, QWORD PTR msg$4[rsp]
	call	?pmmngr_free@@YAXPEAX@Z			; pmmngr_free

; 157  : 		mutex_unlock (mouse);

	mov	rcx, QWORD PTR mouse
	call	?mutex_unlock@@YAXPEAUmutex_t@@@Z	; mutex_unlock

; 158  : 
; 159  : 		thread_t* thr = (thread_t*)thread_iterate_block_list (2);

	mov	ecx, 2
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR thr$5[rsp], rax

; 160  : 		if (thr != NULL){

	cmp	QWORD PTR thr$5[rsp], 0
	je	SHORT $LN2@mouse_hand

; 161  : 			thr->state = THREAD_STATE_READY;

	mov	rax, QWORD PTR thr$5[rsp]
	mov	BYTE PTR [rax+224], 1

; 162  : 			unblock_thread(thr);

	mov	rcx, QWORD PTR thr$5[rsp]
	call	?unblock_thread@@YAXPEAU_thread_@@@Z	; unblock_thread
$LN2@mouse_hand:

; 163  : 		}
; 164  : 
; 165  : 		if (left_button_up()) {

	call	?left_button_up@@YAHXZ			; left_button_up
	test	eax, eax
	je	SHORT $LN1@mouse_hand

; 166  : 			mouse_button_state |= 5;

	mov	eax, DWORD PTR ?mouse_button_state@@3IA	; mouse_button_state
	or	eax, 5
	mov	DWORD PTR ?mouse_button_state@@3IA, eax	; mouse_button_state
$LN1@mouse_hand:

; 167  : 		}
; 168  : 
; 169  : 
; 170  : 		memcpy (prev_button, curr_button, 3);

	mov	r8d, 3
	lea	rdx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	lea	rcx, OFFSET FLAT:?prev_button@@3PAEA	; prev_button
	call	memcpy

; 171  : 		memset (curr_button, 0x00, 3);

	mov	r8d, 3
	xor	edx, edx
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	call	?memset@@YAXPEAXEI@Z			; memset
$LN14@mouse_hand:
$read_next$30:

; 172  : read_next:
; 173  : 		break;

	jmp	SHORT $LN24@mouse_hand

; 174  : 	}

	jmp	$LN25@mouse_hand
$LN24@mouse_hand:

; 175  : 
; 176  : 	set_multi_task_enable(true);

	mov	cl, 1
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 177  : 	interrupt_end(12);

	mov	ecx, 12
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 178  : 	x64_sti();

	call	x64_sti

; 179  : }

	add	rsp, 72					; 00000048H
	ret	0
?mouse_handler@@YAX_KPEAX@Z ENDP			; mouse_handler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
tv72 = 0
?left_button_up@@YAHXZ PROC				; left_button_up

; 67   : int left_button_up() {

$LN5:
	sub	rsp, 24

; 68   : 	return prev_button[0] && !curr_button[0];

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

; 69   : }

	add	rsp, 24
	ret	0
?left_button_up@@YAHXZ ENDP				; left_button_up
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
?mouse_read@@YAEXZ PROC					; mouse_read

; 61   : uint8_t mouse_read () {

$LN3:
	sub	rsp, 40					; 00000028H

; 62   : 	mouse_wait (0);

	xor	ecx, ecx
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 63   : 	return inportb (0x60);

	mov	cx, 96					; 00000060H
	call	?inportb@@YAEG@Z			; inportb

; 64   : }

	add	rsp, 40					; 00000028H
	ret	0
?mouse_read@@YAEXZ ENDP					; mouse_read
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
write$ = 48
?mouse_write@@YAXE@Z PROC				; mouse_write

; 54   : void mouse_write (uint8_t write) {

$LN3:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H

; 55   : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 56   : 	outportb (0x64, 0xD4);

	mov	dl, 212					; 000000d4H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 57   : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 58   : 	outportb (0x60, write);

	movzx	edx, BYTE PTR write$[rsp]
	mov	cx, 96					; 00000060H
	call	?outportb@@YAXGE@Z			; outportb

; 59   : }

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

; 35   : void  mouse_wait (uint8_t a_type){

$LN11:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 36   : 	uint32_t _timer_out_ = 100000;

	mov	DWORD PTR _timer_out_$[rsp], 100000	; 000186a0H

; 37   : 	if (a_type == 0) {

	movzx	eax, BYTE PTR a_type$[rsp]
	test	eax, eax
	jne	SHORT $LN8@mouse_wait
$LN7@mouse_wait:

; 38   : 		while (_timer_out_--){

	mov	eax, DWORD PTR _timer_out_$[rsp]
	mov	DWORD PTR tv68[rsp], eax
	mov	eax, DWORD PTR _timer_out_$[rsp]
	dec	eax
	mov	DWORD PTR _timer_out_$[rsp], eax
	cmp	DWORD PTR tv68[rsp], 0
	je	SHORT $LN6@mouse_wait

; 39   : 			if ((x64_inportb(0x64) & 1) == 1){

	mov	cx, 100					; 00000064H
	call	x64_inportb
	movzx	eax, al
	and	eax, 1
	cmp	eax, 1
	jne	SHORT $LN5@mouse_wait

; 40   : 				return;

	jmp	SHORT $LN9@mouse_wait
$LN5@mouse_wait:

; 41   : 			}
; 42   : 		}

	jmp	SHORT $LN7@mouse_wait
$LN6@mouse_wait:

; 43   : 		return;

	jmp	SHORT $LN9@mouse_wait

; 44   : 	}else {

	jmp	SHORT $LN4@mouse_wait
$LN8@mouse_wait:
$LN3@mouse_wait:

; 45   : 		while (_timer_out_--){

	mov	eax, DWORD PTR _timer_out_$[rsp]
	mov	DWORD PTR tv76[rsp], eax
	mov	eax, DWORD PTR _timer_out_$[rsp]
	dec	eax
	mov	DWORD PTR _timer_out_$[rsp], eax
	cmp	DWORD PTR tv76[rsp], 0
	je	SHORT $LN2@mouse_wait

; 46   : 			if ((x64_inportb(0x64) & 2) == 0){

	mov	cx, 100					; 00000064H
	call	x64_inportb
	movzx	eax, al
	and	eax, 2
	test	eax, eax
	jne	SHORT $LN1@mouse_wait

; 47   : 				return;

	jmp	SHORT $LN9@mouse_wait
$LN1@mouse_wait:

; 48   : 			}
; 49   : 		}

	jmp	SHORT $LN3@mouse_wait
$LN2@mouse_wait:
$LN4@mouse_wait:
$LN9@mouse_wait:

; 50   : 		return;
; 51   : 	}
; 52   : }

	add	rsp, 56					; 00000038H
	ret	0
?mouse_wait@@YAXE@Z ENDP				; mouse_wait
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
;	COMDAT ??__Emouse@@YAXXZ
text$yc	SEGMENT
??__Emouse@@YAXXZ PROC					; `dynamic initializer for 'mouse'', COMDAT

; 32   : static mutex_t  *mouse = create_mutex();

	sub	rsp, 40					; 00000028H
	call	?create_mutex@@YAPEAUmutex_t@@XZ	; create_mutex
	mov	QWORD PTR mouse, rax
	add	rsp, 40					; 00000028H
	ret	0
??__Emouse@@YAXXZ ENDP					; `dynamic initializer for 'mouse''
text$yc	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
status$ = 32
?initialize_mouse@@YAXXZ PROC				; initialize_mouse

; 212  : void initialize_mouse () {

$LN3:
	sub	rsp, 56					; 00000038H

; 213  : 	mouse_cycle = 0;

	mov	BYTE PTR mouse_cycle, 0

; 214  : 	mouse_x = 0;

	mov	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x

; 215  : 	mouse_y = 0;

	mov	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y

; 216  : 
; 217  : 	uint8_t status;
; 218  : 
; 219  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 220  :     outportb (0x64, 0xA8);

	mov	dl, 168					; 000000a8H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 221  : 
; 222  : 	mouse_wait(1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 223  : 	outportb (0x64, 0x20);

	mov	dl, 32					; 00000020H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 224  : 
; 225  : 	mouse_wait (0);

	xor	ecx, ecx
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 226  : 	status = (inportb (0x60) | 2);

	mov	cx, 96					; 00000060H
	call	?inportb@@YAEG@Z			; inportb
	movzx	eax, al
	or	eax, 2
	mov	BYTE PTR status$[rsp], al

; 227  : 
; 228  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 229  : 	outportb (0x64, 0x60);

	mov	dl, 96					; 00000060H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 230  : 
; 231  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 232  : 	outportb (0x60, status);

	movzx	edx, BYTE PTR status$[rsp]
	mov	cx, 96					; 00000060H
	call	?outportb@@YAXGE@Z			; outportb

; 233  : 
; 234  : 	mouse_write (0xF6);

	mov	cl, 246					; 000000f6H
	call	?mouse_write@@YAXE@Z			; mouse_write

; 235  : 	mouse_read ();

	call	?mouse_read@@YAEXZ			; mouse_read

; 236  : 
; 237  : 	mouse_write (0xF4);

	mov	cl, 244					; 000000f4H
	call	?mouse_write@@YAXE@Z			; mouse_write

; 238  : 	mouse_read ();

	call	?mouse_read@@YAEXZ			; mouse_read

; 239  : 
; 240  : 	interrupt_set (34, mouse_handler, 12);  //34

	mov	r8b, 12
	lea	rdx, OFFSET FLAT:?mouse_handler@@YAX_KPEAX@Z ; mouse_handler
	mov	ecx, 34					; 00000022H
	call	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z	; interrupt_set

; 241  : 
; 242  : 	mouse_register_device ();

	call	?mouse_register_device@@YAXXZ		; mouse_register_device

; 243  : 	irq_mask(12, true);

	mov	dl, 1
	mov	cl, 12
	call	?irq_mask@@YAXE_N@Z			; irq_mask

; 244  : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_mouse@@YAXXZ ENDP				; initialize_mouse
_TEXT	ENDS
END
