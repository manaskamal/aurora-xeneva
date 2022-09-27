; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3628	DB	'[Aurora]:Key Pressed', 0aH, 00H
CONST	ENDS
PUBLIC	?AuKeyboardInitialize@@YAXXZ			; AuKeyboardInitialize
PUBLIC	?AuKeyboardSendCmd@@YAXE@Z			; AuKeyboardSendCmd
PUBLIC	?AuKeyboardSetLight@@YAX_N00@Z			; AuKeyboardSetLight
PUBLIC	?AuKeyboardHandler@@YAX_KPEAX@Z			; AuKeyboardHandler
EXTRN	inportb:PROC
EXTRN	outportb:PROC
EXTRN	AuInterruptEnd:PROC
EXTRN	AuInterruptSet:PROC
EXTRN	printf:PROC
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuPmmngrFree:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	?is_scheduler_initialized@@YA_NXZ:PROC		; is_scheduler_initialized
EXTRN	?message_send@@YAXGPEAU_message_@@@Z:PROC	; message_send
_BSS	SEGMENT
__Au_capslock_key DB 01H DUP (?)
__Au_numlock_key DB 01H DUP (?)
__Au_scroll_lock_key DB 01H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?AuKeyboardInitialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+76
	DD	imagerel $unwind$?AuKeyboardInitialize@@YAXXZ
$pdata$?AuKeyboardSendCmd@@YAXE@Z DD imagerel $LN6
	DD	imagerel $LN6+57
	DD	imagerel $unwind$?AuKeyboardSendCmd@@YAXE@Z
$pdata$?AuKeyboardSetLight@@YAX_N00@Z DD imagerel $LN9
	DD	imagerel $LN9+176
	DD	imagerel $unwind$?AuKeyboardSetLight@@YAX_N00@Z
$pdata$?AuKeyboardHandler@@YAX_KPEAX@Z DD imagerel $LN9
	DD	imagerel $LN9+224
	DD	imagerel $unwind$?AuKeyboardHandler@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuKeyboardInitialize@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuKeyboardSendCmd@@YAXE@Z DD 010801H
	DD	04208H
$unwind$?AuKeyboardSetLight@@YAX_N00@Z DD 011101H
	DD	06211H
$unwind$?AuKeyboardHandler@@YAX_KPEAX@Z DD 010e01H
	DD	0820eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\kybrd.cpp
_TEXT	SEGMENT
tv78 = 32
code$1 = 36
code$ = 40
msg$2 = 48
v$ = 80
p$ = 88
?AuKeyboardHandler@@YAX_KPEAX@Z PROC			; AuKeyboardHandler

