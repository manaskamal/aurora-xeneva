; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?sys_get_current_time@@YAXPEAU_sys_time_@@@Z	; sys_get_current_time
PUBLIC	?sys_get_system_tick@@YAIXZ			; sys_get_system_tick
EXTRN	x64_cli:PROC
EXTRN	AuGetYear:PROC
EXTRN	AuGetSecond:PROC
EXTRN	AuGetDay:PROC
EXTRN	AuGetHour:PROC
EXTRN	AuGetMinutes:PROC
EXTRN	AuGetCentury:PROC
EXTRN	AuGetMonth:PROC
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	?sched_get_tick@@YAIXZ:PROC			; sched_get_tick
pdata	SEGMENT
$pdata$?sys_get_current_time@@YAXPEAU_sys_time_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+127
	DD	imagerel $unwind$?sys_get_current_time@@YAXPEAU_sys_time_@@@Z
$pdata$?sys_get_system_tick@@YAIXZ DD imagerel $LN3
	DD	imagerel $LN3+19
	DD	imagerel $unwind$?sys_get_system_tick@@YAIXZ
pdata	ENDS
xdata	SEGMENT
$unwind$?sys_get_current_time@@YAXPEAU_sys_time_@@@Z DD 010901H
	DD	04209H
$unwind$?sys_get_system_tick@@YAIXZ DD 010401H
	DD	04204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\systime.cpp
_TEXT	SEGMENT
?sys_get_system_tick@@YAIXZ PROC			; sys_get_system_tick

; 30   : uint32_t sys_get_system_tick () {

$LN3:
	sub	rsp, 40					; 00000028H

; 31   : 	x64_cli();

	call	x64_cli

; 32   : 	return sched_get_tick();

	call	?sched_get_tick@@YAIXZ			; sched_get_tick

; 33   : }

	add	rsp, 40					; 00000028H
	ret	0
?sys_get_system_tick@@YAIXZ ENDP			; sys_get_system_tick
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\systime.cpp
_TEXT	SEGMENT
time$ = 48
?sys_get_current_time@@YAXPEAU_sys_time_@@@Z PROC	; sys_get_current_time

; 18   : void sys_get_current_time (sys_time *time) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 19   : 	x64_cli();

	call	x64_cli

; 20   : 	memset (time, 0, sizeof(sys_time));

	mov	r8d, 7
	xor	edx, edx
	mov	rcx, QWORD PTR time$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 21   : 	time->seconds = AuGetSecond();

	call	AuGetSecond
	mov	rcx, QWORD PTR time$[rsp]
	mov	BYTE PTR [rcx], al

; 22   : 	time->minutes = AuGetMinutes();

	call	AuGetMinutes
	mov	rcx, QWORD PTR time$[rsp]
	mov	BYTE PTR [rcx+1], al

; 23   : 	time->hour = AuGetHour();

	call	AuGetHour
	mov	rcx, QWORD PTR time$[rsp]
	mov	BYTE PTR [rcx+2], al

; 24   : 	time->day = AuGetDay();

	call	AuGetDay
	mov	rcx, QWORD PTR time$[rsp]
	mov	BYTE PTR [rcx+3], al

; 25   : 	time->month = AuGetMonth();

	call	AuGetMonth
	mov	rcx, QWORD PTR time$[rsp]
	mov	BYTE PTR [rcx+4], al

; 26   : 	time->year = AuGetYear();

	call	AuGetYear
	mov	rcx, QWORD PTR time$[rsp]
	mov	BYTE PTR [rcx+5], al

; 27   : 	time->century = AuGetCentury();

	call	AuGetCentury
	mov	rcx, QWORD PTR time$[rsp]
	mov	BYTE PTR [rcx+6], al

; 28   : }

	add	rsp, 40					; 00000028H
	ret	0
?sys_get_current_time@@YAXPEAU_sys_time_@@@Z ENDP	; sys_get_current_time
_TEXT	ENDS
END
