; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?first_loop@@3PEAU_pri_loop_box_@@EA		; first_loop
PUBLIC	?last_loop@@3PEAU_pri_loop_box_@@EA		; last_loop
PUBLIC	?_pri_loop_root_created_@@3_NA			; _pri_loop_root_created_
_BSS	SEGMENT
?first_loop@@3PEAU_pri_loop_box_@@EA DQ 01H DUP (?)	; first_loop
?last_loop@@3PEAU_pri_loop_box_@@EA DQ 01H DUP (?)	; last_loop
?_pri_loop_root_created_@@3_NA DB 01H DUP (?)		; _pri_loop_root_created_
_BSS	ENDS
CONST	SEGMENT
$SG3696	DB	'pri_loop', 00H
	ORG $+7
$SG3697	DB	'/dev/pri_loop', 00H
CONST	ENDS
PUBLIC	?pri_loop_init@@YAXXZ				; pri_loop_init
PUBLIC	?pri_put_message@@YAXPEAU_pri_event_@@@Z	; pri_put_message
PUBLIC	?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z	; pri_loop_destroy
PUBLIC	?pri_loop_destroy_by_id@@YAXG@Z			; pri_loop_destroy_by_id
PUBLIC	?pri_loop_advance@@YAXPEAU_pri_loop_box_@@@Z	; pri_loop_advance
PUBLIC	?pri_loop_retreat@@YAXPEAU_pri_loop_box_@@@Z	; pri_loop_retreat
PUBLIC	?pri_loop_empty@@YA_NPEAU_pri_loop_box_@@@Z	; pri_loop_empty
PUBLIC	?pri_loop_full@@YA_NPEAU_pri_loop_box_@@@Z	; pri_loop_full
PUBLIC	?pri_loop_create@@YAX_N@Z			; pri_loop_create
PUBLIC	?pri_get_message@@YAHPEAU_pri_event_@@_N@Z	; pri_get_message
PUBLIC	?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z	; pri_loop_ioquery
EXTRN	strcpy:PROC
EXTRN	memset:PROC
EXTRN	memcpy:PROC
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuPmmngrFree:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	x64_cli:PROC
EXTRN	malloc:PROC
EXTRN	free:PROC
EXTRN	vfs_mount:PROC
EXTRN	unblock_thread:PROC
EXTRN	get_current_thread:PROC
EXTRN	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z:PROC ; thread_iterate_ready_list
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
EXTRN	__ImageBase:BYTE
pdata	SEGMENT
$pdata$?pri_loop_init@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+202
	DD	imagerel $unwind$?pri_loop_init@@YAXXZ
$pdata$?pri_put_message@@YAXPEAU_pri_event_@@@Z DD imagerel $LN10
	DD	imagerel $LN10+233
	DD	imagerel $unwind$?pri_put_message@@YAXPEAU_pri_event_@@@Z
$pdata$?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+170
	DD	imagerel $unwind$?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z
$pdata$?pri_loop_destroy_by_id@@YAXG@Z DD imagerel $LN7
	DD	imagerel $LN7+82
	DD	imagerel $unwind$?pri_loop_destroy_by_id@@YAXG@Z
$pdata$?pri_loop_advance@@YAXPEAU_pri_loop_box_@@@Z DD imagerel $LN6
	DD	imagerel $LN6+134
	DD	imagerel $unwind$?pri_loop_advance@@YAXPEAU_pri_loop_box_@@@Z
$pdata$?pri_loop_empty@@YA_NPEAU_pri_loop_box_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+65
	DD	imagerel $unwind$?pri_loop_empty@@YA_NPEAU_pri_loop_box_@@@Z
$pdata$?pri_loop_create@@YAX_N@Z DD imagerel $LN7
	DD	imagerel $LN7+287
	DD	imagerel $unwind$?pri_loop_create@@YAX_N@Z
$pdata$?pri_get_message@@YAHPEAU_pri_event_@@_N@Z DD imagerel $LN10
	DD	imagerel $LN10+257
	DD	imagerel $unwind$?pri_get_message@@YAHPEAU_pri_event_@@_N@Z
$pdata$?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN16
	DD	imagerel $LN16+352
	DD	imagerel $unwind$?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?pri_loop_init@@YAXXZ DD 010401H
	DD	06204H
