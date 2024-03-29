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
$SG4020	DB	'dsp', 00H
	ORG $+4
$SG4021	DB	'/dev/dsp', 00H
CONST	ENDS
PUBLIC	?AuSoundInitialize@@YAXXZ			; AuSoundInitialize
PUBLIC	AuSoundRegisterDevice
PUBLIC	AuSoundRequestNext
PUBLIC	?AuSoundStart@@YAXXZ				; AuSoundStart
PUBLIC	?AuSoundStop@@YAXXZ				; AuSoundStop
PUBLIC	?AuSoundDeInitialize@@YAXXZ			; AuSoundDeInitialize
PUBLIC	?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z	; AuSoundWrite
PUBLIC	?AuSoundDestroyDSP@@YAXG@Z			; AuSoundDestroyDSP
PUBLIC	?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z		; AuSoundAddDSP
PUBLIC	?AuRemoveDSP@@YAXPEAU_dsp_@@@Z			; AuRemoveDSP
PUBLIC	?AuRequestNextBlock@@YAXG@Z			; AuRequestNextBlock
PUBLIC	?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z		; AuSoundGetDSP
PUBLIC	?AuSoundRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z	; AuSoundRead
PUBLIC	?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z	; AuSoundIOQuery
PUBLIC	?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z	; AuFileWrite
EXTRN	strcpy:PROC
EXTRN	memset:PROC
EXTRN	vfs_mount:PROC
EXTRN	AuPmmngrAllocBlocks:PROC
EXTRN	AuPmmngrFreeBlocks:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	x64_cli:PROC
EXTRN	malloc:PROC
EXTRN	free:PROC
EXTRN	block_thread:PROC
EXTRN	get_current_thread:PROC
EXTRN	force_sched:PROC
EXTRN	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z:PROC	; circ_buf_init
EXTRN	?circ_buf_free@@YAXPEAU_circ_buf_@@@Z:PROC	; circ_buf_free
EXTRN	?circular_buf_put2@@YAHPEAU_circ_buf_@@E@Z:PROC	; circular_buf_put2
EXTRN	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z:PROC ; circular_buf_get
EXTRN	?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z:PROC	; circular_buf_full
EXTRN	?pri_put_message@@YAXPEAU_pri_event_@@@Z:PROC	; pri_put_message
pdata	SEGMENT
$pdata$?AuSoundInitialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+354
	DD	imagerel $unwind$?AuSoundInitialize@@YAXXZ
$pdata$AuSoundRequestNext DD imagerel $LN25
	DD	imagerel $LN25+508
	DD	imagerel $unwind$AuSoundRequestNext
$pdata$?AuSoundStart@@YAXXZ DD imagerel $LN4
	DD	imagerel $LN4+31
	DD	imagerel $unwind$?AuSoundStart@@YAXXZ
$pdata$?AuSoundStop@@YAXXZ DD imagerel $LN4
	DD	imagerel $LN4+31
	DD	imagerel $unwind$?AuSoundStop@@YAXXZ
$pdata$?AuSoundDeInitialize@@YAXXZ DD imagerel $LN4
	DD	imagerel $LN4+31
	DD	imagerel $unwind$?AuSoundDeInitialize@@YAXXZ
$pdata$?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z DD imagerel $LN13
	DD	imagerel $LN13+320
	DD	imagerel $unwind$?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z
$pdata$?AuSoundDestroyDSP@@YAXG@Z DD imagerel $LN8
	DD	imagerel $LN8+163
	DD	imagerel $unwind$?AuSoundDestroyDSP@@YAXG@Z
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
	DD	08204H
$unwind$AuSoundRequestNext DD 010901H
	DD	0c209H
$unwind$?AuSoundStart@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuSoundStop@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuSoundDeInitialize@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z DD 011301H
	DD	0a213H
$unwind$?AuSoundDestroyDSP@@YAXG@Z DD 010901H
	DD	06209H
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

