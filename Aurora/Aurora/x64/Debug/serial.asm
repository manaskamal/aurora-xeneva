; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_BSS	SEGMENT
_serial_initialized_ DB 01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG2865	DB	'Serial Handler', 0aH, 00H
$SG2958	DB	'.', 00H
CONST	ENDS
PUBLIC	?initialize_serial@@YAXXZ			; initialize_serial
PUBLIC	?write_serial@@YAXD@Z				; write_serial
PUBLIC	?debug_serial@@YAXPEAD@Z			; debug_serial
PUBLIC	?_debug_print_@@YAXPEADZZ			; _debug_print_
PUBLIC	?is_serial_initialized@@YA_NXZ			; is_serial_initialized
PUBLIC	?serial_handler@@YAX_KPEAX@Z			; serial_handler
PUBLIC	?is_transmit_empty@@YAHXZ			; is_transmit_empty
EXTRN	x64_inportb:PROC
EXTRN	x64_outportb:PROC
EXTRN	?interrupt_end@@YAXI@Z:PROC			; interrupt_end
EXTRN	?strlen@@YA_KPEBD@Z:PROC			; strlen
EXTRN	?sztoa@@YAPEAD_KPEADH@Z:PROC			; sztoa
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?ftoa@@YAPEADME@Z:PROC				; ftoa
EXTRN	_fltused:DWORD
pdata	SEGMENT
$pdata$?initialize_serial@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+93
	DD	imagerel $unwind$?initialize_serial@@YAXXZ
$pdata$?write_serial@@YAXD@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?write_serial@@YAXD@Z
$pdata$?debug_serial@@YAXPEAD@Z DD imagerel $LN6
	DD	imagerel $LN6+85
	DD	imagerel $unwind$?debug_serial@@YAXPEAD@Z
$pdata$?_debug_print_@@YAXPEADZZ DD imagerel $LN25
	DD	imagerel $LN25+860
	DD	imagerel $unwind$?_debug_print_@@YAXPEADZZ
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
$unwind$?_debug_print_@@YAXPEADZZ DD 021b01H
	DD	023011bH
$unwind$?serial_handler@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?is_transmit_empty@@YAHXZ DD 010401H
	DD	04204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?is_transmit_empty@@YAHXZ PROC				; is_transmit_empty

; 43   : int is_transmit_empty () {

$LN3:
	sub	rsp, 40					; 00000028H

; 44   : 	return x64_inportb (PORT + 5) & 0x20;

	mov	cx, 1021				; 000003fdH
	call	x64_inportb
	movzx	eax, al
	and	eax, 32					; 00000020H

; 45   : }

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

; 23   : void serial_handler (size_t v, void* p) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 24   : 	printf ("Serial Handler\n");

	lea	rcx, OFFSET FLAT:$SG2865
	call	?printf@@YAXPEBDZZ			; printf

; 25   : 	interrupt_end(4);

	mov	ecx, 4
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 26   : }

	add	rsp, 40					; 00000028H
	ret	0
?serial_handler@@YAX_KPEAX@Z ENDP			; serial_handler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?is_serial_initialized@@YA_NXZ PROC			; is_serial_initialized

; 140  : 	return _serial_initialized_;

	movzx	eax, BYTE PTR _serial_initialized_

; 141  : }

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