$unwind$?pri_put_message@@YAXPEAU_pri_event_@@@Z DD 010901H
	DD	08209H
$unwind$?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z DD 010901H
	DD	04209H
$unwind$?pri_loop_destroy_by_id@@YAXG@Z DD 010901H
	DD	06209H
$unwind$?pri_loop_advance@@YAXPEAU_pri_loop_box_@@@Z DD 010901H
	DD	02209H
$unwind$?pri_loop_empty@@YA_NPEAU_pri_loop_box_@@@Z DD 010901H
	DD	02209H
$unwind$?pri_loop_create@@YAX_N@Z DD 010801H
	DD	06208H
$unwind$?pri_get_message@@YAHPEAU_pri_event_@@_N@Z DD 010d01H
	DD	0620dH
$unwind$?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD 021501H
	DD	0350115H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
tv64 = 32
ret_code$ = 36
box$1 = 40
tv70 = 48
event$2 = 56
e$3 = 64
e$4 = 240
file$ = 432
code$ = 440
arg$ = 448
?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z PROC	; pri_loop_ioquery

; 220  : int pri_loop_ioquery (vfs_node_t *file, int code, void *arg) {

$LN16:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 424				; 000001a8H

; 221  : 	x64_cli();

	call	x64_cli

; 222  : 	int ret_code = 1;

	mov	DWORD PTR ret_code$[rsp], 1

; 223  : 	switch (code) {

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv64[rsp], eax
	mov	eax, DWORD PTR tv64[rsp]
	sub	eax, 401				; 00000191H
	mov	DWORD PTR tv64[rsp], eax
	cmp	DWORD PTR tv64[rsp], 5
	ja	$LN11@pri_loop_i
	movsxd	rax, DWORD PTR tv64[rsp]
	lea	rcx, OFFSET FLAT:__ImageBase
	mov	eax, DWORD PTR $LN15@pri_loop_i[rcx+rax*4]
	add	rax, rcx
	jmp	rax
$LN10@pri_loop_i:

; 224  : 	case PRI_LOOP_CREATE: {
; 225  : 		pri_loop_create(false);

	xor	ecx, ecx
	call	?pri_loop_create@@YAX_N@Z		; pri_loop_create

; 226  : 		break;

	jmp	$LN11@pri_loop_i
$LN9@pri_loop_i:

; 227  : 	}
; 228  : 	case PRI_LOOP_CREATE_ROOT: {
; 229  : 		pri_loop_create(true);

	mov	cl, 1
	call	?pri_loop_create@@YAX_N@Z		; pri_loop_create

; 230  : 		break;

	jmp	$LN11@pri_loop_i
$LN8@pri_loop_i:

; 231  : 	}
; 232  : 	case PRI_LOOP_DESTROY: {
; 233  : 		pri_loop_box_t *box;
; 234  : 		for (box = first_loop; box != NULL; box = box->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR box$1[rsp], rax
	jmp	SHORT $LN7@pri_loop_i
$LN6@pri_loop_i:
	mov	rax, QWORD PTR box$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR box$1[rsp], rax
$LN7@pri_loop_i:
	cmp	QWORD PTR box$1[rsp], 0
	je	SHORT $LN5@pri_loop_i

; 235  : 			if (box->owner_id == get_current_thread()->id) {

	mov	rax, QWORD PTR box$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	mov	DWORD PTR tv70[rsp], eax
	call	get_current_thread
	movzx	eax, WORD PTR [rax+238]
	mov	ecx, DWORD PTR tv70[rsp]
	cmp	ecx, eax
	jne	SHORT $LN4@pri_loop_i

; 236  : 				pri_loop_destroy(box);

	mov	rcx, QWORD PTR box$1[rsp]
	call	?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z ; pri_loop_destroy

; 237  : 				break;

	jmp	SHORT $LN5@pri_loop_i
$LN4@pri_loop_i:

; 238  : 			}
; 239  : 		}

	jmp	SHORT $LN6@pri_loop_i
$LN5@pri_loop_i:

; 240  : 		break;

	jmp	SHORT $LN11@pri_loop_i
$LN3@pri_loop_i:

; 241  : 	}
; 242  : 	case PRI_LOOP_PUT_EVENT: {
; 243  : 		pri_event_t *event = (pri_event_t*)arg;

	mov	rax, QWORD PTR arg$[rsp]
	mov	QWORD PTR event$2[rsp], rax

; 244  : 		pri_put_message(event);

	mov	rcx, QWORD PTR event$2[rsp]
	call	?pri_put_message@@YAXPEAU_pri_event_@@@Z ; pri_put_message

; 245  : 		break;

	jmp	SHORT $LN11@pri_loop_i
$LN2@pri_loop_i:

; 246  : 	}
; 247  : 
; 248  : 	case PRI_LOOP_GET_EVENT: {
; 249  : 		pri_event_t e;
; 250  : 		ret_code = pri_get_message(&e, false);

	xor	edx, edx
	lea	rcx, QWORD PTR e$3[rsp]
	call	?pri_get_message@@YAHPEAU_pri_event_@@_N@Z ; pri_get_message
	mov	DWORD PTR ret_code$[rsp], eax

; 251  : 		memcpy (arg,&e,sizeof(pri_event_t));

	mov	r8d, 176				; 000000b0H
	lea	rdx, QWORD PTR e$3[rsp]
	mov	rcx, QWORD PTR arg$[rsp]
	call	memcpy

; 252  : 		break;

	jmp	SHORT $LN11@pri_loop_i
$LN1@pri_loop_i:

; 253  : 	}
; 254  : 
; 255  : 	case PRI_LOOP_GET_EVENT_ROOT: {
; 256  : 		pri_event_t e;
; 257  : 		ret_code = pri_get_message(&e, true);

	mov	dl, 1
	lea	rcx, QWORD PTR e$4[rsp]
	call	?pri_get_message@@YAHPEAU_pri_event_@@_N@Z ; pri_get_message
	mov	DWORD PTR ret_code$[rsp], eax

; 258  : 		memcpy (arg,&e,sizeof(pri_event_t));

	mov	r8d, 176				; 000000b0H
	lea	rdx, QWORD PTR e$4[rsp]
	mov	rcx, QWORD PTR arg$[rsp]
	call	memcpy
$LN11@pri_loop_i:

; 259  : 		break;
; 260  : 	}
; 261  : 	}
; 262  : 
; 263  : 	return ret_code;

	mov	eax, DWORD PTR ret_code$[rsp]

; 264  : }

	add	rsp, 424				; 000001a8H
	ret	0
	npad	1
