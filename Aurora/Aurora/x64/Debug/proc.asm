; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_BSS	SEGMENT
user_stack_index DD 01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG3630	DB	'Executable image not found', 0aH, 00H
CONST	ENDS
PUBLIC	?create_process@@YAXPEBDPEADE@Z			; create_process
PUBLIC	?create_user_stack@@YAPEA_KPEA_K@Z		; create_user_stack
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?map_page_ex@@YA_NPEA_K_K1@Z:PROC		; map_page_ex
EXTRN	?create_user_address_space@@YAPEA_KXZ:PROC	; create_user_address_space
EXTRN	?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z:PROC ; create_user_thread
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?open@@YA?AU_file_@@PEBD@Z:PROC			; open
EXTRN	?read_blk@@YAXPEAU_file_@@PEAE@Z:PROC		; read_blk
EXTRN	?load_pe_file@@YAXPEAEH@Z:PROC			; load_pe_file
EXTRN	?get_entry_point@@YAP6AXPEAX@ZXZ:PROC		; get_entry_point
EXTRN	?get_image_base@@YA_KXZ:PROC			; get_image_base
EXTRN	?create_mutex@@YAPEAUmutex_t@@XZ:PROC		; create_mutex
EXTRN	?mutex_lock@@YAXPEAUmutex_t@@@Z:PROC		; mutex_lock
EXTRN	?mutex_unlock@@YAXPEAUmutex_t@@@Z:PROC		; mutex_unlock
_BSS	SEGMENT
	ALIGN	8

process_mutex DQ 01H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?create_process@@YAXPEBDPEADE@Z DD imagerel $LN6
	DD	imagerel $LN6+501
	DD	imagerel $unwind$?create_process@@YAXPEBDPEADE@Z
pdata	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$??__Eprocess_mutex@@YAXXZ DD imagerel ??__Eprocess_mutex@@YAXXZ
	DD	imagerel ??__Eprocess_mutex@@YAXXZ+21
	DD	imagerel $unwind$??__Eprocess_mutex@@YAXXZ
pdata	ENDS
pdata	SEGMENT
$pdata$?create_user_stack@@YAPEA_KPEA_K@Z DD imagerel $LN6
	DD	imagerel $LN6+162
	DD	imagerel $unwind$?create_user_stack@@YAPEA_KPEA_K@Z
pdata	ENDS
CRT$XCU	SEGMENT
process_mutex$initializer$ DQ FLAT:??__Eprocess_mutex@@YAXXZ
CRT$XCU	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$??__Eprocess_mutex@@YAXXZ DD 010401H
	DD	04204H
xdata	ENDS
xdata	SEGMENT
$unwind$?create_process@@YAXPEBDPEADE@Z DD 041801H
	DD	0290118H
	DD	060107011H
$unwind$?create_user_stack@@YAPEA_KPEA_K@Z DD 010901H
	DD	08209H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\proc.cpp
_TEXT	SEGMENT
i$1 = 32
location$ = 40
tv71 = 48
cr3$ = 80
?create_user_stack@@YAPEA_KPEA_K@Z PROC			; create_user_stack

; 21   : uint64_t *create_user_stack (uint64_t* cr3) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 22   : 
; 23   : #define USER_STACK 0x0000700000000000
; 24   : 	uint64_t location = USER_STACK + user_stack_index;

	movsxd	rax, DWORD PTR user_stack_index
	mov	rcx, 123145302310912			; 0000700000000000H
	add	rax, rcx
	mov	QWORD PTR location$[rsp], rax

; 25   : 	
; 26   : 	/* 1 mb stack / process */
; 27   : 	for (int i=0; i < 0x100000/4096; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@create_use
$LN2@create_use:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@create_use:
	cmp	DWORD PTR i$1[rsp], 256			; 00000100H
	jge	SHORT $LN1@create_use

; 28   : 		map_page_ex(cr3,(uint64_t)pmmngr_alloc(),location + i * 4096);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR location$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tv71[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rcx, QWORD PTR tv71[rsp]
	mov	r8, rcx
	mov	rdx, rax
	mov	rcx, QWORD PTR cr3$[rsp]
	call	?map_page_ex@@YA_NPEA_K_K1@Z		; map_page_ex

; 29   : 	}

	jmp	SHORT $LN2@create_use
$LN1@create_use:

; 30   : 
; 31   : 	user_stack_index += 0x100000;

	mov	eax, DWORD PTR user_stack_index
	add	eax, 1048576				; 00100000H
	mov	DWORD PTR user_stack_index, eax

; 32   : 	return (uint64_t*)(USER_STACK +  user_stack_index);

	movsxd	rax, DWORD PTR user_stack_index
	mov	rcx, 123145302310912			; 0000700000000000H
	add	rax, rcx

; 33   : }

	add	rsp, 72					; 00000048H
	ret	0
