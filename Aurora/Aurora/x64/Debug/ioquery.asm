; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?ioquery@@YAXHHPEAX@Z				; ioquery
EXTRN	?vfs_get_file_system@@YAPEAU_file_system_@@H@Z:PROC ; vfs_get_file_system
EXTRN	x64_cli:PROC
pdata	SEGMENT
$pdata$?ioquery@@YAXHHPEAX@Z DD imagerel $LN4
	DD	imagerel $LN4+67
	DD	imagerel $unwind$?ioquery@@YAXHHPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?ioquery@@YAXHHPEAX@Z DD 011101H
	DD	06211H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\ioquery.cpp
_TEXT	SEGMENT
sys_$ = 32
device_id$ = 64
code$ = 72
arg$ = 80
?ioquery@@YAXHHPEAX@Z PROC				; ioquery

; 21   : void ioquery (int device_id, int code, void* arg) {

$LN4:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 22   : 	x64_cli();

	call	x64_cli

; 23   : 
; 24   : 	if (device_id < 0)

	cmp	DWORD PTR device_id$[rsp], 0
	jge	SHORT $LN1@ioquery

; 25   : 		return;

	jmp	SHORT $LN2@ioquery
$LN1@ioquery:

; 26   : 
; 27   : 	file_system_t *sys_ = vfs_get_file_system(device_id);

	mov	ecx, DWORD PTR device_id$[rsp]
	call	?vfs_get_file_system@@YAPEAU_file_system_@@H@Z ; vfs_get_file_system
	mov	QWORD PTR sys_$[rsp], rax

; 28   : 	sys_->ioquery (code, arg);

	mov	rdx, QWORD PTR arg$[rsp]
	mov	ecx, DWORD PTR code$[rsp]
	mov	rax, QWORD PTR sys_$[rsp]
	call	QWORD PTR [rax+32]
$LN2@ioquery:

; 29   : }

	add	rsp, 56					; 00000038H
	ret	0
?ioquery@@YAXHHPEAX@Z ENDP				; ioquery
_TEXT	ENDS
END