$LN15@pri_loop_i:
	DD	$LN10@pri_loop_i
	DD	$LN8@pri_loop_i
	DD	$LN3@pri_loop_i
	DD	$LN2@pri_loop_i
	DD	$LN9@pri_loop_i
	DD	$LN1@pri_loop_i
?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP	; pri_loop_ioquery
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
owner_id$ = 32
ret_code$ = 36
loop$1 = 40
event$ = 64
root$ = 72
?pri_get_message@@YAHPEAU_pri_event_@@_N@Z PROC		; pri_get_message

; 188  : int pri_get_message (pri_event_t *event, bool root) {

$LN10:
	mov	BYTE PTR [rsp+16], dl
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 189  : 	x64_cli();

	call	x64_cli

; 190  : 	int ret_code = PRI_LOOP_NO_MSG;

	mov	DWORD PTR ret_code$[rsp], -1

; 191  : 
; 192  : 	uint16_t owner_id = 0;

	xor	eax, eax
	mov	WORD PTR owner_id$[rsp], ax

; 193  : 	if(root)

	movzx	eax, BYTE PTR root$[rsp]
	test	eax, eax
	je	SHORT $LN7@pri_get_me

; 194  : 		owner_id = PRI_LOOP_ROOT_ID;

	mov	eax, 1
	mov	WORD PTR owner_id$[rsp], ax

; 195  : 	else

	jmp	SHORT $LN6@pri_get_me
$LN7@pri_get_me:

; 196  : 		owner_id = get_current_thread()->id;

	call	get_current_thread
	movzx	eax, WORD PTR [rax+238]
	mov	WORD PTR owner_id$[rsp], ax
$LN6@pri_get_me:

; 197  : 
; 198  : 	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR loop$1[rsp], rax
	jmp	SHORT $LN5@pri_get_me
$LN4@pri_get_me:
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR loop$1[rsp], rax
$LN5@pri_get_me:
	cmp	QWORD PTR loop$1[rsp], 0
	je	$LN3@pri_get_me

; 199  : 		if (loop->owner_id == owner_id) {

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR owner_id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN2@pri_get_me

; 200  : 
; 201  : 			if (!pri_loop_empty(loop)) {

	mov	rcx, QWORD PTR loop$1[rsp]
	call	?pri_loop_empty@@YA_NPEAU_pri_loop_box_@@@Z ; pri_loop_empty
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN1@pri_get_me

; 202  : 				memcpy (event,&loop->address[loop->tail_idx], sizeof(pri_event_t));

	mov	rax, QWORD PTR loop$1[rsp]
	movsxd	rax, DWORD PTR [rax+16]
	mov	rcx, QWORD PTR loop$1[rsp]
	mov	rcx, QWORD PTR [rcx]
	lea	rax, QWORD PTR [rcx+rax*8]
	mov	r8d, 176				; 000000b0H
	mov	rdx, rax
	mov	rcx, QWORD PTR event$[rsp]
	call	memcpy

; 203  : 				memset (&loop->address[loop->tail_idx], 0, sizeof(pri_event_t));

	mov	rax, QWORD PTR loop$1[rsp]
	movsxd	rax, DWORD PTR [rax+16]
	mov	rcx, QWORD PTR loop$1[rsp]
	mov	rcx, QWORD PTR [rcx]
	lea	rax, QWORD PTR [rcx+rax*8]
	mov	r8d, 176				; 000000b0H
	xor	edx, edx
	mov	rcx, rax
	call	memset

; 204  : 				pri_loop_retreat(loop);

	mov	rcx, QWORD PTR loop$1[rsp]
	call	?pri_loop_retreat@@YAXPEAU_pri_loop_box_@@@Z ; pri_loop_retreat

; 205  : 				ret_code = 1;

	mov	DWORD PTR ret_code$[rsp], 1
$LN1@pri_get_me:

; 206  : 			}
; 207  : 			break;

	jmp	SHORT $LN3@pri_get_me
$LN2@pri_get_me:

; 208  : 		}
; 209  : 	}

	jmp	$LN4@pri_get_me
