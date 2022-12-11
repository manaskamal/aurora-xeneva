; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?kyboard_thr@@3PEAU_thread_@@EA			; kyboard_thr
_BSS	SEGMENT
?kyboard_thr@@3PEAU_thread_@@EA DQ 01H DUP (?)		; kyboard_thr
_BSS	ENDS
CONST	SEGMENT
$SG3635	DB	'[Aurora]:Key Pressed', 0aH, 00H
	ORG $+2
$SG3652	DB	'kybrd', 00H
	ORG $+2
$SG3653	DB	'/dev/kybrd', 00H
CONST	ENDS
PUBLIC	?AuKeyboardInitialize@@YAXXZ			; AuKeyboardInitialize
PUBLIC	?AuKeyboardSendCmd@@YAXE@Z			; AuKeyboardSendCmd
PUBLIC	?AuKeyboardSetLight@@YAX_N00@Z			; AuKeyboardSetLight
PUBLIC	?AuKeyboardHandler@@YAX_KPEAX@Z			; AuKeyboardHandler
PUBLIC	?kybrd_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z	; kybrd_ioquery
EXTRN	x64_cli:PROC
EXTRN	inportb:PROC
EXTRN	outportb:PROC
EXTRN	AuInterruptEnd:PROC
EXTRN	AuInterruptSet:PROC
EXTRN	strcpy:PROC
EXTRN	printf:PROC
EXTRN	vfs_mount:PROC
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuPmmngrFree:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	malloc:PROC
EXTRN	get_current_thread:PROC
EXTRN	?is_scheduler_initialized@@YA_NXZ:PROC		; is_scheduler_initialized
EXTRN	?message_send@@YAXGPEAU_message_@@@Z:PROC	; message_send
_BSS	SEGMENT
__Au_capslock_key DB 01H DUP (?)
	ALIGN	4

__Au_numlock_key DB 01H DUP (?)
	ALIGN	4

__Au_scroll_lock_key DB 01H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?AuKeyboardInitialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+273
	DD	imagerel $unwind$?AuKeyboardInitialize@@YAXXZ
$pdata$?AuKeyboardSendCmd@@YAXE@Z DD imagerel $LN6
	DD	imagerel $LN6+57
	DD	imagerel $unwind$?AuKeyboardSendCmd@@YAXE@Z
$pdata$?AuKeyboardSetLight@@YAX_N00@Z DD imagerel $LN9
	DD	imagerel $LN9+176
	DD	imagerel $unwind$?AuKeyboardSetLight@@YAX_N00@Z
$pdata$?AuKeyboardHandler@@YAX_KPEAX@Z DD imagerel $LN10
	DD	imagerel $LN10+248
	DD	imagerel $unwind$?AuKeyboardHandler@@YAX_KPEAX@Z
$pdata$?kybrd_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+65
	DD	imagerel $unwind$?kybrd_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuKeyboardInitialize@@YAXXZ DD 010401H
	DD	06204H
$unwind$?AuKeyboardSendCmd@@YAXE@Z DD 010801H
	DD	04208H
$unwind$?AuKeyboardSetLight@@YAX_N00@Z DD 011101H
	DD	06211H
$unwind$?AuKeyboardHandler@@YAX_KPEAX@Z DD 010e01H
	DD	0820eH
$unwind$?kybrd_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z DD 011201H
	DD	06212H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\kybrd.cpp
_TEXT	SEGMENT
tv64 = 32
file$ = 64
code$ = 72
arg$ = 80
?kybrd_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z PROC		; kybrd_ioquery

; 97   : int kybrd_ioquery (vfs_node_t* file, int code, void* arg) {

$LN6:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 98   : 	x64_cli();

	call	x64_cli

; 99   : 	switch(code) {

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv64[rsp], eax
	cmp	DWORD PTR tv64[rsp], 400		; 00000190H
	je	SHORT $LN1@kybrd_ioqu
	jmp	SHORT $LN2@kybrd_ioqu
$LN1@kybrd_ioqu:

; 100  : 	case KYBRD_IOQUERY_REGISTER_THREAD:
; 101  : 		kyboard_thr = get_current_thread();

	call	get_current_thread
	mov	QWORD PTR ?kyboard_thr@@3PEAU_thread_@@EA, rax ; kyboard_thr
$LN2@kybrd_ioqu:

; 102  : 		break;
; 103  : 	}
; 104  : 
; 105  : 	return 1;

	mov	eax, 1

; 106  : }

	add	rsp, 56					; 00000038H
	ret	0
?kybrd_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP		; kybrd_ioquery
_TEXT	ENDS
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

