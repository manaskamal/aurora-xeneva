; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3909	DB	'dev', 00H
$SG3923	DB	'/', 00H
CONST	ENDS
PUBLIC	?sys_open_file@@YAHPEADPEAU_file_@@@Z		; sys_open_file
PUBLIC	?sys_read_file@@YA_KHPEAEPEAU_file_@@@Z		; sys_read_file
PUBLIC	?sys_write_file@@YAXHPEA_KPEAU_file_@@@Z	; sys_write_file
PUBLIC	?sys_close_file@@YAXH@Z				; sys_close_file
PUBLIC	?sys_copy_fd@@YAHHHH@Z				; sys_copy_fd
EXTRN	strcmp:PROC
EXTRN	strchr:PROC
EXTRN	memset:PROC
EXTRN	memcpy:PROC
EXTRN	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z:PROC	; vfs_finddir
EXTRN	openfs:PROC
EXTRN	readfs:PROC
EXTRN	writefs:PROC
EXTRN	readfs_block:PROC
EXTRN	x64_cli:PROC
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuPmmngrFree:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	free:PROC
EXTRN	get_current_thread:PROC
EXTRN	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z:PROC ; thread_iterate_ready_list
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
pdata	SEGMENT
$pdata$?sys_open_file@@YAHPEADPEAU_file_@@@Z DD imagerel $LN18
	DD	imagerel $LN18+676
	DD	imagerel $unwind$?sys_open_file@@YAHPEADPEAU_file_@@@Z
$pdata$?sys_read_file@@YA_KHPEAEPEAU_file_@@@Z DD imagerel $LN12
	DD	imagerel $LN12+463
	DD	imagerel $unwind$?sys_read_file@@YA_KHPEAEPEAU_file_@@@Z
$pdata$?sys_write_file@@YAXHPEA_KPEAU_file_@@@Z DD imagerel $LN6
	DD	imagerel $LN6+289
	DD	imagerel $unwind$?sys_write_file@@YAXHPEA_KPEAU_file_@@@Z
$pdata$?sys_close_file@@YAXH@Z DD imagerel $LN5
	DD	imagerel $LN5+93
	DD	imagerel $unwind$?sys_close_file@@YAXH@Z
$pdata$?sys_copy_fd@@YAHHHH@Z DD imagerel $LN7
	DD	imagerel $LN7+160
	DD	imagerel $unwind$?sys_copy_fd@@YAHHHH@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?sys_open_file@@YAHPEADPEAU_file_@@@Z DD 021101H
	DD	0110111H
$unwind$?sys_read_file@@YA_KHPEAEPEAU_file_@@@Z DD 011201H
	DD	0c212H
$unwind$?sys_write_file@@YAXHPEA_KPEAU_file_@@@Z DD 021501H
	DD	0150115H
$unwind$?sys_close_file@@YAXH@Z DD 010801H
	DD	06208H
$unwind$?sys_copy_fd@@YAHHHH@Z DD 011101H
	DD	06211H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
t$ = 32
node$ = 40
tid$ = 64
fd$ = 72
dest_fd$ = 80
?sys_copy_fd@@YAHHHH@Z PROC				; sys_copy_fd

; 211  : int sys_copy_fd (int tid, int fd, int dest_fd) {

$LN7:
	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 212  : 	x64_cli();

	call	x64_cli

; 213  : 	vfs_node_t *node = get_current_thread()->fd[fd];

	call	get_current_thread
	movsxd	rcx, DWORD PTR fd$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+264]
	mov	QWORD PTR node$[rsp], rax

; 214  : 	thread_t *t = thread_iterate_block_list(tid);

	mov	ecx, DWORD PTR tid$[rsp]
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR t$[rsp], rax

; 215  : 	if (t == NULL)

	cmp	QWORD PTR t$[rsp], 0
	jne	SHORT $LN4@sys_copy_f

; 216  : 		t = thread_iterate_ready_list(tid);

	movzx	ecx, WORD PTR tid$[rsp]
	call	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ; thread_iterate_ready_list
	mov	QWORD PTR t$[rsp], rax
$LN4@sys_copy_f:

; 217  : 
; 218  : 	if (t == NULL)

	cmp	QWORD PTR t$[rsp], 0
	jne	SHORT $LN3@sys_copy_f