; 199  : void AuFileWrite (vfs_node_t* node, uint64_t *buffer, uint32_t length) {

$LN7:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 200  : 	x64_cli();

	call	x64_cli

; 201  : 	dsp_t *dsp = AuSoundGetDSP(get_current_thread()->id);

	call	get_current_thread
	movzx	ecx, WORD PTR [rax+238]
	call	?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z	; AuSoundGetDSP
	mov	QWORD PTR dsp$[rsp], rax

; 202  : 	uint8_t* al = (uint8_t*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR al$[rsp], rax

; 203  : 	uint8_t* aligned_buffer = (uint8_t*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR aligned_buffer$[rsp], rax

; 204  : 	if (circular_buf_full(dsp->buffer)) {

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z ; circular_buf_full
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN4@AuFileWrit

; 205  : 		dsp->blocked_thr = get_current_thread();

	call	get_current_thread
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rcx+24], rax

; 206  : 		block_thread(get_current_thread());

	call	get_current_thread
	mov	rcx, rax
	call	block_thread

; 207  : 		force_sched();

	call	force_sched
$LN4@AuFileWrit:

; 208  : 	}
; 209  : 	for (int i = 0; i < BUFF_SIZE; i++) 

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuFileWrit
$LN2@AuFileWrit:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuFileWrit:
	cmp	DWORD PTR i$1[rsp], 4096		; 00001000H
	jge	SHORT $LN1@AuFileWrit

; 210  : 		circular_buf_put2(dsp->buffer, aligned_buffer[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR aligned_buffer$[rsp]
	movzx	edx, BYTE PTR [rcx+rax]
	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_put2@@YAHPEAU_circ_buf_@@E@Z ; circular_buf_put2
	jmp	SHORT $LN2@AuFileWrit
$LN1@AuFileWrit:

; 211  : 	
; 212  : }

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

; 158  : int AuSoundIOQuery (vfs_node_t *node, int code, void* arg) {

$LN13:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 159  : 	x64_cli();

	call	x64_cli

; 160  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN10@AuSoundIOQ

; 161  : 		return 1;

	mov	eax, 1
	jmp	$LN11@AuSoundIOQ
$LN10@AuSoundIOQ:

; 162  : 
; 163  : 	switch (code)

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv65[rsp], eax
	cmp	DWORD PTR tv65[rsp], 100		; 00000064H
	je	SHORT $LN7@AuSoundIOQ
	cmp	DWORD PTR tv65[rsp], 106		; 0000006aH
	je	$LN2@AuSoundIOQ
	jmp	$LN8@AuSoundIOQ
$LN7@AuSoundIOQ:

; 164  : 	{
; 165  : 	case SOUND_REGISTER_MEDIAPLAYER:{
; 166  : 		registered_thr = get_current_thread();

	call	get_current_thread
	mov	QWORD PTR ?registered_thr@@3PEAU_thread_@@EA, rax ; registered_thr

; 167  : 		dsp_t *dsp = (dsp_t*)malloc(sizeof(dsp_t));

	mov	ecx, 56					; 00000038H
	call	malloc
	mov	QWORD PTR dsp$1[rsp], rax

; 168  : 		uint8_t* buffer = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 1
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buffer$2[rsp], rax

; 169  : 		dsp->buffer = circ_buf_init(buffer, BUFF_SIZE); //(uint8_t*)

	mov	edx, 4096				; 00001000H
	mov	rcx, QWORD PTR buffer$2[rsp]
	call	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z ; circ_buf_init
	mov	rcx, QWORD PTR dsp$1[rsp]
	mov	QWORD PTR [rcx], rax

; 170  : 		dsp->id = get_current_thread()->id;

	call	get_current_thread
	mov	rcx, QWORD PTR dsp$1[rsp]
	movzx	eax, WORD PTR [rax+238]
	mov	WORD PTR [rcx+8], ax

; 171  : 		dsp->registered_thr = get_current_thread();

	call	get_current_thread
	mov	rcx, QWORD PTR dsp$1[rsp]
	mov	QWORD PTR [rcx+16], rax

; 172  : 		AuSoundAddDSP(dsp);

	mov	rcx, QWORD PTR dsp$1[rsp]
	call	?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z	; AuSoundAddDSP

; 173  : 		break;

	jmp	SHORT $LN8@AuSoundIOQ

; 174  : 	}
; 175  : 	case SOUND_START_OUTPUT:{
; 176  : 		/* This Code should be removed */
; 177  : 		break;

	jmp	SHORT $LN8@AuSoundIOQ

; 178  : 	}
; 179  : 	case SOUND_STOP_OUTPUT:{
; 180  : 		/* This Code should be removed */
; 181  : 		break;

	jmp	SHORT $LN8@AuSoundIOQ

; 182  : 						   }
; 183  : 	case SOUND_START_INPUT: //Not implemented
; 184  : 		break;

	jmp	SHORT $LN8@AuSoundIOQ

; 185  : 	case SOUND_STOP_INPUT:
; 186  : 		break;  //Not implemented

	jmp	SHORT $LN8@AuSoundIOQ
$LN2@AuSoundIOQ:

; 187  : 	case SOUND_SET_VOLUME: {
; 188  : 		if (!registered_dev)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundIOQ

; 189  : 			return -1;

	mov	eax, -1
	jmp	SHORT $LN11@AuSoundIOQ
$LN1@AuSoundIOQ:

; 190  : 		au_sound_callback_t *callbk = (au_sound_callback_t*)arg;

	mov	rax, QWORD PTR arg$[rsp]
	mov	QWORD PTR callbk$3[rsp], rax

; 191  : 		registered_dev->set_volume(callbk->uchar_1);

	mov	rax, QWORD PTR callbk$3[rsp]
	movzx	ecx, BYTE PTR [rax]
	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+64]
$LN8@AuSoundIOQ:

; 192  : 		break;
; 193  : 	}	
; 194  : 	}
; 195  : 
; 196  : 	return 0;

	xor	eax, eax
$LN11@AuSoundIOQ:

; 197  : }

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

; 121  : size_t AuSoundRead (vfs_node_t *file, uint64_t* buffer, uint32_t length) {

	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 122  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundRea

; 123  : 		return -1;

	mov	rax, -1
	jmp	SHORT $LN2@AuSoundRea
$LN1@AuSoundRea:

; 124  : 	return 0;

	xor	eax, eax
$LN2@AuSoundRea:

; 125  : }

	fatret	0
?AuSoundRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z ENDP		; AuSoundRead
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$1 = 0
id$ = 32
?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z PROC			; AuSoundGetDSP

; 111  : dsp_t* AuSoundGetDSP(uint16_t id) {

$LN7:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 24

; 112  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

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

; 113  : 		if (dsp->id == id)

	mov	rax, QWORD PTR dsp$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN1@AuSoundGet

; 114  : 			return dsp;

	mov	rax, QWORD PTR dsp$1[rsp]
	jmp	SHORT $LN5@AuSoundGet
$LN1@AuSoundGet:

; 115  : 	}

	jmp	SHORT $LN3@AuSoundGet
$LN2@AuSoundGet:

; 116  : 
; 117  : 	return NULL;

	xor	eax, eax
$LN5@AuSoundGet:

; 118  : }

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

; 92   : void AuRequestNextBlock(uint16_t id) {

$LN3:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 216				; 000000d8H

; 93   : 	pri_event_t e;
; 94   : 	e.to_id = id;

	movzx	eax, BYTE PTR id$[rsp]
	mov	BYTE PTR e$[rsp+1], al

; 95   : 	e.from_id = 0;

	mov	BYTE PTR e$[rsp+2], 0

; 96   : 	e.type = 10;

	mov	BYTE PTR e$[rsp], 10

; 97   : 	pri_put_message(&e);

	lea	rcx, QWORD PTR e$[rsp]
	call	?pri_put_message@@YAXPEAU_pri_event_@@@Z ; pri_put_message

; 98   : 	//thread_t *t = thread_iterate_ready_list(id);
; 99   : 	//if (t == NULL)
; 100  : 	//	t = thread_iterate_block_list(id);
; 101  : 
; 102  : 	//if (t->state == THREAD_STATE_BLOCKED)
; 103  : 	//	unblock_thread(t);
; 104  : }

	add	rsp, 216				; 000000d8H
	ret	0
?AuRequestNextBlock@@YAXG@Z ENDP			; AuRequestNextBlock
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 8
?AuRemoveDSP@@YAXPEAU_dsp_@@@Z PROC			; AuRemoveDSP

; 74   : void AuRemoveDSP(dsp_t *dsp) {

	mov	QWORD PTR [rsp+8], rcx

; 75   : 	if (dsp_first == NULL)

	cmp	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first
	jne	SHORT $LN5@AuRemoveDS

; 76   : 		return;

	jmp	SHORT $LN6@AuRemoveDS
$LN5@AuRemoveDS:

; 77   : 
; 78   : 	if (dsp == dsp_first) {

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	cmp	QWORD PTR dsp$[rsp], rax
	jne	SHORT $LN4@AuRemoveDS

; 79   : 		dsp_first = dsp_first->next;

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, rax ; dsp_first

; 80   : 	} else {

	jmp	SHORT $LN3@AuRemoveDS
$LN4@AuRemoveDS:

; 81   : 		dsp->prev->next = dsp->next;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+48]
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rcx+40]
	mov	QWORD PTR [rax+40], rcx
$LN3@AuRemoveDS:

; 82   : 	}
; 83   : 
; 84   : 	if (dsp == dsp_last) {

	mov	rax, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	cmp	QWORD PTR dsp$[rsp], rax
	jne	SHORT $LN2@AuRemoveDS

; 85   : 		dsp_last = dsp->prev;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+48]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last

