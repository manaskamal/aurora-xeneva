; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?master_count@@3HA				; master_count
PUBLIC	?slave_count@@3HA				; slave_count
PUBLIC	?root@@3PEAU_tele_type_@@EA			; root
PUBLIC	?last@@3PEAU_tele_type_@@EA			; last
_BSS	SEGMENT
?root@@3PEAU_tele_type_@@EA DQ 01H DUP (?)		; root
?last@@3PEAU_tele_type_@@EA DQ 01H DUP (?)		; last
_BSS	ENDS
CONST	SEGMENT
$SG3580	DB	'/dev/', 00H
	ORG $+2
$SG3581	DB	'ttym', 00H
	ORG $+3
$SG3585	DB	'[TTY]: Master node mounted at -> %s  ', 0dH, 0aH, 00H
$SG3587	DB	'/dev/', 00H
	ORG $+2
$SG3588	DB	'ttys', 00H
	ORG $+3
$SG3592	DB	'[TTY]: Slave node mounted at %s ', 0dH, 0aH, 00H
	ORG $+5
$SG3595	DB	'Used RAM -> %d MB/ Total RAM %d MB', 0dH, 0aH, 00H
CONST	ENDS
_DATA	SEGMENT
?master_count@@3HA DD 01H				; master_count
?slave_count@@3HA DD 01H				; slave_count
_DATA	ENDS
PUBLIC	?ttype_init@@YAXXZ				; ttype_init
PUBLIC	?ttype_create@@YAHPEAH0@Z			; ttype_create
PUBLIC	?get_ttype@@YAPEAU_tele_type_@@H@Z		; get_ttype
PUBLIC	?ttype_dup_master@@YAXHH@Z			; ttype_dup_master
PUBLIC	?ttype_insert@@YAXPEAU_tele_type_@@@Z		; ttype_insert
PUBLIC	?ttype_delete@@YAXPEAU_tele_type_@@@Z		; ttype_delete
PUBLIC	?ttype_master_read@@YAXPEAU_vfs_node_@@PEA_KI@Z	; ttype_master_read
PUBLIC	?ttype_master_write@@YAXPEAU_vfs_node_@@PEA_KI@Z ; ttype_master_write
PUBLIC	?ttype_slave_read@@YAXPEAU_vfs_node_@@PEA_KI@Z	; ttype_slave_read
PUBLIC	?ttype_slave_write@@YAXPEAU_vfs_node_@@PEA_KI@Z	; ttype_slave_write
EXTRN	strcpy:PROC
EXTRN	memset:PROC
EXTRN	vfs_mount:PROC
EXTRN	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z:PROC	; circ_buf_init
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuPmmngrFree:PROC
EXTRN	?pmmngr_get_used_ram@@YA_KXZ:PROC		; pmmngr_get_used_ram
EXTRN	?pmmngr_get_total_ram@@YA_KXZ:PROC		; pmmngr_get_total_ram
EXTRN	x64_cli:PROC
EXTRN	malloc:PROC
EXTRN	?sztoa@@YAPEAD_KPEADH@Z:PROC			; sztoa
EXTRN	get_current_thread:PROC
EXTRN	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z:PROC ; thread_iterate_ready_list
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
EXTRN	_debug_print_:PROC
pdata	SEGMENT
$pdata$?ttype_create@@YAHPEAH0@Z DD imagerel $LN3
	DD	imagerel $LN3+1426
	DD	imagerel $unwind$?ttype_create@@YAHPEAH0@Z
$pdata$?get_ttype@@YAPEAU_tele_type_@@H@Z DD imagerel $LN8
	DD	imagerel $LN8+78
	DD	imagerel $unwind$?get_ttype@@YAPEAU_tele_type_@@H@Z
$pdata$?ttype_dup_master@@YAXHH@Z DD imagerel $LN5
	DD	imagerel $LN5+156
	DD	imagerel $unwind$?ttype_dup_master@@YAXHH@Z
$pdata$?ttype_delete@@YAXPEAU_tele_type_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+146
	DD	imagerel $unwind$?ttype_delete@@YAXPEAU_tele_type_@@@Z
$pdata$?ttype_master_read@@YAXPEAU_vfs_node_@@PEA_KI@Z DD imagerel $LN3
	DD	imagerel $LN3+78
	DD	imagerel $unwind$?ttype_master_read@@YAXPEAU_vfs_node_@@PEA_KI@Z
$pdata$?ttype_master_write@@YAXPEAU_vfs_node_@@PEA_KI@Z DD imagerel $LN3
	DD	imagerel $LN3+29
	DD	imagerel $unwind$?ttype_master_write@@YAXPEAU_vfs_node_@@PEA_KI@Z
$pdata$?ttype_slave_read@@YAXPEAU_vfs_node_@@PEA_KI@Z DD imagerel $LN3
	DD	imagerel $LN3+29
	DD	imagerel $unwind$?ttype_slave_read@@YAXPEAU_vfs_node_@@PEA_KI@Z
$pdata$?ttype_slave_write@@YAXPEAU_vfs_node_@@PEA_KI@Z DD imagerel $LN3
	DD	imagerel $LN3+78
	DD	imagerel $unwind$?ttype_slave_write@@YAXPEAU_vfs_node_@@PEA_KI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?ttype_create@@YAHPEAH0@Z DD 021101H
	DD	0130111H
