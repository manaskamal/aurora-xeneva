; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?first_loop@@3PEAU_pri_loop_box_@@EA		; first_loop
PUBLIC	?last_loop@@3PEAU_pri_loop_box_@@EA		; last_loop
_BSS	SEGMENT
?first_loop@@3PEAU_pri_loop_box_@@EA DQ 01H DUP (?)	; first_loop
?last_loop@@3PEAU_pri_loop_box_@@EA DQ 01H DUP (?)	; last_loop
_BSS	ENDS
CONST	SEGMENT
$SG3619	DB	'pri_loop', 00H
	ORG $+7
$SG3620	DB	'/dev/pri_loop', 00H
CONST	ENDS
PUBLIC	?pri_loop_init@@YAXXZ				; pri_loop_init
PUBLIC	?pri_put_message@@YAXPEAU_pri_event_@@@Z	; pri_put_message
PUBLIC	?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z	; pri_loop_destroy
PUBLIC	?pri_loop_destroy_by_id@@YAXG@Z			; pri_loop_destroy_by_id
PUBLIC	?pri_loop_create@@YAXXZ				; pri_loop_create
PUBLIC	?pri_get_message@@YAXPEAU_pri_event_@@@Z	; pri_get_message
PUBLIC	?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z	; pri_loop_ioquery
EXTRN	strcpy:PROC
EXTRN	memset:PROC
EXTRN	memcpy:PROC
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuPmmngrFree:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	malloc:PROC
EXTRN	free:PROC
EXTRN	vfs_mount:PROC
EXTRN	?unblock_thread@@YAXPEAU_thread_@@@Z:PROC	; unblock_thread
EXTRN	get_current_thread:PROC
EXTRN	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z:PROC ; thread_iterate_ready_list
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
pdata	SEGMENT
$pdata$?pri_loop_init@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+195
	DD	imagerel $unwind$?pri_loop_init@@YAXXZ
$pdata$?pri_put_message@@YAXPEAU_pri_event_@@@Z DD imagerel $LN10
	DD	imagerel $LN10+245
	DD	imagerel $unwind$?pri_put_message@@YAXPEAU_pri_event_@@@Z
$pdata$?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+170
	DD	imagerel $unwind$?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z
$pdata$?pri_loop_destroy_by_id@@YAXG@Z DD imagerel $LN7
	DD	imagerel $LN7+82
	DD	imagerel $unwind$?pri_loop_destroy_by_id@@YAXG@Z
$pdata$?pri_loop_create@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+213
	DD	imagerel $unwind$?pri_loop_create@@YAXXZ
$pdata$?pri_get_message@@YAXPEAU_pri_event_@@@Z DD imagerel $LN9
	DD	imagerel $LN9+228
	DD	imagerel $unwind$?pri_get_message@@YAXPEAU_pri_event_@@@Z
$pdata$?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN13
	DD	imagerel $LN13+244
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
$unwind$?pri_loop_create@@YAXXZ DD 010401H
	DD	06204H
$unwind$?pri_get_message@@YAXPEAU_pri_event_@@@Z DD 010901H
	DD	06209H
$unwind$?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD 021501H
	DD	01f0115H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
tv64 = 32
box$1 = 40
tv68 = 48
event$2 = 56
e$3 = 64
file$ = 256
code$ = 264
arg$ = 272
?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z PROC	; pri_loop_ioquery

