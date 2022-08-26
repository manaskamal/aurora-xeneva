; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?registered_dev@@3PEAU_sound_@@EA		; registered_dev
PUBLIC	?registered_thr@@3PEAU_thread_@@EA		; registered_thr
PUBLIC	?next_pos@@3IA					; next_pos
PUBLIC	?data_buff@@3PEAEEA				; data_buff
PUBLIC	?dsp_first@@3PEAU_dsp_@@EA			; dsp_first
PUBLIC	?dsp_last@@3PEAU_dsp_@@EA			; dsp_last
PUBLIC	?_audio_started_@@3_NA				; _audio_started_
PUBLIC	?_audio_stoped_@@3_NA				; _audio_stoped_
_BSS	SEGMENT
?registered_dev@@3PEAU_sound_@@EA DQ 01H DUP (?)	; registered_dev
?registered_thr@@3PEAU_thread_@@EA DQ 01H DUP (?)	; registered_thr
?next_pos@@3IA DD 01H DUP (?)				; next_pos
	ALIGN	8

?data_buff@@3PEAEEA DQ 01H DUP (?)			; data_buff
?dsp_first@@3PEAU_dsp_@@EA DQ 01H DUP (?)		; dsp_first
?dsp_last@@3PEAU_dsp_@@EA DQ 01H DUP (?)		; dsp_last
?_audio_started_@@3_NA DB 01H DUP (?)			; _audio_started_
	ALIGN	4

?_audio_stoped_@@3_NA DB 01H DUP (?)			; _audio_stoped_
_BSS	ENDS
CONST	SEGMENT
$SG3975	DB	'dsp', 00H
	ORG $+4
$SG3976	DB	'/dev/dsp', 00H
CONST	ENDS
PUBLIC	?AuSoundInitialize@@YAXXZ			; AuSoundInitialize
PUBLIC	AuSoundRegisterDevice
PUBLIC	AuSoundRequestNext
PUBLIC	?AuSoundStart@@YAXXZ				; AuSoundStart
PUBLIC	?AuSoundDeInitialize@@YAXXZ			; AuSoundDeInitialize
PUBLIC	?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z	; AuSoundWrite
PUBLIC	?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z		; AuSoundAddDSP
PUBLIC	?AuRemoveDSP@@YAXPEAU_dsp_@@@Z			; AuRemoveDSP
PUBLIC	?AuRequestNextBlock@@YAXG@Z			; AuRequestNextBlock
PUBLIC	?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z		; AuSoundGetDSP
PUBLIC	?AuSoundRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z	; AuSoundRead
PUBLIC	?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z	; AuSoundIOQuery
PUBLIC	?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z	; AuFileWrite
EXTRN	strcpy:PROC
EXTRN	vfs_mount:PROC
EXTRN	AuPmmngrAllocBlocks:PROC
EXTRN	AuPmmngrFreeBlocks:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	x64_cli:PROC
EXTRN	malloc:PROC
EXTRN	?block_thread@@YAXPEAU_thread_@@@Z:PROC		; block_thread
EXTRN	get_current_thread:PROC
EXTRN	force_sched:PROC
EXTRN	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z:PROC	; circ_buf_init
EXTRN	?circular_buf_put2@@YAHPEAU_circ_buf_@@E@Z:PROC	; circular_buf_put2
EXTRN	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z:PROC ; circular_buf_get
EXTRN	?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z:PROC	; circular_buf_full
EXTRN	?pri_put_message@@YAXPEAU_pri_event_@@@Z:PROC	; pri_put_message
pdata	SEGMENT
$pdata$?AuSoundInitialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+237
	DD	imagerel $unwind$?AuSoundInitialize@@YAXXZ
$pdata$AuSoundRequestNext DD imagerel $LN25
	DD	imagerel $LN25+508
	DD	imagerel $unwind$AuSoundRequestNext
$pdata$?AuSoundStart@@YAXXZ DD imagerel $LN4
	DD	imagerel $LN4+31
	DD	imagerel $unwind$?AuSoundStart@@YAXXZ
$pdata$?AuSoundDeInitialize@@YAXXZ DD imagerel $LN4
	DD	imagerel $LN4+31
	DD	imagerel $unwind$?AuSoundDeInitialize@@YAXXZ
