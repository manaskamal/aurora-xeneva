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
_BSS	SEGMENT
?registered_dev@@3PEAU_sound_@@EA DQ 01H DUP (?)	; registered_dev
?registered_thr@@3PEAU_thread_@@EA DQ 01H DUP (?)	; registered_thr
?next_pos@@3IA DD 01H DUP (?)				; next_pos
	ALIGN	8

?data_buff@@3PEAEEA DQ 01H DUP (?)			; data_buff
?dsp_first@@3PEAU_dsp_@@EA DQ 01H DUP (?)		; dsp_first
?dsp_last@@3PEAU_dsp_@@EA DQ 01H DUP (?)		; dsp_last
_BSS	ENDS
CONST	SEGMENT
$SG3882	DB	'dsp', 00H
	ORG $+4
$SG3883	DB	'/dev/dsp', 00H
CONST	ENDS
PUBLIC	?AuSoundInitialize@@YAXXZ			; AuSoundInitialize
PUBLIC	AuSoundRegisterDevice
PUBLIC	AuSoundRequestNext
PUBLIC	?AuSoundOutputStart@@YAXXZ			; AuSoundOutputStart
PUBLIC	?AuSoundOutputStop@@YAXXZ			; AuSoundOutputStop
PUBLIC	?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z	; AuSoundWrite
PUBLIC	?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z		; AuSoundAddDSP
PUBLIC	?AuRemoveDSP@@YAXPEAU_dsp_@@@Z			; AuRemoveDSP
PUBLIC	?AuRequestNextBlock@@YAXG@Z			; AuRequestNextBlock
PUBLIC	?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z		; AuSoundGetDSP
PUBLIC	?AuSoundRead@@YAXPEAU_vfs_node_@@PEA_KI@Z	; AuSoundRead
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
EXTRN	?unblock_thread@@YAXPEAU_thread_@@@Z:PROC	; unblock_thread
EXTRN	get_current_thread:PROC
EXTRN	force_sched:PROC
EXTRN	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z:PROC ; thread_iterate_ready_list
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
EXTRN	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z:PROC	; circ_buf_init
EXTRN	?circular_buf_put2@@YAHPEAU_circ_buf_@@E@Z:PROC	; circular_buf_put2
EXTRN	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z:PROC ; circular_buf_get
EXTRN	?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z:PROC	; circular_buf_full
pdata	SEGMENT
$pdata$?AuSoundInitialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+223
	DD	imagerel $unwind$?AuSoundInitialize@@YAXXZ
$pdata$AuSoundRequestNext DD imagerel $LN21
	DD	imagerel $LN21+410
	DD	imagerel $unwind$AuSoundRequestNext
$pdata$?AuSoundOutputStart@@YAXXZ DD imagerel $LN4
	DD	imagerel $LN4+31
	DD	imagerel $unwind$?AuSoundOutputStart@@YAXXZ
$pdata$?AuSoundOutputStop@@YAXXZ DD imagerel $LN4
	DD	imagerel $LN4+31
	DD	imagerel $unwind$?AuSoundOutputStop@@YAXXZ
$pdata$?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z DD imagerel $LN13
	DD	imagerel $LN13+334
	DD	imagerel $unwind$?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z
$pdata$?AuRequestNextBlock@@YAXG@Z DD imagerel $LN5
	DD	imagerel $LN5+81
	DD	imagerel $unwind$?AuRequestNextBlock@@YAXG@Z
$pdata$?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z DD imagerel $LN7
	DD	imagerel $LN7+73
	DD	imagerel $unwind$?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z
$pdata$?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN11
	DD	imagerel $LN11+234
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
$unwind$?AuSoundOutputStart@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuSoundOutputStop@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z DD 011301H
	DD	0a213H
$unwind$?AuRequestNextBlock@@YAXG@Z DD 010901H
	DD	06209H
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

