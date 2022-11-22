; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3606	DB	'AuPipe', 00H
	ORG $+1
$SG3610	DB	'AuPipe', 00H
CONST	ENDS
PUBLIC	?AuCreatePipe@@YAPEAU_pipe_@@XZ			; AuCreatePipe
PUBLIC	?AuAllocAnonPipe@@YAXQEAH@Z			; AuAllocAnonPipe
PUBLIC	?pipe_read@@YA_KPEAU_vfs_node_@@PEA_KI@Z	; pipe_read
PUBLIC	?pipe_write@@YAXPEAU_vfs_node_@@PEA_KI@Z	; pipe_write
PUBLIC	?pipe_close@@YAHPEAU_vfs_node_@@@Z		; pipe_close
EXTRN	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z:PROC	; circ_buf_init
EXTRN	?circular_buf_put@@YAXPEAU_circ_buf_@@E@Z:PROC	; circular_buf_put
EXTRN	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z:PROC ; circular_buf_get
EXTRN	strcpy:PROC
EXTRN	malloc:PROC
EXTRN	free:PROC
EXTRN	get_current_thread:PROC
pdata	SEGMENT
$pdata$?AuCreatePipe@@YAPEAU_pipe_@@XZ DD imagerel $LN3
	DD	imagerel $LN3+99
	DD	imagerel $unwind$?AuCreatePipe@@YAPEAU_pipe_@@XZ
$pdata$?AuAllocAnonPipe@@YAXQEAH@Z DD imagerel $LN3
	DD	imagerel $LN3+590
	DD	imagerel $unwind$?AuAllocAnonPipe@@YAXQEAH@Z
$pdata$?pipe_read@@YA_KPEAU_vfs_node_@@PEA_KI@Z DD imagerel $LN6
	DD	imagerel $LN6+105
	DD	imagerel $unwind$?pipe_read@@YA_KPEAU_vfs_node_@@PEA_KI@Z
$pdata$?pipe_write@@YAXPEAU_vfs_node_@@PEA_KI@Z DD imagerel $LN6
	DD	imagerel $LN6+97
	DD	imagerel $unwind$?pipe_write@@YAXPEAU_vfs_node_@@PEA_KI@Z
$pdata$?pipe_close@@YAHPEAU_vfs_node_@@@Z DD imagerel $LN4
	DD	imagerel $LN4+52
	DD	imagerel $unwind$?pipe_close@@YAHPEAU_vfs_node_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuCreatePipe@@YAPEAU_pipe_@@XZ DD 010401H
	DD	08204H
$unwind$?AuAllocAnonPipe@@YAXQEAH@Z DD 010901H
	DD	08209H
$unwind$?pipe_read@@YA_KPEAU_vfs_node_@@PEA_KI@Z DD 011301H
	DD	06213H
$unwind$?pipe_write@@YAXPEAU_vfs_node_@@PEA_KI@Z DD 011301H
	DD	06213H
$unwind$?pipe_close@@YAHPEAU_vfs_node_@@@Z DD 010901H
	DD	04209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\pipe.cpp
_TEXT	SEGMENT
file$ = 48
?pipe_close@@YAHPEAU_vfs_node_@@@Z PROC			; pipe_close

; 74   : int pipe_close (vfs_node_t *file) {

$LN4:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 75   : 	if (file->device)

	mov	rax, QWORD PTR file$[rsp]
	cmp	QWORD PTR [rax+56], 0
	je	SHORT $LN1@pipe_close

; 76   : 		free(file->device);

	mov	rax, QWORD PTR file$[rsp]
	mov	rcx, QWORD PTR [rax+56]
	call	free
$LN1@pipe_close:

; 77   : 
; 78   : 	free(file);

	mov	rcx, QWORD PTR file$[rsp]
	call	free

; 79   : 	return 0;

	xor	eax, eax

; 80   : }

	add	rsp, 40					; 00000028H
	ret	0