; 52   : {

$LN9:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 53   : 	static bool _extended = false;
; 54   : 	int code = 0;

	mov	DWORD PTR code$[rsp], 0

; 55   : 	//! read scan code only if the kybrd controller output buffer is full (scan mode is in it)
; 56   : 	if (inportb(0x64) & 1)

	mov	cx, 100					; 00000064H
	call	inportb
	movzx	eax, al
	and	eax, 1
	test	eax, eax
	je	$LN4@AuKeyboard

; 57   : 	{
; 58   : 		int code = inportb(0x60);

	mov	cx, 96					; 00000060H
	call	inportb
	movzx	eax, al
	mov	DWORD PTR code$1[rsp], eax

; 59   : 		if (is_scheduler_initialized()) {

	call	?is_scheduler_initialized@@YA_NXZ	; is_scheduler_initialized
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN3@AuKeyboard

; 60   : 			if (code == 0x3a) {

	cmp	DWORD PTR code$1[rsp], 58		; 0000003aH
	jne	SHORT $LN2@AuKeyboard

; 61   : 				__Au_capslock_key = !__Au_capslock_key;

	movzx	eax, BYTE PTR __Au_capslock_key
	test	eax, eax
	jne	SHORT $LN7@AuKeyboard
	mov	DWORD PTR tv78[rsp], 1
	jmp	SHORT $LN8@AuKeyboard
$LN7@AuKeyboard:
	mov	DWORD PTR tv78[rsp], 0
$LN8@AuKeyboard:
	movzx	eax, BYTE PTR tv78[rsp]
	mov	BYTE PTR __Au_capslock_key, al
$LN2@AuKeyboard:

; 62   : 			}
; 63   : 
; 64   : 			message_t *msg = (message_t*)p2v((size_t)AuPmmngrAlloc());

	call	AuPmmngrAlloc
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR msg$2[rsp], rax

; 65   : 			msg->type = 3;

	mov	eax, 3
	mov	rcx, QWORD PTR msg$2[rsp]
	mov	WORD PTR [rcx+56], ax

; 66   : 		    msg->dword = code;

	mov	rax, QWORD PTR msg$2[rsp]
	mov	ecx, DWORD PTR code$1[rsp]
	mov	DWORD PTR [rax], ecx

; 67   : 		    message_send (2,msg);

	mov	rdx, QWORD PTR msg$2[rsp]
	mov	cx, 2
	call	?message_send@@YAXGPEAU_message_@@@Z	; message_send

; 68   : 			AuPmmngrFree ((void*)v2p((size_t)msg));

	mov	rcx, QWORD PTR msg$2[rsp]
	call	v2p
	mov	rcx, rax
	call	AuPmmngrFree

; 69   : 		} else {

	jmp	SHORT $LN1@AuKeyboard
$LN3@AuKeyboard:

; 70   : 			printf ("[Aurora]:Key Pressed\n");

	lea	rcx, OFFSET FLAT:$SG3628
	call	printf
$LN1@AuKeyboard:
$LN4@AuKeyboard:
$end$10:

; 71   : 		}
; 72   : 
; 73   : 		/*thread_t* thr = (thread_t*)thread_iterate_ready_list (1);
; 74   : 	    if (thr != NULL){
; 75   : 			unblock_thread(thr);
; 76   : 		}*/
; 77   : 		//!Here we need to pass this code to window manager process {a.k.a DWM} or shell program
; 78   : 		//!shell will decode the scancode and will take action
; 79   : 	}
; 80   : 
; 81   : 
; 82   : 	//AuKeyboardSetLight(__Au_numlock_key, __Au_capslock_key, __Au_scroll_lock_key);
; 83   : 
; 84   :  end:
; 85   : 	//! tell apic we are done!!!
; 86   : 	AuInterruptEnd(1);

	mov	ecx, 1
	call	AuInterruptEnd

; 87   : 	return;
; 88   : }

	add	rsp, 72					; 00000048H
	ret	0
?AuKeyboardHandler@@YAX_KPEAX@Z ENDP			; AuKeyboardHandler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\kybrd.cpp
_TEXT	SEGMENT
data$ = 32
tv70 = 36
tv78 = 40
tv86 = 44
num$ = 64
caps$ = 72
scroll$ = 80
?AuKeyboardSetLight@@YAX_N00@Z PROC			; AuKeyboardSetLight

