; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?pipe_count@@3HA				; pipe_count
_BSS	SEGMENT
?pipe_count@@3HA DD 01H DUP (?)				; pipe_count
_BSS	ENDS
CONST	SEGMENT
$SG3305	DB	'pipe', 00H
	ORG $+3
$SG3307	DB	'/dev/', 00H
CONST	ENDS
PUBLIC	?pipe_create@@YAPEAU_pipe_@@XZ			; pipe_create
PUBLIC	?allocate_pipe@@YAXPEAHPEAD@Z			; allocate_pipe
PUBLIC	?pipe_write@@YAXPEAU_vfs_node_@@PEAEI@Z		; pipe_write
PUBLIC	?pipe_read@@YAXPEAU_vfs_node_@@PEA_KI@Z		; pipe_read
EXTRN	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z:PROC	; circ_buf_init
EXTRN	?circular_buf_put@@YAXPEAU_circ_buf_@@H@Z:PROC	; circular_buf_put
EXTRN	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z:PROC ; circular_buf_get
EXTRN	?strcpy@@YAPEADPEADPEBD@Z:PROC			; strcpy
EXTRN	?strlen@@YA_KPEBD@Z:PROC			; strlen
EXTRN	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z:PROC	; vfs_mount
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?sztoa@@YAPEAD_KPEADH@Z:PROC			; sztoa
EXTRN	?malloc@@YAPEAX_K@Z:PROC			; malloc
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
pdata	SEGMENT
$pdata$?pipe_create@@YAPEAU_pipe_@@XZ DD imagerel $LN3
	DD	imagerel $LN3+91
	DD	imagerel $unwind$?pipe_create@@YAPEAU_pipe_@@XZ
$pdata$?allocate_pipe@@YAXPEAHPEAD@Z DD imagerel $LN5
	DD	imagerel $LN5+471
	DD	imagerel $unwind$?allocate_pipe@@YAXPEAHPEAD@Z
$pdata$?pipe_write@@YAXPEAU_vfs_node_@@PEAEI@Z DD imagerel $LN6
	DD	imagerel $LN6+99
	DD	imagerel $unwind$?pipe_write@@YAXPEAU_vfs_node_@@PEAEI@Z
$pdata$?pipe_read@@YAXPEAU_vfs_node_@@PEA_KI@Z DD imagerel $LN6
	DD	imagerel $LN6+100
	DD	imagerel $unwind$?pipe_read@@YAXPEAU_vfs_node_@@PEA_KI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?pipe_create@@YAPEAU_pipe_@@XZ DD 010401H
	DD	08204H
$unwind$?allocate_pipe@@YAXPEAHPEAD@Z DD 010e01H
	DD	0c20eH
$unwind$?pipe_write@@YAXPEAU_vfs_node_@@PEAEI@Z DD 011301H
	DD	06213H
$unwind$?pipe_read@@YAXPEAU_vfs_node_@@PEA_KI@Z DD 011301H
	DD	06213H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\pipe.cpp
_TEXT	SEGMENT
i$1 = 32
p$ = 40
file$ = 64
buffer$ = 72
length$ = 80
?pipe_read@@YAXPEAU_vfs_node_@@PEA_KI@Z PROC		; pipe_read

