; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG2942	DB	'File not found', 0aH, 00H
CONST	ENDS
PUBLIC	?sys_open_file@@YAXPEAU_file_@@PEBD@Z		; sys_open_file
PUBLIC	?sys_read_file@@YAXPEAU_file_@@PEAEH@Z		; sys_read_file
EXTRN	?open@@YA?AU_file_@@PEBD@Z:PROC			; open
EXTRN	?read@@YAXPEAU_file_@@PEAEI@Z:PROC		; read
EXTRN	x64_cli:PROC
EXTRN	memcpy:PROC
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
pdata	SEGMENT
$pdata$?sys_open_file@@YAXPEAU_file_@@PEBD@Z DD imagerel $LN4
	DD	imagerel $LN4+139
	DD	imagerel $unwind$?sys_open_file@@YAXPEAU_file_@@PEBD@Z
$pdata$?sys_read_file@@YAXPEAU_file_@@PEAEH@Z DD imagerel $LN3
	DD	imagerel $LN3+49
	DD	imagerel $unwind$?sys_read_file@@YAXPEAU_file_@@PEAEH@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?sys_open_file@@YAXPEAU_file_@@PEBD@Z DD 041301H
	DD	01d0113H
	DD	0600b700cH
$unwind$?sys_read_file@@YAXPEAU_file_@@PEAEH@Z DD 011301H
	DD	04213H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
file$ = 48
buffer$ = 56
length$ = 64
?sys_read_file@@YAXPEAU_file_@@PEAEH@Z PROC		; sys_read_file

; 26   : void sys_read_file (FILE *file, unsigned char* buffer, int length) {

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 27   : 	x64_cli ();

	call	x64_cli

; 28   : 	read (file,buffer,length);

	mov	r8d, DWORD PTR length$[rsp]
	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, QWORD PTR file$[rsp]
	call	?read@@YAXPEAU_file_@@PEAEI@Z		; read

; 29   : }

	add	rsp, 40					; 00000028H
	ret	0
?sys_read_file@@YAXPEAU_file_@@PEAEH@Z ENDP		; sys_read_file
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
f$ = 32
$T1 = 96
$T2 = 160
file$ = 256
filename$ = 264
?sys_open_file@@YAXPEAU_file_@@PEBD@Z PROC		; sys_open_file

; 17   : void  sys_open_file (FILE *file, const char* filename) {

$LN4:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 232				; 000000e8H

; 18   : 	x64_cli ();

	call	x64_cli

; 19   : 	FILE f = open (filename);

	mov	rdx, QWORD PTR filename$[rsp]
	lea	rcx, QWORD PTR $T2[rsp]
	call	?open@@YA?AU_file_@@PEBD@Z		; open
	lea	rcx, QWORD PTR $T1[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 60					; 0000003cH
	rep movsb
	lea	rax, QWORD PTR f$[rsp]
	lea	rcx, QWORD PTR $T1[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 60					; 0000003cH
	rep movsb

; 20   : 	if (f.status == FILE_FLAG_INVALID) {

	cmp	DWORD PTR f$[rsp+56], 3
	jne	SHORT $LN1@sys_open_f

; 21   : 		printf ("File not found\n");

	lea	rcx, OFFSET FLAT:$SG2942
	call	?printf@@YAXPEBDZZ			; printf
$LN1@sys_open_f:

; 22   : 	}
; 23   : 	memcpy (file, &f, sizeof(FILE));

	mov	r8d, 60					; 0000003cH
	lea	rdx, QWORD PTR f$[rsp]
	mov	rcx, QWORD PTR file$[rsp]
	call	memcpy

; 24   : }

	add	rsp, 232				; 000000e8H
	pop	rdi
	pop	rsi
	ret	0
?sys_open_file@@YAXPEAU_file_@@PEBD@Z ENDP		; sys_open_file
_TEXT	ENDS
END
