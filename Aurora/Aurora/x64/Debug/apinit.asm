; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG2860	DB	'Welcome to Application Processor ', 0aH, 00H
CONST	ENDS
PUBLIC	?AuApInit@@YAXPEAX@Z				; AuApInit
EXTRN	x64_cli:PROC
EXTRN	printf:PROC
EXTRN	?AuAPStarted@@YAXXZ:PROC			; AuAPStarted
pdata	SEGMENT
$pdata$?AuApInit@@YAXPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?AuApInit@@YAXPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuApInit@@YAXPEAX@Z DD 010901H
	DD	04209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apinit.cpp
_TEXT	SEGMENT
cpu$ = 48
?AuApInit@@YAXPEAX@Z PROC				; AuApInit

; 39   : void AuApInit(void* cpu) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 40   : 	x64_cli();

	call	x64_cli

; 41   : 	printf ("Welcome to Application Processor \n");

	lea	rcx, OFFSET FLAT:$SG2860
	call	printf

; 42   : 	AuAPStarted();

	call	?AuAPStarted@@YAXXZ			; AuAPStarted
$LN2@AuApInit:

; 43   : 	for(;;);

	jmp	SHORT $LN2@AuApInit

; 44   : }

	add	rsp, 40					; 00000028H
	ret	0
?AuApInit@@YAXPEAX@Z ENDP				; AuApInit
_TEXT	ENDS
END