; 86   : 	} else {

	jmp	SHORT $LN1@AuRemoveDS
$LN2@AuRemoveDS:

; 87   : 		dsp->next->prev = dsp->prev;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rcx+48]
	mov	QWORD PTR [rax+48], rcx
$LN1@AuRemoveDS:
$LN6@AuRemoveDS:

; 88   : 	}
; 89   : 
; 90   : }

	fatret	0
?AuRemoveDSP@@YAXPEAU_dsp_@@@Z ENDP			; AuRemoveDSP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 8
?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z PROC			; AuSoundAddDSP

; 57   : void AuSoundAddDSP(dsp_t *dsp) {

	mov	QWORD PTR [rsp+8], rcx

; 58   : 	dsp->next = NULL;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+40], 0

; 59   : 	dsp->prev = NULL;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+48], 0

; 60   : 	if (dsp_first == NULL) {

	cmp	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first
	jne	SHORT $LN2@AuSoundAdd

; 61   : 		dsp_first = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, rax ; dsp_first

; 62   : 		dsp_last = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last

; 63   : 	}else {

	jmp	SHORT $LN1@AuSoundAdd
$LN2@AuSoundAdd:

; 64   : 		dsp_last->next = dsp;

	mov	rax, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+40], rcx

; 65   : 		dsp->prev = dsp_last;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	mov	QWORD PTR [rax+48], rcx

