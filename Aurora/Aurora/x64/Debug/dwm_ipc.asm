; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?dwm_queue@@3PA_KA				; dwm_queue
_BSS	SEGMENT
?dwm_queue@@3PA_KA DQ 0200H DUP (?)			; dwm_queue
_BSS	ENDS
PUBLIC	?dwm_ipc_init@@YAXXZ				; dwm_ipc_init
PUBLIC	?dwm_put_message@@YAXPEAU_dwm_message_@@@Z	; dwm_put_message
PUBLIC	?dwm_dispatch_message@@YAXPEAU_dwm_message_@@@Z	; dwm_dispatch_message
PUBLIC	?get_dwm_message_q_address@@YAPEA_KXZ		; get_dwm_message_q_address
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	memcpy:PROC
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	x64_cli:PROC
EXTRN	?map_page@@YA_N_K0E@Z:PROC			; map_page
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
EXTRN	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z:PROC ; thread_iterate_ready_list
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
EXTRN	?create_mutex@@YAPEAUmutex_t@@XZ:PROC		; create_mutex
EXTRN	?mutex_lock@@YAXPEAUmutex_t@@@Z:PROC		; mutex_lock
EXTRN	?mutex_unlock@@YAXPEAUmutex_t@@@Z:PROC		; mutex_unlock
_BSS	SEGMENT
msg_mutex DQ	01H DUP (?)
msg_rcv_mutex DQ 01H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?dwm_ipc_init@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+60
	DD	imagerel $unwind$?dwm_ipc_init@@YAXXZ
$pdata$?dwm_put_message@@YAXPEAU_dwm_message_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+132
	DD	imagerel $unwind$?dwm_put_message@@YAXPEAU_dwm_message_@@@Z
$pdata$?dwm_dispatch_message@@YAXPEAU_dwm_message_@@@Z DD imagerel $LN4
	DD	imagerel $LN4+118
	DD	imagerel $unwind$?dwm_dispatch_message@@YAXPEAU_dwm_message_@@@Z
pdata	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$??__Emsg_mutex@@YAXXZ DD imagerel ??__Emsg_mutex@@YAXXZ
	DD	imagerel ??__Emsg_mutex@@YAXXZ+21
	DD	imagerel $unwind$??__Emsg_mutex@@YAXXZ
pdata	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$??__Emsg_rcv_mutex@@YAXXZ DD imagerel ??__Emsg_rcv_mutex@@YAXXZ
	DD	imagerel ??__Emsg_rcv_mutex@@YAXXZ+21
	DD	imagerel $unwind$??__Emsg_rcv_mutex@@YAXXZ
pdata	ENDS
CRT$XCU	SEGMENT
msg_mutex$initializer$ DQ FLAT:??__Emsg_mutex@@YAXXZ
CRT$XCU	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$??__Emsg_rcv_mutex@@YAXXZ DD 010401H
	DD	04204H
xdata	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$??__Emsg_mutex@@YAXXZ DD 010401H
	DD	04204H
xdata	ENDS
xdata	SEGMENT
$unwind$?dwm_ipc_init@@YAXXZ DD 010401H
	DD	06204H
$unwind$?dwm_put_message@@YAXPEAU_dwm_message_@@@Z DD 010901H
	DD	06209H
$unwind$?dwm_dispatch_message@@YAXPEAU_dwm_message_@@@Z DD 010901H
	DD	06209H
xdata	ENDS
CRT$XCU	SEGMENT
msg_rcv_mutex$initializer$ DQ FLAT:??__Emsg_rcv_mutex@@YAXXZ
CRT$XCU	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\dwm_ipc.cpp
;	COMDAT ??__Emsg_rcv_mutex@@YAXXZ
text$yc	SEGMENT
??__Emsg_rcv_mutex@@YAXXZ PROC				; `dynamic initializer for 'msg_rcv_mutex'', COMDAT

; 19   : static mutex_t *msg_rcv_mutex = create_mutex();

	sub	rsp, 40					; 00000028H
	call	?create_mutex@@YAPEAUmutex_t@@XZ	; create_mutex
	mov	QWORD PTR msg_rcv_mutex, rax
	add	rsp, 40					; 00000028H
	ret	0
??__Emsg_rcv_mutex@@YAXXZ ENDP				; `dynamic initializer for 'msg_rcv_mutex''
text$yc	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\dwm_ipc.cpp
;	COMDAT ??__Emsg_mutex@@YAXXZ
text$yc	SEGMENT
??__Emsg_mutex@@YAXXZ PROC				; `dynamic initializer for 'msg_mutex'', COMDAT

; 18   : static mutex_t *msg_mutex = create_mutex ();

	sub	rsp, 40					; 00000028H
	call	?create_mutex@@YAPEAUmutex_t@@XZ	; create_mutex
	mov	QWORD PTR msg_mutex, rax
	add	rsp, 40					; 00000028H
	ret	0
??__Emsg_mutex@@YAXXZ ENDP				; `dynamic initializer for 'msg_mutex''
text$yc	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\dwm_ipc.cpp
_TEXT	SEGMENT
?get_dwm_message_q_address@@YAPEA_KXZ PROC		; get_dwm_message_q_address

; 28   : 	return 0;

	xor	eax, eax

; 29   : }

	ret	0