$LN3@pri_get_me:

; 210  : 
; 211  : 	return ret_code;

	mov	eax, DWORD PTR ret_code$[rsp]

; 212  : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_get_message@@YAHPEAU_pri_event_@@_N@Z ENDP		; pri_get_message
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
loop$ = 32
root$ = 64
?pri_loop_create@@YAX_N@Z PROC				; pri_loop_create

; 79   : void pri_loop_create (bool root) {

$LN7:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 80   : 	pri_loop_box_t *loop = (pri_loop_box_t*)malloc(sizeof(pri_loop_box_t));

	mov	ecx, 40					; 00000028H
	call	malloc
	mov	QWORD PTR loop$[rsp], rax

; 81   : 	loop->address = (uint64_t*)p2v((size_t)AuPmmngrAlloc());//malloc(sizeof(pri_event_t));

	call	AuPmmngrAlloc
	mov	rcx, rax
	call	p2v
	mov	rcx, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rcx], rax

; 82   : 	memset(loop->address,0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rax, QWORD PTR loop$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	memset

; 83   : 
; 84   : 	if (root && _pri_loop_root_created_ == false){

	movzx	eax, BYTE PTR root$[rsp]
	test	eax, eax
	je	SHORT $LN4@pri_loop_c
	movzx	eax, BYTE PTR ?_pri_loop_root_created_@@3_NA ; _pri_loop_root_created_
	test	eax, eax
	jne	SHORT $LN4@pri_loop_c

; 85   : 		loop->owner_id = PRI_LOOP_ROOT_ID; 

	mov	eax, 1
	mov	rcx, QWORD PTR loop$[rsp]
	mov	WORD PTR [rcx+8], ax

; 86   : 		_pri_loop_root_created_ = true;

	mov	BYTE PTR ?_pri_loop_root_created_@@3_NA, 1 ; _pri_loop_root_created_

; 87   : 	}else {

	jmp	SHORT $LN3@pri_loop_c
$LN4@pri_loop_c:

; 88   : 		loop->owner_id = get_current_thread()->id;

	call	get_current_thread
	mov	rcx, QWORD PTR loop$[rsp]
	movzx	eax, WORD PTR [rax+238]
	mov	WORD PTR [rcx+8], ax
$LN3@pri_loop_c:

; 89   : 	}
; 90   : 
; 91   : 	loop->next = NULL;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rax+24], 0