$pdata$?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z DD imagerel $LN13
	DD	imagerel $LN13+320
	DD	imagerel $unwind$?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z
$pdata$?AuRequestNextBlock@@YAXG@Z DD imagerel $LN3
	DD	imagerel $LN3+52
	DD	imagerel $unwind$?AuRequestNextBlock@@YAXG@Z
$pdata$?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z DD imagerel $LN7
	DD	imagerel $LN7+73
	DD	imagerel $unwind$?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z
$pdata$?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN13
	DD	imagerel $LN13+254
	DD	imagerel $unwind$?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z
$pdata$?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z DD imagerel $LN7
	DD	imagerel $LN7+182
	DD	imagerel $unwind$?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuSoundInitialize@@YAXXZ DD 010401H
	DD	06204H
$unwind$AuSoundRequestNext DD 010901H
	DD	0c209H
$unwind$?AuSoundStart@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuSoundDeInitialize@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z DD 011301H
	DD	0a213H
$unwind$?AuRequestNextBlock@@YAXG@Z DD 020c01H
	DD	01b010cH
$unwind$?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z DD 010901H
	DD	02209H
$unwind$?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z DD 011201H
	DD	08212H
$unwind$?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z DD 011301H
	DD	08213H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
i$1 = 32
dsp$ = 40
aligned_buffer$ = 48
al$ = 56
node$ = 80
buffer$ = 88
length$ = 96
?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z PROC		; AuFileWrite

