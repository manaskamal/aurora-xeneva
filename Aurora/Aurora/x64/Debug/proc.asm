; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?process_head@@3PEAU_process_@@EA		; process_head
PUBLIC	?process_last@@3PEAU_process_@@EA		; process_last
_BSS	SEGMENT
user_stack_index DD 01H DUP (?)
	ALIGN	8

?process_head@@3PEAU_process_@@EA DQ 01H DUP (?)	; process_head
?process_last@@3PEAU_process_@@EA DQ 01H DUP (?)	; process_last
_BSS	ENDS
CONST	SEGMENT
$SG3675	DB	'Executable image not found', 0aH, 00H
	ORG $+4
$SG3704	DB	'Process for child created -> %s', 0aH, 00H
CONST	ENDS
PUBLIC	?create_user_stack@@YAPEA_KPEA_K@Z		; create_user_stack
PUBLIC	?create_process@@YAXPEBDPEADE@Z			; create_process
PUBLIC	?kill_process@@YAXXZ				; kill_process
PUBLIC	?add_process@@YAXPEAU_process_@@@Z		; add_process
PUBLIC	?remove_process@@YAXPEAU_process_@@@Z		; remove_process
PUBLIC	?find_process_by_thread@@YAPEAU_process_@@PEAU_thread_@@@Z ; find_process_by_thread
PUBLIC	??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?pmmngr_free@@YAXPEAX@Z:PROC			; pmmngr_free
EXTRN	x64_cli:PROC
EXTRN	?map_page_ex@@YA_NPEA_K_K1@Z:PROC		; map_page_ex
EXTRN	?create_user_address_space@@YAPEA_KXZ:PROC	; create_user_address_space
EXTRN	?unmap_page@@YAX_K@Z:PROC			; unmap_page
EXTRN	?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z:PROC ; create_user_thread
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
EXTRN	?task_delete@@YAXPEAU_thread_@@@Z:PROC		; task_delete
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?open@@YA?AU_file_@@PEBD@Z:PROC			; open
EXTRN	?read_blk@@YAXPEAU_file_@@PEAE@Z:PROC		; read_blk
EXTRN	?load_pe_file@@YAXPEAEH@Z:PROC			; load_pe_file
EXTRN	?create_mutex@@YAPEAUmutex_t@@XZ:PROC		; create_mutex
_BSS	SEGMENT
process_mutex DQ 01H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?create_user_stack@@YAPEA_KPEA_K@Z DD imagerel $LN6
	DD	imagerel $LN6+162
	DD	imagerel $unwind$?create_user_stack@@YAPEA_KPEA_K@Z
$pdata$?create_process@@YAXPEBDPEADE@Z DD imagerel $LN6
	DD	imagerel $LN6+591
	DD	imagerel $unwind$?create_process@@YAXPEBDPEADE@Z
$pdata$?kill_process@@YAXXZ DD imagerel $LN9
	DD	imagerel $LN9+239
	DD	imagerel $unwind$?kill_process@@YAXXZ
pdata	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$??__Eprocess_mutex@@YAXXZ DD imagerel ??__Eprocess_mutex@@YAXXZ
	DD	imagerel ??__Eprocess_mutex@@YAXXZ+21
	DD	imagerel $unwind$??__Eprocess_mutex@@YAXXZ
pdata	ENDS
pdata	SEGMENT
$pdata$?remove_process@@YAXPEAU_process_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+146
	DD	imagerel $unwind$?remove_process@@YAXPEAU_process_@@@Z
$pdata$?find_process_by_thread@@YAPEAU_process_@@PEAU_thread_@@@Z DD imagerel $LN7
	DD	imagerel $LN7+69
	DD	imagerel $unwind$?find_process_by_thread@@YAPEAU_process_@@PEAU_thread_@@@Z
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
$unwind$?create_user_stack@@YAPEA_KPEA_K@Z DD 010901H
	DD	08209H
$unwind$?create_process@@YAXPEBDPEADE@Z DD 041801H
	DD	02b0118H
	DD	060107011H
