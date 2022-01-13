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
CONST	SEGMENT
$SG6061	DB	'mouse', 00H
	ORG $+2
$SG6062	DB	'/dev/mouse', 00H
	ORG $+5
$SG6066	DB	'mouse interrupt setupped', 0aH, 00H
CONST	ENDS
PUBLIC	?initialize_mouse@@YAXXZ			; initialize_mouse
PUBLIC	?mouse_wait@@YAXE@Z				; mouse_wait
PUBLIC	?mouse_write@@YAXE@Z				; mouse_write
PUBLIC	?mouse_read@@YAEXZ				; mouse_read
PUBLIC	?left_button_up@@YAHXZ				; left_button_up
PUBLIC	?mouse_handler@@YAX_KPEAX@Z			; mouse_handler
PUBLIC	?mouse_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z	; mouse_ioquery
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
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z:PROC	; vfs_mount
EXTRN	?malloc@@YAPEAX_K@Z:PROC			; malloc
EXTRN	?get_screen_width@@YAIXZ:PROC			; get_screen_width
EXTRN	?get_screen_height@@YAIXZ:PROC			; get_screen_height
EXTRN	?dwm_put_message@@YAXPEAU_dwm_message_@@@Z:PROC	; dwm_put_message
EXTRN	?create_mutex@@YAPEAUmutex_t@@XZ:PROC		; create_mutex
_BSS	SEGMENT
mouse_byte DB	04H DUP (?)
	ALIGN	8

mouse	DQ	01H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?initialize_mouse@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+198
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
$pdata$?mouse_handler@@YAX_KPEAX@Z DD imagerel $LN26
	DD	imagerel $LN26+995
	DD	imagerel $unwind$?mouse_handler@@YAX_KPEAX@Z
$pdata$?mouse_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN9
	DD	imagerel $LN9+97
	DD	imagerel $unwind$?mouse_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z
$pdata$?mouse_register_device@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+201
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
	DD	0c20eH
$unwind$?mouse_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD 011201H
	DD	06212H
$unwind$?mouse_register_device@@YAXXZ DD 010401H
	DD	06204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
node$ = 32
?mouse_register_device@@YAXXZ PROC			; mouse_register_device

; 211  : void mouse_register_device () {

$LN3:
	sub	rsp, 56					; 00000038H

; 212  : 	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 104				; 00000068H
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	QWORD PTR node$[rsp], rax

; 213  : 	strcpy (node->filename, "mouse");

	mov	rax, QWORD PTR node$[rsp]
	lea	rdx, OFFSET FLAT:$SG6061
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 214  : 	node->size = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+32], 0

; 215  : 	node->eof = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+36], 0

; 216  : 	node->pos = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+40], 0

; 217  : 	node->current = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+44], 0

; 218  : 	node->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+48], 2

; 219  : 	node->status = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+52], 0

; 220  : 	node->open = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+64], 0

; 221  : 	node->read = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+72], 0

; 222  : 	node->write = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+80], 0

; 223  : 	node->read_blk = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+88], 0

; 224  : 	node->ioquery = mouse_ioquery;

	mov	rax, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:?mouse_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z ; mouse_ioquery
	mov	QWORD PTR [rax+96], rcx

; 225  : 	vfs_mount ("/dev/mouse", node);

	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:$SG6062
	call	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z	; vfs_mount

; 226  : }

	add	rsp, 56					; 00000038H
	ret	0
?mouse_register_device@@YAXXZ ENDP			; mouse_register_device
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
tv64 = 32
node$ = 64
code$ = 72
arg$ = 80
?mouse_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z PROC		; mouse_ioquery