; 219  : 		return AU_FAILURE;

	mov	eax, -7
	jmp	SHORT $LN5@sys_copy_f
$LN3@sys_copy_f:

; 220  : 
; 221  : 	if (t->fd[dest_fd] != NULL){

	movsxd	rax, DWORD PTR dest_fd$[rsp]
	mov	rcx, QWORD PTR t$[rsp]
	cmp	QWORD PTR [rcx+rax*8+264], 0
	je	SHORT $LN2@sys_copy_f

; 222  : 		return AU_FAILURE;

	mov	eax, -7
	jmp	SHORT $LN5@sys_copy_f

; 223  : 	}else{

	jmp	SHORT $LN1@sys_copy_f
$LN2@sys_copy_f:

; 224  : 		t->fd[dest_fd] = node;

	movsxd	rax, DWORD PTR dest_fd$[rsp]
	mov	rcx, QWORD PTR t$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	mov	QWORD PTR [rcx+rax*8+264], rdx
$LN1@sys_copy_f:

; 225  : 	}
; 226  : 	return AU_SUCCESS;

	mov	eax, 1
$LN5@sys_copy_f:

; 227  : }

	add	rsp, 56					; 00000038H
	ret	0
?sys_copy_fd@@YAHHHH@Z ENDP				; sys_copy_fd
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
node$ = 32
fd$ = 64
?sys_close_file@@YAXH@Z PROC				; sys_close_file

; 194  : void sys_close_file (int fd) {

$LN5:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 195  : 	x64_cli();

	call	x64_cli

; 196  : 	vfs_node_t *node = get_current_thread()->fd[fd];

	call	get_current_thread
	movsxd	rcx, DWORD PTR fd$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+264]
	mov	QWORD PTR node$[rsp], rax

; 197  : 	get_current_thread()->fd[fd] = 0;

	call	get_current_thread
	movsxd	rcx, DWORD PTR fd$[rsp]
	mov	QWORD PTR [rax+rcx*8+264], 0

; 198  : 	if ((node->flags & FS_FLAG_DEVICE)){

	mov	rax, QWORD PTR node$[rsp]
	movzx	eax, BYTE PTR [rax+48]
	and	eax, 8
	test	eax, eax
	je	SHORT $LN2@sys_close_

; 199  : 		
; 200  : 		return;

	jmp	SHORT $LN3@sys_close_

; 201  : 	}else{

	jmp	SHORT $LN1@sys_close_
$LN2@sys_close_:

; 202  : 		free(node);

	mov	rcx, QWORD PTR node$[rsp]
	call	free
$LN1@sys_close_:
$LN3@sys_close_:

; 203  : 	}
; 204  : 
; 205  : }

	add	rsp, 56					; 00000038H
	ret	0
?sys_close_file@@YAXH@Z ENDP				; sys_close_file
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
node$ = 32
file$ = 48
fd$ = 176
buffer$ = 184
ufile$ = 192
?sys_write_file@@YAXHPEA_KPEAU_file_@@@Z PROC		; sys_write_file

; 164  : void sys_write_file (int fd, uint64* buffer, FILE *ufile) {

$LN6:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 168				; 000000a8H

; 165  : 	x64_cli();

	call	x64_cli

; 166  : 	vfs_node_t file;
; 167  : 	file.size = ufile->size;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+4]
	mov	DWORD PTR file$[rsp+32], eax

; 168  : 	file.eof = ufile->eof;

	mov	rax, QWORD PTR ufile$[rsp]
	movzx	eax, BYTE PTR [rax+8]
	mov	BYTE PTR file$[rsp+36], al

; 169  : 	file.pos = ufile->pos;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+12]
	mov	DWORD PTR file$[rsp+40], eax

; 170  : 	file.current = ufile->start_cluster;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+16]
	mov	DWORD PTR file$[rsp+44], eax

; 171  : 	file.flags = ufile->flags;

	mov	rax, QWORD PTR ufile$[rsp]
	movzx	eax, BYTE PTR [rax+20]
	mov	BYTE PTR file$[rsp+48], al

; 172  : 	file.status = ufile->status;

	mov	rax, QWORD PTR ufile$[rsp]
	movzx	eax, BYTE PTR [rax+24]
	mov	BYTE PTR file$[rsp+49], al

