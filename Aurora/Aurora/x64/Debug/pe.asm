; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?ent@@3P6AXPEAX@ZEA				; ent
PUBLIC	?image_base@@3_KA				; image_base
_BSS	SEGMENT
?ent@@3P6AXPEAX@ZEA DQ 01H DUP (?)			; ent
?image_base@@3_KA DQ 01H DUP (?)			; image_base
_BSS	ENDS
CONST	SEGMENT
$SG3307	DB	'Import table va -> %d, size -> %d ', 0aH, 00H
	ORG $+4
$SG3308	DB	'Import table va -> %d, size -> %d ', 0aH, 00H
CONST	ENDS
PUBLIC	?load_pe_file@@YAXPEA_KH@Z			; load_pe_file
PUBLIC	?get_entry_point@@YAP6AXPEAX@ZXZ		; get_entry_point
PUBLIC	?get_image_base@@YA_KXZ				; get_image_base
PUBLIC	?GetProcAddress@@YAPEAXPEAXPEBD@Z		; GetProcAddress
PUBLIC	??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>
PUBLIC	??$raw_offset@PEAU_IMAGE_EXPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_EXPORT_DIRECTORY@@PEAXH@Z ; raw_offset<_IMAGE_EXPORT_DIRECTORY * __ptr64,void * __ptr64>
PUBLIC	??$raw_offset@PEAIPEAX@@YAPEAIPEAXH@Z		; raw_offset<unsigned int * __ptr64,void * __ptr64>
PUBLIC	??$raw_offset@PEAGPEAX@@YAPEAGPEAXH@Z		; raw_offset<unsigned short * __ptr64,void * __ptr64>
PUBLIC	??$raw_offset@PEADPEAX@@YAPEADPEAXH@Z		; raw_offset<char * __ptr64,void * __ptr64>
PUBLIC	??$raw_offset@PEAXPEAX@@YAPEAXPEAXH@Z		; raw_offset<void * __ptr64,void * __ptr64>
PUBLIC	?LinkLibrary@@YAXPEAX0@Z			; LinkLibrary
PUBLIC	??$raw_offset@PEAU_IMAGE_IMPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_IMPORT_DIRECTORY@@PEAXH@Z ; raw_offset<_IMAGE_IMPORT_DIRECTORY * __ptr64,void * __ptr64>
PUBLIC	??$raw_offset@PEBDPEAX@@YAPEBDPEAXH@Z		; raw_offset<char const * __ptr64,void * __ptr64>
PUBLIC	??$raw_offset@PEA_KPEAX@@YAPEA_KPEAXH@Z		; raw_offset<unsigned __int64 * __ptr64,void * __ptr64>
PUBLIC	??$raw_offset@PEAU_IMAGE_IMPORT_HINT_TABLE@@PEAX@@YAPEAU_IMAGE_IMPORT_HINT_TABLE@@PEAXH@Z ; raw_offset<_IMAGE_IMPORT_HINT_TABLE * __ptr64,void * __ptr64>
EXTRN	?strcmp@@YAHPEBD0@Z:PROC			; strcmp
EXTRN	printf:PROC
pdata	SEGMENT
$pdata$?load_pe_file@@YAXPEA_KH@Z DD imagerel $LN3
	DD	imagerel $LN3+94
	DD	imagerel $unwind$?load_pe_file@@YAXPEA_KH@Z
$pdata$?GetProcAddress@@YAPEAXPEAXPEBD@Z DD imagerel $LN10
	DD	imagerel $LN10+386
	DD	imagerel $unwind$?GetProcAddress@@YAPEAXPEAXPEBD@Z
$pdata$?LinkLibrary@@YAXPEAX0@Z DD imagerel $LN11
	DD	imagerel $LN11+441
	DD	imagerel $unwind$?LinkLibrary@@YAXPEAX0@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?load_pe_file@@YAXPEA_KH@Z DD 010d01H
	DD	0620dH
$unwind$?GetProcAddress@@YAPEAXPEAXPEBD@Z DD 010e01H
	DD	0e20eH
