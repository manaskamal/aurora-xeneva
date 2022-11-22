; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?root_dir@@3PEAU_vfs_entry_@@EA			; root_dir
_BSS	SEGMENT
?root_dir@@3PEAU_vfs_entry_@@EA DQ 01H DUP (?)		; root_dir
_BSS	ENDS
CONST	SEGMENT
$SG3652	DB	'[VFS]: Mounting filesystem to root failed, already in us'
	DB	'e', 0aH, 00H
	ORG $+5
$SG3680	DB	'Recursively calling for -> %s ', 0dH, 0aH, 00H
	ORG $+7
$SG3681	DB	'[vfs]: already mounted -> %s ', 0dH, 0aH, 00H
$SG3683	DB	'Not found entry -> %s ', 0dH, 0aH, 00H
	ORG $+7
$SG3685	DB	'Mounting path -> %s, creating entry ', 0dH, 0aH, 00H
	ORG $+1
$SG3687	DB	'Entry created -> %x ', 0dH, 0aH, 00H
	ORG $+1
$SG3689	DB	'Ent->child -> %x %x nodes-> %d ', 0dH, 0aH, 00H
	ORG $+6
$SG3690	DB	'List added %x ', 0dH, 0aH, 00H
	ORG $+7
$SG3729	DB	'Directory', 00H
	ORG $+2
$SG3732	DB	'File', 00H
	ORG $+7
$SG3733	DB	'%s -> %s ', 0dH, 0aH, 00H
CONST	ENDS
PUBLIC	?AuVFSInit@@YAXXZ				; AuVFSInit
PUBLIC	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z		; vfs_finddir
PUBLIC	vfs_mkdir
PUBLIC	vfs_mkentry
PUBLIC	vfs_mount
PUBLIC	vfs_unmount
PUBLIC	vfs_remove_file
PUBLIC	?vfs_lsdir@@YAXPEAD@Z				; vfs_lsdir
PUBLIC	openfs
PUBLIC	readfs
PUBLIC	writefs
PUBLIC	readfs_block
PUBLIC	vfs_ioquery
EXTRN	strcmp:PROC
EXTRN	strcpy:PROC
EXTRN	strlen:PROC
EXTRN	strchr:PROC
EXTRN	initialize_list:PROC
EXTRN	list_add:PROC
EXTRN	list_remove:PROC
EXTRN	list_get_at:PROC
EXTRN	malloc:PROC
EXTRN	?initialize_fat32@@YAXXZ:PROC			; initialize_fat32
EXTRN	?fat32_self_register@@YAXXZ:PROC		; fat32_self_register
EXTRN	?devfs_mount@@YAXXZ:PROC			; devfs_mount
EXTRN	_debug_print_:PROC
pdata	SEGMENT
$pdata$?AuVFSInit@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+77
	DD	imagerel $unwind$?AuVFSInit@@YAXXZ
$pdata$?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z DD imagerel $LN20
	DD	imagerel $LN20+502
	DD	imagerel $unwind$?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z
$pdata$vfs_mkdir DD imagerel $LN20
	DD	imagerel $LN20+504
	DD	imagerel $unwind$vfs_mkdir
$pdata$vfs_mkentry DD imagerel $LN3
	DD	imagerel $LN3+55
	DD	imagerel $unwind$vfs_mkentry
$pdata$vfs_mount DD imagerel $LN23
	DD	imagerel $LN23+793
	DD	imagerel $unwind$vfs_mount
$pdata$vfs_unmount DD imagerel $LN19
	DD	imagerel $LN19+479
	DD	imagerel $unwind$vfs_unmount
$pdata$vfs_remove_file DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$vfs_remove_file
$pdata$?vfs_lsdir@@YAXPEAD@Z DD imagerel $LN25
	DD	imagerel $LN25+598
	DD	imagerel $unwind$?vfs_lsdir@@YAXPEAD@Z
$pdata$openfs DD imagerel $LN4
	DD	imagerel $LN4+45
	DD	imagerel $unwind$openfs
$pdata$readfs DD imagerel $LN4
	DD	imagerel $LN4+69
	DD	imagerel $unwind$readfs
$pdata$writefs DD imagerel $LN4
	DD	imagerel $LN4+60
	DD	imagerel $unwind$writefs
$pdata$readfs_block DD imagerel $LN4
	DD	imagerel $LN4+59
	DD	imagerel $unwind$readfs_block
$pdata$vfs_ioquery DD imagerel $LN4
	DD	imagerel $LN4+53
	DD	imagerel $unwind$vfs_ioquery
pdata	ENDS
xdata	SEGMENT
$unwind$?AuVFSInit@@YAXXZ DD 010401H
	DD	06204H
$unwind$?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z DD 010901H
	DD	0e209H
$unwind$vfs_mkdir DD 011301H
	DD	0c213H
$unwind$vfs_mkentry DD 010401H
	DD	06204H
$unwind$vfs_mount DD 011301H
	DD	0e213H
$unwind$vfs_unmount DD 020c01H
	DD	011010cH
$unwind$vfs_remove_file DD 010901H
	DD	04209H
$unwind$?vfs_lsdir@@YAXPEAD@Z DD 010901H
	DD	0e209H
$unwind$openfs DD 010e01H
	DD	0420eH
$unwind$readfs DD 011801H
	DD	04218H
$unwind$writefs DD 011801H
	DD	04218H
$unwind$readfs_block DD 011301H
	DD	04213H
$unwind$vfs_ioquery DD 011201H
	DD	04212H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
node$ = 48
code$ = 56
arg$ = 64
vfs_ioquery PROC

; 68   : int vfs_ioquery (vfs_node_t *node, int code, void* arg) {

$LN4:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 69   : 	if (node) {

	cmp	QWORD PTR node$[rsp], 0
	je	SHORT $LN1@vfs_ioquer

; 70   : 		return node->ioquery (node, code, arg);

	mov	r8, QWORD PTR arg$[rsp]
	mov	edx, DWORD PTR code$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	mov	rax, QWORD PTR node$[rsp]
	call	QWORD PTR [rax+104]
$LN1@vfs_ioquer:

; 71   : 	}
; 72   : }

	add	rsp, 40					; 00000028H
	ret	0