$unwind$?kill_process@@YAXXZ DD 010401H
	DD	0a204H
$unwind$?remove_process@@YAXPEAU_process_@@@Z DD 010901H
	DD	04209H
$unwind$?find_process_by_thread@@YAPEAU_process_@@PEAU_thread_@@@Z DD 010901H
	DD	02209H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z PROC ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>, COMDAT

; 182  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 183  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 184  : 	}

	ret	0
??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z ENDP ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\proc.cpp
_TEXT	SEGMENT
proc$1 = 0
thread$ = 32
?find_process_by_thread@@YAPEAU_process_@@PEAU_thread_@@@Z PROC ; find_process_by_thread

; 61   : process_t *find_process_by_thread (thread_t *thread) {

$LN7:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 62   : 	for (process_t *proc = process_head; proc != NULL; proc = proc->next) {

	mov	rax, QWORD PTR ?process_head@@3PEAU_process_@@EA ; process_head
	mov	QWORD PTR proc$1[rsp], rax
	jmp	SHORT $LN4@find_proce
$LN3@find_proce:
	mov	rax, QWORD PTR proc$1[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR proc$1[rsp], rax
$LN4@find_proce:
	cmp	QWORD PTR proc$1[rsp], 0
	je	SHORT $LN2@find_proce

; 63   : 		if (proc->thread_data_pointer == thread) {

	mov	rax, QWORD PTR proc$1[rsp]
	mov	rcx, QWORD PTR thread$[rsp]
	cmp	QWORD PTR [rax+16], rcx
	jne	SHORT $LN1@find_proce

; 64   : 			return proc;

	mov	rax, QWORD PTR proc$1[rsp]
	jmp	SHORT $LN5@find_proce
$LN1@find_proce:

; 65   : 		}
; 66   : 	}

	jmp	SHORT $LN3@find_proce
$LN2@find_proce:
$LN5@find_proce:

; 67   : }

	add	rsp, 24
	ret	0
?find_process_by_thread@@YAPEAU_process_@@PEAU_thread_@@@Z ENDP ; find_process_by_thread
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\proc.cpp
_TEXT	SEGMENT
proc$ = 48
?remove_process@@YAXPEAU_process_@@@Z PROC		; remove_process

; 39   : void remove_process (process_t *proc) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 40   : 	
; 41   : 	if (process_head == NULL)

	cmp	QWORD PTR ?process_head@@3PEAU_process_@@EA, 0 ; process_head
	jne	SHORT $LN5@remove_pro

; 42   : 		return;

	jmp	SHORT $LN6@remove_pro
$LN5@remove_pro:

; 43   : 
; 44   : 	if (proc == process_head) {

	mov	rax, QWORD PTR ?process_head@@3PEAU_process_@@EA ; process_head
	cmp	QWORD PTR proc$[rsp], rax
	jne	SHORT $LN4@remove_pro

; 45   : 		process_head = process_head->next;

	mov	rax, QWORD PTR ?process_head@@3PEAU_process_@@EA ; process_head
	mov	rax, QWORD PTR [rax+56]
	mov	QWORD PTR ?process_head@@3PEAU_process_@@EA, rax ; process_head

; 46   : 	} else {

	jmp	SHORT $LN3@remove_pro
$LN4@remove_pro:

; 47   : 		proc->prev->next = proc->next;

	mov	rax, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rax+64]
	mov	rcx, QWORD PTR proc$[rsp]
	mov	rcx, QWORD PTR [rcx+56]
	mov	QWORD PTR [rax+56], rcx
$LN3@remove_pro:

; 48   : 	}
; 49   : 
; 50   : 	if (proc == process_last) {

	mov	rax, QWORD PTR ?process_last@@3PEAU_process_@@EA ; process_last
	cmp	QWORD PTR proc$[rsp], rax
	jne	SHORT $LN2@remove_pro

; 51   : 		process_last = proc->prev;

	mov	rax, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rax+64]
	mov	QWORD PTR ?process_last@@3PEAU_process_@@EA, rax ; process_last

