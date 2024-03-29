; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_BSS	SEGMENT
_serial_initialized_ DB 01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG3617	DB	'Serial Handler', 0aH, 00H
$SG3710	DB	'.', 00H
	ORG $+2
$SG3737	DB	'serial', 00H
	ORG $+5
$SG3738	DB	'/dev/serial', 00H
CONST	ENDS
PUBLIC	?AuInitializeSerial@@YAXXZ			; AuInitializeSerial
PUBLIC	?AuInitializeSerialFile@@YAXXZ			; AuInitializeSerialFile
PUBLIC	?write_serial@@YAXD@Z				; write_serial
PUBLIC	?debug_serial@@YAXPEAD@Z			; debug_serial
PUBLIC	_debug_print_
PUBLIC	?is_serial_initialized@@YA_NXZ			; is_serial_initialized
PUBLIC	?SerialHandler@@YAX_KPEAX@Z			; SerialHandler
PUBLIC	?is_transmit_empty@@YAHXZ			; is_transmit_empty
PUBLIC	?AuSerialWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z	; AuSerialWrite
PUBLIC	?AuSerialRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z	; AuSerialRead
PUBLIC	?AuSerialIoQuery@@YAHPEAU_vfs_node_@@HPEAX@Z	; AuSerialIoQuery
EXTRN	x64_inportb:PROC
EXTRN	x64_outportb:PROC
EXTRN	AuInterruptEnd:PROC
EXTRN	strcpy:PROC
EXTRN	strlen:PROC
EXTRN	?sztoa@@YAPEAD_KPEADH@Z:PROC			; sztoa
EXTRN	printf:PROC
EXTRN	?ftoa@@YAPEADME@Z:PROC				; ftoa
EXTRN	vfs_mount:PROC
EXTRN	malloc:PROC
EXTRN	_fltused:DWORD
pdata	SEGMENT
$pdata$?AuInitializeSerial@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+93
	DD	imagerel $unwind$?AuInitializeSerial@@YAXXZ
$pdata$?AuInitializeSerialFile@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+201
	DD	imagerel $unwind$?AuInitializeSerialFile@@YAXXZ
$pdata$?write_serial@@YAXD@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?write_serial@@YAXD@Z
$pdata$?debug_serial@@YAXPEAD@Z DD imagerel $LN6
	DD	imagerel $LN6+85
	DD	imagerel $unwind$?debug_serial@@YAXPEAD@Z
$pdata$_debug_print_ DD imagerel $LN25
	DD	imagerel $LN25+860
	DD	imagerel $unwind$_debug_print_
$pdata$?SerialHandler@@YAX_KPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+41
	DD	imagerel $unwind$?SerialHandler@@YAX_KPEAX@Z
$pdata$?is_transmit_empty@@YAHXZ DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?is_transmit_empty@@YAHXZ
$pdata$?AuSerialWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z DD imagerel $LN3
	DD	imagerel $LN3+44
	DD	imagerel $unwind$?AuSerialWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuInitializeSerial@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuInitializeSerialFile@@YAXXZ DD 010401H
	DD	06204H
$unwind$?write_serial@@YAXD@Z DD 010801H
	DD	04208H
$unwind$?debug_serial@@YAXPEAD@Z DD 010901H
	DD	06209H
$unwind$_debug_print_ DD 021b01H
	DD	023011bH
$unwind$?SerialHandler@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?is_transmit_empty@@YAHXZ DD 010401H
	DD	04204H
$unwind$?AuSerialWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z DD 011301H
	DD	06213H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
devid$ = 8
code$ = 16
arg$ = 24
?AuSerialIoQuery@@YAHPEAU_vfs_node_@@HPEAX@Z PROC	; AuSerialIoQuery

; 184  : int AuSerialIoQuery (vfs_node_t* devid, int code, void* arg) {

	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 185  : 	return 1;

	mov	eax, 1

; 186  : }

	ret	0
?AuSerialIoQuery@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP	; AuSerialIoQuery
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
file$ = 8
buffer$ = 16
length$ = 24
?AuSerialRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z PROC	; AuSerialRead

