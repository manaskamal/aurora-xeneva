; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3520	DB	'[Aurora]:Key Pressed', 0aH, 00H
CONST	ENDS
PUBLIC	?AuKeyboardInitialize@@YAXXZ			; AuKeyboardInitialize
PUBLIC	?AuKeyboardHandler@@YAX_KPEAX@Z			; AuKeyboardHandler
EXTRN	inportb:PROC
EXTRN	AuInterruptEnd:PROC
EXTRN	AuInterruptSet:PROC
EXTRN	printf:PROC
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuPmmngrFree:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	?is_scheduler_initialized@@YA_NXZ:PROC		; is_scheduler_initialized
EXTRN	?message_send@@YAXGPEAU_message_@@@Z:PROC	; message_send
pdata	SEGMENT
$pdata$?AuKeyboardInitialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+32
	DD	imagerel $unwind$?AuKeyboardInitialize@@YAXXZ
$pdata$?AuKeyboardHandler@@YAX_KPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+173
	DD	imagerel $unwind$?AuKeyboardHandler@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuKeyboardInitialize@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuKeyboardHandler@@YAX_KPEAX@Z DD 010e01H
	DD	0620eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\kybrd.cpp
_TEXT	SEGMENT
code$1 = 32
code$ = 36
msg$2 = 40
v$ = 64
p$ = 72
?AuKeyboardHandler@@YAX_KPEAX@Z PROC			; AuKeyboardHandler

; 22   : {

$LN6:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 23   : 	static bool _extended = false;
; 24   : 	int code = 0;

	mov	DWORD PTR code$[rsp], 0

; 25   : 	//! read scan code only if the kybrd controller output buffer is full (scan mode is in it)
; 26   : 	if (inportb(0x64) & 1)

	mov	cx, 100					; 00000064H
	call	inportb
	movzx	eax, al
	and	eax, 1
	test	eax, eax
	je	SHORT $LN3@AuKeyboard

; 27   : 	{
; 28   : 		int code = inportb(0x60);

	mov	cx, 96					; 00000060H
	call	inportb
	movzx	eax, al
	mov	DWORD PTR code$1[rsp], eax

; 29   : 		if (is_scheduler_initialized()) {

	call	?is_scheduler_initialized@@YA_NXZ	; is_scheduler_initialized
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN2@AuKeyboard

; 30   : 			message_t *msg = (message_t*)p2v((size_t)AuPmmngrAlloc());

	call	AuPmmngrAlloc
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR msg$2[rsp], rax

; 31   : 			msg->type = 3;

	mov	eax, 3
	mov	rcx, QWORD PTR msg$2[rsp]
	mov	WORD PTR [rcx+56], ax

; 32   : 		    msg->dword = code;

	mov	rax, QWORD PTR msg$2[rsp]
	mov	ecx, DWORD PTR code$1[rsp]
	mov	DWORD PTR [rax], ecx

; 33   : 		    message_send (2,msg);

	mov	rdx, QWORD PTR msg$2[rsp]
	mov	cx, 2
	call	?message_send@@YAXGPEAU_message_@@@Z	; message_send

; 34   : 			AuPmmngrFree ((void*)v2p((size_t)msg));

	mov	rcx, QWORD PTR msg$2[rsp]
	call	v2p
	mov	rcx, rax
	call	AuPmmngrFree

; 35   : 		} else {

	jmp	SHORT $LN1@AuKeyboard
$LN2@AuKeyboard:

; 36   : 			printf ("[Aurora]:Key Pressed\n");

	lea	rcx, OFFSET FLAT:$SG3520
	call	printf
$LN1@AuKeyboard:
$LN3@AuKeyboard:
$end$7:

; 37   : 		}
; 38   : 
; 39   : 		/*thread_t* thr = (thread_t*)thread_iterate_ready_list (1);
; 40   : 	    if (thr != NULL){
; 41   : 			unblock_thread(thr);
; 42   : 		}*/
; 43   : 		//!Here we need to pass this code to window manager process {a.k.a DWM} or shell program
; 44   : 		//!shell will decode the scancode and will take action
; 45   : 	}
; 46   : 
; 47   :  end:
; 48   : 	//! tell apic we are done!!!
; 49   : 	AuInterruptEnd(1);

	mov	ecx, 1
	call	AuInterruptEnd

; 50   : 	return;
; 51   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuKeyboardHandler@@YAX_KPEAX@Z ENDP			; AuKeyboardHandler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\kybrd.cpp
_TEXT	SEGMENT
?AuKeyboardInitialize@@YAXXZ PROC			; AuKeyboardInitialize

; 59   : void AuKeyboardInitialize () {

$LN3:
	sub	rsp, 40					; 00000028H

; 60   : 	AuInterruptSet (1,AuKeyboardHandler,1, false);

	xor	r9d, r9d
	mov	r8b, 1
	lea	rdx, OFFSET FLAT:?AuKeyboardHandler@@YAX_KPEAX@Z ; AuKeyboardHandler
	mov	ecx, 1
	call	AuInterruptSet

; 61   : }

	add	rsp, 40					; 00000028H
	ret	0
?AuKeyboardInitialize@@YAXXZ ENDP			; AuKeyboardInitialize
_TEXT	ENDS
END