; 52   : 	} else {

	jmp	SHORT $LN1@remove_pro
$LN2@remove_pro:

; 53   : 		proc->next->prev = proc->prev;

	mov	rax, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rax+56]
	mov	rcx, QWORD PTR proc$[rsp]
	mov	rcx, QWORD PTR [rcx+64]
	mov	QWORD PTR [rax+64], rcx
$LN1@remove_pro:

; 54   : 	}
; 55   : 
; 56   : 	pmmngr_free (proc);

	mov	rcx, QWORD PTR proc$[rsp]
	call	?pmmngr_free@@YAXPEAX@Z			; pmmngr_free
$LN6@remove_pro:

; 57   : }

	add	rsp, 40					; 00000028H
	ret	0
?remove_process@@YAXPEAU_process_@@@Z ENDP		; remove_process
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\proc.cpp
_TEXT	SEGMENT
proc$ = 8
?add_process@@YAXPEAU_process_@@@Z PROC			; add_process

; 23   : void add_process (process_t *proc) {

	mov	QWORD PTR [rsp+8], rcx

; 24   : 
; 25   : 	proc->next = NULL;

	mov	rax, QWORD PTR proc$[rsp]
	mov	QWORD PTR [rax+56], 0

; 26   : 	proc->prev = NULL;

	mov	rax, QWORD PTR proc$[rsp]
	mov	QWORD PTR [rax+64], 0

; 27   : 
; 28   : 	if (process_head == NULL) {

	cmp	QWORD PTR ?process_head@@3PEAU_process_@@EA, 0 ; process_head
	jne	SHORT $LN2@add_proces

; 29   : 		process_head = proc;

	mov	rax, QWORD PTR proc$[rsp]
	mov	QWORD PTR ?process_head@@3PEAU_process_@@EA, rax ; process_head

; 30   : 		process_last = proc;

	mov	rax, QWORD PTR proc$[rsp]
	mov	QWORD PTR ?process_last@@3PEAU_process_@@EA, rax ; process_last

; 31   : 	} else {

	jmp	SHORT $LN1@add_proces
$LN2@add_proces:

; 32   : 		process_last->next = proc;

	mov	rax, QWORD PTR ?process_last@@3PEAU_process_@@EA ; process_last
	mov	rcx, QWORD PTR proc$[rsp]
	mov	QWORD PTR [rax+56], rcx

; 33   : 		proc->prev = process_last;

	mov	rax, QWORD PTR proc$[rsp]
	mov	rcx, QWORD PTR ?process_last@@3PEAU_process_@@EA ; process_last
	mov	QWORD PTR [rax+64], rcx

; 34   : 		process_last = proc;

	mov	rax, QWORD PTR proc$[rsp]
	mov	QWORD PTR ?process_last@@3PEAU_process_@@EA, rax ; process_last
$LN1@add_proces:

; 35   : 	}
; 36   : }

	fatret	0
?add_process@@YAXPEAU_process_@@@Z ENDP			; add_process
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
i$1 = 32
i$2 = 36
proc$ = 40
remove_thread$ = 48
init_stack$ = 56
tv76 = 64
virtual_addr$3 = 72
?kill_process@@YAXXZ PROC				; kill_process

; 146  : void kill_process () {

$LN9:
	sub	rsp, 88					; 00000058H

; 147  : 	x64_cli();

	call	x64_cli

; 148  : 	thread_t * remove_thread = get_current_thread();

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	QWORD PTR remove_thread$[rsp], rax

; 149  : 	process_t *proc = find_process_by_thread (remove_thread);

	mov	rcx, QWORD PTR remove_thread$[rsp]
	call	?find_process_by_thread@@YAPEAU_process_@@PEAU_thread_@@@Z ; find_process_by_thread
	mov	QWORD PTR proc$[rsp], rax

; 150  : 	uint64_t  init_stack = proc->stack - 0x100000;

	mov	rax, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rax+48]
	sub	rax, 1048576				; 00100000H
	mov	QWORD PTR init_stack$[rsp], rax