$unwind$?get_ttype@@YAPEAU_tele_type_@@H@Z DD 010801H
	DD	02208H
$unwind$?ttype_dup_master@@YAXHH@Z DD 010c01H
	DD	0620cH
$unwind$?ttype_delete@@YAXPEAU_tele_type_@@@Z DD 010901H
	DD	04209H
$unwind$?ttype_master_read@@YAXPEAU_vfs_node_@@PEA_KI@Z DD 011301H
	DD	08213H
$unwind$?ttype_master_write@@YAXPEAU_vfs_node_@@PEA_KI@Z DD 011301H
	DD	04213H
$unwind$?ttype_slave_read@@YAXPEAU_vfs_node_@@PEA_KI@Z DD 011301H
	DD	04213H
$unwind$?ttype_slave_write@@YAXPEAU_vfs_node_@@PEA_KI@Z DD 011301H
	DD	08213H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
tv64 = 32
node$ = 40
type$ = 48
file$ = 80
buffer$ = 88
length$ = 96
?ttype_slave_write@@YAXPEAU_vfs_node_@@PEA_KI@Z PROC	; ttype_slave_write

; 203  : void ttype_slave_write (vfs_node_t *file, uint64_t* buffer, uint32_t length) {

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 204  : 	vfs_node_t *node = get_current_thread()->fd[get_current_thread()->slave_fd];

	call	get_current_thread
	mov	QWORD PTR tv64[rsp], rax
	call	get_current_thread
	movzx	eax, BYTE PTR [rax+757]
	mov	rcx, QWORD PTR tv64[rsp]
	mov	rax, QWORD PTR [rcx+rax*8+272]
	mov	QWORD PTR node$[rsp], rax

; 205  : 	ttype_t *type = (ttype_t*)node->device;

	mov	rax, QWORD PTR node$[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR type$[rsp], rax

; 206  : 	/*for (int i = 0; i < 32; i++)
; 207  : 		type->out_buffer[i] = buffer[i];*/
; 208  : }

	add	rsp, 72					; 00000048H
	ret	0
?ttype_slave_write@@YAXPEAU_vfs_node_@@PEA_KI@Z ENDP	; ttype_slave_write
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
file$ = 48
buffer$ = 56
length$ = 64
?ttype_slave_read@@YAXPEAU_vfs_node_@@PEA_KI@Z PROC	; ttype_slave_read

; 171  : void ttype_slave_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 172  : 	x64_cli();

	call	x64_cli

; 173  : 
; 174  : 	/* get the ttype */
; 175  : 	/*vfs_node_t *node = get_current_thread()->fd[get_current_thread()->slave_fd];
; 176  : 	ttype_t *type = (ttype_t*)node->device;*/
; 177  : 
; 178  : 	//! lets read everything that has been written 
; 179  : 	//! by child, be carefull we only read that much
; 180  : 	//! that have been written by child process
; 181  : 	//for (int i = 0; i < type->written; i++) {
; 182  : 	//	circular_buf_get(type->in_buffer,(uint8_t*)&buffer[i]);
; 183  : 	//}
; 184  : 
; 185  : 	//! resate the written count, so that child process
; 186  : 	//! can write its next data
; 187  : 	//type->written = 0;
; 188  : 
; 189  : 	//! check if child process is blocked
; 190  : 	//if (type->blocked_pid > 0) {
; 191  : 		//! yes, than simply unblock it
; 192  : 	/*	thread_t *dest = thread_iterate_ready_list(type->blocked_pid);
; 193  : 		if (dest == NULL)
; 194  : 			dest = thread_iterate_block_list(type->blocked_pid);
; 195  : 
; 196  : 		if (dest != NULL && dest->state == THREAD_STATE_BLOCKED)
; 197  : 			unblock_thread(dest);*/
; 198  : 	//}
; 199  : 
; 200  : 	
; 201  : }

	add	rsp, 40					; 00000028H
	ret	0
?ttype_slave_read@@YAXPEAU_vfs_node_@@PEA_KI@Z ENDP	; ttype_slave_read
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
file$ = 48
buffer$ = 56
length$ = 64
?ttype_master_write@@YAXPEAU_vfs_node_@@PEA_KI@Z PROC	; ttype_master_write

