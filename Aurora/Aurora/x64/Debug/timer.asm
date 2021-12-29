; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?timer_head@@3PEAU_timer_@@EA			; timer_head
PUBLIC	?timer_last@@3PEAU_timer_@@EA			; timer_last
PUBLIC	?utimer_id@@3IA					; utimer_id
_BSS	SEGMENT
?timer_head@@3PEAU_timer_@@EA DQ 01H DUP (?)		; timer_head
?timer_last@@3PEAU_timer_@@EA DQ 01H DUP (?)		; timer_last
?utimer_id@@3IA DD 01H DUP (?)				; utimer_id
_BSS	ENDS
PUBLIC	?create_timer@@YAHIG@Z				; create_timer
PUBLIC	?destroy_timer@@YAXH@Z				; destroy_timer
PUBLIC	?pause_timer@@YAXH@Z				; pause_timer
PUBLIC	?start_timer@@YAXH@Z				; start_timer
PUBLIC	?timer_fire@@YAXXZ				; timer_fire
PUBLIC	?find_timer_id@@YAHG@Z				; find_timer_id
PUBLIC	?timer_insert@@YAXPEAU_timer_@@@Z		; timer_insert
PUBLIC	?timer_delete@@YAXPEAU_timer_@@@Z		; timer_delete
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?pmmngr_free@@YAXPEAX@Z:PROC			; pmmngr_free
EXTRN	x64_cli:PROC
EXTRN	?post_box_put_msg@@YAXPEAU_post_box_message_@@G@Z:PROC ; post_box_put_msg
pdata	SEGMENT
$pdata$?create_timer@@YAHIG@Z DD imagerel $LN3
	DD	imagerel $LN3+118
	DD	imagerel $unwind$?create_timer@@YAHIG@Z
$pdata$?destroy_timer@@YAXH@Z DD imagerel $LN7
	DD	imagerel $LN7+87
	DD	imagerel $unwind$?destroy_timer@@YAXH@Z
$pdata$?pause_timer@@YAXH@Z DD imagerel $LN7
	DD	imagerel $LN7+70
	DD	imagerel $unwind$?pause_timer@@YAXH@Z
$pdata$?start_timer@@YAXH@Z DD imagerel $LN7
	DD	imagerel $LN7+70
	DD	imagerel $unwind$?start_timer@@YAXH@Z
$pdata$?timer_fire@@YAXXZ DD imagerel $LN9
	DD	imagerel $LN9+166
	DD	imagerel $unwind$?timer_fire@@YAXXZ
$pdata$?find_timer_id@@YAHG@Z DD imagerel $LN7
	DD	imagerel $LN7+81
	DD	imagerel $unwind$?find_timer_id@@YAHG@Z
$pdata$?timer_delete@@YAXPEAU_timer_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+146
	DD	imagerel $unwind$?timer_delete@@YAXPEAU_timer_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?create_timer@@YAHIG@Z DD 010d01H
	DD	0620dH
$unwind$?destroy_timer@@YAXH@Z DD 010801H
	DD	06208H
$unwind$?pause_timer@@YAXH@Z DD 010801H
	DD	02208H
$unwind$?start_timer@@YAXH@Z DD 010801H
	DD	02208H
$unwind$?timer_fire@@YAXXZ DD 010401H
	DD	0a204H
$unwind$?find_timer_id@@YAHG@Z DD 010901H
	DD	02209H
$unwind$?timer_delete@@YAXPEAU_timer_@@@Z DD 010901H
	DD	04209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\timer.cpp
_TEXT	SEGMENT
new_timer$ = 48
?timer_delete@@YAXPEAU_timer_@@@Z PROC			; timer_delete

; 38   : void timer_delete (timer_t* new_timer) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 39   : 
; 40   : 	if (timer_head == NULL)

	cmp	QWORD PTR ?timer_head@@3PEAU_timer_@@EA, 0 ; timer_head
	jne	SHORT $LN5@timer_dele

; 41   : 		return;

	jmp	SHORT $LN6@timer_dele
$LN5@timer_dele:

; 42   : 
; 43   : 	if (new_timer == timer_head) {

	mov	rax, QWORD PTR ?timer_head@@3PEAU_timer_@@EA ; timer_head
	cmp	QWORD PTR new_timer$[rsp], rax
	jne	SHORT $LN4@timer_dele

; 44   : 		timer_head = timer_head->next;

	mov	rax, QWORD PTR ?timer_head@@3PEAU_timer_@@EA ; timer_head
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR ?timer_head@@3PEAU_timer_@@EA, rax ; timer_head

; 45   : 	} else {

	jmp	SHORT $LN3@timer_dele
$LN4@timer_dele:

; 46   : 		new_timer->prev->next = new_timer->next;

	mov	rax, QWORD PTR new_timer$[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	rcx, QWORD PTR new_timer$[rsp]
	mov	rcx, QWORD PTR [rcx+24]
	mov	QWORD PTR [rax+24], rcx
$LN3@timer_dele:

; 47   : 	}
; 48   : 
; 49   : 	if (new_timer == timer_last) {

	mov	rax, QWORD PTR ?timer_last@@3PEAU_timer_@@EA ; timer_last
	cmp	QWORD PTR new_timer$[rsp], rax
	jne	SHORT $LN2@timer_dele

; 50   : 		timer_last = new_timer->prev;

	mov	rax, QWORD PTR new_timer$[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	QWORD PTR ?timer_last@@3PEAU_timer_@@EA, rax ; timer_last

; 51   : 	} else {

	jmp	SHORT $LN1@timer_dele
$LN2@timer_dele:

; 52   : 		new_timer->next->prev = new_timer->prev;

	mov	rax, QWORD PTR new_timer$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR new_timer$[rsp]
	mov	rcx, QWORD PTR [rcx+32]
	mov	QWORD PTR [rax+32], rcx
$LN1@timer_dele:

; 53   : 	}
; 54   : 	pmmngr_free(new_timer);

	mov	rcx, QWORD PTR new_timer$[rsp]
	call	?pmmngr_free@@YAXPEAX@Z			; pmmngr_free
$LN6@timer_dele:

; 55   : }

	add	rsp, 40					; 00000028H
	ret	0
?timer_delete@@YAXPEAU_timer_@@@Z ENDP			; timer_delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\timer.cpp
_TEXT	SEGMENT
new_timer$ = 8
?timer_insert@@YAXPEAU_timer_@@@Z PROC			; timer_insert

; 23   : void timer_insert (timer_t* new_timer ) {

	mov	QWORD PTR [rsp+8], rcx

; 24   : 	new_timer->next = NULL;

	mov	rax, QWORD PTR new_timer$[rsp]
	mov	QWORD PTR [rax+24], 0

; 25   : 	new_timer->prev = NULL;

	mov	rax, QWORD PTR new_timer$[rsp]
	mov	QWORD PTR [rax+32], 0

; 26   : 
; 27   : 	if (timer_head == NULL) {

	cmp	QWORD PTR ?timer_head@@3PEAU_timer_@@EA, 0 ; timer_head
	jne	SHORT $LN2@timer_inse

; 28   : 		timer_last = new_timer;

	mov	rax, QWORD PTR new_timer$[rsp]
	mov	QWORD PTR ?timer_last@@3PEAU_timer_@@EA, rax ; timer_last

; 29   : 		timer_head = new_timer;

	mov	rax, QWORD PTR new_timer$[rsp]
	mov	QWORD PTR ?timer_head@@3PEAU_timer_@@EA, rax ; timer_head

; 30   : 	} else {

	jmp	SHORT $LN1@timer_inse
$LN2@timer_inse:

; 31   : 		timer_last->next = new_timer;

	mov	rax, QWORD PTR ?timer_last@@3PEAU_timer_@@EA ; timer_last
	mov	rcx, QWORD PTR new_timer$[rsp]
	mov	QWORD PTR [rax+24], rcx

; 32   : 		new_timer->prev = timer_last;

	mov	rax, QWORD PTR new_timer$[rsp]
	mov	rcx, QWORD PTR ?timer_last@@3PEAU_timer_@@EA ; timer_last
	mov	QWORD PTR [rax+32], rcx
$LN1@timer_inse:

; 33   : 	}
; 34   : 	timer_last = new_timer;

	mov	rax, QWORD PTR new_timer$[rsp]
	mov	QWORD PTR ?timer_last@@3PEAU_timer_@@EA, rax ; timer_last

; 35   : }

	ret	0
?timer_insert@@YAXPEAU_timer_@@@Z ENDP			; timer_insert
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\timer.cpp
_TEXT	SEGMENT
t$1 = 0
id$ = 32
?find_timer_id@@YAHG@Z PROC				; find_timer_id

; 127  : int find_timer_id (uint16_t id) {

$LN7:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 24

; 128  : 	for (timer_t *t = timer_head; t != NULL; t = t->next) {

	mov	rax, QWORD PTR ?timer_head@@3PEAU_timer_@@EA ; timer_head
	mov	QWORD PTR t$1[rsp], rax
	jmp	SHORT $LN4@find_timer
$LN3@find_timer:
	mov	rax, QWORD PTR t$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR t$1[rsp], rax
$LN4@find_timer:
	cmp	QWORD PTR t$1[rsp], 0
	je	SHORT $LN2@find_timer

; 129  : 		if (t->task_id == id) {

	mov	rax, QWORD PTR t$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	movzx	ecx, WORD PTR id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN1@find_timer

; 130  : 			return t->utimer_id;

	mov	rax, QWORD PTR t$1[rsp]
	mov	eax, DWORD PTR [rax+12]
	jmp	SHORT $LN5@find_timer

; 131  : 			break;

	jmp	SHORT $LN2@find_timer
$LN1@find_timer:

; 132  : 		}
; 133  : 	}

	jmp	SHORT $LN3@find_timer
$LN2@find_timer:

; 134  : 
; 135  : 	return -1;

	mov	eax, -1
$LN5@find_timer:

; 136  : }

	add	rsp, 24
	ret	0
?find_timer_id@@YAHG@Z ENDP				; find_timer_id
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\timer.cpp
_TEXT	SEGMENT
t$1 = 32
msg$2 = 40
?timer_fire@@YAXXZ PROC					; timer_fire

; 144  : void timer_fire () {

$LN9:
	sub	rsp, 88					; 00000058H

; 145  : 	x64_cli();

	call	x64_cli

; 146  : 	if (timer_head != NULL) {

	cmp	QWORD PTR ?timer_head@@3PEAU_timer_@@EA, 0 ; timer_head
	je	$LN6@timer_fire

; 147  : 		for (timer_t *t = timer_head; t != NULL; t = t->next) {

	mov	rax, QWORD PTR ?timer_head@@3PEAU_timer_@@EA ; timer_head
	mov	QWORD PTR t$1[rsp], rax
	jmp	SHORT $LN5@timer_fire
$LN4@timer_fire:
	mov	rax, QWORD PTR t$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR t$1[rsp], rax
$LN5@timer_fire:
	cmp	QWORD PTR t$1[rsp], 0
	je	SHORT $LN3@timer_fire

; 148  : 			if (t->start) {

	mov	rax, QWORD PTR t$1[rsp]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	je	SHORT $LN2@timer_fire

; 149  : 				if (t->timer_count == t->interval ) {

	mov	rax, QWORD PTR t$1[rsp]
	mov	rcx, QWORD PTR t$1[rsp]
	mov	ecx, DWORD PTR [rcx+4]
	cmp	DWORD PTR [rax], ecx
	jne	SHORT $LN1@timer_fire

; 150  : 					postmsg_t msg;
; 151  : 			        msg.type = SYSTEM_MESSAGE_TIMER_EVENT;

	mov	eax, 1
	mov	WORD PTR msg$2[rsp], ax

; 152  : 			        msg.to_id = t->task_id;

	mov	rax, QWORD PTR t$1[rsp]
	movzx	eax, WORD PTR [rax+8]
	mov	WORD PTR msg$2[rsp+28], ax

; 153  : 			        post_box_put_msg (&msg,t->task_id);

	mov	rax, QWORD PTR t$1[rsp]
	movzx	edx, WORD PTR [rax+8]
	lea	rcx, QWORD PTR msg$2[rsp]
	call	?post_box_put_msg@@YAXPEAU_post_box_message_@@G@Z ; post_box_put_msg

; 154  : 			        t->timer_count = 0;

	mov	rax, QWORD PTR t$1[rsp]
	mov	DWORD PTR [rax], 0
$LN1@timer_fire:

; 155  : 		         }
; 156  : 			     t->timer_count++;

	mov	rax, QWORD PTR t$1[rsp]
	mov	eax, DWORD PTR [rax]
	inc	eax
	mov	rcx, QWORD PTR t$1[rsp]
	mov	DWORD PTR [rcx], eax
$LN2@timer_fire:

; 157  : 			}
; 158  : 		}

	jmp	SHORT $LN4@timer_fire
$LN3@timer_fire:
$LN6@timer_fire:

; 159  : 	}
; 160  : }

	add	rsp, 88					; 00000058H
	ret	0
?timer_fire@@YAXXZ ENDP					; timer_fire
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\timer.cpp
_TEXT	SEGMENT
t$1 = 0
utimer_id$ = 32
?start_timer@@YAXH@Z PROC				; start_timer

; 97   : void start_timer (int utimer_id ) {

$LN7:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 24

; 98   : 	for (timer_t *t = timer_head; t != NULL; t = t->next) {

	mov	rax, QWORD PTR ?timer_head@@3PEAU_timer_@@EA ; timer_head
	mov	QWORD PTR t$1[rsp], rax
	jmp	SHORT $LN4@start_time
$LN3@start_time:
	mov	rax, QWORD PTR t$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR t$1[rsp], rax
$LN4@start_time:
	cmp	QWORD PTR t$1[rsp], 0
	je	SHORT $LN2@start_time

; 99   : 		if (t->utimer_id == utimer_id) {

	mov	rax, QWORD PTR t$1[rsp]
	mov	ecx, DWORD PTR utimer_id$[rsp]
	cmp	DWORD PTR [rax+12], ecx
	jne	SHORT $LN1@start_time

; 100  : 			t->start = true;

	mov	rax, QWORD PTR t$1[rsp]
	mov	BYTE PTR [rax+16], 1

; 101  : 			break;

	jmp	SHORT $LN2@start_time
$LN1@start_time:

; 102  : 		}
; 103  : 	}

	jmp	SHORT $LN3@start_time
$LN2@start_time:

; 104  : }

	add	rsp, 24
	ret	0
?start_timer@@YAXH@Z ENDP				; start_timer
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\timer.cpp
_TEXT	SEGMENT
t$1 = 0
utimer_id$ = 32
?pause_timer@@YAXH@Z PROC				; pause_timer

; 82   : void pause_timer (int utimer_id) {

$LN7:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 24

; 83   : 	for (timer_t *t = timer_head; t != NULL; t = t->next) {

	mov	rax, QWORD PTR ?timer_head@@3PEAU_timer_@@EA ; timer_head
	mov	QWORD PTR t$1[rsp], rax
	jmp	SHORT $LN4@pause_time
$LN3@pause_time:
	mov	rax, QWORD PTR t$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR t$1[rsp], rax
$LN4@pause_time:
	cmp	QWORD PTR t$1[rsp], 0
	je	SHORT $LN2@pause_time

; 84   : 		if (t->utimer_id == utimer_id) {

	mov	rax, QWORD PTR t$1[rsp]
	mov	ecx, DWORD PTR utimer_id$[rsp]
	cmp	DWORD PTR [rax+12], ecx
	jne	SHORT $LN1@pause_time

; 85   : 			t->start = false;

	mov	rax, QWORD PTR t$1[rsp]
	mov	BYTE PTR [rax+16], 0

; 86   : 			break;

	jmp	SHORT $LN2@pause_time
$LN1@pause_time:

; 87   : 		}
; 88   : 	}

	jmp	SHORT $LN3@pause_time
$LN2@pause_time:

; 89   : }

	add	rsp, 24
	ret	0
?pause_timer@@YAXH@Z ENDP				; pause_timer
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\timer.cpp
_TEXT	SEGMENT
t$1 = 32
utimer_id$ = 64
?destroy_timer@@YAXH@Z PROC				; destroy_timer

; 111  : void destroy_timer (int utimer_id) {

$LN7:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 112  : 	for (timer_t *t = timer_head; t != NULL; t = t->next) {

	mov	rax, QWORD PTR ?timer_head@@3PEAU_timer_@@EA ; timer_head
	mov	QWORD PTR t$1[rsp], rax
	jmp	SHORT $LN4@destroy_ti
$LN3@destroy_ti:
	mov	rax, QWORD PTR t$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR t$1[rsp], rax
$LN4@destroy_ti:
	cmp	QWORD PTR t$1[rsp], 0
	je	SHORT $LN2@destroy_ti

; 113  : 		if (t->utimer_id == utimer_id) {

	mov	rax, QWORD PTR t$1[rsp]
	mov	ecx, DWORD PTR utimer_id$[rsp]
	cmp	DWORD PTR [rax+12], ecx
	jne	SHORT $LN1@destroy_ti

; 114  : 			timer_delete (t);

	mov	rcx, QWORD PTR t$1[rsp]
	call	?timer_delete@@YAXPEAU_timer_@@@Z	; timer_delete

; 115  : 			utimer_id--;

	mov	eax, DWORD PTR utimer_id$[rsp]
	dec	eax
	mov	DWORD PTR utimer_id$[rsp], eax

; 116  : 			break;

	jmp	SHORT $LN2@destroy_ti
$LN1@destroy_ti:

; 117  : 		}
; 118  : 	}

	jmp	SHORT $LN3@destroy_ti
$LN2@destroy_ti:

; 119  : 	
; 120  : }

	add	rsp, 56					; 00000038H
	ret	0
?destroy_timer@@YAXH@Z ENDP				; destroy_timer
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\timer.cpp
_TEXT	SEGMENT
t$ = 32
interval$ = 64
id$ = 72
?create_timer@@YAHIG@Z PROC				; create_timer

; 65   : int create_timer (uint32_t interval, uint16_t id) {	

$LN3:
	mov	WORD PTR [rsp+16], dx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 66   : 	utimer_id++;

	mov	eax, DWORD PTR ?utimer_id@@3IA		; utimer_id
	inc	eax
	mov	DWORD PTR ?utimer_id@@3IA, eax		; utimer_id

; 67   : 	timer_t *t = (timer_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR t$[rsp], rax

; 68   : 	t->timer_count = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	DWORD PTR [rax], 0

; 69   : 	t->task_id = id;

	mov	rax, QWORD PTR t$[rsp]
	movzx	ecx, WORD PTR id$[rsp]
	mov	WORD PTR [rax+8], cx

; 70   : 	t->interval = interval;

	mov	rax, QWORD PTR t$[rsp]
	mov	ecx, DWORD PTR interval$[rsp]
	mov	DWORD PTR [rax+4], ecx

; 71   : 	t->utimer_id = utimer_id;

	mov	rax, QWORD PTR t$[rsp]
	mov	ecx, DWORD PTR ?utimer_id@@3IA		; utimer_id
	mov	DWORD PTR [rax+12], ecx

; 72   : 	t->start = false;

	mov	rax, QWORD PTR t$[rsp]
	mov	BYTE PTR [rax+16], 0

; 73   : 	timer_insert (t);

	mov	rcx, QWORD PTR t$[rsp]
	call	?timer_insert@@YAXPEAU_timer_@@@Z	; timer_insert

; 74   : 	return utimer_id;

	mov	eax, DWORD PTR ?utimer_id@@3IA		; utimer_id

; 75   : }

	add	rsp, 56					; 00000038H
	ret	0
?create_timer@@YAHIG@Z ENDP				; create_timer
_TEXT	ENDS
END