; 183  : void AuFileWrite (vfs_node_t* node, uint64_t *buffer, uint32_t length) {

$LN7:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 184  : 	x64_cli();

	call	x64_cli

; 185  : 	dsp_t *dsp = AuSoundGetDSP(get_current_thread()->id);

	call	get_current_thread
	movzx	ecx, WORD PTR [rax+234]
	call	?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z	; AuSoundGetDSP
	mov	QWORD PTR dsp$[rsp], rax

; 186  : 	uint8_t* al = (uint8_t*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR al$[rsp], rax

; 187  : 	uint8_t* aligned_buffer = (uint8_t*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR aligned_buffer$[rsp], rax

; 188  : 	if (circular_buf_full(dsp->buffer)) {

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_full@@YA_NPEAU_circ_buf_@@@Z ; circular_buf_full
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN4@AuFileWrit

; 189  : 		dsp->blocked_thr = get_current_thread();

	call	get_current_thread
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rcx+24], rax

; 190  : 		block_thread(get_current_thread());

	call	get_current_thread
	mov	rcx, rax
	call	?block_thread@@YAXPEAU_thread_@@@Z	; block_thread

; 191  : 		force_sched();

	call	force_sched
$LN4@AuFileWrit:

; 192  : 	}
; 193  : 	for (int i = 0; i < BUFF_SIZE; i++) 

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuFileWrit
$LN2@AuFileWrit:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuFileWrit:
	cmp	DWORD PTR i$1[rsp], 8192		; 00002000H
	jge	SHORT $LN1@AuFileWrit

; 194  : 		circular_buf_put2(dsp->buffer, aligned_buffer[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR aligned_buffer$[rsp]
	movzx	edx, BYTE PTR [rcx+rax]
	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_put2@@YAHPEAU_circ_buf_@@E@Z ; circular_buf_put2
	jmp	SHORT $LN2@AuFileWrit
$LN1@AuFileWrit:

; 195  : 	
; 196  : }

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
node$ = 80
code$ = 88
arg$ = 96
?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z PROC	; AuSoundIOQuery

; 149  : int AuSoundIOQuery (vfs_node_t *node, int code, void* arg) {

$LN11:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 150  : 	x64_cli();

	call	x64_cli

; 151  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN8@AuSoundIOQ

; 152  : 		return 1;

	mov	eax, 1
	jmp	$LN9@AuSoundIOQ
$LN8@AuSoundIOQ:

; 153  : 
; 154  : 	switch (code)

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv65[rsp], eax
	cmp	DWORD PTR tv65[rsp], 100		; 00000064H
	je	SHORT $LN5@AuSoundIOQ
	cmp	DWORD PTR tv65[rsp], 102		; 00000066H
	je	$LN4@AuSoundIOQ
	cmp	DWORD PTR tv65[rsp], 103		; 00000067H
	je	$LN3@AuSoundIOQ
	jmp	$LN6@AuSoundIOQ
$LN5@AuSoundIOQ:

; 155  : 	{
; 156  : 	case SOUND_REGISTER_MEDIAPLAYER:{
; 157  : 		registered_thr = get_current_thread();

	call	get_current_thread
	mov	QWORD PTR ?registered_thr@@3PEAU_thread_@@EA, rax ; registered_thr

; 158  : 		dsp_t *dsp = (dsp_t*)malloc(sizeof(dsp_t));

	mov	ecx, 56					; 00000038H
	call	malloc
	mov	QWORD PTR dsp$1[rsp], rax

; 159  : 		uint8_t* buffer = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 2
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buffer$2[rsp], rax

; 160  : 		dsp->buffer = circ_buf_init(buffer, BUFF_SIZE); //(uint8_t*)

	mov	edx, 8192				; 00002000H
	mov	rcx, QWORD PTR buffer$2[rsp]
	call	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z ; circ_buf_init
	mov	rcx, QWORD PTR dsp$1[rsp]
	mov	QWORD PTR [rcx], rax

; 161  : 		dsp->id = get_current_thread()->id;

	call	get_current_thread
	mov	rcx, QWORD PTR dsp$1[rsp]
	movzx	eax, WORD PTR [rax+234]
	mov	WORD PTR [rcx+8], ax

; 162  : 		dsp->registered_thr = get_current_thread();

	call	get_current_thread
	mov	rcx, QWORD PTR dsp$1[rsp]
	mov	QWORD PTR [rcx+16], rax

; 163  : 		AuSoundAddDSP(dsp);

	mov	rcx, QWORD PTR dsp$1[rsp]
	call	?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z	; AuSoundAddDSP

; 164  : 		break;

	jmp	SHORT $LN6@AuSoundIOQ
$LN4@AuSoundIOQ:

; 165  : 	}
; 166  : 	case SOUND_START_OUTPUT:{
; 167  : 		//AuSoundWrite(node,NULL, BUFF_SIZE);
; 168  : 		registered_dev->start_output_stream();

	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+56]

; 169  : 		break;

	jmp	SHORT $LN6@AuSoundIOQ
$LN3@AuSoundIOQ:

; 170  : 	}
; 171  : 	case SOUND_STOP_OUTPUT:
; 172  : 		registered_dev->stop_output_stream();

	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+48]
$LN6@AuSoundIOQ:

; 173  : 		break;
; 174  : 	case SOUND_START_INPUT: //Not implemented
; 175  : 		break;
; 176  : 	case SOUND_STOP_INPUT:
; 177  : 		break;  //Not implemented
; 178  : 	}
; 179  : 
; 180  : 	return 0;

	xor	eax, eax
$LN9@AuSoundIOQ:

; 181  : }

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
?AuSoundRead@@YAXPEAU_vfs_node_@@PEA_KI@Z PROC		; AuSoundRead

; 119  : void AuSoundRead (vfs_node_t *file, uint64_t* buffer, uint32_t length) {

	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 120  : 	if (registered_dev == NULL)
; 121  : 		return;
; 122  : }

	ret	0
?AuSoundRead@@YAXPEAU_vfs_node_@@PEA_KI@Z ENDP		; AuSoundRead
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$1 = 0
id$ = 32
?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z PROC			; AuSoundGetDSP

; 109  : dsp_t* AuSoundGetDSP(uint16_t id) {

$LN7:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 24

; 110  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

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

; 111  : 		if (dsp->id == id)

	mov	rax, QWORD PTR dsp$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN1@AuSoundGet

; 112  : 			return dsp;

	mov	rax, QWORD PTR dsp$1[rsp]
	jmp	SHORT $LN5@AuSoundGet
$LN1@AuSoundGet:

; 113  : 	}

	jmp	SHORT $LN3@AuSoundGet
$LN2@AuSoundGet:

; 114  : 
; 115  : 	return NULL;

	xor	eax, eax
$LN5@AuSoundGet:

; 116  : }

	add	rsp, 24
	ret	0
