; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3620	DB	'dev', 00H
CONST	ENDS
PUBLIC	?sys_open_file@@YAHPEADPEAU_file_@@@Z		; sys_open_file
PUBLIC	?sys_read_file@@YAXHPEAEPEAU_file_@@@Z		; sys_read_file
PUBLIC	?sys_write_file@@YAXHPEAEPEAU_file_@@@Z		; sys_write_file
EXTRN	?strcmp@@YAHPEBD0@Z:PROC			; strcmp
EXTRN	?strchr@@YAPEADPEADH@Z:PROC			; strchr
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	memcpy:PROC
EXTRN	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z:PROC	; vfs_finddir
EXTRN	?openfs@@YA?AU_vfs_node_@@PEAU1@PEAD@Z:PROC	; openfs
EXTRN	?readfs@@YAXPEAU_vfs_node_@@0PEA_KI@Z:PROC	; readfs
EXTRN	?writefs@@YAXPEAU_vfs_node_@@0PEAEI@Z:PROC	; writefs
EXTRN	?readfs_block@@YAXPEAU_vfs_node_@@0PEA_K@Z:PROC	; readfs_block
EXTRN	x64_cli:PROC
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?pmmngr_free@@YAXPEAX@Z:PROC			; pmmngr_free
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
pdata	SEGMENT
$pdata$?sys_open_file@@YAHPEADPEAU_file_@@@Z DD imagerel $LN17
	DD	imagerel $LN17+632
	DD	imagerel $unwind$?sys_open_file@@YAHPEADPEAU_file_@@@Z
$pdata$?sys_read_file@@YAXHPEAEPEAU_file_@@@Z DD imagerel $LN10
	DD	imagerel $LN10+420
	DD	imagerel $unwind$?sys_read_file@@YAXHPEAEPEAU_file_@@@Z
$pdata$?sys_write_file@@YAXHPEAEPEAU_file_@@@Z DD imagerel $LN6
	DD	imagerel $LN6+286
	DD	imagerel $unwind$?sys_write_file@@YAXHPEAEPEAU_file_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?sys_open_file@@YAHPEADPEAU_file_@@@Z DD 041301H
	DD	0370113H
	DD	0600b700cH
$unwind$?sys_read_file@@YAXHPEAEPEAU_file_@@@Z DD 021501H
	DD	0170115H
$unwind$?sys_write_file@@YAXHPEAEPEAU_file_@@@Z DD 021501H
	DD	0150115H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
node$ = 32
file$ = 48
fd$ = 176
buffer$ = 184
ufile$ = 192
?sys_write_file@@YAXHPEAEPEAU_file_@@@Z PROC		; sys_write_file

; 152  : void sys_write_file (int fd, unsigned char* buffer, FILE *ufile) {

$LN6:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 168				; 000000a8H

; 153  : 	x64_cli();

	call	x64_cli

; 154  : 	vfs_node_t file;
; 155  : 	file.size = ufile->size;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+4]
	mov	DWORD PTR file$[rsp+32], eax

; 156  : 	file.eof = ufile->eof;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+8]
	mov	DWORD PTR file$[rsp+36], eax

; 157  : 	file.pos = ufile->pos;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+12]
	mov	DWORD PTR file$[rsp+40], eax

; 158  : 	file.current = ufile->start_cluster;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+16]
	mov	DWORD PTR file$[rsp+44], eax

; 159  : 	file.flags = ufile->flags;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+20]
	mov	DWORD PTR file$[rsp+48], eax

; 160  : 	file.status = ufile->status;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+24]
	mov	DWORD PTR file$[rsp+52], eax

; 161  : 	file.open = 0;

	mov	QWORD PTR file$[rsp+64], 0

; 162  : 	file.read = 0;

	mov	QWORD PTR file$[rsp+72], 0

; 163  : 	file.read_blk = 0;

	mov	QWORD PTR file$[rsp+88], 0

; 164  : 	file.write = 0;

	mov	QWORD PTR file$[rsp+80], 0

; 165  : 	file.ioquery  = 0;

	mov	QWORD PTR file$[rsp+96], 0

; 166  : 
; 167  : 	vfs_node_t *node = get_current_thread()->fd[fd];

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movsxd	rcx, DWORD PTR fd$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+272]
	mov	QWORD PTR node$[rsp], rax

