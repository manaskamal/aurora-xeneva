; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_BSS	SEGMENT
_serial_initialized_ DB 01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG3142	DB	'.', 00H
	ORG $+6
$SG3049	DB	'Serial Handler', 0aH, 00H
CONST	ENDS
PUBLIC	?AuInitializeSerial@@YAXXZ			; AuInitializeSerial
PUBLIC	?write_serial@@YAXD@Z				; write_serial
PUBLIC	?debug_serial@@YAXPEAD@Z			; debug_serial
PUBLIC	?_debug_print_@@YAXPEADZZ			; _debug_print_
PUBLIC	?is_serial_initialized@@YA_NXZ			; is_serial_initialized
PUBLIC	?SerialHandler@@YAX_KPEAX@Z			; SerialHandler
PUBLIC	?is_transmit_empty@@YAHXZ			; is_transmit_empty
EXTRN	x64_inportb:PROC
EXTRN	x64_outportb:PROC
EXTRN	AuInterruptEnd:PROC
EXTRN	strlen:PROC
EXTRN	?sztoa@@YAPEAD_KPEADH@Z:PROC			; sztoa
EXTRN	printf:PROC
EXTRN	?ftoa@@YAPEADME@Z:PROC				; ftoa
EXTRN	p2v:PROC
EXTRN	_fltused:DWORD
pdata	SEGMENT
$pdata$?AuInitializeSerial@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+156
	DD	imagerel $unwind$?AuInitializeSerial@@YAXXZ
$pdata$?write_serial@@YAXD@Z DD imagerel $LN5
	DD	imagerel $LN5+47
	DD	imagerel $unwind$?write_serial@@YAXD@Z
$pdata$?debug_serial@@YAXPEAD@Z DD imagerel $LN6
	DD	imagerel $LN6+85
	DD	imagerel $unwind$?debug_serial@@YAXPEAD@Z
$pdata$?_debug_print_@@YAXPEADZZ DD imagerel $LN25
	DD	imagerel $LN25+860
	DD	imagerel $unwind$?_debug_print_@@YAXPEADZZ
$pdata$?SerialHandler@@YAX_KPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+41
	DD	imagerel $unwind$?SerialHandler@@YAX_KPEAX@Z
$pdata$?is_transmit_empty@@YAHXZ DD imagerel $LN3
	DD	imagerel $LN3+33
	DD	imagerel $unwind$?is_transmit_empty@@YAHXZ
pdata	ENDS
xdata	SEGMENT
$unwind$?AuInitializeSerial@@YAXXZ DD 010401H
	DD	04204H
$unwind$?write_serial@@YAXD@Z DD 010801H
	DD	04208H
$unwind$?debug_serial@@YAXPEAD@Z DD 010901H
	DD	06209H
$unwind$?_debug_print_@@YAXPEADZZ DD 021b01H
	DD	023011bH
$unwind$?SerialHandler@@YAX_KPEAX@Z DD 010e01H
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

; 45   : 	return x64_inportb (p2v(PORT + 5)) & 0x20;

	mov	ecx, 1021				; 000003fdH
	call	p2v
	movzx	ecx, ax
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
?SerialHandler@@YAX_KPEAX@Z PROC			; SerialHandler

; 24   : void SerialHandler (size_t v, void* p) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 25   : 	printf ("Serial Handler\n");

	lea	rcx, OFFSET FLAT:$SG3049
	call	printf

; 26   : 	AuInterruptEnd(4);

	mov	ecx, 4
	call	AuInterruptEnd

; 27   : }

	add	rsp, 40					; 00000028H
	ret	0
?SerialHandler@@YAX_KPEAX@Z ENDP			; SerialHandler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?is_serial_initialized@@YA_NXZ PROC			; is_serial_initialized

; 141  : 	return _serial_initialized_;

	movzx	eax, BYTE PTR _serial_initialized_

; 142  : }

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
?_debug_print_@@YAXPEADZZ PROC				; _debug_print_