; 173  : 	file.open = 0;

	mov	QWORD PTR file$[rsp+64], 0

; 174  : 	file.read = 0;

	mov	QWORD PTR file$[rsp+72], 0

; 175  : 	file.read_blk = 0;

	mov	QWORD PTR file$[rsp+88], 0

; 176  : 	file.write = 0;

	mov	QWORD PTR file$[rsp+80], 0

; 177  : 	file.ioquery  = 0;

	mov	QWORD PTR file$[rsp+96], 0

; 178  : 
; 179  : 	vfs_node_t *node = get_current_thread()->fd[fd];

	call	get_current_thread
	movsxd	rcx, DWORD PTR fd$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+264]
	mov	QWORD PTR node$[rsp], rax

; 180  : 	if (node == NULL) {

	cmp	QWORD PTR node$[rsp], 0
	jne	SHORT $LN3@sys_write_

; 181  : 		return;

	jmp	SHORT $LN4@sys_write_
$LN3@sys_write_:

; 182  : 	}
; 183  : 
; 184  : 	if (ufile->flags) {

	mov	rax, QWORD PTR ufile$[rsp]
	cmp	DWORD PTR [rax+20], 0
	je	SHORT $LN2@sys_write_

; 185  : 		writefs(node, &file,buffer,file.size);

	mov	r9d, DWORD PTR file$[rsp+32]
	mov	r8, QWORD PTR buffer$[rsp]
	lea	rdx, QWORD PTR file$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	writefs

; 186  : 	}else {

	jmp	SHORT $LN1@sys_write_
$LN2@sys_write_:

; 187  : 		writefs(node, node, buffer,file.size);

	mov	r9d, DWORD PTR file$[rsp+32]
	mov	r8, QWORD PTR buffer$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	writefs
$LN1@sys_write_:
$LN4@sys_write_:

; 188  : 	}
; 189  : }

	add	rsp, 168				; 000000a8H
	ret	0
?sys_write_file@@YAXHPEA_KPEAU_file_@@@Z ENDP		; sys_write_file
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
i$1 = 32
node$ = 40
byte_read$ = 48
buff$2 = 56
file$ = 64
read_$3 = 72
read_$4 = 80
fd$ = 112
buffer$ = 120
ufile$ = 128
?sys_read_file@@YA_KHPEAEPEAU_file_@@@Z PROC		; sys_read_file