; 92   : 	loop->prev = NULL;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rax+32], 0

; 93   : 	loop->head_idx = 0;

	mov	rax, QWORD PTR loop$[rsp]
	mov	DWORD PTR [rax+12], 0

; 94   : 	loop->tail_idx = 0;

	mov	rax, QWORD PTR loop$[rsp]
	mov	DWORD PTR [rax+16], 0

; 95   : 	loop->full = false;

	mov	rax, QWORD PTR loop$[rsp]
	mov	BYTE PTR [rax+20], 0

; 96   : 
; 97   : 	/* speed of consuming/producing messages depends
; 98   : 	 * on size of the loop box, less size =
; 99   : 	 * low latency message consum/produce */
; 100  : 	loop->size = 4096 / sizeof(pri_event_t);

	mov	eax, 23
	mov	rcx, QWORD PTR loop$[rsp]
	mov	WORD PTR [rcx+22], ax

; 101  : 
; 102  : 	if (first_loop == NULL)  {

	cmp	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, 0 ; first_loop
	jne	SHORT $LN2@pri_loop_c

; 103  : 		first_loop = loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, rax ; first_loop

; 104  : 		last_loop = loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA, rax ; last_loop

; 105  : 	} else {

	jmp	SHORT $LN1@pri_loop_c
$LN2@pri_loop_c:

; 106  : 		last_loop->next = loop;

	mov	rax, QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA ; last_loop
	mov	rcx, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rax+24], rcx

; 107  : 		loop->prev = last_loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	rcx, QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA ; last_loop
	mov	QWORD PTR [rax+32], rcx

; 108  : 		last_loop = loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA, rax ; last_loop
$LN1@pri_loop_c:

; 109  : 	}
; 110  : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_loop_create@@YAX_N@Z ENDP				; pri_loop_create
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
loop$ = 8
?pri_loop_full@@YA_NPEAU_pri_loop_box_@@@Z PROC		; pri_loop_full

; 72   : {

	mov	QWORD PTR [rsp+8], rcx

; 73   : 	return loop->full;

	mov	rax, QWORD PTR loop$[rsp]
	movzx	eax, BYTE PTR [rax+20]

; 74   : }

	ret	0
?pri_loop_full@@YA_NPEAU_pri_loop_box_@@@Z ENDP		; pri_loop_full
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
tv70 = 0
loop$ = 32
?pri_loop_empty@@YA_NPEAU_pri_loop_box_@@@Z PROC	; pri_loop_empty

; 67   : bool pri_loop_empty (pri_loop_box_t* loop) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 68   : 	return (!loop->full && (loop->head_idx == loop->tail_idx));

	mov	rax, QWORD PTR loop$[rsp]
	movzx	eax, BYTE PTR [rax+20]
	test	eax, eax
	jne	SHORT $LN3@pri_loop_e
	mov	rax, QWORD PTR loop$[rsp]
	mov	rcx, QWORD PTR loop$[rsp]
	mov	ecx, DWORD PTR [rcx+16]
	cmp	DWORD PTR [rax+12], ecx
	jne	SHORT $LN3@pri_loop_e
	mov	DWORD PTR tv70[rsp], 1
	jmp	SHORT $LN4@pri_loop_e
$LN3@pri_loop_e:
	mov	DWORD PTR tv70[rsp], 0
$LN4@pri_loop_e:
	movzx	eax, BYTE PTR tv70[rsp]

; 69   : }

	add	rsp, 24
	ret	0
?pri_loop_empty@@YA_NPEAU_pri_loop_box_@@@Z ENDP	; pri_loop_empty
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
loop$ = 8
?pri_loop_retreat@@YAXPEAU_pri_loop_box_@@@Z PROC	; pri_loop_retreat

