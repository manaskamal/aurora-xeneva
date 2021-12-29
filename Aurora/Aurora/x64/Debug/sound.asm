; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3532	DB	'fb', 00H
	ORG $+5
$SG3533	DB	'/dev/snd', 00H
CONST	ENDS
PUBLIC	?sound_initialize@@YAXXZ			; sound_initialize
PUBLIC	?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z	; snd_io_query
EXTRN	?strcpy@@YAPEADPEADPEBD@Z:PROC			; strcpy
EXTRN	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z:PROC	; vfs_mount
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?hda_audio_play@@YAXXZ:PROC			; hda_audio_play
pdata	SEGMENT
$pdata$?sound_initialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+196
	DD	imagerel $unwind$?sound_initialize@@YAXXZ
$pdata$?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+50
	DD	imagerel $unwind$?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?sound_initialize@@YAXXZ DD 010401H
	DD	06204H
$unwind$?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z DD 011201H
	DD	06212H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
tv64 = 32
node$ = 64
code$ = 72
arg$ = 80
?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z PROC		; snd_io_query

; 21   : int snd_io_query (vfs_node_t* node, int code, void* arg) {

$LN6:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 22   : 	switch(code) {

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv64[rsp], eax
	cmp	DWORD PTR tv64[rsp], 12
	je	SHORT $LN1@snd_io_que
	jmp	SHORT $LN2@snd_io_que
$LN1@snd_io_que:

; 23   : 	case PLAY_STARTUP:
; 24   : 		hda_audio_play();

	call	?hda_audio_play@@YAXXZ			; hda_audio_play
$LN2@snd_io_que:

; 25   : 		break;
; 26   : 	}
; 27   : 
; 28   : 	return 1;

	mov	eax, 1

; 29   : }

	add	rsp, 56					; 00000038H
	ret	0
?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP		; snd_io_query
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sound.cpp
_TEXT	SEGMENT
snd$ = 32
?sound_initialize@@YAXXZ PROC				; sound_initialize

; 31   : void sound_initialize () {

$LN3:
	sub	rsp, 56					; 00000038H

; 32   : 	vfs_node_t * snd = (vfs_node_t*)pmmngr_alloc(); //malloc(sizeof(vfs_node_t));

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR snd$[rsp], rax

; 33   : 	strcpy (snd->filename, "fb");

	mov	rax, QWORD PTR snd$[rsp]
	lea	rdx, OFFSET FLAT:$SG3532
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 34   : 	snd->size = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	DWORD PTR [rax+32], 0

; 35   : 	snd->eof = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	DWORD PTR [rax+36], 0

; 36   : 	snd->pos = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	DWORD PTR [rax+40], 0

; 37   : 	snd->current = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	DWORD PTR [rax+44], 0

; 38   : 	snd->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR snd$[rsp]
	mov	DWORD PTR [rax+48], 2

; 39   : 	snd->status = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	DWORD PTR [rax+52], 0

; 40   : 	snd->open = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	QWORD PTR [rax+64], 0

; 41   : 	snd->read = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	QWORD PTR [rax+72], 0

; 42   : 	snd->write = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	QWORD PTR [rax+80], 0

; 43   : 	snd->read_blk = 0;

	mov	rax, QWORD PTR snd$[rsp]
	mov	QWORD PTR [rax+88], 0

; 44   : 	snd->ioquery = snd_io_query;

	mov	rax, QWORD PTR snd$[rsp]
	lea	rcx, OFFSET FLAT:?snd_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z ; snd_io_query
	mov	QWORD PTR [rax+96], rcx

; 45   : 	vfs_mount ("/dev/snd", snd);

	mov	rdx, QWORD PTR snd$[rsp]
	lea	rcx, OFFSET FLAT:$SG3533
	call	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z	; vfs_mount

; 46   : }

	add	rsp, 56					; 00000038H
	ret	0
?sound_initialize@@YAXXZ ENDP				; sound_initialize
_TEXT	ENDS
END