; 115  : size_t sys_read_file (int fd, uint8_t* buffer, FILE *ufile) {

$LN12:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 104				; 00000068H

; 116  : 	x64_cli ();

	call	x64_cli

; 117  : 	vfs_node_t *file = NULL; 

	mov	QWORD PTR file$[rsp], 0

; 118  : 	size_t byte_read = AU_INVALID;

	mov	QWORD PTR byte_read$[rsp], -1

; 119  : 	vfs_node_t *node = NULL;

	mov	QWORD PTR node$[rsp], 0

; 120  : 
; 121  : 	/* if UFILE->size is greater than 0, it's a
; 122  : 	 * file system based file descriptor, so get
; 123  : 	 * the root file system file */
; 124  : 	if (ufile){

	cmp	QWORD PTR ufile$[rsp], 0
	je	$LN9@sys_read_f

; 125  : 		node = vfs_finddir("/");

	lea	rcx, OFFSET FLAT:$SG3923
	call	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z	; vfs_finddir
	mov	QWORD PTR node$[rsp], rax

; 126  : 		file = get_current_thread()->fd[fd];

	call	get_current_thread
	movsxd	rcx, DWORD PTR fd$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+264]
	mov	QWORD PTR file$[rsp], rax

; 127  : 		if (node == NULL)

	cmp	QWORD PTR node$[rsp], 0
	jne	SHORT $LN8@sys_read_f

; 128  : 			return byte_read;

	mov	rax, QWORD PTR byte_read$[rsp]
	jmp	$LN10@sys_read_f
$LN8@sys_read_f:

; 129  : 		for (int i=0; i < ufile->size; i++){

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN7@sys_read_f
$LN6@sys_read_f:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN7@sys_read_f:
	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+4]
	cmp	DWORD PTR i$1[rsp], eax
	jae	$LN5@sys_read_f

; 130  : 			if (file->eof) {

	mov	rax, QWORD PTR file$[rsp]
	movzx	eax, BYTE PTR [rax+36]
	test	eax, eax
	je	SHORT $LN4@sys_read_f

; 131  : 				ufile->eof = 1;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	DWORD PTR [rax+8], 1

; 132  : 				break;

	jmp	$LN5@sys_read_f
$LN4@sys_read_f:

; 133  : 			}
; 134  : 			uint64_t* buff = (uint64_t*)p2v((size_t)AuPmmngrAlloc());

	call	AuPmmngrAlloc
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buff$2[rsp], rax

; 135  : 			memset(buff, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR buff$2[rsp]
	call	memset

; 136  : 			size_t read_ = readfs_block (node,file,(uint64_t*)v2p((size_t)buff));

	mov	rcx, QWORD PTR buff$2[rsp]
	call	v2p
	mov	r8, rax
	mov	rdx, QWORD PTR file$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	readfs_block
	mov	QWORD PTR read_$3[rsp], rax

; 137  : 			memcpy (buffer,buff,4096);

	mov	r8d, 4096				; 00001000H
	mov	rdx, QWORD PTR buff$2[rsp]
	mov	rcx, QWORD PTR buffer$[rsp]
	call	memcpy

; 138  : 			buffer += 4096;

	mov	rax, QWORD PTR buffer$[rsp]
	add	rax, 4096				; 00001000H
	mov	QWORD PTR buffer$[rsp], rax

; 139  : 			AuPmmngrFree((void*)v2p((size_t)buff));

	mov	rcx, QWORD PTR buff$2[rsp]
	call	v2p
	mov	rcx, rax
	call	AuPmmngrFree

; 140  : 			byte_read += read_;

	mov	rax, QWORD PTR read_$3[rsp]
	mov	rcx, QWORD PTR byte_read$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR byte_read$[rsp], rax

; 141  : 		}

	jmp	$LN6@sys_read_f
$LN5@sys_read_f:
	jmp	SHORT $LN3@sys_read_f
$LN9@sys_read_f:

; 142  : 
; 143  : 	}else if (ufile == NULL) {

	cmp	QWORD PTR ufile$[rsp], 0
	jne	SHORT $LN2@sys_read_f

; 144  : 		/* So this fd is non-file system based fd
; 145  : 		 * get it from fd table */
; 146  : 		node = get_current_thread()->fd[fd];

	call	get_current_thread
	movsxd	rcx, DWORD PTR fd$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+264]
	mov	QWORD PTR node$[rsp], rax

; 147  : 		if (node == NULL)

	cmp	QWORD PTR node$[rsp], 0
	jne	SHORT $LN1@sys_read_f

; 148  : 			return byte_read;

	mov	rax, QWORD PTR byte_read$[rsp]
	jmp	SHORT $LN10@sys_read_f
$LN1@sys_read_f:

; 149  : 
; 150  : 		size_t read_ = readfs(node, node, (uint64_t*)buffer, node->size);

	mov	rax, QWORD PTR node$[rsp]
	mov	r9d, DWORD PTR [rax+32]
	mov	r8, QWORD PTR buffer$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	readfs
	mov	QWORD PTR read_$4[rsp], rax

; 151  : 		byte_read += read_;

	mov	rax, QWORD PTR read_$4[rsp]
	mov	rcx, QWORD PTR byte_read$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR byte_read$[rsp], rax
$LN2@sys_read_f:
$LN3@sys_read_f:

; 152  : 	}
; 153  : 
; 154  : 	return byte_read;

	mov	rax, QWORD PTR byte_read$[rsp]
$LN10@sys_read_f:

; 155  : }

	add	rsp, 104				; 00000068H
	ret	0
?sys_read_file@@YA_KHPEAEPEAU_file_@@@Z ENDP		; sys_read_file
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
fd_found$ = 32
i$ = 36
i$1 = 40
fd$ = 44
file$2 = 48
p$ = 56
node$ = 64
tv168 = 72
tv183 = 80
_node$3 = 88
tv172 = 96
tv157 = 104
pathname$ = 112
filename$ = 144
ufile$ = 152
?sys_open_file@@YAHPEADPEAU_file_@@@Z PROC		; sys_open_file

