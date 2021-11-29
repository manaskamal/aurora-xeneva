; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?waked@@3_NA					; waked
_BSS	SEGMENT
top	DQ	01H DUP (?)
process_count DD 01H DUP (?)
?waked@@3_NA DB	01H DUP (?)				; waked
_BSS	ENDS
PUBLIC	?procmngr_add_process@@YAXPEAU_procmngr_queue_@@@Z ; procmngr_add_process
PUBLIC	?procmngr_get_process@@YAPEAU_procmngr_queue_@@XZ ; procmngr_get_process
PUBLIC	?procmngr_start@@YAXXZ				; procmngr_start
PUBLIC	?procmngr_wakeup@@YAXXZ				; procmngr_wakeup
PUBLIC	?procmngr_create_process@@YAXPEAU_procmngr_queue_@@@Z ; procmngr_create_process
EXTRN	?pmmngr_free@@YAXPEAX@Z:PROC			; pmmngr_free
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	?block_thread@@YAXPEAU_thread_@@@Z:PROC		; block_thread
EXTRN	?unblock_thread@@YAXPEAU_thread_@@@Z:PROC	; unblock_thread
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
EXTRN	?force_sched@@YAXXZ:PROC			; force_sched
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
EXTRN	?create_process@@YAXPEBDPEAD@Z:PROC		; create_process
pdata	SEGMENT
$pdata$?procmngr_add_process@@YAXPEAU_procmngr_queue_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+63
	DD	imagerel $unwind$?procmngr_add_process@@YAXPEAU_procmngr_queue_@@@Z
$pdata$?procmngr_get_process@@YAPEAU_procmngr_queue_@@XZ DD imagerel $LN4
	DD	imagerel $LN4+104
	DD	imagerel $unwind$?procmngr_get_process@@YAPEAU_procmngr_queue_@@XZ
$pdata$?procmngr_start@@YAXXZ DD imagerel $LN9
	DD	imagerel $LN9+106
	DD	imagerel $unwind$?procmngr_start@@YAXXZ
$pdata$?procmngr_wakeup@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+60
	DD	imagerel $unwind$?procmngr_wakeup@@YAXXZ
$pdata$?procmngr_create_process@@YAXPEAU_procmngr_queue_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+46
	DD	imagerel $unwind$?procmngr_create_process@@YAXPEAU_procmngr_queue_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?procmngr_add_process@@YAXPEAU_procmngr_queue_@@@Z DD 010901H
	DD	02209H
$unwind$?procmngr_get_process@@YAPEAU_procmngr_queue_@@XZ DD 010401H
	DD	06204H
$unwind$?procmngr_start@@YAXXZ DD 010401H
	DD	06204H
$unwind$?procmngr_wakeup@@YAXXZ DD 010401H
	DD	06204H
$unwind$?procmngr_create_process@@YAXPEAU_procmngr_queue_@@@Z DD 010901H
	DD	04209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\procmngr.cpp
_TEXT	SEGMENT
queue$ = 48
?procmngr_create_process@@YAXPEAU_procmngr_queue_@@@Z PROC ; procmngr_create_process

; 44   : void procmngr_create_process (procmngr_queue *queue) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 45   : 	x64_cli();

	call	x64_cli

; 46   : 	create_process (queue->path,queue->name);

	mov	rax, QWORD PTR queue$[rsp]
	mov	rcx, QWORD PTR queue$[rsp]
	add	rcx, 8
	mov	rdx, rax
	call	?create_process@@YAXPEBDPEAD@Z		; create_process

; 47   : 	x64_sti();

	call	x64_sti

; 48   : }

	add	rsp, 40					; 00000028H
	ret	0
?procmngr_create_process@@YAXPEAU_procmngr_queue_@@@Z ENDP ; procmngr_create_process
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\procmngr.cpp
_TEXT	SEGMENT
proc_thr$ = 32
?procmngr_wakeup@@YAXXZ PROC				; procmngr_wakeup

; 51   : void procmngr_wakeup () {

$LN5:
	sub	rsp, 56					; 00000038H

; 52   : 	thread_t *proc_thr = (thread_t*)thread_iterate_block_list (3);

	mov	ecx, 3
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR proc_thr$[rsp], rax

; 53   : 	if (proc_thr != NULL) {

	cmp	QWORD PTR proc_thr$[rsp], 0
	je	SHORT $LN2@procmngr_w

; 54   : 		if (!waked) {

	movzx	eax, BYTE PTR ?waked@@3_NA		; waked
	test	eax, eax
	jne	SHORT $LN1@procmngr_w

; 55   : 			waked = true;

	mov	BYTE PTR ?waked@@3_NA, 1		; waked

; 56   : 			unblock_thread (proc_thr);

	mov	rcx, QWORD PTR proc_thr$[rsp]
	call	?unblock_thread@@YAXPEAU_thread_@@@Z	; unblock_thread
$LN1@procmngr_w:
$LN2@procmngr_w:

; 57   : 		}
; 58   : 	}
; 59   : }

	add	rsp, 56					; 00000038H
	ret	0
