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
$SG3304	DB	'pri_loop', 00H
	ORG $+7
$SG3305	DB	'/dev/pri_loop', 00H
CONST	ENDS
PUBLIC	?pri_loop_init@@YAXXZ				; pri_loop_init
PUBLIC	?pri_loop_create@@YAXXZ				; pri_loop_create
PUBLIC	?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z	; pri_loop_destroy
PUBLIC	?pri_put_message@@YAXPEAU_pri_event_@@@Z	; pri_put_message
PUBLIC	?pri_get_message@@YAXPEAU_pri_event_@@@Z	; pri_get_message
PUBLIC	?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z	; pri_loop_ioquery
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?pmmngr_free@@YAXPEAX@Z:PROC			; pmmngr_free
EXTRN	x64_cli:PROC
EXTRN	?strcpy@@YAPEADPEADPEBD@Z:PROC			; strcpy
EXTRN	memcpy:PROC
EXTRN	?malloc@@YAPEAX_K@Z:PROC			; malloc
EXTRN	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z:PROC	; vfs_mount
EXTRN	?unblock_thread@@YAXPEAU_thread_@@@Z:PROC	; unblock_thread
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
EXTRN	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z:PROC ; thread_iterate_ready_list
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
pdata	SEGMENT
$pdata$?pri_loop_init@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+201
	DD	imagerel $unwind$?pri_loop_init@@YAXXZ
$pdata$?pri_loop_create@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+164
	DD	imagerel $unwind$?pri_loop_create@@YAXXZ
$pdata$?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+146
	DD	imagerel $unwind$?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z
$pdata$?pri_put_message@@YAXPEAU_pri_event_@@@Z DD imagerel $LN9
	DD	imagerel $LN9+199
	DD	imagerel $unwind$?pri_put_message@@YAXPEAU_pri_event_@@@Z
$pdata$?pri_get_message@@YAXPEAU_pri_event_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+140
	DD	imagerel $unwind$?pri_get_message@@YAXPEAU_pri_event_@@@Z
$pdata$?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN13
	DD	imagerel $LN13+244
	DD	imagerel $unwind$?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?pri_loop_init@@YAXXZ DD 010401H
	DD	06204H
$unwind$?pri_loop_create@@YAXXZ DD 010401H
	DD	06204H
$unwind$?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z DD 010901H
	DD	04209H
$unwind$?pri_put_message@@YAXPEAU_pri_event_@@@Z DD 010901H
	DD	08209H
$unwind$?pri_get_message@@YAXPEAU_pri_event_@@@Z DD 010901H
	DD	06209H
$unwind$?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD 021501H
	DD	0130115H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
tv64 = 32
box$1 = 40
tv68 = 48
event$2 = 56
e$3 = 64
file$ = 160
code$ = 168
arg$ = 176
?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z PROC	; pri_loop_ioquery