; 170  : int pri_loop_ioquery (vfs_node_t *file, int code, void *arg) {

$LN13:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 248				; 000000f8H

; 171  : 	switch (code) {

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv64[rsp], eax
	cmp	DWORD PTR tv64[rsp], 401		; 00000191H
	je	SHORT $LN8@pri_loop_i
	cmp	DWORD PTR tv64[rsp], 402		; 00000192H
	je	SHORT $LN7@pri_loop_i
	cmp	DWORD PTR tv64[rsp], 403		; 00000193H
	je	SHORT $LN2@pri_loop_i
	cmp	DWORD PTR tv64[rsp], 404		; 00000194H
	je	SHORT $LN1@pri_loop_i
	jmp	$LN9@pri_loop_i
$LN8@pri_loop_i:

; 172  : 	case PRI_LOOP_CREATE: {
; 173  : 		pri_loop_create();

	call	?pri_loop_create@@YAXXZ			; pri_loop_create

; 174  : 		break;

	jmp	$LN9@pri_loop_i
$LN7@pri_loop_i:

; 175  : 	}
; 176  : 	case PRI_LOOP_DESTROY: {
; 177  : 		pri_loop_box_t *box;
; 178  : 		for (box = first_loop; box != NULL; box = box->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR box$1[rsp], rax
	jmp	SHORT $LN6@pri_loop_i
$LN5@pri_loop_i:
	mov	rax, QWORD PTR box$1[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR box$1[rsp], rax
$LN6@pri_loop_i:
	cmp	QWORD PTR box$1[rsp], 0
	je	SHORT $LN4@pri_loop_i

; 179  : 			if (box->owner_id == get_current_thread()->id) {

	mov	rax, QWORD PTR box$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	mov	DWORD PTR tv68[rsp], eax
	call	get_current_thread
	movzx	eax, WORD PTR [rax+242]
	mov	ecx, DWORD PTR tv68[rsp]
	cmp	ecx, eax
	jne	SHORT $LN3@pri_loop_i

; 180  : 				pri_loop_destroy(box);

	mov	rcx, QWORD PTR box$1[rsp]
	call	?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z ; pri_loop_destroy

; 181  : 				break;

	jmp	SHORT $LN4@pri_loop_i
$LN3@pri_loop_i:

; 182  : 			}
; 183  : 		}

	jmp	SHORT $LN5@pri_loop_i
$LN4@pri_loop_i:

; 184  : 		break;

	jmp	SHORT $LN9@pri_loop_i
$LN2@pri_loop_i:

; 185  : 	}
; 186  : 	case PRI_LOOP_PUT_EVENT: {
; 187  : 		pri_event_t *event = (pri_event_t*)arg;

	mov	rax, QWORD PTR arg$[rsp]
	mov	QWORD PTR event$2[rsp], rax

; 188  : 		pri_put_message(event);

	mov	rcx, QWORD PTR event$2[rsp]
	call	?pri_put_message@@YAXPEAU_pri_event_@@@Z ; pri_put_message

; 189  : 		break;

	jmp	SHORT $LN9@pri_loop_i
$LN1@pri_loop_i:

; 190  : 	}
; 191  : 
; 192  : 	case PRI_LOOP_GET_EVENT: {
; 193  : 		pri_event_t e;
; 194  : 		pri_get_message(&e);

	lea	rcx, QWORD PTR e$3[rsp]
	call	?pri_get_message@@YAXPEAU_pri_event_@@@Z ; pri_get_message

; 195  : 		memcpy (arg,&e,sizeof(pri_event_t));

	mov	r8d, 176				; 000000b0H
	lea	rdx, QWORD PTR e$3[rsp]
	mov	rcx, QWORD PTR arg$[rsp]
	call	memcpy
$LN9@pri_loop_i:

; 196  : 		break;
; 197  : 	}
; 198  : 	}
; 199  : 
; 200  : 	return 1;

	mov	eax, 1

; 201  : }

	add	rsp, 248				; 000000f8H
	ret	0
?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP	; pri_loop_ioquery
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
owner_id$ = 32
loop$1 = 40
event$ = 64
?pri_get_message@@YAXPEAU_pri_event_@@@Z PROC		; pri_get_message

; 141  : void pri_get_message (pri_event_t *event) {

$LN9:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 142  : 	x64_cli ();

	call	x64_cli

; 143  : 
; 144  : 	uint16_t owner_id = get_current_thread()->id;

	call	get_current_thread
	movzx	eax, WORD PTR [rax+242]
	mov	WORD PTR owner_id$[rsp], ax

; 145  : 	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR loop$1[rsp], rax
	jmp	SHORT $LN6@pri_get_me
$LN5@pri_get_me:
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR loop$1[rsp], rax
$LN6@pri_get_me:
	cmp	QWORD PTR loop$1[rsp], 0
	je	$LN4@pri_get_me

; 146  : 		if (loop->owner_id == owner_id) {

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR owner_id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN3@pri_get_me

; 147  : 			if (loop->message_pending){

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, BYTE PTR [rax+10]
	test	eax, eax
	je	SHORT $LN2@pri_get_me

; 148  : 				memcpy (event,loop->address, sizeof(pri_event_t));

	mov	r8d, 176				; 000000b0H
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rdx, QWORD PTR [rax]
	mov	rcx, QWORD PTR event$[rsp]
	call	memcpy

; 149  : 				memset (loop->address, 0, sizeof(pri_event_t));

	mov	r8d, 176				; 000000b0H
	xor	edx, edx
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rcx, QWORD PTR [rax]
	call	memset

; 150  : 				loop->pending_msg_count--;

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+12]
	dec	ax
	mov	rcx, QWORD PTR loop$1[rsp]
	mov	WORD PTR [rcx+12], ax

; 151  : 				if (loop->pending_msg_count == 0) {

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+12]
	test	eax, eax
	jne	SHORT $LN1@pri_get_me

; 152  : 					loop->message_pending = false;

	mov	rax, QWORD PTR loop$1[rsp]
	mov	BYTE PTR [rax+10], 0
$LN1@pri_get_me:
$LN2@pri_get_me:

; 153  : 				}
; 154  : 			}
; 155  : 			memset (loop->address, 0, sizeof(pri_event_t));

	mov	r8d, 176				; 000000b0H
	xor	edx, edx
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rcx, QWORD PTR [rax]
	call	memset

; 156  : 			break;

	jmp	SHORT $LN4@pri_get_me
$LN3@pri_get_me:

; 157  : 		}
; 158  : 	}

	jmp	$LN5@pri_get_me