; 57   : void _debug_print_ (char* format, ...) {

$LN25:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 280				; 00000118H

; 58   : 	_va_list_ args;
; 59   : 	va_start(args, format);

	lea	rax, QWORD PTR format$[rsp+8]
	mov	QWORD PTR args$[rsp], rax
$LN22@debug_prin:

; 60   : 
; 61   : 	while (*format)

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	$LN21@debug_prin

; 62   : 	{
; 63   : 		if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	$LN20@debug_prin

; 64   : 		{
; 65   : 			++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 66   : 			if (*format == 'd')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 100				; 00000064H
	jne	$LN19@debug_prin

; 67   : 			{
; 68   : 				size_t width = 0;

	mov	QWORD PTR width$6[rsp], 0

; 69   : 				if (format[1] == '.')

	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 46					; 0000002eH
	jne	$LN18@debug_prin

; 70   : 				{
; 71   : 					for (size_t i = 2; format[i] >= '0' && format[i] <= '9'; ++i)

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

; 72   : 					{
; 73   : 						width *= 10;

	mov	rax, QWORD PTR width$6[rsp]
	imul	rax, 10
	mov	QWORD PTR width$6[rsp], rax

; 74   : 						width += format[i] - '0';

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

; 75   : 					}

	jmp	SHORT $LN16@debug_prin
$LN15@debug_prin:
$LN18@debug_prin:

; 76   : 				}
; 77   : 				size_t i = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR i$5[rsp], rax

; 78   : 				char buffer[sizeof(size_t) * 8 + 1];
; 79   : 			//	size_t len
; 80   : 				if (i < 0) {

	cmp	QWORD PTR i$5[rsp], 0
	jae	SHORT $LN14@debug_prin

; 81   : 					i = +i;

	mov	rax, QWORD PTR i$5[rsp]
	mov	QWORD PTR i$5[rsp], rax

; 82   : 					sztoa (i,buffer,10);

	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$11[rsp]
	mov	rcx, QWORD PTR i$5[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 83   : 				}else {

	jmp	SHORT $LN13@debug_prin
$LN14@debug_prin:

; 84   : 					sztoa(i, buffer, 10);

	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$11[rsp]
	mov	rcx, QWORD PTR i$5[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 85   : 					size_t len = strlen(buffer);

	lea	rcx, QWORD PTR buffer$11[rsp]
	call	?strlen@@YA_KPEBD@Z			; strlen
	mov	QWORD PTR len$10[rsp], rax
$LN13@debug_prin:

; 86   : 				}
; 87   : 			/*	while (len++ < width)
; 88   : 					puts("0");*/
; 89   : 				debug_serial(buffer);

	lea	rcx, QWORD PTR buffer$11[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	$LN12@debug_prin
$LN19@debug_prin:

; 90   : 			}
; 91   : 			else if (*format == 'c')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 99					; 00000063H
	jne	SHORT $LN11@debug_prin

; 92   : 			{
; 93   : 				char c = va_arg(args, char);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 4
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	movzx	eax, BYTE PTR [rax-4]
	mov	BYTE PTR c$1[rsp], al

; 94   : 				//char buffer[sizeof(size_t) * 8 + 1];
; 95   : 				//sztoa(c, buffer, 10);
; 96   : 				//puts(buffer);
; 97   : 				write_serial(c);

	movzx	ecx, BYTE PTR c$1[rsp]
	call	?write_serial@@YAXD@Z			; write_serial
	jmp	$LN10@debug_prin
$LN11@debug_prin:

; 98   : 			}
; 99   : 			else if (*format == 'x')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 120				; 00000078H
	jne	SHORT $LN9@debug_prin

; 100  : 			{
; 101  : 				size_t x = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$9[rsp], rax

; 102  : 				char buffer[sizeof(size_t) * 8 + 1];
; 103  : 				sztoa(x, buffer, 16);

	mov	r8d, 16
	lea	rdx, QWORD PTR buffer$12[rsp]
	mov	rcx, QWORD PTR x$9[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 104  : 				//puts("0x");
; 105  : 				debug_serial(buffer);

	lea	rcx, QWORD PTR buffer$12[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	$LN8@debug_prin
$LN9@debug_prin:

; 106  : 			}
; 107  : 			else if (*format == 's')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 115				; 00000073H
	jne	SHORT $LN7@debug_prin

; 108  : 			{
; 109  : 				char* x = va_arg(args, char*);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$8[rsp], rax

; 110  : 				debug_serial(x);

	mov	rcx, QWORD PTR x$8[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	$LN6@debug_prin
$LN7@debug_prin:

; 111  : 			}
; 112  : 			else if (*format == 'f')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 102				; 00000066H
	jne	SHORT $LN5@debug_prin

; 113  : 			{
; 114  : 				double x = va_arg(args, double);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	movsdx	xmm0, QWORD PTR [rax-8]
	movsdx	QWORD PTR x$7[rsp], xmm0

; 115  : 				debug_serial(ftoa(x,2));

	cvtsd2ss xmm0, QWORD PTR x$7[rsp]
	mov	dl, 2
	call	?ftoa@@YAPEADME@Z			; ftoa
	mov	rcx, rax
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
	jmp	SHORT $LN4@debug_prin
$LN5@debug_prin:

; 116  : 			}
; 117  : 			else if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	SHORT $LN3@debug_prin

; 118  : 			{
; 119  : 				debug_serial(".");

	lea	rcx, OFFSET FLAT:$SG2958
	call	?debug_serial@@YAXPEAD@Z		; debug_serial

; 120  : 			}
; 121  : 			else

	jmp	SHORT $LN2@debug_prin
$LN3@debug_prin:

; 122  : 			{
; 123  : 				char buf[3];
; 124  : 				buf[0] = '%'; buf[1] = *format; buf[2] = '\0';

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

; 125  : 				debug_serial(buf);

	lea	rcx, QWORD PTR buf$3[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
$LN2@debug_prin:
$LN4@debug_prin:
$LN6@debug_prin:
$LN8@debug_prin:
$LN10@debug_prin:
$LN12@debug_prin:

; 126  : 			}
; 127  : 		}
; 128  : 		else

	jmp	SHORT $LN1@debug_prin
$LN20@debug_prin:

; 129  : 		{
; 130  : 			char buf[2];
; 131  : 			buf[0] = *format; buf[1] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR format$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR buf$2[rsp+rax], cl
	mov	eax, 1
	imul	rax, 1
	mov	BYTE PTR buf$2[rsp+rax], 0

; 132  : 			debug_serial(buf);

	lea	rcx, QWORD PTR buf$2[rsp]
	call	?debug_serial@@YAXPEAD@Z		; debug_serial
$LN1@debug_prin:

; 133  : 		}
; 134  : 		++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 135  : 	}

	jmp	$LN22@debug_prin
$LN21@debug_prin:

; 136  : 	va_end(args);
; 137  : }

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

; 52   : void debug_serial (char* string) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 53   : 	for (int i = 0; i < strlen(string); i++)

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

; 54   : 		write_serial(string[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR string$[rsp]
	movzx	ecx, BYTE PTR [rcx+rax]
	call	?write_serial@@YAXD@Z			; write_serial
	jmp	SHORT $LN2@debug_seri
$LN1@debug_seri:

; 55   : }

	add	rsp, 56					; 00000038H
	ret	0
?debug_serial@@YAXPEAD@Z ENDP				; debug_serial
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
a$ = 48
?write_serial@@YAXD@Z PROC				; write_serial

; 47   : void write_serial (char a) {

$LN5:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H
$LN2@write_seri:

; 48   : 	while (is_transmit_empty() == 0);

	call	?is_transmit_empty@@YAHXZ		; is_transmit_empty
	test	eax, eax
	jne	SHORT $LN1@write_seri
	jmp	SHORT $LN2@write_seri
$LN1@write_seri:

; 49   : 	x64_outportb (PORT, a);

	movzx	edx, BYTE PTR a$[rsp]
	mov	cx, 1016				; 000003f8H
	call	x64_outportb

; 50   : }

	add	rsp, 40					; 00000028H
	ret	0
?write_serial@@YAXD@Z ENDP				; write_serial
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\serial.cpp
_TEXT	SEGMENT
?initialize_serial@@YAXXZ PROC				; initialize_serial

; 28   : void initialize_serial() {

$LN3:
	sub	rsp, 40					; 00000028H

; 29   : 	x64_outportb (PORT + 1, 0x00);

	xor	edx, edx
	mov	cx, 1017				; 000003f9H
	call	x64_outportb

; 30   : 	x64_outportb (PORT + 3, 0x80);

	mov	dl, 128					; 00000080H
	mov	cx, 1019				; 000003fbH
	call	x64_outportb

; 31   : 	x64_outportb (PORT + 0, 0x03);

	mov	dl, 3
	mov	cx, 1016				; 000003f8H
	call	x64_outportb

; 32   : 	x64_outportb (PORT + 1, 0x00);

	xor	edx, edx
	mov	cx, 1017				; 000003f9H
	call	x64_outportb

; 33   : 	x64_outportb (PORT + 3, 0x03);

	mov	dl, 3
	mov	cx, 1019				; 000003fbH
	call	x64_outportb

; 34   : 	x64_outportb (PORT + 2, 0xC7);

	mov	dl, 199					; 000000c7H
	mov	cx, 1018				; 000003faH
	call	x64_outportb

; 35   : 	x64_outportb (PORT + 4, 0x0B);

	mov	dl, 11
	mov	cx, 1020				; 000003fcH
	call	x64_outportb

; 36   : 	
; 37   : 
; 38   : 	//x64_outportb (PORT + 4, 0x0F);
; 39   : 	//interrupt_set (4,serial_handler, 4);
; 40   : 	_serial_initialized_ = true;

	mov	BYTE PTR _serial_initialized_, 1

; 41   : }

	add	rsp, 40					; 00000028H
	ret	0
?initialize_serial@@YAXXZ ENDP				; initialize_serial
_TEXT	ENDS
END