; 57   : {

$LN10:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 58   : 	static bool _extended = false;
; 59   : 	int code = 0;

	mov	DWORD PTR code$[rsp], 0

; 60   : 	//! read scan code only if the kybrd controller output buffer is full (scan mode is in it)
; 61   : 	if (inportb(0x64) & 1)

	mov	cx, 100					; 00000064H
	call	inportb
	movzx	eax, al
	and	eax, 1
	test	eax, eax
	je	$LN5@AuKeyboard

; 62   : 	{
; 63   : 		int code = inportb(0x60);

	mov	cx, 96					; 00000060H
	call	inportb
	movzx	eax, al
	mov	DWORD PTR code$1[rsp], eax

; 64   : 		if (is_scheduler_initialized()) {

	call	?is_scheduler_initialized@@YA_NXZ	; is_scheduler_initialized
	movzx	eax, al
	test	eax, eax
	je	$LN4@AuKeyboard

; 65   : 			if (code == 0x3a) {

	cmp	DWORD PTR code$1[rsp], 58		; 0000003aH
	jne	SHORT $LN3@AuKeyboard

; 66   : 				__Au_capslock_key = !__Au_capslock_key;

	movzx	eax, BYTE PTR __Au_capslock_key
	test	eax, eax
	jne	SHORT $LN8@AuKeyboard
	mov	DWORD PTR tv78[rsp], 1
	jmp	SHORT $LN9@AuKeyboard
$LN8@AuKeyboard:
	mov	DWORD PTR tv78[rsp], 0
$LN9@AuKeyboard:
	movzx	eax, BYTE PTR tv78[rsp]
	mov	BYTE PTR __Au_capslock_key, al
$LN3@AuKeyboard:

; 67   : 			}
; 68   : 
; 69   : 			if (kyboard_thr != NULL) {

	cmp	QWORD PTR ?kyboard_thr@@3PEAU_thread_@@EA, 0 ; kyboard_thr
	je	SHORT $LN2@AuKeyboard

; 70   : 				message_t *msg = (message_t*)p2v((size_t)AuPmmngrAlloc());

	call	AuPmmngrAlloc
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR msg$2[rsp], rax

; 71   : 				msg->type = 3;

	mov	eax, 3
	mov	rcx, QWORD PTR msg$2[rsp]
	mov	WORD PTR [rcx+56], ax

; 72   : 				msg->dword = code;

	mov	rax, QWORD PTR msg$2[rsp]
	mov	ecx, DWORD PTR code$1[rsp]
	mov	DWORD PTR [rax], ecx

; 73   : 				message_send (kyboard_thr->id,msg);

	mov	rdx, QWORD PTR msg$2[rsp]
	mov	rax, QWORD PTR ?kyboard_thr@@3PEAU_thread_@@EA ; kyboard_thr
	movzx	ecx, WORD PTR [rax+238]
	call	?message_send@@YAXGPEAU_message_@@@Z	; message_send

; 74   : 				AuPmmngrFree ((void*)v2p((size_t)msg));

	mov	rcx, QWORD PTR msg$2[rsp]
	call	v2p
	mov	rcx, rax
	call	AuPmmngrFree
$LN2@AuKeyboard:

; 75   : 			}
; 76   : 		} else {

	jmp	SHORT $LN1@AuKeyboard
$LN4@AuKeyboard:

; 77   : 			printf ("[Aurora]:Key Pressed\n");

	lea	rcx, OFFSET FLAT:$SG3635
	call	printf
$LN1@AuKeyboard:
$LN5@AuKeyboard:
$end$11:

; 78   : 		}
; 79   : 
; 80   : 		/*thread_t* thr = (thread_t*)thread_iterate_ready_list (1);
; 81   : 	    if (thr != NULL){
; 82   : 			unblock_thread(thr);
; 83   : 		}*/
; 84   : 		//!Here we need to pass this code to window manager process {a.k.a DWM} or shell program
; 85   : 		//!shell will decode the scancode and will take action
; 86   : 	}
; 87   : 
; 88   : 
; 89   : 	//AuKeyboardSetLight(__Au_numlock_key, __Au_capslock_key, __Au_scroll_lock_key);
; 90   : 
; 91   :  end:
; 92   : 	//! tell apic we are done!!!
; 93   : 	AuInterruptEnd(1);

	mov	ecx, 1
	call	AuInterruptEnd

; 94   : 	return;
; 95   : }

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