; 116  : void ttype_master_write (vfs_node_t *file, uint64_t* buffer, uint32_t length) {

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 117  : 	x64_cli();

	call	x64_cli

; 118  : 
; 119  : 	//! get the master node from the child process
; 120  : 	//vfs_node_t *node = get_current_thread()->fd[get_current_thread()->master_fd];
; 121  : 	//ttype_t *type = (ttype_t*)node->device;
; 122  : 
; 123  : 	//! first of all, get the registered terminal emulator
; 124  : 	//! id, we need to unblock it, if it is blocked by default
; 125  : 	/*thread_t *dest = thread_iterate_ready_list(type->pid);
; 126  : 	if (dest == NULL)
; 127  : 		dest = thread_iterate_block_list(type->pid);*/
; 128  : 
; 129  : 	//! check, if another data is already written to the
; 130  : 	//! buffer
; 131  : 	//if (type->written > 0)  {
; 132  : 		//! yes, the buffer is in use, let's wait for the
; 133  : 		//! buffer usage to be finished
; 134  : 		//type->blocked_pid = get_current_thread()->id;
; 135  : 
; 136  : 		//! unblock the terminal emulator if it is blocked cause
; 137  : 		//! it will get the ttype buffer usage to be finished
; 138  : 		//if (dest != NULL && dest->state == THREAD_STATE_BLOCKED)
; 139  : 		//	unblock_thread(dest);
; 140  : 
; 141  : 		////! block the current thread, till the buffer usage get over
; 142  : 		//block_thread(get_current_thread());
; 143  : 		//force_sched();
; 144  : 	//}
; 145  : 
; 146  : 
; 147  :      //! unblock the terminal emulator, cause - new text is available to 
; 148  : 	//! be processed
; 149  : 	//if (dest != NULL && dest->state == THREAD_STATE_BLOCKED)
; 150  : 	//	unblock_thread(dest);
; 151  : 
; 152  : 	////! so finally we now use the type buffer to store our text data
; 153  : 	//for (int i = 0; i < length; i++) {
; 154  : 	//	circular_buf_put(type->in_buffer,buffer[i]);
; 155  : 	//	//type->written++; //increament the written count, cause we only
; 156  : 	//	// read that much of text, that actually get written
; 157  : 	//}
; 158  : 
; 159  : 
; 160  : 	
; 161  : 
; 162  : }

	add	rsp, 40					; 00000028H
	ret	0
?ttype_master_write@@YAXPEAU_vfs_node_@@PEA_KI@Z ENDP	; ttype_master_write
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
tv64 = 32
node$ = 40
type$ = 48
file$ = 80
buffer$ = 88
length$ = 96
?ttype_master_read@@YAXPEAU_vfs_node_@@PEA_KI@Z PROC	; ttype_master_read

; 101  : void ttype_master_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 102  : 	//!Read it from out buffer
; 103  : 	vfs_node_t *node = get_current_thread()->fd[get_current_thread()->master_fd];

	call	get_current_thread
	mov	QWORD PTR tv64[rsp], rax
	call	get_current_thread
	movzx	eax, BYTE PTR [rax+756]
	mov	rcx, QWORD PTR tv64[rsp]
	mov	rax, QWORD PTR [rcx+rax*8+272]
	mov	QWORD PTR node$[rsp], rax

; 104  : 	ttype_t *type = (ttype_t*)node->device;

	mov	rax, QWORD PTR node$[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR type$[rsp], rax

; 105  : 	/*for (int i = 0; i < 32; i++)
; 106  : 		buffer[i] = type->out_buffer[i];*/
; 107  : 
; 108  : }

	add	rsp, 72					; 00000048H
	ret	0
?ttype_master_read@@YAXPEAU_vfs_node_@@PEA_KI@Z ENDP	; ttype_master_read
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
tty$ = 48
?ttype_delete@@YAXPEAU_tele_type_@@@Z PROC		; ttype_delete

; 75   : void ttype_delete (ttype_t* tty) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 76   : 
; 77   : 	if (root == NULL)

	cmp	QWORD PTR ?root@@3PEAU_tele_type_@@EA, 0 ; root
	jne	SHORT $LN5@ttype_dele

; 78   : 		return;

	jmp	SHORT $LN6@ttype_dele
$LN5@ttype_dele:

; 79   : 
; 80   : 	if (tty == root) {

	mov	rax, QWORD PTR ?root@@3PEAU_tele_type_@@EA ; root
	cmp	QWORD PTR tty$[rsp], rax
	jne	SHORT $LN4@ttype_dele

; 81   : 		root = root->next;

	mov	rax, QWORD PTR ?root@@3PEAU_tele_type_@@EA ; root
	mov	rax, QWORD PTR [rax+104]
	mov	QWORD PTR ?root@@3PEAU_tele_type_@@EA, rax ; root

; 82   : 	} else {

	jmp	SHORT $LN3@ttype_dele
$LN4@ttype_dele:

; 83   : 		tty->prev->next = tty->next;

	mov	rax, QWORD PTR tty$[rsp]
	mov	rax, QWORD PTR [rax+112]
	mov	rcx, QWORD PTR tty$[rsp]
	mov	rcx, QWORD PTR [rcx+104]
	mov	QWORD PTR [rax+104], rcx
$LN3@ttype_dele:

; 84   : 	}
; 85   : 
; 86   : 	if (tty == last) {

	mov	rax, QWORD PTR ?last@@3PEAU_tele_type_@@EA ; last
	cmp	QWORD PTR tty$[rsp], rax
	jne	SHORT $LN2@ttype_dele

; 87   : 		last = tty->prev;

	mov	rax, QWORD PTR tty$[rsp]
	mov	rax, QWORD PTR [rax+112]
	mov	QWORD PTR ?last@@3PEAU_tele_type_@@EA, rax ; last

; 88   : 	} else {

	jmp	SHORT $LN1@ttype_dele
$LN2@ttype_dele:

; 89   : 		tty->next->prev = tty->prev;

	mov	rax, QWORD PTR tty$[rsp]
	mov	rax, QWORD PTR [rax+104]
	mov	rcx, QWORD PTR tty$[rsp]
	mov	rcx, QWORD PTR [rcx+112]
	mov	QWORD PTR [rax+112], rcx
$LN1@ttype_dele:

; 90   : 	}
; 91   : 
; 92   : 	AuPmmngrFree(tty);

	mov	rcx, QWORD PTR tty$[rsp]
	call	AuPmmngrFree