; 66   : 		dsp_last = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last
$LN1@AuSoundAdd:

; 67   : 	}
; 68   : }

	fatret	0
?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z ENDP			; AuSoundAddDSP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
target_dsp$ = 32
dsp$1 = 40
id$ = 64
?AuSoundDestroyDSP@@YAXG@Z PROC				; AuSoundDestroyDSP

; 334  : void AuSoundDestroyDSP(uint16_t id) {

$LN8:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 56					; 00000038H

; 335  : 	dsp_t* target_dsp = NULL;

	mov	QWORD PTR target_dsp$[rsp], 0

; 336  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	mov	QWORD PTR dsp$1[rsp], rax
	jmp	SHORT $LN5@AuSoundDes
$LN4@AuSoundDes:
	mov	rax, QWORD PTR dsp$1[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR dsp$1[rsp], rax
$LN5@AuSoundDes:
	cmp	QWORD PTR dsp$1[rsp], 0
	je	SHORT $LN3@AuSoundDes

; 337  : 		if (dsp->id == id) {

	mov	rax, QWORD PTR dsp$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN2@AuSoundDes

; 338  : 			target_dsp = dsp;

	mov	rax, QWORD PTR dsp$1[rsp]
	mov	QWORD PTR target_dsp$[rsp], rax

; 339  : 			break;

	jmp	SHORT $LN3@AuSoundDes
$LN2@AuSoundDes:

; 340  : 		}
; 341  : 	}

	jmp	SHORT $LN4@AuSoundDes
$LN3@AuSoundDes:

; 342  : 
; 343  : 	if (target_dsp == NULL)

	cmp	QWORD PTR target_dsp$[rsp], 0
	jne	SHORT $LN1@AuSoundDes

; 344  : 		return;

	jmp	SHORT $LN6@AuSoundDes
$LN1@AuSoundDes:

; 345  : 
; 346  : 
; 347  : 	AuPmmngrFreeBlocks((void*)v2p((uint64_t)target_dsp->buffer->buffer),
; 348  : 		BUFF_SIZE/4096);

	mov	rax, QWORD PTR target_dsp$[rsp]
	mov	rax, QWORD PTR [rax]
	mov	rcx, QWORD PTR [rax]
	call	v2p
	mov	edx, 1
	mov	rcx, rax
	call	AuPmmngrFreeBlocks

; 349  : 
; 350  : 	circ_buf_free(target_dsp->buffer);

	mov	rax, QWORD PTR target_dsp$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circ_buf_free@@YAXPEAU_circ_buf_@@@Z	; circ_buf_free

; 351  : 	AuRemoveDSP(target_dsp);

	mov	rcx, QWORD PTR target_dsp$[rsp]
	call	?AuRemoveDSP@@YAXPEAU_dsp_@@@Z		; AuRemoveDSP

; 352  : 	free(target_dsp);

	mov	rcx, QWORD PTR target_dsp$[rsp]
	call	free
$LN6@AuSoundDes:

; 353  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuSoundDestroyDSP@@YAXG@Z ENDP				; AuSoundDestroyDSP
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

; 133  : void AuSoundWrite (vfs_node_t *file, uint8_t* buffer, uint32_t length) {

$LN13:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 134  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN10@AuSoundWri

; 135  : 		return;

	jmp	$LN11@AuSoundWri
$LN10@AuSoundWri:

; 136  : 	int16_t* tmp_buffer = (int16_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 1
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR tmp_buffer$[rsp], rax

; 137  : 	uint8_t* buff = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 1
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buff$[rsp], rax

; 138  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

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

; 139  : 
; 140  : 		for (int i = 0; i < BUFF_SIZE; i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN6@AuSoundWri
$LN5@AuSoundWri:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN6@AuSoundWri:
	cmp	DWORD PTR i$2[rsp], 4096		; 00001000H
	jge	SHORT $LN4@AuSoundWri

; 141  : 			circular_buf_get(dsp->buffer,buff); 

	mov	rdx, QWORD PTR buff$[rsp]
	mov	rax, QWORD PTR dsp$3[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z ; circular_buf_get
	jmp	SHORT $LN5@AuSoundWri
$LN4@AuSoundWri:

; 142  : 
; 143  : 		int16_t* aligned_buff = (int16_t*)buff;

	mov	rax, QWORD PTR buff$[rsp]
	mov	QWORD PTR aligned_buff$4[rsp], rax

; 144  : 		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++) {

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

; 145  : 			tmp_buffer[i] = aligned_buff[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR tmp_buffer$[rsp]
	mov	r8, QWORD PTR aligned_buff$4[rsp]
	movzx	eax, WORD PTR [r8+rax*2]
	mov	WORD PTR [rdx+rcx*2], ax

; 146  : 		}

	jmp	SHORT $LN2@AuSoundWri
$LN1@AuSoundWri:

; 147  : 		//AuRequestNextBlock(dsp->id);
; 148  : 	}

	jmp	$LN8@AuSoundWri
$LN7@AuSoundWri:

; 149  : 	
; 150  : 	registered_dev->write((uint8_t*)tmp_buffer, BUFF_SIZE);

	mov	edx, 4096				; 00001000H
	mov	rcx, QWORD PTR tmp_buffer$[rsp]
	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+32]

; 151  : 	AuPmmngrFreeBlocks((void*)v2p((size_t)buff), BUFF_SIZE/4096);

	mov	rcx, QWORD PTR buff$[rsp]
	call	v2p
	mov	edx, 1
	mov	rcx, rax
	call	AuPmmngrFreeBlocks

; 152  : 	AuPmmngrFreeBlocks((void*)v2p((size_t)tmp_buffer), BUFF_SIZE/4096);

	mov	rcx, QWORD PTR tmp_buffer$[rsp]
	call	v2p
	mov	edx, 1
	mov	rcx, rax
	call	AuPmmngrFreeBlocks
$LN11@AuSoundWri:

; 153  : }

	add	rsp, 88					; 00000058H
	ret	0
?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z ENDP		; AuSoundWrite
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
?AuSoundDeInitialize@@YAXXZ PROC			; AuSoundDeInitialize

; 322  : void AuSoundDeInitialize() {

$LN4:
	sub	rsp, 40					; 00000028H

; 323  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundDeI

; 324  : 		return;

	jmp	SHORT $LN2@AuSoundDeI
$LN1@AuSoundDeI:

; 325  : 	registered_dev->stop_output_stream();

	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+48]
$LN2@AuSoundDeI:

; 326  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuSoundDeInitialize@@YAXXZ ENDP			; AuSoundDeInitialize
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
?AuSoundStop@@YAXXZ PROC				; AuSoundStop

; 313  : void AuSoundStop() {

$LN4:
	sub	rsp, 40					; 00000028H

; 314  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundSto

; 315  : 		return;

	jmp	SHORT $LN2@AuSoundSto
$LN1@AuSoundSto:

; 316  : 	registered_dev->stop_output_stream();

	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+48]
$LN2@AuSoundSto:

; 317  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuSoundStop@@YAXXZ ENDP				; AuSoundStop
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
?AuSoundStart@@YAXXZ PROC				; AuSoundStart

; 304  : void AuSoundStart() {

$LN4:
	sub	rsp, 40					; 00000028H

; 305  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundSta

; 306  : 		return;

	jmp	SHORT $LN2@AuSoundSta
$LN1@AuSoundSta:

; 307  : 	registered_dev->start_output_stream();

	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+56]
$LN2@AuSoundSta:

; 308  : }

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

; 263  : void AuSoundRequestNext (uint64_t *buffer) {

$LN25:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 264  : 	if (dsp_first == NULL)

	cmp	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first
	jne	SHORT $LN22@AuSoundReq

; 265  : 		return;

	jmp	$LN23@AuSoundReq
$LN22@AuSoundReq:

; 266  : 	int16_t* hw_buffer = (int16_t*)(buffer);

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR hw_buffer$[rsp], rax

; 267  : 
; 268  : 	for (int i = 0; i < BUFF_SIZE /sizeof(int16_t); i++)

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

; 269  : 		hw_buffer[i] = 0;

	movsxd	rax, DWORD PTR i$4[rsp]
	xor	ecx, ecx
	mov	rdx, QWORD PTR hw_buffer$[rsp]
	mov	WORD PTR [rdx+rax*2], cx
	jmp	SHORT $LN20@AuSoundReq
$LN19@AuSoundReq:

; 270  : 	
; 271  : 
; 272  : 	uint8_t *buff = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 1
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buff$[rsp], rax

; 273  : 
; 274  : 	for (dsp_t *dsp = dsp_last; dsp != NULL; dsp = dsp->prev) {

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

; 275  : 
; 276  : 		for (int i = 0; i < BUFF_SIZE; i++)

	mov	DWORD PTR i$5[rsp], 0
	jmp	SHORT $LN15@AuSoundReq
$LN14@AuSoundReq:
	mov	eax, DWORD PTR i$5[rsp]
	inc	eax
	mov	DWORD PTR i$5[rsp], eax
$LN15@AuSoundReq:
	cmp	DWORD PTR i$5[rsp], 4096		; 00001000H
	jge	SHORT $LN13@AuSoundReq

; 277  : 			circular_buf_get(dsp->buffer,buff);

	mov	rdx, QWORD PTR buff$[rsp]
	mov	rax, QWORD PTR dsp$7[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z ; circular_buf_get
	jmp	SHORT $LN14@AuSoundReq
$LN13@AuSoundReq:

; 278  : 		
; 279  : 		int16_t *data_bu = (int16_t*)buff;

	mov	rax, QWORD PTR buff$[rsp]
	mov	QWORD PTR data_bu$8[rsp], rax

; 280  : 
; 281  : 		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++)

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

; 282  : 			data_bu[i] /= 2;

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

; 283  : 
; 284  : 		for (int i = 0; i < BUFF_SIZE /sizeof(int16_t); i++){

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

; 285  : 			hw_buffer[i] += data_bu[i];

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

; 286  : 		}

	jmp	SHORT $LN8@AuSoundReq
$LN7@AuSoundReq:

; 287  : 
; 288  : 	}

	jmp	$LN17@AuSoundReq
$LN16@AuSoundReq:

; 289  : 
; 290  : 
; 291  : 	for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++)

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

; 292  : 		hw_buffer[i] /= 2;

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

; 293  : 
; 294  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

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

; 295  : 		AuRequestNextBlock(dsp->id);

	mov	rax, QWORD PTR dsp$6[rsp]
	movzx	ecx, WORD PTR [rax+8]
	call	?AuRequestNextBlock@@YAXG@Z		; AuRequestNextBlock

; 296  : 	}

	jmp	SHORT $LN2@AuSoundReq