; 192  : void AuFileWrite (vfs_node_t* node, uint64_t *buffer, uint32_t length) {

$LN7:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 193  : 	x64_cli();

	call	x64_cli

; 194  : 	dsp_t *dsp = AuSoundGetDSP(get_current_thread()->id);

	call	get_current_thread
	movzx	ecx, WORD PTR [rax+242]
	call	?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z	; AuSoundGetDSP
	mov	QWORD PTR dsp$[rsp], rax

; 195  : 	uint8_t* al = (uint8_t*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR al$[rsp], rax

; 196  : 	uint8_t* aligned_buffer = (uint8_t*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR aligned_buffer$[rsp], rax

; 197  : 	if (circular_buf_full(dsp->buffer)) {

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z ; circular_buf_full
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN4@AuFileWrit

; 198  : 		dsp->blocked_thr = get_current_thread();

	call	get_current_thread
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rcx+24], rax

; 199  : 		block_thread(get_current_thread());

	call	get_current_thread
	mov	rcx, rax
	call	?block_thread@@YAXPEAU_thread_@@@Z	; block_thread

; 200  : 		force_sched();

	call	force_sched
$LN4@AuFileWrit:

; 201  : 	}
; 202  : 	for (int i = 0; i < BUFF_SIZE; i++) 

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuFileWrit
$LN2@AuFileWrit:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuFileWrit:
	cmp	DWORD PTR i$1[rsp], 4096		; 00001000H
	jge	SHORT $LN1@AuFileWrit

; 203  : 		circular_buf_put2(dsp->buffer, aligned_buffer[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR aligned_buffer$[rsp]
	movzx	edx, BYTE PTR [rcx+rax]
	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_put2@@YAHPEAU_circ_buf_@@E@Z ; circular_buf_put2
	jmp	SHORT $LN2@AuFileWrit
$LN1@AuFileWrit:

; 204  : 	
; 205  : }

	add	rsp, 72					; 00000048H
	ret	0
?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z ENDP		; AuFileWrite
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
tv65 = 32
dsp$1 = 40
buffer$2 = 48
callbk$3 = 56
node$ = 80
code$ = 88
arg$ = 96
?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z PROC	; AuSoundIOQuery

; 151  : int AuSoundIOQuery (vfs_node_t *node, int code, void* arg) {

$LN13:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 152  : 	x64_cli();

	call	x64_cli

; 153  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN10@AuSoundIOQ

; 154  : 		return 1;

	mov	eax, 1
	jmp	$LN11@AuSoundIOQ
$LN10@AuSoundIOQ:

; 155  : 
; 156  : 	switch (code)

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv65[rsp], eax
	cmp	DWORD PTR tv65[rsp], 100		; 00000064H
	je	SHORT $LN7@AuSoundIOQ
	cmp	DWORD PTR tv65[rsp], 106		; 0000006aH
	je	$LN2@AuSoundIOQ
	jmp	$LN8@AuSoundIOQ
$LN7@AuSoundIOQ:

; 157  : 	{
; 158  : 	case SOUND_REGISTER_MEDIAPLAYER:{
; 159  : 		registered_thr = get_current_thread();

	call	get_current_thread
	mov	QWORD PTR ?registered_thr@@3PEAU_thread_@@EA, rax ; registered_thr

; 160  : 		dsp_t *dsp = (dsp_t*)malloc(sizeof(dsp_t));

	mov	ecx, 56					; 00000038H
	call	malloc
	mov	QWORD PTR dsp$1[rsp], rax

; 161  : 		uint8_t* buffer = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 1
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buffer$2[rsp], rax

; 162  : 		dsp->buffer = circ_buf_init(buffer, BUFF_SIZE); //(uint8_t*)

	mov	edx, 4096				; 00001000H
	mov	rcx, QWORD PTR buffer$2[rsp]
	call	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z ; circ_buf_init
	mov	rcx, QWORD PTR dsp$1[rsp]
	mov	QWORD PTR [rcx], rax

; 163  : 		dsp->id = get_current_thread()->id;

	call	get_current_thread
	mov	rcx, QWORD PTR dsp$1[rsp]
	movzx	eax, WORD PTR [rax+242]
	mov	WORD PTR [rcx+8], ax

; 164  : 		dsp->registered_thr = get_current_thread();

	call	get_current_thread
	mov	rcx, QWORD PTR dsp$1[rsp]
	mov	QWORD PTR [rcx+16], rax

; 165  : 		AuSoundAddDSP(dsp);

	mov	rcx, QWORD PTR dsp$1[rsp]
	call	?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z	; AuSoundAddDSP

; 166  : 		break;

	jmp	SHORT $LN8@AuSoundIOQ

; 167  : 	}
; 168  : 	case SOUND_START_OUTPUT:{
; 169  : 		/* This Code should be removed */
; 170  : 		break;

	jmp	SHORT $LN8@AuSoundIOQ

; 171  : 	}
; 172  : 	case SOUND_STOP_OUTPUT:{
; 173  : 		/* This Code should be removed */
; 174  : 		break;

	jmp	SHORT $LN8@AuSoundIOQ

; 175  : 						   }
; 176  : 	case SOUND_START_INPUT: //Not implemented
; 177  : 		break;

	jmp	SHORT $LN8@AuSoundIOQ

; 178  : 	case SOUND_STOP_INPUT:
; 179  : 		break;  //Not implemented

	jmp	SHORT $LN8@AuSoundIOQ
$LN2@AuSoundIOQ:

; 180  : 	case SOUND_SET_VOLUME: {
; 181  : 		if (!registered_dev)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundIOQ

; 182  : 			return -1;

	mov	eax, -1
	jmp	SHORT $LN11@AuSoundIOQ
$LN1@AuSoundIOQ:

; 183  : 		au_sound_callback_t *callbk = (au_sound_callback_t*)arg;

	mov	rax, QWORD PTR arg$[rsp]
	mov	QWORD PTR callbk$3[rsp], rax

; 184  : 		registered_dev->set_volume(callbk->uchar_1);

	mov	rax, QWORD PTR callbk$3[rsp]
	movzx	ecx, BYTE PTR [rax]
	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+64]
$LN8@AuSoundIOQ:

; 185  : 		break;
; 186  : 	}	
; 187  : 	}
; 188  : 
; 189  : 	return 0;

	xor	eax, eax
$LN11@AuSoundIOQ:

; 190  : }

	add	rsp, 72					; 00000048H
	ret	0
?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP	; AuSoundIOQuery
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
file$ = 8
buffer$ = 16
length$ = 24
?AuSoundRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z PROC		; AuSoundRead

; 120  : size_t AuSoundRead (vfs_node_t *file, uint64_t* buffer, uint32_t length) {

	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 121  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundRea

; 122  : 		return -1;

	mov	rax, -1
	jmp	SHORT $LN2@AuSoundRea
$LN1@AuSoundRea:

; 123  : 	return 0;

	xor	eax, eax
$LN2@AuSoundRea:

; 124  : }

	fatret	0
?AuSoundRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z ENDP		; AuSoundRead
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$1 = 0
id$ = 32
?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z PROC			; AuSoundGetDSP

; 110  : dsp_t* AuSoundGetDSP(uint16_t id) {

$LN7:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 24

; 111  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	mov	QWORD PTR dsp$1[rsp], rax
	jmp	SHORT $LN4@AuSoundGet
$LN3@AuSoundGet:
	mov	rax, QWORD PTR dsp$1[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR dsp$1[rsp], rax
$LN4@AuSoundGet:
	cmp	QWORD PTR dsp$1[rsp], 0
	je	SHORT $LN2@AuSoundGet

; 112  : 		if (dsp->id == id)

	mov	rax, QWORD PTR dsp$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN1@AuSoundGet

; 113  : 			return dsp;

	mov	rax, QWORD PTR dsp$1[rsp]
	jmp	SHORT $LN5@AuSoundGet
$LN1@AuSoundGet:

; 114  : 	}

	jmp	SHORT $LN3@AuSoundGet
$LN2@AuSoundGet:

; 115  : 
; 116  : 	return NULL;

	xor	eax, eax
$LN5@AuSoundGet:

; 117  : }

	add	rsp, 24
	ret	0
?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z ENDP			; AuSoundGetDSP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
e$ = 32
id$ = 224
?AuRequestNextBlock@@YAXG@Z PROC			; AuRequestNextBlock

; 91   : void AuRequestNextBlock(uint16_t id) {

$LN3:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 216				; 000000d8H

; 92   : 	pri_event_t e;
; 93   : 	e.to_id = id;

	movzx	eax, BYTE PTR id$[rsp]
	mov	BYTE PTR e$[rsp+1], al

; 94   : 	e.from_id = 0;

	mov	BYTE PTR e$[rsp+2], 0

; 95   : 	e.type = 10;

	mov	BYTE PTR e$[rsp], 10

; 96   : 	pri_put_message(&e);

	lea	rcx, QWORD PTR e$[rsp]
	call	?pri_put_message@@YAXPEAU_pri_event_@@@Z ; pri_put_message

; 97   : 	//thread_t *t = thread_iterate_ready_list(id);
; 98   : 	//if (t == NULL)
; 99   : 	//	t = thread_iterate_block_list(id);
; 100  : 
; 101  : 	//if (t->state == THREAD_STATE_BLOCKED)
; 102  : 	//	unblock_thread(t);
; 103  : }

	add	rsp, 216				; 000000d8H
	ret	0
?AuRequestNextBlock@@YAXG@Z ENDP			; AuRequestNextBlock
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 8
?AuRemoveDSP@@YAXPEAU_dsp_@@@Z PROC			; AuRemoveDSP

; 73   : void AuRemoveDSP(dsp_t *dsp) {

	mov	QWORD PTR [rsp+8], rcx

; 74   : 	if (dsp_first == NULL)

	cmp	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first
	jne	SHORT $LN5@AuRemoveDS

; 75   : 		return;

	jmp	SHORT $LN6@AuRemoveDS
$LN5@AuRemoveDS:

; 76   : 
; 77   : 	if (dsp == dsp_first) {

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	cmp	QWORD PTR dsp$[rsp], rax
	jne	SHORT $LN4@AuRemoveDS

; 78   : 		dsp_first = dsp_first->next;

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, rax ; dsp_first

; 79   : 	} else {

	jmp	SHORT $LN3@AuRemoveDS
$LN4@AuRemoveDS:

; 80   : 		dsp->prev->next = dsp->next;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+48]
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rcx+40]
	mov	QWORD PTR [rax+40], rcx
$LN3@AuRemoveDS:

; 81   : 	}
; 82   : 
; 83   : 	if (dsp == dsp_last) {

	mov	rax, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	cmp	QWORD PTR dsp$[rsp], rax
	jne	SHORT $LN2@AuRemoveDS

; 84   : 		dsp_last = dsp->prev;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+48]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last

; 85   : 	} else {

	jmp	SHORT $LN1@AuRemoveDS
$LN2@AuRemoveDS:

; 86   : 		dsp->next->prev = dsp->prev;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rcx+48]
	mov	QWORD PTR [rax+48], rcx