; 58   : void _debug_print_ (char* format, ...) {

$LN25:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 280				; 00000118H

; 59   : 	_va_list_ args;
; 60   : 	va_start(args, format);

	lea	rax, QWORD PTR format$[rsp+8]
	mov	QWORD PTR args$[rsp], rax
$LN22@debug_prin:

; 61   : 
; 62   : 	while (*format)

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	$LN21@debug_prin

; 63   : 	{
; 64   : 		if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	$LN20@debug_prin

; 65   : 		{
; 66   : 			++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 67   : 			if (*format == 'd')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 100				; 00000064H
	jne	$LN19@debug_prin

; 68   : 			{
; 69   : 				size_t width = 0;

	mov	QWORD PTR width$6[rsp], 0

; 70   : 				if (format[1] == '.')

	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 46					; 0000002eH
	jne	$LN18@debug_prin

; 71   : 				{
; 72   : 					for (size_t i = 2; format[i] >= '0' && format[i] <= '9'; ++i)

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

; 73   : 					{
; 74   : 						width *= 10;

	mov	rax, QWORD PTR width$6[rsp]
	imul	rax, 10
	mov	QWORD PTR width$6[rsp], rax

; 75   : 						width += format[i] - '0';

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

; 76   : 					}

	jmp	SHORT $LN16@debug_prin
$LN15@debug_prin:
$LN18@debug_prin:

; 77   : 				}
; 78   : 				size_t i = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR i$5[rsp], rax

; 79   : 				char buffer[sizeof(size_t) * 8 + 1];
; 80   : 			//	size_t len
; 81   : 				if (i < 0) {

	cmp	QWORD PTR i$5[rsp], 0
	jae	SHORT $LN14@debug_prin

; 82   : 					i = +i;

	mov	rax, QWORD PTR i$5[rsp]
	mov	QWORD PTR i$5[rsp], rax

; 83   : 					sztoa (i,buffer,10);

	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$11[rsp]
	mov	rcx, QWORD PTR i$5[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 84   : 				}else {

	jmp	SHORT $LN13@debug_prin
$LN14@debug_prin:

; 85   : 					sztoa(i, buffer, 10);

	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$11[rsp]
	mov	rcx, QWORD PTR i$5[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 86   : 					size_t len = strlen(buffer);

	lea	rcx, QWORD PTR buffer$11[rsp]
	call	strlen
	mov	QWORD PTR len$10[rsp], rax
$LN13@debug_prin:

; 87   : 				}
; 88   : 			/*	while (len++ < width)
; 89   : 					puts("0");*/
; 90   : 				debug_serial(buffer);

	lea	rcx, QWORD PTR buffer$11[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	$LN12@debug_prin
$LN19@debug_prin:

; 91   : 			}
; 92   : 			else if (*format == 'c')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 99					; 00000063H
	jne	SHORT $LN11@debug_prin

; 93   : 			{
; 94   : 				char c = va_arg(args, char);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 4
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	movzx	eax, BYTE PTR [rax-4]
	mov	BYTE PTR c$1[rsp], al

; 95   : 				//char buffer[sizeof(size_t) * 8 + 1];
; 96   : 				//sztoa(c, buffer, 10);
; 97   : 				//puts(buffer);
; 98   : 				write_serial(c);

	movzx	ecx, BYTE PTR c$1[rsp]
	call	?write_serial@@YAXD@Z			; write_serial
	jmp	$LN10@debug_prin
$LN11@debug_prin:

; 99   : 			}
; 100  : 			else if (*format == 'x')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 120				; 00000078H
	jne	SHORT $LN9@debug_prin

; 101  : 			{
; 102  : 				size_t x = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$9[rsp], rax

; 103  : 				char buffer[sizeof(size_t) * 8 + 1];
; 104  : 				sztoa(x, buffer, 16);

	mov	r8d, 16
	lea	rdx, QWORD PTR buffer$12[rsp]
	mov	rcx, QWORD PTR x$9[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 105  : 				//puts("0x");
; 106  : 				debug_serial(buffer);

	lea	rcx, QWORD PTR buffer$12[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	$LN8@debug_prin
$LN9@debug_prin:

; 107  : 			}
; 108  : 			else if (*format == 's')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 115				; 00000073H
	jne	SHORT $LN7@debug_prin

; 109  : 			{
; 110  : 				char* x = va_arg(args, char*);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$8[rsp], rax

; 111  : 				debug_serial(x);

	mov	rcx, QWORD PTR x$8[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	$LN6@debug_prin
$LN7@debug_prin:

; 112  : 			}
; 113  : 			else if (*format == 'f')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 102				; 00000066H
	jne	SHORT $LN5@debug_prin

; 114  : 			{
; 115  : 				double x = va_arg(args, double);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	movsdx	xmm0, QWORD PTR [rax-8]
	movsdx	QWORD PTR x$7[rsp], xmm0

; 116  : 				debug_serial(ftoa(x,2));

	cvtsd2ss xmm0, QWORD PTR x$7[rsp]
	mov	dl, 2
	call	?ftoa@@YAPEADME@Z			; ftoa
	mov	rcx, rax
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	SHORT $LN4@debug_prin
$LN5@debug_prin:

; 117  : 			}
; 118  : 			else if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	SHORT $LN3@debug_prin

; 119  : 			{
; 120  : 				debug_serial(".");

	lea	rcx, OFFSET FLAT:$SG3142
	call	?debug_serial@@YAXPEAD@Z		; debug_serial

; 121  : 			}
; 122  : 			else

	jmp	SHORT $LN2@debug_prin
$LN3@debug_prin:

; 123  : 			{
; 124  : 				char buf[3];
; 125  : 				buf[0] = '%'; buf[1] = *format; buf[2] = '\0';

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

; 126  : 				debug_serial(buf);

	lea	rcx, QWORD PTR buf$3[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
$LN2@debug_prin:
$LN4@debug_prin:
$LN6@debug_prin:
$LN8@debug_prin:
$LN10@debug_prin:
$LN12@debug_prin:

; 127  : 			}
; 128  : 		}
; 129  : 		else

	jmp	SHORT $LN1@debug_prin
$LN20@debug_prin:

; 130  : 		{
; 131  : 			char buf[2];
; 132  : 			buf[0] = *format; buf[1] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR format$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR buf$2[rsp+rax], cl
	mov	eax, 1
	imul	rax, 1
	mov	BYTE PTR buf$2[rsp+rax], 0

; 133  : 			debug_serial(buf);

	lea	rcx, QWORD PTR buf$2[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
$LN1@debug_prin:

; 134  : 		}
; 135  : 		++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 136  : 	}

	jmp	$LN22@debug_prin
$LN21@debug_prin:

; 137  : 	va_end(args);
; 138  : }

	add	rsp, 280				; 00000118H
	ret	0
?_debug_print_@@YAXPEADZZ ENDP				; _debug_print_
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
	call	strlen
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

$LN5:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H
$LN2@write_seri:

; 49   : 	while (is_transmit_empty() == 0);

	call	?is_transmit_empty@@YAHXZ		; is_transmit_empty
	test	eax, eax
	jne	SHORT $LN1@write_seri
	jmp	SHORT $LN2@write_seri
$LN1@write_seri:

; 50   : 	x64_outportb (p2v(PORT), a);

	mov	ecx, 1016				; 000003f8H
	call	p2v
	movzx	edx, BYTE PTR a$[rsp]
	movzx	ecx, ax
	call	x64_outportb

; 51   : }

	add	rsp, 40					; 00000028H
	ret	0
?write_serial@@YAXD@Z ENDP				; write_serial
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?AuInitializeSerial@@YAXXZ PROC				; AuInitializeSerial

; 29   : void AuInitializeSerial() {

$LN3:
	sub	rsp, 40					; 00000028H

; 30   : 	x64_outportb (p2v(PORT + 1), 0x00);

	mov	ecx, 1017				; 000003f9H
	call	p2v
	xor	edx, edx
	movzx	ecx, ax
	call	x64_outportb

; 31   : 	x64_outportb (p2v(PORT + 3), 0x80);

	mov	ecx, 1019				; 000003fbH
	call	p2v
	mov	dl, 128					; 00000080H
	movzx	ecx, ax
	call	x64_outportb

; 32   : 	x64_outportb (p2v(PORT + 0), 0x03);

	mov	ecx, 1016				; 000003f8H
	call	p2v
	mov	dl, 3
	movzx	ecx, ax
	call	x64_outportb

; 33   : 	x64_outportb (p2v(PORT + 1), 0x00);

	mov	ecx, 1017				; 000003f9H
	call	p2v
	xor	edx, edx
	movzx	ecx, ax
	call	x64_outportb

; 34   : 	x64_outportb (p2v(PORT + 3), 0x03);

	mov	ecx, 1019				; 000003fbH
	call	p2v
	mov	dl, 3
	movzx	ecx, ax
	call	x64_outportb

; 35   : 	x64_outportb (p2v(PORT + 2), 0xC7);

	mov	ecx, 1018				; 000003faH
	call	p2v
	mov	dl, 199					; 000000c7H
	movzx	ecx, ax
	call	x64_outportb

; 36   : 	x64_outportb (p2v(PORT + 4), 0x0B);

	mov	ecx, 1020				; 000003fcH
	call	p2v
	mov	dl, 11
	movzx	ecx, ax
	call	x64_outportb

; 37   : 	
; 38   : 
; 39   : 	//x64_outportb (PORT + 4, 0x0F);
; 40   : 	//interrupt_set (4,serial_handler, 4);
; 41   : 	_serial_initialized_ = true;

	mov	BYTE PTR _serial_initialized_, 1

; 42   : }

	add	rsp, 40					; 00000028H
	ret	0
?AuInitializeSerial@@YAXXZ ENDP				; AuInitializeSerial
_TEXT	ENDS
END