; 151  : 	for (int i = 0; i < 0x100000 / 256; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN6@kill_proce
$LN5@kill_proce:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN6@kill_proce:
	cmp	DWORD PTR i$1[rsp], 4096		; 00001000H
	jge	SHORT $LN4@kill_proce

; 152  : 		unmap_page (init_stack + i * 4096);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR init_stack$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, rax
	call	?unmap_page@@YAX_K@Z			; unmap_page

; 153  : 	}

	jmp	SHORT $LN5@kill_proce
$LN4@kill_proce:

; 154  : 
; 155  : 	for (int i = 0; i < proc->image_size / 4096; i++) {

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN3@kill_proce
$LN2@kill_proce:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN3@kill_proce:
	movsxd	rax, DWORD PTR i$2[rsp]
	mov	QWORD PTR tv76[rsp], rax
	xor	edx, edx
	mov	rcx, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rcx+24]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	rcx, QWORD PTR tv76[rsp]
	cmp	rcx, rax
	jae	SHORT $LN1@kill_proce

; 156  : 		uint64_t virtual_addr = proc->image_base + (i * 4096);

	mov	eax, DWORD PTR i$2[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR proc$[rsp]
	add	rax, QWORD PTR [rcx+40]
	mov	QWORD PTR virtual_addr$3[rsp], rax

; 157  : 		unmap_page (virtual_addr);

	mov	rcx, QWORD PTR virtual_addr$3[rsp]
	call	?unmap_page@@YAX_K@Z			; unmap_page

; 158  : 	}

	jmp	SHORT $LN2@kill_proce
$LN1@kill_proce:

; 159  : 
; 160  : 	remove_process (proc);

	mov	rcx, QWORD PTR proc$[rsp]
	call	?remove_process@@YAXPEAU_process_@@@Z	; remove_process

; 161  : 	task_delete (remove_thread);

	mov	rcx, QWORD PTR remove_thread$[rsp]
	call	?task_delete@@YAXPEAU_thread_@@@Z	; task_delete

; 162  : }

	add	rsp, 88					; 00000058H
	ret	0
?kill_process@@YAXXZ ENDP				; kill_process
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\proc.cpp
_TEXT	SEGMENT
process$ = 48
position$ = 56
cr3$ = 64
nt$ = 72
buf$ = 80
_image_base_$ = 88
dos$ = 96
block$1 = 104
stack$ = 112
t$ = 120
ent$ = 128
file$ = 136
$T2 = 200
$T3 = 264
filename$ = 368
procname$ = 376
priority$ = 384
?create_process@@YAXPEBDPEADE@Z PROC			; create_process