; 189  : int mouse_ioquery (vfs_node_t *node, int code, void* arg) {

$LN9:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 190  : 	switch (code) {

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv64[rsp], eax
	cmp	DWORD PTR tv64[rsp], 300		; 0000012cH
	je	SHORT $LN4@mouse_ioqu
	cmp	DWORD PTR tv64[rsp], 301		; 0000012dH
	je	SHORT $LN3@mouse_ioqu
	cmp	DWORD PTR tv64[rsp], 302		; 0000012eH
	je	SHORT $LN2@mouse_ioqu
	jmp	SHORT $LN1@mouse_ioqu
$LN4@mouse_ioqu:

; 191  : 		case MOUSE_IOCODE_DISABLE:
; 192  : 			irq_mask(12,true);

	mov	dl, 1
	mov	cl, 12
	call	?irq_mask@@YAXE_N@Z			; irq_mask

; 193  : 			break;

	jmp	SHORT $LN5@mouse_ioqu
$LN3@mouse_ioqu:

; 194  : 		case MOUSE_IOCODE_ENABLE:
; 195  : 			irq_mask(12, false);

	xor	edx, edx
	mov	cl, 12
	call	?irq_mask@@YAXE_N@Z			; irq_mask

; 196  : 			break;

	jmp	SHORT $LN5@mouse_ioqu
$LN2@mouse_ioqu:

; 197  : 		case 302:
; 198  : 			return 10;

	mov	eax, 10
	jmp	SHORT $LN7@mouse_ioqu
$LN1@mouse_ioqu:
$LN5@mouse_ioqu:

; 199  : 			break;
; 200  : 		default:
; 201  : 			break;
; 202  : 	}
; 203  : 
; 204  : 	return 1;

	mov	eax, 1
$LN7@mouse_ioqu:

; 205  : }

	add	rsp, 56					; 00000038H
	ret	0
?mouse_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP		; mouse_ioquery
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\mouse.cpp
_TEXT	SEGMENT
mouse_in$1 = 32
status$ = 33
x$2 = 36
tv75 = 40
y$3 = 44
tv151 = 48
tv156 = 52
msg$4 = 56
p$ = 112
param$ = 120
?mouse_handler@@YAX_KPEAX@Z PROC			; mouse_handler