; 115  : int pri_loop_ioquery (vfs_node_t *file, int code, void *arg) {

$LN13:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 152				; 00000098H

; 116  : 	switch (code) {

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

; 117  : 	case PRI_LOOP_CREATE: {
; 118  : 		pri_loop_create();

	call	?pri_loop_create@@YAXXZ			; pri_loop_create

; 119  : 		break;

	jmp	$LN9@pri_loop_i
$LN7@pri_loop_i:

; 120  : 	}
; 121  : 	case PRI_LOOP_DESTROY: {
; 122  : 		pri_loop_box_t *box;
; 123  : 		for (box = first_loop; box != NULL; box = box->next) {

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

; 124  : 			if (box->owner_id == get_current_thread()->id) {

	mov	rax, QWORD PTR box$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	mov	DWORD PTR tv68[rsp], eax
	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movzx	eax, WORD PTR [rax+234]
	mov	ecx, DWORD PTR tv68[rsp]
	cmp	ecx, eax
	jne	SHORT $LN3@pri_loop_i

; 125  : 				pri_loop_destroy(box);

	mov	rcx, QWORD PTR box$1[rsp]
	call	?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z ; pri_loop_destroy

; 126  : 				break;

	jmp	SHORT $LN4@pri_loop_i
$LN3@pri_loop_i:

; 127  : 			}
; 128  : 		}

	jmp	SHORT $LN5@pri_loop_i
$LN4@pri_loop_i:

; 129  : 		break;

	jmp	SHORT $LN9@pri_loop_i
$LN2@pri_loop_i:

; 130  : 	}
; 131  : 	case PRI_LOOP_PUT_EVENT: {
; 132  : 		pri_event_t *event = (pri_event_t*)arg;

	mov	rax, QWORD PTR arg$[rsp]
	mov	QWORD PTR event$2[rsp], rax

; 133  : 		pri_put_message(event);

	mov	rcx, QWORD PTR event$2[rsp]
	call	?pri_put_message@@YAXPEAU_pri_event_@@@Z ; pri_put_message

; 134  : 		break;

	jmp	SHORT $LN9@pri_loop_i
$LN1@pri_loop_i:

; 135  : 	}
; 136  : 
; 137  : 	case PRI_LOOP_GET_EVENT: {
; 138  : 		pri_event_t e;
; 139  : 		pri_get_message(&e);

	lea	rcx, QWORD PTR e$3[rsp]
	call	?pri_get_message@@YAXPEAU_pri_event_@@@Z ; pri_get_message

; 140  : 		memcpy (arg,&e,sizeof(pri_event_t));

	mov	r8d, 72					; 00000048H
	lea	rdx, QWORD PTR e$3[rsp]
	mov	rcx, QWORD PTR arg$[rsp]
	call	memcpy
$LN9@pri_loop_i:

; 141  : 		break;
; 142  : 	}
; 143  : 	}
; 144  : 
; 145  : 	return 1;

	mov	eax, 1

; 146  : }

	add	rsp, 152				; 00000098H
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

; 99   : void pri_get_message (pri_event_t *event) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 100  : 	x64_cli ();

	call	x64_cli

; 101  : 
; 102  : 	uint16_t owner_id = get_current_thread()->id;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movzx	eax, WORD PTR [rax+234]
	mov	WORD PTR owner_id$[rsp], ax

; 103  : 	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR loop$1[rsp], rax
	jmp	SHORT $LN5@pri_get_me
$LN4@pri_get_me:
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR loop$1[rsp], rax
$LN5@pri_get_me:
	cmp	QWORD PTR loop$1[rsp], 0
	je	SHORT $LN3@pri_get_me

; 104  : 		if (loop->owner_id == owner_id) {

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR owner_id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN2@pri_get_me

; 105  : 			if (loop->message_pending){

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, BYTE PTR [rax+10]
	test	eax, eax
	je	SHORT $LN1@pri_get_me

; 106  : 				memcpy (event,loop->address, sizeof(pri_event_t));

	mov	r8d, 72					; 00000048H
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rdx, QWORD PTR [rax]
	mov	rcx, QWORD PTR event$[rsp]
	call	memcpy

; 107  : 				loop->message_pending = false;

	mov	rax, QWORD PTR loop$1[rsp]
	mov	BYTE PTR [rax+10], 0
$LN1@pri_get_me:

; 108  : 			} 
; 109  : 			break;

	jmp	SHORT $LN3@pri_get_me
$LN2@pri_get_me:

; 110  : 		}
; 111  : 	}

	jmp	SHORT $LN4@pri_get_me
$LN3@pri_get_me:

; 112  : 	return;
; 113  : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_get_message@@YAXPEAU_pri_event_@@@Z ENDP		; pri_get_message
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
owner_id$ = 32
loop$1 = 40
thread$ = 48
event$ = 80
?pri_put_message@@YAXPEAU_pri_event_@@@Z PROC		; pri_put_message