; 62   : void pri_loop_retreat (pri_loop_box_t* loop) {

	mov	QWORD PTR [rsp+8], rcx

; 63   : 	loop->full = false;

	mov	rax, QWORD PTR loop$[rsp]
	mov	BYTE PTR [rax+20], 0

; 64   : 	loop->tail_idx = (loop->tail_idx + 1) % loop->size;

	mov	rax, QWORD PTR loop$[rsp]
	mov	eax, DWORD PTR [rax+16]
	inc	eax
	mov	rcx, QWORD PTR loop$[rsp]
	movzx	ecx, WORD PTR [rcx+22]
	cdq
	idiv	ecx
	mov	eax, edx
	mov	rcx, QWORD PTR loop$[rsp]
	mov	DWORD PTR [rcx+16], eax

; 65   : }

	ret	0
?pri_loop_retreat@@YAXPEAU_pri_loop_box_@@@Z ENDP	; pri_loop_retreat
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
tv83 = 0
loop$ = 32
?pri_loop_advance@@YAXPEAU_pri_loop_box_@@@Z PROC	; pri_loop_advance

; 50   : void pri_loop_advance (pri_loop_box_t* loop) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 51   : 
; 52   : 	if (loop->full) {

	mov	rax, QWORD PTR loop$[rsp]
	movzx	eax, BYTE PTR [rax+20]
	test	eax, eax
	je	SHORT $LN1@pri_loop_a

; 53   : 		loop->tail_idx = (loop->tail_idx + 1) % loop->size;

	mov	rax, QWORD PTR loop$[rsp]
	mov	eax, DWORD PTR [rax+16]
	inc	eax
	mov	rcx, QWORD PTR loop$[rsp]
	movzx	ecx, WORD PTR [rcx+22]
	cdq
	idiv	ecx
	mov	eax, edx
	mov	rcx, QWORD PTR loop$[rsp]
	mov	DWORD PTR [rcx+16], eax
$LN1@pri_loop_a:

; 54   : 	}
; 55   : 
; 56   : 	loop->head_idx = (loop->head_idx + 1) & loop->size;

	mov	rax, QWORD PTR loop$[rsp]
	mov	eax, DWORD PTR [rax+12]
	inc	eax
	mov	rcx, QWORD PTR loop$[rsp]
	movzx	ecx, WORD PTR [rcx+22]
	and	eax, ecx
	mov	rcx, QWORD PTR loop$[rsp]
	mov	DWORD PTR [rcx+12], eax

; 57   : 
; 58   : 	loop->full = (loop->head_idx == loop->tail_idx);

	mov	rax, QWORD PTR loop$[rsp]
	mov	rcx, QWORD PTR loop$[rsp]
	mov	ecx, DWORD PTR [rcx+16]
	cmp	DWORD PTR [rax+12], ecx
	jne	SHORT $LN4@pri_loop_a
	mov	DWORD PTR tv83[rsp], 1
	jmp	SHORT $LN5@pri_loop_a
$LN4@pri_loop_a:
	mov	DWORD PTR tv83[rsp], 0
$LN5@pri_loop_a:
	mov	rax, QWORD PTR loop$[rsp]
	movzx	ecx, BYTE PTR tv83[rsp]
	mov	BYTE PTR [rax+20], cl

; 59   : }

	add	rsp, 24
	ret	0
?pri_loop_advance@@YAXPEAU_pri_loop_box_@@@Z ENDP	; pri_loop_advance
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
loop$1 = 32
id$ = 64
?pri_loop_destroy_by_id@@YAXG@Z PROC			; pri_loop_destroy_by_id

; 140  : void pri_loop_destroy_by_id (uint16_t id) {

$LN7:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 56					; 00000038H

; 141  : 	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR loop$1[rsp], rax
	jmp	SHORT $LN4@pri_loop_d
$LN3@pri_loop_d:
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR loop$1[rsp], rax
$LN4@pri_loop_d:
	cmp	QWORD PTR loop$1[rsp], 0
	je	SHORT $LN2@pri_loop_d

; 142  : 		if (loop->owner_id == id) {

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN1@pri_loop_d

; 143  : 			pri_loop_destroy (loop);

	mov	rcx, QWORD PTR loop$1[rsp]
	call	?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z ; pri_loop_destroy

; 144  : 			break;

	jmp	SHORT $LN2@pri_loop_d
$LN1@pri_loop_d:

; 145  : 		}
; 146  : 	}

	jmp	SHORT $LN3@pri_loop_d