$LN1@AuSoundReq:

; 297  : 
; 298  : 	AuPmmngrFreeBlocks((void*)v2p((size_t)buff),BUFF_SIZE/4096);

	mov	rcx, QWORD PTR buff$[rsp]
	call	v2p
	mov	edx, 1
	mov	rcx, rax
	call	AuPmmngrFreeBlocks
$LN23@AuSoundReq:

; 299  : }

	add	rsp, 104				; 00000068H
	ret	0
AuSoundRequestNext ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dev$ = 8
AuSoundRegisterDevice PROC

; 252  : void AuSoundRegisterDevice(sound_t * dev) {

	mov	QWORD PTR [rsp+8], rcx

; 253  : 	if (registered_dev)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	je	SHORT $LN1@AuSoundReg

; 254  : 		return;

	jmp	SHORT $LN2@AuSoundReg
$LN1@AuSoundReg:

; 255  : 	registered_dev = dev;

	mov	rax, QWORD PTR dev$[rsp]
	mov	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, rax ; registered_dev
$LN2@AuSoundReg:

; 256  : }

	fatret	0
AuSoundRegisterDevice ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 32
dsp_$ = 40
buffer$ = 48
?AuSoundInitialize@@YAXXZ PROC				; AuSoundInitialize

; 217  : void AuSoundInitialize () {

$LN3:
	sub	rsp, 72					; 00000048H

; 218  : 	vfs_node_t *dsp = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 112				; 00000070H
	call	malloc
	mov	QWORD PTR dsp$[rsp], rax

; 219  : 	strcpy (dsp->filename, "dsp");

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rdx, OFFSET FLAT:$SG4020
	mov	rcx, rax
	call	strcpy

; 220  : 	dsp->size = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	DWORD PTR [rax+32], 0

; 221  : 	dsp->eof = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	BYTE PTR [rax+36], 0

; 222  : 	dsp->pos = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	DWORD PTR [rax+40], 0

; 223  : 	dsp->current = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	DWORD PTR [rax+44], 0

; 224  : 	dsp->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	BYTE PTR [rax+48], 12

; 225  : 	dsp->status = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	BYTE PTR [rax+49], 0

; 226  : 	dsp->open = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+64], 0