; 179  : size_t AuSerialRead (vfs_node_t *file, uint64_t* buffer,uint32_t length){

	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 180  : 	return 0;

	xor	eax, eax

; 181  : }

	ret	0
?AuSerialRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z ENDP	; AuSerialRead
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
format$ = 32
file$ = 64
buffer$ = 72
length$ = 80
?AuSerialWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z PROC	; AuSerialWrite

; 169  : void AuSerialWrite (vfs_node_t *file, uint64_t* buffer, uint32_t length) {

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 170  : 	char* format = (char*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR format$[rsp], rax

; 171  : 	_debug_print_ (format);

	mov	rcx, QWORD PTR format$[rsp]
	call	_debug_print_

; 172  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuSerialWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z ENDP	; AuSerialWrite
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?is_transmit_empty@@YAHXZ PROC				; is_transmit_empty

; 65   : int is_transmit_empty () {

$LN3:
	sub	rsp, 40					; 00000028H

; 66   : 	return x64_inportb (PORT + 5) & 0x20;

	mov	cx, 1021				; 000003fdH
	call	x64_inportb
	movzx	eax, al
	and	eax, 32					; 00000020H

; 67   : }

	add	rsp, 40					; 00000028H
	ret	0
?is_transmit_empty@@YAHXZ ENDP				; is_transmit_empty
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?SerialHandler@@YAX_KPEAX@Z PROC			; SerialHandler

; 46   : void SerialHandler (size_t v, void* p) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 47   : 	printf ("Serial Handler\n");

	lea	rcx, OFFSET FLAT:$SG3617
	call	printf

; 48   : 	AuInterruptEnd(4);

	mov	ecx, 4
	call	AuInterruptEnd

; 49   : }

	add	rsp, 40					; 00000028H
	ret	0
?SerialHandler@@YAX_KPEAX@Z ENDP			; SerialHandler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?is_serial_initialized@@YA_NXZ PROC			; is_serial_initialized

; 210  : 	return _serial_initialized_;

	movzx	eax, BYTE PTR _serial_initialized_

; 211  : }

	ret	0
?is_serial_initialized@@YA_NXZ ENDP			; is_serial_initialized
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
c$1 = 32
args$ = 40
buf$2 = 48
buf$3 = 52
i$4 = 56
i$5 = 64
width$6 = 72
x$7 = 80
x$8 = 88
x$9 = 96
len$10 = 104
buffer$11 = 112
buffer$12 = 192
format$ = 288
_debug_print_ PROC