?get_dwm_message_q_address@@YAPEA_KXZ ENDP		; get_dwm_message_q_address
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\dwm_ipc.cpp
_TEXT	SEGMENT
tmsg$ = 32
msg$ = 64
?dwm_dispatch_message@@YAXPEAU_dwm_message_@@@Z PROC	; dwm_dispatch_message

; 46   : void dwm_dispatch_message (dwm_message_t *msg) {

$LN4:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 47   : 	x64_cli();

	call	x64_cli

; 48   : 	mutex_lock (msg_rcv_mutex);

	mov	rcx, QWORD PTR msg_rcv_mutex
	call	?mutex_lock@@YAXPEAUmutex_t@@@Z		; mutex_lock

; 49   : 	dwm_message_t *tmsg = (dwm_message_t*)get_current_thread()->mouse_box;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rax, QWORD PTR [rax+240]
	mov	QWORD PTR tmsg$[rsp], rax

; 50   : 	if (tmsg->type != 0) {

	mov	rax, QWORD PTR tmsg$[rsp]
	movzx	eax, WORD PTR [rax]
	test	eax, eax
	je	SHORT $LN1@dwm_dispat

; 51   : 		memcpy (msg,tmsg,sizeof(dwm_message_t));

	mov	r8d, 28
	mov	rdx, QWORD PTR tmsg$[rsp]
	mov	rcx, QWORD PTR msg$[rsp]
	call	memcpy
$LN1@dwm_dispat:

; 52   : 	}
; 53   : 
; 54   : 	memset (get_current_thread()->mouse_box, 0, 4096);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR [rax+240]
	call	?memset@@YAXPEAXEI@Z			; memset

; 55   : 	mutex_unlock (msg_rcv_mutex);

	mov	rcx, QWORD PTR msg_rcv_mutex
	call	?mutex_unlock@@YAXPEAUmutex_t@@@Z	; mutex_unlock

; 56   : }

	add	rsp, 56					; 00000038H
	ret	0
?dwm_dispatch_message@@YAXPEAU_dwm_message_@@@Z ENDP	; dwm_dispatch_message
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\dwm_ipc.cpp
_TEXT	SEGMENT
t$ = 32
tmsg$ = 40
msg$ = 64
?dwm_put_message@@YAXPEAU_dwm_message_@@@Z PROC		; dwm_put_message

; 30   : void dwm_put_message (dwm_message_t *msg) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 31   : 	//x64_cli ();
; 32   : 	mutex_lock (msg_mutex);

	mov	rcx, QWORD PTR msg_mutex
	call	?mutex_lock@@YAXPEAUmutex_t@@@Z		; mutex_lock

; 33   : 	thread_t *t  = thread_iterate_ready_list (2);   //!ready list

	mov	cx, 2
	call	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ; thread_iterate_ready_list
	mov	QWORD PTR t$[rsp], rax

; 34   : 	if (t == NULL) {

	cmp	QWORD PTR t$[rsp], 0
	jne	SHORT $LN2@dwm_put_me

; 35   : 		t = thread_iterate_block_list(2);

	mov	ecx, 2
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR t$[rsp], rax
$LN2@dwm_put_me:

; 36   : 	}
; 37   : 
; 38   : 	dwm_message_t *tmsg = (dwm_message_t*)t->mouse_box;

	mov	rax, QWORD PTR t$[rsp]
	mov	rax, QWORD PTR [rax+240]
	mov	QWORD PTR tmsg$[rsp], rax

; 39   : 	if (tmsg->type == 0)

	mov	rax, QWORD PTR tmsg$[rsp]
	movzx	eax, WORD PTR [rax]
	test	eax, eax
	jne	SHORT $LN1@dwm_put_me

; 40   : 		memcpy (t->mouse_box,msg,sizeof(dwm_message_t));

	mov	r8d, 28
	mov	rdx, QWORD PTR msg$[rsp]
	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR [rax+240]
	call	memcpy
$LN1@dwm_put_me:

; 41   : 	mutex_unlock (msg_mutex);

	mov	rcx, QWORD PTR msg_mutex
	call	?mutex_unlock@@YAXPEAUmutex_t@@@Z	; mutex_unlock

; 42   : 
; 43   : }

	add	rsp, 56					; 00000038H
	ret	0
?dwm_put_message@@YAXPEAU_dwm_message_@@@Z ENDP		; dwm_put_message
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\dwm_ipc.cpp
_TEXT	SEGMENT
p$ = 32
?dwm_ipc_init@@YAXXZ PROC				; dwm_ipc_init

; 21   : void dwm_ipc_init () {

$LN3:
	sub	rsp, 56					; 00000038H

; 22   : 	void* p = pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR p$[rsp], rax

; 23   : 	memset(p, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR p$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 24   : 	map_page((uint64_t)p,0xFFFFFD0000000000, 0);

	xor	r8d, r8d
	mov	rdx, -3298534883328			; fffffd0000000000H
	mov	rcx, QWORD PTR p$[rsp]
	call	?map_page@@YA_N_K0E@Z			; map_page

; 25   : }

	add	rsp, 56					; 00000038H
	ret	0
?dwm_ipc_init@@YAXXZ ENDP				; dwm_ipc_init
_TEXT	ENDS
END