; 168  : 	if (node == NULL) {

	cmp	QWORD PTR node$[rsp], 0
	jne	SHORT $LN3@sys_write_

; 169  : 		return;

	jmp	SHORT $LN4@sys_write_
$LN3@sys_write_:

; 170  : 	}
; 171  : 
; 172  : 	if (ufile->flags) {

	mov	rax, QWORD PTR ufile$[rsp]
	cmp	DWORD PTR [rax+20], 0
	je	SHORT $LN2@sys_write_

; 173  : 		writefs(node, &file,buffer,file.size);

	mov	r9d, DWORD PTR file$[rsp+32]
	mov	r8, QWORD PTR buffer$[rsp]
	lea	rdx, QWORD PTR file$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	?writefs@@YAXPEAU_vfs_node_@@0PEAEI@Z	; writefs

; 174  : 	}else {

	jmp	SHORT $LN1@sys_write_
$LN2@sys_write_:

; 175  : 		writefs(node, node, buffer,file.size);

	mov	r9d, DWORD PTR file$[rsp+32]
	mov	r8, QWORD PTR buffer$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	?writefs@@YAXPEAU_vfs_node_@@0PEAEI@Z	; writefs
$LN1@sys_write_:
$LN4@sys_write_:

; 176  : 	}
; 177  : }

	add	rsp, 168				; 000000a8H
	ret	0
?sys_write_file@@YAXHPEAEPEAU_file_@@@Z ENDP		; sys_write_file
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
i$1 = 32
buff$2 = 40
node$ = 48
file$ = 64
fd$ = 192
buffer$ = 200
ufile$ = 208
?sys_read_file@@YAXHPEAEPEAU_file_@@@Z PROC		; sys_read_file

; 107  : void sys_read_file (int fd, uint8_t* buffer, FILE *ufile) {

$LN10:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 184				; 000000b8H

; 108  : 	x64_cli ();

	call	x64_cli

; 109  : 	vfs_node_t file;
; 110  : 	file.size = ufile->size;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+4]
	mov	DWORD PTR file$[rsp+32], eax

; 111  : 	file.eof = ufile->eof;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+8]
	mov	DWORD PTR file$[rsp+36], eax

; 112  : 	file.pos = ufile->pos;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+12]
	mov	DWORD PTR file$[rsp+40], eax

; 113  : 	file.current = ufile->start_cluster;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+16]
	mov	DWORD PTR file$[rsp+44], eax

; 114  : 	file.flags = ufile->flags;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+20]
	mov	DWORD PTR file$[rsp+48], eax

; 115  : 	file.status = ufile->status;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+24]
	mov	DWORD PTR file$[rsp+52], eax

; 116  : 	file.open = 0;

	mov	QWORD PTR file$[rsp+64], 0

; 117  : 	file.read = 0;

	mov	QWORD PTR file$[rsp+72], 0

; 118  : 	file.read_blk = 0;

	mov	QWORD PTR file$[rsp+88], 0

; 119  : 	file.write = 0;

	mov	QWORD PTR file$[rsp+80], 0

; 120  : 	file.ioquery  = 0;

	mov	QWORD PTR file$[rsp+96], 0

; 121  : 
; 122  : 	vfs_node_t *node = get_current_thread()->fd[fd];

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movsxd	rcx, DWORD PTR fd$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+272]
	mov	QWORD PTR node$[rsp], rax

; 123  : 	if (node == NULL)

	cmp	QWORD PTR node$[rsp], 0
	jne	SHORT $LN7@sys_read_f

; 124  : 		return;

	jmp	$LN8@sys_read_f
$LN7@sys_read_f:

; 125  : 
; 126  : 	if (ufile->flags > 0){

	mov	rax, QWORD PTR ufile$[rsp]
	cmp	DWORD PTR [rax+20], 0
	jbe	$LN6@sys_read_f

; 127  : 		for (int i = 0; i < file.size; i += 8) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN5@sys_read_f
$LN4@sys_read_f:
	mov	eax, DWORD PTR i$1[rsp]
	add	eax, 8
	mov	DWORD PTR i$1[rsp], eax
$LN5@sys_read_f:
	mov	eax, DWORD PTR file$[rsp+32]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN3@sys_read_f

; 128  : 			if (file.eof) 

	cmp	DWORD PTR file$[rsp+36], 0
	je	SHORT $LN2@sys_read_f

; 129  : 				break;

	jmp	SHORT $LN3@sys_read_f
$LN2@sys_read_f:

; 130  : 			uint64_t* buff = (uint64_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR buff$2[rsp], rax

; 131  : 			memset(buff, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR buff$2[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 132  : 			readfs_block (node,&file,buff);

	mov	r8, QWORD PTR buff$2[rsp]
	lea	rdx, QWORD PTR file$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	?readfs_block@@YAXPEAU_vfs_node_@@0PEA_K@Z ; readfs_block

; 133  : 			memcpy (buffer,buff,4096);

	mov	r8d, 4096				; 00001000H
	mov	rdx, QWORD PTR buff$2[rsp]
	mov	rcx, QWORD PTR buffer$[rsp]
	call	memcpy

; 134  : 			buffer += 4096;

	mov	rax, QWORD PTR buffer$[rsp]
	add	rax, 4096				; 00001000H
	mov	QWORD PTR buffer$[rsp], rax

; 135  : 			pmmngr_free(buff);

	mov	rcx, QWORD PTR buff$2[rsp]
	call	?pmmngr_free@@YAXPEAX@Z			; pmmngr_free

; 136  : 			
; 137  : 		}

	jmp	$LN4@sys_read_f
$LN3@sys_read_f:
	jmp	SHORT $LN1@sys_read_f
$LN6@sys_read_f:

; 138  : 
; 139  : 	}else {
; 140  : 		readfs(node, node, (uint64_t*)buffer, file.size);

	mov	r9d, DWORD PTR file$[rsp+32]
	mov	r8, QWORD PTR buffer$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	?readfs@@YAXPEAU_vfs_node_@@0PEA_KI@Z	; readfs
$LN1@sys_read_f:
$LN8@sys_read_f:

; 141  : 	}
; 142  : 
; 143  : }

	add	rsp, 184				; 000000b8H
	ret	0
?sys_read_file@@YAXHPEAEPEAU_file_@@@Z ENDP		; sys_read_file
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
fd_found$ = 32
i$ = 36
i$1 = 40
fd$ = 44
p$ = 48
node$ = 56
tv146 = 64
_node$2 = 72
tv135 = 80
pathname$ = 88
file$3 = 112
$T4 = 224
$T5 = 328
filename$ = 464
ufile$ = 472
?sys_open_file@@YAHPEADPEAU_file_@@@Z PROC		; sys_open_file

; 48   : int sys_open_file (char* filename, FILE *ufile) {

$LN17:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 440				; 000001b8H

; 49   : 	x64_cli();

	call	x64_cli

; 50   : 	char* p = strchr (filename, '/');

	mov	edx, 47					; 0000002fH
	mov	rcx, QWORD PTR filename$[rsp]
	call	?strchr@@YAPEADPEADH@Z			; strchr
	mov	QWORD PTR p$[rsp], rax

; 51   : 	if (p)

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN14@sys_open_f

; 52   : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax
$LN14@sys_open_f:

; 53   : 
; 54   : 
; 55   : 	char pathname[16];
; 56   : 	int i;
; 57   : 	for (i = 0; i < 16; i++) {

	mov	DWORD PTR i$[rsp], 0
	jmp	SHORT $LN13@sys_open_f
$LN12@sys_open_f:
	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
$LN13@sys_open_f:
	cmp	DWORD PTR i$[rsp], 16
	jge	SHORT $LN11@sys_open_f

; 58   : 		if ( p[i] == '/'  || p[i] == '\0')

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	je	SHORT $LN9@sys_open_f
	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	jne	SHORT $LN10@sys_open_f
$LN9@sys_open_f:

; 59   : 			break;

	jmp	SHORT $LN11@sys_open_f
$LN10@sys_open_f:

; 60   : 		pathname[i] = p[i];

	movsxd	rax, DWORD PTR i$[rsp]
	movsxd	rcx, DWORD PTR i$[rsp]
	mov	rdx, QWORD PTR p$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR pathname$[rsp+rcx], al

; 61   : 	}

	jmp	SHORT $LN12@sys_open_f
$LN11@sys_open_f:

; 62   : 
; 63   : 	pathname[i] = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	BYTE PTR pathname$[rsp+rax], 0

; 64   : 
; 65   :     int fd = 0;

	mov	DWORD PTR fd$[rsp], 0

; 66   : 	vfs_node_t *node = vfs_finddir(filename);

	mov	rcx, QWORD PTR filename$[rsp]
	call	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z	; vfs_finddir
	mov	QWORD PTR node$[rsp], rax

; 67   : 	bool fd_found = false;

	mov	BYTE PTR fd_found$[rsp], 0

; 68   : 	if (node) {

	cmp	QWORD PTR node$[rsp], 0
	je	$LN8@sys_open_f

; 69   : 		for (int i = 0; i < 60; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN7@sys_open_f
$LN6@sys_open_f:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN7@sys_open_f:
	cmp	DWORD PTR i$1[rsp], 60			; 0000003cH
	jge	SHORT $LN5@sys_open_f

; 70   : 			vfs_node_t *_node = get_current_thread()->fd[i];

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+272]
	mov	QWORD PTR _node$2[rsp], rax

; 71   : 			if (_node == node) {

	mov	rax, QWORD PTR node$[rsp]
	cmp	QWORD PTR _node$2[rsp], rax
	jne	SHORT $LN4@sys_open_f

; 72   : 				fd = i;

	mov	eax, DWORD PTR i$1[rsp]
	mov	DWORD PTR fd$[rsp], eax

; 73   : 				fd_found = true;

	mov	BYTE PTR fd_found$[rsp], 1

; 74   : 				break;

	jmp	SHORT $LN5@sys_open_f
$LN4@sys_open_f:

; 75   : 			}
; 76   : 		}

	jmp	SHORT $LN6@sys_open_f
$LN5@sys_open_f:

; 77   : 		if (!fd_found){

	movzx	eax, BYTE PTR fd_found$[rsp]
	test	eax, eax
	jne	SHORT $LN3@sys_open_f

; 78   : 			get_current_thread()->fd[get_current_thread()->fd_current] = node;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	QWORD PTR tv135[rsp], rax
	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movsxd	rax, DWORD PTR [rax+752]
	mov	rcx, QWORD PTR node$[rsp]
	mov	rdx, QWORD PTR tv135[rsp]
	mov	QWORD PTR [rdx+rax*8+272], rcx

; 79   : 			fd = get_current_thread()->fd_current;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	eax, DWORD PTR [rax+752]
	mov	DWORD PTR fd$[rsp], eax

; 80   : 			get_current_thread()->fd_current++;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	add	rax, 752				; 000002f0H
	mov	QWORD PTR tv146[rsp], rax
	mov	rax, QWORD PTR tv146[rsp]
	mov	eax, DWORD PTR [rax]
	inc	eax
	mov	rcx, QWORD PTR tv146[rsp]
	mov	DWORD PTR [rcx], eax
$LN3@sys_open_f:
$LN8@sys_open_f:

; 81   : 		}
; 82   : 	}
; 83   : 
; 84   : 	if (!(strcmp(pathname, "dev") == 0)) {

	lea	rdx, OFFSET FLAT:$SG3620
	lea	rcx, QWORD PTR pathname$[rsp]
	call	?strcmp@@YAHPEBD0@Z			; strcmp
	test	eax, eax
	je	$LN2@sys_open_f

; 85   : 		vfs_node_t file = openfs(node, filename);

	mov	r8, QWORD PTR filename$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, QWORD PTR $T5[rsp]
	call	?openfs@@YA?AU_vfs_node_@@PEAU1@PEAD@Z	; openfs
	lea	rcx, QWORD PTR $T4[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 104				; 00000068H
	rep movsb
	lea	rax, QWORD PTR file$3[rsp]
	lea	rcx, QWORD PTR $T4[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 104				; 00000068H
	rep movsb

; 86   : 		if (ufile) {

	cmp	QWORD PTR ufile$[rsp], 0
	je	SHORT $LN1@sys_open_f

; 87   : 			ufile->id = fd;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR fd$[rsp]
	mov	DWORD PTR [rax], ecx

; 88   : 			ufile->size = file.size;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$3[rsp+32]
	mov	DWORD PTR [rax+4], ecx

; 89   : 			ufile->eof = file.eof;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$3[rsp+36]
	mov	DWORD PTR [rax+8], ecx

; 90   : 			ufile->pos = file.pos;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$3[rsp+40]
	mov	DWORD PTR [rax+12], ecx

; 91   : 			ufile->start_cluster = file.current;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$3[rsp+44]
	mov	DWORD PTR [rax+16], ecx

; 92   : 			ufile->flags = file.flags; 

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$3[rsp+48]
	mov	DWORD PTR [rax+20], ecx

; 93   : 			ufile->status = file.status;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$3[rsp+52]
	mov	DWORD PTR [rax+24], ecx
$LN1@sys_open_f:
$LN2@sys_open_f:

; 94   : 		}
; 95   : 	}
; 96   : 	
; 97   : 	//! return the allocated fd number
; 98   : 	return fd;

	mov	eax, DWORD PTR fd$[rsp]

; 99   : }

	add	rsp, 440				; 000001b8H
	pop	rdi
	pop	rsi
	ret	0
?sys_open_file@@YAHPEADPEAU_file_@@@Z ENDP		; sys_open_file
_TEXT	ENDS
END
