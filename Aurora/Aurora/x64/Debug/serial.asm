; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG2844	DB	'Serial Handler', 0aH, 00H
CONST	ENDS
PUBLIC	?initialize_serial@@YAXXZ			; initialize_serial
PUBLIC	?write_serial@@YAXD@Z				; write_serial
PUBLIC	?debug_serial@@YAXPEAD@Z			; debug_serial
PUBLIC	?serial_handler@@YAX_KPEAX@Z			; serial_handler
PUBLIC	?is_transmit_empty@@YAHXZ			; is_transmit_empty
EXTRN	x64_inportb:PROC
EXTRN	x64_outportb:PROC
EXTRN	?interrupt_end@@YAXI@Z:PROC			; interrupt_end
EXTRN	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z:PROC	; interrupt_set
EXTRN	?strlen@@YA_KPEBD@Z:PROC			; strlen
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
pdata	SEGMENT
$pdata$?initialize_serial@@YAXXZ DD imagerel $LN4
	DD	imagerel $LN4+160
	DD	imagerel $unwind$?initialize_serial@@YAXXZ
$pdata$?write_serial@@YAXD@Z DD imagerel $LN3
	DD	imagerel $LN3+27
	DD	imagerel $unwind$?write_serial@@YAXD@Z
$pdata$?debug_serial@@YAXPEAD@Z DD imagerel $LN6
	DD	imagerel $LN6+85
	DD	imagerel $unwind$?debug_serial@@YAXPEAD@Z
$pdata$?serial_handler@@YAX_KPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+41
	DD	imagerel $unwind$?serial_handler@@YAX_KPEAX@Z
$pdata$?is_transmit_empty@@YAHXZ DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?is_transmit_empty@@YAHXZ
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_serial@@YAXXZ DD 010401H
	DD	04204H
$unwind$?write_serial@@YAXD@Z DD 010801H
	DD	04208H
$unwind$?debug_serial@@YAXPEAD@Z DD 010901H
	DD	06209H
$unwind$?serial_handler@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?is_transmit_empty@@YAHXZ DD 010401H
	DD	04204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?is_transmit_empty@@YAHXZ PROC				; is_transmit_empty

; 44   : int is_transmit_empty () {

$LN3:
	sub	rsp, 40					; 00000028H

; 45   : 	return x64_inportb (PORT + 5) & 0x20;

	mov	cx, 1021				; 000003fdH
	call	x64_inportb
	movzx	eax, al
	and	eax, 32					; 00000020H

; 46   : }

	add	rsp, 40					; 00000028H
	ret	0
?is_transmit_empty@@YAHXZ ENDP				; is_transmit_empty
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?serial_handler@@YAX_KPEAX@Z PROC			; serial_handler

; 20   : void serial_handler (size_t v, void* p) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 21   : 	printf ("Serial Handler\n");

	lea	rcx, OFFSET FLAT:$SG2844
	call	?printf@@YAXPEBDZZ			; printf

; 22   : 	interrupt_end(4);

	mov	ecx, 4
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 23   : }

	add	rsp, 40					; 00000028H
	ret	0
?serial_handler@@YAX_KPEAX@Z ENDP			; serial_handler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
i$1 = 32
tv65 = 40
string$ = 64
?debug_serial@@YAXPEAD@Z PROC				; debug_serial

; 53   : void debug_serial (char* string) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 54   : 	for (int i = 0; i < strlen(string); i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@debug_seri
$LN2@debug_seri:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@debug_seri:
	movsxd	rax, DWORD PTR i$1[rsp]
	mov	QWORD PTR tv65[rsp], rax
	mov	rcx, QWORD PTR string$[rsp]
	call	?strlen@@YA_KPEBD@Z			; strlen
	mov	rcx, QWORD PTR tv65[rsp]
	cmp	rcx, rax
	jae	SHORT $LN1@debug_seri

; 55   : 		write_serial(string[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR string$[rsp]
	movzx	ecx, BYTE PTR [rcx+rax]
	call	?write_serial@@YAXD@Z			; write_serial
	jmp	SHORT $LN2@debug_seri
$LN1@debug_seri:

; 56   : }

	add	rsp, 56					; 00000038H
	ret	0
?debug_serial@@YAXPEAD@Z ENDP				; debug_serial
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
a$ = 48
?write_serial@@YAXD@Z PROC				; write_serial

; 48   : void write_serial (char a) {

$LN3:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H

; 49   : 	//while (is_transmit_empty() == 0);
; 50   : 	x64_outportb (PORT, a);

	movzx	edx, BYTE PTR a$[rsp]
	mov	cx, 1016				; 000003f8H
	call	x64_outportb

; 51   : }

	add	rsp, 40					; 00000028H
	ret	0
?write_serial@@YAXD@Z ENDP				; write_serial
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?initialize_serial@@YAXXZ PROC				; initialize_serial

; 25   : void initialize_serial() {

$LN4:
	sub	rsp, 40					; 00000028H

; 26   : 	x64_outportb (PORT + 1, 0x00);

	xor	edx, edx
	mov	cx, 1017				; 000003f9H
	call	x64_outportb

; 27   : 	x64_outportb (PORT + 3, 0x80);

	mov	dl, 128					; 00000080H
	mov	cx, 1019				; 000003fbH
	call	x64_outportb

; 28   : 	x64_outportb (PORT + 0, 0x03);

	mov	dl, 3
	mov	cx, 1016				; 000003f8H
	call	x64_outportb

; 29   : 	x64_outportb (PORT + 1, 0x00);

	xor	edx, edx
	mov	cx, 1017				; 000003f9H
	call	x64_outportb

; 30   : 	x64_outportb (PORT + 3, 0x03);

	mov	dl, 3
	mov	cx, 1019				; 000003fbH
	call	x64_outportb

; 31   : 	x64_outportb (PORT + 2, 0xC7);

	mov	dl, 199					; 000000c7H
	mov	cx, 1018				; 000003faH
	call	x64_outportb

; 32   : 	x64_outportb (PORT + 4, 0x0B);

	mov	dl, 11
	mov	cx, 1020				; 000003fcH
	call	x64_outportb

; 33   : 	x64_outportb (PORT + 4, 0x1E);

	mov	dl, 30
	mov	cx, 1020				; 000003fcH
	call	x64_outportb

; 34   : 	x64_outportb (PORT + 0, 0xAE);

	mov	dl, 174					; 000000aeH
	mov	cx, 1016				; 000003f8H
	call	x64_outportb

; 35   : 
; 36   : 	if (x64_inportb (PORT + 0) != 0xAE) {

	mov	cx, 1016				; 000003f8H
	call	x64_inportb
	movzx	eax, al
	cmp	eax, 174				; 000000aeH
	je	SHORT $LN1@initialize

; 37   : 		return;

	jmp	SHORT $LN2@initialize
$LN1@initialize:

; 38   : 	}
; 39   : 
; 40   : 	x64_outportb (PORT + 4, 0x0F);

	mov	dl, 15
	mov	cx, 1020				; 000003fcH
	call	x64_outportb

; 41   : 	interrupt_set (4,serial_handler, 4);

	mov	r8b, 4
	lea	rdx, OFFSET FLAT:?serial_handler@@YAX_KPEAX@Z ; serial_handler
	mov	ecx, 4
	call	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z	; interrupt_set
$LN2@initialize:

; 42   : }

	add	rsp, 40					; 00000028H
	ret	0
?initialize_serial@@YAXXZ ENDP				; initialize_serial
_TEXT	ENDS
END