; 88   : void mouse_handler (size_t p, void* param) {

$LN26:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 89   : 
; 90   : 	uint8_t status = inportb (MOUSE_STATUS);

	mov	cx, 100					; 00000064H
	call	?inportb@@YAEG@Z			; inportb
	mov	BYTE PTR status$[rsp], al
$LN23@mouse_hand:

; 91   : 	while ((status & MOUSE_BBIT) && (status & MOUSE_F_BIT)) {

	movzx	eax, BYTE PTR status$[rsp]
	and	eax, 1
	test	eax, eax
	je	$LN22@mouse_hand
	movzx	eax, BYTE PTR status$[rsp]
	and	eax, 32					; 00000020H
	test	eax, eax
	je	$LN22@mouse_hand

; 92   : 		int8_t mouse_in = inportb (MOUSE_PORT);

	mov	cx, 96					; 00000060H
	call	?inportb@@YAEG@Z			; inportb
	mov	BYTE PTR mouse_in$1[rsp], al

; 93   : 		switch (mouse_cycle) {

	movzx	eax, BYTE PTR mouse_cycle
	mov	BYTE PTR tv75[rsp], al
	cmp	BYTE PTR tv75[rsp], 0
	je	SHORT $LN19@mouse_hand
	cmp	BYTE PTR tv75[rsp], 1
	je	SHORT $LN17@mouse_hand
	cmp	BYTE PTR tv75[rsp], 2
	je	SHORT $LN16@mouse_hand
	cmp	BYTE PTR tv75[rsp], 3
	je	$LN14@mouse_hand
	jmp	$LN20@mouse_hand
$LN19@mouse_hand:

; 94   : 		case 0:
; 95   : 			mouse_byte[0] = mouse_in;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 96   : 			if (!(mouse_in & MOUSE_V_BIT)) break;

	movsx	eax, BYTE PTR mouse_in$1[rsp]
	and	eax, 8
	test	eax, eax
	jne	SHORT $LN18@mouse_hand
	jmp	SHORT $LN20@mouse_hand
$LN18@mouse_hand:

; 97   : 			++mouse_cycle;

	movzx	eax, BYTE PTR mouse_cycle
	inc	al
	mov	BYTE PTR mouse_cycle, al

; 98   : 			break;

	jmp	SHORT $LN20@mouse_hand
$LN17@mouse_hand:

; 99   : 		case 1:
; 100  : 			mouse_byte[1] = mouse_in;

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 101  : 			++mouse_cycle;

	movzx	eax, BYTE PTR mouse_cycle
	inc	al
	mov	BYTE PTR mouse_cycle, al

; 102  : 			break;

	jmp	SHORT $LN20@mouse_hand
$LN16@mouse_hand:

; 103  : 		case 2:
; 104  : 			mouse_byte[2] = mouse_in;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 105  : 			goto finish_packet;

	jmp	SHORT $LN15@mouse_hand
	jmp	SHORT $finish_packet$27
$LN14@mouse_hand:

; 106  : 		case 3:
; 107  : 			mouse_byte[3] = mouse_in;

	mov	eax, 1
	imul	rax, 3
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	edx, BYTE PTR mouse_in$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 108  : 			goto finish_packet;

	jmp	SHORT $LN13@mouse_hand
	jmp	SHORT $finish_packet$27
$LN20@mouse_hand:

; 109  : 		}
; 110  : 
; 111  : 		goto read_next;

	jmp	$LN12@mouse_hand
	jmp	$read_next$28
$LN13@mouse_hand:
$LN15@mouse_hand:
$finish_packet$27:

; 112  : 
; 113  : finish_packet:
; 114  : 		mouse_cycle = 0;

	mov	BYTE PTR mouse_cycle, 0

; 115  : 
; 116  : 		int x = mouse_byte[1];

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR x$2[rsp], eax

; 117  : 		int y = mouse_byte[2];

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR y$3[rsp], eax

; 118  : 		if (x && mouse_byte[0] & ( 1 <<  4)) {

	cmp	DWORD PTR x$2[rsp], 0
	je	SHORT $LN11@mouse_hand
	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 16
	test	eax, eax
	je	SHORT $LN11@mouse_hand

; 119  : 			x = x - 0x100;

	mov	eax, DWORD PTR x$2[rsp]
	sub	eax, 256				; 00000100H
	mov	DWORD PTR x$2[rsp], eax
$LN11@mouse_hand:

; 120  : 		}
; 121  : 
; 122  : 		if (y && mouse_byte[0] & (1 << 5)) {

	cmp	DWORD PTR y$3[rsp], 0
	je	SHORT $LN10@mouse_hand
	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 32					; 00000020H
	test	eax, eax
	je	SHORT $LN10@mouse_hand

; 123  : 			y = y - 0x100;

	mov	eax, DWORD PTR y$3[rsp]
	sub	eax, 256				; 00000100H
	mov	DWORD PTR y$3[rsp], eax
$LN10@mouse_hand:

; 124  : 		}
; 125  : 
; 126  : 		mouse_x_difference = x;

	mov	eax, DWORD PTR x$2[rsp]
	mov	DWORD PTR ?mouse_x_difference@@3HA, eax	; mouse_x_difference

; 127  : 		mouse_y_difference = y;

	mov	eax, DWORD PTR y$3[rsp]
	mov	DWORD PTR ?mouse_y_difference@@3HA, eax	; mouse_y_difference

; 128  : 		mouse_x += mouse_x_difference;

	mov	eax, DWORD PTR ?mouse_x_difference@@3HA	; mouse_x_difference
	mov	ecx, DWORD PTR ?mouse_x@@3HA		; mouse_x
	add	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x

; 129  : 		mouse_y -= mouse_y_difference;

	mov	eax, DWORD PTR ?mouse_y_difference@@3HA	; mouse_y_difference
	mov	ecx, DWORD PTR ?mouse_y@@3HA		; mouse_y
	sub	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y

; 130  : 
; 131  : 		if (mouse_x < 0)

	cmp	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x
	jge	SHORT $LN9@mouse_hand

; 132  : 			mouse_x = 0;

	mov	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x
$LN9@mouse_hand:

; 133  : 
; 134  : 		if (mouse_y < 0)

	cmp	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y
	jge	SHORT $LN8@mouse_hand

; 135  : 			mouse_y = 0;

	mov	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y
$LN8@mouse_hand:

; 136  : 
; 137  : 		if (mouse_x + 24 > get_screen_width())

	mov	eax, DWORD PTR ?mouse_x@@3HA		; mouse_x
	add	eax, 24
	mov	DWORD PTR tv151[rsp], eax
	call	?get_screen_width@@YAIXZ		; get_screen_width
	mov	ecx, DWORD PTR tv151[rsp]
	cmp	ecx, eax
	jbe	SHORT $LN7@mouse_hand

; 138  : 			mouse_x = get_screen_width() - 24;

	call	?get_screen_width@@YAIXZ		; get_screen_width
	sub	eax, 24
	mov	DWORD PTR ?mouse_x@@3HA, eax		; mouse_x
$LN7@mouse_hand:

; 139  : 
; 140  : 		if (mouse_y + 24 > get_screen_height())

	mov	eax, DWORD PTR ?mouse_y@@3HA		; mouse_y
	add	eax, 24
	mov	DWORD PTR tv156[rsp], eax
	call	?get_screen_height@@YAIXZ		; get_screen_height
	mov	ecx, DWORD PTR tv156[rsp]
	cmp	ecx, eax
	jbe	SHORT $LN6@mouse_hand

; 141  : 			mouse_y = get_screen_height() - 24;

	call	?get_screen_height@@YAIXZ		; get_screen_height
	sub	eax, 24
	mov	DWORD PTR ?mouse_y@@3HA, eax		; mouse_y
$LN6@mouse_hand:

; 142  : 
; 143  : 		mouse_button_state = 0;

	mov	DWORD PTR ?mouse_button_state@@3IA, 0	; mouse_button_state

; 144  : 
; 145  : 		if (mouse_byte[0] & 0x01) {    //0x01 for PS/2

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN5@mouse_hand

; 146  : 			curr_button[0] = 1;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 1

; 147  : 			mouse_button_state |= 1;

	mov	eax, DWORD PTR ?mouse_button_state@@3IA	; mouse_button_state
	or	eax, 1
	mov	DWORD PTR ?mouse_button_state@@3IA, eax	; mouse_button_state

; 148  : 		}else

	jmp	SHORT $LN4@mouse_hand
$LN5@mouse_hand:

; 149  : 			curr_button[0] = 0;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 0
$LN4@mouse_hand:

; 150  : 
; 151  : 		if (mouse_byte[0] & 0x02) {

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN3@mouse_hand

; 152  : 			curr_button[2] = 1;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 1

; 153  : 		}else 

	jmp	SHORT $LN2@mouse_hand
$LN3@mouse_hand:

; 154  : 			curr_button[2] = 0;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	mov	BYTE PTR [rcx+rax], 0
$LN2@mouse_hand:

; 155  : 
; 156  : 		if (mouse_byte[0] & 0x04)

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	and	eax, 4
	test	eax, eax
	je	SHORT $LN1@mouse_hand

; 157  : 			mouse_button |= MOUSE_MIDDLE_CLICK;

	mov	eax, DWORD PTR ?mouse_button@@3HC	; mouse_button
	or	eax, 4
	mov	DWORD PTR ?mouse_button@@3HC, eax	; mouse_button
$LN1@mouse_hand:

; 158  : 		
; 159  : 		//!Pass here the message stream to all waiting processes
; 160  : 	
; 161  : 		x64_cli();

	call	x64_cli

; 162  : 		//mutex_lock (mouse);
; 163  : 		dwm_message_t msg; // = (dwm_message_t*)pmmngr_alloc();
; 164  : 		msg.type = 1;

	mov	eax, 1
	mov	WORD PTR msg$4[rsp], ax

; 165  : 		msg.dword = mouse_x;

	mov	eax, DWORD PTR ?mouse_x@@3HA		; mouse_x
	mov	DWORD PTR msg$4[rsp+4], eax

; 166  : 		msg.dword2 = mouse_y;

	mov	eax, DWORD PTR ?mouse_y@@3HA		; mouse_y
	mov	DWORD PTR msg$4[rsp+8], eax

; 167  : 		msg.dword4 = mouse_button_state;

	mov	eax, DWORD PTR ?mouse_button_state@@3IA	; mouse_button_state
	mov	DWORD PTR msg$4[rsp+16], eax

; 168  : 		msg.dword5 = mouse_byte[1];

	mov	eax, 1
	imul	rax, 1
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	mov	DWORD PTR msg$4[rsp+20], eax

; 169  : 		msg.dword6 = -mouse_byte[2];

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:mouse_byte
	movzx	eax, BYTE PTR [rcx+rax]
	neg	eax
	mov	DWORD PTR msg$4[rsp+24], eax

; 170  : 		dwm_put_message (&msg);

	lea	rcx, QWORD PTR msg$4[rsp]
	call	?dwm_put_message@@YAXPEAU_dwm_message_@@@Z ; dwm_put_message

; 171  : 		x64_sti();

	call	x64_sti

; 172  : 		//pmmngr_free (msg);
; 173  : 		//mutex_unlock (mouse);
; 174  :     /*	if (left_button_up()) {
; 175  : 			mouse_button_state |= 5;
; 176  : 		}*/
; 177  : 
; 178  : 		memcpy (prev_button, curr_button, 3);

	mov	r8d, 3
	lea	rdx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	lea	rcx, OFFSET FLAT:?prev_button@@3PAEA	; prev_button
	call	memcpy

; 179  : 		memset (curr_button, 0x00, 3);

	mov	r8d, 3
	xor	edx, edx
	lea	rcx, OFFSET FLAT:?curr_button@@3PAEA	; curr_button
	call	?memset@@YAXPEAXEI@Z			; memset
$LN12@mouse_hand:
$read_next$28:

; 180  : read_next:
; 181  : 		break;

	jmp	SHORT $LN22@mouse_hand

; 182  : 	}

	jmp	$LN23@mouse_hand
$LN22@mouse_hand:

; 183  : 
; 184  : 	interrupt_end(12);

	mov	ecx, 12
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 185  : }

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
	call	?inportb@@YAEG@Z			; inportb

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
	call	?outportb@@YAXGE@Z			; outportb