vfs_ioquery ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
node$ = 48
file$ = 56
buffer$ = 64
readfs_block PROC

; 61   : size_t readfs_block (vfs_node_t* node, vfs_node_t* file, uint64_t *buffer) {

$LN4:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 62   : 	if (node) {

	cmp	QWORD PTR node$[rsp], 0
	je	SHORT $LN1@readfs_blo

; 63   : 		return node->read_blk (file, buffer);

	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, QWORD PTR file$[rsp]
	mov	rax, QWORD PTR node$[rsp]
	call	QWORD PTR [rax+96]
	jmp	SHORT $LN2@readfs_blo
$LN1@readfs_blo:

; 64   : 	}
; 65   : 	return -1;

	mov	rax, -1
$LN2@readfs_blo:

; 66   : }

	add	rsp, 40					; 00000028H
	ret	0
readfs_block ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
node$ = 48
file$ = 56
buffer$ = 64
length$ = 72
writefs	PROC

; 55   : void writefs (vfs_node_t *node, vfs_node_t* file, uint64_t *buffer, uint32_t length) {

$LN4:
	mov	DWORD PTR [rsp+32], r9d
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 56   : 	if (node) {

	cmp	QWORD PTR node$[rsp], 0
	je	SHORT $LN1@writefs

; 57   : 		node->write (file, buffer, length);

	mov	r8d, DWORD PTR length$[rsp]
	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, QWORD PTR file$[rsp]
	mov	rax, QWORD PTR node$[rsp]
	call	QWORD PTR [rax+80]
$LN1@writefs:

; 58   : 	}
; 59   : }

	add	rsp, 40					; 00000028H
	ret	0
writefs	ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
node$ = 48
file$ = 56
buffer$ = 64
length$ = 72
readfs	PROC

; 47   : size_t readfs (vfs_node_t *node, vfs_node_t* file, uint64_t* buffer, uint32_t length) {

$LN4:
	mov	DWORD PTR [rsp+32], r9d
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 48   : 	if (node) {

	cmp	QWORD PTR node$[rsp], 0
	je	SHORT $LN1@readfs

; 49   : 		return node->read (file, buffer, length);

	mov	r8d, DWORD PTR length$[rsp]
	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, QWORD PTR file$[rsp]
	mov	rax, QWORD PTR node$[rsp]
	call	QWORD PTR [rax+72]
	jmp	SHORT $LN2@readfs
$LN1@readfs:

; 50   : 	}
; 51   : 	return -1;

	mov	rax, -1
$LN2@readfs:

; 52   : }

	add	rsp, 40					; 00000028H
	ret	0
readfs	ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
node$ = 48
path$ = 56
openfs	PROC

; 41   : vfs_node_t* openfs (vfs_node_t *node, char* path) {

$LN4:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 42   : 	if (node) {

	cmp	QWORD PTR node$[rsp], 0
	je	SHORT $LN1@openfs

; 43   : 		return node->open (node, path);

	mov	rdx, QWORD PTR path$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	mov	rax, QWORD PTR node$[rsp]
	call	QWORD PTR [rax+64]
$LN1@openfs:

; 44   : 	}
; 45   : }

	add	rsp, 40					; 00000028H
	ret	0
openfs	ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
i$1 = 32
found$ = 36
next$ = 40
j$2 = 48
i$3 = 52
ent$ = 56
file_$4 = 64
type$5 = 72
f$6 = 80
entry_found$ = 88
pathname$7 = 96
path$ = 128
?vfs_lsdir@@YAXPEAD@Z PROC				; vfs_lsdir