$unwind$?LinkLibrary@@YAXPEAX0@Z DD 010e01H
	DD	0e20eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEAU_IMAGE_IMPORT_HINT_TABLE@@PEAX@@YAPEAU_IMAGE_IMPORT_HINT_TABLE@@PEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEAU_IMAGE_IMPORT_HINT_TABLE@@PEAX@@YAPEAU_IMAGE_IMPORT_HINT_TABLE@@PEAXH@Z PROC ; raw_offset<_IMAGE_IMPORT_HINT_TABLE * __ptr64,void * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEAU_IMAGE_IMPORT_HINT_TABLE@@PEAX@@YAPEAU_IMAGE_IMPORT_HINT_TABLE@@PEAXH@Z ENDP ; raw_offset<_IMAGE_IMPORT_HINT_TABLE * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEA_KPEAX@@YAPEA_KPEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEA_KPEAX@@YAPEA_KPEAXH@Z PROC		; raw_offset<unsigned __int64 * __ptr64,void * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEA_KPEAX@@YAPEA_KPEAXH@Z ENDP		; raw_offset<unsigned __int64 * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEBDPEAX@@YAPEBDPEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEBDPEAX@@YAPEBDPEAXH@Z PROC		; raw_offset<char const * __ptr64,void * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEBDPEAX@@YAPEBDPEAXH@Z ENDP		; raw_offset<char const * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEAU_IMAGE_IMPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_IMPORT_DIRECTORY@@PEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEAU_IMAGE_IMPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_IMPORT_DIRECTORY@@PEAXH@Z PROC ; raw_offset<_IMAGE_IMPORT_DIRECTORY * __ptr64,void * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEAU_IMAGE_IMPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_IMPORT_DIRECTORY@@PEAXH@Z ENDP ; raw_offset<_IMAGE_IMPORT_DIRECTORY * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pe.cpp
_TEXT	SEGMENT
datadir$ = 32
n$1 = 40
iat$2 = 48
importdir$ = 56
dos_header$ = 64
nt_headers$ = 72
fname$3 = 80
procaddr$4 = 88
hint$5 = 96
func$6 = 104
image$ = 128
exporter$ = 136
?LinkLibrary@@YAXPEAX0@Z PROC				; LinkLibrary

; 82   : void LinkLibrary (void* image, void *exporter) {

$LN11:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 120				; 00000078H

; 83   : 	PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)image;

	mov	rax, QWORD PTR image$[rsp]
	mov	QWORD PTR dos_header$[rsp], rax

; 84   : 	PIMAGE_NT_HEADERS nt_headers = raw_offset<PIMAGE_NT_HEADERS>(dos_header, dos_header->e_lfanew);

	mov	rax, QWORD PTR dos_header$[rsp]
	movzx	eax, WORD PTR [rax+60]
	mov	edx, eax
	mov	rcx, QWORD PTR dos_header$[rsp]
	call	??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>
	mov	QWORD PTR nt_headers$[rsp], rax

; 85   : 	if (IMAGE_DATA_DIRECTORY_IMPORT + 1 > nt_headers->OptionalHeader.NumberOfRvaAndSizes)

	mov	rax, QWORD PTR nt_headers$[rsp]
	cmp	DWORD PTR [rax+132], 2
	jae	SHORT $LN8@LinkLibrar

; 86   : 		return;

	jmp	$LN9@LinkLibrar
$LN8@LinkLibrar:

; 87   : 	IMAGE_DATA_DIRECTORY& datadir = nt_headers->OptionalHeader.DataDirectory[IMAGE_DATA_DIRECTORY_IMPORT];

	mov	eax, 8
	imul	rax, 1
	mov	rcx, QWORD PTR nt_headers$[rsp]
	lea	rax, QWORD PTR [rcx+rax+136]
	mov	QWORD PTR datadir$[rsp], rax

; 88   : 	if (datadir.VirtualAddress == 0 || datadir.Size == 0) {

	mov	rax, QWORD PTR datadir$[rsp]
	cmp	DWORD PTR [rax], 0
	je	SHORT $LN6@LinkLibrar
	mov	rax, QWORD PTR datadir$[rsp]
	cmp	DWORD PTR [rax+4], 0
	jne	SHORT $LN7@LinkLibrar
$LN6@LinkLibrar:

; 89   : 		printf ("Import table va -> %d, size -> %d \n", datadir.VirtualAddress, datadir.Size);

	mov	rax, QWORD PTR datadir$[rsp]
	mov	r8d, DWORD PTR [rax+4]
	mov	rax, QWORD PTR datadir$[rsp]
	mov	edx, DWORD PTR [rax]
	lea	rcx, OFFSET FLAT:$SG3307
	call	printf

; 90   : 		return;

	jmp	$LN9@LinkLibrar
$LN7@LinkLibrar:

; 91   : 	}
; 92   : 	printf ("Import table va -> %d, size -> %d \n", datadir.VirtualAddress, datadir.Size);

	mov	rax, QWORD PTR datadir$[rsp]
	mov	r8d, DWORD PTR [rax+4]
	mov	rax, QWORD PTR datadir$[rsp]
	mov	edx, DWORD PTR [rax]
	lea	rcx, OFFSET FLAT:$SG3308
	call	printf