$LN2@pri_loop_d:

; 147  : 
; 148  : 	return;
; 149  : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_loop_destroy_by_id@@YAXG@Z ENDP			; pri_loop_destroy_by_id
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
box$ = 48
?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z PROC	; pri_loop_destroy

; 116  : void pri_loop_destroy (pri_loop_box_t *box) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 117  : 	if (first_loop == NULL)

	cmp	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, 0 ; first_loop
	jne	SHORT $LN5@pri_loop_d

; 118  : 		return;

	jmp	$LN6@pri_loop_d
$LN5@pri_loop_d:

; 119  : 
; 120  : 	if (box == first_loop) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	cmp	QWORD PTR box$[rsp], rax
	jne	SHORT $LN4@pri_loop_d

; 121  : 		first_loop = first_loop->next;

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, rax ; first_loop

; 122  : 	} else {

	jmp	SHORT $LN3@pri_loop_d
$LN4@pri_loop_d:

; 123  : 		box->prev->next = box->next;

	mov	rax, QWORD PTR box$[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	rcx, QWORD PTR box$[rsp]
	mov	rcx, QWORD PTR [rcx+24]
	mov	QWORD PTR [rax+24], rcx
$LN3@pri_loop_d:

; 124  : 	}
; 125  : 
; 126  : 	if (box == last_loop) {

	mov	rax, QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA ; last_loop
	cmp	QWORD PTR box$[rsp], rax
	jne	SHORT $LN2@pri_loop_d

; 127  : 		last_loop = box->prev;

	mov	rax, QWORD PTR box$[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA, rax ; last_loop

; 128  : 	} else {

	jmp	SHORT $LN1@pri_loop_d
$LN2@pri_loop_d:

; 129  : 		box->next->prev = box->prev;

	mov	rax, QWORD PTR box$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR box$[rsp]
	mov	rcx, QWORD PTR [rcx+32]
	mov	QWORD PTR [rax+32], rcx
$LN1@pri_loop_d:

; 130  : 	}
; 131  : 
; 132  : 	AuPmmngrFree((void*)v2p((size_t)box->address));

	mov	rax, QWORD PTR box$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	v2p
	mov	rcx, rax
	call	AuPmmngrFree

; 133  : 	free(box);

	mov	rcx, QWORD PTR box$[rsp]
	call	free
$LN6@pri_loop_d:

; 134  : }

	add	rsp, 40					; 00000028H
	ret	0
?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z ENDP	; pri_loop_destroy
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
owner_id$ = 32
loop$1 = 40
thread$ = 48
event$ = 80
?pri_put_message@@YAXPEAU_pri_event_@@@Z PROC		; pri_put_message

; 155  : void pri_put_message (pri_event_t *event) {

$LN10:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 156  : 	x64_cli();

	call	x64_cli

; 157  : 
; 158  : 	uint16_t owner_id = event->to_id;

	mov	rax, QWORD PTR event$[rsp]
	movzx	eax, BYTE PTR [rax+1]
	mov	WORD PTR owner_id$[rsp], ax

; 159  : 	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR loop$1[rsp], rax
	jmp	SHORT $LN7@pri_put_me
$LN6@pri_put_me:
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR loop$1[rsp], rax
$LN7@pri_put_me:
	cmp	QWORD PTR loop$1[rsp], 0
	je	SHORT $LN5@pri_put_me

; 160  : 		if (loop->owner_id == owner_id) {

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR owner_id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN4@pri_put_me

; 161  : 
; 162  : 			if (!pri_loop_full(loop)) {

	mov	rcx, QWORD PTR loop$1[rsp]
	call	?pri_loop_full@@YA_NPEAU_pri_loop_box_@@@Z ; pri_loop_full
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN3@pri_put_me

; 163  : 				memcpy (&loop->address[loop->head_idx], event, sizeof(pri_event_t));

	mov	rax, QWORD PTR loop$1[rsp]
	movsxd	rax, DWORD PTR [rax+12]
	mov	rcx, QWORD PTR loop$1[rsp]
	mov	rcx, QWORD PTR [rcx]
	lea	rax, QWORD PTR [rcx+rax*8]
	mov	r8d, 176				; 000000b0H
	mov	rdx, QWORD PTR event$[rsp]
	mov	rcx, rax
	call	memcpy

; 164  : 				pri_loop_advance(loop);

	mov	rcx, QWORD PTR loop$1[rsp]
	call	?pri_loop_advance@@YAXPEAU_pri_loop_box_@@@Z ; pri_loop_advance
$LN3@pri_put_me:

; 165  : 			}
; 166  : 			
; 167  : 			break;

	jmp	SHORT $LN5@pri_put_me
$LN4@pri_put_me:

; 168  : 		}
; 169  : 	}

	jmp	SHORT $LN6@pri_put_me
$LN5@pri_put_me:

; 170  : 
; 171  : 	//! check if the destination thread is blocked or not
; 172  : 	//! if blocked, wake it up, cause new message is pending
; 173  : 	thread_t *thread = thread_iterate_ready_list(owner_id);	

	movzx	ecx, WORD PTR owner_id$[rsp]
	call	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ; thread_iterate_ready_list
	mov	QWORD PTR thread$[rsp], rax

; 174  : 	if (thread == NULL) 

	cmp	QWORD PTR thread$[rsp], 0
	jne	SHORT $LN2@pri_put_me

; 175  : 		thread = thread_iterate_block_list(owner_id);

	movzx	eax, WORD PTR owner_id$[rsp]
	mov	ecx, eax
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR thread$[rsp], rax
$LN2@pri_put_me:

; 176  : 	if (thread != NULL && thread->state == THREAD_STATE_BLOCKED) {

	cmp	QWORD PTR thread$[rsp], 0
	je	SHORT $LN1@pri_put_me
	mov	rax, QWORD PTR thread$[rsp]
	movzx	eax, BYTE PTR [rax+237]
	cmp	eax, 3
	jne	SHORT $LN1@pri_put_me

; 177  : 		unblock_thread(thread);

	mov	rcx, QWORD PTR thread$[rsp]
	call	unblock_thread
$LN1@pri_put_me:
$ret$11:

; 178  : 	}
; 179  : ret:
; 180  : 
; 181  : 	return;
; 182  : }

	add	rsp, 72					; 00000048H
	ret	0
