; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?dsp_head@@3PEAU_dsp_@@EA			; dsp_head
PUBLIC	?dsp_last@@3PEAU_dsp_@@EA			; dsp_last
_BSS	SEGMENT
_sound_loop_prop_ DB 01H DUP (?)
	ALIGN	8

?dsp_head@@3PEAU_dsp_@@EA DQ 01H DUP (?)		; dsp_head
?dsp_last@@3PEAU_dsp_@@EA DQ 01H DUP (?)		; dsp_last
_BSS	ENDS
CONST	SEGMENT
$SG3776	DB	'snd', 00H
	ORG $+4
$SG3777	DB	'/dev/snd', 00H
CONST	ENDS
PUBLIC	?sound_initialize@@YAXXZ			; sound_initialize
PUBLIC	?sound_request_next@@YAXPEAE@Z			; sound_request_next
PUBLIC	?dsp_insert@@YAXPEAU_dsp_@@@Z			; dsp_insert
PUBLIC	?dsp_delete@@YAXPEAU_dsp_@@@Z			; dsp_delete
PUBLIC	?sound_create_client@@YAXPEAU_vfs_node_@@@Z	; sound_create_client
PUBLIC	?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z	; snd_io_query
PUBLIC	?sound_write@@YAXPEAU_vfs_node_@@PEAEI@Z	; sound_write
EXTRN	?strcpy@@YAPEADPEADPEBD@Z:PROC			; strcpy
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	memcpy:PROC
EXTRN	vfs_mount:PROC
EXTRN	?AuPmmngrAlloc@@YAPEAXXZ:PROC			; AuPmmngrAlloc
EXTRN	?AuPmmngrFree@@YAXPEAX@Z:PROC			; AuPmmngrFree
EXTRN	?malloc@@YAPEAX_K@Z:PROC			; malloc
EXTRN	?hda_audio_play@@YAXXZ:PROC			; hda_audio_play
pdata	SEGMENT
$pdata$?sound_initialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+220
	DD	imagerel $unwind$?sound_initialize@@YAXXZ
$pdata$?sound_request_next@@YAXPEAE@Z DD imagerel $LN9
	DD	imagerel $LN9+139
	DD	imagerel $unwind$?sound_request_next@@YAXPEAE@Z
$pdata$?dsp_delete@@YAXPEAU_dsp_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+173
	DD	imagerel $unwind$?dsp_delete@@YAXPEAU_dsp_@@@Z
$pdata$?sound_create_client@@YAXPEAU_vfs_node_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+66
	DD	imagerel $unwind$?sound_create_client@@YAXPEAU_vfs_node_@@@Z
$pdata$?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN9
	DD	imagerel $LN9+99
	DD	imagerel $unwind$?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z
$pdata$?sound_write@@YAXPEAU_vfs_node_@@PEAEI@Z DD imagerel $LN4
	DD	imagerel $LN4+74
	DD	imagerel $unwind$?sound_write@@YAXPEAU_vfs_node_@@PEAEI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?sound_initialize@@YAXXZ DD 010401H
	DD	06204H
$unwind$?sound_request_next@@YAXPEAE@Z DD 010901H
	DD	02209H
$unwind$?dsp_delete@@YAXPEAU_dsp_@@@Z DD 010901H
	DD	04209H
$unwind$?sound_create_client@@YAXPEAU_vfs_node_@@@Z DD 010901H
	DD	06209H
$unwind$?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z DD 011201H
	DD	06212H
$unwind$?sound_write@@YAXPEAU_vfs_node_@@PEAEI@Z DD 011301H
	DD	06213H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$1 = 32
file$ = 64
buffer$ = 72
length$ = 80
?sound_write@@YAXPEAU_vfs_node_@@PEAEI@Z PROC		; sound_write