?AuSoundGetDSP@@YAPEAU_dsp_@@G@Z ENDP			; AuSoundGetDSP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
t$ = 32
id$ = 64
?AuRequestNextBlock@@YAXG@Z PROC			; AuRequestNextBlock

; 90   : void AuRequestNextBlock(uint16_t id) {

$LN5:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 56					; 00000038H

; 91   : 	//pri_event_t e;
; 92   : 	//e.to_id = id;
; 93   : 	//e.from_id = 0;
; 94   : 	//e.type = 10;
; 95   : 	//pri_put_message(&e);
; 96   : 	thread_t *t = thread_iterate_ready_list(id);

	movzx	ecx, WORD PTR id$[rsp]
	call	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ; thread_iterate_ready_list
	mov	QWORD PTR t$[rsp], rax

; 97   : 	if (t == NULL)

	cmp	QWORD PTR t$[rsp], 0
	jne	SHORT $LN2@AuRequestN

; 98   : 		t = thread_iterate_block_list(id);

	movzx	eax, WORD PTR id$[rsp]
	mov	ecx, eax
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR t$[rsp], rax
$LN2@AuRequestN:

; 99   : 
; 100  : 	if (t->state == THREAD_STATE_BLOCKED)

	mov	rax, QWORD PTR t$[rsp]
	movzx	eax, BYTE PTR [rax+232]
	cmp	eax, 3
	jne	SHORT $LN1@AuRequestN

; 101  : 		unblock_thread(t);

	mov	rcx, QWORD PTR t$[rsp]
	call	?unblock_thread@@YAXPEAU_thread_@@@Z	; unblock_thread
$LN1@AuRequestN:

; 102  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuRequestNextBlock@@YAXG@Z ENDP			; AuRequestNextBlock
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 8
?AuRemoveDSP@@YAXPEAU_dsp_@@@Z PROC			; AuRemoveDSP

; 72   : void AuRemoveDSP(dsp_t *dsp) {

	mov	QWORD PTR [rsp+8], rcx

; 73   : 	if (dsp_first == NULL)

	cmp	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first
	jne	SHORT $LN5@AuRemoveDS

; 74   : 		return;

	jmp	SHORT $LN6@AuRemoveDS
$LN5@AuRemoveDS:

; 75   : 
; 76   : 	if (dsp == dsp_first) {

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	cmp	QWORD PTR dsp$[rsp], rax
	jne	SHORT $LN4@AuRemoveDS

; 77   : 		dsp_first = dsp_first->next;

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, rax ; dsp_first

; 78   : 	} else {

	jmp	SHORT $LN3@AuRemoveDS
$LN4@AuRemoveDS:

; 79   : 		dsp->prev->next = dsp->next;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+48]
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rcx+40]
	mov	QWORD PTR [rax+40], rcx
$LN3@AuRemoveDS:

; 80   : 	}
; 81   : 
; 82   : 	if (dsp == dsp_last) {

	mov	rax, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	cmp	QWORD PTR dsp$[rsp], rax
	jne	SHORT $LN2@AuRemoveDS

; 83   : 		dsp_last = dsp->prev;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+48]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last

