; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?sys@@3U_file_system_@@A			; sys
_BSS	SEGMENT
?sys@@3U_file_system_@@A DB 020H DUP (?)		; sys
_BSS	ENDS
CONST	SEGMENT
$SG2771	DB	'FAT32', 00H
CONST	ENDS
PUBLIC	?initialize_vfs@@YAXXZ				; initialize_vfs
PUBLIC	?open@@YA?AU_file_@@PEBD@Z			; open
PUBLIC	?read@@YAXPEAU_file_@@PEAEI@Z			; read
PUBLIC	?read_blk@@YAXPEAU_file_@@PEAE@Z		; read_blk
EXTRN	?initialize_fat32@@YAXXZ:PROC			; initialize_fat32
EXTRN	?fat32_open@@YA?AU_file_@@PEBD@Z:PROC		; fat32_open
EXTRN	?fat32_read_file@@YAXPEAU_file_@@PEAEH@Z:PROC	; fat32_read_file
EXTRN	?fat32_read@@YAXPEAU_file_@@PEAE@Z:PROC		; fat32_read
EXTRN	memcpy:PROC
pdata	SEGMENT
$pdata$?initialize_vfs@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+81
	DD	imagerel $unwind$?initialize_vfs@@YAXXZ
$pdata$?open@@YA?AU_file_@@PEBD@Z DD imagerel $LN3
	DD	imagerel $LN3+97
	DD	imagerel $unwind$?open@@YA?AU_file_@@PEBD@Z
$pdata$?read@@YAXPEAU_file_@@PEAEI@Z DD imagerel $LN3
	DD	imagerel $LN3+45
	DD	imagerel $unwind$?read@@YAXPEAU_file_@@PEAEI@Z
$pdata$?read_blk@@YAXPEAU_file_@@PEAE@Z DD imagerel $LN3
	DD	imagerel $LN3+35
	DD	imagerel $unwind$?read_blk@@YAXPEAU_file_@@PEAE@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_vfs@@YAXXZ DD 010401H
	DD	04204H
$unwind$?open@@YA?AU_file_@@PEBD@Z DD 041301H
	DD	0150113H
	DD	0600b700cH
$unwind$?read@@YAXPEAU_file_@@PEAEI@Z DD 011301H
	DD	04213H
$unwind$?read_blk@@YAXPEAU_file_@@PEAE@Z DD 010e01H
	DD	0420eH
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\vfs.cpp
_TEXT	SEGMENT
pfile$ = 48
buffer$ = 56
?read_blk@@YAXPEAU_file_@@PEAE@Z PROC			; read_blk

; 37   : void read_blk (FILE *pfile, unsigned char *buffer) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 38   : 	sys.sys_read_blk(pfile,buffer);

	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, QWORD PTR pfile$[rsp]
	call	QWORD PTR ?sys@@3U_file_system_@@A+24

; 39   : }

	add	rsp, 40					; 00000028H
	ret	0
?read_blk@@YAXPEAU_file_@@PEAE@Z ENDP			; read_blk
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\vfs.cpp
_TEXT	SEGMENT
pfile$ = 48
buffer$ = 56
count$ = 64
?read@@YAXPEAU_file_@@PEAEI@Z PROC			; read

; 33   : void read (FILE *pfile, unsigned char* buffer,unsigned int count) {

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 34   :     sys.sys_read (pfile,buffer,count);

	mov	r8d, DWORD PTR count$[rsp]
	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, QWORD PTR pfile$[rsp]
	call	QWORD PTR ?sys@@3U_file_system_@@A+16

; 35   : }

	add	rsp, 40					; 00000028H
	ret	0
?read@@YAXPEAU_file_@@PEAEI@Z ENDP			; read
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\vfs.cpp
_TEXT	SEGMENT
$T1 = 32
$T2 = 96
$T3 = 192
filename$ = 200
?open@@YA?AU_file_@@PEBD@Z PROC				; open

; 30   : FILE open (const char* filename) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 168				; 000000a8H

; 31   : 	return sys.sys_open(filename);

	mov	rdx, QWORD PTR filename$[rsp]
	lea	rcx, QWORD PTR $T2[rsp]
	call	QWORD PTR ?sys@@3U_file_system_@@A+8
	lea	rcx, QWORD PTR $T1[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 60					; 0000003cH
	rep movsb
	lea	rax, QWORD PTR $T1[rsp]
	mov	rdi, QWORD PTR $T3[rsp]
	mov	rsi, rax
	mov	ecx, 60					; 0000003cH
	rep movsb
	mov	rax, QWORD PTR $T3[rsp]

; 32   : }

	add	rsp, 168				; 000000a8H
	pop	rdi
	pop	rsi
	ret	0
?open@@YA?AU_file_@@PEBD@Z ENDP				; open
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\vfs.cpp
_TEXT	SEGMENT
?initialize_vfs@@YAXXZ PROC				; initialize_vfs

; 18   : void initialize_vfs () {

$LN3:
	sub	rsp, 40					; 00000028H

; 19   : 	
; 20   : 	//! By default FAT32 is recommended
; 21   : #ifdef ARCH_X64
; 22   : 	initialize_fat32();

	call	?initialize_fat32@@YAXXZ		; initialize_fat32

; 23   : 	memcpy(sys.name,"FAT32",5);

	mov	r8d, 5
	lea	rdx, OFFSET FLAT:$SG2771
	lea	rcx, OFFSET FLAT:?sys@@3U_file_system_@@A ; sys
	call	memcpy

; 24   : 	sys.sys_open = fat32_open;

	lea	rax, OFFSET FLAT:?fat32_open@@YA?AU_file_@@PEBD@Z ; fat32_open
	mov	QWORD PTR ?sys@@3U_file_system_@@A+8, rax

; 25   : 	sys.sys_read = fat32_read_file;

	lea	rax, OFFSET FLAT:?fat32_read_file@@YAXPEAU_file_@@PEAEH@Z ; fat32_read_file
	mov	QWORD PTR ?sys@@3U_file_system_@@A+16, rax

; 26   : 	sys.sys_read_blk = fat32_read;

	lea	rax, OFFSET FLAT:?fat32_read@@YAXPEAU_file_@@PEAE@Z ; fat32_read
	mov	QWORD PTR ?sys@@3U_file_system_@@A+24, rax

; 27   : #endif
; 28   : }

	add	rsp, 40					; 00000028H
	ret	0
?initialize_vfs@@YAXXZ ENDP				; initialize_vfs
_TEXT	ENDS
END