; 63   : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 64   : 	outportb (0x60, write);

	movzx	edx, BYTE PTR write$[rsp]
	mov	cx, 96					; 00000060H
	call	?outportb@@YAXGE@Z			; outportb

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

; 232  : void initialize_mouse () {

$LN3:
	sub	rsp, 56					; 00000038H

; 233  : 	mouse_cycle = 0;

	mov	BYTE PTR mouse_cycle, 0

; 234  : 	mouse_x = 0;

	mov	DWORD PTR ?mouse_x@@3HA, 0		; mouse_x

; 235  : 	mouse_y = 0;

	mov	DWORD PTR ?mouse_y@@3HA, 0		; mouse_y

; 236  : 
; 237  : 	uint8_t status;
; 238  : 
; 239  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 240  :     outportb (0x64, 0xA8);

	mov	dl, 168					; 000000a8H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 241  : 
; 242  : 	mouse_wait(1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 243  : 	outportb (0x64, 0x20);

	mov	dl, 32					; 00000020H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 244  : 
; 245  : 	mouse_wait (0);

	xor	ecx, ecx
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 246  : 	status = (inportb (0x60) | 2);

	mov	cx, 96					; 00000060H
	call	?inportb@@YAEG@Z			; inportb
	movzx	eax, al
	or	eax, 2
	mov	BYTE PTR status$[rsp], al

; 247  : 
; 248  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 249  : 	outportb (0x64, 0x60);

	mov	dl, 96					; 00000060H
	mov	cx, 100					; 00000064H
	call	?outportb@@YAXGE@Z			; outportb

; 250  : 
; 251  : 	mouse_wait (1);

	mov	cl, 1
	call	?mouse_wait@@YAXE@Z			; mouse_wait

; 252  : 	outportb (0x60, status);

	movzx	edx, BYTE PTR status$[rsp]
	mov	cx, 96					; 00000060H
	call	?outportb@@YAXGE@Z			; outportb

; 253  : 
; 254  : 	mouse_write (0xF6);

	mov	cl, 246					; 000000f6H
	call	?mouse_write@@YAXE@Z			; mouse_write

; 255  : 	mouse_read ();

	call	?mouse_read@@YAEXZ			; mouse_read

; 256  : 
; 257  : 	mouse_write (0xF4);

	mov	cl, 244					; 000000f4H
	call	?mouse_write@@YAXE@Z			; mouse_write

; 258  : 	mouse_read ();

	call	?mouse_read@@YAEXZ			; mouse_read

; 259  : 
; 260  : 	interrupt_set (34, mouse_handler, 12);  //34

	mov	r8b, 12
	lea	rdx, OFFSET FLAT:?mouse_handler@@YAX_KPEAX@Z ; mouse_handler
	mov	ecx, 34					; 00000022H
	call	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z	; interrupt_set

; 261  : 	printf ("mouse interrupt setupped\n");

	lea	rcx, OFFSET FLAT:$SG6066
	call	?printf@@YAXPEBDZZ			; printf

; 262  : 	mouse_register_device ();

	call	?mouse_register_device@@YAXXZ		; mouse_register_device

; 263  : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_mouse@@YAXXZ ENDP				; initialize_mouse
_TEXT	ENDS
END