; 108  : void sound_write (vfs_node_t *file, uint8_t* buffer, uint32_t length) {

$LN4:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 109  : 	/* it will write the audio content to hda descriptor buffers */
; 110  : 	if (file->device) {

	mov	rax, QWORD PTR file$[rsp]
	cmp	QWORD PTR [rax+56], 0
	je	SHORT $LN1@sound_writ

; 111  : 		dsp_t *dsp = (dsp_t*)file->device;

	mov	rax, QWORD PTR file$[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR dsp$1[rsp], rax

; 112  : 		memcpy (dsp->buf,buffer, 512);

	mov	rax, QWORD PTR dsp$1[rsp]
	mov	r8d, 512				; 00000200H
	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, rax
	call	memcpy
$LN1@sound_writ:

; 113  : 	}
; 114  : }

	add	rsp, 56					; 00000038H
	ret	0
?sound_write@@YAXPEAU_vfs_node_@@PEAEI@Z ENDP		; sound_write
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
tv64 = 32
node$ = 64
code$ = 72
arg$ = 80
?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z PROC		; snd_io_query

; 88   : int snd_io_query (vfs_node_t* node, int code, void* arg) {

$LN9:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 89   : 	switch(code) {

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv64[rsp], eax
	cmp	DWORD PTR tv64[rsp], 12
	je	SHORT $LN4@snd_io_que
	cmp	DWORD PTR tv64[rsp], 13
	je	SHORT $LN3@snd_io_que
	cmp	DWORD PTR tv64[rsp], 14
	je	SHORT $LN2@snd_io_que
	cmp	DWORD PTR tv64[rsp], 16
	je	SHORT $LN1@snd_io_que
	jmp	SHORT $LN5@snd_io_que
$LN4@snd_io_que:

; 90   : 	case PLAY_STARTUP:
; 91   : 		hda_audio_play();

	call	?hda_audio_play@@YAXXZ			; hda_audio_play

; 92   : 		break;

	jmp	SHORT $LN5@snd_io_que
$LN3@snd_io_que:

; 93   : 	case SOUND_LOOP_ENABLE: 
; 94   : 		_sound_loop_prop_ = true;

	mov	BYTE PTR _sound_loop_prop_, 1

; 95   : 		break;

	jmp	SHORT $LN5@snd_io_que
$LN2@snd_io_que:

; 96   : 	case SOUND_PLAY:
; 97   : 		hda_audio_play();

	call	?hda_audio_play@@YAXXZ			; hda_audio_play

; 98   : 		break;

	jmp	SHORT $LN5@snd_io_que
$LN1@snd_io_que:

; 99   : 	case SOUND_CREATE_CLIENT:
; 100  : 		sound_create_client (node);

	mov	rcx, QWORD PTR node$[rsp]
	call	?sound_create_client@@YAXPEAU_vfs_node_@@@Z ; sound_create_client
$LN5@snd_io_que:

; 101  : 		break;
; 102  : 	}
; 103  : 
; 104  : 	return 1;

	mov	eax, 1

; 105  : }

	add	rsp, 56					; 00000038H
	ret	0
?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP		; snd_io_query
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 32
node$ = 64
?sound_create_client@@YAXPEAU_vfs_node_@@@Z PROC	; sound_create_client

; 80   : void sound_create_client (vfs_node_t *node) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 81   : 	dsp_t *dsp = (dsp_t*)AuPmmngrAlloc();

	call	?AuPmmngrAlloc@@YAPEAXXZ		; AuPmmngrAlloc
	mov	QWORD PTR dsp$[rsp], rax

; 82   : 	memset(dsp,0,4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR dsp$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 83   : 	node->device = dsp;

	mov	rax, QWORD PTR node$[rsp]
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+56], rcx

; 84   : 	dsp_insert (dsp);

	mov	rcx, QWORD PTR dsp$[rsp]
	call	?dsp_insert@@YAXPEAU_dsp_@@@Z		; dsp_insert

; 85   : }

	add	rsp, 56					; 00000038H
	ret	0
?sound_create_client@@YAXPEAU_vfs_node_@@@Z ENDP	; sound_create_client
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 48
?dsp_delete@@YAXPEAU_dsp_@@@Z PROC			; dsp_delete

; 57   : void dsp_delete (dsp_t* dsp) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 58   : 
; 59   : 	if (dsp_head == NULL)

	cmp	QWORD PTR ?dsp_head@@3PEAU_dsp_@@EA, 0	; dsp_head
	jne	SHORT $LN5@dsp_delete

