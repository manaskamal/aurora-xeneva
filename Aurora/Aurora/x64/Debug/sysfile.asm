; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3499	DB	'dev', 00H
CONST	ENDS
PUBLIC	?sys_open_file@@YAHPEADPEAU_file_@@@Z		; sys_open_file
PUBLIC	?sys_read_file@@YAXHPEAEPEAU_file_@@@Z		; sys_read_file
EXTRN	?strcmp@@YAHPEBD0@Z:PROC			; strcmp
EXTRN	?strchr@@YAPEADPEADH@Z:PROC			; strchr
EXTRN	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z:PROC	; vfs_finddir
EXTRN	?openfs@@YA?AU_vfs_node_@@PEAU1@PEAD@Z:PROC	; openfs
EXTRN	?readfs@@YAXPEAU_vfs_node_@@0PEAEI@Z:PROC	; readfs
EXTRN	x64_cli:PROC
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
pdata	SEGMENT
$pdata$?sys_open_file@@YAHPEADPEAU_file_@@@Z DD imagerel $LN10
	DD	imagerel $LN10+508
	DD	imagerel $unwind$?sys_open_file@@YAHPEADPEAU_file_@@@Z
$pdata$?sys_read_file@@YAXHPEAEPEAU_file_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+229
	DD	imagerel $unwind$?sys_read_file@@YAXHPEAEPEAU_file_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?sys_open_file@@YAHPEADPEAU_file_@@@Z DD 041301H
	DD	0310113H
	DD	0600b700cH
$unwind$?sys_read_file@@YAXHPEAEPEAU_file_@@@Z DD 021501H
	DD	0130115H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
node$ = 32
file$ = 48
fd$ = 160
buffer$ = 168
ufile$ = 176
?sys_read_file@@YAXHPEAEPEAU_file_@@@Z PROC		; sys_read_file

; 55   : void sys_read_file (int fd, unsigned char* buffer, FILE *ufile) {

$LN3:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 152				; 00000098H

; 56   : 	x64_cli ();

	call	x64_cli

; 57   : 	vfs_node_t file;
; 58   : 	file.size = ufile->size;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+4]
	mov	DWORD PTR file$[rsp+32], eax

; 59   : 	file.eof = ufile->eof;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+8]
	mov	DWORD PTR file$[rsp+36], eax

; 60   : 	file.pos = ufile->pos;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+12]
	mov	DWORD PTR file$[rsp+40], eax

; 61   : 	file.current = ufile->start_cluster;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+16]
	mov	DWORD PTR file$[rsp+44], eax

; 62   : 	file.flags = ufile->flags;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+20]
	mov	DWORD PTR file$[rsp+48], eax

; 63   : 	file.status = ufile->status;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	eax, DWORD PTR [rax+24]
	mov	DWORD PTR file$[rsp+52], eax

; 64   : 	file.open = 0;

	mov	QWORD PTR file$[rsp+56], 0

; 65   : 	file.read = 0;

	mov	QWORD PTR file$[rsp+64], 0

; 66   : 	file.read_blk = 0;

	mov	QWORD PTR file$[rsp+80], 0

; 67   : 	file.write = 0;

	mov	QWORD PTR file$[rsp+72], 0

; 68   : 	file.ioquery  = 0;

	mov	QWORD PTR file$[rsp+88], 0

; 69   : 
; 70   : 	vfs_node_t *node = get_current_thread()->fd[fd];

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movsxd	rcx, DWORD PTR fd$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+264]
	mov	QWORD PTR node$[rsp], rax

; 71   : 	readfs(node,&file,buffer,file.size);

	mov	r9d, DWORD PTR file$[rsp+32]
	mov	r8, QWORD PTR buffer$[rsp]
	lea	rdx, QWORD PTR file$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	?readfs@@YAXPEAU_vfs_node_@@0PEAEI@Z	; readfs

; 72   : }

	add	rsp, 152				; 00000098H
	ret	0
?sys_read_file@@YAXHPEAEPEAU_file_@@@Z ENDP		; sys_read_file
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysfile.cpp
_TEXT	SEGMENT
i$ = 32
p$ = 40
fd$ = 48
tv151 = 56
node$ = 64
tv92 = 72
pathname$ = 80
file$1 = 96
$T2 = 192
$T3 = 288
filename$ = 416
ufile$ = 424
?sys_open_file@@YAHPEADPEAU_file_@@@Z PROC		; sys_open_file

