; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3189	DB	'dev', 00H
$SG3191	DB	'/dev', 00H
CONST	ENDS
PUBLIC	?devfs_mount@@YAXXZ				; devfs_mount
EXTRN	strcpy:PROC
EXTRN	memset:PROC
EXTRN	vfs_mkdir:PROC
EXTRN	vfs_mkentry:PROC
EXTRN	malloc:PROC
pdata	SEGMENT
$pdata$?devfs_mount@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+103
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
ent$ = 40
?devfs_mount@@YAXXZ PROC				; devfs_mount

; 16   : void devfs_mount () {

$LN3:
	sub	rsp, 56					; 00000038H

; 17   : 	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 104				; 00000068H
	call	malloc
	mov	QWORD PTR node$[rsp], rax

; 18   : 	memset(node, 0, sizeof(vfs_node_t));

	mov	r8d, 104				; 00000068H
	xor	edx, edx
	mov	rcx, QWORD PTR node$[rsp]
	call	memset

; 19   : 	strcpy(node->filename, "dev");

	mov	rax, QWORD PTR node$[rsp]
	lea	rdx, OFFSET FLAT:$SG3189
	mov	rcx, rax
	call	strcpy

; 20   : 	node->flags = FS_FLAG_DIRECTORY;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+48], 2

; 21   : 
; 22   : 	vfs_entry *ent = vfs_mkentry();

	call	vfs_mkentry
	mov	QWORD PTR ent$[rsp], rax

; 23   : 	vfs_mkdir("/dev", node, ent);

	mov	r8, QWORD PTR ent$[rsp]
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:$SG3191
	call	vfs_mkdir

; 24   : }

	add	rsp, 56					; 00000038H
	ret	0
?devfs_mount@@YAXXZ ENDP				; devfs_mount
_TEXT	ENDS
END
