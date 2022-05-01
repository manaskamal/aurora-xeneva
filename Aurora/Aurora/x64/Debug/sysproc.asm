; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3890	DB	'***Process killed ', 0dH, 0aH, 00H
	ORG $+3
$SG3891	DB	'*** Current used RAM -> %d MB / total -> %d MB ', 0dH, 0aH
	DB	00H
CONST	ENDS
PUBLIC	?create__sys_process@@YAHPEBDPEAD@Z		; create__sys_process
PUBLIC	?sys_exit@@YAXXZ				; sys_exit
PUBLIC	?sys_kill@@YAXHH@Z				; sys_kill
PUBLIC	?sys_set_signal@@YAXHP6AXH@Z@Z			; sys_set_signal
PUBLIC	?sys_attach_ttype@@YAXH@Z			; sys_attach_ttype
EXTRN	?pmmngr_get_used_ram@@YA_KXZ:PROC		; pmmngr_get_used_ram
EXTRN	?pmmngr_get_total_ram@@YA_KXZ:PROC		; pmmngr_get_total_ram
EXTRN	x64_cli:PROC
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
EXTRN	?force_sched@@YAXXZ:PROC			; force_sched
EXTRN	?AuCreateProcess@@YAHPEBDPEAD@Z:PROC		; AuCreateProcess
EXTRN	?kill_process@@YAXXZ:PROC			; kill_process
EXTRN	?kill_process_by_id@@YAXG@Z:PROC		; kill_process_by_id
EXTRN	?_debug_print_@@YAXPEADZZ:PROC			; _debug_print_
pdata	SEGMENT
$pdata$?create__sys_process@@YAHPEBDPEAD@Z DD imagerel $LN3
	DD	imagerel $LN3+45
	DD	imagerel $unwind$?create__sys_process@@YAHPEBDPEAD@Z
$pdata$?sys_exit@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+114
	DD	imagerel $unwind$?sys_exit@@YAXXZ
$pdata$?sys_kill@@YAXHH@Z DD imagerel $LN3
	DD	imagerel $LN3+37
	DD	imagerel $unwind$?sys_kill@@YAXHH@Z
$pdata$?sys_set_signal@@YAXHP6AXH@Z@Z DD imagerel $LN3
	DD	imagerel $LN3+23
	DD	imagerel $unwind$?sys_set_signal@@YAXHP6AXH@Z@Z
$pdata$?sys_attach_ttype@@YAXH@Z DD imagerel $LN3
	DD	imagerel $LN3+40
	DD	imagerel $unwind$?sys_attach_ttype@@YAXH@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?create__sys_process@@YAHPEBDPEAD@Z DD 010e01H
	DD	0620eH
$unwind$?sys_exit@@YAXXZ DD 010401H
	DD	06204H
$unwind$?sys_kill@@YAXHH@Z DD 010c01H
	DD	0420cH
$unwind$?sys_set_signal@@YAXHP6AXH@Z@Z DD 010d01H
	DD	0420dH
$unwind$?sys_attach_ttype@@YAXH@Z DD 010801H
	DD	06208H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysproc.cpp
_TEXT	SEGMENT
tv66 = 32
id$ = 64
?sys_attach_ttype@@YAXH@Z PROC				; sys_attach_ttype

; 91   : void sys_attach_ttype (int id) {

$LN3:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 92   : 	get_current_thread()->ttype = id;

	movsxd	rax, DWORD PTR id$[rsp]
	mov	QWORD PTR tv66[rsp], rax
	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rcx, QWORD PTR tv66[rsp]
	mov	QWORD PTR [rax+744], rcx

; 93   : }

	add	rsp, 56					; 00000038H
	ret	0
?sys_attach_ttype@@YAXH@Z ENDP				; sys_attach_ttype
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysproc.cpp
_TEXT	SEGMENT
signo$ = 48
handler$ = 56
?sys_set_signal@@YAXHP6AXH@Z@Z PROC			; sys_set_signal

; 82   : void sys_set_signal (int signo, sig_handler handler) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 83   : 	x64_cli();

	call	x64_cli

; 84   : 	//get_current_thread()->signals[signo] = handler;
; 85   : }

	add	rsp, 40					; 00000028H
	ret	0
?sys_set_signal@@YAXHP6AXH@Z@Z ENDP			; sys_set_signal
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysproc.cpp
_TEXT	SEGMENT
pid$ = 48
signo$ = 56
?sys_kill@@YAXHH@Z PROC					; sys_kill

; 70   : void sys_kill (int pid, int signo) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 71   : 	x64_cli();

	call	x64_cli

; 72   : 	kill_process_by_id(pid);

	movzx	ecx, WORD PTR pid$[rsp]
	call	?kill_process_by_id@@YAXG@Z		; kill_process_by_id

; 73   : 	force_sched();

	call	?force_sched@@YAXXZ			; force_sched

; 74   : 	//! For now, no signals are supported, just kill the process
; 75   : }

	add	rsp, 40					; 00000028H
	ret	0
?sys_kill@@YAXHH@Z ENDP					; sys_kill
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysproc.cpp
_TEXT	SEGMENT
tv67 = 32
?sys_exit@@YAXXZ PROC					; sys_exit

; 56   : void sys_exit () {

$LN3:
	sub	rsp, 56					; 00000038H

; 57   : 	x64_cli();	

	call	x64_cli

; 58   : 	kill_process();

	call	?kill_process@@YAXXZ			; kill_process

; 59   : 	_debug_print_ ("***Process killed \r\n");

	lea	rcx, OFFSET FLAT:$SG3890
	call	?_debug_print_@@YAXPEADZZ		; _debug_print_

; 60   : 	_debug_print_ ("*** Current used RAM -> %d MB / total -> %d MB \r\n", pmmngr_get_used_ram() / 1024 / 1024, pmmngr_get_total_ram() / 1024 / 1024);

	call	?pmmngr_get_total_ram@@YA_KXZ		; pmmngr_get_total_ram
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	QWORD PTR tv67[rsp], rax
	call	?pmmngr_get_used_ram@@YA_KXZ		; pmmngr_get_used_ram
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	rcx, QWORD PTR tv67[rsp]
	mov	r8, rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:$SG3891
	call	?_debug_print_@@YAXPEADZZ		; _debug_print_

; 61   : 	force_sched();

	call	?force_sched@@YAXXZ			; force_sched

; 62   : }

	add	rsp, 56					; 00000038H
	ret	0
?sys_exit@@YAXXZ ENDP					; sys_exit
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysproc.cpp
_TEXT	SEGMENT
id$ = 32
name$ = 64
procnm$ = 72
?create__sys_process@@YAHPEBDPEAD@Z PROC		; create__sys_process

; 44   : int create__sys_process (const char* name, char* procnm) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 45   : 	x64_cli();

	call	x64_cli

; 46   : 	int id = AuCreateProcess (name, procnm);

	mov	rdx, QWORD PTR procnm$[rsp]
	mov	rcx, QWORD PTR name$[rsp]
	call	?AuCreateProcess@@YAHPEBDPEAD@Z		; AuCreateProcess
	mov	DWORD PTR id$[rsp], eax

; 47   : 	/*int master_fd = get_current_thread()->master_fd;
; 48   : 	ttype_dup_master(id, master_fd);*/
; 49   : 	return 0;

	xor	eax, eax

; 50   : }

	add	rsp, 56					; 00000038H
	ret	0
?create__sys_process@@YAHPEBDPEAD@Z ENDP		; create__sys_process
_TEXT	ENDS
END
