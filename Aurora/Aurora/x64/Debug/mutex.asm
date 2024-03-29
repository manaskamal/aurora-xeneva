; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	AuMutexCreate
PUBLIC	AuMutexLock
PUBLIC	AuMutexUnlock
PUBLIC	AuMutexDestroy
EXTRN	malloc:PROC
EXTRN	free:PROC
EXTRN	block_thread:PROC
EXTRN	unblock_thread:PROC
EXTRN	get_current_thread:PROC
EXTRN	force_sched:PROC
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
pdata	SEGMENT
$pdata$AuMutexCreate DD imagerel $LN3
	DD	imagerel $LN3+64
	DD	imagerel $unwind$AuMutexCreate
$pdata$AuMutexLock DD imagerel $LN7
	DD	imagerel $LN7+182
	DD	imagerel $unwind$AuMutexLock
$pdata$AuMutexUnlock DD imagerel $LN10
	DD	imagerel $LN10+195
	DD	imagerel $unwind$AuMutexUnlock
$pdata$AuMutexDestroy DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$AuMutexDestroy
pdata	ENDS
xdata	SEGMENT
$unwind$AuMutexCreate DD 010401H
	DD	06204H
$unwind$AuMutexLock DD 010901H
	DD	04209H
$unwind$AuMutexUnlock DD 010901H
	DD	06209H
$unwind$AuMutexDestroy DD 010901H
	DD	04209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\atomic\mutex.cpp
_TEXT	SEGMENT
obj$ = 48
AuMutexDestroy PROC

; 106  : AU_EXTERN AU_EXPORT void AuMutexDestroy (mutex_t *obj) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 107  : 	free(obj);

	mov	rcx, QWORD PTR obj$[rsp]
	call	free

; 108  : }

	add	rsp, 40					; 00000028H
	ret	0
AuMutexDestroy ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\atomic\mutex.cpp
_TEXT	SEGMENT
id$1 = 32
i$2 = 36
thr$3 = 40
obj$ = 64
AuMutexUnlock PROC

; 75   : AU_EXTERN AU_EXPORT void AuMutexUnlock (mutex_t *obj) {

$LN10:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 76   : 
; 77   : 	if (get_current_thread() == NULL)

	call	get_current_thread
	test	rax, rax
	jne	SHORT $LN7@AuMutexUnl

; 78   : 		return;

	jmp	$LN8@AuMutexUnl
$LN7@AuMutexUnl:

; 79   : 
; 80   : 
; 81   : 	if (obj->blocks <= 0) 

	mov	rax, QWORD PTR obj$[rsp]
	cmp	DWORD PTR [rax+12], 0
	ja	SHORT $LN6@AuMutexUnl

; 82   : 		return;

	jmp	$LN8@AuMutexUnl
$LN6@AuMutexUnl:

; 83   : 
; 84   : 	
; 85   : 	if (obj->blocks == 1) {

	mov	rax, QWORD PTR obj$[rsp]
	cmp	DWORD PTR [rax+12], 1
	jne	SHORT $LN5@AuMutexUnl

; 86   : 		for (int i = 0; i < obj->block_thread_num; i++){

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN4@AuMutexUnl
$LN3@AuMutexUnl:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN4@AuMutexUnl:
	mov	rax, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rax+8]
	cmp	DWORD PTR i$2[rsp], eax
	jge	SHORT $LN2@AuMutexUnl

; 87   : 			uint16_t id = obj->block_thread_id[obj->block_thread_num];

	mov	rax, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rax+8]
	mov	rcx, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rcx+rax*4+16]
	mov	WORD PTR id$1[rsp], ax

; 88   : 			thread_t * thr = thread_iterate_block_list (id);

	movzx	eax, WORD PTR id$1[rsp]
	mov	ecx, eax
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR thr$3[rsp], rax

; 89   : 			if (thr != NULL)

	cmp	QWORD PTR thr$3[rsp], 0
	je	SHORT $LN1@AuMutexUnl

; 90   : 				unblock_thread(thr);

	mov	rcx, QWORD PTR thr$3[rsp]
	call	unblock_thread
$LN1@AuMutexUnl:

; 91   : 		}

	jmp	SHORT $LN3@AuMutexUnl
$LN2@AuMutexUnl:

; 92   : 		obj->block_thread_num = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	WORD PTR [rcx+8], ax

; 93   : 		obj->owner_thread = NULL;

	mov	rax, QWORD PTR obj$[rsp]
	mov	QWORD PTR [rax], 0

; 94   : 		return;

	jmp	SHORT $LN8@AuMutexUnl