; 86   : void create_process(const char* filename, char* procname, uint8_t priority) {

$LN6:
	mov	BYTE PTR [rsp+24], r8b
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 344				; 00000158H

; 87   : 
; 88   : 	//mutex_lock (process_mutex);
; 89   : 	//!allocate a data-structure for process 
; 90   : 	process_t *process = (process_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR process$[rsp], rax

; 91   : 
; 92   : 	//!open the process file-binary
; 93   : 	FILE file = open(filename);

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

; 94   : 	if (file.status == FILE_FLAG_INVALID) {

	cmp	DWORD PTR file$[rsp+56], 3
	jne	SHORT $LN3@create_pro

; 95   : 		printf("Executable image not found\n");

	lea	rcx, OFFSET FLAT:$SG3675
	call	?printf@@YAXPEBDZZ			; printf

; 96   : 		return;

	jmp	$LN4@create_pro
$LN3@create_pro:

; 97   : 	}
; 98   : 	//!open the binary file and read it
; 99   : 	unsigned char* buf = (unsigned char*)pmmngr_alloc();   //18*1024

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR buf$[rsp], rax

; 100  : 	read_blk(&file,buf);

	mov	rdx, QWORD PTR buf$[rsp]
	lea	rcx, QWORD PTR file$[rsp]
	call	?read_blk@@YAXPEAU_file_@@PEAE@Z	; read_blk

; 101  : 	
; 102  : 	IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)buf;

	mov	rax, QWORD PTR buf$[rsp]
	mov	QWORD PTR dos$[rsp], rax

; 103  : 	PIMAGE_NT_HEADERS nt = raw_offset<PIMAGE_NT_HEADERS>(dos, dos->e_lfanew);

	mov	rax, QWORD PTR dos$[rsp]
	movzx	eax, WORD PTR [rax+60]
	mov	edx, eax
	mov	rcx, QWORD PTR dos$[rsp]
	call	??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>
	mov	QWORD PTR nt$[rsp], rax

; 104  : 	//!extract the informations
; 105  :     load_pe_file(buf,file.size);

	mov	edx, DWORD PTR file$[rsp+36]
	mov	rcx, QWORD PTR buf$[rsp]
	call	?load_pe_file@@YAXPEAEH@Z		; load_pe_file

; 106  : 	uint64_t _image_base_ = nt->OptionalHeader.ImageBase;

	mov	rax, QWORD PTR nt$[rsp]
	mov	rax, QWORD PTR [rax+48]
	mov	QWORD PTR _image_base_$[rsp], rax

; 107  : 	ientry ent = (ientry)(nt->OptionalHeader.AddressOfEntryPoint + nt->OptionalHeader.ImageBase); //buffer

	mov	rax, QWORD PTR nt$[rsp]
	mov	eax, DWORD PTR [rax+40]
	mov	rcx, QWORD PTR nt$[rsp]
	add	rax, QWORD PTR [rcx+48]
	mov	QWORD PTR ent$[rsp], rax

; 108  : 	//ientry ent = get_entry_point();
; 109  : 	//printf ("size pf address for process -> %s is -> %x\n", procname, dos->e_magic);
; 110  : 	//uint64_t _image_base_ = (uint64_t)get_image_base();
; 111  : 	
; 112  : 	//! create the user stack and address space
; 113  : 	
; 114  :     uint64_t *cr3 = create_user_address_space();

	call	?create_user_address_space@@YAPEA_KXZ	; create_user_address_space
	mov	QWORD PTR cr3$[rsp], rax

; 115  : 	uint64_t stack = (uint64_t)create_user_stack(cr3);

	mov	rcx, QWORD PTR cr3$[rsp]
	call	?create_user_stack@@YAPEA_KPEA_K@Z	; create_user_stack
	mov	QWORD PTR stack$[rsp], rax

; 116  : 	map_page_ex(cr3,(uint64_t)buf,_image_base_);

	mov	r8, QWORD PTR _image_base_$[rsp]
	mov	rdx, QWORD PTR buf$[rsp]
	mov	rcx, QWORD PTR cr3$[rsp]
	call	?map_page_ex@@YA_NPEA_K_K1@Z		; map_page_ex

; 117  : 
; 118  : 	//! read rest of the image
; 119  : 	int position = 1;  //we already read 4096 bytes at first

	mov	DWORD PTR position$[rsp], 1
$LN2@create_pro:

; 120  : 	while(file.eof != 1){

	cmp	DWORD PTR file$[rsp+40], 1
	je	SHORT $LN1@create_pro

; 121  : 		unsigned char* block = (unsigned char*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR block$1[rsp], rax

; 122  : 		read_blk(&file,block);

	mov	rdx, QWORD PTR block$1[rsp]
	lea	rcx, QWORD PTR file$[rsp]
	call	?read_blk@@YAXPEAU_file_@@PEAE@Z	; read_blk

; 123  : 		map_page_ex(cr3,(uint64_t)block,_image_base_ + position * 4096);

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

; 124  : 		position++;

	mov	eax, DWORD PTR position$[rsp]
	inc	eax
	mov	DWORD PTR position$[rsp], eax

; 125  : 	}

	jmp	SHORT $LN2@create_pro
$LN1@create_pro:

; 126  : 
; 127  : 	//!allocate current process
; 128  : 	process->name = procname;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR procname$[rsp]
	mov	QWORD PTR [rax], rcx

; 129  : 	process->entry_point = ent;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR ent$[rsp]
	mov	QWORD PTR [rax+8], rcx

; 130  : 
; 131  : 	process->cr3 = cr3;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR cr3$[rsp]
	mov	QWORD PTR [rax+32], rcx

; 132  : 	process->image_base = _image_base_;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR _image_base_$[rsp]
	mov	QWORD PTR [rax+40], rcx

; 133  : 	process->stack = stack;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR stack$[rsp]
	mov	QWORD PTR [rax+48], rcx

; 134  : 	process->image_size = nt->OptionalHeader.SizeOfImage;

	mov	rax, QWORD PTR nt$[rsp]
	mov	eax, DWORD PTR [rax+80]
	mov	rcx, QWORD PTR process$[rsp]
	mov	QWORD PTR [rcx+24], rax

; 135  : 	//! Create and thread and start scheduling when scheduler starts */
; 136  : 	thread_t *t = create_user_thread(process->entry_point,stack,(uint64_t)cr3,procname,priority);

	movzx	eax, BYTE PTR priority$[rsp]
	mov	BYTE PTR [rsp+32], al
	mov	r9, QWORD PTR procname$[rsp]
	mov	r8, QWORD PTR cr3$[rsp]
	mov	rdx, QWORD PTR stack$[rsp]
	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z ; create_user_thread
	mov	QWORD PTR t$[rsp], rax

; 137  : 	printf ("Process for child created -> %s\n", procname);

	mov	rdx, QWORD PTR procname$[rsp]
	lea	rcx, OFFSET FLAT:$SG3704
	call	?printf@@YAXPEBDZZ			; printf

; 138  : 	//! add the process to process manager
; 139  : 	process->thread_data_pointer = t;

	mov	rax, QWORD PTR process$[rsp]
	mov	rcx, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+16], rcx

; 140  :     add_process(process);

	mov	rcx, QWORD PTR process$[rsp]
	call	?add_process@@YAXPEAU_process_@@@Z	; add_process
$LN4@create_pro:

; 141  : 	//mutex_unlock (process_mutex);
; 142  : 
; 143  : }

	add	rsp, 344				; 00000158H
	pop	rdi
	pop	rsi
	ret	0