; 60   : 		return;

	jmp	$LN6@dsp_delete
$LN5@dsp_delete:

; 61   : 
; 62   : 	if (dsp == dsp_head) {

	mov	rax, QWORD PTR ?dsp_head@@3PEAU_dsp_@@EA ; dsp_head
	cmp	QWORD PTR dsp$[rsp], rax
	jne	SHORT $LN4@dsp_delete

; 63   : 		dsp_head = dsp_head->next;

	mov	rax, QWORD PTR ?dsp_head@@3PEAU_dsp_@@EA ; dsp_head
	mov	rax, QWORD PTR [rax+520]
	mov	QWORD PTR ?dsp_head@@3PEAU_dsp_@@EA, rax ; dsp_head

; 64   : 	} else {

	jmp	SHORT $LN3@dsp_delete
$LN4@dsp_delete:

; 65   : 		dsp->prev->next = dsp->next;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+528]
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rcx+520]
	mov	QWORD PTR [rax+520], rcx
$LN3@dsp_delete:

; 66   : 	}
; 67   : 
; 68   : 	if (dsp == dsp_last) {

	mov	rax, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	cmp	QWORD PTR dsp$[rsp], rax
	jne	SHORT $LN2@dsp_delete

; 69   : 		dsp_last = dsp->prev;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+528]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last

; 70   : 	} else {

	jmp	SHORT $LN1@dsp_delete
$LN2@dsp_delete:

; 71   : 		dsp->next->prev = dsp->prev;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rax, QWORD PTR [rax+520]
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR [rcx+528]
	mov	QWORD PTR [rax+528], rcx
$LN1@dsp_delete:

; 72   : 	}
; 73   : 
; 74   : 	AuPmmngrFree (dsp);

	mov	rcx, QWORD PTR dsp$[rsp]
	call	?AuPmmngrFree@@YAXPEAX@Z		; AuPmmngrFree
$LN6@dsp_delete:

; 75   : }

	add	rsp, 40					; 00000028H
	ret	0
?dsp_delete@@YAXPEAU_dsp_@@@Z ENDP			; dsp_delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
dsp$ = 8
?dsp_insert@@YAXPEAU_dsp_@@@Z PROC			; dsp_insert

; 39   : void dsp_insert (dsp_t* dsp) {

	mov	QWORD PTR [rsp+8], rcx

; 40   : 	dsp->next = NULL;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+520], 0

; 41   : 	dsp->prev = NULL;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+528], 0

; 42   : 
; 43   : 	if (dsp_head == NULL) {

	cmp	QWORD PTR ?dsp_head@@3PEAU_dsp_@@EA, 0	; dsp_head
	jne	SHORT $LN2@dsp_insert

; 44   : 		dsp_last = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last

; 45   : 		dsp_head = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_head@@3PEAU_dsp_@@EA, rax ; dsp_head

; 46   : 	} else {

	jmp	SHORT $LN1@dsp_insert
$LN2@dsp_insert:

; 47   : 		dsp_last->next = dsp;

	mov	rax, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	mov	rcx, QWORD PTR dsp$[rsp]
	mov	QWORD PTR [rax+520], rcx

; 48   : 		dsp->prev = dsp_last;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	rcx, QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA ; dsp_last
	mov	QWORD PTR [rax+528], rcx
$LN1@dsp_insert:

; 49   : 	}
; 50   : 	dsp_last = dsp;

	mov	rax, QWORD PTR dsp$[rsp]
	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, rax ; dsp_last

; 51   : }

	ret	0
?dsp_insert@@YAXPEAU_dsp_@@@Z ENDP			; dsp_insert
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
i$1 = 0
c_dsp$2 = 8
usable_buffer$ = 32
?sound_request_next@@YAXPEAE@Z PROC			; sound_request_next