$LN6@ttype_dele:

; 93   : }

	add	rsp, 40					; 00000028H
	ret	0
?ttype_delete@@YAXPEAU_tele_type_@@@Z ENDP		; ttype_delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
tty$ = 8
?ttype_insert@@YAXPEAU_tele_type_@@@Z PROC		; ttype_insert

; 59   : void ttype_insert (ttype_t* tty ) {

	mov	QWORD PTR [rsp+8], rcx

; 60   : 	tty->next = NULL;

	mov	rax, QWORD PTR tty$[rsp]
	mov	QWORD PTR [rax+104], 0

; 61   : 	tty->prev = NULL;

	mov	rax, QWORD PTR tty$[rsp]
	mov	QWORD PTR [rax+112], 0

; 62   : 
; 63   : 	if (root == NULL) {

	cmp	QWORD PTR ?root@@3PEAU_tele_type_@@EA, 0 ; root
	jne	SHORT $LN2@ttype_inse

; 64   : 		last = tty;

	mov	rax, QWORD PTR tty$[rsp]
	mov	QWORD PTR ?last@@3PEAU_tele_type_@@EA, rax ; last

; 65   : 		root = tty;

	mov	rax, QWORD PTR tty$[rsp]
	mov	QWORD PTR ?root@@3PEAU_tele_type_@@EA, rax ; root

; 66   : 		//_debug_print_ ("**TTY ROOT WAS NULL \r\n");
; 67   : 	} else {

	jmp	SHORT $LN1@ttype_inse
$LN2@ttype_inse:

; 68   : 		last->next = tty;

	mov	rax, QWORD PTR ?last@@3PEAU_tele_type_@@EA ; last
	mov	rcx, QWORD PTR tty$[rsp]
	mov	QWORD PTR [rax+104], rcx

; 69   : 		tty->prev = last;

	mov	rax, QWORD PTR tty$[rsp]
	mov	rcx, QWORD PTR ?last@@3PEAU_tele_type_@@EA ; last
	mov	QWORD PTR [rax+112], rcx
$LN1@ttype_inse:

; 70   : 	}
; 71   : 	last = tty;

	mov	rax, QWORD PTR tty$[rsp]
	mov	QWORD PTR ?last@@3PEAU_tele_type_@@EA, rax ; last

; 72   : }

	ret	0
?ttype_insert@@YAXPEAU_tele_type_@@@Z ENDP		; ttype_insert
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
dest$ = 32
node$ = 40
task_id$ = 64
master_fd$ = 72
?ttype_dup_master@@YAXHH@Z PROC				; ttype_dup_master

; 352  : void ttype_dup_master (int task_id, int master_fd) {

$LN5:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 353  : 	x64_cli();

	call	x64_cli

; 354  : 	vfs_node_t *node = get_current_thread()->fd[master_fd];

	call	get_current_thread
	movsxd	rcx, DWORD PTR master_fd$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+272]
	mov	QWORD PTR node$[rsp], rax

; 355  : 	thread_t *dest = thread_iterate_ready_list(task_id);

	movzx	ecx, WORD PTR task_id$[rsp]
	call	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ; thread_iterate_ready_list
	mov	QWORD PTR dest$[rsp], rax

; 356  : 	if (dest == NULL) {

	cmp	QWORD PTR dest$[rsp], 0
	jne	SHORT $LN2@ttype_dup_

; 357  : 		dest = thread_iterate_block_list(task_id);

	mov	ecx, DWORD PTR task_id$[rsp]
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR dest$[rsp], rax
$LN2@ttype_dup_:

; 358  : 	}
; 359  : 	if (dest != NULL) {

	cmp	QWORD PTR dest$[rsp], 0
	je	SHORT $LN1@ttype_dup_

; 360  : 		dest->fd[1] = node;

	mov	eax, 8
	imul	rax, 1
	mov	rcx, QWORD PTR dest$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	mov	QWORD PTR [rcx+rax+272], rdx

; 361  : 		dest->fd[2] = node;

	mov	eax, 8
	imul	rax, 2
	mov	rcx, QWORD PTR dest$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	mov	QWORD PTR [rcx+rax+272], rdx
$LN1@ttype_dup_:

; 362  : 	}
; 363  : 	dest->master_fd = 1;

	mov	rax, QWORD PTR dest$[rsp]
	mov	BYTE PTR [rax+756], 1

; 364  : }

	add	rsp, 56					; 00000038H
	ret	0
?ttype_dup_master@@YAXHH@Z ENDP				; ttype_dup_master
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
tty$1 = 0
id$ = 32
?get_ttype@@YAPEAU_tele_type_@@H@Z PROC			; get_ttype