$LN4@pri_get_me:

; 159  : 
; 160  : 	x64_sti();

	call	x64_sti

; 161  : 	return;
; 162  : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_get_message@@YAXPEAU_pri_event_@@@Z ENDP		; pri_get_message
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
loop$ = 32
?pri_loop_create@@YAXXZ PROC				; pri_loop_create

; 45   : void pri_loop_create () {

$LN5:
	sub	rsp, 56					; 00000038H

; 46   : 	pri_loop_box_t *loop = (pri_loop_box_t*)malloc(sizeof(pri_loop_box_t));

	mov	ecx, 32					; 00000020H
	call	malloc
	mov	QWORD PTR loop$[rsp], rax

; 47   : 	loop->address = (void*)p2v((size_t)AuPmmngrAlloc());//malloc(sizeof(pri_event_t));

	call	AuPmmngrAlloc
	mov	rcx, rax
	call	p2v
	mov	rcx, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rcx], rax

; 48   : 	memset(loop->address,0, sizeof(pri_event_t));

	mov	r8d, 176				; 000000b0H
	xor	edx, edx
	mov	rax, QWORD PTR loop$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	memset

; 49   : 	loop->owner_id = get_current_thread()->id;

	call	get_current_thread
	mov	rcx, QWORD PTR loop$[rsp]
	movzx	eax, WORD PTR [rax+242]
	mov	WORD PTR [rcx+8], ax

; 50   : 	loop->pending_msg_count = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR loop$[rsp]
	mov	WORD PTR [rcx+12], ax

; 51   : 	loop->message_pending = 0;

	mov	rax, QWORD PTR loop$[rsp]
	mov	BYTE PTR [rax+10], 0

; 52   : 	loop->next = NULL;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rax+16], 0

; 53   : 	loop->prev = NULL;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rax+24], 0

; 54   : 
; 55   : 	if (first_loop == NULL)  {

	cmp	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, 0 ; first_loop
	jne	SHORT $LN2@pri_loop_c

; 56   : 		first_loop = loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, rax ; first_loop

; 57   : 		last_loop = loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA, rax ; last_loop

; 58   : 	} else {

	jmp	SHORT $LN1@pri_loop_c
$LN2@pri_loop_c:

; 59   : 		last_loop->next = loop;

	mov	rax, QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA ; last_loop
	mov	rcx, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rax+16], rcx

; 60   : 		loop->prev = last_loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	rcx, QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA ; last_loop
	mov	QWORD PTR [rax+24], rcx

; 61   : 		last_loop = loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA, rax ; last_loop
$LN1@pri_loop_c:

; 62   : 	}
; 63   : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_loop_create@@YAXXZ ENDP				; pri_loop_create
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
loop$1 = 32
id$ = 64
?pri_loop_destroy_by_id@@YAXG@Z PROC			; pri_loop_destroy_by_id