?pri_put_message@@YAXPEAU_pri_event_@@@Z ENDP		; pri_put_message
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
node$ = 32
?pri_loop_init@@YAXXZ PROC				; pri_loop_init

; 269  : void pri_loop_init () {

$LN3:
	sub	rsp, 56					; 00000038H

; 270  : 	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 112				; 00000070H
	call	malloc
	mov	QWORD PTR node$[rsp], rax

; 271  : 	strcpy (node->filename, "pri_loop");

	mov	rax, QWORD PTR node$[rsp]
	lea	rdx, OFFSET FLAT:$SG3696
	mov	rcx, rax
	call	strcpy

; 272  : 	node->size = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+32], 0

; 273  : 	node->eof = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+36], 0

; 274  : 	node->pos = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+40], 0

; 275  : 	node->current = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+44], 0

; 276  : 	node->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+48], 12

; 277  : 	node->status = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+49], 0

; 278  : 	node->open = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+64], 0

; 279  : 	node->read = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+72], 0

; 280  : 	node->write = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+80], 0

; 281  : 	node->read_blk = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+96], 0

; 282  : 	node->ioquery = pri_loop_ioquery;

	mov	rax, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z ; pri_loop_ioquery
	mov	QWORD PTR [rax+104], rcx

; 283  : 	vfs_mount ("/dev/pri_loop", node, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:$SG3697
	call	vfs_mount

; 284  : 	_pri_loop_root_created_ = false;

	mov	BYTE PTR ?_pri_loop_root_created_@@3_NA, 0 ; _pri_loop_root_created_

; 285  : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_loop_init@@YAXXZ ENDP				; pri_loop_init
_TEXT	ENDS
END