; 210  : ttype_t * get_ttype (int id) {

$LN8:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 24

; 211  : 	if (root != NULL){

	cmp	QWORD PTR ?root@@3PEAU_tele_type_@@EA, 0 ; root
	je	SHORT $LN5@get_ttype

; 212  : 		for (ttype_t* tty = root; tty != NULL; tty = tty->next) {

	mov	rax, QWORD PTR ?root@@3PEAU_tele_type_@@EA ; root
	mov	QWORD PTR tty$1[rsp], rax
	jmp	SHORT $LN4@get_ttype
$LN3@get_ttype:
	mov	rax, QWORD PTR tty$1[rsp]
	mov	rax, QWORD PTR [rax+104]
	mov	QWORD PTR tty$1[rsp], rax
$LN4@get_ttype:
	cmp	QWORD PTR tty$1[rsp], 0
	je	SHORT $LN2@get_ttype

; 213  : 			if (tty->id == id) 

	mov	rax, QWORD PTR tty$1[rsp]
	movzx	eax, BYTE PTR [rax]
	cmp	eax, DWORD PTR id$[rsp]
	jne	SHORT $LN1@get_ttype

; 214  : 				return tty;

	mov	rax, QWORD PTR tty$1[rsp]
	jmp	SHORT $LN6@get_ttype
$LN1@get_ttype:

; 215  : 		}

	jmp	SHORT $LN3@get_ttype
$LN2@get_ttype:
$LN5@get_ttype:

; 216  : 	}
; 217  : 	return NULL;

	xor	eax, eax
$LN6@get_ttype:

; 218  : }

	add	rsp, 24
	ret	0
?get_ttype@@YAPEAU_tele_type_@@H@Z ENDP			; get_ttype
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
tty$ = 32
mn$ = 40
sn$ = 48
s_fd$ = 56
m_fd$ = 60
sname$ = 64
mname$ = 80
inbuffer$ = 96
tv263 = 104
tv252 = 112
outbuffer$ = 120
tv279 = 128
master_fd$ = 160
slave_fd$ = 168
?ttype_create@@YAHPEAH0@Z PROC				; ttype_create

; 220  : int ttype_create (int* master_fd, int* slave_fd) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 152				; 00000098H

; 221  : 	x64_cli();

	call	x64_cli

; 222  : 
; 223  : 	/** The malloc needs fixings, that's why there
; 224  : 	 ** are limited number of pty
; 225  : 	 **/
; 226  : 	/*if (master_count > 3)
; 227  : 		return -1;*/
; 228  : 
; 229  : 	ttype_t *tty= (ttype_t*)malloc(sizeof(ttype_t));  //pmmngr_alloc();

	mov	ecx, 120				; 00000078H
	call	malloc
	mov	QWORD PTR tty$[rsp], rax

; 230  : 
; 231  : 	void* inbuffer = AuPmmngrAlloc();

	call	AuPmmngrAlloc
	mov	QWORD PTR inbuffer$[rsp], rax