$LN5@AuMutexUnl:

; 95   : 	}
; 96   : 
; 97   : 	//! decreament the block count
; 98   : 	obj->blocks--;

	mov	rax, QWORD PTR obj$[rsp]
	mov	eax, DWORD PTR [rax+12]
	dec	eax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rcx+12], eax
$LN8@AuMutexUnl:

; 99   : }

	add	rsp, 56					; 00000038H
	ret	0
AuMutexUnlock ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\atomic\mutex.cpp
_TEXT	SEGMENT
obj$ = 48
AuMutexLock PROC

; 49   : AU_EXTERN AU_EXPORT void AuMutexLock (mutex_t * obj) {

$LN7:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 50   : 	//! check
; 51   : 	if (get_current_thread() == NULL)

	call	get_current_thread
	test	rax, rax
	jne	SHORT $LN4@AuMutexLoc

; 52   : 		return;

	jmp	$LN5@AuMutexLoc
$LN4@AuMutexLoc:

; 53   : 
; 54   : 	if (obj->blocks != 0 && obj->owner_thread == get_current_thread()) {

	mov	rax, QWORD PTR obj$[rsp]
	cmp	DWORD PTR [rax+12], 0
	je	SHORT $LN3@AuMutexLoc
	call	get_current_thread
	mov	rcx, QWORD PTR obj$[rsp]
	cmp	QWORD PTR [rcx], rax
	jne	SHORT $LN3@AuMutexLoc

; 55   : 		obj->blocks++;

	mov	rax, QWORD PTR obj$[rsp]
	mov	eax, DWORD PTR [rax+12]
	inc	eax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rcx+12], eax

; 56   : 		return;

	jmp	SHORT $LN5@AuMutexLoc
$LN3@AuMutexLoc:
$LN2@AuMutexLoc:

; 57   : 	}
; 58   : 	
; 59   : 
; 60   : 	while (obj->blocks != 0) {

	mov	rax, QWORD PTR obj$[rsp]
	cmp	DWORD PTR [rax+12], 0
	je	SHORT $LN1@AuMutexLoc

; 61   : 		block_thread(get_current_thread());

	call	get_current_thread
	mov	rcx, rax
	call	block_thread

; 62   : 		obj->block_thread_id[obj->block_thread_num] = get_current_thread()->id;

	call	get_current_thread
	movzx	eax, WORD PTR [rax+238]
	mov	rcx, QWORD PTR obj$[rsp]
	movzx	ecx, WORD PTR [rcx+8]
	mov	rdx, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rdx+rcx*4+16], eax

; 63   : 		obj->block_thread_num++;

	mov	rax, QWORD PTR obj$[rsp]
	movzx	eax, WORD PTR [rax+8]
	inc	ax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	WORD PTR [rcx+8], ax

; 64   : 		force_sched();

	call	force_sched

; 65   : 	}

	jmp	SHORT $LN2@AuMutexLoc
$LN1@AuMutexLoc:

; 66   : 	
; 67   : 	obj->blocks = 1;

	mov	rax, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rax+12], 1

; 68   : 	obj->owner_thread = get_current_thread();

	call	get_current_thread
	mov	rcx, QWORD PTR obj$[rsp]
	mov	QWORD PTR [rcx], rax
$LN5@AuMutexLoc:

; 69   : }

	add	rsp, 40					; 00000028H
	ret	0
AuMutexLock ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\atomic\mutex.cpp
_TEXT	SEGMENT
obj$ = 32
AuMutexCreate PROC

; 39   : AU_EXTERN AU_EXPORT mutex_t * AuMutexCreate () {

$LN3:
	sub	rsp, 56					; 00000038H

; 40   : 	mutex_t * obj = (mutex_t*)malloc(sizeof(mutex_t));

	mov	ecx, 216				; 000000d8H
	call	malloc
	mov	QWORD PTR obj$[rsp], rax

; 41   : 	obj->blocks = 0;

	mov	rax, QWORD PTR obj$[rsp]
	mov	DWORD PTR [rax+12], 0

; 42   : 	obj->owner_thread= 0;

	mov	rax, QWORD PTR obj$[rsp]
	mov	QWORD PTR [rax], 0

; 43   : 	obj->block_thread_num = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR obj$[rsp]
	mov	WORD PTR [rcx+8], ax

; 44   : 	return obj;

	mov	rax, QWORD PTR obj$[rsp]

; 45   : }

	add	rsp, 56					; 00000038H
	ret	0
AuMutexCreate ENDP
_TEXT	ENDS
END