$LN1@AuRemoveDS:
$LN6@AuRemoveDS:

; 87   : 	}
; 88   : 
; 89   : }

	fatret	0
?AuRemoveDSP@@YAXPEAU_dsp_@@@Z ENDP			; AuRemoveDSP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 8
?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z PROC			; AuSoundAddDSP

; 56   : void AuSoundAddDSP(dsp_t *dsp) {

	mov	QWORD PTR [rsp+8], rcx

; 57   : 	dsp->next = NULL;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+40], 0

; 58   : 	dsp->prev = NULL;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+48], 0

; 59   : 	if (dsp_first == NULL) {

	cmp	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first
	jne	SHORT $LN2@AuSoundAdd

; 60   : 		dsp_first = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, rax ; dsp_first

; 61   : 		dsp_last = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last

; 62   : 	}else {

	jmp	SHORT $LN1@AuSoundAdd
$LN2@AuSoundAdd:

; 63   : 		dsp_last->next = dsp;

	mov	rax, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+40], rcx

; 64   : 		dsp->prev = dsp_last;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	mov	QWORD PTR [rax+48], rcx

; 65   : 		dsp_last = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last
$LN1@AuSoundAdd:

; 66   : 	}
; 67   : }

	fatret	0
?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z ENDP			; AuSoundAddDSP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
i$1 = 32
i$2 = 36
dsp$3 = 40
buff$ = 48
tmp_buffer$ = 56
aligned_buff$4 = 64
file$ = 96
buffer$ = 104
length$ = 112
?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z PROC		; AuSoundWrite

