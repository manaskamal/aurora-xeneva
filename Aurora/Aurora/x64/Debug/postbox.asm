; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?post_box_put_msg@@YAXPEAU_post_box_message_@@G@Z ; post_box_put_msg
EXTRN	memcpy:PROC
EXTRN	?unblock_thread@@YAXPEAU_thread_@@@Z:PROC	; unblock_thread
EXTRN	?is_multi_task_enable@@YA_NXZ:PROC		; is_multi_task_enable
EXTRN	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z:PROC ; thread_iterate_ready_list
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
pdata	SEGMENT
$pdata$?post_box_put_msg@@YAXPEAU_post_box_message_@@G@Z DD imagerel $LN7
	DD	imagerel $LN7+157
	DD	imagerel $unwind$?post_box_put_msg@@YAXPEAU_post_box_message_@@G@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?post_box_put_msg@@YAXPEAU_post_box_message_@@G@Z DD 010e01H
	DD	0620eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\ipc\postbox.cpp
_TEXT	SEGMENT
t$ = 32
tmsg$ = 40
msg$ = 64
to_id$ = 72
?post_box_put_msg@@YAXPEAU_post_box_message_@@G@Z PROC	; post_box_put_msg

; 29   : void post_box_put_msg (postmsg_t *msg, uint16_t to_id) {

$LN7:
	mov	WORD PTR [rsp+16], dx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 30   : 
; 31   : 	/* check, if multitasking is initialized,
; 32   : 	   if not, just return
; 33   : 	   */
; 34   : 	if (!is_multi_task_enable())

	call	?is_multi_task_enable@@YA_NXZ		; is_multi_task_enable
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN4@post_box_p

; 35   : 		return;

	jmp	SHORT $LN5@post_box_p
$LN4@post_box_p:

; 36   : 
; 37   : 	thread_t *t  = thread_iterate_ready_list (to_id);   //!ready list

	movzx	ecx, WORD PTR to_id$[rsp]
	call	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ; thread_iterate_ready_list
	mov	QWORD PTR t$[rsp], rax

; 38   : 	if (t == NULL) {

	cmp	QWORD PTR t$[rsp], 0
	jne	SHORT $LN3@post_box_p

; 39   : 		t = thread_iterate_block_list(to_id);

	movzx	eax, WORD PTR to_id$[rsp]
	mov	ecx, eax
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR t$[rsp], rax
$LN3@post_box_p:

; 40   : 	}
; 41   : 
; 42   : 	postmsg_t *tmsg = (postmsg_t*)t->msg_box;

	mov	rax, QWORD PTR t$[rsp]
	mov	rax, QWORD PTR [rax+256]
	mov	QWORD PTR tmsg$[rsp], rax

; 43   : 	if (tmsg->type == 0)

	mov	rax, QWORD PTR tmsg$[rsp]
	movzx	eax, WORD PTR [rax]
	test	eax, eax
	jne	SHORT $LN2@post_box_p

; 44   : 		memcpy (t->msg_box,msg,sizeof(postmsg_t));

	mov	r8d, 32					; 00000020H
	mov	rdx, QWORD PTR msg$[rsp]
	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR [rax+256]
	call	memcpy
$LN2@post_box_p:

; 45   : 
; 46   : 	if (t->state == THREAD_STATE_BLOCKED){

	mov	rax, QWORD PTR t$[rsp]
	movzx	eax, BYTE PTR [rax+240]
	cmp	eax, 3
	jne	SHORT $LN1@post_box_p

; 47   : 		unblock_thread(t);

	mov	rcx, QWORD PTR t$[rsp]
	call	?unblock_thread@@YAXPEAU_thread_@@@Z	; unblock_thread
$LN1@post_box_p:
$LN5@post_box_p:

; 48   : 	}
; 49   : }

	add	rsp, 56					; 00000038H
	ret	0
?post_box_put_msg@@YAXPEAU_post_box_message_@@G@Z ENDP	; post_box_put_msg
_TEXT	ENDS
END