; 84   : 	} else {

	jmp	SHORT $LN1@AuRemoveDS
$LN2@AuRemoveDS:

; 85   : 		dsp->next->prev = dsp->prev;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rcx+48]
	mov	QWORD PTR [rax+48], rcx
$LN1@AuRemoveDS:
$LN6@AuRemoveDS:

; 86   : 	}
; 87   : 
; 88   : }

	fatret	0
?AuRemoveDSP@@YAXPEAU_dsp_@@@Z ENDP			; AuRemoveDSP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 8
?AuSoundAddDSP@@YAXPEAU_dsp_@@@Z PROC			; AuSoundAddDSP

; 55   : void AuSoundAddDSP(dsp_t *dsp) {

	mov	QWORD PTR [rsp+8], rcx

; 56   : 	dsp->next = NULL;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+40], 0

; 57   : 	dsp->prev = NULL;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+48], 0

; 58   : 	if (dsp_first == NULL) {

	cmp	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first
	jne	SHORT $LN2@AuSoundAdd

; 59   : 		dsp_first = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, rax ; dsp_first

; 60   : 		dsp_last = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last

; 61   : 	}else {

	jmp	SHORT $LN1@AuSoundAdd
$LN2@AuSoundAdd:

; 62   : 		dsp_last->next = dsp;

	mov	rax, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+40], rcx

; 63   : 		dsp->prev = dsp_last;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	mov	QWORD PTR [rax+48], rcx

; 64   : 		dsp_last = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last
$LN1@AuSoundAdd:

; 65   : 	}
; 66   : }

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