; 232  : 	memset(inbuffer, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR inbuffer$[rsp]
	call	memset

; 233  : 	void* outbuffer = AuPmmngrAlloc();

	call	AuPmmngrAlloc
	mov	QWORD PTR outbuffer$[rsp], rax

; 234  : 	memset(outbuffer, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR outbuffer$[rsp]
	call	memset

; 235  : 
; 236  : 	tty->in_buffer = circ_buf_init((uint8_t*)inbuffer,4095);

	mov	edx, 4095				; 00000fffH
	mov	rcx, QWORD PTR inbuffer$[rsp]
	call	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z ; circ_buf_init
	mov	rcx, QWORD PTR tty$[rsp]
	mov	QWORD PTR [rcx+72], rax

; 237  : 	tty->out_buffer = circ_buf_init((uint8_t*)outbuffer, 4095);

	mov	edx, 4095				; 00000fffH
	mov	rcx, QWORD PTR outbuffer$[rsp]
	call	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z ; circ_buf_init
	mov	rcx, QWORD PTR tty$[rsp]
	mov	QWORD PTR [rcx+80], rax

; 238  : 	//
; 239  : 	tty->id = slave_count;

	mov	rax, QWORD PTR tty$[rsp]
	movzx	ecx, BYTE PTR ?slave_count@@3HA
	mov	BYTE PTR [rax], cl

; 240  : 
; 241  : 	//! tty->pid -- stores the current terminal emulator id
; 242  : 
; 243  : 	//! Create the namings
; 244  : 	char mname[10];
; 245  : 	strcpy (mname, "/dev/");

	lea	rdx, OFFSET FLAT:$SG3580
	lea	rcx, QWORD PTR mname$[rsp]
	call	strcpy

; 246  : 	strcpy (mname+5, "ttym");

	lea	rax, QWORD PTR mname$[rsp+5]
	lea	rdx, OFFSET FLAT:$SG3581
	mov	rcx, rax
	call	strcpy

; 247  : 	sztoa (master_count,mname+9,10);

	lea	rax, QWORD PTR mname$[rsp+9]
	movsxd	rcx, DWORD PTR ?master_count@@3HA	; master_count
	mov	r8d, 10
	mov	rdx, rax
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 248  : 
; 249  : 
; 250  : 
; 251  : 	//////! Master node
; 252  : 	vfs_node_t *mn = (vfs_node_t*)malloc(sizeof(vfs_node_t));  //pmmngr_alloc();

	mov	ecx, 104				; 00000068H
	call	malloc
	mov	QWORD PTR mn$[rsp], rax

; 253  : 	strcpy(mn->filename, mname+5);

	lea	rax, QWORD PTR mname$[rsp+5]
	mov	rcx, QWORD PTR mn$[rsp]
	mov	rdx, rax
	call	strcpy

; 254  : 	mn->size = 0;

	mov	rax, QWORD PTR mn$[rsp]
	mov	DWORD PTR [rax+32], 0

; 255  : 	mn->eof = 0;

	mov	rax, QWORD PTR mn$[rsp]
	mov	BYTE PTR [rax+36], 0

; 256  : 	mn->pos = 0;

	mov	rax, QWORD PTR mn$[rsp]
	mov	DWORD PTR [rax+40], 0

; 257  : 	mn->current = 0;

	mov	rax, QWORD PTR mn$[rsp]
	mov	DWORD PTR [rax+44], 0

; 258  : 	mn->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR mn$[rsp]
	mov	BYTE PTR [rax+48], 4

; 259  : 	mn->status = 0;

	mov	rax, QWORD PTR mn$[rsp]
	mov	BYTE PTR [rax+49], 0

; 260  : 	mn->open = 0;

	mov	rax, QWORD PTR mn$[rsp]
	mov	QWORD PTR [rax+64], 0

; 261  : 	mn->device = tty;

	mov	rax, QWORD PTR mn$[rsp]
	mov	rcx, QWORD PTR tty$[rsp]
	mov	QWORD PTR [rax+56], rcx

; 262  : 	mn->read = ttype_master_read;

	mov	rax, QWORD PTR mn$[rsp]
	lea	rcx, OFFSET FLAT:?ttype_master_read@@YAXPEAU_vfs_node_@@PEA_KI@Z ; ttype_master_read
	mov	QWORD PTR [rax+72], rcx

; 263  : 	mn->write = ttype_master_write;

	mov	rax, QWORD PTR mn$[rsp]
	lea	rcx, OFFSET FLAT:?ttype_master_write@@YAXPEAU_vfs_node_@@PEA_KI@Z ; ttype_master_write
	mov	QWORD PTR [rax+80], rcx

; 264  : 	mn->read_blk = 0;

	mov	rax, QWORD PTR mn$[rsp]
	mov	QWORD PTR [rax+88], 0

; 265  : 	mn->ioquery = 0;

	mov	rax, QWORD PTR mn$[rsp]
	mov	QWORD PTR [rax+96], 0

; 266  : 
; 267  : 	_debug_print_ ("[TTY]: Master node mounted at -> %s  \r\n", mname);

	lea	rdx, QWORD PTR mname$[rsp]
	lea	rcx, OFFSET FLAT:$SG3585
	call	_debug_print_

; 268  : 
; 269  : 	char sname[10];
; 270  : 	strcpy (sname, "/dev/");

	lea	rdx, OFFSET FLAT:$SG3587
	lea	rcx, QWORD PTR sname$[rsp]
	call	strcpy

; 271  : 	strcpy (sname+5, "ttys");

	lea	rax, QWORD PTR sname$[rsp+5]
	lea	rdx, OFFSET FLAT:$SG3588
	mov	rcx, rax
	call	strcpy

; 272  : 	sztoa (slave_count,sname+9,10);

	lea	rax, QWORD PTR sname$[rsp+9]
	movsxd	rcx, DWORD PTR ?slave_count@@3HA	; slave_count
	mov	r8d, 10
	mov	rdx, rax
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 273  : 
; 274  : 	vfs_node_t *sn = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 104				; 00000068H
	call	malloc
	mov	QWORD PTR sn$[rsp], rax

; 275  : 	strcpy(sn->filename, sname);

	mov	rax, QWORD PTR sn$[rsp]
	lea	rdx, QWORD PTR sname$[rsp]
	mov	rcx, rax
	call	strcpy

; 276  : 	sn->size = 0;

	mov	rax, QWORD PTR sn$[rsp]
	mov	DWORD PTR [rax+32], 0

; 277  : 	sn->eof = 0;

	mov	rax, QWORD PTR sn$[rsp]
	mov	BYTE PTR [rax+36], 0

; 278  : 	sn->pos = 0;

	mov	rax, QWORD PTR sn$[rsp]
	mov	DWORD PTR [rax+40], 0

; 279  : 	sn->current = 0;

	mov	rax, QWORD PTR sn$[rsp]
	mov	DWORD PTR [rax+44], 0

; 280  : 	sn->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR sn$[rsp]
	mov	BYTE PTR [rax+48], 4

; 281  : 	sn->status = 0;

	mov	rax, QWORD PTR sn$[rsp]
	mov	BYTE PTR [rax+49], 0

; 282  : 	sn->open = 0;

	mov	rax, QWORD PTR sn$[rsp]
	mov	QWORD PTR [rax+64], 0

; 283  : 	sn->device = tty;

	mov	rax, QWORD PTR sn$[rsp]
	mov	rcx, QWORD PTR tty$[rsp]
	mov	QWORD PTR [rax+56], rcx

; 284  : 	sn->read = ttype_slave_read;

	mov	rax, QWORD PTR sn$[rsp]
	lea	rcx, OFFSET FLAT:?ttype_slave_read@@YAXPEAU_vfs_node_@@PEA_KI@Z ; ttype_slave_read
	mov	QWORD PTR [rax+72], rcx

; 285  : 	sn->write = ttype_slave_write;

	mov	rax, QWORD PTR sn$[rsp]
	lea	rcx, OFFSET FLAT:?ttype_slave_write@@YAXPEAU_vfs_node_@@PEA_KI@Z ; ttype_slave_write
	mov	QWORD PTR [rax+80], rcx

; 286  : 	sn->read_blk = 0;

	mov	rax, QWORD PTR sn$[rsp]
	mov	QWORD PTR [rax+88], 0

; 287  : 	sn->ioquery = 0;

	mov	rax, QWORD PTR sn$[rsp]
	mov	QWORD PTR [rax+96], 0

; 288  : 	vfs_mount (sname, sn, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR sn$[rsp]
	lea	rcx, QWORD PTR sname$[rsp]
	call	vfs_mount

; 289  : 
; 290  : 	_debug_print_ ("[TTY]: Slave node mounted at %s \r\n", sname);

	lea	rdx, QWORD PTR sname$[rsp]
	lea	rcx, OFFSET FLAT:$SG3592
	call	_debug_print_

; 291  : 	
; 292  : 	/*for (int i = 0; i < 32; i++) {
; 293  : 		tty->m_path[i] = mname[i];
; 294  : 		tty->s_path[i] = sname[i];
; 295  : 	}*/
; 296  : 		
; 297  : 	tty->controlling_pid = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR tty$[rsp]
	mov	WORD PTR [rcx+88], ax

; 298  : 	tty->foreground_pid = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR tty$[rsp]
	mov	WORD PTR [rcx+90], ax

; 299  : 
; 300  : 	tty->term.c_iflag = ICRNL | BRKINT;

	mov	rax, QWORD PTR tty$[rsp]
	mov	DWORD PTR [rax+12], 258			; 00000102H

; 301  : 	tty->term.c_oflag = ONLCR | OPOST;

	mov	rax, QWORD PTR tty$[rsp]
	mov	DWORD PTR [rax+16], 5

; 302  : 	tty->term.c_lflag = ECHO | ECHOE | ECHOK | ICANON | ISIG | IEXTEN;

	mov	rax, QWORD PTR tty$[rsp]
	mov	DWORD PTR [rax+24], 32827		; 0000803bH

; 303  : 	tty->term.c_cflag = CREAD | CS8;

	mov	rax, QWORD PTR tty$[rsp]
	mov	DWORD PTR [rax+20], 176			; 000000b0H

; 304  : 	tty->term.c_cc[VEOF] = 4;

	mov	eax, 1
	imul	rax, 4
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 4

; 305  : 	tty->term.c_cc[VEOL] = 0;

	mov	eax, 1
	imul	rax, 11
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 0

; 306  : 	tty->term.c_cc[VERASE] = 0x7f;

	mov	eax, 1
	imul	rax, 2
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 127		; 0000007fH

; 307  : 	tty->term.c_cc[VINTR] = 3;

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 3

; 308  : 	tty->term.c_cc[VKILL] = 21;

	mov	eax, 1
	imul	rax, 3
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 21

; 309  : 	tty->term.c_cc[VMIN] = 1;

	mov	eax, 1
	imul	rax, 6
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 1

; 310  : 	tty->term.c_cc[VQUIT] = 28;

	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 28

; 311  : 	tty->term.c_cc[VSTART] = 17;

	mov	eax, 1
	imul	rax, 8
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 17

; 312  : 	tty->term.c_cc[VSTOP] = 19;

	mov	eax, 1
	imul	rax, 9
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 19

; 313  : 	tty->term.c_cc[VSUSP] = 26;

	mov	eax, 1
	imul	rax, 10
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 26

; 314  : 	tty->term.c_cc[VTIME] = 0;

	mov	eax, 1
	imul	rax, 5
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 0

; 315  : 	tty->term.c_cc[VLNEXT] = 22;

	mov	eax, 1
	imul	rax, 15
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 22

; 316  : 	tty->term.c_cc[VWERASE] = 23;

	mov	eax, 1
	imul	rax, 14
	mov	rcx, QWORD PTR tty$[rsp]
	mov	BYTE PTR [rcx+rax+29], 23

; 317  : 
; 318  : 	tty->size.ws_col = 25;

	mov	eax, 25
	mov	rcx, QWORD PTR tty$[rsp]
	mov	WORD PTR [rcx+4], ax

; 319  : 	tty->size.ws_row = 80;

	mov	eax, 80					; 00000050H
	mov	rcx, QWORD PTR tty$[rsp]
	mov	WORD PTR [rcx+2], ax

; 320  : 
; 321  : 	//! Allocate fd for master
; 322  : 	int m_fd = get_current_thread()->fd_current;

	call	get_current_thread
	mov	eax, DWORD PTR [rax+752]
	mov	DWORD PTR m_fd$[rsp], eax

; 323  : 	get_current_thread()->fd[m_fd] = mn;

	call	get_current_thread
	movsxd	rcx, DWORD PTR m_fd$[rsp]
	mov	rdx, QWORD PTR mn$[rsp]
	mov	QWORD PTR [rax+rcx*8+272], rdx

; 324  : 	get_current_thread()->fd_current++;

	call	get_current_thread
	add	rax, 752				; 000002f0H
	mov	QWORD PTR tv252[rsp], rax
	mov	rax, QWORD PTR tv252[rsp]
	mov	eax, DWORD PTR [rax]
	inc	eax
	mov	rcx, QWORD PTR tv252[rsp]
	mov	DWORD PTR [rcx], eax

; 325  : 
; 326  : 	//! Allocate fd for slave
; 327  : 	int s_fd = get_current_thread()->fd_current;

	call	get_current_thread
	mov	eax, DWORD PTR [rax+752]
	mov	DWORD PTR s_fd$[rsp], eax

; 328  : 	get_current_thread()->fd[s_fd] = sn;

	call	get_current_thread
	movsxd	rcx, DWORD PTR s_fd$[rsp]
	mov	rdx, QWORD PTR sn$[rsp]
	mov	QWORD PTR [rax+rcx*8+272], rdx

; 329  : 	get_current_thread()->fd_current++;

	call	get_current_thread
	add	rax, 752				; 000002f0H
	mov	QWORD PTR tv263[rsp], rax
	mov	rax, QWORD PTR tv263[rsp]
	mov	eax, DWORD PTR [rax]
	inc	eax
	mov	rcx, QWORD PTR tv263[rsp]
	mov	DWORD PTR [rcx], eax

; 330  : 
; 331  : 	get_current_thread()->master_fd = m_fd;

	call	get_current_thread
	movzx	ecx, BYTE PTR m_fd$[rsp]
	mov	BYTE PTR [rax+756], cl

; 332  : 	get_current_thread()->slave_fd = s_fd;

	call	get_current_thread
	movzx	ecx, BYTE PTR s_fd$[rsp]
	mov	BYTE PTR [rax+757], cl

; 333  : 
; 334  : 	get_current_thread()->fd[1] = mn;

	call	get_current_thread
	mov	ecx, 8
	imul	rcx, 1
	mov	rdx, QWORD PTR mn$[rsp]
	mov	QWORD PTR [rax+rcx+272], rdx

; 335  : 	get_current_thread()->fd[2] = mn;

	call	get_current_thread
	mov	ecx, 8
	imul	rcx, 2
	mov	rdx, QWORD PTR mn$[rsp]
	mov	QWORD PTR [rax+rcx+272], rdx

; 336  : 
; 337  : 	//tty->master_fd = 0; //m_fd;
; 338  : 	//tty->slave_fd = 0; //s_fd;
; 339  : 
; 340  : 	//_debug_print_ ("TTY Created \r\n");
; 341  : 
; 342  : 	_debug_print_ ("Used RAM -> %d MB/ Total RAM %d MB\r\n", pmmngr_get_used_ram() / 1024 / 1024, pmmngr_get_total_ram() / 1024 / 1024);

	call	?pmmngr_get_total_ram@@YA_KXZ		; pmmngr_get_total_ram
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	QWORD PTR tv279[rsp], rax
	call	?pmmngr_get_used_ram@@YA_KXZ		; pmmngr_get_used_ram
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	rcx, QWORD PTR tv279[rsp]
	mov	r8, rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:$SG3595
	call	_debug_print_

; 343  : 
; 344  : 	ttype_insert (tty);

	mov	rcx, QWORD PTR tty$[rsp]
	call	?ttype_insert@@YAXPEAU_tele_type_@@@Z	; ttype_insert

; 345  : 	master_count++;

	mov	eax, DWORD PTR ?master_count@@3HA	; master_count
	inc	eax
	mov	DWORD PTR ?master_count@@3HA, eax	; master_count

; 346  : 	slave_count++;

	mov	eax, DWORD PTR ?slave_count@@3HA	; slave_count
	inc	eax
	mov	DWORD PTR ?slave_count@@3HA, eax	; slave_count

; 347  : 	*master_fd = m_fd;

	mov	rax, QWORD PTR master_fd$[rsp]
	mov	ecx, DWORD PTR m_fd$[rsp]
	mov	DWORD PTR [rax], ecx

; 348  : 	*slave_fd = s_fd;

	mov	rax, QWORD PTR slave_fd$[rsp]
	mov	ecx, DWORD PTR s_fd$[rsp]
	mov	DWORD PTR [rax], ecx

; 349  : 	return 0;

	xor	eax, eax

; 350  : }

	add	rsp, 152				; 00000098H
	ret	0
?ttype_create@@YAHPEAH0@Z ENDP				; ttype_create
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\ttype.cpp
_TEXT	SEGMENT
?ttype_init@@YAXXZ PROC					; ttype_init

; 368  : 	root = NULL;

	mov	QWORD PTR ?root@@3PEAU_tele_type_@@EA, 0 ; root

; 369  : 	last = NULL;

	mov	QWORD PTR ?last@@3PEAU_tele_type_@@EA, 0 ; last

; 370  : 	master_count = 1;

	mov	DWORD PTR ?master_count@@3HA, 1		; master_count

; 371  : 	slave_count = 1;

	mov	DWORD PTR ?slave_count@@3HA, 1		; slave_count

; 372  : }

	ret	0
?ttype_init@@YAXXZ ENDP					; ttype_init
_TEXT	ENDS
END