?pipe_close@@YAHPEAU_vfs_node_@@@Z ENDP			; pipe_close
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\pipe.cpp
_TEXT	SEGMENT
i$1 = 32
p$ = 40
file$ = 64
buffer$ = 72
length$ = 80
?pipe_write@@YAXPEAU_vfs_node_@@PEA_KI@Z PROC		; pipe_write

; 63   : void pipe_write (vfs_node_t *file, uint64_t* buffer, uint32_t length) {

$LN6:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 64   : 	pipe_t *p = (pipe_t*)file->device;

	mov	rax, QWORD PTR file$[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR p$[rsp], rax

; 65   : 	for (int i = 0; i < length; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@pipe_write
$LN2@pipe_write:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@pipe_write:
	mov	eax, DWORD PTR length$[rsp]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN1@pipe_write

; 66   : 		circular_buf_put(p->buf, buffer[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR buffer$[rsp]
	movzx	edx, BYTE PTR [rcx+rax*8]
	mov	rax, QWORD PTR p$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_put@@YAXPEAU_circ_buf_@@E@Z ; circular_buf_put

; 67   : 	}

	jmp	SHORT $LN2@pipe_write
$LN1@pipe_write:

; 68   : }

	add	rsp, 56					; 00000038H
	ret	0
?pipe_write@@YAXPEAU_vfs_node_@@PEA_KI@Z ENDP		; pipe_write
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\pipe.cpp
_TEXT	SEGMENT
i$1 = 32
p$ = 40
file$ = 64
buffer$ = 72
length$ = 80
?pipe_read@@YA_KPEAU_vfs_node_@@PEA_KI@Z PROC		; pipe_read

; 54   : size_t pipe_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {

$LN6:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 55   : 	pipe_t *p = (pipe_t*)file->device;

	mov	rax, QWORD PTR file$[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR p$[rsp], rax

; 56   : 	for (int i = 0; i < length; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@pipe_read
$LN2@pipe_read:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@pipe_read:
	mov	eax, DWORD PTR length$[rsp]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN1@pipe_read

; 57   : 		circular_buf_get (p->buf,(uint8_t*)&buffer[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR buffer$[rsp]
	lea	rax, QWORD PTR [rcx+rax*8]
	mov	rdx, rax
	mov	rax, QWORD PTR p$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z ; circular_buf_get
	jmp	SHORT $LN2@pipe_read
$LN1@pipe_read:

; 58   : 
; 59   : 	return 1;

	mov	eax, 1

; 60   : }

	add	rsp, 56					; 00000038H
	ret	0
?pipe_read@@YA_KPEAU_vfs_node_@@PEA_KI@Z ENDP		; pipe_read
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\pipe.cpp
_TEXT	SEGMENT
readn$ = 32
writen$ = 40
t$ = 48
p$ = 56
fd$ = 80
?AuAllocAnonPipe@@YAXQEAH@Z PROC			; AuAllocAnonPipe

; 89   : void AuAllocAnonPipe (int fd[2]) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 90   : 
; 91   : 	pipe_t *p = AuCreatePipe();

	call	?AuCreatePipe@@YAPEAU_pipe_@@XZ		; AuCreatePipe
	mov	QWORD PTR p$[rsp], rax

; 92   : 	
; 93   : 	vfs_node_t *readn = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 112				; 00000070H
	call	malloc
	mov	QWORD PTR readn$[rsp], rax

; 94   : 	strcpy(readn->filename, "AuPipe");

	mov	rax, QWORD PTR readn$[rsp]
	lea	rdx, OFFSET FLAT:$SG3606
	mov	rcx, rax
	call	strcpy

; 95   : 	readn->size = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	DWORD PTR [rax+32], 0

; 96   : 	readn->eof = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	BYTE PTR [rax+36], 0

; 97   : 	readn->pos = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	DWORD PTR [rax+40], 0

; 98   : 	readn->current = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	DWORD PTR [rax+44], 0

; 99   : 	readn->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;

	mov	rax, QWORD PTR readn$[rsp]
	mov	BYTE PTR [rax+48], 12

; 100  : 	readn->status = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	BYTE PTR [rax+49], 0

; 101  : 	readn->open = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	QWORD PTR [rax+64], 0

; 102  : 	readn->device = p;

	mov	rax, QWORD PTR readn$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	mov	QWORD PTR [rax+56], rcx

; 103  : 	readn->read = pipe_read;

	mov	rax, QWORD PTR readn$[rsp]
	lea	rcx, OFFSET FLAT:?pipe_read@@YA_KPEAU_vfs_node_@@PEA_KI@Z ; pipe_read
	mov	QWORD PTR [rax+72], rcx

; 104  : 	readn->write = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	QWORD PTR [rax+80], 0

; 105  : 	readn->read_blk = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	QWORD PTR [rax+96], 0

; 106  : 	readn->ioquery = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	QWORD PTR [rax+104], 0

; 107  : 	readn->close = pipe_close;

	mov	rax, QWORD PTR readn$[rsp]
	lea	rcx, OFFSET FLAT:?pipe_close@@YAHPEAU_vfs_node_@@@Z ; pipe_close
	mov	QWORD PTR [rax+88], rcx

; 108  : 
; 109  : 	vfs_node_t *writen = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 112				; 00000070H
	call	malloc
	mov	QWORD PTR writen$[rsp], rax

; 110  : 	strcpy(writen->filename, "AuPipe");

	mov	rax, QWORD PTR writen$[rsp]
	lea	rdx, OFFSET FLAT:$SG3610
	mov	rcx, rax
	call	strcpy

; 111  : 	writen->size = 0;

	mov	rax, QWORD PTR writen$[rsp]
	mov	DWORD PTR [rax+32], 0

; 112  : 	writen->eof = 0;

	mov	rax, QWORD PTR writen$[rsp]
	mov	BYTE PTR [rax+36], 0

; 113  : 	writen->pos = 0;

	mov	rax, QWORD PTR writen$[rsp]
	mov	DWORD PTR [rax+40], 0

; 114  : 	writen->current = 0;

	mov	rax, QWORD PTR writen$[rsp]
	mov	DWORD PTR [rax+44], 0

; 115  : 	writen->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;

	mov	rax, QWORD PTR writen$[rsp]
	mov	BYTE PTR [rax+48], 12

; 116  : 	writen->status = 0;

	mov	rax, QWORD PTR writen$[rsp]
	mov	BYTE PTR [rax+49], 0

; 117  : 	writen->open = 0;

	mov	rax, QWORD PTR writen$[rsp]
	mov	QWORD PTR [rax+64], 0

; 118  : 	writen->device = p;

	mov	rax, QWORD PTR writen$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	mov	QWORD PTR [rax+56], rcx

; 119  : 	writen->write = pipe_write;

	mov	rax, QWORD PTR writen$[rsp]
	lea	rcx, OFFSET FLAT:?pipe_write@@YAXPEAU_vfs_node_@@PEA_KI@Z ; pipe_write
	mov	QWORD PTR [rax+80], rcx

; 120  : 	writen->read = 0;

	mov	rax, QWORD PTR writen$[rsp]
	mov	QWORD PTR [rax+72], 0

; 121  : 	writen->read_blk = 0;

	mov	rax, QWORD PTR writen$[rsp]
	mov	QWORD PTR [rax+96], 0

; 122  : 	writen->ioquery = 0;

	mov	rax, QWORD PTR writen$[rsp]
	mov	QWORD PTR [rax+104], 0

; 123  : 	writen->close = pipe_close;

	mov	rax, QWORD PTR writen$[rsp]
	lea	rcx, OFFSET FLAT:?pipe_close@@YAHPEAU_vfs_node_@@@Z ; pipe_close
	mov	QWORD PTR [rax+88], rcx

; 124  : 	
; 125  : 	/* Read End */
; 126  : 	thread_t * t = get_current_thread();

	call	get_current_thread
	mov	QWORD PTR t$[rsp], rax

; 127  : 	t->fd[t->fd_current] = readn;

	mov	rax, QWORD PTR t$[rsp]
	movsxd	rax, DWORD PTR [rax+744]
	mov	rcx, QWORD PTR t$[rsp]
	mov	rdx, QWORD PTR readn$[rsp]
	mov	QWORD PTR [rcx+rax*8+264], rdx

; 128  : 	fd[0] = t->fd_current;

	mov	eax, 4
	imul	rax, 0
	mov	rcx, QWORD PTR fd$[rsp]
	mov	rdx, QWORD PTR t$[rsp]
	mov	edx, DWORD PTR [rdx+744]
	mov	DWORD PTR [rcx+rax], edx

; 129  : 	t->fd_current++;

	mov	rax, QWORD PTR t$[rsp]
	mov	eax, DWORD PTR [rax+744]
	inc	eax
	mov	rcx, QWORD PTR t$[rsp]
	mov	DWORD PTR [rcx+744], eax

; 130  : 
; 131  : 	/* Write End */
; 132  : 	t->fd[t->fd_current] = writen;

	mov	rax, QWORD PTR t$[rsp]
	movsxd	rax, DWORD PTR [rax+744]
	mov	rcx, QWORD PTR t$[rsp]
	mov	rdx, QWORD PTR writen$[rsp]
	mov	QWORD PTR [rcx+rax*8+264], rdx

; 133  : 	fd[1] = t->fd_current;

	mov	eax, 4
	imul	rax, 1
	mov	rcx, QWORD PTR fd$[rsp]
	mov	rdx, QWORD PTR t$[rsp]
	mov	edx, DWORD PTR [rdx+744]
	mov	DWORD PTR [rcx+rax], edx

; 134  : 	t->fd_current++;

	mov	rax, QWORD PTR t$[rsp]
	mov	eax, DWORD PTR [rax+744]
	inc	eax
	mov	rcx, QWORD PTR t$[rsp]
	mov	DWORD PTR [rcx+744], eax

; 135  : 	
; 136  : }

	add	rsp, 72					; 00000048H
	ret	0
?AuAllocAnonPipe@@YAXQEAH@Z ENDP			; AuAllocAnonPipe
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\pipe.cpp
_TEXT	SEGMENT
pipe$ = 32
p$ = 40
circ$ = 48
?AuCreatePipe@@YAPEAU_pipe_@@XZ PROC			; AuCreatePipe

; 43   : pipe_t* AuCreatePipe () {

$LN3:
	sub	rsp, 72					; 00000048H

; 44   : 	unsigned char *p = (unsigned char*)malloc(MAX_PIPE_BUFFER_SZ);  //Main Buffer

	mov	ecx, 1024				; 00000400H
	call	malloc
	mov	QWORD PTR p$[rsp], rax

; 45   : 	circ_buf_t *circ = circ_buf_init((unsigned char*)p,MAX_PIPE_BUFFER_SZ);

	mov	edx, 1024				; 00000400H
	mov	rcx, QWORD PTR p$[rsp]
	call	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z ; circ_buf_init
	mov	QWORD PTR circ$[rsp], rax

; 46   : 	pipe_t *pipe = (pipe_t*)malloc(sizeof(pipe_t));

	mov	ecx, 16
	call	malloc
	mov	QWORD PTR pipe$[rsp], rax

; 47   : 	pipe->buf = circ;

	mov	rax, QWORD PTR pipe$[rsp]
	mov	rcx, QWORD PTR circ$[rsp]
	mov	QWORD PTR [rax], rcx

; 48   : 	pipe->readers = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR pipe$[rsp]
	mov	WORD PTR [rcx+8], ax

; 49   : 	pipe->writers = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR pipe$[rsp]
	mov	WORD PTR [rcx+10], ax

; 50   : 	return pipe;

	mov	rax, QWORD PTR pipe$[rsp]

; 51   : }

	add	rsp, 72					; 00000048H
	ret	0
?AuCreatePipe@@YAPEAU_pipe_@@XZ ENDP			; AuCreatePipe
_TEXT	ENDS
END