; 78   : void pri_put_message (pri_event_t *event) {

$LN9:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 79   : 	x64_cli();

	call	x64_cli

; 80   : 
; 81   : 	uint16_t owner_id = event->to_id;

	mov	rax, QWORD PTR event$[rsp]
	movzx	eax, BYTE PTR [rax+1]
	mov	WORD PTR owner_id$[rsp], ax

; 82   : 	for (pri_loop_box_t *loop = first_loop; loop != NULL; loop = loop->next) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	QWORD PTR loop$1[rsp], rax
	jmp	SHORT $LN6@pri_put_me
$LN5@pri_put_me:
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR loop$1[rsp], rax
$LN6@pri_put_me:
	cmp	QWORD PTR loop$1[rsp], 0
	je	SHORT $LN4@pri_put_me

; 83   : 		if (loop->owner_id == owner_id) {

	mov	rax, QWORD PTR loop$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR owner_id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN3@pri_put_me

; 84   : 			memcpy (loop->address, event, sizeof(pri_event_t));

	mov	r8d, 72					; 00000048H
	mov	rdx, QWORD PTR event$[rsp]
	mov	rax, QWORD PTR loop$1[rsp]
	mov	rcx, QWORD PTR [rax]
	call	memcpy

; 85   : 			loop->message_pending = 1;

	mov	rax, QWORD PTR loop$1[rsp]
	mov	BYTE PTR [rax+10], 1

; 86   : 			break;

	jmp	SHORT $LN4@pri_put_me
$LN3@pri_put_me:

; 87   : 		}
; 88   : 	}

	jmp	SHORT $LN5@pri_put_me
$LN4@pri_put_me:

; 89   : 
; 90   : 	thread_t *thread = thread_iterate_ready_list(owner_id);

	movzx	ecx, WORD PTR owner_id$[rsp]
	call	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ; thread_iterate_ready_list
	mov	QWORD PTR thread$[rsp], rax

; 91   : 	if (thread == NULL) 

	cmp	QWORD PTR thread$[rsp], 0
	jne	SHORT $LN2@pri_put_me

; 92   : 		thread = thread_iterate_block_list(owner_id);

	movzx	eax, WORD PTR owner_id$[rsp]
	mov	ecx, eax
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR thread$[rsp], rax
$LN2@pri_put_me:

; 93   : 	if (thread != NULL && thread->state == THREAD_STATE_BLOCKED)

	cmp	QWORD PTR thread$[rsp], 0
	je	SHORT $LN1@pri_put_me
	mov	rax, QWORD PTR thread$[rsp]
	movzx	eax, BYTE PTR [rax+232]
	cmp	eax, 3
	jne	SHORT $LN1@pri_put_me

; 94   : 		unblock_thread(thread);

	mov	rcx, QWORD PTR thread$[rsp]
	call	?unblock_thread@@YAXPEAU_thread_@@@Z	; unblock_thread
$LN1@pri_put_me:

; 95   : 
; 96   : 	return;
; 97   : }

	add	rsp, 72					; 00000048H
	ret	0
?pri_put_message@@YAXPEAU_pri_event_@@@Z ENDP		; pri_put_message
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
box$ = 48
?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z PROC	; pri_loop_destroy

; 59   : void pri_loop_destroy (pri_loop_box_t *box) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 60   : 	if (first_loop == NULL)

	cmp	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, 0 ; first_loop
	jne	SHORT $LN5@pri_loop_d

; 61   : 		return;

	jmp	SHORT $LN6@pri_loop_d
$LN5@pri_loop_d:

; 62   : 
; 63   : 	if (box == first_loop) {

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	cmp	QWORD PTR box$[rsp], rax
	jne	SHORT $LN4@pri_loop_d

; 64   : 		first_loop = first_loop->next;

	mov	rax, QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA ; first_loop
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, rax ; first_loop

; 65   : 	} else {

	jmp	SHORT $LN3@pri_loop_d
$LN4@pri_loop_d:

; 66   : 		box->prev->next = box->next;

	mov	rax, QWORD PTR box$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR box$[rsp]
	mov	rcx, QWORD PTR [rcx+16]
	mov	QWORD PTR [rax+16], rcx
$LN3@pri_loop_d:

; 67   : 	}
; 68   : 
; 69   : 	if (box == last_loop) {

	mov	rax, QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA ; last_loop
	cmp	QWORD PTR box$[rsp], rax
	jne	SHORT $LN2@pri_loop_d

; 70   : 		last_loop = box->prev;

	mov	rax, QWORD PTR box$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA, rax ; last_loop

; 71   : 	} else {

	jmp	SHORT $LN1@pri_loop_d
$LN2@pri_loop_d:

; 72   : 		box->next->prev = box->prev;

	mov	rax, QWORD PTR box$[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	rcx, QWORD PTR box$[rsp]
	mov	rcx, QWORD PTR [rcx+24]
	mov	QWORD PTR [rax+24], rcx
$LN1@pri_loop_d:

; 73   : 	}
; 74   : 	pmmngr_free(box);

	mov	rcx, QWORD PTR box$[rsp]
	call	?pmmngr_free@@YAXPEAX@Z			; pmmngr_free
$LN6@pri_loop_d:

; 75   : }

	add	rsp, 40					; 00000028H
	ret	0
