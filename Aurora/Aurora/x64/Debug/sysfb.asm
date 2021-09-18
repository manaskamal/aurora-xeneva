; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?sys_get_fb_mem@@YAPEAIXZ			; sys_get_fb_mem
PUBLIC	?sys_fb_update@@YAXXZ				; sys_fb_update
PUBLIC	?sys_fb_move_cursor@@YAXII@Z			; sys_fb_move_cursor
EXTRN	x64_cli:PROC
EXTRN	?svga_update@@YAXIIII@Z:PROC			; svga_update
EXTRN	?svga_get_fb_mem@@YAPEAIXZ:PROC			; svga_get_fb_mem
EXTRN	?hw_move_cursor@@YAXPEAIII@Z:PROC		; hw_move_cursor
EXTRN	?get_screen_width@@YAIXZ:PROC			; get_screen_width
EXTRN	?get_screen_height@@YAIXZ:PROC			; get_screen_height
pdata	SEGMENT
$pdata$?sys_get_fb_mem@@YAPEAIXZ DD imagerel $LN3
	DD	imagerel $LN3+19
	DD	imagerel $unwind$?sys_get_fb_mem@@YAPEAIXZ
$pdata$?sys_fb_update@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+47
	DD	imagerel $unwind$?sys_fb_update@@YAXXZ
$pdata$?sys_fb_move_cursor@@YAXII@Z DD imagerel $LN3
	DD	imagerel $LN3+38
	DD	imagerel $unwind$?sys_fb_move_cursor@@YAXII@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?sys_get_fb_mem@@YAPEAIXZ DD 010401H
	DD	04204H
$unwind$?sys_fb_update@@YAXXZ DD 010401H
	DD	06204H
$unwind$?sys_fb_move_cursor@@YAXII@Z DD 010c01H
	DD	0420cH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfb.cpp
_TEXT	SEGMENT
x$ = 48
y$ = 56
?sys_fb_move_cursor@@YAXII@Z PROC			; sys_fb_move_cursor

; 31   : void sys_fb_move_cursor (uint32_t x, uint32_t y) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 32   : 	x64_cli();

	call	x64_cli

; 33   : 	hw_move_cursor (NULL, x, y);

	mov	r8d, DWORD PTR y$[rsp]
	mov	edx, DWORD PTR x$[rsp]
	xor	ecx, ecx
	call	?hw_move_cursor@@YAXPEAIII@Z		; hw_move_cursor

; 34   : }

	add	rsp, 40					; 00000028H
	ret	0
?sys_fb_move_cursor@@YAXII@Z ENDP			; sys_fb_move_cursor
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfb.cpp
_TEXT	SEGMENT
tv64 = 32
?sys_fb_update@@YAXXZ PROC				; sys_fb_update

; 26   : void sys_fb_update () {

$LN3:
	sub	rsp, 56					; 00000038H

; 27   : 	x64_cli();

	call	x64_cli

; 28   : 	svga_update (0,0,get_screen_width(),get_screen_height());

	call	?get_screen_height@@YAIXZ		; get_screen_height
	mov	DWORD PTR tv64[rsp], eax
	call	?get_screen_width@@YAIXZ		; get_screen_width
	mov	ecx, DWORD PTR tv64[rsp]
	mov	r9d, ecx
	mov	r8d, eax
	xor	edx, edx
	xor	ecx, ecx
	call	?svga_update@@YAXIIII@Z			; svga_update

; 29   : }

	add	rsp, 56					; 00000038H
	ret	0
?sys_fb_update@@YAXXZ ENDP				; sys_fb_update
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfb.cpp
_TEXT	SEGMENT
?sys_get_fb_mem@@YAPEAIXZ PROC				; sys_get_fb_mem

; 20   : uint32_t* sys_get_fb_mem () {

$LN3:
	sub	rsp, 40					; 00000028H

; 21   : 	x64_cli();

	call	x64_cli

; 22   : 	return svga_get_fb_mem();

	call	?svga_get_fb_mem@@YAPEAIXZ		; svga_get_fb_mem

; 23   : }

	add	rsp, 40					; 00000028H
	ret	0
?sys_get_fb_mem@@YAPEAIXZ ENDP				; sys_get_fb_mem
_TEXT	ENDS
END