; 50   : int sys_open_file (char* filename, FILE *ufile) {

$LN18:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 136				; 00000088H

; 51   : 	x64_cli();

	call	x64_cli

; 52   : 	char* p = strchr (filename, '/');

	mov	edx, 47					; 0000002fH
	mov	rcx, QWORD PTR filename$[rsp]
	call	strchr
	mov	QWORD PTR p$[rsp], rax

; 53   : 	if (p)

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN15@sys_open_f

; 54   : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax
$LN15@sys_open_f:

; 55   : 
; 56   : 
; 57   : 	char pathname[16];
; 58   : 	int i;
; 59   : 	for (i = 0; i < 16; i++) {

	mov	DWORD PTR i$[rsp], 0
	jmp	SHORT $LN14@sys_open_f
$LN13@sys_open_f:
	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
$LN14@sys_open_f:
	cmp	DWORD PTR i$[rsp], 16
	jge	SHORT $LN12@sys_open_f

; 60   : 		if ( p[i] == '/'  || p[i] == '\0')

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	je	SHORT $LN10@sys_open_f
	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	jne	SHORT $LN11@sys_open_f
$LN10@sys_open_f:

; 61   : 			break;

	jmp	SHORT $LN12@sys_open_f
$LN11@sys_open_f:

; 62   : 		pathname[i] = p[i];

	movsxd	rax, DWORD PTR i$[rsp]
	movsxd	rcx, DWORD PTR i$[rsp]
	mov	rdx, QWORD PTR p$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR pathname$[rsp+rcx], al

; 63   : 	}

	jmp	SHORT $LN13@sys_open_f
$LN12@sys_open_f:

; 64   : 
; 65   : 	pathname[i] = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	BYTE PTR pathname$[rsp+rax], 0

; 66   : 
; 67   : 	int fd = AU_INVLD_FD;

	mov	DWORD PTR fd$[rsp], -4

; 68   : 	vfs_node_t *node = vfs_finddir(filename);

	mov	rcx, QWORD PTR filename$[rsp]
	call	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z	; vfs_finddir
	mov	QWORD PTR node$[rsp], rax

; 69   : 
; 70   : 	bool fd_found = false;

	mov	BYTE PTR fd_found$[rsp], 0

; 71   : 	if (node) {

	cmp	QWORD PTR node$[rsp], 0
	je	SHORT $LN9@sys_open_f

; 72   : 		for (int i = 0; i < 60; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN8@sys_open_f
$LN7@sys_open_f:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN8@sys_open_f:
	cmp	DWORD PTR i$1[rsp], 60			; 0000003cH
	jge	SHORT $LN6@sys_open_f

; 73   : 			vfs_node_t *_node = get_current_thread()->fd[i];

	call	get_current_thread
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+264]
	mov	QWORD PTR _node$3[rsp], rax

; 74   : 			if (_node == node) {

	mov	rax, QWORD PTR node$[rsp]
	cmp	QWORD PTR _node$3[rsp], rax
	jne	SHORT $LN5@sys_open_f

; 75   : 				fd = i;

	mov	eax, DWORD PTR i$1[rsp]
	mov	DWORD PTR fd$[rsp], eax

; 76   : 				fd_found = true;

	mov	BYTE PTR fd_found$[rsp], 1

; 77   : 				break;

	jmp	SHORT $LN6@sys_open_f
$LN5@sys_open_f:

; 78   : 			}
; 79   : 		}

	jmp	SHORT $LN7@sys_open_f
$LN6@sys_open_f:
$LN9@sys_open_f:

; 80   : 	}
; 81   : 
; 82   : 	if (!(strcmp(pathname, "dev") == 0)) {

	lea	rdx, OFFSET FLAT:$SG3909
	lea	rcx, QWORD PTR pathname$[rsp]
	call	strcmp
	test	eax, eax
	je	$LN4@sys_open_f

; 83   : 		vfs_node_t *file = openfs(node, filename);

	mov	rdx, QWORD PTR filename$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	openfs
	mov	QWORD PTR file$2[rsp], rax

; 84   : 		if (ufile) {

	cmp	QWORD PTR ufile$[rsp], 0
	je	$LN3@sys_open_f

; 85   : 			ufile->id = fd;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR fd$[rsp]
	mov	DWORD PTR [rax], ecx

; 86   : 			ufile->size = file->size;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	rcx, QWORD PTR file$2[rsp]
	mov	ecx, DWORD PTR [rcx+32]
	mov	DWORD PTR [rax+4], ecx

; 87   : 			ufile->eof = file->eof;

	mov	rax, QWORD PTR file$2[rsp]
	movzx	eax, BYTE PTR [rax+36]
	mov	rcx, QWORD PTR ufile$[rsp]
	mov	DWORD PTR [rcx+8], eax

; 88   : 			ufile->pos = file->pos;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	rcx, QWORD PTR file$2[rsp]
	mov	ecx, DWORD PTR [rcx+40]
	mov	DWORD PTR [rax+12], ecx

; 89   : 			ufile->start_cluster = file->current;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	rcx, QWORD PTR file$2[rsp]
	mov	ecx, DWORD PTR [rcx+44]
	mov	DWORD PTR [rax+16], ecx

; 90   : 			ufile->flags = file->flags; 

	mov	rax, QWORD PTR file$2[rsp]
	movzx	eax, BYTE PTR [rax+48]
	mov	rcx, QWORD PTR ufile$[rsp]
	mov	DWORD PTR [rcx+20], eax

; 91   : 			ufile->status = file->status;

	mov	rax, QWORD PTR file$2[rsp]
	movzx	eax, BYTE PTR [rax+49]
	mov	rcx, QWORD PTR ufile$[rsp]
	mov	DWORD PTR [rcx+24], eax
$LN3@sys_open_f:

; 92   : 		}
; 93   : 
; 94   : 		get_current_thread()->fd[get_current_thread()->fd_current] = file;

	call	get_current_thread
	mov	QWORD PTR tv157[rsp], rax
	call	get_current_thread
	movsxd	rax, DWORD PTR [rax+744]
	mov	rcx, QWORD PTR file$2[rsp]
	mov	rdx, QWORD PTR tv157[rsp]
	mov	QWORD PTR [rdx+rax*8+264], rcx

; 95   : 		fd = get_current_thread()->fd_current;

	call	get_current_thread
	mov	eax, DWORD PTR [rax+744]
	mov	DWORD PTR fd$[rsp], eax

; 96   : 		get_current_thread()->fd_current++;

	call	get_current_thread
	add	rax, 744				; 000002e8H
	mov	QWORD PTR tv168[rsp], rax
	mov	rax, QWORD PTR tv168[rsp]
	mov	eax, DWORD PTR [rax]
	inc	eax
	mov	rcx, QWORD PTR tv168[rsp]
	mov	DWORD PTR [rcx], eax

; 97   : 	}else {

	jmp	SHORT $LN2@sys_open_f
$LN4@sys_open_f:

; 98   : 		if (!fd_found){

	movzx	eax, BYTE PTR fd_found$[rsp]
	test	eax, eax
	jne	SHORT $LN1@sys_open_f

; 99   : 			get_current_thread()->fd[get_current_thread()->fd_current] = node;

	call	get_current_thread
	mov	QWORD PTR tv172[rsp], rax
	call	get_current_thread
	movsxd	rax, DWORD PTR [rax+744]
	mov	rcx, QWORD PTR node$[rsp]
	mov	rdx, QWORD PTR tv172[rsp]
	mov	QWORD PTR [rdx+rax*8+264], rcx

; 100  : 			fd = get_current_thread()->fd_current;

	call	get_current_thread
	mov	eax, DWORD PTR [rax+744]
	mov	DWORD PTR fd$[rsp], eax

; 101  : 			get_current_thread()->fd_current++;

	call	get_current_thread
	add	rax, 744				; 000002e8H
	mov	QWORD PTR tv183[rsp], rax
	mov	rax, QWORD PTR tv183[rsp]
	mov	eax, DWORD PTR [rax]
	inc	eax
	mov	rcx, QWORD PTR tv183[rsp]
	mov	DWORD PTR [rcx], eax
$LN1@sys_open_f:
$LN2@sys_open_f:

; 102  : 		}
; 103  : 	}
; 104  : 	
; 105  : 	//! return the allocated fd number
; 106  : 	return fd;

	mov	eax, DWORD PTR fd$[rsp]

; 107  : }

	add	rsp, 136				; 00000088H
	ret	0
?sys_open_file@@YAHPEADPEAU_file_@@@Z ENDP		; sys_open_file
_TEXT	ENDS
END