; 93   : 	PIMAGE_IMPORT_DIRECTORY importdir = raw_offset<PIMAGE_IMPORT_DIRECTORY>(image, datadir.VirtualAddress);

	mov	rax, QWORD PTR datadir$[rsp]
	mov	edx, DWORD PTR [rax]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEAU_IMAGE_IMPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_IMPORT_DIRECTORY@@PEAXH@Z ; raw_offset<_IMAGE_IMPORT_DIRECTORY * __ptr64,void * __ptr64>
	mov	QWORD PTR importdir$[rsp], rax

; 94   : 	for (size_t n = 0; importdir[n].ThunkTableRva; ++n) {

	mov	QWORD PTR n$1[rsp], 0
	jmp	SHORT $LN5@LinkLibrar
$LN4@LinkLibrar:
	mov	rax, QWORD PTR n$1[rsp]
	inc	rax
	mov	QWORD PTR n$1[rsp], rax
$LN5@LinkLibrar:
	mov	rax, QWORD PTR n$1[rsp]
	imul	rax, 20
	mov	rcx, QWORD PTR importdir$[rsp]
	cmp	DWORD PTR [rcx+rax+16], 0
	je	$LN3@LinkLibrar

; 95   : 		const char* func = raw_offset<const char*>(image, importdir[n].NameRva);

	mov	rax, QWORD PTR n$1[rsp]
	imul	rax, 20
	mov	rcx, QWORD PTR importdir$[rsp]
	mov	edx, DWORD PTR [rcx+rax+12]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEBDPEAX@@YAPEBDPEAXH@Z	; raw_offset<char const * __ptr64,void * __ptr64>
	mov	QWORD PTR func$6[rsp], rax

; 96   : 		PIMAGE_IMPORT_LOOKUP_TABLE_PE32P iat = raw_offset<PIMAGE_IMPORT_LOOKUP_TABLE_PE32P>(image, importdir[n].ThunkTableRva);

	mov	rax, QWORD PTR n$1[rsp]
	imul	rax, 20
	mov	rcx, QWORD PTR importdir$[rsp]
	mov	edx, DWORD PTR [rcx+rax+16]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEA_KPEAX@@YAPEA_KPEAXH@Z	; raw_offset<unsigned __int64 * __ptr64,void * __ptr64>
	mov	QWORD PTR iat$2[rsp], rax
$LN2@LinkLibrar:

; 97   : 		while (*iat) {

	mov	rax, QWORD PTR iat$2[rsp]
	cmp	QWORD PTR [rax], 0
	je	SHORT $LN1@LinkLibrar

; 98   : 			PIMAGE_IMPORT_HINT_TABLE hint = raw_offset<PIMAGE_IMPORT_HINT_TABLE>(image, *iat);

	mov	rax, QWORD PTR iat$2[rsp]
	mov	edx, DWORD PTR [rax]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEAU_IMAGE_IMPORT_HINT_TABLE@@PEAX@@YAPEAU_IMAGE_IMPORT_HINT_TABLE@@PEAXH@Z ; raw_offset<_IMAGE_IMPORT_HINT_TABLE * __ptr64,void * __ptr64>
	mov	QWORD PTR hint$5[rsp], rax

; 99   : 			const char* fname = hint->name;

	mov	rax, QWORD PTR hint$5[rsp]
	add	rax, 2
	mov	QWORD PTR fname$3[rsp], rax

; 100  : 			void* procaddr = GetProcAddress((void*)0xFFFFC00000000000, fname);

	mov	rdx, QWORD PTR fname$3[rsp]
	mov	rcx, -70368744177664			; ffffc00000000000H
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR procaddr$4[rsp], rax

; 101  : 			*iat = (uint64_t)procaddr;

	mov	rax, QWORD PTR iat$2[rsp]
	mov	rcx, QWORD PTR procaddr$4[rsp]
	mov	QWORD PTR [rax], rcx

; 102  : 			++iat;

	mov	rax, QWORD PTR iat$2[rsp]
	add	rax, 8
	mov	QWORD PTR iat$2[rsp], rax

; 103  : 		}

	jmp	SHORT $LN2@LinkLibrar
$LN1@LinkLibrar:

; 104  : 	}

	jmp	$LN4@LinkLibrar