?create_process@@YAXPEBDPEADE@Z ENDP			; create_process
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\proc.cpp
_TEXT	SEGMENT
i$1 = 32
location$ = 40
tv71 = 48
cr3$ = 80
?create_user_stack@@YAPEA_KPEA_K@Z PROC			; create_user_stack

; 70   : uint64_t *create_user_stack (uint64_t* cr3) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 71   : 
; 72   : #define USER_STACK 0x0000700000000000
; 73   : 	uint64_t location = USER_STACK + user_stack_index;

	movsxd	rax, DWORD PTR user_stack_index
	mov	rcx, 123145302310912			; 0000700000000000H
	add	rax, rcx
	mov	QWORD PTR location$[rsp], rax

; 74   : 	
; 75   : 	/* 1 mb stack / process */
; 76   : 	for (int i=0; i < 0x100000/4096; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@create_use
$LN2@create_use:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@create_use:
	cmp	DWORD PTR i$1[rsp], 256			; 00000100H
	jge	SHORT $LN1@create_use

; 77   : 		map_page_ex(cr3,(uint64_t)pmmngr_alloc(),location + i * 4096);

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

; 78   : 	}

	jmp	SHORT $LN2@create_use
$LN1@create_use:

; 79   : 
; 80   : 	user_stack_index += 0x100000;

	mov	eax, DWORD PTR user_stack_index
	add	eax, 1048576				; 00100000H
	mov	DWORD PTR user_stack_index, eax

; 81   : 	return (uint64_t*)(USER_STACK +  user_stack_index);

	movsxd	rax, DWORD PTR user_stack_index
	mov	rcx, 123145302310912			; 0000700000000000H
	add	rax, rcx

; 82   : }

	add	rsp, 72					; 00000048H
	ret	0
?create_user_stack@@YAPEA_KPEA_K@Z ENDP			; create_user_stack
_TEXT	ENDS
END