; 30   : void pipe_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {

$LN6:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 31   : 	pipe_t *p = (pipe_t*)file->device;

	mov	rax, QWORD PTR file$[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR p$[rsp], rax

; 32   : 	for (int i = 0; i < length; i++)

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

; 33   : 		circular_buf_get (p->buf,(uint8_t*)&buffer[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR buffer$[rsp]
	lea	rax, QWORD PTR [rcx+rax*8]
	mov	rdx, rax
	mov	rax, QWORD PTR p$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_get@@YAHPEAU_circ_buf_@@PEAE@Z ; circular_buf_get
	jmp	SHORT $LN2@pipe_read
$LN1@pipe_read:

; 34   : }

	add	rsp, 56					; 00000038H
	ret	0
?pipe_read@@YAXPEAU_vfs_node_@@PEA_KI@Z ENDP		; pipe_read
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\pipe.cpp
_TEXT	SEGMENT
i$1 = 32
p$ = 40
file$ = 64
buffer$ = 72
length$ = 80
?pipe_write@@YAXPEAU_vfs_node_@@PEAEI@Z PROC		; pipe_write

; 37   : void pipe_write (vfs_node_t *file, uint8_t* buffer, uint32_t length) {

$LN6:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 38   : 	pipe_t *p = (pipe_t*)file->device;

	mov	rax, QWORD PTR file$[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR p$[rsp], rax

; 39   : 	for (int i = 0; i < length; i++) {

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

; 40   : 		circular_buf_put(p->buf, buffer[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR buffer$[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	mov	edx, eax
	mov	rax, QWORD PTR p$[rsp]
	mov	rcx, QWORD PTR [rax]
	call	?circular_buf_put@@YAXPEAU_circ_buf_@@H@Z ; circular_buf_put

; 41   : 	}

	jmp	SHORT $LN2@pipe_write
$LN1@pipe_write:

; 42   : }

	add	rsp, 56					; 00000038H
	ret	0
?pipe_write@@YAXPEAU_vfs_node_@@PEAEI@Z ENDP		; pipe_write
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\pipe.cpp
_TEXT	SEGMENT
p_value$ = 32
readn$ = 40
t$ = 48
p$ = 56
pipe_name$ = 64
path_name$ = 80
fd$ = 112
name$ = 120
?allocate_pipe@@YAXPEAHPEAD@Z PROC			; allocate_pipe

; 46   : void allocate_pipe (int *fd, char* name) {

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 47   : 
; 48   : 	///!=========================================
; 49   : 	///!  Allocate new node for read
; 50   : 	///!=========================================
; 51   : 	pipe_t *p = pipe_create();

	call	?pipe_create@@YAPEAU_pipe_@@XZ		; pipe_create
	mov	QWORD PTR p$[rsp], rax

; 52   : 	char p_value[2];
; 53   : 	sztoa(pipe_count, p_value,10);

	movsxd	rax, DWORD PTR ?pipe_count@@3HA		; pipe_count
	mov	r8d, 10
	lea	rdx, QWORD PTR p_value$[rsp]
	mov	rcx, rax
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 54   : 
; 55   : 	char pipe_name[10];
; 56   : 	if (name)

	cmp	QWORD PTR name$[rsp], 0
	je	SHORT $LN2@allocate_p

; 57   : 		strcpy(pipe_name, name);

	mov	rdx, QWORD PTR name$[rsp]
	lea	rcx, QWORD PTR pipe_name$[rsp]
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 58   : 	else {

	jmp	SHORT $LN1@allocate_p
$LN2@allocate_p:

; 59   : 		strcpy(pipe_name, "pipe");

	lea	rdx, OFFSET FLAT:$SG3305
	lea	rcx, QWORD PTR pipe_name$[rsp]
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 60   : 		strcpy (pipe_name + strlen(pipe_name)-1, p_value);

	lea	rcx, QWORD PTR pipe_name$[rsp]
	call	?strlen@@YA_KPEBD@Z			; strlen
	lea	rax, QWORD PTR pipe_name$[rsp+rax-1]
	lea	rdx, QWORD PTR p_value$[rsp]
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy
$LN1@allocate_p:

; 61   : 	}
; 62   : 	
; 63   : 
; 64   : 	char path_name[10];
; 65   : 	strcpy(path_name, "/dev/");

	lea	rdx, OFFSET FLAT:$SG3307
	lea	rcx, QWORD PTR path_name$[rsp]
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 66   : 	strcpy (path_name + strlen(path_name)-1, pipe_name);

	lea	rcx, QWORD PTR path_name$[rsp]
	call	?strlen@@YA_KPEBD@Z			; strlen
	lea	rax, QWORD PTR path_name$[rsp+rax-1]
	lea	rdx, QWORD PTR pipe_name$[rsp]
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 67   : 
; 68   : 	
; 69   : 	vfs_node_t *readn = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 104				; 00000068H
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	QWORD PTR readn$[rsp], rax

; 70   : 	strcpy(readn->filename, pipe_name);

	mov	rax, QWORD PTR readn$[rsp]
	lea	rdx, QWORD PTR pipe_name$[rsp]
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 71   : 	readn->size = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	DWORD PTR [rax+32], 0

; 72   : 	readn->eof = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	DWORD PTR [rax+36], 0

; 73   : 	readn->pos = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	DWORD PTR [rax+40], 0

; 74   : 	readn->current = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	DWORD PTR [rax+44], 0

; 75   : 	readn->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR readn$[rsp]
	mov	DWORD PTR [rax+48], 2

; 76   : 	readn->status = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	DWORD PTR [rax+52], 0

; 77   : 	readn->open = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	QWORD PTR [rax+64], 0

; 78   : 	readn->device = p;

	mov	rax, QWORD PTR readn$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	mov	QWORD PTR [rax+56], rcx

; 79   : 	readn->read = pipe_read;

	mov	rax, QWORD PTR readn$[rsp]
	lea	rcx, OFFSET FLAT:?pipe_read@@YAXPEAU_vfs_node_@@PEA_KI@Z ; pipe_read
	mov	QWORD PTR [rax+72], rcx

; 80   : 	readn->write = pipe_write;

	mov	rax, QWORD PTR readn$[rsp]
	lea	rcx, OFFSET FLAT:?pipe_write@@YAXPEAU_vfs_node_@@PEAEI@Z ; pipe_write
	mov	QWORD PTR [rax+80], rcx

; 81   : 	readn->read_blk = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	QWORD PTR [rax+88], 0

; 82   : 	readn->ioquery = 0;

	mov	rax, QWORD PTR readn$[rsp]
	mov	QWORD PTR [rax+96], 0

; 83   : 	vfs_mount (path_name, readn);

	mov	rdx, QWORD PTR readn$[rsp]
	lea	rcx, QWORD PTR path_name$[rsp]
	call	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z	; vfs_mount

; 84   : 
; 85   : 	thread_t * t = get_current_thread();

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	QWORD PTR t$[rsp], rax

; 86   : 	t->fd[t->fd_current] = readn;

	mov	rax, QWORD PTR t$[rsp]
	movsxd	rax, DWORD PTR [rax+752]
	mov	rcx, QWORD PTR t$[rsp]
	mov	rdx, QWORD PTR readn$[rsp]
	mov	QWORD PTR [rcx+rax*8+272], rdx

; 87   : 	*fd = t->fd_current;

	mov	rax, QWORD PTR fd$[rsp]
	mov	rcx, QWORD PTR t$[rsp]
	mov	ecx, DWORD PTR [rcx+752]
	mov	DWORD PTR [rax], ecx

; 88   : 	t->fd_current++;

	mov	rax, QWORD PTR t$[rsp]
	mov	eax, DWORD PTR [rax+752]
	inc	eax
	mov	rcx, QWORD PTR t$[rsp]
	mov	DWORD PTR [rcx+752], eax

; 89   : 	
; 90   : 	pipe_count++;

	mov	eax, DWORD PTR ?pipe_count@@3HA		; pipe_count
	inc	eax
	mov	DWORD PTR ?pipe_count@@3HA, eax		; pipe_count

; 91   : }

	add	rsp, 104				; 00000068H
	ret	0
?allocate_pipe@@YAXPEAHPEAD@Z ENDP			; allocate_pipe
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\pipe.cpp
_TEXT	SEGMENT
pipe$ = 32
p$ = 40
circ$ = 48
?pipe_create@@YAPEAU_pipe_@@XZ PROC			; pipe_create

; 19   : pipe_t* pipe_create () {

$LN3:
	sub	rsp, 72					; 00000048H

; 20   : 	unsigned char *p = (unsigned char*)pmmngr_alloc();  //Main Buffer

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR p$[rsp], rax

; 21   : 	circ_buf_t *circ = circ_buf_init((unsigned char*)p,4096);

	mov	edx, 4096				; 00001000H
	mov	rcx, QWORD PTR p$[rsp]
	call	?circ_buf_init@@YAPEAU_circ_buf_@@PEAE_K@Z ; circ_buf_init
	mov	QWORD PTR circ$[rsp], rax

; 22   : 	pipe_t *pipe = (pipe_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR pipe$[rsp], rax

; 23   : 	pipe->buf = circ;

	mov	rax, QWORD PTR pipe$[rsp]
	mov	rcx, QWORD PTR circ$[rsp]
	mov	QWORD PTR [rax], rcx

; 24   : 	pipe->readers = 0;

	mov	rax, QWORD PTR pipe$[rsp]
	mov	DWORD PTR [rax+8], 0

; 25   : 	pipe->writers = 0;

	mov	rax, QWORD PTR pipe$[rsp]
	mov	DWORD PTR [rax+12], 0

; 26   : 	return pipe;

	mov	rax, QWORD PTR pipe$[rsp]

; 27   : }

	add	rsp, 72					; 00000048H
	ret	0
?pipe_create@@YAPEAU_pipe_@@XZ ENDP			; pipe_create
_TEXT	ENDS
END