; 117  : void sound_request_next (uint8_t* usable_buffer) {

$LN9:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 118  : 	for (dsp_t *c_dsp = dsp_head; c_dsp != NULL; c_dsp = c_dsp->next) {

	mov	rax, QWORD PTR ?dsp_head@@3PEAU_dsp_@@EA ; dsp_head
	mov	QWORD PTR c_dsp$2[rsp], rax
	jmp	SHORT $LN6@sound_requ
$LN5@sound_requ:
	mov	rax, QWORD PTR c_dsp$2[rsp]
	mov	rax, QWORD PTR [rax+520]
	mov	QWORD PTR c_dsp$2[rsp], rax
$LN6@sound_requ:
	cmp	QWORD PTR c_dsp$2[rsp], 0
	je	SHORT $LN4@sound_requ

; 119  : 		for (int i = 0; i < SAMPLES_PER_BUFFER; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@sound_requ
$LN2@sound_requ:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@sound_requ:
	cmp	DWORD PTR i$1[rsp], 256			; 00000100H
	jge	SHORT $LN1@sound_requ

; 120  : 			usable_buffer[i] = c_dsp->buf[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR usable_buffer$[rsp]
	mov	r8, QWORD PTR c_dsp$2[rsp]
	movzx	eax, BYTE PTR [r8+rax]
	mov	BYTE PTR [rdx+rcx], al

; 121  : 			usable_buffer[i] /= 2;

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR usable_buffer$[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	cdq
	sub	eax, edx
	sar	eax, 1
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR usable_buffer$[rsp]
	mov	BYTE PTR [rdx+rcx], al

; 122  : 		}

	jmp	SHORT $LN2@sound_requ
$LN1@sound_requ:

; 123  : 		//memcpy (usable_buffer,c_dsp->buf,512/);
; 124  : 	}

	jmp	SHORT $LN5@sound_requ
$LN4@sound_requ:

; 125  : }

	add	rsp, 24
	ret	0
?sound_request_next@@YAXPEAE@Z ENDP			; sound_request_next
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
snd$ = 32
?sound_initialize@@YAXXZ PROC				; sound_initialize

; 128  : void sound_initialize () {

$LN3:
	sub	rsp, 56					; 00000038H

; 129  : 	dsp_last = NULL;

	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, 0	; dsp_last

; 130  : 	dsp_last = NULL;

	mov	QWORD PTR ?dsp_last@@3PEAU_dsp_@@EA, 0	; dsp_last

; 131  : 
; 132  : 	vfs_node_t * snd = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 104				; 00000068H
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	QWORD PTR snd$[rsp], rax

; 133  : 	strcpy (snd->filename, "snd");

	mov	rax, QWORD PTR snd$[rsp]
	lea	rdx, OFFSET FLAT:$SG3776
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 134  : 	snd->size = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	DWORD PTR [rax+32], 0

; 135  : 	snd->eof = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	BYTE PTR [rax+36], 0

; 136  : 	snd->pos = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	DWORD PTR [rax+40], 0

; 137  : 	snd->current = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	DWORD PTR [rax+44], 0

; 138  : 	snd->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR snd$[rsp]
	mov	BYTE PTR [rax+48], 2

; 139  : 	snd->status = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	BYTE PTR [rax+49], 0

; 140  : 	snd->open = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	QWORD PTR [rax+64], 0

; 141  : 	snd->read = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	QWORD PTR [rax+72], 0

; 142  : 	snd->write = sound_write;

	mov	rax, QWORD PTR snd$[rsp]
	lea	rcx, OFFSET FLAT:?sound_write@@YAXPEAU_vfs_node_@@PEAEI@Z ; sound_write
	mov	QWORD PTR [rax+80], rcx

; 143  : 	snd->read_blk = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	QWORD PTR [rax+88], 0

; 144  : 	snd->ioquery = snd_io_query;

	mov	rax, QWORD PTR snd$[rsp]
	lea	rcx, OFFSET FLAT:?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z ; snd_io_query
	mov	QWORD PTR [rax+96], rcx

; 145  : 	vfs_mount ("/dev/snd", snd, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR snd$[rsp]
	lea	rcx, OFFSET FLAT:$SG3777
	call	vfs_mount

; 146  : }

	add	rsp, 56					; 00000038H
	ret	0
?sound_initialize@@YAXXZ ENDP				; sound_initialize
_TEXT	ENDS
END