; 124  : void AuSoundWrite (vfs_node_t *file, uint8_t* buffer, uint32_t length) {

$LN13:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 125  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN10@AuSoundWri

; 126  : 		return;

	jmp	$LN11@AuSoundWri
$LN10@AuSoundWri:

; 127  : 	int16_t* tmp_buffer = (int16_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 2
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR tmp_buffer$[rsp], rax

; 128  : 	uint8_t* buff = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 2
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buff$[rsp], rax

; 129  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

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

; 130  : 
; 131  : 		for (int i = 0; i < BUFF_SIZE; i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN6@AuSoundWri
$LN5@AuSoundWri:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN6@AuSoundWri:
	cmp	DWORD PTR i$2[rsp], 8192		; 00002000H
	jge	SHORT $LN4@AuSoundWri

; 132  : 			circular_buf_get(dsp->buffer,buff); 

	mov	rdx, QWORD PTR buff$[rsp]
	mov	rax, QWORD PTR dsp$3[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z ; circular_buf_get
	jmp	SHORT $LN5@AuSoundWri
$LN4@AuSoundWri:

; 133  : 
; 134  : 		int16_t* aligned_buff = (int16_t*)buff;

	mov	rax, QWORD PTR buff$[rsp]
	mov	QWORD PTR aligned_buff$4[rsp], rax

; 135  : 		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuSoundWri
$LN2@AuSoundWri:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuSoundWri:
	movsxd	rax, DWORD PTR i$1[rsp]
	cmp	rax, 4096				; 00001000H
	jae	SHORT $LN1@AuSoundWri

; 136  : 			tmp_buffer[i] = aligned_buff[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR tmp_buffer$[rsp]
	mov	r8, QWORD PTR aligned_buff$4[rsp]
	movzx	eax, WORD PTR [r8+rax*2]
	mov	WORD PTR [rdx+rcx*2], ax

; 137  : 		}

	jmp	SHORT $LN2@AuSoundWri
$LN1@AuSoundWri:

; 138  : 		AuRequestNextBlock(dsp->id);

	mov	rax, QWORD PTR dsp$3[rsp]
	movzx	ecx, WORD PTR [rax+8]
	call	?AuRequestNextBlock@@YAXG@Z		; AuRequestNextBlock

; 139  : 	}

	jmp	$LN8@AuSoundWri
$LN7@AuSoundWri:

; 140  : 	
; 141  : 	registered_dev->write((uint8_t*)tmp_buffer, BUFF_SIZE);

	mov	edx, 8192				; 00002000H
	mov	rcx, QWORD PTR tmp_buffer$[rsp]
	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+32]

; 142  : 	AuPmmngrFreeBlocks((void*)v2p((size_t)buff), BUFF_SIZE/4096);

	mov	rcx, QWORD PTR buff$[rsp]
	call	v2p
	mov	edx, 2
	mov	rcx, rax
	call	AuPmmngrFreeBlocks

; 143  : 	AuPmmngrFreeBlocks((void*)v2p((size_t)tmp_buffer), BUFF_SIZE/4096);

	mov	rcx, QWORD PTR tmp_buffer$[rsp]
	call	v2p
	mov	edx, 2
	mov	rcx, rax
	call	AuPmmngrFreeBlocks
$LN11@AuSoundWri:

; 144  : }

	add	rsp, 88					; 00000058H
	ret	0
?AuSoundWrite@@YAXPEAU_vfs_node_@@PEAEI@Z ENDP		; AuSoundWrite
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
?AuSoundOutputStop@@YAXXZ PROC				; AuSoundOutputStop

; 260  : void AuSoundOutputStop() {

$LN4:
	sub	rsp, 40					; 00000028H

; 261  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundOut

; 262  : 		return;

	jmp	SHORT $LN2@AuSoundOut
$LN1@AuSoundOut:

; 263  : 	registered_dev->stop_output_stream();

	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+48]
$LN2@AuSoundOut:

; 264  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuSoundOutputStop@@YAXXZ ENDP				; AuSoundOutputStop
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
?AuSoundOutputStart@@YAXXZ PROC				; AuSoundOutputStart

; 254  : void AuSoundOutputStart() {

$LN4:
	sub	rsp, 40					; 00000028H

; 255  : 	if (registered_dev == NULL)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	jne	SHORT $LN1@AuSoundOut

; 256  : 		return;

	jmp	SHORT $LN2@AuSoundOut
$LN1@AuSoundOut:

; 257  : 	registered_dev->start_output_stream();

	mov	rax, QWORD PTR ?registered_dev@@3PEAU_sound_@@EA ; registered_dev
	call	QWORD PTR [rax+56]
$LN2@AuSoundOut:

; 258  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuSoundOutputStart@@YAXXZ ENDP				; AuSoundOutputStart
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
i$1 = 32
i$2 = 36
i$3 = 40
i$4 = 44
dsp$5 = 48
dsp$6 = 56
hw_buffer$ = 64
buff$ = 72
data_bu$7 = 80
buffer$ = 112
AuSoundRequestNext PROC

; 225  : void AuSoundRequestNext (uint64_t *buffer) {

$LN21:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 226  : 	int16_t* hw_buffer = (int16_t*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR hw_buffer$[rsp], rax

; 227  : 	uint8_t *buff = (uint8_t*)p2v((size_t)AuPmmngrAllocBlocks(BUFF_SIZE/4096));

	mov	ecx, 2
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buff$[rsp], rax

; 228  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

	mov	rax, QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA ; dsp_first
	mov	QWORD PTR dsp$5[rsp], rax
	jmp	SHORT $LN18@AuSoundReq
$LN17@AuSoundReq:
	mov	rax, QWORD PTR dsp$5[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR dsp$5[rsp], rax
$LN18@AuSoundReq:
	cmp	QWORD PTR dsp$5[rsp], 0
	je	$LN16@AuSoundReq

; 229  : 
; 230  : 		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++)

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN15@AuSoundReq
$LN14@AuSoundReq:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN15@AuSoundReq:
	movsxd	rax, DWORD PTR i$3[rsp]
	cmp	rax, 4096				; 00001000H
	jae	SHORT $LN13@AuSoundReq

; 231  : 			hw_buffer[i] = 0;

	movsxd	rax, DWORD PTR i$3[rsp]
	xor	ecx, ecx
	mov	rdx, QWORD PTR hw_buffer$[rsp]
	mov	WORD PTR [rdx+rax*2], cx
	jmp	SHORT $LN14@AuSoundReq
$LN13@AuSoundReq:

; 232  : 		
; 233  : 		for (int i = 0; i < BUFF_SIZE; i++)

	mov	DWORD PTR i$4[rsp], 0
	jmp	SHORT $LN12@AuSoundReq
$LN11@AuSoundReq:
	mov	eax, DWORD PTR i$4[rsp]
	inc	eax
	mov	DWORD PTR i$4[rsp], eax
$LN12@AuSoundReq:
	cmp	DWORD PTR i$4[rsp], 8192		; 00002000H
	jge	SHORT $LN10@AuSoundReq

; 234  : 			circular_buf_get(dsp->buffer,buff);

	mov	rdx, QWORD PTR buff$[rsp]
	mov	rax, QWORD PTR dsp$5[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z ; circular_buf_get
	jmp	SHORT $LN11@AuSoundReq
$LN10@AuSoundReq:

; 235  : 		
; 236  : 		int16_t *data_bu = (int16_t*)buff;

	mov	rax, QWORD PTR buff$[rsp]
	mov	QWORD PTR data_bu$7[rsp], rax

; 237  : 		for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++){

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN9@AuSoundReq
$LN8@AuSoundReq:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN9@AuSoundReq:
	movsxd	rax, DWORD PTR i$2[rsp]
	cmp	rax, 4096				; 00001000H
	jae	SHORT $LN7@AuSoundReq

; 238  : 			hw_buffer[i] = data_bu[i];

	movsxd	rax, DWORD PTR i$2[rsp]
	movsxd	rcx, DWORD PTR i$2[rsp]
	mov	rdx, QWORD PTR hw_buffer$[rsp]
	mov	r8, QWORD PTR data_bu$7[rsp]
	movzx	eax, WORD PTR [r8+rax*2]
	mov	WORD PTR [rdx+rcx*2], ax

; 239  : 		}

	jmp	SHORT $LN8@AuSoundReq
$LN7@AuSoundReq:

; 240  : 	}

	jmp	$LN17@AuSoundReq
$LN16@AuSoundReq:

; 241  : 
; 242  : 
; 243  : 	for (int i = 0; i < BUFF_SIZE / sizeof(int16_t); i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN6@AuSoundReq
$LN5@AuSoundReq:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN6@AuSoundReq:
	movsxd	rax, DWORD PTR i$1[rsp]
	cmp	rax, 4096				; 00001000H
	jae	SHORT $LN4@AuSoundReq

; 244  : 		hw_buffer[i] /= 2;

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR hw_buffer$[rsp]
	movsx	eax, WORD PTR [rcx+rax*2]
	cdq
	sub	eax, edx
	sar	eax, 1
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR hw_buffer$[rsp]
	mov	WORD PTR [rdx+rcx*2], ax
	jmp	SHORT $LN5@AuSoundReq
$LN4@AuSoundReq:

; 245  : 
; 246  : 	for (dsp_t *dsp = dsp_first; dsp != NULL; dsp = dsp->next) {

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

; 247  : 		AuRequestNextBlock(dsp->id);

	mov	rax, QWORD PTR dsp$6[rsp]
	movzx	ecx, WORD PTR [rax+8]
	call	?AuRequestNextBlock@@YAXG@Z		; AuRequestNextBlock

; 248  : 	}

	jmp	SHORT $LN2@AuSoundReq
$LN1@AuSoundReq:

; 249  : 
; 250  : 	AuPmmngrFreeBlocks((void*)v2p((size_t)buff),BUFF_SIZE/4096);

	mov	rcx, QWORD PTR buff$[rsp]
	call	v2p
	mov	edx, 2
	mov	rcx, rax
	call	AuPmmngrFreeBlocks

; 251  : }

	add	rsp, 104				; 00000068H
	ret	0
AuSoundRequestNext ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dev$ = 8
AuSoundRegisterDevice PROC

; 218  : void AuSoundRegisterDevice(sound_t * dev) {

	mov	QWORD PTR [rsp+8], rcx

; 219  : 	if (registered_dev)

	cmp	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, 0 ; registered_dev
	je	SHORT $LN1@AuSoundReg

; 220  : 		return;

	jmp	SHORT $LN2@AuSoundReg
$LN1@AuSoundReg:

; 221  : 	registered_dev = dev;

	mov	rax, QWORD PTR dev$[rsp]
	mov	QWORD PTR ?registered_dev@@3PEAU_sound_@@EA, rax ; registered_dev
$LN2@AuSoundReg:

; 222  : }

	fatret	0
AuSoundRegisterDevice ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 32
?AuSoundInitialize@@YAXXZ PROC				; AuSoundInitialize

; 198  : void AuSoundInitialize () {

$LN3:
	sub	rsp, 56					; 00000038H

; 199  : 	vfs_node_t *dsp = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 104				; 00000068H
	call	malloc
	mov	QWORD PTR dsp$[rsp], rax

; 200  : 	strcpy (dsp->filename, "dsp");

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rdx, OFFSET FLAT:$SG3882
	mov	rcx, rax
	call	strcpy

; 201  : 	dsp->size = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	DWORD PTR [rax+32], 0

; 202  : 	dsp->eof = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	BYTE PTR [rax+36], 0

; 203  : 	dsp->pos = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	DWORD PTR [rax+40], 0

; 204  : 	dsp->current = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	DWORD PTR [rax+44], 0

; 205  : 	dsp->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	BYTE PTR [rax+48], 2

; 206  : 	dsp->status = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	BYTE PTR [rax+49], 0

; 207  : 	dsp->open = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+64], 0

; 208  : 	dsp->read = AuSoundRead;

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:?AuSoundRead@@YAXPEAU_vfs_node_@@PEA_KI@Z ; AuSoundRead
	mov	QWORD PTR [rax+72], rcx

; 209  : 	dsp->write = AuFileWrite;

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:?AuFileWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z ; AuFileWrite
	mov	QWORD PTR [rax+80], rcx

; 210  : 	dsp->read_blk = 0;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+88], 0

; 211  : 	dsp->ioquery = AuSoundIOQuery;

	mov	rax, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:?AuSoundIOQuery@@YAHPEAU_vfs_node_@@HPEAX@Z ; AuSoundIOQuery
	mov	QWORD PTR [rax+96], rcx

; 212  : 	vfs_mount ("/dev/dsp", dsp, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR dsp$[rsp]
	lea	rcx, OFFSET FLAT:$SG3883
	call	vfs_mount

; 213  : 
; 214  : 	dsp_first = NULL;

	mov	QWORD PTR ?dsp_first@@3PEAU_dsp_@@EA, 0	; dsp_first

; 215  : 	dsp_last = NULL;

	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, 0	; dsp_last

; 216  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuSoundInitialize@@YAXXZ ENDP				; AuSoundInitialize
_TEXT	ENDS
END