; 227  : 	dsp->read = AuSoundRead;

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:?AuSoundRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z ; AuSoundRead
	mov	QWORD PTR [rax+72], rcx

; 228  : 	dsp->write = AuFileWrite;

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z ; AuFileWrite
	mov	QWORD PTR [rax+80], rcx

; 229  : 	dsp->read_blk = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+96], 0

; 230  : 	dsp->ioquery = AuSoundIOQuery;

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z ; AuSoundIOQuery
	mov	QWORD PTR [rax+104], rcx

; 231  : 	vfs_mount ("/dev/dsp", dsp, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:$SG4021
	call	vfs_mount

; 232  : 
; 233  : 	dsp_first = NULL;

	mov	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first

; 234  : 	dsp_last = NULL;

	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, 0	; dsp_last

; 235  : 	_audio_started_ = false;

	mov	BYTE PTR ?_audio_started_@@3_NA, 0	; _audio_started_

; 236  : 	_audio_stoped_ = false;

	mov	BYTE PTR ?_audio_stoped_@@3_NA, 0	; _audio_stoped_

; 237  : 
; 238  : 	dsp_t *dsp_ = (dsp_t*)malloc(sizeof(dsp_t));

	mov	ecx, 56					; 00000038H
	call	malloc
	mov	QWORD PTR dsp_$[rsp], rax

; 239  : 	uint8_t* buffer = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 1
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buffer$[rsp], rax

; 240  : 	memset(buffer, 0, BUFF_SIZE);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR buffer$[rsp]
	call	memset

; 241  : 	dsp_->buffer = circ_buf_init(buffer, BUFF_SIZE); //(uint8_t*)

	mov	edx, 4096				; 00001000H
	mov	rcx, QWORD PTR buffer$[rsp]
	call	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z ; circ_buf_init
	mov	rcx, QWORD PTR dsp_$[rsp]
	mov	QWORD PTR [rcx], rax

; 242  : 	dsp_->id = KERNEL_DSP_ID;

	mov	eax, 65534				; 0000fffeH
	mov	rcx, QWORD PTR dsp_$[rsp]
	mov	WORD PTR [rcx+8], ax

; 243  : 	dsp_->registered_thr = get_current_thread();

	call	get_current_thread
	mov	rcx, QWORD PTR dsp_$[rsp]
	mov	QWORD PTR [rcx+16], rax

; 244  : 	AuSoundAddDSP(dsp_);

	mov	rcx, QWORD PTR dsp_$[rsp]
	call	?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z	; AuSoundAddDSP

; 245  : }

	add	rsp, 72					; 00000048H
	ret	0
?AuSoundInitialize@@YAXXZ ENDP				; AuSoundInitialize
_TEXT	ENDS
END