$LN3@LinkLibrar:
$LN9@LinkLibrar:

; 105  : }

	add	rsp, 120				; 00000078H
	ret	0
?LinkLibrary@@YAXPEAX0@Z ENDP				; LinkLibrary
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEAXPEAX@@YAPEAXPEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEAXPEAX@@YAPEAXPEAXH@Z PROC		; raw_offset<void * __ptr64,void * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEAXPEAX@@YAPEAXPEAXH@Z ENDP		; raw_offset<void * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEADPEAX@@YAPEADPEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEADPEAX@@YAPEADPEAXH@Z PROC		; raw_offset<char * __ptr64,void * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEADPEAX@@YAPEADPEAXH@Z ENDP		; raw_offset<char * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEAGPEAX@@YAPEAGPEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEAGPEAX@@YAPEAGPEAXH@Z PROC		; raw_offset<unsigned short * __ptr64,void * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEAGPEAX@@YAPEAGPEAXH@Z ENDP		; raw_offset<unsigned short * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEAIPEAX@@YAPEAIPEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEAIPEAX@@YAPEAIPEAXH@Z PROC		; raw_offset<unsigned int * __ptr64,void * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEAIPEAX@@YAPEAIPEAXH@Z ENDP		; raw_offset<unsigned int * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEAU_IMAGE_EXPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_EXPORT_DIRECTORY@@PEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEAU_IMAGE_EXPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_EXPORT_DIRECTORY@@PEAXH@Z PROC ; raw_offset<_IMAGE_EXPORT_DIRECTORY * __ptr64,void * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEAU_IMAGE_EXPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_EXPORT_DIRECTORY@@PEAXH@Z ENDP ; raw_offset<_IMAGE_EXPORT_DIRECTORY * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z PROC ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z ENDP ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pe.cpp
_TEXT	SEGMENT
i$1 = 32
ordinal$2 = 36
exportdir$ = 40
FunctionAddress$3 = 48
datadir$ = 56
dos_header$ = 64
ntHeaders$ = 72
function_name$4 = 80
FunctionOrdinalAddressArray$ = 88
FuntionNameAddressArray$ = 96
FunctionAddressArray$ = 104
image$ = 128
procname$ = 136
?GetProcAddress@@YAPEAXPEAXPEBD@Z PROC			; GetProcAddress

; 50   : void* GetProcAddress(void *image, const char* procname){

$LN10:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 120				; 00000078H

; 51   : 	
; 52   : 	PIMAGE_DOS_HEADER dos_header  = (PIMAGE_DOS_HEADER)image;

	mov	rax, QWORD PTR image$[rsp]
	mov	QWORD PTR dos_header$[rsp], rax

; 53   : 	PIMAGE_NT_HEADERS ntHeaders = raw_offset<PIMAGE_NT_HEADERS>(dos_header, dos_header->e_lfanew); 

	mov	rax, QWORD PTR dos_header$[rsp]
	movzx	eax, WORD PTR [rax+60]
	mov	edx, eax
	mov	rcx, QWORD PTR dos_header$[rsp]
	call	??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>
	mov	QWORD PTR ntHeaders$[rsp], rax

; 54   : 	if (IMAGE_DATA_DIRECTORY_EXPORT + 1 > ntHeaders->OptionalHeader.NumberOfRvaAndSizes)

	mov	rax, QWORD PTR ntHeaders$[rsp]
	cmp	DWORD PTR [rax+132], 1
	jae	SHORT $LN7@GetProcAdd

; 55   : 		return NULL;

	xor	eax, eax
	jmp	$LN8@GetProcAdd
$LN7@GetProcAdd:

; 56   : 	IMAGE_DATA_DIRECTORY& datadir = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DATA_DIRECTORY_EXPORT];

	mov	eax, 8
	imul	rax, 0
	mov	rcx, QWORD PTR ntHeaders$[rsp]
	lea	rax, QWORD PTR [rcx+rax+136]
	mov	QWORD PTR datadir$[rsp], rax