; 19   : int sys_open_file (char* filename, FILE *ufile) {

$LN10:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 392				; 00000188H

; 20   : 	x64_cli();

	call	x64_cli

; 21   : 	char* p = strchr (filename, '/');

	mov	edx, 47					; 0000002fH
	mov	rcx, QWORD PTR filename$[rsp]
	call	?strchr@@YAPEADPEADH@Z			; strchr
	mov	QWORD PTR p$[rsp], rax

; 22   : 	if (p)

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN7@sys_open_f

; 23   : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax
$LN7@sys_open_f:

; 24   : 
; 25   : 
; 26   : 	char pathname[16];
; 27   : 	int i;
; 28   : 	for (i = 0; i < 16; i++) {

	mov	DWORD PTR i$[rsp], 0
	jmp	SHORT $LN6@sys_open_f
$LN5@sys_open_f:
	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
$LN6@sys_open_f:
	cmp	DWORD PTR i$[rsp], 16
	jge	SHORT $LN4@sys_open_f

; 29   : 		if ( p[i] == '/'  || p[i] == '\0')

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	je	SHORT $LN2@sys_open_f
	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	jne	SHORT $LN3@sys_open_f
$LN2@sys_open_f:

; 30   : 			break;

	jmp	SHORT $LN4@sys_open_f
$LN3@sys_open_f:

; 31   : 		pathname[i] = p[i];

	movsxd	rax, DWORD PTR i$[rsp]
	movsxd	rcx, DWORD PTR i$[rsp]
	mov	rdx, QWORD PTR p$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR pathname$[rsp+rcx], al

; 32   : 	}

	jmp	SHORT $LN5@sys_open_f
$LN4@sys_open_f:

; 33   : 
; 34   : 	pathname[i] = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	BYTE PTR pathname$[rsp+rax], 0

; 35   : 
; 36   : 
; 37   : 	vfs_node_t *node = vfs_finddir(filename);

	mov	rcx, QWORD PTR filename$[rsp]
	call	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z	; vfs_finddir
	mov	QWORD PTR node$[rsp], rax

; 38   : 	get_current_thread()->fd[get_current_thread()->fd_current] = node;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	QWORD PTR tv92[rsp], rax
	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movsxd	rax, DWORD PTR [rax+744]
	mov	rcx, QWORD PTR node$[rsp]
	mov	rdx, QWORD PTR tv92[rsp]
	mov	QWORD PTR [rdx+rax*8+264], rcx

; 39   :     int fd = get_current_thread()->fd_current;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	eax, DWORD PTR [rax+744]
	mov	DWORD PTR fd$[rsp], eax

; 40   : 
; 41   : 	if (!(strcmp(pathname, "dev") == 0)) {

	lea	rdx, OFFSET FLAT:$SG3499
	lea	rcx, QWORD PTR pathname$[rsp]
	call	?strcmp@@YAHPEBD0@Z			; strcmp
	test	eax, eax
	je	$LN1@sys_open_f

; 42   : 		vfs_node_t file = openfs(node, filename);

	mov	r8, QWORD PTR filename$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, QWORD PTR $T3[rsp]
	call	?openfs@@YA?AU_vfs_node_@@PEAU1@PEAD@Z	; openfs
	lea	rcx, QWORD PTR $T2[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 96					; 00000060H
	rep movsb
	lea	rax, QWORD PTR file$1[rsp]
	lea	rcx, QWORD PTR $T2[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 96					; 00000060H
	rep movsb

; 43   : 		ufile->id = fd;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR fd$[rsp]
	mov	DWORD PTR [rax], ecx

; 44   : 		ufile->size = file.size;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$1[rsp+32]
	mov	DWORD PTR [rax+4], ecx

; 45   : 		ufile->eof = file.eof;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$1[rsp+36]
	mov	DWORD PTR [rax+8], ecx

; 46   : 		ufile->pos = file.pos;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$1[rsp+40]
	mov	DWORD PTR [rax+12], ecx

; 47   : 		ufile->start_cluster = file.current;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$1[rsp+44]
	mov	DWORD PTR [rax+16], ecx

; 48   : 		ufile->flags = file.flags; 

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$1[rsp+48]
	mov	DWORD PTR [rax+20], ecx

; 49   : 		ufile->status = file.status;

	mov	rax, QWORD PTR ufile$[rsp]
	mov	ecx, DWORD PTR file$1[rsp+52]
	mov	DWORD PTR [rax+24], ecx
$LN1@sys_open_f:

; 50   : 	}
; 51   : 	get_current_thread()->fd_current++;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	add	rax, 744				; 000002e8H
	mov	QWORD PTR tv151[rsp], rax
	mov	rax, QWORD PTR tv151[rsp]
	mov	eax, DWORD PTR [rax]
	inc	eax
	mov	rcx, QWORD PTR tv151[rsp]
	mov	DWORD PTR [rcx], eax

; 52   : 	return fd;

	mov	eax, DWORD PTR fd$[rsp]

; 53   : }

	add	rsp, 392				; 00000188H
	pop	rdi
	pop	rsi
	ret	0
?sys_open_file@@YAHPEADPEAU_file_@@@Z ENDP		; sys_open_file
_TEXT	ENDS
END