; 79   : void _debug_print_ (char* format, ...) {

$LN25:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 280				; 00000118H

; 80   : 
; 81   : 
; 82   : 	_va_list_ args;
; 83   : 	va_start(args, format);

	lea	rax, QWORD PTR format$[rsp+8]
	mov	QWORD PTR args$[rsp], rax
$LN22@debug_prin:

; 84   : 
; 85   : 	while (*format)

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	$LN21@debug_prin

; 86   : 	{
; 87   : 		if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	$LN20@debug_prin

; 88   : 		{
; 89   : 			++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 90   : 			if (*format == 'd')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 100				; 00000064H
	jne	$LN19@debug_prin

; 91   : 			{
; 92   : 				size_t width = 0;

	mov	QWORD PTR width$6[rsp], 0

; 93   : 				if (format[1] == '.')

	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 46					; 0000002eH
	jne	$LN18@debug_prin

; 94   : 				{
; 95   : 					for (size_t i = 2; format[i] >= '0' && format[i] <= '9'; ++i)

	mov	QWORD PTR i$4[rsp], 2
	jmp	SHORT $LN17@debug_prin
$LN16@debug_prin:
	mov	rax, QWORD PTR i$4[rsp]
	inc	rax
	mov	QWORD PTR i$4[rsp], rax
$LN17@debug_prin:
	mov	rax, QWORD PTR i$4[rsp]
	mov	rcx, QWORD PTR format$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 48					; 00000030H
	jl	SHORT $LN15@debug_prin
	mov	rax, QWORD PTR i$4[rsp]
	mov	rcx, QWORD PTR format$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 57					; 00000039H
	jg	SHORT $LN15@debug_prin

; 96   : 					{
; 97   : 						width *= 10;

	mov	rax, QWORD PTR width$6[rsp]
	imul	rax, 10
	mov	QWORD PTR width$6[rsp], rax

; 98   : 						width += format[i] - '0';

	mov	rax, QWORD PTR i$4[rsp]
	mov	rcx, QWORD PTR format$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movsx	eax, BYTE PTR [rax]
	sub	eax, 48					; 00000030H
	cdqe
	mov	rcx, QWORD PTR width$6[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR width$6[rsp], rax

; 99   : 					}

	jmp	SHORT $LN16@debug_prin
$LN15@debug_prin:
$LN18@debug_prin:

; 100  : 				}
; 101  : 				size_t i = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR i$5[rsp], rax

; 102  : 				char buffer[sizeof(size_t) * 8 + 1];
; 103  : 			//	size_t len
; 104  : 				if (i < 0) {

	cmp	QWORD PTR i$5[rsp], 0
	jae	SHORT $LN14@debug_prin

; 105  : 					i = +i;

	mov	rax, QWORD PTR i$5[rsp]
	mov	QWORD PTR i$5[rsp], rax

; 106  : 					sztoa (i,buffer,10);

	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$11[rsp]
	mov	rcx, QWORD PTR i$5[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 107  : 				}else {

	jmp	SHORT $LN13@debug_prin
$LN14@debug_prin:

; 108  : 					sztoa(i, buffer, 10);

	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$11[rsp]
	mov	rcx, QWORD PTR i$5[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 109  : 					size_t len = strlen(buffer);

	lea	rcx, QWORD PTR buffer$11[rsp]
	call	strlen
	mov	QWORD PTR len$10[rsp], rax
$LN13@debug_prin:

; 110  : 				}
; 111  : 			/*	while (len++ < width)
; 112  : 					puts("0");*/
; 113  : 				debug_serial(buffer);

	lea	rcx, QWORD PTR buffer$11[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	$LN12@debug_prin
$LN19@debug_prin:

; 114  : 			}
; 115  : 			else if (*format == 'c')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 99					; 00000063H
	jne	SHORT $LN11@debug_prin

; 116  : 			{
; 117  : 				char c = va_arg(args, char);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 4
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	movzx	eax, BYTE PTR [rax-4]
	mov	BYTE PTR c$1[rsp], al

; 118  : 				//char buffer[sizeof(size_t) * 8 + 1];
; 119  : 				//sztoa(c, buffer, 10);
; 120  : 				//puts(buffer);
; 121  : 				write_serial(c);

	movzx	ecx, BYTE PTR c$1[rsp]
	call	?write_serial@@YAXD@Z			; write_serial
	jmp	$LN10@debug_prin
$LN11@debug_prin:

; 122  : 			}
; 123  : 			else if (*format == 'x')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 120				; 00000078H
	jne	SHORT $LN9@debug_prin

; 124  : 			{
; 125  : 				size_t x = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$9[rsp], rax

; 126  : 				char buffer[sizeof(size_t) * 8 + 1];
; 127  : 				sztoa(x, buffer, 16);

	mov	r8d, 16
	lea	rdx, QWORD PTR buffer$12[rsp]
	mov	rcx, QWORD PTR x$9[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 128  : 				//puts("0x");
; 129  : 				debug_serial(buffer);

	lea	rcx, QWORD PTR buffer$12[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	$LN8@debug_prin
$LN9@debug_prin:

; 130  : 			}
; 131  : 			else if (*format == 's')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 115				; 00000073H
	jne	SHORT $LN7@debug_prin

; 132  : 			{
; 133  : 				char* x = va_arg(args, char*);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$8[rsp], rax

; 134  : 				debug_serial(x);

	mov	rcx, QWORD PTR x$8[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	$LN6@debug_prin
$LN7@debug_prin:

; 135  : 			}
; 136  : 			else if (*format == 'f')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 102				; 00000066H
	jne	SHORT $LN5@debug_prin

; 137  : 			{
; 138  : 				double x = va_arg(args, double);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	movsdx	xmm0, QWORD PTR [rax-8]
	movsdx	QWORD PTR x$7[rsp], xmm0

; 139  : 				debug_serial(ftoa(x,2));

	cvtsd2ss xmm0, QWORD PTR x$7[rsp]
	mov	dl, 2
	call	?ftoa@@YAPEADME@Z			; ftoa
	mov	rcx, rax
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	SHORT $LN4@debug_prin
$LN5@debug_prin:

; 140  : 			}
; 141  : 			else if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	SHORT $LN3@debug_prin

; 142  : 			{
; 143  : 				debug_serial(".");

	lea	rcx, OFFSET FLAT:$SG3710
	call	?debug_serial@@YAXPEAD@Z		; debug_serial

; 144  : 			}
; 145  : 			else

	jmp	SHORT $LN2@debug_prin
$LN3@debug_prin:

; 146  : 			{
; 147  : 				char buf[3];
; 148  : 				buf[0] = '%'; buf[1] = *format; buf[2] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	BYTE PTR buf$3[rsp+rax], 37		; 00000025H
	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR format$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR buf$3[rsp+rax], cl
	mov	eax, 1
	imul	rax, 2
	mov	BYTE PTR buf$3[rsp+rax], 0

; 149  : 				debug_serial(buf);

	lea	rcx, QWORD PTR buf$3[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
$LN2@debug_prin:
$LN4@debug_prin:
$LN6@debug_prin:
$LN8@debug_prin:
$LN10@debug_prin:
$LN12@debug_prin:

; 150  : 			}
; 151  : 		}
; 152  : 		else

	jmp	SHORT $LN1@debug_prin
$LN20@debug_prin:

; 153  : 		{
; 154  : 			char buf[2];
; 155  : 			buf[0] = *format; buf[1] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR format$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR buf$2[rsp+rax], cl
	mov	eax, 1
	imul	rax, 1
	mov	BYTE PTR buf$2[rsp+rax], 0

; 156  : 			debug_serial(buf);

	lea	rcx, QWORD PTR buf$2[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
$LN1@debug_prin:

; 157  : 		}
; 158  : 		++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 159  : 	}

	jmp	$LN22@debug_prin
$LN21@debug_prin:

; 160  : 	va_end(args);
; 161  : 
; 162  : }

	add	rsp, 280				; 00000118H
	ret	0
_debug_print_ ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
i$1 = 32
tv65 = 40
string$ = 64
?debug_serial@@YAXPEAD@Z PROC				; debug_serial

; 74   : void debug_serial (char* string) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 75   : 	for (int i = 0; i < strlen(string); i++)

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
	call	strlen
	mov	rcx, QWORD PTR tv65[rsp]
	cmp	rcx, rax
	jae	SHORT $LN1@debug_seri

; 76   : 		write_serial(string[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR string$[rsp]
	movzx	ecx, BYTE PTR [rcx+rax]
	call	?write_serial@@YAXD@Z			; write_serial
	jmp	SHORT $LN2@debug_seri
$LN1@debug_seri:

; 77   : }

	add	rsp, 56					; 00000038H
	ret	0
?debug_serial@@YAXPEAD@Z ENDP				; debug_serial
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
a$ = 48
?write_serial@@YAXD@Z PROC				; write_serial

; 69   : void write_serial (char a) {

$LN5:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H
$LN2@write_seri:

; 70   : 	while (is_transmit_empty() == 0);

	call	?is_transmit_empty@@YAHXZ		; is_transmit_empty
	test	eax, eax
	jne	SHORT $LN1@write_seri
	jmp	SHORT $LN2@write_seri
$LN1@write_seri:

; 71   : 	x64_outportb (PORT, a);

	movzx	edx, BYTE PTR a$[rsp]
	mov	cx, 1016				; 000003f8H
	call	x64_outportb

; 72   : }

	add	rsp, 40					; 00000028H
	ret	0
?write_serial@@YAXD@Z ENDP				; write_serial
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
node$ = 32
?AuInitializeSerialFile@@YAXXZ PROC			; AuInitializeSerialFile

; 192  : void AuInitializeSerialFile() {

$LN3:
	sub	rsp, 56					; 00000038H

; 193  : 	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 112				; 00000070H
	call	malloc
	mov	QWORD PTR node$[rsp], rax

; 194  : 	strcpy (node->filename, "serial");

	mov	rax, QWORD PTR node$[rsp]
	lea	rdx, OFFSET FLAT:$SG3737
	mov	rcx, rax
	call	strcpy

; 195  : 	node->size = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+32], 0

; 196  : 	node->eof = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+36], 0

; 197  : 	node->pos = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+40], 0

; 198  : 	node->current = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	DWORD PTR [rax+44], 0

; 199  : 	node->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+48], 12

; 200  : 	node->status = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	BYTE PTR [rax+49], 0

; 201  : 	node->open = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+64], 0

; 202  : 	node->read = AuSerialRead;

	mov	rax, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:?AuSerialRead@@YA_KPEAU_vfs_node_@@PEA_KI@Z ; AuSerialRead
	mov	QWORD PTR [rax+72], rcx

; 203  : 	node->write = AuSerialWrite;

	mov	rax, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:?AuSerialWrite@@YAXPEAU_vfs_node_@@PEA_KI@Z ; AuSerialWrite
	mov	QWORD PTR [rax+80], rcx

; 204  : 	node->read_blk = 0;

	mov	rax, QWORD PTR node$[rsp]
	mov	QWORD PTR [rax+96], 0

; 205  : 	node->ioquery = AuSerialIoQuery;

	mov	rax, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:?AuSerialIoQuery@@YAHPEAU_vfs_node_@@HPEAX@Z ; AuSerialIoQuery
	mov	QWORD PTR [rax+104], rcx

; 206  : 	vfs_mount ("/dev/serial", node, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, OFFSET FLAT:$SG3738
	call	vfs_mount

; 207  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuInitializeSerialFile@@YAXXZ ENDP			; AuInitializeSerialFile
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?AuInitializeSerial@@YAXXZ PROC				; AuInitializeSerial

; 51   : void AuInitializeSerial() {

$LN3:
	sub	rsp, 40					; 00000028H

; 52   : 	x64_outportb (PORT + 1, 0x00);

	xor	edx, edx
	mov	cx, 1017				; 000003f9H
	call	x64_outportb

; 53   : 	x64_outportb ((PORT + 3), 0x80);

	mov	dl, 128					; 00000080H
	mov	cx, 1019				; 000003fbH
	call	x64_outportb

; 54   : 	x64_outportb ((PORT + 0), 0x03);

	mov	dl, 3
	mov	cx, 1016				; 000003f8H
	call	x64_outportb

; 55   : 	x64_outportb ((PORT + 1), 0x00);

	xor	edx, edx
	mov	cx, 1017				; 000003f9H
	call	x64_outportb

; 56   : 	x64_outportb ((PORT + 3), 0x03);

	mov	dl, 3
	mov	cx, 1019				; 000003fbH
	call	x64_outportb

; 57   : 	x64_outportb ((PORT + 2), 0xC7);

	mov	dl, 199					; 000000c7H
	mov	cx, 1018				; 000003faH
	call	x64_outportb

; 58   : 	x64_outportb ((PORT + 4), 0x0B);

	mov	dl, 11
	mov	cx, 1020				; 000003fcH
	call	x64_outportb

; 59   : 
; 60   : 	//x64_outportb (PORT + 4, 0x0F);
; 61   : 	//interrupt_set (4,serial_handler, 4);
; 62   : 	_serial_initialized_ = true;

	mov	BYTE PTR _serial_initialized_, 1

; 63   : }

	add	rsp, 40					; 00000028H
	ret	0
?AuInitializeSerial@@YAXXZ ENDP				; AuInitializeSerial
_TEXT	ENDS
END