; 57   : 	if (datadir.VirtualAddress == 0 || datadir.Size == 0)

	mov	rax, QWORD PTR datadir$[rsp]
	cmp	DWORD PTR [rax], 0
	je	SHORT $LN5@GetProcAdd
	mov	rax, QWORD PTR datadir$[rsp]
	cmp	DWORD PTR [rax+4], 0
	jne	SHORT $LN6@GetProcAdd
$LN5@GetProcAdd:

; 58   : 		return NULL;

	xor	eax, eax
	jmp	$LN8@GetProcAdd
$LN6@GetProcAdd:

; 59   : 	PIMAGE_EXPORT_DIRECTORY exportdir = raw_offset<PIMAGE_EXPORT_DIRECTORY>(image, datadir.VirtualAddress);

	mov	rax, QWORD PTR datadir$[rsp]
	mov	edx, DWORD PTR [rax]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEAU_IMAGE_EXPORT_DIRECTORY@@PEAX@@YAPEAU_IMAGE_EXPORT_DIRECTORY@@PEAXH@Z ; raw_offset<_IMAGE_EXPORT_DIRECTORY * __ptr64,void * __ptr64>
	mov	QWORD PTR exportdir$[rsp], rax

; 60   : 	uint32_t* FuntionNameAddressArray = raw_offset<uint32_t*>(image,exportdir->AddressOfNames);

	mov	rax, QWORD PTR exportdir$[rsp]
	mov	edx, DWORD PTR [rax+32]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEAIPEAX@@YAPEAIPEAXH@Z	; raw_offset<unsigned int * __ptr64,void * __ptr64>
	mov	QWORD PTR FuntionNameAddressArray$[rsp], rax

; 61   : 	uint16_t* FunctionOrdinalAddressArray = raw_offset<uint16_t*>(image,exportdir->AddressOfNameOrdinal);

	mov	rax, QWORD PTR exportdir$[rsp]
	mov	edx, DWORD PTR [rax+36]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEAGPEAX@@YAPEAGPEAXH@Z	; raw_offset<unsigned short * __ptr64,void * __ptr64>
	mov	QWORD PTR FunctionOrdinalAddressArray$[rsp], rax

; 62   : 	uint32_t* FunctionAddressArray = raw_offset<uint32_t*>(image,exportdir->AddressOfFunctions);

	mov	rax, QWORD PTR exportdir$[rsp]
	mov	edx, DWORD PTR [rax+28]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEAIPEAX@@YAPEAIPEAXH@Z	; raw_offset<unsigned int * __ptr64,void * __ptr64>
	mov	QWORD PTR FunctionAddressArray$[rsp], rax

; 63   : 
; 64   : 	for (int i = 0; i < exportdir->NumberOfNames; i++ ) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@GetProcAdd
$LN3@GetProcAdd:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@GetProcAdd:
	mov	rax, QWORD PTR exportdir$[rsp]
	mov	eax, DWORD PTR [rax+24]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN2@GetProcAdd