; 36   : void AuKeyboardSetLight (bool num, bool caps, bool scroll) {

$LN9:
	mov	BYTE PTR [rsp+24], r8b
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 37   : 	uint8_t data = 0;

	mov	BYTE PTR data$[rsp], 0

; 38   : 
; 39   : 	data = (scroll) ? (data | 1) : (data & 1);

	movzx	eax, BYTE PTR scroll$[rsp]
	test	eax, eax
	je	SHORT $LN3@AuKeyboard
	movzx	eax, BYTE PTR data$[rsp]
	or	eax, 1
	mov	DWORD PTR tv70[rsp], eax
	jmp	SHORT $LN4@AuKeyboard
$LN3@AuKeyboard:
	movzx	eax, BYTE PTR data$[rsp]
	and	eax, 1
	mov	DWORD PTR tv70[rsp], eax
$LN4@AuKeyboard:
	movzx	eax, BYTE PTR tv70[rsp]
	mov	BYTE PTR data$[rsp], al

; 40   : 	data = (num) ? (num | 2) : (num & 2);

	movzx	eax, BYTE PTR num$[rsp]
	test	eax, eax
	je	SHORT $LN5@AuKeyboard
	movzx	eax, BYTE PTR num$[rsp]
	or	eax, 2
	mov	DWORD PTR tv78[rsp], eax
	jmp	SHORT $LN6@AuKeyboard
$LN5@AuKeyboard:
	movzx	eax, BYTE PTR num$[rsp]
	and	eax, 2
	mov	DWORD PTR tv78[rsp], eax
$LN6@AuKeyboard:
	movzx	eax, BYTE PTR tv78[rsp]
	mov	BYTE PTR data$[rsp], al

; 41   : 	data = (caps) ? (num | 4) : (num & 4);

	movzx	eax, BYTE PTR caps$[rsp]
	test	eax, eax
	je	SHORT $LN7@AuKeyboard
	movzx	eax, BYTE PTR num$[rsp]
	or	eax, 4
	mov	DWORD PTR tv86[rsp], eax
	jmp	SHORT $LN8@AuKeyboard
$LN7@AuKeyboard:
	movzx	eax, BYTE PTR num$[rsp]
	and	eax, 4
	mov	DWORD PTR tv86[rsp], eax
$LN8@AuKeyboard:
	movzx	eax, BYTE PTR tv86[rsp]
	mov	BYTE PTR data$[rsp], al

; 42   : 
; 43   : 	AuKeyboardSendCmd(0xED);

	mov	cl, 237					; 000000edH
	call	?AuKeyboardSendCmd@@YAXE@Z		; AuKeyboardSendCmd

; 44   : 	AuKeyboardSendCmd(data);

	movzx	ecx, BYTE PTR data$[rsp]
	call	?AuKeyboardSendCmd@@YAXE@Z		; AuKeyboardSendCmd

; 45   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuKeyboardSetLight@@YAX_N00@Z ENDP			; AuKeyboardSetLight
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\kybrd.cpp
_TEXT	SEGMENT
cmd$ = 48
?AuKeyboardSendCmd@@YAXE@Z PROC				; AuKeyboardSendCmd

; 22   : void AuKeyboardSendCmd (uint8_t cmd) {

$LN6:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H
$LN3@AuKeyboard:

; 23   : 	
; 24   : 	while(1) 

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN2@AuKeyboard

; 25   : 		if ((inportb(0x64) & 0x2) == 0)

	mov	cx, 100					; 00000064H
	call	inportb
	movzx	eax, al
	and	eax, 2
	test	eax, eax
	jne	SHORT $LN1@AuKeyboard

; 26   : 			break;

	jmp	SHORT $LN2@AuKeyboard
$LN1@AuKeyboard:

; 27   : 	outportb(0x60, cmd);

	jmp	SHORT $LN3@AuKeyboard
$LN2@AuKeyboard:
	movzx	edx, BYTE PTR cmd$[rsp]
	mov	cx, 96					; 00000060H
	call	outportb

; 28   : }

	add	rsp, 40					; 00000028H
	ret	0
?AuKeyboardSendCmd@@YAXE@Z ENDP				; AuKeyboardSendCmd
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\kybrd.cpp
_TEXT	SEGMENT
?AuKeyboardInitialize@@YAXXZ PROC			; AuKeyboardInitialize

; 96   : void AuKeyboardInitialize () {

$LN3:
	sub	rsp, 40					; 00000028H

; 97   : 	AuInterruptSet (1,AuKeyboardHandler,1, false);

	xor	r9d, r9d
	mov	r8b, 1
	lea	rdx, OFFSET FLAT:?AuKeyboardHandler@@YAX_KPEAX@Z ; AuKeyboardHandler
	mov	ecx, 1
	call	AuInterruptSet

; 98   : 	__Au_capslock_key = __Au_numlock_key = __Au_scroll_lock_key = false;

	mov	BYTE PTR __Au_scroll_lock_key, 0
	movzx	eax, BYTE PTR __Au_scroll_lock_key
	mov	BYTE PTR __Au_numlock_key, al
	movzx	eax, BYTE PTR __Au_numlock_key
	mov	BYTE PTR __Au_capslock_key, al

; 99   : 	outportb(0xF0, 1);

	mov	dl, 1
	mov	cx, 240					; 000000f0H
	call	outportb

; 100  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuKeyboardInitialize@@YAXXZ ENDP			; AuKeyboardInitialize
_TEXT	ENDS
END
