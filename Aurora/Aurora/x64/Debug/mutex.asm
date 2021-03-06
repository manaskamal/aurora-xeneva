; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?create_mutex@@YAPEAUmutex_t@@XZ		; create_mutex
PUBLIC	?mutex_lock@@YAXPEAUmutex_t@@@Z			; mutex_lock
PUBLIC	?mutex_unlock@@YAXPEAUmutex_t@@@Z		; mutex_unlock
EXTRN	malloc:PROC
EXTRN	?block_thread@@YAXPEAU_thread_@@@Z:PROC		; block_thread
EXTRN	?unblock_thread@@YAXPEAU_thread_@@@Z:PROC	; unblock_thread
EXTRN	get_current_thread:PROC
EXTRN	?set_multi_task_enable@@YAX_N@Z:PROC		; set_multi_task_enable
EXTRN	force_sched:PROC
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
pdata	SEGMENT
$pdata$?create_mutex@@YAPEAUmutex_t@@XZ DD imagerel $LN3
	DD	imagerel $LN3+64
	DD	imagerel $unwind$?create_mutex@@YAPEAUmutex_t@@XZ
$pdata$?mutex_lock@@YAXPEAUmutex_t@@@Z DD imagerel $LN6
	DD	imagerel $LN6+195
	DD	imagerel $unwind$?mutex_lock@@YAXPEAUmutex_t@@@Z
$pdata$?mutex_unlock@@YAXPEAUmutex_t@@@Z DD imagerel $LN8
	DD	imagerel $LN8+189
	DD	imagerel $unwind$?mutex_unlock@@YAXPEAUmutex_t@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?create_mutex@@YAPEAUmutex_t@@XZ DD 010401H
	DD	06204H
$unwind$?mutex_lock@@YAXPEAUmutex_t@@@Z DD 010901H
	DD	04209H
$unwind$?mutex_unlock@@YAXPEAUmutex_t@@@Z DD 010901H
	DD	06209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\atomic\mutex.cpp
_TEXT	SEGMENT
id$1 = 32
thr$2 = 40
obj$ = 64
?mutex_unlock@@YAXPEAUmutex_t@@@Z PROC			; mutex_unlock

; 57   : void mutex_unlock (mutex_t *obj) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 58   : 
; 59   : 	set_multi_task_enable (false);

	xor	ecx, ecx
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 60   : 
; 61   : 	if (obj->blocks <= 0) {

	mov	rax, QWORD PTR obj$[rsp]
	cmp	DWORD PTR [rax+12], 0
	ja	SHORT $LN5@mutex_unlo

; 62   : 		set_multi_task_enable (true);

	mov	cl, 1
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 63   : 		return;

	jmp	$LN6@mutex_unlo
$LN5@mutex_unlo:

; 64   : 	}
; 65   : 
; 66   : 	if (obj->block_thread_num > 0) {

	mov	rax, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rax+8]
	test	eax, eax
	jle	SHORT $LN4@mutex_unlo
$LN3@mutex_unlo:

; 67   : 		while (obj->block_thread_num != 0) {

	mov	rax, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rax+8]
	test	eax, eax
	je	SHORT $LN2@mutex_unlo

; 68   : 			uint16_t id = obj->block_thread_id[obj->block_thread_num];

	mov	rax, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rax+8]
	mov	rcx, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rcx+rax*4+16]
	mov	WORD PTR id$1[rsp], ax

; 69   : 			thread_t * thr = thread_iterate_block_list (id);

	movzx	eax, WORD PTR id$1[rsp]
	mov	ecx, eax
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR thr$2[rsp], rax

; 70   : 			if (thr != NULL)

	cmp	QWORD PTR thr$2[rsp], 0
	je	SHORT $LN1@mutex_unlo

; 71   : 				unblock_thread(thr);

	mov	rcx, QWORD PTR thr$2[rsp]
	call	?unblock_thread@@YAXPEAU_thread_@@@Z	; unblock_thread
$LN1@mutex_unlo:

; 72   : 			obj->block_thread_num--;

	mov	rax, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rax+8]
	dec	ax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	WORD PTR [rcx+8], ax

; 73   : 		}

	jmp	SHORT $LN3@mutex_unlo
$LN2@mutex_unlo:
$LN4@mutex_unlo:

; 74   : 	}
; 75   : 
; 76   : 	//! decreament the block count
; 77   : 	obj->blocks--;

	mov	rax, QWORD PTR obj$[rsp]
	mov	eax, DWORD PTR [rax+12]
	dec	eax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rcx+12], eax