; 65   : 
; 66   : 	    char* function_name = raw_offset<char*>(image,FuntionNameAddressArray [i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR FuntionNameAddressArray$[rsp]
	mov	edx, DWORD PTR [rcx+rax*4]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEADPEAX@@YAPEADPEAXH@Z	; raw_offset<char * __ptr64,void * __ptr64>
	mov	QWORD PTR function_name$4[rsp], rax

; 67   : 		if (strcmp (function_name, procname) == 0) {

	mov	rdx, QWORD PTR procname$[rsp]
	mov	rcx, QWORD PTR function_name$4[rsp]
	call	?strcmp@@YAHPEBD0@Z			; strcmp
	test	eax, eax
	jne	SHORT $LN1@GetProcAdd

; 68   : 			uint16_t ordinal = FunctionOrdinalAddressArray[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR FunctionOrdinalAddressArray$[rsp]
	movzx	eax, WORD PTR [rcx+rax*2]
	mov	WORD PTR ordinal$2[rsp], ax

; 69   : 			uint32_t FunctionAddress = FunctionAddressArray [ordinal];

	movzx	eax, WORD PTR ordinal$2[rsp]
	mov	rcx, QWORD PTR FunctionAddressArray$[rsp]
	mov	eax, DWORD PTR [rcx+rax*4]
	mov	DWORD PTR FunctionAddress$3[rsp], eax

; 70   : 			return raw_offset<void*>(image,FunctionAddress);

	mov	edx, DWORD PTR FunctionAddress$3[rsp]
	mov	rcx, QWORD PTR image$[rsp]
	call	??$raw_offset@PEAXPEAX@@YAPEAXPEAXH@Z	; raw_offset<void * __ptr64,void * __ptr64>
	jmp	SHORT $LN8@GetProcAdd
$LN1@GetProcAdd:

; 71   : 		}
; 72   : 	}

	jmp	$LN3@GetProcAdd
$LN2@GetProcAdd:

; 73   : 
; 74   : 	return nullptr;

	xor	eax, eax
$LN8@GetProcAdd:

; 75   : }

	add	rsp, 120				; 00000078H
	ret	0
?GetProcAddress@@YAPEAXPEAXPEBD@Z ENDP			; GetProcAddress
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pe.cpp
_TEXT	SEGMENT
?get_image_base@@YA_KXZ PROC				; get_image_base

; 46   : 	return image_base;

	mov	rax, QWORD PTR ?image_base@@3_KA	; image_base

; 47   : }

	ret	0
?get_image_base@@YA_KXZ ENDP				; get_image_base
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pe.cpp
_TEXT	SEGMENT
?get_entry_point@@YAP6AXPEAX@ZXZ PROC			; get_entry_point

; 41   : 	return ent;

	mov	rax, QWORD PTR ?ent@@3P6AXPEAX@ZEA	; ent

; 42   : }

	ret	0
?get_entry_point@@YAP6AXPEAX@ZXZ ENDP			; get_entry_point
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pe.cpp
_TEXT	SEGMENT
nt$ = 32
dos$ = 40
buffer$ = 64
size$ = 72
?load_pe_file@@YAXPEA_KH@Z PROC				; load_pe_file

; 22   : void load_pe_file (uint64_t* buffer, int size) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 23   : 
; 24   : 	IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR dos$[rsp], rax

; 25   : 	PIMAGE_NT_HEADERS nt = raw_offset<PIMAGE_NT_HEADERS>(dos, dos->e_lfanew);

	mov	rax, QWORD PTR dos$[rsp]
	movzx	eax, WORD PTR [rax+60]
	mov	edx, eax
	mov	rcx, QWORD PTR dos$[rsp]
	call	??$raw_offset@PEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@@@YAPEAU_IMAGE_NT_HEADERS_PE32PLUS@@PEAU_IMAGE_DOS_HEADER_@@H@Z ; raw_offset<_IMAGE_NT_HEADERS_PE32PLUS * __ptr64,_IMAGE_DOS_HEADER_ * __ptr64>
	mov	QWORD PTR nt$[rsp], rax

; 26   : 
; 27   :     image_base = nt->OptionalHeader.ImageBase;

	mov	rax, QWORD PTR nt$[rsp]
	mov	rax, QWORD PTR [rax+48]
	mov	QWORD PTR ?image_base@@3_KA, rax	; image_base

; 28   : 	ent = (ientry)(nt->OptionalHeader.AddressOfEntryPoint + nt->OptionalHeader.ImageBase); //buffer

	mov	rax, QWORD PTR nt$[rsp]
	mov	eax, DWORD PTR [rax+40]
	mov	rcx, QWORD PTR nt$[rsp]
	add	rax, QWORD PTR [rcx+48]
	mov	QWORD PTR ?ent@@3P6AXPEAX@ZEA, rax	; ent

; 29   : 	//! For now Xeneva only loads binary that are aligned in 512, 1024 & 4096 byte
; 30   : 	//! aligned. Simply we call its entry address that are expected to be aligned in
; 31   : 	//! 512, 1024 and 4096 bytes
; 32   : 
; 33   : 	//! copy the image to its desired virtual address
; 34   : 	//memcpy ((void*)nt->OptionalHeader.ImageBase,buffer, size);
; 35   : 
; 36   : 	//! set the entry point
; 37   : 	//set_entry_point (nt);
; 38   : }

	add	rsp, 56					; 00000038H
	ret	0
?load_pe_file@@YAXPEA_KH@Z ENDP				; load_pe_file
_TEXT	ENDS
END