?pri_loop_destroy@@YAXPEAU_pri_loop_box_@@@Z ENDP	; pri_loop_destroy
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
loop$ = 32
?pri_loop_create@@YAXXZ PROC				; pri_loop_create

; 42   : void pri_loop_create () {

$LN5:
	sub	rsp, 56					; 00000038H

; 43   : 	pri_loop_box_t *loop = (pri_loop_box_t*)malloc(sizeof(pri_loop_box_t));

	mov	ecx, 32					; 00000020H
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	QWORD PTR loop$[rsp], rax

; 44   : 	loop->address = pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rcx, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rcx], rax

; 45   : 	loop->owner_id = get_current_thread()->id;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rcx, QWORD PTR loop$[rsp]
	movzx	eax, WORD PTR [rax+234]
	mov	WORD PTR [rcx+8], ax

; 46   : 	loop->next = NULL;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rax+16], 0

; 47   : 	loop->prev = NULL;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rax+24], 0

; 48   : 
; 49   : 	if (first_loop == NULL)  {

	cmp	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, 0 ; first_loop
	jne	SHORT $LN2@pri_loop_c

; 50   : 		first_loop = loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR ?first_loop@@3PEAU_pri_loop_box_@@EA, rax ; first_loop

; 51   : 		last_loop = loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA, rax ; last_loop

; 52   : 	} else {

	jmp	SHORT $LN1@pri_loop_c
$LN2@pri_loop_c:

; 53   : 		last_loop->next = loop;

	mov	rax, QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA ; last_loop
	mov	rcx, QWORD PTR loop$[rsp]
	mov	QWORD PTR [rax+16], rcx

; 54   : 		loop->prev = last_loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	rcx, QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA ; last_loop
	mov	QWORD PTR [rax+24], rcx

; 55   : 		last_loop = loop;

	mov	rax, QWORD PTR loop$[rsp]
	mov	QWORD PTR ?last_loop@@3PEAU_pri_loop_box_@@EA, rax ; last_loop
$LN1@pri_loop_c:

; 56   : 	}
; 57   : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_loop_create@@YAXXZ ENDP				; pri_loop_create
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\pri_loop.cpp
_TEXT	SEGMENT
node$ = 32
?pri_loop_init@@YAXXZ PROC				; pri_loop_init

; 149  : void pri_loop_init () {

$LN3:
	sub	rsp, 56					; 00000038H

; 150  : 	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 104				; 00000068H
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	QWORD PTR node$[rsp], rax

; 151  : 	strcpy (node->filename, "pri_loop");

	mov	rax, QWORD PTR node$[rsp]
	lea	rdx, OFFSET FLAT:$SG3304
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 152  : 	node->size = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+32], 0

; 153  : 	node->eof = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+36], 0

; 154  : 	node->pos = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+40], 0

; 155  : 	node->current = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+44], 0

; 156  : 	node->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+48], 2

; 157  : 	node->status = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+52], 0

; 158  : 	node->open = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+64], 0

; 159  : 	node->read = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+72], 0

; 160  : 	node->write = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+80], 0

; 161  : 	node->read_blk = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+88], 0

; 162  : 	node->ioquery = pri_loop_ioquery;

	mov	rax, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:?pri_loop_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z ; pri_loop_ioquery
	mov	QWORD PTR [rax+96], rcx

; 163  : 	vfs_mount ("/dev/pri_loop", node);

	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:$SG3305
	call	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z	; vfs_mount

; 164  : }

	add	rsp, 56					; 00000038H
	ret	0
?pri_loop_init@@YAXXZ ENDP				; pri_loop_init
_TEXT	ENDS
END