; 94   : void pri_loop_destroy_by_id (uint16_t id) {

$LN7:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 56					; 00000038H

; 95   : 	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR loop$1[rsp], rax
	jmp	SHORT $LN4@pri_loop_d
$LN3@pri_loop_d:
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR loop$1[rsp], rax
$LN4@pri_loop_d:
	cmp	QWORD PTR loop$1[rsp], 0
	je	SHORT $LN2@pri_loop_d

; 96   : 		if (loop->owner_id == id) {

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN1@pri_loop_d

; 97   : 			pri_loop_destroy (loop);

	mov	rcx, QWORD PTR loop$1[rsp]
	call	?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z ; pri_loop_destroy

; 98   : 			break;

	jmp	SHORT $LN2@pri_loop_d
$LN1@pri_loop_d:

; 99   : 		}
; 100  : 	}

	jmp	SHORT $LN3@pri_loop_d
$LN2@pri_loop_d:

; 101  : 
; 102  : 	return;
; 103  : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_loop_destroy_by_id@@YAXG@Z ENDP			; pri_loop_destroy_by_id
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
box$ = 48
?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z PROC	; pri_loop_destroy

; 69   : void pri_loop_destroy (pri_loop_box_t *box) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 70   : 	if (first_loop == NULL)

	cmp	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, 0 ; first_loop
	jne	SHORT $LN5@pri_loop_d

; 71   : 		return;

	jmp	$LN6@pri_loop_d
$LN5@pri_loop_d:

; 72   : 
; 73   : 	if (box == first_loop) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	cmp	QWORD PTR box$[rsp], rax
	jne	SHORT $LN4@pri_loop_d

; 74   : 		first_loop = first_loop->next;

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, rax ; first_loop

; 75   : 	} else {

	jmp	SHORT $LN3@pri_loop_d
$LN4@pri_loop_d:

; 76   : 		box->prev->next = box->next;

	mov	rax, QWORD PTR box$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR box$[rsp]
	mov	rcx, QWORD PTR [rcx+16]
	mov	QWORD PTR [rax+16], rcx
$LN3@pri_loop_d:

; 77   : 	}
; 78   : 
; 79   : 	if (box == last_loop) {

	mov	rax, QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA ; last_loop
	cmp	QWORD PTR box$[rsp], rax
	jne	SHORT $LN2@pri_loop_d

; 80   : 		last_loop = box->prev;

	mov	rax, QWORD PTR box$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA, rax ; last_loop

; 81   : 	} else {

	jmp	SHORT $LN1@pri_loop_d
$LN2@pri_loop_d:

; 82   : 		box->next->prev = box->prev;

	mov	rax, QWORD PTR box$[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	rcx, QWORD PTR box$[rsp]
	mov	rcx, QWORD PTR [rcx+24]
	mov	QWORD PTR [rax+24], rcx
$LN1@pri_loop_d:

; 83   : 	}
; 84   : 
; 85   : 	AuPmmngrFree((void*)v2p((size_t)box->address));

	mov	rax, QWORD PTR box$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	v2p
	mov	rcx, rax
	call	AuPmmngrFree

; 86   : 	//AuPmmngrFree(box);
; 87   : 	free(box);

	mov	rcx, QWORD PTR box$[rsp]
	call	free
$LN6@pri_loop_d:

; 88   : }

	add	rsp, 40					; 00000028H
	ret	0
?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z ENDP	; pri_loop_destroy
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
hunged$ = 32
owner_id$ = 36
loop$1 = 40
thread$ = 48
event$ = 80
?pri_put_message@@YAXPEAU_pri_event_@@@Z PROC		; pri_put_message