; 41   : void AuKeyboardSetLight (bool num, bool caps, bool scroll) {

$LN9:
	mov	BYTE PTR [rsp+24], r8b
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 42   : 	uint8_t data = 0;

	mov	BYTE PTR data$[rsp], 0

; 43   : 
; 44   : 	data = (scroll) ? (data | 1) : (data & 1);

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

; 45   : 	data = (num) ? (num | 2) : (num & 2);

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

; 46   : 	data = (caps) ? (num | 4) : (num & 4);

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

; 47   : 
; 48   : 	AuKeyboardSendCmd(0xED);

	mov	cl, 237					; 000000edH
	call	?AuKeyboardSendCmd@@YAXE@Z		; AuKeyboardSendCmd

; 49   : 	AuKeyboardSendCmd(data);

	movzx	ecx, BYTE PTR data$[rsp]
	call	?AuKeyboardSendCmd@@YAXE@Z		; AuKeyboardSendCmd

; 50   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuKeyboardSetLight@@YAX_N00@Z ENDP			; AuKeyboardSetLight
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\kybrd.cpp
_TEXT	SEGMENT
cmd$ = 48
?AuKeyboardSendCmd@@YAXE@Z PROC				; AuKeyboardSendCmd

; 28   : void AuKeyboardSendCmd (uint8_t cmd) {

$LN6:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H
$LN3@AuKeyboard:

; 29   : 	while(1) 

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN2@AuKeyboard

; 30   : 		if ((inportb(0x64) & 0x2) == 0)

	mov	cx, 100					; 00000064H
	call	inportb
	movzx	eax, al
	and	eax, 2
	test	eax, eax
	jne	SHORT $LN1@AuKeyboard

; 31   : 			break;

	jmp	SHORT $LN2@AuKeyboard
$LN1@AuKeyboard:

; 32   : 	outportb(0x60, cmd);

	jmp	SHORT $LN3@AuKeyboard
$LN2@AuKeyboard:
	movzx	edx, BYTE PTR cmd$[rsp]
	mov	cx, 96					; 00000060H
	call	outportb

; 33   : }

	add	rsp, 40					; 00000028H
	ret	0
?AuKeyboardSendCmd@@YAXE@Z ENDP				; AuKeyboardSendCmd
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\kybrd.cpp
_TEXT	SEGMENT
node$ = 32
?AuKeyboardInitialize@@YAXXZ PROC			; AuKeyboardInitialize

; 112  : void AuKeyboardInitialize () {

$LN3:
	sub	rsp, 56					; 00000038H

; 113  : 	AuInterruptSet (1,AuKeyboardHandler,1, false);

	xor	r9d, r9d
	mov	r8b, 1
	lea	rdx, OFFSET FLAT:?AuKeyboardHandler@@YAX_KPEAX@Z ; AuKeyboardHandler
	mov	ecx, 1
	call	AuInterruptSet

; 114  : 	__Au_capslock_key = __Au_numlock_key = __Au_scroll_lock_key = false;

	mov	BYTE PTR __Au_scroll_lock_key, 0
	movzx	eax, BYTE PTR __Au_scroll_lock_key
	mov	BYTE PTR __Au_numlock_key, al
	movzx	eax, BYTE PTR __Au_numlock_key
	mov	BYTE PTR __Au_capslock_key, al

; 115  : 
; 116  : 	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 112				; 00000070H
	call	malloc
	mov	QWORD PTR node$[rsp], rax

; 117  : 
; 118  : 	strcpy (node->filename, "kybrd");

	mov	rax, QWORD PTR node$[rsp]
	lea	rdx, OFFSET FLAT:$SG3652
	mov	rcx, rax
	call	strcpy

; 119  : 	node->size = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+32], 0

; 120  : 	node->eof = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+36], 0

; 121  : 	node->pos = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+40], 0

; 122  : 	node->current = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+44], 0

; 123  : 	node->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+48], 12

; 124  : 	node->status = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+49], 0

; 125  : 	node->open = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+64], 0

; 126  : 	node->read = NULL;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+72], 0

; 127  : 	node->write = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+80], 0

; 128  : 	node->read_blk = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+96], 0

; 129  : 	node->ioquery = kybrd_ioquery;

	mov	rax, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:?kybrd_ioquery@@YAHPEAU_vfs_node_@@HPEAX@Z ; kybrd_ioquery
	mov	QWORD PTR [rax+104], rcx

; 130  : 	vfs_mount ("/dev/kybrd", node, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:$SG3653
	call	vfs_mount

; 131  : 
; 132  : 	kyboard_thr = NULL;

	mov	QWORD PTR ?kyboard_thr@@3PEAU_thread_@@EA, 0 ; kyboard_thr

; 133  : 	outportb(0xF0, 1);

	mov	dl, 1
	mov	cx, 240					; 000000f0H
	call	outportb

; 134  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuKeyboardInitialize@@YAXXZ ENDP			; AuKeyboardInitialize
_TEXT	ENDS
END
