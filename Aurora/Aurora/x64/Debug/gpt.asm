; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3018	DB	'[GPT]: Initializing gpt partition tables....', 0aH, 00H
	ORG $+2
$SG3022	DB	'[GPT]: Signature %s', 0aH, 00H
	ORG $+3
$SG3023	DB	'[GPT]: Revision %x', 0aH, 00H
	ORG $+4
$SG3024	DB	'[GPT]: Total partition entries %d', 0aH, 00H
	ORG $+5
$SG3025	DB	'[GPT]: Partition table lba -> %d', 0aH, 00H
	ORG $+6
$SG3027	DB	'[GPT]: SizeOf(GPTPartitionTable) -> %d', 0aH, 00H
CONST	ENDS
PUBLIC	?initialize_gpt@@YAXXZ				; initialize_gpt
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	printf:PROC
EXTRN	?AuPmmngrFree@@YAXPEAX@Z:PROC			; AuPmmngrFree
EXTRN	?ata_read_28@@YAEIGPEAE@Z:PROC			; ata_read_28
pdata	SEGMENT
$pdata$?initialize_gpt@@YAXXZ DD imagerel $LN6
	DD	imagerel $LN6+278
	DD	imagerel $unwind$?initialize_gpt@@YAXXZ
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_gpt@@YAXXZ DD 020701H
	DD	0890107H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\gpt.cpp
_TEXT	SEGMENT
i$1 = 32
gpt_h$ = 40
raw_byte_index$ = 48
part$2 = 56
buffer$ = 64
buf$ = 576
?initialize_gpt@@YAXXZ PROC				; initialize_gpt

; 21   : void initialize_gpt () {

$LN6:
	sub	rsp, 1096				; 00000448H

; 22   : 	printf ("[GPT]: Initializing gpt partition tables....\n");

	lea	rcx, OFFSET FLAT:$SG3018
	call	printf

; 23   : 	uint8_t buffer[512];
; 24   : 	memset(buffer,0,512);

	mov	r8d, 512				; 00000200H
	xor	edx, edx
	lea	rcx, QWORD PTR buffer$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 25   : 
; 26   : 	ata_read_28 (1,1,buffer);

	lea	r8, QWORD PTR buffer$[rsp]
	mov	dx, 1
	mov	ecx, 1
	call	?ata_read_28@@YAEIGPEAE@Z		; ata_read_28

; 27   : 
; 28   : 	gpt_header_t *gpt_h = (gpt_header_t*)buffer;

	lea	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR gpt_h$[rsp], rax

; 29   : 
; 30   : 	printf ("[GPT]: Signature %s\n", gpt_h->signature);

	mov	rax, QWORD PTR gpt_h$[rsp]
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:$SG3022
	call	printf

; 31   : 	printf ("[GPT]: Revision %x\n", gpt_h->reserved);

	mov	rax, QWORD PTR gpt_h$[rsp]
	mov	edx, DWORD PTR [rax+20]
	lea	rcx, OFFSET FLAT:$SG3023
	call	printf

; 32   : 	printf ("[GPT]: Total partition entries %d\n", gpt_h->num_partition_entries);

	mov	rax, QWORD PTR gpt_h$[rsp]
	mov	edx, DWORD PTR [rax+80]
	lea	rcx, OFFSET FLAT:$SG3024
	call	printf

; 33   : 	printf ("[GPT]: Partition table lba -> %d\n", gpt_h->partition_table_lba);

	mov	rax, QWORD PTR gpt_h$[rsp]
	mov	rdx, QWORD PTR [rax+72]
	lea	rcx, OFFSET FLAT:$SG3025
	call	printf

; 34   : 	printf ("[GPT]: SizeOf(GPTPartitionTable) -> %d\n", sizeof(gpt_partition_t));

	mov	edx, 128				; 00000080H
	lea	rcx, OFFSET FLAT:$SG3027
	call	printf

; 35   : 	uint8_t buf[512];
; 36   : 	//memset (buf, 0, 4096);
; 37   : 	auto raw_byte_index = gpt_h->partition_table_lba;

	mov	rax, QWORD PTR gpt_h$[rsp]
	mov	rax, QWORD PTR [rax+72]
	mov	QWORD PTR raw_byte_index$[rsp], rax

; 38   : 
; 39   : 	for (int i = 0; i < 128; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@initialize
$LN2@initialize:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@initialize:
	cmp	DWORD PTR i$1[rsp], 128			; 00000080H
	jge	SHORT $LN1@initialize

; 40   : 		ata_read_28(raw_byte_index, 1, buf);

	lea	r8, QWORD PTR buf$[rsp]
	mov	dx, 1
	mov	ecx, DWORD PTR raw_byte_index$[rsp]
	call	?ata_read_28@@YAEIGPEAE@Z		; ata_read_28

; 41   : 		gpt_partition_t *part = (gpt_partition_t*)buf;

	lea	rax, QWORD PTR buf$[rsp]
	mov	QWORD PTR part$2[rsp], rax

; 42   : 		raw_byte_index++;

	mov	rax, QWORD PTR raw_byte_index$[rsp]
	inc	rax
	mov	QWORD PTR raw_byte_index$[rsp], rax

; 43   : 	}

	jmp	SHORT $LN2@initialize
$LN1@initialize:

; 44   : 
; 45   : 	AuPmmngrFree(buf);

	lea	rcx, QWORD PTR buf$[rsp]
	call	?AuPmmngrFree@@YAXPEAX@Z		; AuPmmngrFree

; 46   : }

	add	rsp, 1096				; 00000448H
	ret	0
?initialize_gpt@@YAXXZ ENDP				; initialize_gpt
_TEXT	ENDS
END