; 126  : void AuSoundWrite (vfs_node_t *file, uint8_t* buffer, uint32_t length) {

$LN13:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 127  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN10@AuSoundWri

; 128  : 		return;

	jmp	$LN11@AuSoundWri
$LN10@AuSoundWri:

; 129  : 	int16_t* tmp_buffer = (int16_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 1
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR tmp_buffer$[rsp], rax

; 130  : 	uint8_t* buff = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 1
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buff$[rsp], rax

; 131  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	mov	QWORD PTR dsp$3[rsp], rax
	jmp	SHORT $LN9@AuSoundWri
$LN8@AuSoundWri:
	mov	rax, QWORD PTR dsp$3[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR dsp$3[rsp], rax
$LN9@AuSoundWri:
	cmp	QWORD PTR dsp$3[rsp], 0
	je	$LN7@AuSoundWri

; 132  : 
; 133  : 		for (int i = 0; i < BUFF_SIZE; i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN6@AuSoundWri
$LN5@AuSoundWri:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN6@AuSoundWri:
	cmp	DWORD PTR i$2[rsp], 4096		; 00001000H
	jge	SHORT $LN4@AuSoundWri

; 134  : 			circular_buf_get(dsp->buffer,buff); 

	mov	rdx, QWORD PTR buff$[rsp]
	mov	rax, QWORD PTR dsp$3[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z ; circular_buf_get
	jmp	SHORT $LN5@AuSoundWri
$LN4@AuSoundWri:

; 135  : 
; 136  : 		int16_t* aligned_buff = (int16_t*)buff;

	mov	rax, QWORD PTR buff$[rsp]
	mov	QWORD PTR aligned_buff$4[rsp], rax

; 137  : 		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuSoundWri
$LN2@AuSoundWri:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuSoundWri:
	movsxd	rax, DWORD PTR i$1[rsp]
	cmp	rax, 2048				; 00000800H
	jae	SHORT $LN1@AuSoundWri

; 138  : 			tmp_buffer[i] = aligned_buff[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR tmp_buffer$[rsp]
	mov	r8, QWORD PTR aligned_buff$4[rsp]
	movzx	eax, WORD PTR [r8+rax*2]
	mov	WORD PTR [rdx+rcx*2], ax

; 139  : 		}

	jmp	SHORT $LN2@AuSoundWri
$LN1@AuSoundWri:

; 140  : 		//AuRequestNextBlock(dsp->id);
; 141  : 	}

	jmp	$LN8@AuSoundWri
$LN7@AuSoundWri:

; 142  : 	
; 143  : 	registered_dev->write((uint8_t*)tmp_buffer, BUFF_SIZE);

	mov	edx, 4096				; 00001000H
	mov	rcx, QWORD PTR tmp_buffer$[rsp]
	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+32]

; 144  : 	AuPmmngrFreeBlocks((void*)v2p((size_t)buff), BUFF_SIZE/4096);

	mov	rcx, QWORD PTR buff$[rsp]
	call	v2p
	mov	edx, 1
	mov	rcx, rax
	call	AuPmmngrFreeBlocks

; 145  : 	AuPmmngrFreeBlocks((void*)v2p((size_t)tmp_buffer), BUFF_SIZE/4096);

	mov	rcx, QWORD PTR tmp_buffer$[rsp]
	call	v2p
	mov	edx, 1
	mov	rcx, rax
	call	AuPmmngrFreeBlocks
$LN11@AuSoundWri:

; 146  : }

	add	rsp, 88					; 00000058H
	ret	0
?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z ENDP		; AuSoundWrite
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
?AuSoundDeInitialize@@YAXXZ PROC			; AuSoundDeInitialize

; 281  : void AuSoundDeInitialize() {

$LN4:
	sub	rsp, 40					; 00000028H

; 282  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundDeI

; 283  : 		return;

	jmp	SHORT $LN2@AuSoundDeI
$LN1@AuSoundDeI:

; 284  : 	registered_dev->stop_output_stream();

	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+48]
$LN2@AuSoundDeI:

; 285  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuSoundDeInitialize@@YAXXZ ENDP			; AuSoundDeInitialize
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
?AuSoundStart@@YAXXZ PROC				; AuSoundStart

; 275  : void AuSoundStart() {

$LN4:
	sub	rsp, 40					; 00000028H

; 276  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundSta

; 277  : 		return;

	jmp	SHORT $LN2@AuSoundSta
$LN1@AuSoundSta:

; 278  : 	registered_dev->start_output_stream();

	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+56]
$LN2@AuSoundSta:

; 279  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuSoundStart@@YAXXZ ENDP				; AuSoundStart
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
i$1 = 32
i$2 = 36
i$3 = 40
i$4 = 44
i$5 = 48
hw_buffer$ = 56
dsp$6 = 64
dsp$7 = 72
data_bu$8 = 80
buff$ = 88
buffer$ = 112
AuSoundRequestNext PROC

; 236  : void AuSoundRequestNext (uint64_t *buffer) {

$LN25:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 237  : 	if (dsp_first == NULL)

	cmp	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first
	jne	SHORT $LN22@AuSoundReq

; 238  : 		return;

	jmp	$LN23@AuSoundReq
$LN22@AuSoundReq:

; 239  : 	int16_t* hw_buffer = (int16_t*)(buffer);

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR hw_buffer$[rsp], rax

; 240  : 
; 241  : 	for (int i = 0; i < BUFF_SIZE /sizeof(int16_t); i++)

	mov	DWORD PTR i$4[rsp], 0
	jmp	SHORT $LN21@AuSoundReq
$LN20@AuSoundReq:
	mov	eax, DWORD PTR i$4[rsp]
	inc	eax
	mov	DWORD PTR i$4[rsp], eax
$LN21@AuSoundReq:
	movsxd	rax, DWORD PTR i$4[rsp]
	cmp	rax, 2048				; 00000800H
	jae	SHORT $LN19@AuSoundReq

; 242  : 		hw_buffer[i] = 0;

	movsxd	rax, DWORD PTR i$4[rsp]
	xor	ecx, ecx
	mov	rdx, QWORD PTR hw_buffer$[rsp]
	mov	WORD PTR [rdx+rax*2], cx
	jmp	SHORT $LN20@AuSoundReq
$LN19@AuSoundReq:

; 243  : 	
; 244  : 
; 245  : 	uint8_t *buff = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 1
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buff$[rsp], rax

; 246  : 
; 247  : 	for (dsp_t *dsp = dsp_last; dsp != NULL; dsp = dsp->prev) {

	mov	rax, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	mov	QWORD PTR dsp$7[rsp], rax
	jmp	SHORT $LN18@AuSoundReq
$LN17@AuSoundReq:
	mov	rax, QWORD PTR dsp$7[rsp]
	mov	rax, QWORD PTR [rax+48]
	mov	QWORD PTR dsp$7[rsp], rax
$LN18@AuSoundReq:
	cmp	QWORD PTR dsp$7[rsp], 0
	je	$LN16@AuSoundReq

; 248  : 
; 249  : 		for (int i = 0; i < BUFF_SIZE; i++)

	mov	DWORD PTR i$5[rsp], 0
	jmp	SHORT $LN15@AuSoundReq
$LN14@AuSoundReq:
	mov	eax, DWORD PTR i$5[rsp]
	inc	eax
	mov	DWORD PTR i$5[rsp], eax
$LN15@AuSoundReq:
	cmp	DWORD PTR i$5[rsp], 4096		; 00001000H
	jge	SHORT $LN13@AuSoundReq

; 250  : 			circular_buf_get(dsp->buffer,buff);

	mov	rdx, QWORD PTR buff$[rsp]
	mov	rax, QWORD PTR dsp$7[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z ; circular_buf_get
	jmp	SHORT $LN14@AuSoundReq
$LN13@AuSoundReq:

; 251  : 		
; 252  : 		int16_t *data_bu = (int16_t*)buff;

	mov	rax, QWORD PTR buff$[rsp]
	mov	QWORD PTR data_bu$8[rsp], rax

; 253  : 
; 254  : 		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN12@AuSoundReq
$LN11@AuSoundReq:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN12@AuSoundReq:
	movsxd	rax, DWORD PTR i$2[rsp]
	cmp	rax, 2048				; 00000800H
	jae	SHORT $LN10@AuSoundReq

; 255  : 			data_bu[i] /= 2;

	movsxd	rax, DWORD PTR i$2[rsp]
	mov	rcx, QWORD PTR data_bu$8[rsp]
	movsx	eax, WORD PTR [rcx+rax*2]
	cdq
	sub	eax, edx
	sar	eax, 1
	movsxd	rcx, DWORD PTR i$2[rsp]
	mov	rdx, QWORD PTR data_bu$8[rsp]
	mov	WORD PTR [rdx+rcx*2], ax
	jmp	SHORT $LN11@AuSoundReq
$LN10@AuSoundReq:

; 256  : 
; 257  : 		for (int i = 0; i < BUFF_SIZE /sizeof(int16_t); i++){

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN9@AuSoundReq
$LN8@AuSoundReq:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN9@AuSoundReq:
	movsxd	rax, DWORD PTR i$1[rsp]
	cmp	rax, 2048				; 00000800H
	jae	SHORT $LN7@AuSoundReq

; 258  : 			hw_buffer[i] += data_bu[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR data_bu$8[rsp]
	movsx	ecx, WORD PTR [rdx+rcx*2]
	mov	rdx, QWORD PTR hw_buffer$[rsp]
	movsx	eax, WORD PTR [rdx+rax*2]
	add	eax, ecx
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR hw_buffer$[rsp]
	mov	WORD PTR [rdx+rcx*2], ax

; 259  : 		}

	jmp	SHORT $LN8@AuSoundReq
$LN7@AuSoundReq:

; 260  : 
; 261  : 	}

	jmp	$LN17@AuSoundReq
$LN16@AuSoundReq:

; 262  : 
; 263  : 
; 264  : 	for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++)

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN6@AuSoundReq
$LN5@AuSoundReq:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN6@AuSoundReq:
	movsxd	rax, DWORD PTR i$3[rsp]
	cmp	rax, 2048				; 00000800H
	jae	SHORT $LN4@AuSoundReq

; 265  : 		hw_buffer[i] /= 2;

	movsxd	rax, DWORD PTR i$3[rsp]
	mov	rcx, QWORD PTR hw_buffer$[rsp]
	movsx	eax, WORD PTR [rcx+rax*2]
	cdq
	sub	eax, edx
	sar	eax, 1
	movsxd	rcx, DWORD PTR i$3[rsp]
	mov	rdx, QWORD PTR hw_buffer$[rsp]
	mov	WORD PTR [rdx+rcx*2], ax
	jmp	SHORT $LN5@AuSoundReq
$LN4@AuSoundReq:

; 266  : 
; 267  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	mov	QWORD PTR dsp$6[rsp], rax
	jmp	SHORT $LN3@AuSoundReq
$LN2@AuSoundReq:
	mov	rax, QWORD PTR dsp$6[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR dsp$6[rsp], rax
$LN3@AuSoundReq:
	cmp	QWORD PTR dsp$6[rsp], 0
	je	SHORT $LN1@AuSoundReq

; 268  : 		AuRequestNextBlock(dsp->id);

	mov	rax, QWORD PTR dsp$6[rsp]
	movzx	ecx, WORD PTR [rax+8]
	call	?AuRequestNextBlock@@YAXG@Z		; AuRequestNextBlock

; 269  : 	}

	jmp	SHORT $LN2@AuSoundReq
$LN1@AuSoundReq:

; 270  : 
; 271  : 	AuPmmngrFreeBlocks((void*)v2p((size_t)buff),BUFF_SIZE/4096);

	mov	rcx, QWORD PTR buff$[rsp]
	call	v2p
	mov	edx, 1
	mov	rcx, rax
	call	AuPmmngrFreeBlocks
$LN23@AuSoundReq:

; 272  : }

	add	rsp, 104				; 00000068H
	ret	0
AuSoundRequestNext ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dev$ = 8
AuSoundRegisterDevice PROC

; 229  : void AuSoundRegisterDevice(sound_t * dev) {

	mov	QWORD PTR [rsp+8], rcx

; 230  : 	if (registered_dev)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	je	SHORT $LN1@AuSoundReg

; 231  : 		return;

	jmp	SHORT $LN2@AuSoundReg
$LN1@AuSoundReg:

; 232  : 	registered_dev = dev;

	mov	rax, QWORD PTR dev$[rsp]
	mov	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, rax ; registered_dev
$LN2@AuSoundReg:

; 233  : }

	fatret	0
AuSoundRegisterDevice ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 32
?AuSoundInitialize@@YAXXZ PROC				; AuSoundInitialize

; 207  : void AuSoundInitialize () {

$LN3:
	sub	rsp, 56					; 00000038H

; 208  : 	vfs_node_t *dsp = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 112				; 00000070H
	call	malloc
	mov	QWORD PTR dsp$[rsp], rax

; 209  : 	strcpy (dsp->filename, "dsp");

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rdx, OFFSET FLAT:$SG3975
	mov	rcx, rax
	call	strcpy

; 210  : 	dsp->size = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	DWORD PTR [rax+32], 0

; 211  : 	dsp->eof = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	BYTE PTR [rax+36], 0

; 212  : 	dsp->pos = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	DWORD PTR [rax+40], 0

; 213  : 	dsp->current = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	DWORD PTR [rax+44], 0

; 214  : 	dsp->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	BYTE PTR [rax+48], 12

; 215  : 	dsp->status = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	BYTE PTR [rax+49], 0

; 216  : 	dsp->open = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+64], 0

; 217  : 	dsp->read = AuSoundRead;

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:?AuSoundRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z ; AuSoundRead
	mov	QWORD PTR [rax+72], rcx

; 218  : 	dsp->write = AuFileWrite;

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z ; AuFileWrite
	mov	QWORD PTR [rax+80], rcx

; 219  : 	dsp->read_blk = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+96], 0

; 220  : 	dsp->ioquery = AuSoundIOQuery;

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z ; AuSoundIOQuery
	mov	QWORD PTR [rax+104], rcx

; 221  : 	vfs_mount ("/dev/dsp", dsp, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:$SG3976
	call	vfs_mount

; 222  : 
; 223  : 	dsp_first = NULL;

	mov	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first

; 224  : 	dsp_last = NULL;

	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, 0	; dsp_last

; 225  : 	_audio_started_ = false;

	mov	BYTE PTR ?_audio_started_@@3_NA, 0	; _audio_started_

; 226  : 	_audio_stoped_ = false;

	mov	BYTE PTR ?_audio_stoped_@@3_NA, 0	; _audio_stoped_

; 227  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuSoundInitialize@@YAXXZ ENDP				; AuSoundInitialize
_TEXT	ENDS
END