?procmngr_wakeup@@YAXXZ ENDP				; procmngr_wakeup
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\procmngr.cpp
_TEXT	SEGMENT
i$1 = 32
queue$ = 40
?procmngr_start@@YAXXZ PROC				; procmngr_start

; 62   : void procmngr_start () {

$LN9:
	sub	rsp, 56					; 00000038H
$LN6@procmngr_s:

; 63   : 	procmngr_queue *queue;
; 64   : 	while (1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN5@procmngr_s

; 65   : 		if (process_count > 0) {

	cmp	DWORD PTR process_count, 0
	jle	SHORT $LN4@procmngr_s

; 66   : 			for (int i = 0; i < process_count; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@procmngr_s
$LN2@procmngr_s:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@procmngr_s:
	mov	eax, DWORD PTR process_count
	cmp	DWORD PTR i$1[rsp], eax
	jge	SHORT $LN1@procmngr_s

; 67   : 				queue = procmngr_get_process ();

	call	?procmngr_get_process@@YAPEAU_procmngr_queue_@@XZ ; procmngr_get_process
	mov	QWORD PTR queue$[rsp], rax

; 68   : 				procmngr_create_process (queue);

	mov	rcx, QWORD PTR queue$[rsp]
	call	?procmngr_create_process@@YAXPEAU_procmngr_queue_@@@Z ; procmngr_create_process

; 69   : 			}

	jmp	SHORT $LN2@procmngr_s
$LN1@procmngr_s:
$LN4@procmngr_s:

; 70   : 		}
; 71   : 
; 72   : 		waked = false;

	mov	BYTE PTR ?waked@@3_NA, 0		; waked

; 73   : 		block_thread(get_current_thread());

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rcx, rax
	call	?block_thread@@YAXPEAU_thread_@@@Z	; block_thread

; 74   : 		force_sched();

	call	?force_sched@@YAXXZ			; force_sched

; 75   : 		//sleep_thread(get_current_thread(),1000);
; 76   : 	}

	jmp	SHORT $LN6@procmngr_s
$LN5@procmngr_s:

; 77   : }

	add	rsp, 56					; 00000038H
	ret	0
?procmngr_start@@YAXXZ ENDP				; procmngr_start
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\procmngr.cpp
_TEXT	SEGMENT
temp$ = 32
?procmngr_get_process@@YAPEAU_procmngr_queue_@@XZ PROC	; procmngr_get_process

; 31   : procmngr_queue* procmngr_get_process () {

$LN4:
	sub	rsp, 56					; 00000038H

; 32   : 	procmngr_queue *temp = NULL;

	mov	QWORD PTR temp$[rsp], 0

; 33   : 	if (top != NULL) {

	cmp	QWORD PTR top, 0
	je	SHORT $LN1@procmngr_g

; 34   : 		temp = top;

	mov	rax, QWORD PTR top
	mov	QWORD PTR temp$[rsp], rax

; 35   : 		top = top->link;

	mov	rax, QWORD PTR top
	mov	rax, QWORD PTR [rax+64]
	mov	QWORD PTR top, rax

; 36   : 		temp->link = NULL;

	mov	rax, QWORD PTR temp$[rsp]
	mov	QWORD PTR [rax+64], 0

; 37   : 		pmmngr_free(temp);

	mov	rcx, QWORD PTR temp$[rsp]
	call	?pmmngr_free@@YAXPEAX@Z			; pmmngr_free

; 38   : 		process_count--;

	mov	eax, DWORD PTR process_count
	dec	eax
	mov	DWORD PTR process_count, eax

; 39   : 		return temp;

	mov	rax, QWORD PTR temp$[rsp]
	jmp	SHORT $LN2@procmngr_g
$LN1@procmngr_g:

; 40   : 	}
; 41   : 	return NULL;

	xor	eax, eax
$LN2@procmngr_g:

; 42   : }

	add	rsp, 56					; 00000038H
	ret	0
?procmngr_get_process@@YAPEAU_procmngr_queue_@@XZ ENDP	; procmngr_get_process
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\procmngr.cpp
_TEXT	SEGMENT
temp$ = 0
queue$ = 32
?procmngr_add_process@@YAXPEAU_procmngr_queue_@@@Z PROC	; procmngr_add_process

; 23   : void procmngr_add_process (procmngr_queue *queue) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 24   : 	procmngr_queue * temp = queue;

	mov	rax, QWORD PTR queue$[rsp]
	mov	QWORD PTR temp$[rsp], rax

; 25   : 
; 26   : 	temp->link = top;

	mov	rax, QWORD PTR temp$[rsp]
	mov	rcx, QWORD PTR top
	mov	QWORD PTR [rax+64], rcx

; 27   : 	top = temp;

	mov	rax, QWORD PTR temp$[rsp]
	mov	QWORD PTR top, rax

; 28   : 	process_count++;

	mov	eax, DWORD PTR process_count
	inc	eax
	mov	DWORD PTR process_count, eax

; 29   : }

	add	rsp, 24
	ret	0
?procmngr_add_process@@YAXPEAU_procmngr_queue_@@@Z ENDP	; procmngr_add_process
_TEXT	ENDS
END