; 109  : void pri_put_message (pri_event_t *event) {

$LN10:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 110  : 	x64_cli();

	call	x64_cli

; 111  : 	bool hunged = false;

	mov	BYTE PTR hunged$[rsp], 0

; 112  : 	uint16_t owner_id = event->to_id;

	mov	rax, QWORD PTR event$[rsp]
	movzx	eax, BYTE PTR [rax+1]
	mov	WORD PTR owner_id$[rsp], ax

; 113  : 	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR loop$1[rsp], rax
	jmp	SHORT $LN7@pri_put_me
$LN6@pri_put_me:
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR loop$1[rsp], rax
$LN7@pri_put_me:
	cmp	QWORD PTR loop$1[rsp], 0
	je	SHORT $LN5@pri_put_me

; 114  : 		if (loop->owner_id == owner_id) {

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR owner_id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN4@pri_put_me

; 115  : 			if (loop->message_pending)

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, BYTE PTR [rax+10]
	test	eax, eax
	je	SHORT $LN3@pri_put_me

; 116  : 				break;

	jmp	SHORT $LN5@pri_put_me
$LN3@pri_put_me:

; 117  : 			memcpy (loop->address, event, sizeof(pri_event_t));

	mov	r8d, 176				; 000000b0H
	mov	rdx, QWORD PTR event$[rsp]
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rcx, QWORD PTR [rax]
	call	memcpy

; 118  : 			loop->message_pending = 1;

	mov	rax, QWORD PTR loop$1[rsp]
	mov	BYTE PTR [rax+10], 1

; 119  : 			loop->pending_msg_count++;

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+12]
	inc	ax
	mov	rcx, QWORD PTR loop$1[rsp]
	mov	WORD PTR [rcx+12], ax

; 120  : 			break;

	jmp	SHORT $LN5@pri_put_me
$LN4@pri_put_me:

; 121  : 		}
; 122  : 	}

	jmp	SHORT $LN6@pri_put_me
$LN5@pri_put_me:

; 123  : 
; 124  : 	//! check if the destination thread is blocked or not
; 125  : 	//! if blocked, wake it up, cause new message is pending
; 126  : 	thread_t *thread = thread_iterate_ready_list(owner_id);	

	movzx	ecx, WORD PTR owner_id$[rsp]
	call	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ; thread_iterate_ready_list
	mov	QWORD PTR thread$[rsp], rax

; 127  : 	if (thread == NULL) 

	cmp	QWORD PTR thread$[rsp], 0
	jne	SHORT $LN2@pri_put_me

; 128  : 		thread = thread_iterate_block_list(owner_id);

	movzx	eax, WORD PTR owner_id$[rsp]
	mov	ecx, eax
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR thread$[rsp], rax
$LN2@pri_put_me:

; 129  : 	if (thread != NULL && thread->state == THREAD_STATE_BLOCKED) {

	cmp	QWORD PTR thread$[rsp], 0
	je	SHORT $LN1@pri_put_me
	mov	rax, QWORD PTR thread$[rsp]
	movzx	eax, BYTE PTR [rax+240]
	cmp	eax, 3
	jne	SHORT $LN1@pri_put_me

; 130  : 		unblock_thread(thread);

	mov	rcx, QWORD PTR thread$[rsp]
	call	?unblock_thread@@YAXPEAU_thread_@@@Z	; unblock_thread
$LN1@pri_put_me:
$ret$11:

; 131  : 	}
; 132  : ret:
; 133  : 	x64_sti();

	call	x64_sti

; 134  : 	return;
; 135  : }

	add	rsp, 72					; 00000048H
	ret	0
?pri_put_message@@YAXPEAU_pri_event_@@@Z ENDP		; pri_put_message
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
node$ = 32
?pri_loop_init@@YAXXZ PROC				; pri_loop_init

; 206  : void pri_loop_init () {

$LN3:
	sub	rsp, 56					; 00000038H

; 207  : 	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 104				; 00000068H
	call	malloc
	mov	QWORD PTR node$[rsp], rax

; 208  : 	strcpy (node->filename, "pri_loop");

	mov	rax, QWORD PTR node$[rsp]
	lea	rdx, OFFSET FLAT:$SG3619
	mov	rcx, rax
	call	strcpy

; 209  : 	node->size = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+32], 0

; 210  : 	node->eof = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+36], 0

; 211  : 	node->pos = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+40], 0

; 212  : 	node->current = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+44], 0

; 213  : 	node->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+48], 12

; 214  : 	node->status = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+49], 0

; 215  : 	node->open = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+64], 0

; 216  : 	node->read = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+72], 0

; 217  : 	node->write = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+80], 0

; 218  : 	node->read_blk = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+88], 0

; 219  : 	node->ioquery = pri_loop_ioquery;

	mov	rax, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z ; pri_loop_ioquery
	mov	QWORD PTR [rax+96], rcx

; 220  : 	vfs_mount ("/dev/pri_loop", node, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:$SG3620
	call	vfs_mount

; 221  : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_loop_init@@YAXXZ ENDP				; pri_loop_init
_TEXT	ENDS
END