; 78   : 	obj->owner_thread = 0;

	mov	rax, QWORD PTR obj$[rsp]
	mov	QWORD PTR [rax], 0

; 79   : 	set_multi_task_enable (true);

	mov	cl, 1
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable
$LN6@mutex_unlo:

; 80   : }

	add	rsp, 56					; 00000038H
	ret	0
?mutex_unlock@@YAXPEAUmutex_t@@@Z ENDP			; mutex_unlock
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\atomic\mutex.cpp
_TEXT	SEGMENT
obj$ = 48
?mutex_lock@@YAXPEAUmutex_t@@@Z PROC			; mutex_lock

; 28   : void mutex_lock (mutex_t * obj) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 29   : 	//!disable multi tasking
; 30   : 	set_multi_task_enable (false);

	xor	ecx, ecx
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 31   : 
; 32   : 	//! check
; 33   : 	if (obj->blocks != 0 && obj->owner_thread == get_current_thread()) {

	mov	rax, QWORD PTR obj$[rsp]
	cmp	DWORD PTR [rax+12], 0
	je	SHORT $LN3@mutex_lock
	call	get_current_thread
	mov	rcx, QWORD PTR obj$[rsp]
	cmp	QWORD PTR [rcx], rax
	jne	SHORT $LN3@mutex_lock

; 34   : 		obj->blocks++;

	mov	rax, QWORD PTR obj$[rsp]
	mov	eax, DWORD PTR [rax+12]
	inc	eax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rcx+12], eax

; 35   : 		set_multi_task_enable (true);

	mov	cl, 1
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 36   : 		return;

	jmp	SHORT $LN4@mutex_lock
$LN3@mutex_lock:
$LN2@mutex_lock:

; 37   : 	}
; 38   : 
; 39   : 
; 40   : 	while (obj->blocks != 0) {

	mov	rax, QWORD PTR obj$[rsp]
	cmp	DWORD PTR [rax+12], 0
	je	SHORT $LN1@mutex_lock

; 41   : 		block_thread(get_current_thread());

	call	get_current_thread
	mov	rcx, rax
	call	?block_thread@@YAXPEAU_thread_@@@Z	; block_thread

; 42   : 		obj->block_thread_num++;

	mov	rax, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rax+8]
	inc	ax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	WORD PTR [rcx+8], ax

; 43   : 		obj->block_thread_id[obj->block_thread_num] = get_current_thread()->id;

	call	get_current_thread
	movzx	eax, WORD PTR [rax+242]
	mov	rcx, QWORD PTR obj$[rsp]
	movzx	ecx, WORD PTR [rcx+8]
	mov	rdx, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rdx+rcx*4+16], eax

; 44   : 		set_multi_task_enable (true);

	mov	cl, 1
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable

; 45   : 		force_sched();

	call	force_sched

; 46   : 	}

	jmp	SHORT $LN2@mutex_lock
$LN1@mutex_lock:

; 47   : 
; 48   : 	obj->blocks = 1;

	mov	rax, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rax+12], 1

; 49   : 	obj->owner_thread = get_current_thread();

	call	get_current_thread
	mov	rcx, QWORD PTR obj$[rsp]
	mov	QWORD PTR [rcx], rax

; 50   : 	set_multi_task_enable (true);

	mov	cl, 1
	call	?set_multi_task_enable@@YAX_N@Z		; set_multi_task_enable
$LN4@mutex_lock:

; 51   : }

	add	rsp, 40					; 00000028H
	ret	0
?mutex_lock@@YAXPEAUmutex_t@@@Z ENDP			; mutex_lock
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\atomic\mutex.cpp
_TEXT	SEGMENT
obj$ = 32
?create_mutex@@YAPEAUmutex_t@@XZ PROC			; create_mutex

; 18   : mutex_t * create_mutex () {

$LN3:
	sub	rsp, 56					; 00000038H

; 19   : 	mutex_t * obj = (mutex_t*)malloc(sizeof(mutex_t));

	mov	ecx, 216				; 000000d8H
	call	malloc
	mov	QWORD PTR obj$[rsp], rax

; 20   : 	obj->blocks = 0;

	mov	rax, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rax+12], 0

; 21   : 	obj->owner_thread= 0;

	mov	rax, QWORD PTR obj$[rsp]
	mov	QWORD PTR [rax], 0

; 22   : 	obj->block_thread_num = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	WORD PTR [rcx+8], ax

; 23   : 	return obj;

	mov	rax, QWORD PTR obj$[rsp]

; 24   : }

	add	rsp, 56					; 00000038H
	ret	0
?create_mutex@@YAPEAUmutex_t@@XZ ENDP			; create_mutex
_TEXT	ENDS
END