; 345  : void vfs_lsdir (char* path) {

$LN25:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 120				; 00000078H

; 346  : 	char* next = strchr(path, '/');

	mov	edx, 47					; 0000002fH
	mov	rcx, QWORD PTR path$[rsp]
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 347  : 	if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN22@vfs_lsdir

; 348  : 		next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN22@vfs_lsdir:

; 349  : 
; 350  : 	bool found = false;

	mov	BYTE PTR found$[rsp], 0

; 351  : 	vfs_entry *ent = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR ent$[rsp], rax

; 352  : 	vfs_node_t *entry_found = 0;

	mov	QWORD PTR entry_found$[rsp], 0

; 353  : 
; 354  : 	if (path[0] == '/' && strlen(path) == 2)

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR path$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	jne	SHORT $LN21@vfs_lsdir
	mov	rcx, QWORD PTR path$[rsp]
	call	strlen
	cmp	rax, 2
	jne	SHORT $LN21@vfs_lsdir

; 355  : 		found = true;

	mov	BYTE PTR found$[rsp], 1
$LN21@vfs_lsdir:
$LN20@vfs_lsdir:

; 356  : 
; 357  : 
; 358  : 	while (next) {

	cmp	QWORD PTR next$[rsp], 0
	je	$LN19@vfs_lsdir

; 359  : 		int i = 0;

	mov	DWORD PTR i$1[rsp], 0

; 360  : 	    char pathname[16];
; 361  : 		for (i = 0; i < 16; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN18@vfs_lsdir
$LN17@vfs_lsdir:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN18@vfs_lsdir:
	cmp	DWORD PTR i$1[rsp], 16
	jge	SHORT $LN16@vfs_lsdir

; 362  : 			if (next[i] == '/' || next[i] == '\0')

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	je	SHORT $LN14@vfs_lsdir
	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	jne	SHORT $LN15@vfs_lsdir
$LN14@vfs_lsdir:

; 363  : 				break;

	jmp	SHORT $LN16@vfs_lsdir
$LN15@vfs_lsdir:

; 364  : 			pathname[i] = next[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR next$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR pathname$7[rsp+rcx], al

; 365  : 		}

	jmp	SHORT $LN17@vfs_lsdir
$LN16@vfs_lsdir:

; 366  : 		pathname[i] = 0;

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	BYTE PTR pathname$7[rsp+rax], 0

; 367  : 
; 368  : 		for (int j = 0; j < ent->childs->pointer; j++) {

	mov	DWORD PTR j$2[rsp], 0
	jmp	SHORT $LN13@vfs_lsdir
$LN12@vfs_lsdir:
	mov	eax, DWORD PTR j$2[rsp]
	inc	eax
	mov	DWORD PTR j$2[rsp], eax
$LN13@vfs_lsdir:
	mov	rax, QWORD PTR ent$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR j$2[rsp], eax
	jae	SHORT $LN11@vfs_lsdir

; 369  : 			vfs_node_t *file_ = (vfs_node_t*)list_get_at(ent->childs, j);

	mov	edx, DWORD PTR j$2[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_get_at
	mov	QWORD PTR file_$4[rsp], rax

; 370  : 			entry_found = file_;

	mov	rax, QWORD PTR file_$4[rsp]
	mov	QWORD PTR entry_found$[rsp], rax

; 371  : 			if (strcmp(file_->filename, pathname) == 0) {

	mov	rax, QWORD PTR file_$4[rsp]
	lea	rdx, QWORD PTR pathname$7[rsp]
	mov	rcx, rax
	call	strcmp
	test	eax, eax
	jne	SHORT $LN10@vfs_lsdir

; 372  : 				if (file_->flags == FS_FLAG_DIRECTORY)

	mov	rax, QWORD PTR file_$4[rsp]
	movzx	eax, BYTE PTR [rax+48]
	cmp	eax, 2
	jne	SHORT $LN9@vfs_lsdir

; 373  : 					ent = (vfs_entry *)file_->device;

	mov	rax, QWORD PTR file_$4[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR ent$[rsp], rax
$LN9@vfs_lsdir:
$LN10@vfs_lsdir:

; 374  : 			}
; 375  : 		}

	jmp	SHORT $LN12@vfs_lsdir
$LN11@vfs_lsdir:

; 376  : 
; 377  : 		next = strchr(next + 1, '/');

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	edx, 47					; 0000002fH
	mov	rcx, rax
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 378  : 		if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN8@vfs_lsdir

; 379  : 			next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN8@vfs_lsdir:

; 380  : 	}

	jmp	$LN20@vfs_lsdir
$LN19@vfs_lsdir:

; 381  : 
; 382  : 	if (ent) {

	cmp	QWORD PTR ent$[rsp], 0
	je	$LN7@vfs_lsdir

; 383  : 		/* if this entry is a directory, recursively
; 384  : 		* call the node and check it */
; 385  : 		for (int i = 0; i < ent->childs->pointer; i++) {

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN6@vfs_lsdir
$LN5@vfs_lsdir:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN6@vfs_lsdir:
	mov	rax, QWORD PTR ent$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR i$3[rsp], eax
	jae	SHORT $LN4@vfs_lsdir

; 386  : 			vfs_node_t *f = (vfs_node_t*)list_get_at(ent->childs, i);

	mov	edx, DWORD PTR i$3[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_get_at
	mov	QWORD PTR f$6[rsp], rax

; 387  : 			char* type = 0;

	mov	QWORD PTR type$5[rsp], 0

; 388  : 			if (f->flags & FS_FLAG_DIRECTORY)

	mov	rax, QWORD PTR f$6[rsp]
	movzx	eax, BYTE PTR [rax+48]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN3@vfs_lsdir

; 389  : 				type = "Directory";

	lea	rax, OFFSET FLAT:$SG3729
	mov	QWORD PTR type$5[rsp], rax
	jmp	SHORT $LN2@vfs_lsdir
$LN3@vfs_lsdir:

; 390  : 			else if (f->flags & FS_FLAG_GENERAL)

	mov	rax, QWORD PTR f$6[rsp]
	movzx	eax, BYTE PTR [rax+48]
	and	eax, 4
	test	eax, eax
	je	SHORT $LN1@vfs_lsdir

; 391  : 				type = "File";

	lea	rax, OFFSET FLAT:$SG3732
	mov	QWORD PTR type$5[rsp], rax
$LN1@vfs_lsdir:
$LN2@vfs_lsdir:

; 392  : 			_debug_print_("%s -> %s \r\n",type, f->filename);

	mov	rax, QWORD PTR f$6[rsp]
	mov	r8, rax
	mov	rdx, QWORD PTR type$5[rsp]
	lea	rcx, OFFSET FLAT:$SG3733
	call	_debug_print_

; 393  : 		}

	jmp	$LN5@vfs_lsdir
$LN4@vfs_lsdir:
$LN7@vfs_lsdir:

; 394  : 		return;
; 395  : 	}
; 396  : }

	add	rsp, 120				; 00000078H
	ret	0
?vfs_lsdir@@YAXPEAD@Z ENDP				; vfs_lsdir
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
path$ = 48
vfs_remove_file PROC

; 198  : vfs_node_t* vfs_remove_file (char* path) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 199  : 	return vfs_unmount (path);

	mov	rcx, QWORD PTR path$[rsp]
	call	vfs_unmount

; 200  : }

	add	rsp, 40					; 00000028H
	ret	0
vfs_remove_file ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
i$1 = 32
next$ = 40
j$2 = 48
ent$ = 56
index$ = 64
file_$3 = 72
entry_found$ = 80
ret$ = 88
pathname$ = 96
fs_path$ = 112
path$ = 144
vfs_unmount PROC

; 147  : vfs_node_t* vfs_unmount (char *path) {

$LN19:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 136				; 00000088H

; 148  : 
; 149  : 	char* next = strchr(path, '/');

	mov	edx, 47					; 0000002fH
	mov	rcx, QWORD PTR path$[rsp]
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 150  : 	if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN16@vfs_unmoun

; 151  : 		next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN16@vfs_unmoun:

; 152  : 
; 153  : 	char* fs_path = next;

	mov	rax, QWORD PTR next$[rsp]
	mov	QWORD PTR fs_path$[rsp], rax

; 154  : 
; 155  : 	vfs_entry* ent = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR ent$[rsp], rax

; 156  : 	vfs_node_t* entry_found = 0;

	mov	QWORD PTR entry_found$[rsp], 0

; 157  : 	char pathname[16];
; 158  : 	int index = 0;

	mov	DWORD PTR index$[rsp], 0
$LN15@vfs_unmoun:

; 159  : 	while(next) {

	cmp	QWORD PTR next$[rsp], 0
	je	$LN14@vfs_unmoun

; 160  : 		int i = 0;

	mov	DWORD PTR i$1[rsp], 0

; 161  : 		for (i = 0; i < 16; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN13@vfs_unmoun
$LN12@vfs_unmoun:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN13@vfs_unmoun:
	cmp	DWORD PTR i$1[rsp], 16
	jge	SHORT $LN11@vfs_unmoun

; 162  : 			if (next[i] == '/' || next[i] == '\0')

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	je	SHORT $LN9@vfs_unmoun
	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	jne	SHORT $LN10@vfs_unmoun
$LN9@vfs_unmoun:

; 163  : 				break;

	jmp	SHORT $LN11@vfs_unmoun
$LN10@vfs_unmoun:

; 164  : 			pathname[i] = next[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR next$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR pathname$[rsp+rcx], al

; 165  : 		}

	jmp	SHORT $LN12@vfs_unmoun
$LN11@vfs_unmoun:

; 166  : 		pathname[i] = 0;

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	BYTE PTR pathname$[rsp+rax], 0

; 167  : 
; 168  : 		if (ent == NULL)

	cmp	QWORD PTR ent$[rsp], 0
	jne	SHORT $LN8@vfs_unmoun

; 169  : 			ent = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR ent$[rsp], rax
$LN8@vfs_unmoun:

; 170  : 
; 171  : 		for (int j = 0; j < ent->childs->pointer; j++) {

	mov	DWORD PTR j$2[rsp], 0
	jmp	SHORT $LN7@vfs_unmoun
$LN6@vfs_unmoun:
	mov	eax, DWORD PTR j$2[rsp]
	inc	eax
	mov	DWORD PTR j$2[rsp], eax
$LN7@vfs_unmoun:
	mov	rax, QWORD PTR ent$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR j$2[rsp], eax
	jae	SHORT $LN5@vfs_unmoun

; 172  : 			vfs_node_t *file_ = (vfs_node_t*)list_get_at(ent->childs, j);

	mov	edx, DWORD PTR j$2[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_get_at
	mov	QWORD PTR file_$3[rsp], rax

; 173  : 			if (strcmp(file_->filename, pathname) == 0) {

	mov	rax, QWORD PTR file_$3[rsp]
	lea	rdx, QWORD PTR pathname$[rsp]
	mov	rcx, rax
	call	strcmp
	test	eax, eax
	jne	SHORT $LN4@vfs_unmoun

; 174  : 				if (file_->flags & FS_FLAG_DIRECTORY)

	mov	rax, QWORD PTR file_$3[rsp]
	movzx	eax, BYTE PTR [rax+48]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN3@vfs_unmoun

; 175  : 					ent = (vfs_entry*)file_->device;

	mov	rax, QWORD PTR file_$3[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR ent$[rsp], rax
$LN3@vfs_unmoun:

; 176  : 				entry_found = file_;

	mov	rax, QWORD PTR file_$3[rsp]
	mov	QWORD PTR entry_found$[rsp], rax

; 177  : 				index = j;

	mov	eax, DWORD PTR j$2[rsp]
	mov	DWORD PTR index$[rsp], eax
$LN4@vfs_unmoun:

; 178  : 			}
; 179  : 		}

	jmp	SHORT $LN6@vfs_unmoun
$LN5@vfs_unmoun:

; 180  : 
; 181  : 		next = strchr(next + 1, '/');

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	edx, 47					; 0000002fH
	mov	rcx, rax
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 182  : 		if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN2@vfs_unmoun

; 183  : 			next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN2@vfs_unmoun:

; 184  : 	}

	jmp	$LN15@vfs_unmoun
$LN14@vfs_unmoun:

; 185  : 
; 186  : 	if (!entry_found) 

	cmp	QWORD PTR entry_found$[rsp], 0
	jne	SHORT $LN1@vfs_unmoun

; 187  : 		entry_found = root_dir->node;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR entry_found$[rsp], rax
$LN1@vfs_unmoun:

; 188  : 
; 189  : 	vfs_node_t* ret = (vfs_node_t*)list_remove (ent->childs, index);

	mov	edx, DWORD PTR index$[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_remove
	mov	QWORD PTR ret$[rsp], rax

; 190  : 	return ret;

	mov	rax, QWORD PTR ret$[rsp]

; 191  : }

	add	rsp, 136				; 00000088H
	ret	0
vfs_unmount ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
found$ = 32
i$1 = 36
next$ = 40
ent$ = 48
j$2 = 56
entry_found$ = 64
entry_$3 = 72
entryn$4 = 80
file_$5 = 88
pathname$6 = 96
path$ = 128
node$ = 136
dirnode$ = 144
vfs_mount PROC

; 272  : void vfs_mount (char *path, vfs_node_t *node, vfs_entry *dirnode) {

$LN23:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 120				; 00000078H

; 273  : 	if (path[0] == '/' && strlen(path) == 2) {

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR path$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	jne	SHORT $LN20@vfs_mount
	mov	rcx, QWORD PTR path$[rsp]
	call	strlen
	cmp	rax, 2
	jne	SHORT $LN20@vfs_mount

; 274  : 		vfs_entry *entry_ = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR entry_$3[rsp], rax

; 275  : 		if (entry_->node) {

	mov	rax, QWORD PTR entry_$3[rsp]
	cmp	QWORD PTR [rax], 0
	je	SHORT $LN19@vfs_mount

; 276  : 			_debug_print_ ("[VFS]: Mounting filesystem to root failed, already in use\n");

	lea	rcx, OFFSET FLAT:$SG3652
	call	_debug_print_

; 277  : 			return;   //Already a root filesystem is present

	jmp	$LN21@vfs_mount
$LN19@vfs_mount:

; 278  : 		}
; 279  : 		entry_->node = node; //else mount

	mov	rax, QWORD PTR entry_$3[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax], rcx

; 280  : 		return;

	jmp	$LN21@vfs_mount
$LN20@vfs_mount:

; 281  : 	}
; 282  : 
; 283  : 	//! seeking else? other mount points
; 284  : 	//! /home/manas
; 285  : 	char* next = strchr(path,'/');

	mov	edx, 47					; 0000002fH
	mov	rcx, QWORD PTR path$[rsp]
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 286  : 	if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN18@vfs_mount

; 287  : 		next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN18@vfs_mount:

; 288  : 	
; 289  : 	vfs_entry *ent = dirnode;

	mov	rax, QWORD PTR dirnode$[rsp]
	mov	QWORD PTR ent$[rsp], rax

; 290  : 	bool found = false;

	mov	BYTE PTR found$[rsp], 0

; 291  : 	vfs_node_t *entry_found = 0;

	mov	QWORD PTR entry_found$[rsp], 0
$LN17@vfs_mount:

; 292  : 	while (next) {

	cmp	QWORD PTR next$[rsp], 0
	je	$LN16@vfs_mount

; 293  : 		int i = 0;

	mov	DWORD PTR i$1[rsp], 0

; 294  : 		char pathname[16];
; 295  : 		for (i = 0; i < 16; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN15@vfs_mount
$LN14@vfs_mount:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN15@vfs_mount:
	cmp	DWORD PTR i$1[rsp], 16
	jge	SHORT $LN13@vfs_mount

; 296  : 			if ( next[i] == '/'  || next[i] == '\0')

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	je	SHORT $LN11@vfs_mount
	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	jne	SHORT $LN12@vfs_mount
$LN11@vfs_mount:

; 297  : 				break;

	jmp	SHORT $LN13@vfs_mount
$LN12@vfs_mount:

; 298  : 			pathname[i] = next[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR next$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR pathname$6[rsp+rcx], al

; 299  : 		}

	jmp	SHORT $LN14@vfs_mount
$LN13@vfs_mount:

; 300  : 		pathname[i] = 0;

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	BYTE PTR pathname$6[rsp+rax], 0

; 301  : 
; 302  : 		if (ent == NULL)

	cmp	QWORD PTR ent$[rsp], 0
	jne	SHORT $LN10@vfs_mount

; 303  : 			ent = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR ent$[rsp], rax
$LN10@vfs_mount:

; 304  : 
; 305  : 		for (int j = 0; j < ent->childs->pointer; j++) {

	mov	DWORD PTR j$2[rsp], 0
	jmp	SHORT $LN9@vfs_mount
$LN8@vfs_mount:
	mov	eax, DWORD PTR j$2[rsp]
	inc	eax
	mov	DWORD PTR j$2[rsp], eax
$LN9@vfs_mount:
	mov	rax, QWORD PTR ent$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR j$2[rsp], eax
	jae	SHORT $LN7@vfs_mount

; 306  : 			vfs_node_t *file_ = (vfs_node_t*)list_get_at(ent->childs, j);

	mov	edx, DWORD PTR j$2[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_get_at
	mov	QWORD PTR file_$5[rsp], rax

; 307  : 			if (strcmp(file_->filename, pathname)==0) {

	mov	rax, QWORD PTR file_$5[rsp]
	lea	rdx, QWORD PTR pathname$6[rsp]
	mov	rcx, rax
	call	strcmp
	test	eax, eax
	jne	SHORT $LN6@vfs_mount

; 308  : 				entry_found = file_;

	mov	rax, QWORD PTR file_$5[rsp]
	mov	QWORD PTR entry_found$[rsp], rax

; 309  : 				found = true;

	mov	BYTE PTR found$[rsp], 1
$LN6@vfs_mount:

; 310  : 			}
; 311  : 		}

	jmp	SHORT $LN8@vfs_mount
$LN7@vfs_mount:

; 312  : 
; 313  : 		next = strchr (next + 1, '/'); 

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	edx, 47					; 0000002fH
	mov	rcx, rax
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 314  : 		if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN5@vfs_mount

; 315  : 			next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN5@vfs_mount:

; 316  : 	}

	jmp	$LN17@vfs_mount
$LN16@vfs_mount:

; 317  : 
; 318  : 	if (found) {

	movzx	eax, BYTE PTR found$[rsp]
	test	eax, eax
	je	SHORT $LN4@vfs_mount

; 319  : 		if (entry_found->flags == FS_FLAG_DIRECTORY) {

	mov	rax, QWORD PTR entry_found$[rsp]
	movzx	eax, BYTE PTR [rax+48]
	cmp	eax, 2
	jne	SHORT $LN3@vfs_mount

; 320  : 			ent = (vfs_entry*)entry_found->device;

	mov	rax, QWORD PTR entry_found$[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR ent$[rsp], rax

; 321  : 			_debug_print_ ("Recursively calling for -> %s \r\n", path);

	mov	rdx, QWORD PTR path$[rsp]
	lea	rcx, OFFSET FLAT:$SG3680
	call	_debug_print_

; 322  : 			vfs_mount(path,node,ent);

	mov	r8, QWORD PTR ent$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	mov	rcx, QWORD PTR path$[rsp]
	call	vfs_mount
$LN3@vfs_mount:

; 323  : 		}
; 324  : 		_debug_print_ ("[vfs]: already mounted -> %s \r\n", path);

	mov	rdx, QWORD PTR path$[rsp]
	lea	rcx, OFFSET FLAT:$SG3681
	call	_debug_print_

; 325  : 		return;

	jmp	$LN21@vfs_mount
$LN4@vfs_mount:

; 326  : 	}
; 327  : 
; 328  : 	if (!found) {

	movzx	eax, BYTE PTR found$[rsp]
	test	eax, eax
	jne	$LN2@vfs_mount

; 329  : 		_debug_print_ ("Not found entry -> %s \r\n", path);

	mov	rdx, QWORD PTR path$[rsp]
	lea	rcx, OFFSET FLAT:$SG3683
	call	_debug_print_

; 330  : 		if (entry_found) {

	cmp	QWORD PTR entry_found$[rsp], 0
	je	SHORT $LN1@vfs_mount

; 331  : 			_debug_print_ ("Mounting path -> %s, creating entry \r\n", path);

	mov	rdx, QWORD PTR path$[rsp]
	lea	rcx, OFFSET FLAT:$SG3685
	call	_debug_print_

; 332  : 			vfs_entry* entryn = vfs_mkentry();

	call	vfs_mkentry
	mov	QWORD PTR entryn$4[rsp], rax

; 333  : 			_debug_print_ ("Entry created -> %x \r\n", entryn);

	mov	rdx, QWORD PTR entryn$4[rsp]
	lea	rcx, OFFSET FLAT:$SG3687
	call	_debug_print_

; 334  : 			vfs_mkdir(path,node,entryn);

	mov	r8, QWORD PTR entryn$4[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	mov	rcx, QWORD PTR path$[rsp]
	call	vfs_mkdir
$LN1@vfs_mount:

; 335  : 		}
; 336  : 		_debug_print_ ("Ent->child -> %x %x nodes-> %d \r\n", ent->childs, node, sizeof(vfs_node_t));

	mov	r9d, 112				; 00000070H
	mov	r8, QWORD PTR node$[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rdx, QWORD PTR [rax+8]
	lea	rcx, OFFSET FLAT:$SG3689
	call	_debug_print_

; 337  : 		list_add(ent->childs, node);

	mov	rdx, QWORD PTR node$[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_add

; 338  : 		_debug_print_ ("List added %x \r\n", ent->childs);

	mov	rax, QWORD PTR ent$[rsp]
	mov	rdx, QWORD PTR [rax+8]
	lea	rcx, OFFSET FLAT:$SG3690
	call	_debug_print_
$LN2@vfs_mount:
$LN21@vfs_mount:

; 339  : 	}
; 340  : 	
; 341  : }

	add	rsp, 120				; 00000078H
	ret	0
vfs_mount ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
ent$ = 32
vfs_mkentry PROC

; 259  : vfs_entry * vfs_mkentry() {

$LN3:
	sub	rsp, 56					; 00000038H

; 260  : 	vfs_entry* ent = (vfs_entry*)malloc(sizeof(vfs_entry));

	mov	ecx, 16
	call	malloc
	mov	QWORD PTR ent$[rsp], rax

; 261  : 	ent->node = 0;

	mov	rax, QWORD PTR ent$[rsp]
	mov	QWORD PTR [rax], 0

; 262  : 	ent->childs = initialize_list();

	call	initialize_list
	mov	rcx, QWORD PTR ent$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 263  : 	return ent;

	mov	rax, QWORD PTR ent$[rsp]

; 264  : }

	add	rsp, 56					; 00000038H
	ret	0
vfs_mkentry ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
found$ = 32
i$1 = 36
j$2 = 40
next$ = 48
ent$ = 56
file_$3 = 64
entry_found$ = 72
pathname$ = 80
path$ = 112
dir$ = 120
dir_node$ = 128
vfs_mkdir PROC

; 207  : void vfs_mkdir (char* path, vfs_node_t* dir, vfs_entry* dir_node) {

$LN20:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 208  : 	dir->device = dir_node;

	mov	rax, QWORD PTR dir$[rsp]
	mov	rcx, QWORD PTR dir_node$[rsp]
	mov	QWORD PTR [rax+56], rcx

; 209  : 	bool found = false;

	mov	BYTE PTR found$[rsp], 0

; 210  : 	char* next = strchr(path, '/');

	mov	edx, 47					; 0000002fH
	mov	rcx, QWORD PTR path$[rsp]
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 211  : 	if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN17@vfs_mkdir

; 212  : 		next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN17@vfs_mkdir:

; 213  : 
; 214  : 	vfs_entry* ent = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR ent$[rsp], rax

; 215  : 	vfs_node_t* entry_found = 0;

	mov	QWORD PTR entry_found$[rsp], 0
$LN16@vfs_mkdir:

; 216  : 	char pathname[16];
; 217  : 	
; 218  : 	while(next) {

	cmp	QWORD PTR next$[rsp], 0
	je	$LN15@vfs_mkdir

; 219  : 		int i = 0;

	mov	DWORD PTR i$1[rsp], 0

; 220  : 
; 221  : 		for (i = 0; i < 16; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN14@vfs_mkdir
$LN13@vfs_mkdir:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN14@vfs_mkdir:
	cmp	DWORD PTR i$1[rsp], 16
	jge	SHORT $LN12@vfs_mkdir

; 222  : 			if (next[i] == '/' || next[i] == '\0')

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	je	SHORT $LN10@vfs_mkdir
	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	jne	SHORT $LN11@vfs_mkdir
$LN10@vfs_mkdir:

; 223  : 				break;

	jmp	SHORT $LN12@vfs_mkdir
$LN11@vfs_mkdir:

; 224  : 			pathname[i] = next[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR next$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR pathname$[rsp+rcx], al

; 225  : 		}

	jmp	SHORT $LN13@vfs_mkdir
$LN12@vfs_mkdir:

; 226  : 		pathname[i] = 0;

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	BYTE PTR pathname$[rsp+rax], 0

; 227  : 
; 228  : 		if (ent == NULL)

	cmp	QWORD PTR ent$[rsp], 0
	jne	SHORT $LN9@vfs_mkdir

; 229  : 			ent = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR ent$[rsp], rax
$LN9@vfs_mkdir:

; 230  : 
; 231  : 		for (int j = 0; j < ent->childs->pointer; j++) {

	mov	DWORD PTR j$2[rsp], 0
	jmp	SHORT $LN8@vfs_mkdir
$LN7@vfs_mkdir:
	mov	eax, DWORD PTR j$2[rsp]
	inc	eax
	mov	DWORD PTR j$2[rsp], eax
$LN8@vfs_mkdir:
	mov	rax, QWORD PTR ent$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR j$2[rsp], eax
	jae	SHORT $LN6@vfs_mkdir

; 232  : 			vfs_node_t* file_ = (vfs_node_t*)list_get_at(ent->childs, j);

	mov	edx, DWORD PTR j$2[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_get_at
	mov	QWORD PTR file_$3[rsp], rax

; 233  : 			if (strcmp(file_->filename, pathname) == 0) {

	mov	rax, QWORD PTR file_$3[rsp]
	lea	rdx, QWORD PTR pathname$[rsp]
	mov	rcx, rax
	call	strcmp
	test	eax, eax
	jne	SHORT $LN5@vfs_mkdir

; 234  : 				if (file_->flags == FS_FLAG_DIRECTORY)

	mov	rax, QWORD PTR file_$3[rsp]
	movzx	eax, BYTE PTR [rax+48]
	cmp	eax, 2
	jne	SHORT $LN4@vfs_mkdir

; 235  : 					ent = (vfs_entry *)file_->device;

	mov	rax, QWORD PTR file_$3[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR ent$[rsp], rax
$LN4@vfs_mkdir:

; 236  : 				found = true;

	mov	BYTE PTR found$[rsp], 1

; 237  : 				entry_found = file_;

	mov	rax, QWORD PTR file_$3[rsp]
	mov	QWORD PTR entry_found$[rsp], rax
$LN5@vfs_mkdir:

; 238  : 			}
; 239  : 		}

	jmp	SHORT $LN7@vfs_mkdir
$LN6@vfs_mkdir:

; 240  : 
; 241  : 		next = strchr(next + 1, '/');

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	edx, 47					; 0000002fH
	mov	rcx, rax
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 242  : 		if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN3@vfs_mkdir

; 243  : 			next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN3@vfs_mkdir:

; 244  : 	}

	jmp	$LN16@vfs_mkdir
$LN15@vfs_mkdir:

; 245  : 
; 246  : 	strcpy(dir->filename, pathname);

	mov	rax, QWORD PTR dir$[rsp]
	lea	rdx, QWORD PTR pathname$[rsp]
	mov	rcx, rax
	call	strcpy

; 247  : 	if (found) {

	movzx	eax, BYTE PTR found$[rsp]
	test	eax, eax
	je	SHORT $LN2@vfs_mkdir

; 248  : 		/* if this entry is a directory, recursively
; 249  : 		* call the node and check it */
; 250  : 		list_add(ent->childs, dir);

	mov	rdx, QWORD PTR dir$[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_add

; 251  : 		return;

	jmp	SHORT $LN18@vfs_mkdir
$LN2@vfs_mkdir:

; 252  : 	}
; 253  : 	if (!found) {

	movzx	eax, BYTE PTR found$[rsp]
	test	eax, eax
	jne	SHORT $LN1@vfs_mkdir

; 254  : 		list_add(ent->childs, dir);

	mov	rdx, QWORD PTR dir$[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_add
$LN1@vfs_mkdir:
$LN18@vfs_mkdir:

; 255  : 		return;
; 256  : 	}		
; 257  : }

	add	rsp, 104				; 00000068H
	ret	0
vfs_mkdir ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
i$1 = 32
next$ = 40
j$2 = 48
ent$ = 56
file_$3 = 64
entry_found$ = 72
entry_$4 = 80
pathname$ = 88
fs_path$ = 104
path$ = 128
?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z PROC		; vfs_finddir

; 92   : vfs_node_t* vfs_finddir (char *path) {

$LN20:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 120				; 00000078H

; 93   : 	if (path[0] == '/' && strlen(path) == 2) {

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR path$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	jne	SHORT $LN17@vfs_finddi
	mov	rcx, QWORD PTR path$[rsp]
	call	strlen
	cmp	rax, 2
	jne	SHORT $LN17@vfs_finddi

; 94   : 		vfs_entry *entry_ = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR entry_$4[rsp], rax

; 95   : 		return entry_->node;

	mov	rax, QWORD PTR entry_$4[rsp]
	mov	rax, QWORD PTR [rax]
	jmp	$LN18@vfs_finddi
$LN17@vfs_finddi:

; 96   : 	}
; 97   : 
; 98   : 
; 99   : 	char* next = strchr(path, '/');

	mov	edx, 47					; 0000002fH
	mov	rcx, QWORD PTR path$[rsp]
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 100  : 	if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN16@vfs_finddi

; 101  : 		next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN16@vfs_finddi:

; 102  : 
; 103  : 	char* fs_path = next;

	mov	rax, QWORD PTR next$[rsp]
	mov	QWORD PTR fs_path$[rsp], rax

; 104  : 
; 105  : 	vfs_entry* ent = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR ent$[rsp], rax

; 106  : 	vfs_node_t* entry_found = 0;

	mov	QWORD PTR entry_found$[rsp], 0
$LN15@vfs_finddi:

; 107  : 	char pathname[16];
; 108  : 
; 109  : 	while(next) {

	cmp	QWORD PTR next$[rsp], 0
	je	$LN14@vfs_finddi

; 110  : 		int i = 0;

	mov	DWORD PTR i$1[rsp], 0

; 111  : 		for (i = 0; i < 16; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN13@vfs_finddi
$LN12@vfs_finddi:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN13@vfs_finddi:
	cmp	DWORD PTR i$1[rsp], 16
	jge	SHORT $LN11@vfs_finddi

; 112  : 			if (next[i] == '/' || next[i] == '\0')

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 47					; 0000002fH
	je	SHORT $LN9@vfs_finddi
	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR next$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	jne	SHORT $LN10@vfs_finddi
$LN9@vfs_finddi:

; 113  : 				break;

	jmp	SHORT $LN11@vfs_finddi
$LN10@vfs_finddi:

; 114  : 			pathname[i] = next[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR next$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR pathname$[rsp+rcx], al

; 115  : 		}

	jmp	SHORT $LN12@vfs_finddi
$LN11@vfs_finddi:

; 116  : 		pathname[i] = 0;

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	BYTE PTR pathname$[rsp+rax], 0

; 117  : 
; 118  : 		if (ent == NULL)

	cmp	QWORD PTR ent$[rsp], 0
	jne	SHORT $LN8@vfs_finddi

; 119  : 			ent = root_dir;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	QWORD PTR ent$[rsp], rax
$LN8@vfs_finddi:

; 120  : 
; 121  : 		for (int j = 0; j < ent->childs->pointer; j++) {

	mov	DWORD PTR j$2[rsp], 0
	jmp	SHORT $LN7@vfs_finddi
$LN6@vfs_finddi:
	mov	eax, DWORD PTR j$2[rsp]
	inc	eax
	mov	DWORD PTR j$2[rsp], eax
$LN7@vfs_finddi:
	mov	rax, QWORD PTR ent$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR j$2[rsp], eax
	jae	SHORT $LN5@vfs_finddi

; 122  : 			vfs_node_t *file_ = (vfs_node_t*)list_get_at(ent->childs, j);

	mov	edx, DWORD PTR j$2[rsp]
	mov	rax, QWORD PTR ent$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	list_get_at
	mov	QWORD PTR file_$3[rsp], rax

; 123  : 			if (strcmp(file_->filename, pathname) == 0) {

	mov	rax, QWORD PTR file_$3[rsp]
	lea	rdx, QWORD PTR pathname$[rsp]
	mov	rcx, rax
	call	strcmp
	test	eax, eax
	jne	SHORT $LN4@vfs_finddi

; 124  : 				if (file_->flags == FS_FLAG_DIRECTORY)

	mov	rax, QWORD PTR file_$3[rsp]
	movzx	eax, BYTE PTR [rax+48]
	cmp	eax, 2
	jne	SHORT $LN3@vfs_finddi

; 125  : 					ent = (vfs_entry*)file_->device;

	mov	rax, QWORD PTR file_$3[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR ent$[rsp], rax
$LN3@vfs_finddi:

; 126  : 				entry_found = file_;

	mov	rax, QWORD PTR file_$3[rsp]
	mov	QWORD PTR entry_found$[rsp], rax
$LN4@vfs_finddi:

; 127  : 			}
; 128  : 		}

	jmp	SHORT $LN6@vfs_finddi
$LN5@vfs_finddi:

; 129  : 
; 130  : 		next = strchr(next + 1, '/');

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	edx, 47					; 0000002fH
	mov	rcx, rax
	call	strchr
	mov	QWORD PTR next$[rsp], rax

; 131  : 		if (next)

	cmp	QWORD PTR next$[rsp], 0
	je	SHORT $LN2@vfs_finddi

; 132  : 			next++;

	mov	rax, QWORD PTR next$[rsp]
	inc	rax
	mov	QWORD PTR next$[rsp], rax
$LN2@vfs_finddi:

; 133  : 	}

	jmp	$LN15@vfs_finddi
$LN14@vfs_finddi:

; 134  : 
; 135  : 	if (!entry_found) 

	cmp	QWORD PTR entry_found$[rsp], 0
	jne	SHORT $LN1@vfs_finddi

; 136  : 		entry_found = root_dir->node;

	mov	rax, QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA ; root_dir
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR entry_found$[rsp], rax
$LN1@vfs_finddi:

; 137  : 
; 138  : 	return entry_found;

	mov	rax, QWORD PTR entry_found$[rsp]
$LN18@vfs_finddi:

; 139  : }

	add	rsp, 120				; 00000078H
	ret	0
?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z ENDP		; vfs_finddir
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\vfs.cpp
_TEXT	SEGMENT
root$ = 32
?AuVFSInit@@YAXXZ PROC					; AuVFSInit

; 75   : void AuVFSInit () {

$LN3:
	sub	rsp, 56					; 00000038H

; 76   : 	vfs_entry *root = (vfs_entry*)malloc(sizeof(vfs_entry));

	mov	ecx, 16
	call	malloc
	mov	QWORD PTR root$[rsp], rax

; 77   : 	root->node = 0;

	mov	rax, QWORD PTR root$[rsp]
	mov	QWORD PTR [rax], 0

; 78   : 	root->childs = initialize_list();

	call	initialize_list
	mov	rcx, QWORD PTR root$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 79   : 	root_dir = root;

	mov	rax, QWORD PTR root$[rsp]
	mov	QWORD PTR ?root_dir@@3PEAU_vfs_entry_@@EA, rax ; root_dir

; 80   : 
; 81   : 
; 82   : 	//! Initialize the root file system
; 83   : 	initialize_fat32();

	call	?initialize_fat32@@YAXXZ		; initialize_fat32

; 84   : 	fat32_self_register();

	call	?fat32_self_register@@YAXXZ		; fat32_self_register

; 85   : 
; 86   : 	//! Initialize the device file system
; 87   : 	devfs_mount();

	call	?devfs_mount@@YAXXZ			; devfs_mount

; 88   : 
; 89   : 
; 90   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuVFSInit@@YAXXZ ENDP					; AuVFSInit
_TEXT	ENDS
END