?create_user_stack@@YAPEA_KPEA_K@Z ENDP			; create_user_stack
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\proc.cpp
;	COMDAT ??__Eprocess_mutex@@YAXXZ
text$yc	SEGMENT
??__Eprocess_mutex@@YAXXZ PROC				; `dynamic initializer for 'process_mutex'', COMDAT

; 18   : static mutex_t *process_mutex = create_mutex();

	sub	rsp, 40					; 00000028H
	call	?create_mutex@@YAPEAUmutex_t@@XZ	; create_mutex
	mov	QWORD PTR process_mutex, rax
	add	rsp, 40					; 00000028H
	ret	0
??__Eprocess_mutex@@YAXXZ ENDP				; `dynamic initializer for 'process_mutex''
text$yc	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\proc.cpp
_TEXT	SEGMENT
position$ = 48
process$ = 56
cr3$ = 64
buf$ = 72
_image_base_$ = 80
block$1 = 88
stack$ = 96
t$ = 104
ent$ = 112
file$ = 120
$T2 = 184
$T3 = 248
filename$ = 352
procname$ = 360
priority$ = 368
?create_process@@YAXPEBDPEADE@Z PROC			; create_process

; 37   : void create_process(const char* filename, char* procname, uint8_t priority) {

$LN6:
	mov	BYTE PTR [rsp+24], r8b
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 328				; 00000148H

; 38   : 
; 39   : 	mutex_lock (process_mutex);

	mov	rcx, QWORD PTR process_mutex
	call	?mutex_lock@@YAXPEAUmutex_t@@@Z		; mutex_lock

; 40   : 	//!allocate a data-structure for process 
; 41   : 	process_t *process = (process_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR process$[rsp], rax

; 42   : 
; 43   : 	//!open the process file-binary
; 44   : 	FILE file = open(filename);

	mov	rdx, QWORD PTR filename$[rsp]
	lea	rcx, QWORD PTR $T3[rsp]
	call	?open@@YA?AU_file_@@PEBD@Z		; open
	lea	rcx, QWORD PTR $T2[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 60					; 0000003cH
	rep movsb
	lea	rax, QWORD PTR file$[rsp]
	lea	rcx, QWORD PTR $T2[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 60					; 0000003cH
	rep movsb

; 45   : 	if (file.status == FILE_FLAG_INVALID) {

	cmp	DWORD PTR file$[rsp+56], 3
	jne	SHORT $LN3@create_pro

; 46   : 		printf("Executable image not found\n");

	lea	rcx, OFFSET FLAT:$SG3630
	call	?printf@@YAXPEBDZZ			; printf

; 47   : 		return;

	jmp	$LN4@create_pro
$LN3@create_pro:

; 48   : 	}
; 49   : 	//!open the binary file and read it
; 50   : 	unsigned char* buf = (unsigned char*)pmmngr_alloc();   //18*1024

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR buf$[rsp], rax

; 51   : 	read_blk(&file,buf);

	mov	rdx, QWORD PTR buf$[rsp]
	lea	rcx, QWORD PTR file$[rsp]
	call	?read_blk@@YAXPEAU_file_@@PEAE@Z	; read_blk

; 52   : 	
; 53   : 	//!extract the informations
; 54   :     load_pe_file(buf,file.size);

	mov	edx, DWORD PTR file$[rsp+36]
	mov	rcx, QWORD PTR buf$[rsp]
	call	?load_pe_file@@YAXPEAEH@Z		; load_pe_file

; 55   : 	ientry ent = get_entry_point();

	call	?get_entry_point@@YAP6AXPEAX@ZXZ	; get_entry_point
	mov	QWORD PTR ent$[rsp], rax

; 56   : 	uint64_t _image_base_ = (uint64_t)get_image_base();

	call	?get_image_base@@YA_KXZ			; get_image_base
	mov	QWORD PTR _image_base_$[rsp], rax

; 57   : 	
; 58   : 	//! create the user stack and address space
; 59   : 	
; 60   :     uint64_t *cr3 = create_user_address_space();

	call	?create_user_address_space@@YAPEA_KXZ	; create_user_address_space
	mov	QWORD PTR cr3$[rsp], rax

; 61   : 	uint64_t stack = (uint64_t)create_user_stack(cr3);

	mov	rcx, QWORD PTR cr3$[rsp]
	call	?create_user_stack@@YAPEA_KPEA_K@Z	; create_user_stack
	mov	QWORD PTR stack$[rsp], rax

; 62   : 	map_page_ex(cr3,(uint64_t)buf,_image_base_);

	mov	r8, QWORD PTR _image_base_$[rsp]
	mov	rdx, QWORD PTR buf$[rsp]
	mov	rcx, QWORD PTR cr3$[rsp]
	call	?map_page_ex@@YA_NPEA_K_K1@Z		; map_page_ex

; 63   : 
; 64   : 	//! read rest of the image
; 65   : 	int position = 1;  //we already read 4096 bytes at first

	mov	DWORD PTR position$[rsp], 1
$LN2@create_pro:

; 66   : 	while(file.eof != 1){

	cmp	DWORD PTR file$[rsp+40], 1
	je	SHORT $LN1@create_pro

; 67   : 		unsigned char* block = (unsigned char*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR block$1[rsp], rax

; 68   : 		read_blk(&file,block);

	mov	rdx, QWORD PTR block$1[rsp]
	lea	rcx, QWORD PTR file$[rsp]
	call	?read_blk@@YAXPEAU_file_@@PEAE@Z	; read_blk

; 69   : 		map_page_ex(cr3,(uint64_t)block,_image_base_ + position * 4096);

	mov	eax, DWORD PTR position$[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR _image_base_$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8, rax
	mov	rdx, QWORD PTR block$1[rsp]
	mov	rcx, QWORD PTR cr3$[rsp]
	call	?map_page_ex@@YA_NPEA_K_K1@Z		; map_page_ex

; 70   : 		position++;

	mov	eax, DWORD PTR position$[rsp]
	inc	eax
	mov	DWORD PTR position$[rsp], eax

; 71   : 	}

	jmp	SHORT $LN2@create_pro
$LN1@create_pro:

; 72   : 
; 73   : 	//!allocate current process
; 74   : 	process->name = procname;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR procname$[rsp]
	mov	QWORD PTR [rax], rcx

; 75   : 	process->entry_point = ent;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR ent$[rsp]
	mov	QWORD PTR [rax+8], rcx

; 76   : 
; 77   : 	process->cr3 = cr3;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR cr3$[rsp]
	mov	QWORD PTR [rax+32], rcx

; 78   : 	process->image_base = _image_base_;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR _image_base_$[rsp]
	mov	QWORD PTR [rax+40], rcx

; 79   : 	process->stack = stack;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR stack$[rsp]
	mov	QWORD PTR [rax+48], rcx

; 80   : 
; 81   : 	//! Create and thread and start scheduling when scheduler starts */
; 82   : 	thread_t *t = create_user_thread(process->entry_point,stack,(uint64_t)cr3,procname,priority);

	movzx	eax, BYTE PTR priority$[rsp]
	mov	BYTE PTR [rsp+32], al
	mov	r9, QWORD PTR procname$[rsp]
	mov	r8, QWORD PTR cr3$[rsp]
	mov	rdx, QWORD PTR stack$[rsp]
	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z ; create_user_thread
	mov	QWORD PTR t$[rsp], rax

; 83   : 	//! add the process to process manager
; 84   : 	process->thread_data_pointer = t;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+16], rcx

; 85   :    // process_manager_add_process(process);
; 86   : 	mutex_unlock (process_mutex);

	mov	rcx, QWORD PTR process_mutex
	call	?mutex_unlock@@YAXPEAUmutex_t@@@Z	; mutex_unlock
$LN4@create_pro:

; 87   : 
; 88   : }

	add	rsp, 328				; 00000148H
	pop	rdi
	pop	rsi
	ret	0
?create_process@@YAXPEBDPEADE@Z ENDP			; create_process
_TEXT	ENDS
END
