; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?wait@@YAXXZ					; wait
PUBLIC	?sys_unblock_id@@YAXG@Z				; sys_unblock_id
EXTRN	x64_cli:PROC
EXTRN	?block_thread@@YAXPEAU_thread_@@@Z:PROC		; block_thread
EXTRN	?unblock_thread@@YAXPEAU_thread_@@@Z:PROC	; unblock_thread
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
EXTRN	?set_multi_task_enable@@YAX_N@Z:PROC		; set_multi_task_enable
EXTRN	force_sched:PROC
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
EXTRN	?create_mutex@@YAPEAUmutex_t@@XZ:PROC		; create_mutex
_BSS	SEGMENT
wait_lock DQ	01H DUP (?)
unblock_lock DQ	01H DUP (?)
_BSS	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$??__Ewait_lock@@YAXXZ DD imagerel ??__Ewait_lock@@YAXXZ
	DD	imagerel ??__Ewait_lock@@YAXXZ+21
	DD	imagerel $unwind$??__Ewait_lock@@YAXXZ
pdata	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$??__Eunblock_lock@@YAXXZ DD imagerel ??__Eunblock_lock@@YAXXZ
	DD	imagerel ??__Eunblock_lock@@YAXXZ+21
	DD	imagerel $unwind$??__Eunblock_lock@@YAXXZ
pdata	ENDS
pdata	SEGMENT
$pdata$?wait@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+53
	DD	imagerel $unwind$?wait@@YAXXZ
$pdata$?sys_unblock_id@@YAXG@Z DD imagerel $LN4
	DD	imagerel $LN4+68
	DD	imagerel $unwind$?sys_unblock_id@@YAXG@Z
pdata	ENDS
CRT$XCU	SEGMENT
wait_lock$initializer$ DQ FLAT:??__Ewait_lock@@YAXXZ
CRT$XCU	ENDS
xdata	SEGMENT
$unwind$?wait@@YAXXZ DD 010401H
	DD	06204H
$unwind$?sys_unblock_id@@YAXG@Z DD 010901H
	DD	06209H
xdata	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$??__Eunblock_lock@@YAXXZ DD 010401H
	DD	04204H
xdata	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$??__Ewait_lock@@YAXXZ DD 010401H
	DD	04204H
xdata	ENDS
CRT$XCU	SEGMENT
unblock_lock$initializer$ DQ FLAT:??__Eunblock_lock@@YAXXZ
CRT$XCU	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\syswait.cpp
_TEXT	SEGMENT
thr$ = 32
id$ = 64
?sys_unblock_id@@YAXG@Z PROC				; sys_unblock_id

; 32   : void sys_unblock_id (uint16_t id) {

$LN4:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 56					; 00000038H

; 33   : 	x64_cli ();

	call	x64_cli

; 34   : 	//mutex_lock (unblock_lock);
; 35   : 	set_multi_task_enable (false);

	xor	ecx, ecx
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 36   : 	thread_t* thr = (thread_t*)thread_iterate_block_list (id);

	movzx	eax, WORD PTR id$[rsp]
	mov	ecx, eax
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR thr$[rsp], rax

; 37   : 	if (thr != NULL){

	cmp	QWORD PTR thr$[rsp], 0
	je	SHORT $LN1@sys_unbloc

; 38   : 		//thr->state = THREAD_STATE_READY;
; 39   : 		unblock_thread(thr);

	mov	rcx, QWORD PTR thr$[rsp]
	call	?unblock_thread@@YAXPEAU_thread_@@@Z	; unblock_thread
$LN1@sys_unbloc:

; 40   : 	}
; 41   : 	set_multi_task_enable (true);

	mov	cl, 1
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 42   : }

	add	rsp, 56					; 00000038H
	ret	0
?sys_unblock_id@@YAXG@Z ENDP				; sys_unblock_id
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\syswait.cpp
_TEXT	SEGMENT
t$ = 32
?wait@@YAXXZ PROC					; wait

; 22   : void wait () {

$LN3:
	sub	rsp, 56					; 00000038H

; 23   : 	x64_cli();

	call	x64_cli

; 24   : 	set_multi_task_enable (false);

	xor	ecx, ecx
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 25   : 	thread_t *t = get_current_thread ();

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	QWORD PTR t$[rsp], rax

; 26   : 	block_thread (t);

	mov	rcx, QWORD PTR t$[rsp]
	call	?block_thread@@YAXPEAU_thread_@@@Z	; block_thread

; 27   : 	set_multi_task_enable (true);

	mov	cl, 1
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 28   : 	force_sched();

	call	force_sched

; 29   : 	//for(;;);
; 30   : }

	add	rsp, 56					; 00000038H
	ret	0
?wait@@YAXXZ ENDP					; wait
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\syswait.cpp
;	COMDAT ??__Eunblock_lock@@YAXXZ
text$yc	SEGMENT
??__Eunblock_lock@@YAXXZ PROC				; `dynamic initializer for 'unblock_lock'', COMDAT

; 21   : static mutex_t *unblock_lock = create_mutex();

	sub	rsp, 40					; 00000028H
	call	?create_mutex@@YAPEAUmutex_t@@XZ	; create_mutex
	mov	QWORD PTR unblock_lock, rax
	add	rsp, 40					; 00000028H
	ret	0
??__Eunblock_lock@@YAXXZ ENDP				; `dynamic initializer for 'unblock_lock''
text$yc	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\syswait.cpp
;	COMDAT ??__Ewait_lock@@YAXXZ
text$yc	SEGMENT
??__Ewait_lock@@YAXXZ PROC				; `dynamic initializer for 'wait_lock'', COMDAT

; 20   : static mutex_t * wait_lock = create_mutex();

	sub	rsp, 40					; 00000028H
	call	?create_mutex@@YAPEAUmutex_t@@XZ	; create_mutex
	mov	QWORD PTR wait_lock, rax
	add	rsp, 40					; 00000028H
	ret	0
??__Ewait_lock@@YAXXZ ENDP				; `dynamic initializer for 'wait_lock''
text$yc	ENDS
END
