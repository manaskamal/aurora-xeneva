; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG2963	DB	'dev', 00H
$SG2964	DB	'/dev', 00H
CONST	ENDS
PUBLIC	?devfs_mount@@YAXXZ				; devfs_mount
EXTRN	?strcpy@@YAPEADPEADPEBD@Z:PROC			; strcpy
EXTRN	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z:PROC	; vfs_mount
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
pdata	SEGMENT
$pdata$?devfs_mount@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+198
	DD	imagerel $unwind$?devfs_mount@@YAXXZ
pdata	ENDS
xdata	SEGMENT
$unwind$?devfs_mount@@YAXXZ DD 010401H
	DD	06204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\devfs.cpp
_TEXT	SEGMENT
node$ = 32
?devfs_mount@@YAXXZ PROC				; devfs_mount

; 16   : void devfs_mount () {

$LN3:
	sub	rsp, 56					; 00000038H

; 17   : 	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 104				; 00000068H
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR node$[rsp], rax

; 18   : 	strcpy(node->filename, "dev");

	mov	rax, QWORD PTR node$[rsp]
	lea	rdx, OFFSET FLAT:$SG2963
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 19   : 	node->size = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+32], 0

; 20   : 	node->eof = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+36], 0

; 21   : 	node->pos = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+40], 0

; 22   : 	node->current = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+44], 0

; 23   : 	node->flags = FS_FLAG_DIRECTORY;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+48], 1

; 24   : 	node->status = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+52], 0

; 25   : 	node->open = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+64], 0

; 26   : 	node->read = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+72], 0

; 27   : 	node->write = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+80], 0

; 28   : 	node->read_blk = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+88], 0

; 29   : 	node->ioquery = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+96], 0

; 30   : 	vfs_mount ("/dev", node);

	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:$SG2964
	call	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z	; vfs_mount

; 31   : }

	add	rsp, 56					; 00000038H
	ret	0
?devfs_mount@@YAXXZ ENDP				; devfs_mount
_TEXT	ENDS
END
